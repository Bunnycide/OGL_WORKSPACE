#include <iostream> 

#include <SDL2/SDL.h>
#include "util.h"

#define WINDOW_SIZE 640,480
#define WINDOW_FLAGS SDL_WINDOW_OPENGL

int main(int argc, char** argv){
    
    // points to draw

    float points[9] = {
		       0.0, 0.5, 0.0,
		       0.5, -0.5, 0.0,		       
		       -0.5, -0.5, 0.0
    };    
    
    SDL_Window* window;

    window = SDL_CreateWindow(  "OGL", // window title
                                SDL_WINDOWPOS_CENTERED, // at center
                                SDL_WINDOWPOS_CENTERED, // at center
                                WINDOW_SIZE, 
                                WINDOW_FLAGS); // enable opengl

    SDL_GLContext glcontext = SDL_GL_CreateContext(window);

    SDL_Event event;

    glewExperimental = GL_TRUE;

    glewInit();
        
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.7, 0.7, 0.7, 1);

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);


    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);        
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    
    GLuint program = loadShaderProgram(
        loadVertShader("./shaders/base.vert"),
        loadFragShader("./shaders/base.frag")
    );    

    glUseProgram(program);

    glm::mat4 model         = glm::mat4(1.0f);
    glm::mat4 view          = glm::mat4(1.0f);
    glm::mat4 projection    = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)640 / (float)480, 0.1f, 100.0f);

    GLuint modelLoc = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    GLuint viewLoc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    GLuint projectionLoc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // GLuint transformLoc = glGetUniformLocation(program, "transform");
    // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));       
    
    while(true){
        if(SDL_PollEvent(&event) == 1){            
            if(event.type == SDL_QUIT){
                break;
            }
        };

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glDrawArrays(GL_TRIANGLES,0 ,3);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
