#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/UObject.hpp>
#include <Unreal/AActor.hpp>
#include <Unreal/UPackage.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Unreal/PackageName.hpp>
#include <Unreal/UnrealVersion.hpp>
#include <Unreal/VersionedContainer/Container.hpp>
#include <Unreal/Searcher/ObjectSearcher.hpp>
#include <Unreal/Searcher/ObjectSearcherProfiler.hpp>
#include <Unreal/ClassListener.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#ifdef __linux__
#include <vector>
#include <algorithm>
#endif

namespace RC::Unreal::UObjectGlobals
{
    RC_UE_API Function<UObject*(StaticConstructObject_Internal_Params_Deprecated)> GlobalState::StaticConstructObjectInternalDeprecated{};
    RC_UE_API Function<UObject*(const FStaticConstructObjectParameters&)> GlobalState::StaticConstructObjectInternal{};

    auto SetupStaticConstructObjectInternalAddress(void* FunctionAddress) -> void
    {
        GlobalState::StaticConstructObjectInternal.assign_address(FunctionAddress);
        GlobalState::StaticConstructObjectInternalDeprecated.assign_address(FunctionAddress);
    }

    namespace Below426
    {
        static auto StaticConstructObject(const FStaticConstructObjectParameters& Params) -> UObject*
        {
            return GlobalState::StaticConstructObjectInternalDeprecated(
                    Params.Class,
                    Params.Outer,
                    Params.Name,
                    Params.SetFlags,
                    Params.InternalSetFlags,
                    Params.Template,
                    Params.bCopyTransientsFromClassDefaults,
                    Params.InstanceGraph,
                    Params.bAssumeTemplateIsArchetype,
                    Params.ExternalPackage
            );
        }
    }
    namespace Below56
    {
        static auto StaticConstructObject(const FStaticConstructObjectParameters& Params) -> UObject*
        {
            static Function<UObject*(const FStaticConstructObjectParameters&)> StaticConstructObjectInternal = [&]() {
                return GlobalState::StaticConstructObjectInternal.get_function_address();
            }();

            if (!StaticConstructObjectInternal.is_ready()) { return nullptr; }
            if (Params.Class == nullptr) { return nullptr; }

            return StaticConstructObjectInternal(Params);
        }
    }
    namespace Above55
    {
        static auto StaticConstructObject(const FStaticConstructObjectParameters& Params) -> UObject*
        {
            static Function<UObject*(const FStaticConstructObjectParameters&)> StaticConstructObjectInternal = [&]() {
                return GlobalState::StaticConstructObjectInternal.get_function_address();
            }();

            if (!StaticConstructObjectInternal.is_ready()) { return nullptr; }
            if (Params.Class == nullptr) { return nullptr; }

            return StaticConstructObjectInternal(Params);
        }
    }

    auto StaticConstructObject(const FStaticConstructObjectParameters& GenericParams) -> UObject*
    {
        if (Version::IsBelow(4, 26))
        {
            return Below426::StaticConstructObject(GenericParams);
        }
        else if (Version::IsBelow(5, 6))
        {
            Below56::FStaticConstructObjectParameters Params{};
            Params.Class = GenericParams.Class;
            Params.Outer = GenericParams.Outer;
            Params.Name = GenericParams.Name;
            Params.SetFlags = GenericParams.SetFlags;
            Params.InternalSetFlags = GenericParams.InternalSetFlags;
            Params.Template = GenericParams.Template;
            Params.bCopyTransientsFromClassDefaults = GenericParams.bCopyTransientsFromClassDefaults;
            Params.InstanceGraph = GenericParams.InstanceGraph;
            Params.bAssumeTemplateIsArchetype = GenericParams.bAssumeTemplateIsArchetype;
            Params.ExternalPackage = GenericParams.ExternalPackage;
            return Below56::StaticConstructObject(Params);
        }
        else
        {
            Above55::FStaticConstructObjectParameters Params{};
            Params.Class = GenericParams.Class;
            Params.Outer = GenericParams.Outer;
            Params.Name = GenericParams.Name;
            Params.SetFlags = GenericParams.SetFlags;
            Params.InternalSetFlags = GenericParams.InternalSetFlags;
            Params.Template = GenericParams.Template;
            Params.bCopyTransientsFromClassDefaults = GenericParams.bCopyTransientsFromClassDefaults;
            Params.InstanceGraph = GenericParams.InstanceGraph;
            Params.bAssumeTemplateIsArchetype = GenericParams.bAssumeTemplateIsArchetype;
            Params.ExternalPackage = GenericParams.ExternalPackage;
            return Above55::StaticConstructObject(Params);
        }
    }

    auto StaticFindObject_InternalSlow([[maybe_unused]]UClass* ObjectClass, [[maybe_unused]]UObject* InObjectPackage, const CharType* OrigInName, [[maybe_unused]]bool bExactClass) -> UObject*
    {
        UObject* FoundObject{};

        UObjectGlobals::ForEachUObject([&](UObject* Object, [[maybe_unused]]int32_t ChunkIndex, [[maybe_unused]]int32_t ObjectIndex) {
            // This call to 'get_full_name' is a problem because it relies on offsets already being found
            // This function is called before offsets have been found as a way to check if required objects have been initialized
            auto ObjFullName = Object->GetFullName();
            auto ObjFullNameNoType = ObjFullName.substr(ObjFullName.find(STR(" ")) + 1);

            if (String::iequal(ObjFullNameNoType, OrigInName))
            {
                FoundObject = static_cast<UObject*>(Object);
                return LoopAction::Break;
            }
            else
            {
                return LoopAction::Continue;
            }
        });

        return FoundObject;
    }

