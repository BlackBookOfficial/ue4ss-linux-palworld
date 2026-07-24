#include <stdexcept>

#include <Unreal/FAssetData.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
namespace RC::Unreal
{
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(FAssetData)

    int32 FAssetData::StaticSize_Private{-1};

    static auto EnsureFAssetDataAvailability() -> void
    {
        if (Version::IsBelow(4, 17)) { throw std::runtime_error{"FAssetData only available in 4.17+"}; }
        if (!bFAssetDataAvailable) { throw std::runtime_error{"FAssetData not available."}; }
    }

    FAssetData::FAssetData() = default;

    FAssetData::FAssetData(const FAssetData& Other)
    {
        EnsureFAssetDataAvailability();
        
        if (Version::IsAtLeast(5, 1))
        {
            auto* TypedThis = std::bit_cast<FAssetData51Plus*>(this);
            auto* TypedOther = std::bit_cast<FAssetData51Plus*>(&Other);

            TypedThis->PackageName = TypedOther->PackageName;
            TypedThis->PackagePath = TypedOther->PackagePath;
            TypedThis->AssetName = TypedOther->AssetName;
            TypedThis->AssetClass = TypedOther->AssetClass;
            TypedThis->AssetClassPath = TypedOther->AssetClassPath;
            TypedThis->TagsAndValues = TypedOther->TagsAndValues;
            TypedThis->TaggedAssetBundles = TypedOther->TaggedAssetBundles;
            TypedThis->ChunkIDs = TypedOther->ChunkIDs;
            TypedThis->PackageFlags = TypedOther->PackageFlags;
        }
        else if (Version::IsAtLeast(4, 27))
        {
            auto* TypedThis = std::bit_cast<FAssetData427Plus*>(this);
            auto* TypedOther = std::bit_cast<FAssetData427Plus*>(&Other);

            TypedThis->ObjectPath = TypedOther->ObjectPath;
            TypedThis->PackageName = TypedOther->PackageName;
            TypedThis->PackagePath = TypedOther->PackagePath;
            TypedThis->AssetName = TypedOther->AssetName;
            TypedThis->AssetClass = TypedOther->AssetClass;
            TypedThis->TagsAndValues = TypedOther->TagsAndValues;
            TypedThis->TaggedAssetBundles = TypedOther->TaggedAssetBundles;
            TypedThis->ChunkIDs = TypedOther->ChunkIDs;
            TypedThis->PackageFlags = TypedOther->PackageFlags;
        }
        else
        {
            auto* TypedThis = std::bit_cast<FAssetDataPre427*>(this);
            auto* TypedOther = std::bit_cast<FAssetDataPre427*>(&Other);

            TypedThis->ObjectPath = TypedOther->ObjectPath;
            TypedThis->PackageName = TypedOther->PackageName;
            TypedThis->PackagePath = TypedOther->PackagePath;
            TypedThis->AssetName = TypedOther->AssetName;
            TypedThis->AssetClass = TypedOther->AssetClass;
            TypedThis->TagsAndValues = TypedOther->TagsAndValues;
            //TypedThis->TaggedAssetBundles = TypedOther->TaggedAssetBundles;
            TypedThis->ChunkIDs = TypedOther->ChunkIDs;
            TypedThis->PackageFlags = TypedOther->PackageFlags;
        }
    }

    FName FAssetData::ObjectPath()
    {
        EnsureFAssetDataAvailability();
        if (Version::IsAtLeast(5, 1))
        {
            Output::send<LogLevel::Warning>(STR("FAssetData::ObjectPath used but is only available in <=5.0\n"));
            return NAME_None;
        }

        if (Version::IsAtLeast(4, 27))
        {
            return std::bit_cast<FAssetData427Plus*>(this)->ObjectPath;
        }
        else
        {
            return std::bit_cast<FAssetDataPre427*>(this)->ObjectPath;
        }
    }

