#include "renderdata.h"
#include "utils.h"

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

    GLuint vao, vbo, lightvao, texture, specTexture, glowTexture;

    void setup(){        

        // setup vertex array and vertex buffer objects also texture
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenTextures(1, &texture);
        glGenTextures(1, &specTexture);
        glGenTextures(1, &glowTexture);

        glBindVertexArray(vao);

        // Get cube data in    
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_light), cube_light, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1); 
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
        glEnableVertexAttribArray(2); 
        
        // Get texture in
        glActiveTexture(GL_TEXTURE0);
        texture = loadTexture("./tex/container.png");
        // Get spec map in
        glActiveTexture(GL_TEXTURE1);
        specTexture = loadTexture("./tex/container_specular.png");
        //Get glow map in
        glActiveTexture(GL_TEXTURE2);
        glowTexture = loadTexture("./tex/matrix.jpg");
        // Setup lamp        

        glGenVertexArrays(1, &lightvao);
        glBindVertexArray(lightvao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  8* sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }    
};