    auto StaticFindObject_InternalNoToStringFromNames(const std::vector<FName>& NameParts) -> UObject*
    {
        UObject* FoundObject{};

        for (const auto& NamePart : NameParts)
        {
            if (NamePart == NAME_None)
            {
                // NAME_None means we're not far enough along engine init for this object to exist yet.
                return nullptr;
            }
        }


        UObjectGlobals::ForEachUObject([&](UObject* Object, [[maybe_unused]]int32_t ChunkIndex, [[maybe_unused]]int32_t ObjectIndex) {
            // In order to remain safe to use early in init before we've hooked FName::ToString up to KismetStringLibrary:Conv_NameToString, we have to
            // compare FNames directly instead of using GetFullName.
            int32_t NumPathParts{};
            auto PathObject = Object;
            while (PathObject)
            {
                const auto PathName = PathObject->GetNamePrivate();
                const auto It = std::ranges::find_if(NameParts, [&](const FName NamePart) {
                    return NamePart.Equals(PathName);
                });
                if (It == NameParts.end())
                {
                    return LoopAction::Continue;
                }
                else
                {
                    PathObject = PathObject->GetOuterPrivate();
                    ++NumPathParts;
                }
            }
            if (NumPathParts == NameParts.size())
            {
                FoundObject = Object;
                return LoopAction::Break;
            }
            else
            {
                return LoopAction::Continue;
            }
        });

        return FoundObject;
    }

    auto StaticFindObject_InternalNoToStringFromStrings(const std::vector<StringViewType>& NameParts) -> UObject*
    {
        std::vector<FName> Names{};
        for (const auto& NamePart : NameParts)
        {
            Names.emplace_back(NamePart, FNAME_Find);
        }
        return StaticFindObject_InternalNoToStringFromNames(Names);
    }

    auto static IsValidObjectForFindXOf(UObject* object) -> bool
    {
        return !object->HasAnyFlags(static_cast<EObjectFlags>(RF_ClassDefaultObject | RF_ArchetypeObject)) && !object->IsA<UClass>();
    }

    UObject* FindObject(UClass* Class, UObject* InOuter, File::StringViewType InName, bool bExactClass, ObjectSearcher* InSearcher)
    {
        return FindObject(Class, InOuter, FromCharTypePtr<TCHAR>(InName.data()), bExactClass, InSearcher);
    }

