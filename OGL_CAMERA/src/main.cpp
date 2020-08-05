#include "shader.h"
#include "render.h"
#include "draw.h"
#include "setup.h"

#define WINDOW_FLAGS SDL_WINDOW_OPENGL

int main(int argc, char** argv){
    
    const int screenWidth = 800, screenHeight = 600;
    
    SDL_Window* window;

    window = setupWindow(screenWidth, screenHeight);

    SDL_GLContext glcontext = setupGL(window);

    setupRender();

    Draw draw(window, glcontext);
    
    draw.drawLoop();
    
    return 0;
}
