#include <Unreal/FSoftObjectPath.hpp>
#include <Unreal/PackageName.hpp>
#include <Unreal/FText.hpp>
#include <Unreal/UAssetRegistryHelpers.hpp>
#include <Unreal/UAssetRegistry.hpp>
#include <Unreal/UnrealInitializer.hpp>
namespace RC::Unreal
{
        FSoftObjectPath::FSoftObjectPath(const UObject* InObject)
        {
            if (InObject)
            {
                SetPath(FString(InObject->GetPathName().c_str()));
            }
        }

        FString FSoftObjectPath::ToString() const
        {
            if (SubPathString.IsEmpty())
            {
                return GetAssetPathString();
            }
            auto AssetPathString = AssetPathName.ToFString();
            FString FullPathString;
            FullPathString.Reserve(AssetPathString.Len() + SubPathString.Len() + 1);
            FullPathString += AssetPathString;
            FullPathString += ':';
            FullPathString += SubPathString;
            return FullPathString;
        }

        void FSoftObjectPath::SetPath(const FString& Path)
        {
            if (Path.IsEmpty() || Path == STR("None"))
            {
                Reset();
            }else if (ensureMsgf(!FPackageName::IsShortPackageName(*Path), TEXT("Cannot create SoftObjectPath with short package names"), Path.Len(), *Path))
            {
                // RE-UE4SS FIX (Corporalwill): [ExportTextPathToObjectPath unimplemented, would require non-array FString:Split() to be implemented]
                /*if (Path[0] != '/')
                {
                    Path = FPackageName::ExportTextPathToObjectPath(Path);
                }*/
                // RE-UE4SS FIX END

                int32 ColonIndex;
                if (Path.FindChar(':', ColonIndex))
                {
                    AssetPathName = FName(*Path.Left(ColonIndex));
                    SubPathString = Path.Mid(ColonIndex + 1);
                }
                else
                {
                    AssetPathName = FName(*Path);
                    SubPathString.Empty();
                }
            }
        }

        UObject* FSoftObjectPath::ResolveObject() const
        {
            if (IsNull())
            {
                return nullptr;
            }
            return ResolveObjectInternal();
        }

        UObject* FSoftObjectPath::ResolveObjectInternal() const
        {
            if (SubPathString.IsEmpty())
            {
                return ResolveObjectInternal(AssetPathName.ToString().c_str());
            }
            else
            {
                return  ResolveObjectInternal(*ToString());
            }
        }

        UObject* FSoftObjectPath::ResolveObjectInternal(const TCHAR* PathString) const
        {
            return UObjectGlobals::FindObject<Unreal::UObject>(nullptr, PathString);
        }

        int32 FSoftObjectPath::GetCurrentTag()
        {
            //TODO: Find way to access tag value
            return 0;
        }

        UObject* FSoftObjectPath::TryLoad(/*FUObjectSerializeContext* InLoadContext = nullptr*/) const
        {

            // RE-UE4SS FIX (Corporalwill): [StaticLoadObject not implemented, reusing code from UE4SS lua function LoadAsset]
            //                              Perhaps we should eventually implement StaticLoadObject and just wrap this code ?
            if (!Unreal::IsInGameThread())
            {
                throw std::runtime_error{"FSoftObjectPath::TryLoad can only be called from within the game thread"};
            }

            auto asset_path_and_name = FName(*this->ToString(), EFindName::FNAME_Add);

            auto* asset_registry = static_cast<UAssetRegistry*>(UAssetRegistryHelpers::GetAssetRegistry().ObjectPointer);
            if (!asset_registry)
            {
                throw std::runtime_error{"FSoftObjectPath::TryLoad did not load assets because asset_registry was nullptr\n"};
            }

            Unreal::UObject* loaded_asset{};
            //bool was_asset_found{};
            //bool did_asset_load{};

            Unreal::FAssetData asset_data = asset_registry->GetAssetByObjectPath(asset_path_and_name);
            if ((Unreal::Version::IsAtMost(5, 0) && asset_data.ObjectPath().GetComparisonIndex()) || asset_data.PackageName().GetComparisonIndex())
            {
                loaded_asset = Unreal::UAssetRegistryHelpers::GetAsset(asset_data);
                /*if (loaded_asset)
                {
                    did_asset_load = true;
                    Output::send(STR("Asset loaded\n"));
                }
                else
                {
                    Output::send(STR("Asset was found but not loaded, could be a package\n"));
                }*/
            }
            // RE-UE4SS FIX END

            return loaded_asset;
        }

        FSoftObjectPath FSoftObjectPath::GetOrCreateIDForObject(const UObject* Object)
        {
            return FSoftObjectPath(Object);
        }
}