    UObject* FindObject(UClass* Class, UObject* InOuter, const TCHAR* InName, bool bExactClass, ObjectSearcher* InSearcher)
    {
        if (!GUObjectArray)
        {
            return nullptr;
        }

        bool bObjectIsCached{};
        if (!Class && !InOuter && InName && !bExactClass)
        {
            if (auto CachedObject = GetGlobalObject(ToCharTypePtr(InName)); CachedObject)
            {
                return CachedObject;
            }
        }

        if (!InName)
        {
            throw std::runtime_error{"Call to FindObject with no InName is not allowed"};
        }

        auto GetPackageNameFromLongName = [](const File::StringType& LongName) -> File::StringType
        {
            auto DelimiterOffset = LongName.find(STR("."));
            if (DelimiterOffset == LongName.npos)
            {
                throw std::runtime_error{"GetPackageNameFromLongName: Name wasn't long."};
            }
            return LongName.substr(0, DelimiterOffset);
        };

        UObject* FoundObject{nullptr};
        const bool bAnyPackage = InOuter == ANY_PACKAGE;
        UObject* ObjectPackage = bAnyPackage ? nullptr : InOuter;
        const bool bIsLongName = !FPackageName::IsShortPackageName(ToCharTypePtr(InName));
        FName ShortName = bIsLongName ? NAME_None : FName(ToCharTypePtr(InName), FNAME_Add);
        FName PackageName = bIsLongName ? FName(GetPackageNameFromLongName(ToCharTypePtr(InName)), FNAME_Add) : NAME_None;

        if (bIsLongName)
        {
            auto NameView = StringViewType{InName};
            auto LastColonDelimiter = NameView.find_last_of(STR(':'));
            auto LastDotDelimiter = NameView.find_last_of(STR('.'));
            if (LastDotDelimiter == NameView.npos && LastColonDelimiter == NameView.npos)
            {
                // Name only contains path.
                ShortName = FName(NameView, FNAME_Add);
            }
            else if (LastColonDelimiter == NameView.npos)
            {
                // Only dots, so the short name should be after the last dot.
                ShortName = FName(NameView.substr(LastDotDelimiter + 1), FNAME_Add);
            }
            else if (LastDotDelimiter == NameView.npos)
            {
                // Only colons, so the short name should be after the last colon.
                ShortName = FName(NameView.substr(LastColonDelimiter + 1), FNAME_Add);
            }
            else
            {
                // Mix of dots and colons.
                if (LastColonDelimiter > LastDotDelimiter)
                {
                    // Last colon is after the last dot, so the short name should be after the last colon.
                    ShortName = FName(NameView.substr(LastColonDelimiter + 1), FNAME_Add);
                }
                else
                {
                    // Last dot is after the last colon, so the short name should be after the last dot.
                    ShortName = FName(NameView.substr(LastDotDelimiter + 1), FNAME_Add);
                }
            }
        }

        auto Searcher = [&InSearcher, &Class]() -> ObjectSearcher {
            return InSearcher ? *InSearcher : FindObjectSearcher(Class, nullptr);
        }();

        bool bQuickSearch = Searcher.IsFast();

        Searcher.ForEach([&](UObject* Object) {
            if (bExactClass && Class != Object->GetClassPrivate()) { return LoopAction::Continue; }

            // If this is a quick search, then the object is guaranteed to be of the specified class.
            // Otherwise, we're searching the entirety of GUObjectArray, and we need to check that the class matches.
            if (Class && !bQuickSearch && !Object->IsA(Class)) { return LoopAction::Continue; }

            bool bIsInOuter{};
            if (!bAnyPackage && !ObjectPackage)
            {
                if (Object->GetOutermost()->GetNamePrivate().Equals(PackageName))
                {
                    bIsInOuter = true;
                }
            }
            else if (!bAnyPackage)
            {
                UObject* Outer = Object->GetOuterPrivate();
                do
                {
                    if (Outer == ObjectPackage)
                    {
                        bIsInOuter = true;
                        break;
                    }
                    Outer = Outer->GetOuterPrivate();
                } while (Outer);
            }

            if (!bAnyPackage && !bIsInOuter) { return LoopAction::Continue; }

            if (bIsLongName)
            {
                if (!Object->GetNamePrivate().Equals(ShortName))
                {
                    return LoopAction::Continue;
                }
#ifdef __linux__
                // Linux limited mode: If FName::ToString is not available (stripped binary),
                // fall back to FName-based path comparison instead of GetFullName()+string comparison.
                // This prevents GetAllActorsOfClass and similar lookups from failing when
                // FName::ToString and Conv_NameToString are both unavailable.
                if (!FName::ToStringInternal.is_ready() && !FName::Conv_NameToStringInternal)
                {
                    // Parse InName path parts into FNames for comparison
                    // InName format: "/Script/Engine.Default__GameplayStatics" or "Package.Outer.Object"
                    StringType InNameStr = ToCharTypePtr(InName);
                    std::vector<FName> InNameParts;
                    // Split by '.' and ':'
                    size_t start = 0;
                    for (size_t i = 0; i < InNameStr.size(); ++i)
                    {
                        if (InNameStr[i] == STR('.') || InNameStr[i] == STR(':'))
                        {
                            if (i > start)
                            {
                                InNameParts.emplace_back(InNameStr.substr(start, i - start), FNAME_Find);
                            }
                            start = i + 1;
                        }
                    }
                    if (start < InNameStr.size())
                    {
                        InNameParts.emplace_back(InNameStr.substr(start), FNAME_Find);
                    }

                    // Compare with object's outer chain (from outermost to innermost)
                    // Build the object's path parts by walking the outer chain
                    std::vector<FName> ObjectPathParts;
                    auto PathObj = Object;
                    while (PathObj)
                    {
                        ObjectPathParts.push_back(PathObj->GetNamePrivate());
                        PathObj = PathObj->GetOuterPrivate();
                    }
                    // Reverse to get outermost-first order (matching InName)
                    std::reverse(ObjectPathParts.begin(), ObjectPathParts.end());

                    // Compare: InNameParts should match the suffix of ObjectPathParts
                    if (InNameParts.size() > ObjectPathParts.size())
                    {
                        return LoopAction::Continue;
                    }
                    bool bMatch = true;
                    for (size_t i = 0; i < InNameParts.size(); ++i)
                    {
                        // Compare from the end (innermost parts first)
                        size_t inIdx = InNameParts.size() - 1 - i;
                        size_t objIdx = ObjectPathParts.size() - 1 - i;
                        if (!InNameParts[inIdx].Equals(ObjectPathParts[objIdx]))
                        {
                            bMatch = false;
                            break;
                        }
                    }
                    if (bMatch)
                    {
                        FoundObject = Object;
                        return LoopAction::Break;
                    }
                }
                else
                {
                    auto FullName = Object->GetFullName();
                    auto ClassLessFullName = FullName.substr(FullName.find(STR(" ")) + 1);
                    if (ToCharTypePtr(InName) == ClassLessFullName)
                    {
                        FoundObject = Object;
                        return LoopAction::Break;
                    }
                }
#else
                auto FullName = Object->GetFullName();
                auto ClassLessFullName = FullName.substr(FullName.find(STR(" ")) + 1);
                if (ToCharTypePtr(InName) == ClassLessFullName)
                {
                    FoundObject = Object;
                    return LoopAction::Break;
                }
#endif
            }
            else if (ObjectPackage || bAnyPackage)
            {
                if (ShortName.Equals(Object->GetNamePrivate()))
                {
                    FoundObject = Object;
                    return LoopAction::Break;
                }
            }

            return LoopAction::Continue;
        });

        if (FoundObject && !bObjectIsCached)
        {
            CacheGlobalObject(FoundObject);
        }

        return FoundObject;
    }

