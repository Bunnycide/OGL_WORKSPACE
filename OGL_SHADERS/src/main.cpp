#include <iostream> 

#include <SDL2/SDL.h>
#include "util.h"

#define WINDOW_SIZE 640,480
#define WINDOW_FLAGS SDL_WINDOW_OPENGL

int main(int argc, char** argv){
       
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
    
    GLuint program = loadShaderProgram(
        loadVertShader("./shaders/base.vert"),
        loadFragShader("./shaders/base.frag")
    );

    // Data
    float vertices[] = {
			//positions          // colors
			 0.5f, -0.25f, 0.0f,   1.0f, 0.0f, 0.0f,
			-0.5f, -0.25f, 0.0f,   0.0f, 1.0f, 0.0f,
			 0.0f,  0.75f, 0.0f,   0.0f, 0.0f, 1.0f,

			 //positions          // colors
			 0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
			-0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
			 0.0f, - 0.5f, 0.0f,   0.0f, 0.0f, 1.0f
    };

    GLuint vbo, vao;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glUseProgram(program);    
    
    while(true){
        if(SDL_PollEvent(&event) == 1){            
            if(event.type == SDL_QUIT){
                break;
            }
        };

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 6);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