    FName FAssetData::PackageName()
    {
        EnsureFAssetDataAvailability();

        if (Version::IsAtLeast(5, 1))
        {
            return std::bit_cast<FAssetData51Plus*>(this)->PackageName;
        }
        else if (Version::IsAtLeast(4, 27))
        {
            return std::bit_cast<FAssetData427Plus*>(this)->PackageName;
        }
        else
        {
            return std::bit_cast<FAssetDataPre427*>(this)->PackageName;
        }
    }

    FName FAssetData::PackagePath()
    {
        EnsureFAssetDataAvailability();

        if (Version::IsAtLeast(5, 1))
        {
            return std::bit_cast<FAssetData51Plus*>(this)->PackagePath;
        }
        else if (Version::IsAtLeast(4, 27))
        {
            return std::bit_cast<FAssetData427Plus*>(this)->PackagePath;
        }
        else
        {
            return std::bit_cast<FAssetDataPre427*>(this)->PackagePath;
        }
    }

    FName FAssetData::AssetName()
    {
        EnsureFAssetDataAvailability();

        if (Version::IsAtLeast(5, 1))
        {
            return std::bit_cast<FAssetData51Plus*>(this)->AssetName;
        }
        else if (Version::IsAtLeast(4, 27))
        {
            return std::bit_cast<FAssetData427Plus*>(this)->AssetName;
        }
        else
        {
            return std::bit_cast<FAssetDataPre427*>(this)->AssetName;
        }
    }

    FName FAssetData::AssetClass()
    {
        EnsureFAssetDataAvailability();

        if (Version::IsAtLeast(5, 1))
        {
            return std::bit_cast<FAssetData51Plus*>(this)->AssetClass;
        }
        else if (Version::IsAtLeast(4, 27))
        {
            return std::bit_cast<FAssetData427Plus*>(this)->AssetClass;
        }
        else
        {
            return std::bit_cast<FAssetDataPre427*>(this)->AssetClass;
        }
    }

    FAssetDataTagMapSharedView FAssetData::TagsAndValues()
    {
        EnsureFAssetDataAvailability();

        if (Version::IsAtLeast(5, 1))
        {
            return std::bit_cast<FAssetData51Plus*>(this)->TagsAndValues;
        }
        else if (Version::IsAtLeast(4, 27))
        {
            return std::bit_cast<FAssetData427Plus*>(this)->TagsAndValues;
        }
        else
        {
            return std::bit_cast<FAssetDataPre427*>(this)->TagsAndValues;
        }
    }

    FAssetBundleData* FAssetData::TaggedAssetBundles()
    {
        EnsureFAssetDataAvailability();

        if (Version::IsAtLeast(5, 1))
        {
            return std::bit_cast<FAssetData51Plus*>(this)->TaggedAssetBundles;
        }
        else if (Version::IsAtLeast(4, 27))
        {
            return std::bit_cast<FAssetData427Plus*>(this)->TaggedAssetBundles;
        }
        else
        {
            throw std::runtime_error{"FAssetData::TaggedAssetBundles is not available in <4.27"};
        }
    }

    /*TArray<int32>*/void FAssetData::ChunkIDs()
    {
        // This isn't implemented because we need some sort of abstraction of the return value which we don't have
        // The reason we need this is because:
        // In <4.27, the return type was TArray<int32>, and in 4.27+ it's TArray<int32, TInlineAllocator<2>>
        throw std::runtime_error{"FAssetData:ChunkIDs is not implemented"};
    }

    TArray<int32>& FAssetData::OldChunkIDsUnsafe()
    {
        EnsureFAssetDataAvailability();

        if (Version::IsAtLeast(4, 27))
        {
            throw std::runtime_error{"FAssetData::OldChunkIDsUnsafe can only be used in pre-4.27"};
        }
        else
        {
            return std::bit_cast<FAssetDataPre427*>(this)->ChunkIDs;
        }
    }

