#include "util.h"

#define WINDOW_SIZE 800,600
#define WINDOW_FLAGS SDL_WINDOW_OPENGL


SDL_Window* setupWindow();
SDL_GLContext setupGL(SDL_Window*);
void draw(SDL_Window*, SDL_GLContext);
void setupRender();

const int screenwidth = 1024;
const int screenheight = 768;

int main(int argc, char** argv){
            
    SDL_Window* window = setupWindow();    

    SDL_GLContext glcontext = setupGL(window);

    setupRender();

    draw(window, glcontext);
    
    return 0;
}

void draw(SDL_Window* window, SDL_GLContext glcontext){

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f, 0.0f, 0.0f),
        glm::vec3( 2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    Shader shader("./shaders/base.vert","./shaders/base.frag");

    shader.use();
    
    glm::mat4 view          = glm::mat4(1.0f);
    glm::mat4 projection    = glm::mat4(1.0f);
    
    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
    
    projection = glm::perspective(glm::radians(45.0f), (float)screenwidth / (float)screenheight, 0.1f, 100.0f);

    GLuint modelLoc = glGetUniformLocation(shader.id(), "model");    

    GLuint viewLoc = glGetUniformLocation(shader.id(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    GLuint projectionLoc = glGetUniformLocation(shader.id(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    SDL_Event event;

    float delta = 0;

    Uint32 currenTime = 0, lastTime = SDL_GetTicks();

    float speed = 50.0f; // dps
    float angle = 0.0f;

    while(true){

        currenTime = SDL_GetTicks();

        delta = (currenTime - lastTime);
        lastTime = currenTime;

        if(SDL_PollEvent(&event) == 1){            
            if(event.type == SDL_QUIT){
                break;
            }
        };

	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        angle += glm::radians(speed) * delta/1000;
        for(unsigned int i = 0; i < 10; i++){
            glm::mat4 model = glm::mat4(1.0);

            model = glm::translate(model, cubePositions[i]);            

            if(i ==0 || (i + 1) % 3 == 0){
                model = glm::rotate(model, angle , glm::vec3(1.0f, 0.3f, 0.5f));                        
            }else{
                model = glm::rotate(model, -angle , glm::vec3(1.0f, 0.3f, 0.5f));                        
            }
            // model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));            
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }	    

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

SDL_Window* setupWindow(){
    return SDL_CreateWindow(  "OGL", // window title
                                SDL_WINDOWPOS_CENTERED, // at center
                                SDL_WINDOWPOS_CENTERED, // at center
                                screenwidth, screenheight, 
                                WINDOW_FLAGS); // enable opengl
}

SDL_GLContext setupGL(SDL_Window* window){
    SDL_GLContext context = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;

    glewInit();
        
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.7, 0.7, 0.7, 1);

    return context;
}

void setupRender(){
    // image for texture

    unsigned char * data;
    int width, height, nrChannels;    
    
    data = stbi_load("./tex/wall.jpg", &width, &height, &nrChannels, 0);

    // cube vertices

    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

    // points to draw
    // Put data in gpu
    float points[] = {
            // Vertices         // tex coords
             0.5f,  0.5f, 0.0f, 1.f, 1.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };
    
    
    GLuint vao, vbo, texture;
    
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);        
    glGenTextures(1, &texture);

    glBindVertexArray(vao); 
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT,GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));        
    glEnableVertexAttribArray(1);         
}