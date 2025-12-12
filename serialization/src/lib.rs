use serde::{Deserialize, Serialize};
use std::ffi::{CStr, CString};
use std::os::raw::c_char;

/// Entity data structure matching C++ ECS
#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct Entity {
    pub id: u64,
    pub components: Vec<ComponentData>,
}

/// Generic component data
#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct ComponentData {
    pub type_name: String,
    pub data: Vec<u8>,
}

/// Scene data structure
#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct Scene {
    pub name: String,
    pub entities: Vec<Entity>,
}

/// Serialize scene to binary format
pub fn serialize_scene(scene: &Scene) -> Result<Vec<u8>, bincode::Error> {
    bincode::serialize(scene)
}

/// Deserialize scene from binary format
pub fn deserialize_scene(data: &[u8]) -> Result<Scene, bincode::Error> {
    bincode::deserialize(data)
}

// ============================================
// C ABI Exports for C++ Interop
// ============================================

/// Serialize scene and return pointer to binary data
/// Caller must free the returned pointer using free_buffer
#[no_mangle]
pub extern "C" fn serialize_scene_c(
    scene_name: *const c_char,
    entity_count: usize,
    out_buffer: *mut *mut u8,
    out_size: *mut usize,
) -> i32 {
    if scene_name.is_null() || out_buffer.is_null() || out_size.is_null() {
        return -1; // Invalid arguments
    }

    unsafe {
        let name = match CStr::from_ptr(scene_name).to_str() {
            Ok(s) => s.to_string(),
            Err(_) => return -2, // Invalid UTF-8
        };

        // Create a dummy scene for demonstration
        let scene = Scene {
            name,
            entities: Vec::new(), // TODO: Accept entity data from C++
        };

        match serialize_scene(&scene) {
            Ok(data) => {
                let size = data.len();
                let buffer = Box::into_raw(data.into_boxed_slice()) as *mut u8;
                
                *out_buffer = buffer;
                *out_size = size;
                0 // Success
            }
            Err(_) => -3, // Serialization error
        }
    }
}

/// Deserialize scene from binary buffer
#[no_mangle]
pub extern "C" fn deserialize_scene_c(
    buffer: *const u8,
    size: usize,
    out_name: *mut c_char,
    name_capacity: usize,
) -> i32 {
    if buffer.is_null() || out_name.is_null() {
        return -1;
    }

    unsafe {
        let data = std::slice::from_raw_parts(buffer, size);
        
        match deserialize_scene(data) {
            Ok(scene) => {
                let name_cstr = match CString::new(scene.name) {
                    Ok(s) => s,
                    Err(_) => return -2,
                };

                let name_bytes = name_cstr.as_bytes_with_nul();
                if name_bytes.len() > name_capacity {
                    return -3; // Buffer too small
                }

                std::ptr::copy_nonoverlapping(
                    name_bytes.as_ptr() as *const c_char,
                    out_name,
                    name_bytes.len(),
                );

                0 // Success
            }
            Err(_) => -4, // Deserialization error
        }
    }
}

/// Free buffer allocated by serialize_scene_c
#[no_mangle]
pub extern "C" fn free_buffer(buffer: *mut u8, size: usize) {
    if !buffer.is_null() {
        unsafe {
            let _ = Box::from_raw(std::slice::from_raw_parts_mut(buffer, size));
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_scene_serialization() {
        let scene = Scene {
            name: "TestScene".to_string(),
            entities: vec![
                Entity {
                    id: 1,
                    components: vec![],
                },
            ],
        };

        let serialized = serialize_scene(&scene).unwrap();
        let deserialized = deserialize_scene(&serialized).unwrap();

        assert_eq!(scene.name, deserialized.name);
        assert_eq!(scene.entities.len(), deserialized.entities.len());
    }
}
