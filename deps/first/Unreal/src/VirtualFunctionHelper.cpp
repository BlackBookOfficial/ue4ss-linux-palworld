#include <Unreal/VirtualFunctionHelper.hpp>

auto GetSharedObjects() -> std::unordered_map<std::string, void*>&
{
    static std::unordered_map<std::string, void*> SSharedObjects;
    return SSharedObjects;
}

void* SharedObjectManager::GetSharedObjectInternal(const char* Id)
{
    const auto Iterator = GetSharedObjects().find(std::string(Id));
    return Iterator != GetSharedObjects().end() ? Iterator->second : nullptr;
}

void SharedObjectManager::SetSharedObjectInternal(const char* Id, void* NewValue)
{
    GetSharedObjects().insert({std::string(Id), NewValue});
}
