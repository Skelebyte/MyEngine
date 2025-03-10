PROJECT_NAME = project
BUILD_DIR = build

ENGINE_DIR = src/Engine

LINUX_FLAGS = -lSDL3 -lpthread -lm -ldl 
WIN_FLAGS = -I$(ENGINE_DIR)/external/include/SDL3 -L$(ENGINE_DIR)/external/lib -lSDL3

ENGINE_SRC = $(wildcard $(ENGINE_DIR)/Source/*/private/*.cpp)
SRC = $(wildcard src/*.cpp) $(wildcard  $(ENGINE_DIR)/external/imgui-docking/*.cpp)

setup:
ifeq ($(OS), Windows_NT)
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	if not exist $(BUILD_DIR)\win mkdir $(BUILD_DIR)\win
	if not exist $(BUILD_DIR)\linux mkdir $(BUILD_DIR)\linux
else
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/win
	mkdir -p $(BUILD_DIR)/linux
endif

build_linux: setup
ifeq ($(OS), Windows_NT)
	wsl
	g++ $(SRC) $(ENGINE_SRC) -o $(BUILD_DIR)/linux/$(PROJECT_NAME) $(LINUX_FLAGS)
	exit
else 
	g++ $(SRC) $(ENGINE_SRC) -o $(BUILD_DIR)/linux/$(PROJECT_NAME) $(LINUX_FLAGS)
endif

build_win: setup
ifeq ($(OS), Linux)
	x86_64-w64-mingw32-g++ $(SRC) $(ENGINE_SRC) -o $(BUILD_DIR)/win/$(PROJECT_NAME).exe $(WIN_FLAGS)
else 
	g++ $(SRC) $(ENGINE_SRC) -o $(BUILD_DIR)/win/$(PROJECT_NAME).exe $(WIN_FLAGS)
endif

build_all: build_win build_linux
	

run:
	./$(BUILD_DIR)/$(PROJECT_NAME)
	