    UObject* FindObject(struct ObjectSearcher& Searcher, UClass* Class, UObject* InOuter, File::StringViewType InName, bool bExactClass)
    {
        return FindObject(Searcher, Class, InOuter, FromCharTypePtr<TCHAR>(InName.data()), bExactClass);
    }

    UObject* FindObject(struct ObjectSearcher& Searcher, UClass* Class, UObject* InOuter, const TCHAR* InName, bool bExactClass)
    {
        return FindObject(Class, InOuter, InName, bExactClass, &Searcher);
    }

    auto FindFirstOf(FName ClassName) -> UObject*
    {
        UObject* ObjectFound{nullptr};

        UObjectGlobals::ForEachUObject([&](UObject* Object, [[maybe_unused]]int32_t ChunkIndex, [[maybe_unused]]int32_t ObjectIndex) {
            UClass* Class = Object->GetClassPrivate();

            if (Class->GetNamePrivate().Equals(ClassName) && IsValidObjectForFindXOf(Object))
            {
                ObjectFound = Object;
                return LoopAction::Break;

            }

            if (!IsValidObjectForFindXOf(Object)) { return LoopAction::Continue; }

            for (UStruct* super_struct : TSuperStructRange(Class))
            {
                if (super_struct->GetNamePrivate().Equals(ClassName))
                {
                    ObjectFound = Object;
                    break;
                }
            }

            return LoopAction::Continue;
        });

        return ObjectFound;
    }

    auto FindFirstOf(const CharType* ClassName) -> UObject*
    {
        return FindFirstOf(FName(ClassName));
    }

    auto FindFirstOf(StringViewType ClassName) -> UObject*
    {
        return FindFirstOf(FName(ClassName));
    }

    auto FindFirstOf(const StringType& ClassName) -> UObject*
    {
        return FindFirstOf(FName(ClassName));
    }

    auto FindFirstOf(std::string_view ClassName) -> UObject*
    {
        return FindFirstOf(FName(ensure_str(ClassName)));
    }

    auto FindFirstOf(const std::string& ClassName) -> UObject*
    {
        return FindFirstOf(FName(ensure_str(ClassName)));
    }

    auto FindAllOf(FName ClassName, std::vector<UObject*>& OutStorage) -> void
    {
        UObjectGlobals::ForEachUObject([&](UObject* Object, [[maybe_unused]]int32_t ChunkIndex, [[maybe_unused]]int32_t ObjectIndex) {
            if (!Object) { return LoopAction::Continue; }

            UClass* Class = Object->GetClassPrivate();
            if (!Class) { return LoopAction::Continue; }

            if (Class->GetNamePrivate().Equals(ClassName) && IsValidObjectForFindXOf(Object))
            {
                OutStorage.emplace_back(Object);
                return LoopAction::Continue;
            }

            if (!IsValidObjectForFindXOf(Object)) { return LoopAction::Continue; }

            for (UStruct* SuperStruct : TSuperStructRange(Class))
            {
                if (SuperStruct->GetNamePrivate().Equals(ClassName))
                {
                    OutStorage.emplace_back(Object);
                    break;
                }
            }

            return LoopAction::Continue;
        });
    }

    auto FindAllOf(const CharType* ClassName, std::vector<UObject*>& OutStorage) -> void
    {
        FindAllOf(FName(ClassName), OutStorage);
    }

    auto FindAllOf(StringViewType ClassName, std::vector<UObject*>& OutStorage) -> void
    {
        FindAllOf(FName(ClassName), OutStorage);
    }

    auto FindAllOf(const StringType& ClassName, std::vector<UObject*>& OutStorage) -> void
    {
        FindAllOf(FName(ClassName), OutStorage);
    }

    auto FindAllOf(std::string_view ClassName, std::vector<UObject*>& OutStorage) -> void
    {
        FindAllOf(FName(ensure_str(ClassName)), OutStorage);
    }

    auto FindAllOf(const std::string& ClassName, std::vector<UObject*>& OutStorage) -> void
    {
        FindAllOf(FName(ensure_str(ClassName)), OutStorage);
    }

