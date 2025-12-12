-- Example Lua script for PrimeFlux Engine
-- This demonstrates the gameplay scripting API

print("[Lua] Script loaded: example_script.lua")

-- Entity behavior callback
function OnUpdate(entity_id, delta_time)
    -- This would be called from C++ for each entity with this script
    -- print(string.format("[Lua] Entity %d updating, dt=%.3f", entity_id, delta_time))
end

-- Entity initialization
function OnStart(entity_id)
    print(string.format("[Lua] Entity %d started", entity_id))
end

-- Entity cleanup
function OnDestroy(entity_id)
    print(string.format("[Lua] Entity %d destroyed", entity_id))
end

-- Example gameplay function
function DamageEntity(entity_id, damage)
    print(string.format("[Lua] Entity %d took %d damage", entity_id, damage))
    -- TODO: Interact with C++ ECS to modify health component
    return true
end

-- Return script metadata
return {
    name = "ExampleScript",
    version = "1.0",
    author = "PrimeFlux"
}
