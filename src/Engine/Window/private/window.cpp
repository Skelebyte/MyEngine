#include "../public/window.hpp"

Engine::Window::Window(const char* title, int w, int h, int flags) {
    if(flags != 0) {
        sdlWindow = SDL_CreateWindow(title, w, h, SDL_EVENT_WINDOW_SHOWN | flags);
    } else {
        sdlWindow = SDL_CreateWindow(title, w, h, SDL_EVENT_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);
    }
    if(!sdlWindow) {
        std::cout<<"Failed to create window!"<<std::endl;
        failed = true;
        SDL_Quit();
    }
    if(failed) return;
    SDL_SetWindowMinimumSize(sdlWindow, 300, 300);

}

Engine::Window::~Window() {
    SDL_DestroyWindow(sdlWindow);
}

bool Engine::Window::Failed() {
    return failed;
}