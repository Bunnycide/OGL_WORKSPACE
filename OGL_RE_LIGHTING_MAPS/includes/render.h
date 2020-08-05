#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include "includes.h"
#include "renderdata.h"

class RenderDataManager{
    private:
    RenderDataManager(){}    

    public:
    RenderDataManager(RenderDataManager const& )            = delete;
    void operator=(RenderDataManager const&)                = delete;

    static RenderDataManager& getInstance(){
        static RenderDataManager instance;  

        return instance;
    }

    GLuint vao, vbo;
    GLuint lightvao;
    
    void setup(){ 
#ifndef RENDER_DATA_SETUP
#define RENDER_DATA_SETUP
        // setup vertex array and vertex buffer objects also texture        
            
        glGenVertexArrays(1, &vao);
        glGenVertexArrays(1, &lightvao);
        glGenBuffers(1, &vbo);
        
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_light), cube_light, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        
        glActiveTexture(GL_TEXTURE0);
        loadTexture("./tex/container.png");
        glActiveTexture(GL_TEXTURE1);
        loadTexture("./tex/container_specular.png");
        glActiveTexture(GL_TEXTURE2);
        loadTexture("./tex/matrix.jpg");
        
        glBindVertexArray(lightvao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
                                
#endif // RENDER_DATA_SETUP
    }
};

#endif // RENDER_H_INCLUDED
