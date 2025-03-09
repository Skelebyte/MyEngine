#ifndef DEVGUI_HPP
#define DEVGUI_HPP

#include "../../Window/public/Window.hpp"
#include "../../../external/include/imgui-docking/imgui.h"
#include "../../../external/include/imgui-docking/imgui_impl_sdl3.h"
#include "../../../external/include/imgui-docking/imgui_impl_sdlrenderer3.h"

#define DEVGUI_SUCCESS 0
#define DEVGUI_NOT_INITIALIZED 2

namespace Engine {

    struct EngineGUISettings {
        bool showDebug = true;
        bool rounded = true;
        float rounding = 5.0f;
    };

    class DevGui {
        public:
        DevGui(Engine::Window* window, SDL_Renderer* renderer, int flags = ImGuiConfigFlags_DockingEnable);
        ~DevGui();

        ImGuiStyle& GetStyle();

        void EngineGUI(ImGuiStyle& style, int fps);

        void (*draw)();
        void EndDraw();

        public:
        EngineGUISettings engineGUISettings;
        
        private:
        bool initialized;
    };

    class Element {
        public:
        Element(const char* title);

    };

    class TextElement : Element {
        public:
        
    };

}

#endif // DEVGUI_HPP