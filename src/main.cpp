#include <iostream>
#include <string>
#include "../include/imgui-docking/imgui.h"
#include "../include/imgui-docking/imgui_impl_sdl3.h"
#include "../include/imgui-docking/imgui_impl_sdlrenderer3.h"
#include <SDL3/SDL.h>
#define SDL_STBIMAGE_IMPLEMENTATION
#include "../include/SDL_stbimage.h"
#define ENGINE_IMPL_WINDOW
#include "Engine/engine.hpp"


#define WIDTH 1920
#define HEIGHT 1080

int main(int argc, char* argv[]) {

    

    // Init SDL, if it fails, end the program.
    if(Engine::Core::Init() != ENGINE_SUCCESS) {
        return 1;
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

    SDL_Surface* surface = STBIMG_Load("assets/image.png");
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
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui_ImplSDL3_InitForSDLRenderer(window->sdlWindow, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
    ImGuiStyle& style = ImGui::GetStyle();



    

    int w;
    int h;
    float scale;
    float mousePos[2] = {0.0f, 0.0f};



    bool debug = true;
    bool rounded = true;
    float rounding = 5.0f;


    bool running = true;
    int targetFPS = 60;
    int frameDelay = 100 / targetFPS;

    int frameStart;
    float deltaTime;
    int frames = 0;
    int fps;

    while(running) {
        frameDelay = 1000 / targetFPS;
        frameStart = SDL_GetTicks();
        frames++;
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_EVENT_QUIT) {
                running = false;
            }
            ImGui_ImplSDL3_ProcessEvent(&e);
        }



        // SDL_GetWindowSize(window, &w, &h);
        // scale = (float)h/(float)HEIGHT;
        // SDL_SetWindowSize(window, (float)WIDTH * scale, (float)HEIGHT * scale);
        // SDL_SetRenderScale(renderer, scale, scale);

        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(0, NULL, ImGuiDockNodeFlags_PassthruCentralNode);

        ImGui::Begin("Settings");
        ImGui::Text("Project Settings");
        if(ImGui::Button("Toggle Debug Window")) {
            debug = !debug;
        }
        ImGui::Text("ImGui Settings");
        if(ImGui::Button("Toggle Rounding")) {
            rounded = !rounded;
        }
        ImGui::SliderFloat("Rounding amount", &rounding, 5.0f, 15.0f);
        ImGui::End();

        ImGui::Begin("Inspector");
        ImGui::Text("Object Name");
        ImGui::Text("this is my image");
        ImGui::End();

        if(debug) {
            ImGui::Begin("Debug");
            ImGui::DragInt("Target Fps", &targetFPS, 1.0f, 1, 200);
            ImGui::DragInt("Frames Per Second", &fps, ImGuiInputTextFlags_ReadOnly);
            ImGui::InputFloat2("Mouse Position", mousePos);
            ImGui::End();
        }

        ImGui::Render();

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 40, 39, 39, 255);

        SDL_FRect irect{100, 100, (float)image->w*div, (float)image->h*div};
        SDL_RenderTexture(renderer, image, NULL, &irect);





        // render ImGui
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
        // SDL_SetRenderLogicalPresentation(renderer, w, h, SDL_LOGICAL_PRESENTATION_STRETCH);

        deltaTime = SDL_GetTicks() - frameStart; 



        if(rounded) {
            style.TabRounding = rounding;
            style.FrameRounding = rounding;
            style.GrabRounding = rounding;
            style.WindowRounding = rounding;
            style.PopupRounding = rounding;
            style.ChildRounding = rounding;
            style.ScrollbarRounding = rounding;
        } else {
            style.TabRounding = 0.0f;
            style.FrameRounding = 0.0f;
            style.GrabRounding = 0.0f;
            style.WindowRounding = 0.0f;
            style.PopupRounding = 0.0f; 
            style.ChildRounding = 0.0f;
            style.ScrollbarRounding = 0.0f;
        }



        SDL_GetMouseState(&mousePos[0], &mousePos[1]);    
        
        if(frameDelay > deltaTime) {
            if(frames > targetFPS) {
                fps = frames - 1;
                frames = 0;
            }
            SDL_Delay(frameDelay - deltaTime);
        }
    }

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    window->~Window();
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}

