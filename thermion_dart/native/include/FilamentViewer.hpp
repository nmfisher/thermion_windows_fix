#pragma once

#include <filament/Camera.h>
#include <filament/Frustum.h>
#include <filament/ColorGrading.h>
#include <filament/Engine.h>
#include <filament/IndexBuffer.h>
#include <filament/RenderableManager.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>
#include <filament/Skybox.h>
#include <filament/TransformManager.h>
#include <filament/VertexBuffer.h>
#include <filament/View.h>
#include <filament/LightManager.h>

#include <gltfio/AssetLoader.h>
#include <gltfio/FilamentAsset.h>
#include <gltfio/ResourceLoader.h>

#include <camutils/Manipulator.h>

#include <utils/NameComponentManager.h>

#include <math/vec3.h>
#include <math/vec4.h>
#include <math/mat3.h>
#include <math/norm.h>

#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

#include "ResourceBuffer.hpp"
#include "SceneManager.hpp"
#include "ThreadPool.hpp"

namespace thermion_filament
{

    typedef std::chrono::time_point<std::chrono::high_resolution_clock> time_point_t;

    using namespace std::chrono;
    using namespace filament;
    using namespace filament::math;
    using namespace gltfio;
    using namespace camutils;

    enum ToneMapping
    {
        ACES,
        FILMIC,
        LINEAR
    };

    class FilamentViewer
    {

        typedef int32_t EntityId;

    public:
        FilamentViewer(const void *context, const ResourceLoaderWrapperImpl *const resourceLoaderWrapper, void *const platform = nullptr, const char *uberArchivePath = nullptr);
        ~FilamentViewer();

        void setToneMapping(ToneMapping toneMapping);
        void setBloom(float strength);
        void loadSkybox(const char *const skyboxUri);
        void removeSkybox();

        void loadIbl(const char *const iblUri, float intensity);
        void removeIbl();
        void rotateIbl(const math::mat3f &matrix);

        void removeEntity(EntityId asset);
        void clearEntities();

        void updateViewportAndCameraProjection(int height, int width, float scaleFactor);
        void render(
            uint64_t frameTimeInNanos,
            void *pixelBuffer,
            void (*callback)(void *buf, size_t size, void *data),
            void *data);
        void setFrameInterval(float interval);

        bool setCamera(EntityId asset, const char *nodeName);
        void setMainCamera();
        EntityId getMainCamera();
        void setCameraFov(double fovDegrees, double aspect);

        void createSwapChain(const void *surface, uint32_t width, uint32_t height);
        void destroySwapChain();

        void createRenderTarget(intptr_t textureId, uint32_t width, uint32_t height);

        Renderer *getRenderer();

        void setBackgroundColor(const float r, const float g, const float b, const float a);
        void setBackgroundImage(const char *resourcePath, bool fillHeight);
        void clearBackgroundImage();
        void setBackgroundImagePosition(float x, float y, bool clamp);

        // Camera methods
        void moveCameraToAsset(EntityId entityId);
        void setViewFrustumCulling(bool enabled);
        void setCameraExposure(float aperture, float shutterSpeed, float sensitivity);
        void setCameraPosition(float x, float y, float z);
        void setCameraRotation(float w, float x, float y, float z);
        const math::mat4 getCameraModelMatrix();
        const math::mat4 getCameraViewMatrix();
        const math::mat4 getCameraProjectionMatrix();
        const math::mat4 getCameraCullingProjectionMatrix();
        const filament::Frustum getCameraFrustum();
        void setCameraModelMatrix(const float *const matrix);
        void setCameraProjectionMatrix(const double *const matrix, double near, double far);
        void setCameraFocalLength(float focalLength);
        void setCameraCulling(double near, double far);
        double getCameraCullingNear();
        double getCameraCullingFar();
        void setCameraFocusDistance(float focusDistance);
        void setCameraManipulatorOptions(filament::camutils::Mode mode, double orbitSpeedX, double orbitSpeedY, double zoomSpeed);
        void grabBegin(float x, float y, bool pan);
        void grabUpdate(float x, float y);
        void grabEnd();
        void scrollBegin();
        void scrollUpdate(float x, float y, float delta);
        void scrollEnd();
        void pick(uint32_t x, uint32_t y, void (*callback)(EntityId entityId, int x, int y));