    auto FindObjects(size_t NumObjectsToFind, const FName ClassName, const FName ObjectShortName, std::vector<UObject*>& OutStorage, int32 RequiredFlags, int32 BannedFlags, bool bExactClass) -> void
    {
        bool bCareAboutClass = ClassName != FName(0u, 0u);
        bool bCareAboutName = ObjectShortName != FName(0u, 0u);

        if (!bCareAboutClass && !bCareAboutName)
        {
            throw std::runtime_error{"[UObjectGlobals::find_objects] Must supply class_name, object_short_name, or both"};
        }

        size_t NumObjectsFound{};

        ForEachUObject([&](UObject* Object, int32, int32) {
            bool bNameMatches{};
            // Intentionally not using the 'Equals' function here because names can have an instance number that we care about.
            if (bCareAboutName && Object->GetNamePrivate() == ObjectShortName)
            {
                bNameMatches = true;
            }

            bool bClassMatches{};
            if (bCareAboutClass)
            {
                auto* ObjClass = Object->GetClassPrivate();
                if (bExactClass)
                {
                    if (ObjClass->GetNamePrivate().Equals(ClassName))
                    {
                        bClassMatches = true;
                    }
                }
                else
                {
                    while (ObjClass)
                    {
                        if (ObjClass->GetNamePrivate().Equals(ClassName))
                        {
                            bClassMatches = true;
                            break;
                        }

                        ObjClass = ObjClass->GetSuperClass();
                    }
                }
            }

            if ((bCareAboutClass && bClassMatches && bCareAboutName && bNameMatches) ||
                (!bCareAboutName && bCareAboutClass && bClassMatches) ||
                (!bCareAboutClass && bCareAboutName && bNameMatches))
            {
                bool bRequiredFlagsPasses = RequiredFlags == EObjectFlags::RF_NoFlags || Object->HasAllFlags(static_cast<EObjectFlags>(RequiredFlags));
                bool bBannedFlagsPasses = BannedFlags == EObjectFlags::RF_NoFlags || !Object->HasAnyFlags(static_cast<EObjectFlags>(BannedFlags));

                if (bRequiredFlagsPasses && bBannedFlagsPasses)
                {
                    OutStorage.emplace_back(Object);
                    ++NumObjectsFound;
                }
            }

            if (NumObjectsToFind != 0 && NumObjectsFound >= NumObjectsToFind)
            {
                return LoopAction::Break;
            }
            else
            {
                return LoopAction::Continue;
            }
        });
    }

    auto FindObjects(size_t NumObjectsToFind, const CharType* ClassName, const CharType* ObjectShortName, std::vector<UObject*>& OutStorage, int32 RequiredFlags, int32 BannedFlags, bool bExactClass) -> void
    {
        FindObjects(NumObjectsToFind, FName(ClassName), FName(ObjectShortName), OutStorage, RequiredFlags, BannedFlags, bExactClass);
    }

    auto FindObject(const FName ClassName, const FName ObjectShortName, int32 RequiredFlags, int32 BannedFlags) -> UObject*
    {
        std::vector<UObject*> FoundObject{};
        FindObjects(1, ClassName, ObjectShortName, FoundObject, RequiredFlags, BannedFlags);

        if (FoundObject.empty())
        {
            return nullptr;
        }
        else
        {
            return FoundObject[0];
        }
    };

    auto FindObjects(const FName ClassName, const FName ObjectShortName, std::vector<UObject*>& OutStorage, int32 RequiredFlags, int32 BannedFlags, bool bExactClass) -> void
    {
        FindObjects(0, ClassName, ObjectShortName, OutStorage, RequiredFlags, BannedFlags, bExactClass);
    }

    auto FindObjects(const CharType* ClassName, const CharType* ObjectShortName, std::vector<UObject*>& OutStorage, int32 RequiredFlags, int32 BannedFlags, bool bExactClass) -> void
    {
        FindObjects(0, ClassName, ObjectShortName, OutStorage, RequiredFlags, BannedFlags, bExactClass);
    }

    auto FindObject(const CharType* ClassName, const CharType* ObjectShortName, int32 RequiredFlags, int32 BannedFlags) -> UObject*
    {
        return FindObject(FName(ClassName), FName(ObjectShortName), RequiredFlags, BannedFlags);
    }

    using ForEachUObjectCallback = std::function<LoopAction(UObject*, int32, int32)>;

    static auto ForEachUObject_NonChunked(const ForEachUObjectCallback& Callable) -> void
    {
        GUOBJECTARRAY_PROFILE_ITER_BEGIN()
        if (!GUObjectArray)
        {
            return;
        }

        LoopAction Action{};

        const auto& ObjObjects = GUObjectArray->GetObjObjects();
        static const auto ItemSize = FUObjectItem::UEP_TotalSize();

        for (int32_t ItemIndex = 0; ItemIndex < ObjObjects.GetNumElements(); ++ItemIndex)
        {
            const auto& ChunkPtr = ObjObjects.GetObjects();
            const auto ObjectItem = std::bit_cast<FUObjectItem*>(&std::bit_cast<uint8_t*>(ChunkPtr)[ItemIndex * ItemSize]);
            const auto Object = ObjectItem->GetUObject();
            if (ObjectItem->IsUnreachable() || !Object) { continue; }
            GUOBJECTARRAY_PROFILE_ITER_COUNT()
            Action = Callable(Object, 0, ItemIndex);
            if (Action == LoopAction::Break) { break; }
        }
        GUOBJECTARRAY_PROFILE_ITER_END()
    }

