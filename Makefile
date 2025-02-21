PROJECT_NAME = project
BUILD_DIR = build

# INCLUDE_DIRS = -Iinclude/imgui

LIBS = -lSDL3

ENGINE_SRC = $(wildcard src/Engine/Window/private/*.cpp)
SRC = $(wildcard src/*.cpp) $(wildcard imgui-docking/*.cpp)

default:
	g++ $(SRC) $(ENGINE_SRC) -o $(BUILD_DIR)/$(PROJECT_NAME) $(LIBS)

run:
	./$(BUILD_DIR)/$(PROJECT_NAME)
	