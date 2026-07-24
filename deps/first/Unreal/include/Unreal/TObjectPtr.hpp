#pragma once

#define UE_WITH_OBJECT_PTR_DEPRECATIONS 0
#if UE_WITH_OBJECT_PTR_DEPRECATIONS
    #define UE_OBJPTR_DEPRECATED(Version, Message) UE_DEPRECATED(Version, Message)
#else
    #define UE_OBJPTR_DEPRECATED(Version, Message) 
#endif

namespace RC::Unreal
{
    class UObject;
    
    template<typename T>
    class TObjectPtr
    {
    public:
        using ElementType = T;
        // Constructors
        TObjectPtr() : Ptr(nullptr) {}
        TObjectPtr(TYPE_OF_NULLPTR) : Ptr(nullptr) {}
        TObjectPtr(const TObjectPtr& Other) : Ptr(Other.Ptr) {}
        explicit TObjectPtr(ElementType* InPtr) : Ptr(InPtr) {}
    
        // Assignment operators
        TObjectPtr& operator=(const TObjectPtr& Other) { Ptr = Other.Ptr; return *this; }
        TObjectPtr& operator=(TYPE_OF_NULLPTR) { Ptr = nullptr; return *this; }
        TObjectPtr& operator=(ElementType* InPtr) { Ptr = InPtr; return *this; }
            
        // Conversion operators
        FORCEINLINE operator T* () const { return Get(); }
        template <typename U>
        UE_OBJPTR_DEPRECATED(5.0, "Explicit cast to other raw pointer types is deprecated.  Please use the Cast API or get the raw pointer with ToRawPtr and cast that instead.")
        explicit FORCEINLINE operator U* () const { return (U*)Get(); }
        explicit FORCEINLINE operator UPTRINT() const { return (UPTRINT)Get(); }
        FORCEINLINE T* operator->() const { return Get(); }
        FORCEINLINE T& operator*() const { return *Get(); }
    
        // Comparison operators
        bool operator==(const TObjectPtr& Other) const { return Ptr == Other.Ptr; }
        bool operator!=(const TObjectPtr& Other) const { return Ptr != Other.Ptr; }
        bool operator==(const ElementType* InPtr) const { return Ptr == InPtr; }
        bool operator!=(const ElementType* InPtr) const { return Ptr != InPtr; }
        bool operator==(TYPE_OF_NULLPTR) const { return Ptr == nullptr; }
        bool operator!=(TYPE_OF_NULLPTR) const { return Ptr != nullptr; }
    
        // Additional API compatibility with UE's TObjectPtr
        bool operator!() const { return Ptr == nullptr; }
        explicit operator bool() const { return Ptr != nullptr; }
        ElementType* Get() const { return Ptr; }
    
    private:
        ElementType* Ptr;
    };

    template <typename T>
    TObjectPtr<T> ToObjectPtr(T* Obj)
    {
        return TObjectPtr<T>{Obj};
    }

    template <typename T>
    FORCEINLINE T* ToRawPtr(const TObjectPtr<T>& Ptr)
    {
        // NOTE: This is specifically not getting a reference to the internal pointer.
        return Ptr.Get();
    }

    template <typename T>
    FORCEINLINE T* ToRawPtr(T* Ptr)
    {
        return Ptr;
    }

    // TODO: Move to its own file.
    template<class TClass>
    class TSubclassOf
    {
    public:
        TClass* Class;
    };
}

