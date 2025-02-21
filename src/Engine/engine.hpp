#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <iostream>
#ifdef ENGINE_IMPL_WINDOW
#include "Window/public/window.hpp"
#endif // ENGINE_IMPL_WINDOW

#include <SDL3/SDL.h>

#define ENGINE_SUCCESS 0
#define ENGINE_SDL_INIT_FAILED 1

namespace Engine {
    class Core {
        public:
        static int Init() {
            if(SDL_Init(SDL_INIT_VIDEO) < 0) {
                std::cout<<"SDL failed to init!"<<std::endl;
                return ENGINE_SDL_INIT_FAILED;
            } else {
                return ENGINE_SUCCESS;
            }
        }
    };
}

#endif // ENGINE_HPP