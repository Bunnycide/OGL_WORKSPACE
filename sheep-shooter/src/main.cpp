#include <iostream>

#include <engine.h>

#define WINDOW_SIZE 640,480
#define WINDOW_FLAGS 0

int main(int argc, char** argv){
    
    Engine engine("GAME", 640, 480);

    engine.setUpdateCallback();

    engine.start();

    return 0;
}
