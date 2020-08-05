#include "includes.h"
#include "shader.h"

class Camera{
    private:
    Shader* shader;

    glm::mat4 posMat = glm::mat4(1.0);
    glm::vec4 cameraPosT = glm::vec4(1.0f);
    glm::vec4 cameraFrontT = glm::vec4(1.0f);

    glm::mat4 view        ;  
    glm::mat4 projection  ;  
    glm::vec3 cameraPos   ;  
    glm::vec3 cameraFront ;  
    glm::vec3 cameraUp    ;

    float cameraSpeed = 0.5f;

    Camera(int w, int h, Shader* shader){
        Camera::shader = shader;

        Camera::view           = glm::mat4(1.0f);
        Camera::projection     = glm::mat4(1.0f);
        
        Camera::cameraPos      = glm::vec3(0.0f, 0.0f, 9.0f);
        Camera::cameraFront    = glm::vec3(0.0f, 0.0f, -1.0f);
        Camera::cameraUp       = glm::vec3(0.0f, 1.0f, 0.0f);        

        Camera::projection     = glm::perspective(
                    glm::radians(45.0f), 
                    (float)w / (float)h, 
                    0.1f, 100.0f
        );

        calculateViewMat();
    }    

    void calculateViewMat(){
        Camera::view           = glm::lookAt(
                    Camera::cameraPos,
                    Camera::cameraPos + Camera::cameraFront,
                    Camera::cameraUp
        );
    }

    public:
    
    static Camera* createCamera(int w, int h, Shader* shader){
        return new Camera(w, h, shader);
    }    
    
    void setup(){
        Camera::shader->use();        
        
        Camera::shader->setMat4(projection,    "proj");
        Camera::shader->setMat4(view,          "view");        
    }

    void moveInDir(glm::vec3 dir, float delta){
        posMat = glm::translate(glm::mat4(1.0f), dir * (cameraSpeed * delta));
        cameraPosT = posMat * glm::vec4(cameraPos, 1.0f);
        cameraPos = glm::vec3(cameraPosT);

        cameraFrontT = posMat * glm::vec4(cameraFront, 1.0f);
        cameraFront = glm::vec3(cameraFrontT);

        calculateViewMat();

        Camera::shader->setMat4(view,          "view");        
    }

    void rotate(float pitch, float yaw, float roll){
        glm::vec3 front;
        front.x = -cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = -sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        cameraFront = glm::normalize(front);

        calculateViewMat();

        Camera::shader->setMat4(view,          "view");
    }
};
