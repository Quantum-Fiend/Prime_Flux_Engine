#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <cstdint>

namespace PrimeFlux {

// Type aliases
using EntityID = uint64_t;
using ComponentTypeID = std::type_index;

/**
 * @brief Base component class - all components inherit from this
 */
struct Component {
    virtual ~Component() = default;
};

/**
 * @brief Entity-Component-System implementation
 */
class ECS {
public:
    ECS();
    ~ECS();

    // Entity management
    EntityID CreateEntity();
    void DestroyEntity(EntityID entity);
    bool IsEntityValid(EntityID entity) const;

    // Component management
    template<typename T, typename... Args>
    T* AddComponent(EntityID entity, Args&&... args);
    
    template<typename T>
    T* GetComponent(EntityID entity);
    
    template<typename T>
    void RemoveComponent(EntityID entity);
    
    template<typename T>
    bool HasComponent(EntityID entity) const;

    // System execution
    void Update(float deltaTime);

    // Query entities with specific components
    template<typename... Components>
    std::vector<EntityID> GetEntitiesWith();

private:
    EntityID m_nextEntityID;
    std::vector<EntityID> m_entities;
    
    // Component storage: ComponentType -> (EntityID -> Component*)
    std::unordered_map<ComponentTypeID, 
        std::unordered_map<EntityID, std::unique_ptr<Component>>> m_components;
};

// Template implementations
template<typename T, typename... Args>
T* ECS::AddComponent(EntityID entity, Args&&... args) {
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
    
    auto typeID = std::type_index(typeid(T));
    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    T* ptr = component.get();
    
    m_components[typeID][entity] = std::move(component);
    return ptr;
}

template<typename T>
T* ECS::GetComponent(EntityID entity) {
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
    
    auto typeID = std::type_index(typeid(T));
    auto& componentMap = m_components[typeID];
    
    auto it = componentMap.find(entity);
    if (it != componentMap.end()) {
        return static_cast<T*>(it->second.get());
    }
    return nullptr;
}

template<typename T>
void ECS::RemoveComponent(EntityID entity) {
    auto typeID = std::type_index(typeid(T));
    m_components[typeID].erase(entity);
}

template<typename T>
bool ECS::HasComponent(EntityID entity) const {
    auto typeID = std::type_index(typeid(T));
    auto it = m_components.find(typeID);
    if (it != m_components.end()) {
        return it->second.find(entity) != it->second.end();
    }
    return false;
}

} // namespace PrimeFlux
