#include "ECS.h"
#include <algorithm>
#include <iostream>

namespace PrimeFlux {

ECS::ECS() : m_nextEntityID(1) {
    std::cout << "[ECS] Entity-Component-System initialized" << std::endl;
}

ECS::~ECS() {
    m_components.clear();
    m_entities.clear();
}

EntityID ECS::CreateEntity() {
    EntityID id = m_nextEntityID++;
    m_entities.push_back(id);
    return id;
}

void ECS::DestroyEntity(EntityID entity) {
    // Remove from entity list
    auto it = std::find(m_entities.begin(), m_entities.end(), entity);
    if (it != m_entities.end()) {
        m_entities.erase(it);
    }

    // Remove all components for this entity
    for (auto& [typeID, componentMap] : m_components) {
        componentMap.erase(entity);
    }
}

bool ECS::IsEntityValid(EntityID entity) const {
    return std::find(m_entities.begin(), m_entities.end(), entity) != m_entities.end();
}

void ECS::Update(float deltaTime) {
    // TODO: Execute systems
    // For now, this is a placeholder
}

} // namespace PrimeFlux
