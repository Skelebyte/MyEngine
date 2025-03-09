PROJECT_NAME = project
BUILD_DIR = build

FLAGS = -lSDL3 -lpthread -lm -ldl 

ENGINE_SRC = src/Engine/Engine.cpp $(wildcard src/Engine/Source/*/private/*.cpp)
SRC = $(wildcard src/*.cpp) $(wildcard  src/Engine/external/imgui-docking/*.cpp)

default:
	g++ $(SRC) $(ENGINE_SRC) -o $(BUILD_DIR)/$(PROJECT_NAME) $(FLAGS) 

run:
	./$(BUILD_DIR)/$(PROJECT_NAME)
	