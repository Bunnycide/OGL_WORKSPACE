#pragma once

#include <includes.h>

class Draw{
private:
    Window window;
    
    double currentFrame = 0;
    double lastFrame = currentFrame;
    double deltaTime;
        
    Shader *shader, *lightShader;    
    Camera *camera;    
    
    bool firstMouse = true;
    
    double lastX =0, lastY=0;
    float pitch = 0.0f, yaw = -90.0f;
    float cameraSensitivity = 0.05f;

    bool specOn = 1;

    glm::mat4 model = glm::mat4(1.0f);
    
public:
    
    Draw(Window window){
        Draw::window = window;
        glClearColor(0.7f, 0.7f, 0.7f, 1.0f);        
    }
    
    Draw(Window window, float r, float g, float b){
        Draw::window = window;
        glClearColor(r, g, b, 1.0f);
    }
            
    void initDraw(){                              
        glfwSetInputMode(window.handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);                
        
        camera = Camera::createCamera(6.0);
        // Cube setup
        shader  = Shader::createShader("./shaders/cube.vs", "./shaders/cube.fs");
        shader->use();
                                
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 
                                                (float)window.width/(float)window.height, 
                                                0.1f, 100.0f);
                
        // bring crate in position

        model = glm::translate(model, cubePositions[0]);

        shader->setMat4(model, "camera.model");
        shader->setMat4(camera->view,  "camera.view");
        shader->setMat4(projection, "camera.projection");       

        shader->setVec3(glm::vec3(0.05f, 0.05f, 0.0f), "material.ambient");
        shader->setInt(0, "material.diffuse");
        shader->setInt(1, "material.specular");        
        shader->setFloat(0.25, "material.shininess");

        // directional light
        shader->setVec3(glm::vec3(-0.2f, -1.0f, -0.3f), "dirLight.direction");
        shader->setVec3(glm::vec3(0.2f, 0.2f, 0.2f), "dirLight.ambient");
        shader->setVec3(glm::vec3(0.5f, 0.5f, 0.5f), "dirLight.diffuse");
        shader->setVec3(glm::vec3(1.0f, 1.0f, 1.0f), "dirLight.specular");

        // point light        
        // -- location
        shader->setVec3(glm::vec3(1.2f, 1.0f, 2.0f), "pointLight.position");

        // -- light components
        shader->setVec3(glm::vec3(0.2f, 0.2f, 0.2f), "pointLight.ambient");
        shader->setVec3(glm::vec3(0.5f, 0.5f, 0.5f), "pointLight.diffuse");
        shader->setVec3(glm::vec3(1.0f, 1.0f, 1.0f), "pointLight.specular");

        // -- attenuation factors
        shader->setFloat(1.0f,  "pointLight.constant");
        shader->setFloat(0.14f, "pointLight.linear");
        shader->setFloat(0.07f, "pointLight.quadratic");

        // spot light
        // -- position
        shader->setVec3(camera->cameraPos,              "spotLight.position");
        shader->setVec3(camera->cameraFront,            "spotLight.direction");
        shader->setFloat(glm::cos(glm::radians(12.5f)), "spotLight.cutoff");
        shader->setFloat(glm::cos(glm::radians(17.5f)), "spotLight.outerCutoff");

        // -- light componenets
        shader->setVec3(glm::vec3(0.2f, 0.2f, 0.2f), "spotLight.ambient");
        shader->setVec3(glm::vec3(0.7f, 0.7f, 0.7f), "spotLight.diffuse");
        shader->setVec3(glm::vec3(1.0f, 1.0f, 1.0f), "spotLight.specular");

        // -- attenuation
        shader->setFloat(1.0f,      "spotLight.constant");
        shader->setFloat(0.0454f,   "spotLight.linear");
        shader->setFloat(0.0075f,   "spotLight.quadratic");

        // Light setup
        model = glm::mat4(1.0f);

        lightShader = Shader::createShader("./shaders/light.vs", 
                                           "./shaders/light.fs");
        
        lightShader->use();                

        model = glm::translate(model, glm::vec3(1.2f, 1.0f, 2.0f));
        model = glm::scale(model, glm::vec3(0.2f));

        lightShader->setMat4(model, "camera.model");
        lightShader->setMat4(camera->view,  "camera.view");
        lightShader->setMat4(projection, "camera.projection");        

        model = glm::mat4(1.0f);
    }
    
    void draw(){
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glBindVertexArray(RenderDataManager::getInstance().vao);
        shader->use();                        

        for(int i = 0; i < 10; i++){
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::radians(20.0f * (i + 1) ), glm::vec3(1.0f, 0.3f, 0.5f));
            shader->setMat4(model, "camera.model");            
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
                
        glBindVertexArray(RenderDataManager::getInstance().lightvao);
        lightShader->use();
        glDrawArrays(GL_TRIANGLES, 0, 36);

    }
    
    void mainLoop(){
        initDraw();
        
        while(!glfwWindowShouldClose(Draw::window.handle))
        {
            Draw::calculateDeltaTime();
            
            // check input
            // ----------
            Draw::processInput();            
            Draw::processMouse();
            Draw::draw();
            
            glfwSwapBuffers(Draw::window.handle);
            glfwPollEvents();
            
            Draw::shader->use();
            Draw::shader->setVec3(camera->cameraPos, "viewPos");
            Draw::shader->setMat4(camera->view, "camera.view"); 

            shader->setVec3(camera->cameraPos,              "spotLight.position");
            shader->setVec3(camera->cameraFront,            "spotLight.direction");
                       
            Draw::lightShader->use();
            Draw::lightShader->setMat4(camera->view, "camera.view");
        }
        
        glfwTerminate();
    }
    
    void calculateDeltaTime(){
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;        
    }        
    
    void processMouse(){
        double xPos,yPos;
        glfwGetCursorPos(window.handle, &xPos, &yPos);
        
        if(firstMouse){
            lastX = xPos;
            lastY = yPos;
            
            firstMouse = false;            
        }
        
        
        double xOffset = xPos - lastX;
        double yOffset = yPos - lastY;
        
        lastX = xPos;
        lastY = yPos;

        xOffset *= cameraSensitivity;
        yOffset *= cameraSensitivity;

        yaw += xOffset;
        pitch += yOffset;

        if(pitch >  89.0f) pitch =  89.0f;
        if(pitch < -89.0f) pitch = -89.0f;
        
        camera->rotate(pitch, yaw, 0.0f);
    }
    
    void processInput()
    {                
        glm::vec3 dir(0.0f);
        glm::vec2 rot(0.0f);
        
        if(glfwGetKey(window.handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(Draw::window.handle, true);
        
        if(glfwGetKey(window.handle, GLFW_KEY_A) == GLFW_PRESS)
            dir.x = -1.0;        
        if(glfwGetKey(window.handle, GLFW_KEY_D) == GLFW_PRESS)
            dir.x = 1.0;
        if(glfwGetKey(window.handle, GLFW_KEY_W) == GLFW_PRESS)
            dir.z = 1.0;
        if(glfwGetKey(window.handle, GLFW_KEY_S) == GLFW_PRESS)
            dir.z = -1.0;

        if(glfwGetKey(window.handle, GLFW_KEY_F) == GLFW_PRESS){
            shader->use();
            specOn = !specOn;            
        }            
        
        camera->moveInDir(dir, deltaTime);
                
    }
};
