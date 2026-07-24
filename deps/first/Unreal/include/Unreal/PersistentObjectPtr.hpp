#pragma once
#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/UnrealCoreStructs.hpp>
#include <Unreal/FWeakObjectPtr.hpp>

namespace RC::Unreal
{
    template<class TObjectID>
    struct TPersistentObjectPtr
    {
        public:
        /** Default constructor, will be null */
        TPersistentObjectPtr()
        {
            Reset();
        }

        /** Reset the lazy pointer back to the null state */
        FORCEINLINE void Reset()
        {
            WeakPtr.Reset();
            ObjectID.Reset();
            TagAtLastTest = 0;
        }

        /** Resets the weak ptr only, call this when ObjectId may change */
        FORCEINLINE void ResetWeakPtr()
        {
            WeakPtr.Reset();
            TagAtLastTest = 0;
        }

        /** Construct from a unique object identifier */
        explicit FORCEINLINE TPersistentObjectPtr(const TObjectID& InObjectID)
            : WeakPtr()
            , TagAtLastTest(0)
            , ObjectID(InObjectID)
        {
        }

        /** Copy from a unique object identifier */
        FORCEINLINE void operator=(const TObjectID& InObjectID)
        {
            WeakPtr.Reset();
            ObjectID = InObjectID;
            TagAtLastTest = 0;
        }

        /** Copy from an object pointer */
        FORCEINLINE void operator=(const class UObject* Object)
        {
            if (Object)
            {
                ObjectID = TObjectID::GetOrCreateIDForObject(Object);
                WeakPtr = Object;
                TagAtLastTest = TObjectID::GetCurrentTag();
            }
            else
            {
                Reset();
            }
        }

        /**
        * Gets the unique object identifier associated with this lazy pointer. Valid even if pointer is not currently valid
        *
        * @return Unique ID for this object, or an invalid FUniqueObjectGuid if this pointer isn't set to anything
        */
        FORCEINLINE const TObjectID& GetUniqueID() const
        {
            return ObjectID;
        }

        /** Non-const version of the above */
        FORCEINLINE TObjectID& GetUniqueID()
        {
            return ObjectID;
        }

        /**
        * Dereference the pointer, which may cause it to become valid again. Will not try to load pending outside of game thread
        *
        * @return nullptr if this object is gone or the pointer was null, otherwise a valid UObject pointer
        */
        FORCEINLINE UObject* Get() const
        {
            UObject* Object = WeakPtr.Get();

            // Do a full resolve if the returned object is null and either we think we've loaded new objects, or the weak ptr may be stale
            if (!Object && ObjectID.IsValid()) /*&& (TObjectID::GetCurrentTag() != TagAtLastTest || WeakPtr.ObjectIndex != INDEX_NONE)   <<--last conditional optimization to reduce full resolve, not possible because GetCurrentTag is unavailable */
            {
                Object = ObjectID.ResolveObject();
                WeakPtr = Object;

                // Note: Only used in Editor
                // Not safe to update tag during save as ResolveObject may have failed accidentally
                //if (Object || !GIsSavingPackage)
                //{
                //    TagAtLastTest = TObjectID::GetCurrentTag();
                //}

                // If this object is pending kill or otherwise invalid, this will return nullptr as expected
                Object = WeakPtr.Get();
            }
            return Object;
        }

        /** Dereference the pointer */
        FORCEINLINE class UObject& operator*() const
        {
            return *Get();
        }

        /** Dereference the pointer */
        FORCEINLINE class UObject* operator->() const
        {
            return Get();
        }

        /** Compare pointers for equality. Only Serial Number matters for the base implementation */
        FORCEINLINE friend bool operator==(const TPersistentObjectPtr& Lhs, const TPersistentObjectPtr& Rhs)
        {
            return Lhs.ObjectID == Rhs.ObjectID;
        }

        FORCEINLINE friend bool operator==(const TPersistentObjectPtr& Lhs, TYPE_OF_NULLPTR)
        {
            return !Lhs.IsValid();
        }

        FORCEINLINE friend bool operator==(TYPE_OF_NULLPTR, const TPersistentObjectPtr& Rhs)
        {
            return !Rhs.IsValid();
        }

        /** Compare pointers for inequality. Only Serial Number matters for the base implementation */
        FORCEINLINE friend bool operator!=(const TPersistentObjectPtr& Lhs, const TPersistentObjectPtr& Rhs)
        {
            return Lhs.ObjectID != Rhs.ObjectID;
        }

        FORCEINLINE friend bool operator!=(const TPersistentObjectPtr& Lhs, TYPE_OF_NULLPTR)
        {
            return Lhs.IsValid();
        }

        FORCEINLINE friend bool operator!=(TYPE_OF_NULLPTR, const TPersistentObjectPtr& Rhs)
        {
            return Rhs.IsValid();
        }

        /**
        * Test if this does not point to a live UObject, but may in the future
        *
        * @return true if this does not point to a real object, but could possibly
        */
        FORCEINLINE bool IsPending() const
        {
            return Get() == nullptr && ObjectID.IsValid();
        }

        /**
        * Test if this points to a live UObject
        *
        * @return true if Get() would return a valid non-null pointer
        */
        FORCEINLINE bool IsValid() const
        {
            return !!Get();
        }

        /**
        * Slightly different than !IsValid(), returns true if this used to point to a UObject, but doesn't any more and has not been assigned or reset in the mean time.
        *
        * @return true if this used to point at a real object but no longer does.
        */
        FORCEINLINE bool IsStale() const
        {
            return WeakPtr.IsStale();
        }

        /**
        * Test if this can never point to a live UObject
        *
        * @return true if this is explicitly pointing to no object
        */
        FORCEINLINE bool IsNull() const
        {
            return !ObjectID.IsValid();
        }

        // RE-UE4SS FIX (Martin): [Member variables must be public, because UE4SS uses them directly, and we don't want to break API]
    public:

        /** Once the object has been noticed to be loaded, this is set to the object weak pointer **/
        mutable FWeakObjectPtr WeakPtr;
        /** Compared to CurrentAnnotationTag and if they are not equal, a guid search will be performed **/
        mutable int32 TagAtLastTest;
        /** Guid for the object this pointer points to or will point to. **/
        TObjectID ObjectID;
        // RE-UE4SS FIX END
};

    struct FUniqueObjectGuid
    {
        FGuid Guid;

        /** Reset the guid pointer back to the invalid state */
        FORCEINLINE void Reset()
        {
            Guid.invalidate();
        }
    };
}


