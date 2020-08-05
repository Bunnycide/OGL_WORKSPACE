#include "includes.h"

struct ImgParams{
    int width, height, nrChannels;
};

char * getSource(const char* path){
    FILE *f = fopen(path, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

    char *string = (char *)malloc(fsize + 1);
    fread(string, 1, fsize, f);
    fclose(f);

    string[fsize] = 0;

    return string;
}


unsigned char* getImageData(const char* path, ImgParams* params){
    unsigned char * data;
    int width, height, nrChannels;

    data = stbi_load("./tex/wall.jpg", &width, &height, &nrChannels, 0);

    params->height = height;
    params->width = width;
    params->nrChannels = nrChannels;

    return data;
}

GLuint loadVertShader(const char* path){
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    const char* source = getSource(path);
    glShaderSource(vs, 1, &source, NULL);
    glCompileShader(vs);

    GLint isCompiled = 0;

    glGetShaderiv(vs, GL_COMPILE_STATUS, &isCompiled);

    if(isCompiled == GL_FALSE){
        GLint maxLength = 0;
        glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);

        char* log = (char *)malloc(maxLength);

        glGetShaderInfoLog(vs, maxLength, &maxLength, log);

        glDeleteShader(vs);

        std::cout << log << std::endl;

        return 0;
    }

    return vs;
}

GLuint loadFragShader(const char* path){
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    const char* source = getSource(path);
    glShaderSource(fs, 1, &source, NULL);
    glCompileShader(fs);

    GLint isCompiled = 0;

    glGetShaderiv(fs, GL_COMPILE_STATUS, &isCompiled);

    if(isCompiled == GL_FALSE){
        GLint maxLength = 0;
        glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);

        char* log = (char *)malloc(maxLength);

        glGetShaderInfoLog(fs, maxLength, &maxLength, log);

        glDeleteShader(fs);

        std::cout << log << std::endl;

        return 0;
    }

    return fs;
}

GLuint loadShaderProgram(GLuint vs, GLuint fs){
    GLuint program = glCreateProgram();
    glAttachShader(program ,vs);
    glAttachShader(program ,fs);
    glLinkProgram(program);

    return program;
}

class Shader{
    private:
    GLuint ID = 0, vert_shader = 0, frag_shader = 0;

    public:  
    Shader(const char* vert_path, const char* frag_path){
        vert_shader = loadVertShader(vert_path);
        frag_shader = loadFragShader(frag_path);

        if(vert_shader != 0 && frag_shader !=0){
            ID = loadShaderProgram(vert_shader, frag_shader);
        }        
    }

    GLuint id(){
        return ID;
    }

    void use(){
        glUseProgram(ID);
    }
};