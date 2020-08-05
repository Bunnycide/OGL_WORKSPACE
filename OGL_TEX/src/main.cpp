#include <iostream> 

#include <SDL2/SDL.h>
#include "util.h"

#define WINDOW_SIZE 640,480
#define WINDOW_FLAGS SDL_WINDOW_OPENGL

int main(int argc, char** argv){

    // image for texture

    unsigned char * data;
    int width, height, nrChannels;

    data = stbi_load("./tex/wall.jpg", &width, &height, &nrChannels, 0);

    // points to draw
    // Put data in gpu
    float points[] = {
            // Vertices         //colors         // tex coords
             0.5f,  0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
				   0,1,2,
				   0,2,3
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

    GLuint vao, vbo, ebo, texture;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);    
    glGenBuffers(1, &ebo);
    glGenTextures(1, &texture);

    glBindVertexArray(vao); 
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT,GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));        
    glEnableVertexAttribArray(1); 
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    GLuint program = loadShaderProgram(
        loadVertShader("./shaders/base.vert"),
        loadFragShader("./shaders/base.frag")
    );

    glUseProgram(program);

    while(true){
        if(SDL_PollEvent(&event) == 1){            
            if(event.type == SDL_QUIT){
                break;
            }
        };

	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	    // Drawing with OGL
        glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
