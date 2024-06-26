#ifndef _FLUTTER_FILAMENT_API_H
#define _FLUTTER_FILAMENT_API_H

#ifdef _WIN32
#ifdef IS_DLL
#define EMSCRIPTEN_KEEPALIVE __declspec(dllimport)
#else
#define EMSCRIPTEN_KEEPALIVE __declspec(dllexport)
#endif
#else
#ifndef EMSCRIPTEN_KEEPALIVE
#define EMSCRIPTEN_KEEPALIVE __attribute__((visibility("default")))
#endif
#endif

// we copy the LLVM <stdbool.h> here rather than including,
// because on Windows it's difficult to pin the exact location which confuses dart ffigen

#ifndef __STDBOOL_H
#define __STDBOOL_H

#define __bool_true_false_are_defined 1

#if defined(__STDC_VERSION__) && __STDC_VERSION__ > 201710L
/* FIXME: We should be issuing a deprecation warning here, but cannot yet due
 * to system headers which include this header file unconditionally.
 */
#elif !defined(__cplusplus)
#define bool _Bool
#define true 1
#define false 0
#elif defined(__GNUC__) && !defined(__STRICT_ANSI__)
/* Define _Bool as a GNU extension. */
#define _Bool bool
#if defined(__cplusplus) && __cplusplus < 201103L
/* For C++98, define bool, false, true as a GNU extension. */
#define bool bool
#define false false
#define true true
#endif
#endif

#endif /* __STDBOOL_H */

#if defined(__APPLE__) || defined(__EMSCRIPTEN__)
#include <stddef.h>
#endif

#include "ResourceBuffer.hpp"

typedef int32_t EntityId;
typedef int32_t _ManipulatorMode;

