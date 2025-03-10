cmake_minimum_required(VERSION 3.26)

find_package(SDL3 REQUIRED)

project(Engine)

file(GLOB ENGINE_SRC Engine/Source/*/private/*.cpp)
file(GLOB EXTERNAL_SRC Engine/external/imgui-docking/*.cpp)

add_executable(
    Complex 
    "main.cpp"
    ${ENGINE_SRC}
    ${EXTERNAL_SRC}
)

target_link_libraries(Engine SDL3::SDL3)