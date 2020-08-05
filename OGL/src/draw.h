#include "shader.h"

class Draw{
    private:  
    SDL_Window* window;
    SDL_GLContext glContext;
    Shader* shader;
    
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
    Draw::shader = Shader::createShader(  "./shaders/base.vert",
                                            "./shaders/base.frag");

    glm::mat4 model         = glm::mat4(1.0f);
    glm::mat4 view          = glm::mat4(1.0f);
    glm::mat4 projection    = glm::mat4(1.0f);
    
    SDL_GetWindowSize(window, &w, &h);
        
    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));    
    projection = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f);
    model = glm::rotate(model, glm::radians(-60.0f), glm::vec3(1.0f, 1.0f, 1.0f));    

    Draw::shader->use();

    Draw::shader->setMat4(model,         "model");
    Draw::shader->setMat4(projection,    "proj");
    Draw::shader->setMat4(view,          "view");    
}

void Draw::handleEvents(SDL_Event event){

}

void Draw::draw(){
    glDrawArrays(GL_TRIANGLES,0 ,36);
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

    delete Draw::shader;
}