    static auto ForEachUObject_Chunked(const ForEachUObjectCallback& Callable) -> void
    {
        GUOBJECTARRAY_PROFILE_ITER_BEGIN()
        if (!GUObjectArray)
        {
            return;
        }

        LoopAction Action{};

        const auto& ObjObjects = GUObjectArray->GetObjObjects();
        const auto NumChunks = ObjObjects.GetNumChunks();
        static const auto ItemSize = FUObjectItem::UEP_TotalSize();

        for (int32_t ChunkIndex = 0; ChunkIndex < NumChunks; ++ChunkIndex)
        {
            for (int32_t ItemIndex = 0; ItemIndex < TUObjectArray::NumElementsPerChunk; ++ItemIndex)
            {
                const auto& ChunksPtr = ObjObjects.GetObjects();
                const auto ObjectItem = std::bit_cast<FUObjectItem*>(&std::bit_cast<uint8_t*>(ChunksPtr[ChunkIndex])[ItemIndex * ItemSize]);
                const auto Object = ObjectItem->GetUObject();
                if (ObjectItem->IsUnreachable() || !Object) { continue; }
                GUOBJECTARRAY_PROFILE_ITER_COUNT()
                Action = Callable(Object, ChunkIndex, ItemIndex);
                if (Action == LoopAction::Break) { break; }
            }
            if (Action == LoopAction::Break) { break; }
        }
        GUOBJECTARRAY_PROFILE_ITER_END()
    }

    static auto ForEachUObject_NonChunkedInRange(int32_t Start, int32_t End, const ForEachUObjectCallback& Callable) -> void
    {
        if (!GUObjectArray)
        {
            return;
        }

        LoopAction Action{};

        const auto& ObjObjects = GUObjectArray->GetObjObjects();
        const auto NumElements = ObjObjects.GetNumElements();
        static const auto ItemSize = FUObjectItem::UEP_TotalSize();

        const int32_t StartItemIndex = Start;
        const int32_t EndItemIndex = End < NumElements ? End : NumElements;

        for (int32_t ItemIndex = StartItemIndex; ItemIndex < EndItemIndex; ++ItemIndex)
        {
            const auto& ChunkPtr = ObjObjects.GetObjects();
            const auto ObjectItem = std::bit_cast<FUObjectItem*>(&std::bit_cast<uint8_t*>(ChunkPtr)[ItemIndex * ItemSize]);
            const auto Object = ObjectItem->GetUObject();
            if (ObjectItem->IsUnreachable() || !Object) { continue; }
            Action = Callable(Object, 0, ItemIndex);
            if (Action == LoopAction::Break) { break; }
        }
    }

    static auto ForEachUObject_ChunkedInRange(int32_t Start, int32_t End, const ForEachUObjectCallback& Callable) -> void
    {
        if (!GUObjectArray)
        {
            return;
        }

        LoopAction Action{};

        const auto& ObjObjects = GUObjectArray->GetObjObjects();
        const auto NumElements = ObjObjects.GetNumElements();
        const auto NumChunks = ObjObjects.GetNumChunks();
        static const auto ItemSize = FUObjectItem::UEP_TotalSize();

        const int32_t EndClamped = End < NumElements ? End : NumElements;
        const int32_t StartChunk = Start / TUObjectArray::NumElementsPerChunk;
        const int32_t StartItemIndex = Start % TUObjectArray::NumElementsPerChunk;

        int32_t CurrentTotalItem = Start;
        for (int32_t ChunkIndex = StartChunk; ChunkIndex < NumChunks; ++ChunkIndex)
        {
            bool ShouldBreak{};
            for (int32_t ItemIndex = StartItemIndex; ItemIndex < TUObjectArray::NumElementsPerChunk; ++ItemIndex)
            {
                const auto& ChunksPtr = ObjObjects.GetObjects();
                const auto ObjectItem = std::bit_cast<FUObjectItem*>(&std::bit_cast<uint8_t*>(ChunksPtr[ChunkIndex])[ItemIndex * ItemSize]);
                const auto Object = ObjectItem->GetUObject();
                if (ObjectItem->IsUnreachable() || !Object) { continue; }
                Action = Callable(Object, ChunkIndex, ItemIndex);
                if (Action == LoopAction::Break || CurrentTotalItem >= EndClamped)
                {
                    ShouldBreak = true;
                    break;
                }
            }
            ++CurrentTotalItem;
            if (ShouldBreak) { break; }
        }
    }

    auto ForEachUObject(const ForEachUObjectCallback& Callable) -> void
    {
        // TODO: Expose whether FUObjectArray is chunked in ini.
        //       This is just in case there's a game with custom changes where they pulled the chunked array into a non-chunked UE version.
        if (Version::IsAtMost(4, 19))
        {
            ForEachUObject_NonChunked(Callable);
        }
        else
        {
            ForEachUObject_Chunked(Callable);
        }
    }

    auto ForEachUObjectInChunk(int32_t ChunkIndex, const std::function<LoopAction(UObject*, int32)>& Callable) -> void
    {
        if (Version::IsAtMost(4, 19))
        {
            ForEachUObject_NonChunked([&](UObject* Object, int32_t, int32_t ObjectIndex) {
                return Callable(Object, ObjectIndex);
            });
        }
        else
        {
            if (!GUObjectArray || ChunkIndex >= GUObjectArray->GetObjObjects().GetNumChunks())
            {
                return;
            }

            LoopAction Action{};

            const auto& ObjObjects = GUObjectArray->GetObjObjects();
            static const auto ItemSize = FUObjectItem::UEP_TotalSize();

            for (int32_t ItemIndex = 0; ItemIndex < TUObjectArray::NumElementsPerChunk; ++ItemIndex)
            {
                const auto& ChunksPtr = ObjObjects.GetObjects();
                const auto ObjectItem = std::bit_cast<FUObjectItem*>(&std::bit_cast<uint8_t*>(ChunksPtr[ChunkIndex])[ItemIndex * ItemSize]);
                const auto Object = ObjectItem->GetUObject();
                if (ObjectItem->IsUnreachable() || !Object) { continue; }
                Action = Callable(Object, ItemIndex);
                if (Action == LoopAction::Break) { break; }
            }
        }
    }

