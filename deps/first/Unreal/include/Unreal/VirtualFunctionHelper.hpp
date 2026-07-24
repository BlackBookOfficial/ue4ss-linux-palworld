#pragma once

#include <unordered_map>
#include <stdexcept>
#include <type_traits>

/**
 * Used to store shared objects with the same identifier
 * Primary use case is bypassing the fact that templates are instantiated per-DLL,
 * so you cannot really use them to store static shared data
 */
class SharedObjectManager {
public:
    template<typename T>
    static inline T& GetSharedObject(const char* UniqueIdentifier)
    {
        auto* ExistingValue = reinterpret_cast<T*>(GetSharedObjectInternal(UniqueIdentifier));
        if (ExistingValue != nullptr)
        {
            return *ExistingValue;
        }
        auto* NewValue = new T();
        SetSharedObjectInternal(UniqueIdentifier, NewValue);
        return *NewValue;
    }
private:
    static void* GetSharedObjectInternal(const char* Id);
    static void SetSharedObjectInternal(const char* Id, void* NewValue);
};

/**
 * Allows accessing type of the object of the provided type
 * Will be used by the virtual call machinery to correctly dispatch virtual function calls
 *
 * The class should provide following properties:
 *  -typename ClassType - type of the object class
 *  -template<typename U> static auto StaticClass() -> ClassType - retrieves the class of the template object type U
 *  -static auto GetClassSuperClass(ClassType) -> ClassType - retrieves the superclass of the provided class
 *  -static auto RegisterLateBindCallback(void(*Callback)()) - registers the callback to be called after StaticClass() is safe to call
 *  -static auto IsClassValid(ClassType) -> bool - returns true if the provided class object is valid
 *
 *  The class extending it should be declared as the typedef named TypeAccessor of your object type
 */
class BaseTypeAccessor {
};

template<typename TCallable, TCallable Callable>
class VirtualFunctionInvoker;

template<typename ReceiverType, typename ReturnValueType, typename... ArgumentTypes, ReturnValueType(ReceiverType::*MemberFuncPtr)(ArgumentTypes...)>
class VirtualFunctionInvoker<ReturnValueType(ReceiverType::*)(ArgumentTypes...), MemberFuncPtr>
{
private:
    using DispatcherFuncType = ReturnValueType(*)(ReceiverType* Self, ArgumentTypes... Args);
    using TypeAccessor = typename ReceiverType::TypeAccessor;
    using ObjectClassType = typename TypeAccessor::ClassType;
    using DispatchMapType = std::unordered_map<ObjectClassType, DispatcherFuncType>;

    inline static auto GetDispatchMap() -> DispatchMapType&
    {
#ifdef _MSC_VER
        return SharedObjectManager::GetSharedObject<DispatchMapType>(__FUNCDNAME__);
#else
        return SharedObjectManager::GetSharedObject<DispatchMapType>(__PRETTY_FUNCTION__);
#endif
    }
public:
    /** Registers the dispatch function associated with the provided class */
    inline static auto RegisterDispatchFunc(ObjectClassType clazz, DispatcherFuncType dispatch_func)
    {
        GetDispatchMap().insert({clazz, dispatch_func});
    }

    /** Dispatches the virtual function call on the provided object */
    inline static auto DispatchCall(ReceiverType* Receiver, ArgumentTypes... Args) -> ReturnValueType
    {
        ObjectClassType ObjectClass = TypeAccessor::GetObjectClass(Receiver);
        DispatchMapType& DispatchMap = GetDispatchMap();

        DispatcherFuncType DispatcherFunc = nullptr;
        while (TypeAccessor::IsClassValid(ObjectClass))
        {
            const auto Iterator = DispatchMap.find(ObjectClass);
            if (Iterator != DispatchMap.end())
            {
                DispatcherFunc = Iterator->second;
                break;
            }
            ObjectClass = TypeAccessor::GetClassSuperClass(ObjectClass);
        }

        if (DispatcherFunc == nullptr)
        {
            throw std::runtime_error("Pure virtual function not implemented");
        }

        if constexpr(std::is_same_v<ReturnValueType, void>)
        {
            DispatcherFunc(Receiver, Args...);
        }
        else
        {
            return DispatcherFunc(Receiver, Args...);
        }
    }
};

template<typename TThunkCallable, typename TImplCallable, TThunkCallable ThunkCallable, TImplCallable ImplCallable>
class VirtualFunctionRegistrar;

