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

    GLuint vao, vbo, texture, lightvao;

    void setup(){
        unsigned char* texdata;  ImgParams imgParams;
        texdata = getImageData("./tex/wall.jpg", &imgParams);    

        // setup vertex array and vertex buffer objects also texture
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenTextures(1, &texture);

        glBindVertexArray(vao);

        // Get cube data in    
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);    

        // Get texture in
        glBindTexture(GL_TEXTURE_2D, texture);   

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgParams.width, imgParams.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texdata);

        stbi_image_free(texdata);        
    }    
};
