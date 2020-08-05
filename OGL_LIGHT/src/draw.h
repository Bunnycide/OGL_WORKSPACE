#include "shader.h"
#include "camera.h"

class Draw{
    private:  
    SDL_Window* window;
    SDL_GLContext glContext;        

    int w, h;
    float delta = 0;
    Uint32 currenTime = 0, lastTime = 0;    

    void initDraw();
    void draw();
    void cleanup();
    void handleEvents(SDL_Event event);
    void calculateDeltaTime();

    public:
    Draw(SDL_Window*, SDL_GLContext);
    void drawLoop();
};

Draw::Draw(SDL_Window* window, SDL_GLContext glContext){
    Draw::window = window;
    Draw::glContext = glContext;

    initDraw();
}

void Draw::initDraw(){
    SDL_GetWindowSize(window, &w, &h);
}

void Draw::handleEvents(SDL_Event event){

}

void Draw::draw(){    
    
}

void Draw::calculateDeltaTime(){
    currenTime = SDL_GetTicks();

    delta = (currenTime - lastTime) / 1000.0f;
    lastTime = currenTime;
}

void Draw::drawLoop(){
    SDL_Event event;        
                
    calculateDeltaTime();

    while(true){        
        
        if(SDL_PollEvent(&event) == 1){            
            if(event.type == SDL_QUIT){
                break;
            }

            Draw::handleEvents(event);
        };

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        
        draw();
        SDL_GL_SwapWindow(window);
    }

    cleanup();
}

void Draw::cleanup(){
    SDL_GL_DeleteContext(Draw::glContext);
    SDL_DestroyWindow(Draw::window);
    SDL_Quit();    
}
