#include <iostream> 

#include <SDL2/SDL.h>
#include "util.h"

#define WINDOW_SIZE 640,480
#define WINDOW_FLAGS SDL_WINDOW_OPENGL

int main(int argc, char**) {
	 
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

	 glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	 
	 glClearColor(0.7, 0.7, 0.7, 1);

	 // Data here

	 float vertices[] = {
			     0.5f,  0.5f, 0.0f,  // top right
			     0.5f, -0.5f, 0.0f,  // bottom right
			     -0.5f, -0.5f, 0.0f,  // bottom left
			     -0.5f,  0.5f, 0.0f   // top left
	 };

	 unsigned int indices[] = {
				   0,1,2,
				   0,2,3
	 };
      
	 GLuint program = loadShaderProgram(
					    loadVertShader("./shaders/base.vert"),
					    loadFragShader("./shaders/base.frag")
					    );

	 GLuint vbo, vao, ebo;
	 glGenVertexArrays(1, &vao);
	 glGenBuffers(1, &vbo);
	 glGenBuffers(1, &ebo);

	 glBindVertexArray(vao);

	 glBindBuffer(GL_ARRAY_BUFFER, vbo);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	 glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	 glEnableVertexAttribArray(0);

	 glBindBuffer(GL_ARRAY_BUFFER, 0);
	 glBindVertexArray(0);

	 glUseProgram(program);
			       
	 while(true){
	   if(SDL_PollEvent(&event) == 1){            
	     if(event.type == SDL_QUIT){
	       break;
	     }
	   };	   
	   
	   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   
	   // Draw
	   
	   glBindVertexArray(vao);
	   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	   SDL_GL_SwapWindow(window);
	 }

	 SDL_GL_DeleteContext(glcontext);
	 SDL_DestroyWindow(window);
	 SDL_Quit();

	 return 0;
}
