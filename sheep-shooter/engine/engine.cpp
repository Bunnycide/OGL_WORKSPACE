#include <engine.h>

#define WINDOW_FLAGS 0

Engine::Engine(const char* name, int width, int height){
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(  name, // window title
                                SDL_WINDOWPOS_CENTERED, // at center
                                SDL_WINDOWPOS_CENTERED, // at center
                                width, height,
                                WINDOW_FLAGS);
}

void Engine::start(){
    Engine::keepRunning = true;
    
    while(Engine::keepRunning){
        if(SDL_PollEvent(&event) == 1){
            if(event.type == SDL_QUIT){
                break;
            }
        }
    }

    Engine::cleanup();
}

void Engine::cleanup(){
    SDL_DestroyWindow(Engine::window);
    SDL_Quit();
}
