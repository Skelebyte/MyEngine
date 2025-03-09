#include "../public/DevGUI.hpp"

/**
 * Contructor for the ImGui library.
 * @param window Reference to the current window.
 * @param renderer Reference to the `SDL_Renderer` attached to the `window->sdlWindow`.
 * @param flags Additional optional flags to the ImGui set up (By default, the `ImGuiConfigFlags_DockingEnable` flag is passed, if you don't want ImGui to be dockable, pass 0 or `NO_FLAGS`).
 */
Engine::DevGui::DevGui(Engine::Window* window, SDL_Renderer* renderer, int flags) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::GetIO().ConfigFlags |= flags;
    ImGui_ImplSDL3_InitForSDLRenderer(window->sdlWindow, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    initialized = true;
}

Engine::DevGui::~DevGui() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

ImGuiStyle& Engine::DevGui::GetStyle() {

    ImGuiStyle& style = ImGui::GetStyle();
    return style;
}

void Engine::DevGui::EndDraw() {
    
}

void Engine::DevGui::EngineGUI(ImGuiStyle& style, int fps) {
    ImGui::Begin("Settings");
    ImGui::Text("Project Settings");
    if(ImGui::Button("Toggle Debug Window")) {
        engineGUISettings.showDebug = !engineGUISettings.showDebug;
    }
    ImGui::Text("ImGui Settings");
    if(ImGui::Button("Toggle Rounding")) {
        engineGUISettings.rounded = !engineGUISettings.rounded;
    }
    ImGui::SliderFloat("Rounding amount", &engineGUISettings.rounding, 5.0f, 15.0f);
    ImGui::End();

    ImGui::Begin("Inspector");
    ImGui::Text("Object Name");
    ImGui::Text("this is my image");
    ImGui::End();

    if(engineGUISettings.showDebug) {
        ImGui::Begin("Debug");
        ImGui::DragInt("Frames Per Second", &fps, ImGuiInputTextFlags_ReadOnly);
        ImGui::End();
    }

    if(engineGUISettings.rounded) {
        style.TabRounding = engineGUISettings.rounding;
        style.FrameRounding = engineGUISettings.rounding;
        style.GrabRounding = engineGUISettings.rounding;
        style.WindowRounding = engineGUISettings.rounding;
        style.PopupRounding = engineGUISettings.rounding;
        style.ChildRounding = engineGUISettings.rounding;
        style.ScrollbarRounding = engineGUISettings.rounding;
    } else {
        style.TabRounding = 0.0f;
        style.FrameRounding = 0.0f;
        style.GrabRounding = 0.0f;
        style.WindowRounding = 0.0f;
        style.PopupRounding = 0.0f; 
        style.ChildRounding = 0.0f;
        style.ScrollbarRounding = 0.0f;
    }
}