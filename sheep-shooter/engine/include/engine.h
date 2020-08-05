#ifndef __ENGINE_H__
#define __ENGINE_H__

#include<SDL2/SDL.h>

class Engine{        

    public:
    Engine( const char*, int,  int);
    void start();

    private:

    SDL_Renderer* renderer;
    SDL_Event event;
    bool keepRunning = false;
    SDL_Window* window;     

    void cleanup();
};

#endif // __ENGINE_H__