#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "includes.h"

class Camera{
public:    

    glm::mat4 posMat = glm::mat4(1.0);
    glm::vec4 cameraPosT = glm::vec4(1.0f);

    glm::mat4 view        ;
    
    glm::vec3 cameraPos   ;  
    glm::vec3 cameraFront ;  
    glm::vec3 cameraUp    ;

    const float cameraSpeed = 1.0f;
    
    float strafed = 0;
    
    Camera(float eye_pos){        

        Camera::view           = glm::mat4(1.0f);        
        
        Camera::cameraPos      = glm::vec3(0.0f, 0.0f, eye_pos);
        Camera::cameraFront    = glm::vec3(0.0f, 0.0f, -1.0f);
        Camera::cameraUp       = glm::vec3(0.0f, 1.0f, 0.0f);              

        calculateViewMat();
    }    

    void calculateViewMat(){
        Camera::view           = glm::lookAt(
                    Camera::cameraPos,
                    Camera::cameraPos + Camera::cameraFront,
                    Camera::cameraUp
        );
    }    
    
    static Camera* createCamera(float originOffset){
        return new Camera(originOffset);
    }
            
    void moveInDir(glm::vec3 dir, float delta){
        if(dir.z != 0.0f)
            cameraPos += dir.z * cameraSpeed * delta * cameraFront;
        if(dir.x != 0.0f)
            cameraPos += dir.x * glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * delta;
                        
        calculateViewMat();
    }
        
    
    void rotate(float pitch, float yaw, float roll){
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        cameraFront = glm::normalize(front);

        calculateViewMat();        
    }    
};

#endif // CAMERA_H_INCLUDED