        EntityId addLight(
            LightManager::Type t, 
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
        void removeLight(EntityId entityId);
        void clearLights();
        void setPostProcessing(bool enabled);

        void setRecording(bool recording);
        void setRecordingOutputDirectory(const char *path);

        void setAntiAliasing(bool msaaEnabled, bool fxaaEnabled, bool taaEnabled);
        void setDepthOfField();

        EntityId createGeometry(float *vertices, uint32_t numVertices, uint16_t *indices, uint32_t numIndices, filament::RenderableManager::PrimitiveType primitiveType = RenderableManager::PrimitiveType::TRIANGLES, const char *materialPath = nullptr);

        SceneManager *const getSceneManager()
        {
            return (SceneManager *const)_sceneManager;
        }

    private:
        const ResourceLoaderWrapperImpl *const _resourceLoaderWrapper;
        void* _context = nullptr;
        Scene *_scene = nullptr;
        View *_view = nullptr;
        Engine *_engine = nullptr;
        thermion_filament::ThreadPool *_tp = nullptr;
        Renderer *_renderer = nullptr;
        RenderTarget *_rt = nullptr;
        Texture *_rtColor = nullptr;
        Texture *_rtDepth = nullptr;

        SwapChain *_swapChain = nullptr;

        SceneManager *_sceneManager = nullptr;

        std::mutex mtx; // mutex to ensure thread safety when removing assets

        std::vector<utils::Entity> _lights;
        Texture *_skyboxTexture = nullptr;
        Skybox *_skybox = nullptr;
        Texture *_iblTexture = nullptr;
        IndirectLight *_indirectLight = nullptr;
        bool _recomputeAabb = false;
        bool _actualSize = false;

        float _frameInterval = 1000.0 / 60.0;

        // Camera properties
        Camera *_mainCamera = nullptr; // the default camera added to every scene. If you want the *active* camera, access via View.
        float _cameraFocalLength = 28.0f;
        float _cameraFocusDistance = 0.0f;
        Manipulator<double> *_manipulator = nullptr;
        filament::camutils::Mode _manipulatorMode = filament::camutils::Mode::ORBIT;
        double _orbitSpeedX = 0.01;
        double _orbitSpeedY = 0.01;
        double _zoomSpeed = 0.01;
        math::mat4f _cameraPosition;
        math::mat4f _cameraRotation;
        void _createManipulator();
        double _near = 0.05;
        double _far = 1000.0;

        ColorGrading *colorGrading = nullptr;

        // background image properties
        uint32_t _imageHeight = 0;
        uint32_t _imageWidth = 0;
        mat4f _imageScale;
        Texture *_imageTexture = nullptr;
        Texture *_dummyImageTexture = nullptr;
        utils::Entity _imageEntity;
        VertexBuffer *_imageVb = nullptr;
        IndexBuffer *_imageIb = nullptr;
        Material *_imageMaterial = nullptr;
        TextureSampler _imageSampler;
        void loadKtx2Texture(std::string path, ResourceBuffer data);
        void loadKtxTexture(std::string path, ResourceBuffer data);
        void loadPngTexture(std::string path, ResourceBuffer data);
        void loadTextureFromPath(std::string path);
        void savePng(void *data, size_t size, int frameNumber);

        time_point_t _recordingStartTime = std::chrono::high_resolution_clock::now();
        time_point_t _fpsCounterStartTime = std::chrono::high_resolution_clock::now();

        bool _recording = false;
        std::string _recordingOutputDirectory = std::string("/tmp");
        std::mutex _recordingMutex;
        double _cumulativeAnimationUpdateTime = 0;
        int _frameCount = 0;
        int _skippedFrames = 0;
    };

    struct FrameCallbackData
    {
        FilamentViewer *viewer;
        uint32_t frameNumber;
    };

}
