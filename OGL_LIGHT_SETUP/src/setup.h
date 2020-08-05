#include "includes.h"

#define WINDOW_FLAGS SDL_WINDOW_OPENGL

SDL_Window* setupWindow(int width, int height){
    return SDL_CreateWindow(  "OGL", // window title
                                SDL_WINDOWPOS_CENTERED, // at center
                                SDL_WINDOWPOS_CENTERED, // at center
                                width, height, 
                                WINDOW_FLAGS); // enable opengl
}

SDL_GLContext setupGL(SDL_Window* window){
    SDL_GLContext glcontext = SDL_GL_CreateContext(window);
    
    glewExperimental = GL_TRUE;

    glewInit();
        
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.0, 0.0, 0.0, 1);

    return glcontext;
}
