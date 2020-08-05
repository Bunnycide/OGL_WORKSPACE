#include "shader.h"
#include "render.h"
#include "draw.h"
#include "setup.h"

#define WINDOW_FLAGS SDL_WINDOW_OPENGL

int main(int argc, char** argv){

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //OpenGL core profile
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 4); //OpenGL 3+
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 2); //OpenGL 3.3

    const int screenWidth = 800, screenHeight = 600;
    
    SDL_Window* window;

    window = setupWindow(screenWidth, screenHeight);

    SDL_GLContext glcontext = setupGL(window);

    RenderDataManager::getInstance().setup();

    Draw draw(window, glcontext);
    
    draw.drawLoop();
    
    return 0;
}