    auto ForEachUObjectInRange(int32_t Start, int32_t End, const std::function<LoopAction(UObject*, int32, int32)>& Callable) -> void
    {
        if (Version::IsAtMost(4, 19))
        {
            ForEachUObject_NonChunkedInRange(Start, End, Callable);
        }
        else
        {
            ForEachUObject_ChunkedInRange(Start, End, Callable);
        }
    }

    struct GlobalHooksInternal
    {
        struct CallableData
        {
            struct InternalData
            {
                UnrealScriptFunctionCallable CallablePre{};
                UnrealScriptFunctionCallable CallablePost{};
                void* CustomData{};
                int32_t PreId{};
                int32_t PostId{};

                InternalData() = default;
                InternalData(UnrealScriptFunctionCallable PreCallable, UnrealScriptFunctionCallable PostCallable, void* CustomData, int32_t PreId, int32_t PostId) :
                      CallablePre(PreCallable),
                      CallablePost(PostCallable),
                      CustomData(CustomData),
                      PreId(PreId),
                      PostId(PostId) {}
            };
            std::vector<InternalData> Callables{};
        };
        static inline std::unordered_map<StringType, CallableData> GlobalScriptHooks{};
        static inline bool bIsHookEnabled{};
        static inline int32_t LastGenericHookId{};
        static inline std::unordered_map<int32_t, int32_t> GenericHookIdToNativeHookId{};
    };

    static auto GlobalScriptHookPre([[maybe_unused]]Hook::TCallbackIterationData<void>& CallbackIterationData, [[maybe_unused]]Unreal::UObject* Context, Unreal::FFrame& Stack, [[maybe_unused]]void* RESULT_DECL) -> void
    {
        if (GlobalHooksInternal::GlobalScriptHooks.empty()) { return; }
        if (auto it = GlobalHooksInternal::GlobalScriptHooks.find(Stack.Node()->GetFullName()); it != GlobalHooksInternal::GlobalScriptHooks.end())
        {
            UnrealScriptFunctionCallableContext CallableContext{Context, Stack, RESULT_DECL};
            for (const auto& Callable : it->second.Callables)
            {
                Callable.CallablePre(CallableContext, Callable.CustomData);
            }
        }
    }

    static auto GlobalScriptHookPost([[maybe_unused]]Hook::TCallbackIterationData<void>& CallbackIterationData, [[maybe_unused]]Unreal::UObject* Context, Unreal::FFrame& Stack, [[maybe_unused]]void* RESULT_DECL) -> void
    {
        if (GlobalHooksInternal::GlobalScriptHooks.empty()) { return; }
        if (auto it = GlobalHooksInternal::GlobalScriptHooks.find(Stack.Node()->GetFullName()); it != GlobalHooksInternal::GlobalScriptHooks.end())
        {
            UnrealScriptFunctionCallableContext CallableContext{Context, Stack, RESULT_DECL};
            for (const auto& Callable : it->second.Callables)
            {
                Callable.CallablePost(CallableContext, Callable.CustomData);
            }
        }
    }

