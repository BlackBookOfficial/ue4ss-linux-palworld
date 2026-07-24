#pragma once
#include <Unreal/FString.hpp>
#include <Unreal/NameTypes.hpp>
namespace RC::Unreal
{
    struct RC_UE_API FSoftObjectPath
    {
        FSoftObjectPath() {}

        /** Construct from a path string. Non-explicit for backwards compatibility. */
        FSoftObjectPath(const FString& Path) { SetPath(Path);};

        explicit FSoftObjectPath(TYPE_OF_NULLPTR){}

        /** Construct from an existing object in memory */
        FSoftObjectPath(const UObject* InObject);

        FSoftObjectPath& operator=(const FString& Path)						{ SetPath(Path); return *this; }

        /** Returns string representation of reference, in form /package/path.assetname[:subpath] */
        FString ToString() const;

        /** Returns the entire asset path as an FName, including both package and asset but not sub object */
        FORCEINLINE FName GetAssetPathName() const
        {
            return AssetPathName;
        }

        /** Returns string version of asset path, including both package and asset but not sub object */
        FORCEINLINE FString GetAssetPathString() const
        {
            if (AssetPathName.IsNone())
            {
                return FString();
            }

            return AssetPathName.ToFString();
        }

        /** Returns the sub path, which is often empty */
        FORCEINLINE const FString& GetSubPathString() const
        {
            return SubPathString;
        }

        /** Sets asset path of this reference based on a string path */
        void SetPath(const FString& Path);

        /**
        * Attempts to load the asset, this will call LoadObject which can be very slow
        * @param InLoadContext Optional load context when called from nested load callstack
        * @return Loaded UObject, or nullptr if the reference is null or the asset fails to load
        */
        UObject* TryLoad(/*FUObjectSerializeContext* InLoadContext = nullptr*/) const;

        /**
        * Attempts to find a currently loaded object that matches this path
        *
        * @return Found UObject, or nullptr if not currently in memory
        */
        UObject* ResolveObject() const;

        /** Resets reference to point to null */
        void Reset()
        {
            AssetPathName = FName();
            SubPathString.Reset();
        }

        /** Check if this could possibly refer to a real object, or was initialized to null */
        FORCEINLINE bool IsValid() const
        {
            return !AssetPathName.IsNone();
        }

        /** Checks to see if this is initialized to null */
        FORCEINLINE bool IsNull() const
        {
            return AssetPathName.IsNone();
        }

        /** Check if this represents an asset, meaning it is not null but does not have a sub path */
        FORCEINLINE bool IsAsset() const
        {
            return !AssetPathName.IsNone() && SubPathString.IsEmpty();
        }

        /** Check if this represents a sub object, meaning it has a sub path */
        FORCEINLINE bool IsSubobject() const
        {
            return !AssetPathName.IsNone() && !SubPathString.IsEmpty();
        }

        /** Code needed by FSoftObjectPtr internals */
        static int32 GetCurrentTag();
        static FSoftObjectPath GetOrCreateIDForObject(const UObject* Object);

        // RE-UE4SS FIX (Martin): [Member variables must be public, because UE4SS uses them directly, and we don't want to break API]
    public:
        /** Asset path, patch to a top level object in a package. This is /package/path.assetname */
        FName AssetPathName;

        /** Optional FString for subobject within an asset. This is the sub path after the : */
        FString SubPathString;

    private:
        // RE-UE4SS FIX END
        UObject* ResolveObjectInternal() const;
        UObject* ResolveObjectInternal(const TCHAR* PathString) const;
    };
}