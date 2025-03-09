#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <SDL3/SDL.h>

#include "../../Debug/public/Debug.hpp"

#define WINDOW_MAXIMIZED SDL_WINDOW_MAXIMIZED
#define WINDOW_RESIZEABLE SDL_WINDOW_RESIZABLE

#define WINDOW_SUCCESS 0
#define WINDOW_FAILURE 1
#define WINDOW_FAILED_TO_CREATE_WINDOW 2

namespace Engine {
    class Window {
        public:
        Window(const char* title, int w, int h, int flags = 0);
        ~Window();

        bool Failed();

        public:
        SDL_Window* sdlWindow;

        private:
        bool failed;
    };
}

#endif