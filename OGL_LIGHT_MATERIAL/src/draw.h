#include "shader.h"
#include "camera.h"

class Draw{
    private:  
    SDL_Window* window;
    SDL_GLContext glContext;
    Shader  *shader, *lampshader;    
    Camera *camera;

    glm::mat4 model         = glm::mat4(1.0f);    
    glm::vec3 lightPos = glm::vec3(1.0f, 1.4f, 1.7f);   

    float angle = 0.0f, radius = 2.5f, angularSpeed = 0.05f; 

    int w, h;
    float delta = 0;
    Uint32 currenTime = 0, lastTime = 0;
    
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

    // 0.0215f, 	0.1745f, 	0.0215f, 	0.07568f, 	0.61424f, 	0.07568f, 	0.633f, 	0.727811f, 	0.633 	0.6

    // Setup cube
    Draw::shader->use();
    Camera::setViewAndProj(Draw::shader, w, h, 6.0f);    
    model = glm::rotate(model, glm::radians(35.0f), glm::vec3(1.0f, 0.0f, 0.0f));    
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));        
    model = glm::scale(model, glm::vec3(2.0f));
    Draw::shader->setMat4(model,             "model");    

    //Setup textures 
    Draw::shader->setInt(0, "material.diffuse");
    Draw::shader->setInt(1, "material.specular");
    Draw::shader->setInt(2, "emission");

    // Setup light
    Draw::shader->setVec3(glm::vec3(0.314f, 0.784f, 0.471f), "object_color");       
    Draw::shader->setVec3(glm::vec3(0.0f, 0.0f, 6.0f) ,"view_pos");

    // Setup material
    Draw::shader->setVec3(glm::vec3(0.0215f, 	0.1745f, 	0.0215f ), "material.ambient");
    Draw::shader->setInt(0, "material.diffuse");
    Draw::shader->setVec3(glm::vec3(0.633f, 	0.727811f, 	0.633f  ), "material.specular");
    Draw::shader->setFloat(0.633f, "material.shininess");

    // Setup light intensity
    Draw::shader->setVec3(lightPos, "light.position");
    Draw::shader->setVec3(glm::vec3(0.2f, 0.2f, 0.2f), "light.ambient");
    Draw::shader->setVec3(glm::vec3(0.7f, 0.7f, 0.7f), "light.diffuse");
    Draw::shader->setVec3(glm::vec3(1.0f, 1.0f, 1.0f), "light.specular");

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

    Draw::calcualteNewLightPos();

    Draw::lampshader->use();
    Draw::lampshader->setMat4(model,        "model");

    glBindVertexArray(RenderDataManager::getInstance().lightvao);
    glDrawArrays(GL_TRIANGLES,0 ,36);

    
    Draw::shader->use();
    Draw::shader->setVec3(lightPos, "light.position");    

    glBindVertexArray(RenderDataManager::getInstance().vao);
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