template<typename BaseReceiverType, typename ImplReceiverType, typename ReturnValueType, typename... ArgumentTypes,
        ReturnValueType(BaseReceiverType::*BaseFunctionPtr)(ArgumentTypes...),
        ReturnValueType(ImplReceiverType::*ImplFunctionPtr)(ArgumentTypes...)>
class VirtualFunctionRegistrar<ReturnValueType(BaseReceiverType::*)(ArgumentTypes...), ReturnValueType(ImplReceiverType::*)(ArgumentTypes...), BaseFunctionPtr, ImplFunctionPtr> {
private:
    using InvokerType = VirtualFunctionInvoker<ReturnValueType(BaseReceiverType::*)(ArgumentTypes...), BaseFunctionPtr>;
    using TypeAccessor = typename BaseReceiverType::TypeAccessor;
public:
    /** Registers the dispatch function inside of the invoker */
    inline VirtualFunctionRegistrar()
    {
        TypeAccessor::RegisterLateBindCallback(&BindVirtualFunction);
    }
private:
    /** Performs the actual binding of the virtual function to the static class */
    static auto BindVirtualFunction() -> void
    {
        InvokerType::RegisterDispatchFunc(TypeAccessor::template StaticClass<ImplReceiverType>(), &DispatchCall);
    }

    /** Dispatches the call to the member function implementation in the impl class */
    static auto DispatchCall(BaseReceiverType* Self, ArgumentTypes... Args) -> ReturnValueType
    {
        if constexpr(std::is_same_v<ReturnValueType, void>)
        {
            (*static_cast<ImplReceiverType*>(Self).*ImplFunctionPtr)(Args...);
        }
        else
        {
            return (*static_cast<ImplReceiverType*>(Self).*ImplFunctionPtr)(Args...);
        }
    }
};


/** Defines declarations needed for overriding virtual functions */
#define DECLARE_VIRTUAL_TYPE(ClassName) \
    template<typename InClassName, typename TFunctionType, TFunctionType Function> \
    friend class VirtualFunctionRegistrarHolder;     \
    template<typename TCallable, TCallable Callable> \
    friend class VirtualFunctionInvoker;             \
    template<typename TThunkCallable, typename TImplCallable, TThunkCallable ThunkCallable, TImplCallable ImplCallable> \
    friend class VirtualFunctionRegistrar;           \
    using TypeAccessor = VirtualTypeBaseClass::TypeAccessor; \

/** Defines the basic data needed for the root virtual class */
#define DECLARE_VIRTUAL_TYPE_BASE(ClassName, TypeAccessorClass) \
    using TypeAccessor = TypeAccessorClass;          \
    using VirtualTypeBaseClass = ClassName;          \
    template<typename InClassName, typename TFunctionType, TFunctionType Function> \
    friend class VirtualFunctionRegistrarHolder;     \
    template<typename TCallable, TCallable Callable> \
    friend class VirtualFunctionInvoker;             \
    template<typename TThunkCallable, typename TImplCallable, TThunkCallable ThunkCallable, TImplCallable ImplCallable> \
    friend class VirtualFunctionRegistrar;           \
protected:

/** Registers the implementation override for the provided function */
#define IMPLEMENT_VIRTUAL_FUNCTION(ClassName, FunctionName) \
template<typename ClassName, typename TFunctionType, TFunctionType Function> \
class VirtualFunctionRegistrarHolder;                       \
template<>                                                  \
class VirtualFunctionRegistrarHolder<ClassName, decltype(&ClassName::FunctionName), &ClassName::FunctionName> \
{                                                           \
public:                                                     \
   using InnerType = VirtualFunctionRegistrar<decltype(&ClassName::FunctionName), decltype(&ClassName::PREPROCESSOR_JOIN(FunctionName, _Impl)), &ClassName::FunctionName, &ClassName::PREPROCESSOR_JOIN(FunctionName, _Impl)>; \
};                                                          \
static VirtualFunctionRegistrarHolder<ClassName, decltype(&ClassName::FunctionName), &ClassName::FunctionName>::InnerType PREPROCESSOR_JOIN3(__virtual_function_registrar_, ClassName, FunctionName); \

/** Performs a call to the virtual function with the provided name */
#define CALL_VIRTUAL_FUNCTION(Self, FunctionName, ...) \
    VirtualFunctionInvoker<decltype(&std::remove_reference_t<decltype(*Self)>::FunctionName), &std::remove_reference_t<decltype(*Self)>::FunctionName>::DispatchCall(Self, __VA_ARGS__)