    TArray<int32, TInlineAllocator<2>>& FAssetData::NewChunkIDsUnsafe()
    {
        EnsureFAssetDataAvailability();

        if (Version::IsAtLeast(5, 1))
        {
            return std::bit_cast<FAssetData51Plus*>(this)->ChunkIDs;
        }
        else if (Version::IsAtLeast(4, 27))
        {
            return std::bit_cast<FAssetData427Plus*>(this)->ChunkIDs;
        }
        else
        {
            throw std::runtime_error{"FAssetData::NewChunkIDsUnsafe can only be used in 4.27+"};
        }
    }

    uint32 FAssetData::PackageFlags()
    {
        EnsureFAssetDataAvailability();

        if (Version::IsAtLeast(5, 1))
        {
            return std::bit_cast<FAssetData51Plus*>(this)->PackageFlags;
        }
        else if (Version::IsAtLeast(4, 27))
        {
            return std::bit_cast<FAssetData427Plus*>(this)->PackageFlags;
        }
        else
        {
            return std::bit_cast<FAssetDataPre427*>(this)->PackageFlags;
        }
    }

    FTopLevelAssetPath& FAssetData::AssetClassPath()
    {
        if (Version::IsBelow(5, 1)) { throw std::runtime_error{"FAssetData::AssetClassPath is only available in 5.1+"}; }

        return std::bit_cast<FAssetData51Plus*>(this)->AssetClassPath;
    }

    void FAssetData::SetObjectPath(FName NewValue)
    {
        EnsureFAssetDataAvailability();
        if (Version::IsAtLeast(5, 1)) { throw std::runtime_error{"FAssetData::SetObjectPath only available in <=5.0\n"}; }
        
        if (Version::IsAtLeast(4, 27))
        {
            std::bit_cast<FAssetData427Plus*>(this)->ObjectPath = NewValue;
        }
        else
        {
            std::bit_cast<FAssetDataPre427*>(this)->ObjectPath = NewValue;
        }
    }

    void FAssetData::SetPackageName(FName NewValue)
    {
        EnsureFAssetDataAvailability();

        if (Version::IsAtLeast(5, 1))
        {
            std::bit_cast<FAssetData51Plus*>(this)->PackageName = NewValue;
        }
        else if (Version::IsAtLeast(4, 27))
        {
            std::bit_cast<FAssetData427Plus*>(this)->PackageName = NewValue;
        }
        else
        {
            std::bit_cast<FAssetDataPre427*>(this)->PackageName = NewValue;
        }
    }

    void FAssetData::SetPackagePath(FName NewValue)
    {
        EnsureFAssetDataAvailability();

        if (Version::IsAtLeast(5, 1))
        {
            std::bit_cast<FAssetData51Plus*>(this)->PackagePath = NewValue;
        }
        else if (Version::IsAtLeast(4, 27))
        {
            std::bit_cast<FAssetData427Plus*>(this)->PackagePath = NewValue;
        }
        else
        {
            std::bit_cast<FAssetDataPre427*>(this)->PackagePath = NewValue;
        }
    }

    void FAssetData::SetAssetName(FName NewValue)
    {
        EnsureFAssetDataAvailability();

        if (Version::IsAtLeast(5, 1))
        {
            std::bit_cast<FAssetData51Plus*>(this)->AssetName = NewValue;
        }
        else if (Version::IsAtLeast(4, 27))
        {
            std::bit_cast<FAssetData427Plus*>(this)->AssetName = NewValue;
        }
        else
        {
            std::bit_cast<FAssetDataPre427*>(this)->AssetName = NewValue;
        }

    }

    void FAssetData::SetAssetClass(FName NewValue)
    {
        EnsureFAssetDataAvailability();

        if (Version::IsAtLeast(5, 1))
        {
            std::bit_cast<FAssetData51Plus*>(this)->AssetClass = NewValue;
        }
        else if (Version::IsAtLeast(4, 27))
        {
            std::bit_cast<FAssetData427Plus*>(this)->AssetClass = NewValue;
        }
        else
        {
            std::bit_cast<FAssetDataPre427*>(this)->AssetClass = NewValue;
        }
    }

