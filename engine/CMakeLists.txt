cmake_minimum_required(VERSION 3.11)
project(bomj VERSION 0.0.1 LANGUAGES C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)

set(GLEW_USE_STATIC_LIBS TRUE)

add_executable(${PROJECT_NAME})
    ${CMAKE_SOURCE_DIR}/src/main.c
    ${CMAKE_SOURCE_DIR}/src/platform/p_opengl.c
    ${CMAKE_SOURCE_DIR}/src/platform/p_windows.c
    ${CMAKE_SOURCE_DIR}/src/platform/pgl/matrix.c
    ${CMAKE_SOURCE_DIR}/src/platform/pgl/vector.c
    ${CMAKE_SOURCE_DIR}/src/platform/p_vulkan.c
)

target_sources(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/src/main.c
    ${CMAKE_SOURCE_DIR}/src/platform/p_opengl.c
    ${CMAKE_SOURCE_DIR}/src/platform/p_windows.c
    ${CMAKE_SOURCE_DIR}/src/platform/pgl/matrix.c
    ${CMAKE_SOURCE_DIR}/src/platform/pgl/vector.c
    ${CMAKE_SOURCE_DIR}/src/platform/p_vulkan.c
)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLEW_STATIC)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/platform ${CMAKE_SOURCE_DIR}/libs/include)
target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/libs/lib/glew32s.lib opengl32 gdi32 ${CMAKE_SOURCE_DIR}/libs/lib/vulkan-1.lib)