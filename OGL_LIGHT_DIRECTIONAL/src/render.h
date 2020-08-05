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

    GLuint vao, vbo, lightvao, texture, specTexture;

    void setupTextureData(){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }

    void setup(){
        unsigned char *texdata, *specTexData;
        ImgParams imgParams, specImgParams;
        texdata = getImageData("./tex/crate.jpg", &imgParams);                  
        specTexData = getImageData("./tex/crate_spec.jpg", &specImgParams);

        // setup vertex array and vertex buffer objects also texture
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenTextures(1, &texture);
        glGenTextures(1, &specTexture);

        glBindVertexArray(vao);

        // Get cube data in    
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_light), cube_light, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // Get texture in
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);   
        setupTextureData();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgParams.width, imgParams.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texdata);
        stbi_image_free(texdata);

        // Get specular map in
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specTexture);
        setupTextureData();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, specImgParams.width, specImgParams.height, 0, GL_RGB, GL_UNSIGNED_BYTE, specTexData);
        stbi_image_free(specTexData);

        // Setup lamp

        glGenVertexArrays(1, &lightvao);
        glBindVertexArray(lightvao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }    
};
