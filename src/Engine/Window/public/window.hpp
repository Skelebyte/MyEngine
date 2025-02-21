#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <SDL3/SDL.h>

#define ENGINE_WINDOW_MAXIMIZED SDL_WINDOW_MAXIMIZED
#define ENGINE_WINDOW_RESIZEABLE SDL_WINDOW_RESIZABLE

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