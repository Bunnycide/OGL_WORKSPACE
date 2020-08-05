#include "shader.h"
#include "camera.h"

class Draw{
    private:  
    SDL_Window* window;
    SDL_GLContext glContext;
    Shader* shader;
    Camera* camera;

    float lastX = 400.0f, lastY = 300.0f;
    float cameraSensitivity = 0.05f;
    float pitch = 0.0f, yaw = -90.0f;

    int w, h;
    float delta = 0;
    Uint32 currenTime = 0, lastTime = 0;
    int mousePosX = 0, mousePosY = 0;

    bool firstMouse = true;

    void initDraw();
    void calculateDeltaTime();
    void draw();
    void cleanup();

    void handleEvents(SDL_Event event);
    void handleKeyBoard(SDL_KeyboardEvent event);
    void handleMouse(SDL_MouseMotionEvent event);
    
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
    SDL_WarpMouseInWindow(window, 400, 300);

    Draw::shader = Shader::createShader(  "./shaders/base.vert",
                                            "./shaders/base.frag");

    glm::mat4 model         = glm::mat4(1.0f);    
    
    SDL_GetWindowSize(window, &w, &h);
    Draw::camera = Camera::createCamera(w,h,shader);
    camera->setup();            

    model = glm::rotate(model, glm::radians(-60.0f), glm::vec3(1.0f, 1.0f, 1.0f));        
    Draw::shader->setMat4(model,         "model");  
}

void Draw::handleEvents(SDL_Event event){
    handleKeyBoard(event.key);
    handleMouse(event.motion);

    SDL_PumpEvents();
}

void Draw::handleKeyBoard(SDL_KeyboardEvent event){
    if(event.type == SDL_KEYDOWN){
        // in +x dir
        if(event.keysym.sym == SDLK_d){
            camera->moveInDir(glm::vec3(1.0f, 0.0f, 0.0f), delta);
        }

        // in -x dir
        if(event.keysym.sym == SDLK_a){
            camera->moveInDir(glm::vec3(-1.0f, 0.0f, 0.0f), delta);
        }

        // in -z dir
        if(event.keysym.sym == SDLK_w){
            camera->moveInDir(glm::vec3(0.0f, 0.0f, -1.0f), delta);
        }

        // in +z dir
        if(event.keysym.sym == SDLK_s){
            camera->moveInDir(glm::vec3(0.0f, 0.0f, 1.0f), delta);
        }
    }
}

void Draw::handleMouse(SDL_MouseMotionEvent event){

    SDL_GetMouseState(&mousePosX, &mousePosY);
    
    if(firstMouse){
        lastX = mousePosX;
        lastY = mousePosY;
        firstMouse = false;
    }

    float xoffset = mousePosX - lastX;
    float yoffset = lastY - mousePosY;

    lastX = mousePosX;
    lastY = mousePosY;

    xoffset *= cameraSensitivity;
    yoffset *= cameraSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if(pitch >  89.0f) pitch =  89.0f;
    if(pitch < -89.0f) pitch = -89.0f;
    
    camera->rotate(pitch, yaw, 0.0f);
}

void Draw::draw(){
    glDrawArrays(GL_TRIANGLES,0 ,36);
}

void Draw::calculateDeltaTime(){
    currenTime = SDL_GetTicks();

    delta = (currenTime - lastTime)/1000.0f;
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
    delete Draw::camera;
}