    auto RegisterHook(UFunction* Function, UnrealScriptFunctionCallable PreCallback, UnrealScriptFunctionCallable PostCallback, void* CustomData) -> std::pair<int, int>
    {
        auto NativeFunction = Function->GetFunc();
        if (NativeFunction &&
            NativeFunction != UObject::ProcessInternalInternal.get_function_address() &&
            Function->HasAnyFunctionFlags(EFunctionFlags::FUNC_Native))
        {
            auto PreId = Function->RegisterPreHook(PreCallback, CustomData);
            auto PostId = Function->RegisterPostHook(PostCallback, CustomData);
            GlobalHooksInternal::GenericHookIdToNativeHookId.emplace(++GlobalHooksInternal::LastGenericHookId, PreId);
            auto GenericPreId = GlobalHooksInternal::LastGenericHookId;
            GlobalHooksInternal::GenericHookIdToNativeHookId.emplace(++GlobalHooksInternal::LastGenericHookId, PostId);
            auto GenericPostId = GlobalHooksInternal::LastGenericHookId;
            return {GenericPreId, GenericPostId};
        }
        else if (NativeFunction &&
                 NativeFunction == UObject::ProcessInternalInternal.get_function_address() &&
                 !Function->HasAnyFunctionFlags(EFunctionFlags::FUNC_Native))
        {
            if (!GlobalHooksInternal::bIsHookEnabled)
            {
                const Hook::FCallbackOptions GlobalScriptHookOptions {false, false, STR("UE4SS"), STR("GlobalScriptHook")};
                if (UObject::ProcessLocalScriptFunctionInternal.is_ready() && Version::IsAtLeast(4, 22))
                {
                    Hook::RegisterProcessLocalScriptFunctionPreCallback(GlobalScriptHookPre, GlobalScriptHookOptions);
                    Hook::RegisterProcessLocalScriptFunctionPostCallback(GlobalScriptHookPost, GlobalScriptHookOptions);
                }
                else if (UObject::ProcessInternalInternal.is_ready() && Version::IsBelow(4, 22))
                {
                    Hook::RegisterProcessInternalPreCallback(GlobalScriptHookPre, GlobalScriptHookOptions);
                    Hook::RegisterProcessInternalPostCallback(GlobalScriptHookPost, GlobalScriptHookOptions);
                }
                GlobalHooksInternal::bIsHookEnabled = true;
            }
            ++GlobalHooksInternal::LastGenericHookId;
            auto GenericPreId = GlobalHooksInternal::LastGenericHookId;
            auto GenericPostId = GlobalHooksInternal::LastGenericHookId;
            auto [Data, _] = GlobalHooksInternal::GlobalScriptHooks.emplace(Function->GetFullName(), GlobalHooksInternal::CallableData{});
            Data->second.Callables.emplace_back(PreCallback, PostCallback, CustomData, GenericPreId, GenericPostId);
            return {GenericPreId, GenericPostId};
        }
        else
        {
            std::string error_message{"Was unable to register a UFunction hook, information:\n"};
            error_message.append(fmt::format("UFunction::Func: {}\n", std::bit_cast<void*>(NativeFunction)));
            error_message.append(fmt::format("ProcessInternal: {}\n", UObject::ProcessInternalInternal.get_function_address()));
            error_message.append(fmt::format("FUNC_Native: {}\n", static_cast<uint32_t>(Function->HasAnyFunctionFlags(EFunctionFlags::FUNC_Native))));
            throw std::runtime_error{error_message};
        }
    }

    auto RegisterHook(const StringType& FunctionFullNameNoType, UnrealScriptFunctionCallable PreCallback, UnrealScriptFunctionCallable PostCallback, void* CustomData) -> std::pair<int, int>
    {
        auto Function = StaticFindObject<UFunction*>(nullptr, nullptr, FunctionFullNameNoType);
        return RegisterHook(Function, PreCallback, PostCallback, CustomData);
    }

    auto UnregisterHook(class UFunction* Function, std::pair<int, int> Ids) -> void
    {
        Output::send(STR("Unregistering hook\n"));
        auto NativeFunction = Function->GetFunc();
        if (NativeFunction &&
            NativeFunction != UObject::ProcessInternalInternal.get_function_address() &&
            Function->HasAnyFunctionFlags(EFunctionFlags::FUNC_Native))
        {
            Output::send(STR("Unregistering native hook ({}, {})\n"), Ids.first, Ids.second);
            if (auto PreNativeId = GlobalHooksInternal::GenericHookIdToNativeHookId.find(Ids.first); PreNativeId != GlobalHooksInternal::GenericHookIdToNativeHookId.end())
            {
                Function->UnregisterHook(PreNativeId->second);
                Output::send(STR("Native hook unregistered\n"));
            }
            if (auto PostNativeId = GlobalHooksInternal::GenericHookIdToNativeHookId.find(Ids.second); PostNativeId != GlobalHooksInternal::GenericHookIdToNativeHookId.end())
            {
                Function->UnregisterHook(PostNativeId->second);
            }
        }
        else if (NativeFunction &&
                 NativeFunction == UObject::ProcessInternalInternal.get_function_address() &&
                 !Function->HasAnyFunctionFlags(EFunctionFlags::FUNC_Native))
        {
            if (auto CallbackDataIt = GlobalHooksInternal::GlobalScriptHooks.find(Function->GetFullName()); CallbackDataIt != GlobalHooksInternal::GlobalScriptHooks.end())
            {
                for (const auto& CallbackData : CallbackDataIt->second.Callables)
                {
                }
                auto& Callbacks = CallbackDataIt->second.Callables;
                Callbacks.erase(std::remove_if(Callbacks.begin(), Callbacks.end(), [&](GlobalHooksInternal::CallableData::InternalData& CallbackData) -> bool {
                    return Ids.first == CallbackData.PreId && Ids.second == CallbackData.PostId;
                }), Callbacks.end());
            }
        }
        else
        {
            std::string error_message{"Was unable to unregister a UFunction hook, information:\n"};
            error_message.append(fmt::format("UFunction::Func: {}\n", std::bit_cast<void*>(NativeFunction)));
            error_message.append(fmt::format("ProcessInternal: {}\n", UObject::ProcessInternalInternal.get_function_address()));
            error_message.append(fmt::format("FUNC_Native: {}\n", static_cast<uint32_t>(Function->HasAnyFunctionFlags(EFunctionFlags::FUNC_Native))));
            throw std::runtime_error{error_message};
        }
    }

    auto UnregisterHook(const StringType& FunctionFullNameNoType, std::pair<int, int> Ids) -> void
    {
        auto Function = StaticFindObject<UFunction*>(nullptr, nullptr, FunctionFullNameNoType);
        if (!Function) { throw std::runtime_error{fmt::format("Unable to find function: {}", to_string(FunctionFullNameNoType))}; }
        UnregisterHook(Function, Ids);
    }
}

