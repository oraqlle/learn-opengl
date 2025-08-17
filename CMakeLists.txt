cmake_minimum_required(VERSION 3.21)

project(
    learn_opengl
    VERSION 0.1.0
    DESCRIPTION "learn-opengl examples"
    LANGUAGES CXX C
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(glfw3 3.4 REQUIRED)

option(WIREFRAME_MODE "Render using wireframe polygons" OFF)

# ---- Declare executable ----
add_executable(learn_opengl src/main.cxx src/glad.c)
target_compile_features(learn_opengl PRIVATE c_std_99)
target_link_libraries(learn_opengl PRIVATE glfw)

if(WIREFRAME_MODE)
    target_compile_definitions(learn_opengl PUBLIC -DWIREFRAME_MODE)
endif(WIREFRAME_MODE)

