#pragma once

#include <cstdint>
#include <cstddef>

// C ABI interface to Rust serialization library

extern "C" {
    /**
     * Serialize a scene to binary format
     * @param scene_name Name of the scene
     * @param entity_count Number of entities (reserved for future use)
     * @param out_buffer Output buffer pointer (allocated by Rust)
     * @param out_size Output buffer size
     * @return 0 on success, negative on error
     */
    int32_t serialize_scene_c(
        const char* scene_name,
        size_t entity_count,
        uint8_t** out_buffer,
        size_t* out_size
    );

    /**
     * Deserialize a scene from binary buffer
     * @param buffer Input binary data
     * @param size Size of input data
     * @param out_name Output scene name buffer
     * @param name_capacity Capacity of name buffer
     * @return 0 on success, negative on error
     */
    int32_t deserialize_scene_c(
        const uint8_t* buffer,
        size_t size,
        char* out_name,
        size_t name_capacity
    );

    /**
     * Free buffer allocated by Rust
     * @param buffer Buffer to free
     * @param size Size of buffer
     */
    void free_buffer(uint8_t* buffer, size_t size);
}
