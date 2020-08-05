cmake_minimum_required(VERSION 3.10.1)
set(PROJECT_NAME OGL_SPOT_LIGHT)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(${PROJECT_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/modules)

find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(GLFW3 REQUIRED)
message(STATUS "GLFW included at ${GLFW3_INCLUDE_DIR}")
find_package(ASSIMP REQUIRED)
message(STATUS "ASSIMP included at ${ASSIMP_INCLUDE_DIR}")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall")

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
add_definitions(${OPENGL_DEFINITIONS})
find_package(X11 REQUIRED)

# all the libs
# ------------------
set(LIBS ${GLFW3_LIBRARY} X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread ${ASSIMP_LIBRARY})

# root direcotry
# ------------------
configure_file(${CMAKE_SOURCE_DIR}/configuration/root_directory.h.in ${CMAKE_SOURCE_DIR}/configuration/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/configuration)

# stbi image lib
add_library(STB_IMAGE "src/stb_image.cpp")
set(LIBS ${LIBS} STB_IMAGE)

add_library(GLAD "glad/src/glad.c")
set(LIBS ${LIBS} GLAD)

add_executable(main src/main.cpp)
target_link_libraries(main ${LIBS})
set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

file(GLOB SHADERS 
    "shaders/*.vs"
    "shaders/*.fs"
    "shaders/*.gs")
    
file(GLOB TEXTURES
    "tex/*.png"
    "tex/*.jpg")
    
# Create the shaders and textures directories    
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/_build/bin/shaders)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/_build/bin/tex)

foreach(SHADER ${SHADERS})
    file(COPY ${SHADER} DESTINATION ${CMAKE_SOURCE_DIR}/_build/bin/shaders)
endforeach(SHADER)
    
foreach(TEXTURE ${TEXTURES})
    file(COPY ${TEXTURE} DESTINATION ${CMAKE_SOURCE_DIR}/_build/bin/tex)
endforeach(TEXTURE)

include_directories(${CMAKE_SOURCE_DIR}/includes ${CMAKE_SOURCE_DIR}/glad/include)
