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
        shader  = Shader::createShader("./shaders/cube2.vs", "./shaders/cube2.fs");
        shader->use();
                                
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 
                                                (float)window.width/(float)window.height, 
                                                0.1f, 100.0f);
                
        shader->setMat4(camera->view,  "camera.view");
        shader->setMat4(projection, "camera.projection");       

        shader->setInt(0, "material.diffuse");
        shader->setInt(1, "material.specular");
        shader->setFloat(64.0f, "material.shininess");

        shader->setVec3(glm::vec3(0.7f, 0.7f, 2.0f), "light.lightPos");
        shader->setVec3(glm::vec3(1.0f), "lightColor");

        shader->setInt(1, "specularOn");

        // Light setup
        lightShader = Shader::createShader("./shaders/light.vs", 
                                           "./shaders/light.fs");
        
        lightShader->use();
        
        glm::mat4 model(1.0f);

        model = glm::translate(model, glm::vec3(0.7f, 0.7f, 2.0f));
        model = glm::scale(model, glm::vec3(0.2f));

        lightShader->setMat4(model, "camera.model");
        lightShader->setMat4(camera->view,  "camera.view");
        lightShader->setMat4(projection, "camera.projection");        
    }
    
    void draw(){
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glBindVertexArray(RenderDataManager::getInstance().vao);
        shader->use();        
        
        glm::mat4 model(1.0f);
                
        for(int i = 0; i < 10; i++){
            model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
            model = glm::rotate(model, glm::radians(30.0f * (i + 1)), glm::vec3(0.0f, 1.0f, 1.0f));
            shader->setVec3(camera->cameraPos, "viewPos");
            shader->setMat4(model, "camera.model");
            glDrawArrays(GL_TRIANGLES ,0, 36);
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
            Draw::shader->setMat4(camera->view, "camera.view");
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
            shader->setInt(specOn, "specularOn");
        }            
        
        camera->moveInDir(dir, deltaTime);
                
    }
};
