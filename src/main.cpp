#include <iostream>
#include <string>
#include "Engine/external/include/imgui-docking/imgui.h"
#include "Engine/external/include/imgui-docking/imgui_impl_sdl3.h"
#include "Engine/external/include/imgui-docking/imgui_impl_sdlrenderer3.h"
#include <SDL3/SDL.h>
#include "Engine/external/include/SDL_stbimage.h"
#define ENGINE_IMPL_WINDOW
#define ENGINE_IMPL_DEVGUI
#include "Engine/Engine.hpp"




void test() {
    // whatever
}

int main(int argc, char* argv[]) {

    

    // Init SDL, if it fails, end the program.
    if(Engine::Core::Init() != ENGINE_SUCCESS) {
        return Engine::Debug::GetError();
    }

    // Create window, if it fails, quit SDL and end the program.
    Engine::Window* window = new Engine::Window("Engine", 1280, 720);
    if(window->Failed()) {
        return 2;
    }

    // Create renderer, if it fails, quit SDL, close the window, and end the program.
    SDL_Renderer* renderer = SDL_CreateRenderer(window->sdlWindow, NULL);
    if(!renderer) {
        std::cout<<"Failed to create renderer!"<<std::endl;
        SDL_DestroyWindow(window->sdlWindow);
        SDL_Quit();
        return 3;
    }

    float div = 0.25f;

    SDL_Surface* surface = STBIMG_Load("assets/SkelebyteSkull_NoBackground.png");
    SDL_Texture* image = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_BGRA8888, SDL_TEXTUREACCESS_TARGET, (float)image->w*div, (float)image->h*div);
    SDL_SetRenderTarget(renderer, texture);
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_FRect rect = {0.0f, 0.0f, (float)image->w*div, (float)image->h*div};
    SDL_RenderTexture(renderer, image, NULL, &rect);
    SDL_SetRenderTarget(renderer, NULL);

    // Create ImGui
    Engine::DevGui* devGui = new Engine::DevGui(window, renderer);
    ImGuiStyle& style = devGui->GetStyle();

    devGui->draw = test;


    int w;
    int h;
    float scale;
    float mousePos[2] = {0.0f, 0.0f};






    bool running = true;


    while(running) {
        Engine::Core::BeginFrame();
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_EVENT_QUIT) {
                running = false;
            }
            ImGui_ImplSDL3_ProcessEvent(&e);
        }





        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(0, NULL, ImGuiDockNodeFlags_PassthruCentralNode);

        devGui->EngineGUI(style, Engine::Core::FPS());


        ImGui::Render();

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 40, 39, 39, 255);

        SDL_FRect irect{100, 100, (float)image->w*div, (float)image->h*div};
        SDL_RenderTexture(renderer, image, NULL, &irect);





        // render ImGui
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

        SDL_RenderPresent(renderer);
        //SDL_SetRenderLogicalPresentation(renderer, w, h, SDL_LOGICAL_PRESENTATION_STRETCH);
        
        SDL_GetMouseState(&mousePos[0], &mousePos[1]);  


        Engine::Core::EndFrame();
    }


   
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}

