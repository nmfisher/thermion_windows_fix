#ifndef _DART_FILAMENT_FFI_API_H
#define _DART_FILAMENT_FFI_API_H

#include "ThermionDartApi.h"

#ifdef __cplusplus
extern "C"
{
#endif

    ///
    /// This header replicates most of the methods in ThermionDartApi.h. 
    /// It represents the interface for:
    /// - invoking those methods that must be called on the main Filament engine thread
    /// - setting up a render loop
    ///
    typedef int32_t EntityId;
    typedef void (*FilamentRenderCallback)(void *const owner);

    EMSCRIPTEN_KEEPALIVE void create_filament_viewer_ffi(
        void *const context,
        void *const platform,
        const char *uberArchivePath,
        const void *const loader,
        void (*renderCallback)(void *const renderCallbackOwner),
        void *const renderCallbackOwner,
        void (*callback)(void *const viewer));
    EMSCRIPTEN_KEEPALIVE void create_swap_chain_ffi(void *const viewer, void *const surface, uint32_t width, uint32_t height, void (*onComplete)());
    EMSCRIPTEN_KEEPALIVE void destroy_swap_chain_ffi(void *const viewer, void (*onComplete)());
    EMSCRIPTEN_KEEPALIVE void create_render_target_ffi(void *const viewer, intptr_t nativeTextureId, uint32_t width, uint32_t height, void (*onComplete)());
    EMSCRIPTEN_KEEPALIVE void destroy_filament_viewer_ffi(void *const viewer);
    EMSCRIPTEN_KEEPALIVE void render_ffi(void *const viewer);
    EMSCRIPTEN_KEEPALIVE FilamentRenderCallback make_render_callback_fn_pointer(FilamentRenderCallback);
    EMSCRIPTEN_KEEPALIVE void set_rendering_ffi(void *const viewer, bool rendering, void(*onComplete)());
    EMSCRIPTEN_KEEPALIVE void set_frame_interval_ffi(void *const viewer, float frameInterval);
    EMSCRIPTEN_KEEPALIVE void update_viewport_and_camera_projection_ffi(void *const viewer, const uint32_t width, const uint32_t height, const float scaleFactor, void (*onComplete)());
    EMSCRIPTEN_KEEPALIVE void set_background_color_ffi(void *const viewer, const float r, const float g, const float b, const float a);
    EMSCRIPTEN_KEEPALIVE void clear_background_image_ffi(void *const viewer);
    EMSCRIPTEN_KEEPALIVE void set_background_image_ffi(void *const viewer, const char *path, bool fillHeight, void (*onComplete)());
    EMSCRIPTEN_KEEPALIVE void set_background_image_position_ffi(void *const viewer, float x, float y, bool clamp);
    EMSCRIPTEN_KEEPALIVE void set_tone_mapping_ffi(void *const viewer, int toneMapping);
    EMSCRIPTEN_KEEPALIVE void set_bloom_ffi(void *const viewer, float strength);
    EMSCRIPTEN_KEEPALIVE void load_skybox_ffi(void *const viewer, const char *skyboxPath, void (*onComplete)());
    EMSCRIPTEN_KEEPALIVE void load_ibl_ffi(void *const viewer, const char *iblPath, float intensity);
    EMSCRIPTEN_KEEPALIVE void remove_skybox_ffi(void *const viewer);
    EMSCRIPTEN_KEEPALIVE void remove_ibl_ffi(void *const viewer);
    EMSCRIPTEN_KEEPALIVE void add_light_ffi(
        void *const viewer,
        uint8_t type,
        float colour,
        float intensity,
        float posX,
        float posY,
        float posZ,
        float dirX,
        float dirY,
        float dirZ,
        float falloffRadius,
        float spotLightConeInner,
        float spotLightConeOuter,
        float sunAngularRadius,
        float sunHaloSize,
        float sunHaloFallof,
        bool shadows,
        void (*callback)(EntityId));
    EMSCRIPTEN_KEEPALIVE void remove_light_ffi(void *const viewer, EntityId entityId);
    EMSCRIPTEN_KEEPALIVE void clear_lights_ffi(void *const viewer);
    EMSCRIPTEN_KEEPALIVE void load_glb_ffi(void *const sceneManager, const char *assetPath, int numInstances, void (*callback)(EntityId));
    EMSCRIPTEN_KEEPALIVE void load_glb_from_buffer_ffi(void *const sceneManager, const void *const data, size_t length, int numInstances, void (*callback)(EntityId));
    EMSCRIPTEN_KEEPALIVE void load_gltf_ffi(void *const sceneManager, const char *assetPath, const char *relativePath, void (*callback)(EntityId));
    EMSCRIPTEN_KEEPALIVE void create_instance_ffi(void *const sceneManager, EntityId entityId, void (*callback)(EntityId));
    EMSCRIPTEN_KEEPALIVE void remove_entity_ffi(void *const viewer, EntityId asset, void (*callback)());
    EMSCRIPTEN_KEEPALIVE void clear_entities_ffi(void *const viewer, void (*callback)());
    EMSCRIPTEN_KEEPALIVE void set_camera_ffi(void *const viewer, EntityId asset, const char *nodeName, void (*callback)(bool));
    EMSCRIPTEN_KEEPALIVE void apply_weights_ffi(
        void *const sceneManager,
        EntityId asset,
        const char *const entityName,
        float *const weights,
        int count);

    EMSCRIPTEN_KEEPALIVE void play_animation_ffi(void *const sceneManager, EntityId asset, int index, bool loop, bool reverse, bool replaceActive, float crossfade);
    EMSCRIPTEN_KEEPALIVE void set_animation_frame_ffi(void *const sceneManager, EntityId asset, int animationIndex, int animationFrame);
    EMSCRIPTEN_KEEPALIVE void stop_animation_ffi(void *const sceneManager, EntityId asset, int index);
    EMSCRIPTEN_KEEPALIVE void get_animation_count_ffi(void *const sceneManager, EntityId asset, void (*callback)(int));
    EMSCRIPTEN_KEEPALIVE void get_animation_name_ffi(void *const sceneManager, EntityId asset, char *const outPtr, int index, void (*callback)());
    EMSCRIPTEN_KEEPALIVE void get_morph_target_name_ffi(void *const sceneManager, EntityId assetEntity, EntityId childEntity, char *const outPtr, int index, void (*callback)());
    EMSCRIPTEN_KEEPALIVE void get_morph_target_name_count_ffi(void *const sceneManager, EntityId asset, EntityId childEntity, void (*callback)(int32_t));
    EMSCRIPTEN_KEEPALIVE void set_morph_target_weights_ffi(void *const sceneManager,
                                                            EntityId asset,
                                                            const float *const morphData,
                                                            int numWeights,
                                                            void (*callback)(bool));

    EMSCRIPTEN_KEEPALIVE void update_bone_matrices_ffi(void *sceneManager,
        EntityId asset, void(*callback)(bool));
    EMSCRIPTEN_KEEPALIVE void set_bone_transform_ffi(
        void *sceneManager,
        EntityId asset,
        int skinIndex, 
        int boneIndex,
        const float *const transform,
        void (*callback)(bool));
    EMSCRIPTEN_KEEPALIVE void set_post_processing_ffi(void *const viewer, bool enabled);
    EMSCRIPTEN_KEEPALIVE void reset_to_rest_pose_ffi(void *const sceneManager, EntityId entityId, void(*callback)());
    EMSCRIPTEN_KEEPALIVE void create_geometry_ffi(void *const viewer, float *vertices, int numVertices, uint16_t *indices, int numIndices, int primitiveType, const char *materialPath, void (*callback)(EntityId));

#ifdef __cplusplus
}
#endif

#endif // _DART_FILAMENT_FFI_API_H
