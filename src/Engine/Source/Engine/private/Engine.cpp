#include "../../../Engine.hpp"

int Engine::Core::targetFPS = 60;
float Engine::Core::frameDelay = 0;
int Engine::Core::frames = 0;
int Engine::Core::fps = 0;
void (*Engine::Core::update)() = nullptr;
bool Engine::Core::frameBegun = false;

int Engine::Core::Init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        Engine::Debug::ThrowError("Failed to initialize SDL3!", GET_MACRO(ENGINE_SDL_INIT_FAILED));
        return ENGINE_SDL_INIT_FAILED;
    } else {
        targetFPS = 60;
        return ENGINE_SUCCESS;
    }
    
}

int Engine::Core::BeginFrame(int runWithUpdate) {
    if(frameBegun == true) {
        Engine::Debug::ThrowError(
            "Engine::Core::EndFrame is not called! Please call Engine::Core::EndFrame at the end of the game loop", 
            GET_MACRO(ENGINE_ENDFRAME_NOT_CALLED)
        );

        return ENGINE_BEGINFRAME_NOT_CALLED;
    }
    Engine::Time::BeginTime();
    frameDelay = 1000 / targetFPS;
    frames++;

    if(runWithUpdate == ENGINE_RUN_BEGINFRAME_WITH_UPDATE) {
        update();
    }
    frameBegun = true;
    return ENGINE_SUCCESS;
}

int Engine::Core::EndFrame() {
    if(frameBegun == false) {
        Engine::Debug::ThrowError(
            "Engine::Core::BeginFrame is not called! Please call Engine::Core::BeginFrame at the end of the game loop", 
            GET_MACRO(ENGINE_BEGINFRAME_NOT_CALLED)
        );
        
        return ENGINE_BEGINFRAME_NOT_CALLED;
    }
    Engine::Time::EndTime();
    if(frameDelay > Engine::Time::DeltaTime()) {
        if(frames > targetFPS) {
            fps = frames - 1;
            frames = 0;
        }
        SDL_Delay(frameDelay - Engine::Time::DeltaTime());
    }
    frameBegun = false;
    return ENGINE_SUCCESS;
}

int Engine::Core::FPS() {
    return fps;
}