#ifdef __cplusplus
extern "C"
{
#endif

	EMSCRIPTEN_KEEPALIVE const void *create_filament_viewer(const void *const context, const void *const loader, void *const platform, const char *uberArchivePath);
	EMSCRIPTEN_KEEPALIVE void destroy_filament_viewer(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE void *get_scene_manager(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE void create_render_target(const void *const viewer, intptr_t texture, uint32_t width, uint32_t height);
	EMSCRIPTEN_KEEPALIVE void clear_background_image(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE void set_background_image(const void *const viewer, const char *path, bool fillHeight);
	EMSCRIPTEN_KEEPALIVE void set_background_image_position(const void *const viewer, float x, float y, bool clamp);
	EMSCRIPTEN_KEEPALIVE void set_background_color(const void *const viewer, const float r, const float g, const float b, const float a);
	EMSCRIPTEN_KEEPALIVE void set_tone_mapping(const void *const viewer, int toneMapping);
	EMSCRIPTEN_KEEPALIVE void set_bloom(const void *const viewer, float strength);
	EMSCRIPTEN_KEEPALIVE void load_skybox(const void *const viewer, const char *skyboxPath);
	EMSCRIPTEN_KEEPALIVE void load_ibl(const void *const viewer, const char *iblPath, float intensity);
	EMSCRIPTEN_KEEPALIVE void rotate_ibl(const void *const viewer, float *rotationMatrix);
	EMSCRIPTEN_KEEPALIVE void remove_skybox(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE void remove_ibl(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE EntityId add_light(
		const void *const viewer, 
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
		bool shadows);
	EMSCRIPTEN_KEEPALIVE void remove_light(const void *const viewer, EntityId entityId);
	EMSCRIPTEN_KEEPALIVE void clear_lights(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE EntityId load_glb(void *sceneManager, const char *assetPath, int numInstances);
	EMSCRIPTEN_KEEPALIVE EntityId load_glb_from_buffer(void *sceneManager, const void *const data, size_t length);
	EMSCRIPTEN_KEEPALIVE EntityId load_gltf(void *sceneManager, const char *assetPath, const char *relativePath);
	EMSCRIPTEN_KEEPALIVE EntityId create_instance(void *sceneManager, EntityId id);
	EMSCRIPTEN_KEEPALIVE int get_instance_count(void *sceneManager, EntityId entityId);
	EMSCRIPTEN_KEEPALIVE void get_instances(void *sceneManager, EntityId entityId, EntityId *out);
	EMSCRIPTEN_KEEPALIVE void set_main_camera(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE EntityId get_main_camera(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE bool set_camera(const void *const viewer, EntityId entity, const char *nodeName);
	EMSCRIPTEN_KEEPALIVE void set_view_frustum_culling(const void *const viewer, bool enabled);
	EMSCRIPTEN_KEEPALIVE void render(
		const void *const viewer,
		uint64_t frameTimeInNanos,
		void *pixelBuffer,
		void (*callback)(void *buf, size_t size, void *data),
		void *data);
	EMSCRIPTEN_KEEPALIVE void create_swap_chain(const void *const viewer, const void *const window, uint32_t width, uint32_t height);
	EMSCRIPTEN_KEEPALIVE void destroy_swap_chain(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE void set_frame_interval(const void *const viewer, float interval);
	EMSCRIPTEN_KEEPALIVE void update_viewport_and_camera_projection(const void *const viewer, uint32_t width, uint32_t height, float scaleFactor);
	EMSCRIPTEN_KEEPALIVE void scroll_begin(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE void scroll_update(const void *const viewer, float x, float y, float z);
	EMSCRIPTEN_KEEPALIVE void scroll_end(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE void grab_begin(const void *const viewer, float x, float y, bool pan);
	EMSCRIPTEN_KEEPALIVE void grab_update(const void *const viewer, float x, float y);
	EMSCRIPTEN_KEEPALIVE void grab_end(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE void apply_weights(
		void *sceneManager,
		EntityId entity,
		const char *const entityName,
		float *const weights,
		int count);
	EMSCRIPTEN_KEEPALIVE bool set_morph_target_weights(
		void *sceneManager,
		EntityId entity,
		const float *const morphData,
		int numWeights);
	EMSCRIPTEN_KEEPALIVE bool set_morph_animation(
		void *sceneManager,
		EntityId entity,
		const float *const morphData,
		const int *const morphIndices,
		int numMorphTargets,
		int numFrames,
		float frameLengthInMs);

	EMSCRIPTEN_KEEPALIVE void reset_to_rest_pose(
		void *sceneManager,
		EntityId asset);
	EMSCRIPTEN_KEEPALIVE void add_bone_animation(
		void *sceneManager,
		EntityId entity,
		int skinIndex,
		int boneIndex,
		const float *const frameData,
		int numFrames,
		float frameLengthInMs,
		float fadeOutInSecs,
		float fadeInInSecs,
		float maxDelta);
	EMSCRIPTEN_KEEPALIVE void get_local_transform(void *sceneManager,
        EntityId entityId, float* const);
	EMSCRIPTEN_KEEPALIVE void get_rest_local_transforms(void *sceneManager,
        EntityId entityId, int skinIndex, float* const out, int numBones);
	EMSCRIPTEN_KEEPALIVE void get_world_transform(void *sceneManager,
        EntityId entityId, float* const);
	EMSCRIPTEN_KEEPALIVE void get_inverse_bind_matrix(void *sceneManager,
        EntityId entityId, int skinIndex, int boneIndex, float* const);
	EMSCRIPTEN_KEEPALIVE bool set_bone_transform(
		void *sceneManager,
		EntityId entity,
		int skinIndex,
		int boneIndex,
		const float *const transform);
	EMSCRIPTEN_KEEPALIVE void play_animation(void *sceneManager, EntityId entity, int index, bool loop, bool reverse, bool replaceActive, float crossfade);
	EMSCRIPTEN_KEEPALIVE void set_animation_frame(void *sceneManager, EntityId entity, int animationIndex, int animationFrame);
	EMSCRIPTEN_KEEPALIVE void stop_animation(void *sceneManager, EntityId entity, int index);
	EMSCRIPTEN_KEEPALIVE int get_animation_count(void *sceneManager, EntityId asset);
	EMSCRIPTEN_KEEPALIVE void get_animation_name(void *sceneManager, EntityId entity, char *const outPtr, int index);
	EMSCRIPTEN_KEEPALIVE float get_animation_duration(void *sceneManager, EntityId entity, int index);
	EMSCRIPTEN_KEEPALIVE int get_bone_count(void *sceneManager, EntityId assetEntity, int skinIndex);
	EMSCRIPTEN_KEEPALIVE void get_bone_names(void *sceneManager, EntityId assetEntity, const char** outPtr, int skinIndex);
	EMSCRIPTEN_KEEPALIVE EntityId get_bone(void *sceneManager,
        EntityId entityId,
        int skinIndex,
        int boneIndex);
	EMSCRIPTEN_KEEPALIVE bool set_transform(void* sceneManager, EntityId entityId, const float* const transform);
	EMSCRIPTEN_KEEPALIVE bool update_bone_matrices(void* sceneManager, EntityId entityId);
	EMSCRIPTEN_KEEPALIVE void get_morph_target_name(void *sceneManager, EntityId assetEntity, EntityId childEntity, char *const outPtr, int index);
	EMSCRIPTEN_KEEPALIVE int get_morph_target_name_count(void *sceneManager, EntityId assetEntity, EntityId childEntity);
	EMSCRIPTEN_KEEPALIVE void remove_entity(const void *const viewer, EntityId asset);
	EMSCRIPTEN_KEEPALIVE void clear_entities(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE bool set_material_color(void *sceneManager, EntityId entity, const char *meshName, int materialIndex, const float r, const float g, const float b, const float a);
	EMSCRIPTEN_KEEPALIVE void transform_to_unit_cube(void *sceneManager, EntityId asset);
	EMSCRIPTEN_KEEPALIVE void queue_position_update(void *sceneManager, EntityId entity, float x, float y, float z, bool relative);
	EMSCRIPTEN_KEEPALIVE void queue_rotation_update(void *sceneManager, EntityId entity, float rads, float x, float y, float z, float w, bool relative);
	EMSCRIPTEN_KEEPALIVE void set_position(void *sceneManager, EntityId entity, float x, float y, float z);
	EMSCRIPTEN_KEEPALIVE void set_rotation(void *sceneManager, EntityId entity, float rads, float x, float y, float z, float w);
	EMSCRIPTEN_KEEPALIVE void set_scale(void *sceneManager, EntityId entity, float scale);

	// Camera methods
	EMSCRIPTEN_KEEPALIVE void move_camera_to_asset(const void *const viewer, EntityId asset);
	EMSCRIPTEN_KEEPALIVE void set_view_frustum_culling(const void *const viewer, bool enabled);
	EMSCRIPTEN_KEEPALIVE void set_camera_exposure(const void *const viewer, float aperture, float shutterSpeed, float sensitivity);
	EMSCRIPTEN_KEEPALIVE void set_camera_position(const void *const viewer, float x, float y, float z);
	EMSCRIPTEN_KEEPALIVE void get_camera_position(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE void set_camera_rotation(const void *const viewer, float w, float x, float y, float z);
	EMSCRIPTEN_KEEPALIVE void set_camera_model_matrix(const void *const viewer, const float *const matrix);
	EMSCRIPTEN_KEEPALIVE const double *const get_camera_model_matrix(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE const double *const get_camera_view_matrix(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE const double *const get_camera_projection_matrix(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE void set_camera_projection_matrix(const void *const viewer, const double *const matrix, double near, double far);
	EMSCRIPTEN_KEEPALIVE void set_camera_culling(const void *const viewer, double near, double far);
	EMSCRIPTEN_KEEPALIVE double get_camera_culling_near(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE double get_camera_culling_far(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE const double *const get_camera_culling_projection_matrix(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE const double *const get_camera_frustum(const void *const viewer);
	EMSCRIPTEN_KEEPALIVE void set_camera_fov(const void *const viewer, float fovInDegrees, float aspect);
	EMSCRIPTEN_KEEPALIVE void set_camera_focal_length(const void *const viewer, float focalLength);
	EMSCRIPTEN_KEEPALIVE void set_camera_focus_distance(const void *const viewer, float focusDistance);
	EMSCRIPTEN_KEEPALIVE void set_camera_manipulator_options(const void *const viewer, _ManipulatorMode mode, double orbitSpeedX, double orbitSpeedY, double zoomSpeed);

	EMSCRIPTEN_KEEPALIVE int hide_mesh(void *sceneManager, EntityId entity, const char *meshName);
	EMSCRIPTEN_KEEPALIVE int reveal_mesh(void *sceneManager, EntityId entity, const char *meshName);
	EMSCRIPTEN_KEEPALIVE void set_post_processing(void *const viewer, bool enabled);
	EMSCRIPTEN_KEEPALIVE void set_antialiasing(void *const viewer, bool msaa, bool fxaa, bool taa);
	EMSCRIPTEN_KEEPALIVE void filament_pick(void *const viewer, int x, int y, void (*callback)(EntityId entityId, int x, int y));
	EMSCRIPTEN_KEEPALIVE const char *get_name_for_entity(void *const sceneManager, const EntityId entityId);
	EMSCRIPTEN_KEEPALIVE EntityId find_child_entity_by_name(void *const sceneManager, const EntityId parent, const char *name);
	EMSCRIPTEN_KEEPALIVE int get_entity_count(void *const sceneManager, const EntityId target, bool renderableOnly);
	EMSCRIPTEN_KEEPALIVE void get_entities(void *const sceneManager, const EntityId target, bool renderableOnly, EntityId *out);
	EMSCRIPTEN_KEEPALIVE const char *get_entity_name_at(void *const sceneManager, const EntityId target, int index, bool renderableOnly);
	EMSCRIPTEN_KEEPALIVE void set_recording(void *const viewer, bool recording);
	EMSCRIPTEN_KEEPALIVE void set_recording_output_directory(void *const viewer, const char *outputDirectory);
	EMSCRIPTEN_KEEPALIVE void ios_dummy();
	EMSCRIPTEN_KEEPALIVE void thermion_flutter_free(void *ptr);
	EMSCRIPTEN_KEEPALIVE void add_collision_component(void *const sceneManager, EntityId entityId, void (*callback)(const EntityId entityId1, const EntityId entityId2), bool affectsCollidingTransform);
	EMSCRIPTEN_KEEPALIVE void remove_collision_component(void *const sceneManager, EntityId entityId);
	EMSCRIPTEN_KEEPALIVE bool add_animation_component(void *const sceneManager, EntityId entityId);
	EMSCRIPTEN_KEEPALIVE void remove_animation_component(void *const sceneManager, EntityId entityId);

	EMSCRIPTEN_KEEPALIVE EntityId create_geometry(void *const viewer, float *vertices, int numVertices, uint16_t *indices, int numIndices, int primitiveType, const char *materialPath);
	EMSCRIPTEN_KEEPALIVE EntityId get_parent(void *const sceneManager, EntityId child);
	EMSCRIPTEN_KEEPALIVE void set_parent(void *const sceneManager, EntityId child, EntityId parent);
	EMSCRIPTEN_KEEPALIVE void test_collisions(void *const sceneManager, EntityId entity);
	EMSCRIPTEN_KEEPALIVE void set_priority(void *const sceneManager, EntityId entityId, int priority);
	EMSCRIPTEN_KEEPALIVE void get_gizmo(void *const sceneManager, EntityId *out);

#ifdef __cplusplus
}
#endif
#endif
