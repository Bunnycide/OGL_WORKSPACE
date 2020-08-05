#include "includes.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

struct Window{
    GLFWwindow* handle;
    int width, height;
};

void init(){
    #ifndef INIT_DONE
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);        
    #define INIT_DONE
    #endif // INIT_DONE
}

Window setupWindow(int width, int height)
{       

    GLFWwindow *window = glfwCreateWindow(  width, height, 
                                            "OGL_POINT_LIGHT", 
                                            NULL, NULL);
    
    Window windowStruct{
        NULL,
        width,
        height
    };
    
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW widow" << std::endl;
        glfwTerminate();        
        return windowStruct;
    }

    glfwMakeContextCurrent(window);

    windowStruct.handle = window;    
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(! gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;        
    }    
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    return windowStruct;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}
