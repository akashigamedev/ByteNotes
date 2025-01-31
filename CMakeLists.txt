cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(byte_notes VERSION 1.0)

set(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps")

# imgui library
add_library(imgui
  ${DEPS_DIR}/imgui/imgui.cpp
  ${DEPS_DIR}/imgui/imgui_demo.cpp
  ${DEPS_DIR}/imgui/imgui_draw.cpp
  ${DEPS_DIR}/imgui/imgui_tables.cpp
  ${DEPS_DIR}/imgui/imgui_widgets.cpp
  ${DEPS_DIR}/imgui/backends/imgui_impl_glfw.cpp
  ${DEPS_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

# add all file inclusions here
file(GLOB_RECURSE BYTENOTES_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE BYTENOTES_FRONTEND_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/frontend/*.cpp)
file(GLOB_RECURSE BYTENOTES_BACKEND_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/backend/*.cpp)
file(GLOB_RECURSE GLAD_SRC ${DEPS_DIR}/glad/src/glad.c)

find_package(OpenGL REQUIRED)
add_subdirectory(${DEPS_DIR}/glfw)

add_executable(byte_notes
  ${BYTENOTES_SRC}
  ${BYTENOTES_FRONTEND_SRC}
  ${BYTENOTES_BACKEND_SRC}
  ${GLAD_SRC}
)

target_compile_definitions(byte_notes PUBLIC 
    BUILD_DIR="${CMAKE_BINARY_DIR}")

target_link_libraries(byte_notes imgui OpenGL::GL glfw)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts/ 
     DESTINATION ${CMAKE_BINARY_DIR}/assets/fonts/)

# add all include directories here
target_include_directories(imgui PUBLIC ${DEPS_DIR}/imgui ${DEPS_DIR}/imgui/backends ${DEPS_DIR}/glfw/include)
target_include_directories(byte_notes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(byte_notes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/frontend)
target_include_directories(byte_notes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/backend)
target_include_directories(byte_notes PUBLIC ${DEPS_DIR}/glad/include)
