#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>

#include "Source/Debug/public/Debug.hpp"

#include "Source/MacroTools.hpp"
#ifdef ENGINE_IMPL_WINDOW
#include "Source/Window/public/Window.hpp"
#endif // ENGINE_IMPL_WINDOW
#ifdef ENGINE_IMPL_DEVGUI
#include "Source/DevGUI/public/DevGUI.hpp"
#endif // ENGINE_IMPL_DEVGUI

#include "Source/Time/public/Time.hpp"

#include <SDL3/SDL.h>

// Errors
#define ENGINE_SUCCESS 0
#define ENGINE_SDL_INIT_FAILED 1
#define ENGINE_BEGINFRAME_NOT_CALLED 2
#define ENGINE_ENDFRAME_NOT_CALLED 3

// Flags
#define NO_FLAGS 0
#define ENGINE_RUN_BEGINFRAME_WITH_UPDATE 1

// Defaults
#define WIDTH 1920
#define HEIGHT 1080


namespace Engine {
    class Core {


        public:
        static int Init();
        static int BeginFrame(int runWithUpdate = 0);
        static int EndFrame();
        static int FPS();

        static void (*update)();

        public:
        static int targetFPS;

        private:
        static float frameDelay;
        static int frames;
        static int fps;

        static bool frameBegun;

    };
}

#endif // ENGINE_HPP