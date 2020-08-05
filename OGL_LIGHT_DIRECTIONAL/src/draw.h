#include "shader.h"
#include "camera.h"

class Draw{
    private:  
    SDL_Window* window;
    SDL_GLContext glContext;
    Shader  *shader, *lampshader;    
    Camera *camera;

    glm::mat4 model         = glm::mat4(1.0f);    
    glm::vec3 lightPos = glm::vec3(1.2f, 1.4f, 2.0f);    

    int w, h;
    float delta = 0;
    Uint32 currenTime = 0, lastTime = 0;

    float angle = 0.0f, radius = 3.0f, angularSpeed = 0.05f;

    void initDraw();
    void draw();
    void cleanup();
    void handleEvents(SDL_Event event);
    void calculateDeltaTime();
    void calcualteNewLightPos();

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
    Draw::shader = Shader::createShader("./shaders/base.vert",
                                        "./shaders/cube.frag");    
    
    SDL_GetWindowSize(window, &w, &h);    

    // Setup cube
    Draw::shader->use();
    Camera::setViewAndProj(Draw::shader, w, h, 6.0f);
    model = glm::rotate(model, glm::radians(35.0f), glm::vec3(1.0f, 0.0f, 0.0f));    
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));        
    model = glm::scale(model, glm::vec3(1.5f));

    Draw::shader->setMat4(model,             "model");    

    // Setup light    
    Draw::shader->setVec3(glm::vec3(1.0f, 1.0f, 1.0f), "light_color");
    Draw::shader->setVec3(lightPos, "light_pos");
    Draw::shader->setVec3(glm::vec3(0.0f, 0.0f, 6.0f) ,"view_pos");
        
    Draw::shader->setInt(0, "material.diffuse");
    Draw::shader->setInt(1,  "material.specular");
    Draw::shader->setFloat(128.0f, "material.shininess");

    Draw::shader->setVec3(glm::vec3(0.2f, 0.2f, 0.2f), "light.ambient");    
    Draw::shader->setVec3(glm::vec3(0.5f, 0.5f, 0.5f), "light.diffuse");
    Draw::shader->setVec3(glm::vec3(1.0f, 1.0f, 1.0f), "liht.specular");

    Draw::shader->setVec3(-lightPos, "light.direction");

    // Our lamp shader

    Draw::lampshader = Shader::createShader("./shaders/lamp.vert",
                                            "./shaders/lamp.frag");

    Draw::lampshader->use();
    Camera::setViewAndProj(Draw::lampshader, w, h, 6.0f);   

    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f));


    Draw::lampshader->setMat4(model, "model");

    model = glm::mat4(1.0f);
}

void Draw::handleEvents(SDL_Event event){

}

void Draw::calcualteNewLightPos(){
    angle += angularSpeed * delta;

    if(angle > 360.0f) angle -=  360.0f;

    lightPos.x = radius * cos(angle);
    lightPos.z = radius * sin(angle);

    // std::cout << "Angle is " << angle << std::endl;
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f));
}

void Draw::draw(){         
    for(uint i = 0; i < 10; i ++){
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);        
        model = glm::rotate(model, glm::radians((float)(i+1) * 40.0f), glm::vec3(1.0f, 1.0f, 0.0f));
        Draw::shader->use();    
        Draw::shader->setMat4(model, "model");        
        glBindVertexArray(RenderDataManager::getInstance().vao);
        glDrawArrays(GL_TRIANGLES,0 ,36);
    }
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