    void FAssetData::SetTagsAndValues(FAssetDataTagMapSharedView NewValue)
    {
        EnsureFAssetDataAvailability();

        if (Version::IsAtLeast(5, 1))
        {
            std::bit_cast<FAssetData51Plus*>(this)->TagsAndValues = NewValue;
        }
        else if (Version::IsAtLeast(4, 27))
        {
            std::bit_cast<FAssetData427Plus*>(this)->TagsAndValues = NewValue;
        }
        else
        {
            std::bit_cast<FAssetDataPre427*>(this)->TagsAndValues = NewValue;
        }
    }

    void FAssetData::SetTaggedAssetBundles(FAssetBundleData* NewValue)
    {
        EnsureFAssetDataAvailability();

        if (Version::IsAtLeast(5, 1))
        {
            std::bit_cast<FAssetData51Plus*>(this)->TaggedAssetBundles = NewValue;
        }
        else if (Version::IsAtLeast(4, 27))
        {
            std::bit_cast<FAssetData427Plus*>(this)->TaggedAssetBundles = NewValue;
        }
        else
        {
            throw std::runtime_error{"FAssetData::TaggedAssetBundles is not available in <4.27"};
        }
    }

    void FAssetData::SetChunkIDs(/*TArray<int32>*/)
    {
        // This isn't implemented because we need some sort of abstraction of the return value which we don't have
        // The reason we need this is because:
        // In <4.27, the return type was TArray<int32>, and in 4.27+ it's TArray<int32, TInlineAllocator<2>>
        throw std::runtime_error{"FAssetData:ChunkIDs is not implemented"};
    }

    void FAssetData::SetOldChunkIDsUnsafe(TArray<int32>& NewValue)
    {
        EnsureFAssetDataAvailability();

        if (Version::IsAtLeast(4, 27))
        {
            throw std::runtime_error{"FAssetData::OldChunkIDsUnsafe can only be used in pre-4.27"};
        }
        else
        {
            std::bit_cast<FAssetDataPre427*>(this)->ChunkIDs = NewValue;
        }
    }

    void FAssetData::SetNewChunkIDsUnsafe(TArray<int32, TInlineAllocator<2>>& NewValue)
    {
        EnsureFAssetDataAvailability();

        if (Version::IsAtLeast(5, 1))
        {
            std::bit_cast<FAssetData51Plus*>(this)->ChunkIDs = NewValue;
        }
        else if (Version::IsAtLeast(4, 27))
        {
            std::bit_cast<FAssetData427Plus*>(this)->ChunkIDs = NewValue;
        }
        else
        {
            throw std::runtime_error{"FAssetData::NewChunkIDsUnsafe can only be used in 4.27+"};
        }
    }

    void FAssetData::SetPackageFlags(uint32 NewValue)
    {
        EnsureFAssetDataAvailability();

        if (Version::IsAtLeast(5, 1))
        {
            std::bit_cast<FAssetData51Plus*>(this)->PackageFlags = NewValue;
        }
        else if (Version::IsAtLeast(4, 27))
        {
            std::bit_cast<FAssetData427Plus*>(this)->PackageFlags = NewValue;
        }
        else
        {
            std::bit_cast<FAssetDataPre427*>(this)->PackageFlags = NewValue;
        }
    }

    void FAssetData::SetAssetClassPath(FTopLevelAssetPath& NewValue)
    {
        if (Version::IsBelow(5, 1)) { throw std::runtime_error{"FAssetData::SetAssetClassPath is only available in 5.1+"}; }

        std::bit_cast<FAssetData51Plus*>(this)->AssetClassPath = NewValue;
    }

    int32 FAssetData::StaticSize()
    {
        if (Version::IsBelow(4, 17)) { throw std::runtime_error{"FAssetData only available in 4.17+"}; };

        if (StaticSize_Private == -1)
        {
            StaticSize_Private = std::bit_cast<UScriptStruct*>(FAssetData::StaticClass())->GetSize();
        }

        return StaticSize_Private;
    }
}
