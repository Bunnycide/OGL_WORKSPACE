#ifndef __SHADER_H__
#define __SHADER_H__

#include "includes.h"

char * getSource(const char* path){
    FILE *f = fopen(path, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *string = (char *)malloc(fsize + 1);
    fread(string, 1, fsize, f);
    fclose(f);

    string[fsize] = 0;

    return string;
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
    Shader() = delete;
    Shader(const char* vert_path, const char* frag_path){
        vert_shader = loadVertShader(vert_path);
        frag_shader = loadFragShader(frag_path);

        if(vert_shader != 0 && frag_shader !=0){
            ID = loadShaderProgram(vert_shader, frag_shader);
        }        

        glDeleteShader(vert_shader);
        glDeleteShader(frag_shader);        
    }
    GLuint ID = 0, vert_shader = 0, frag_shader = 0;

    public:      

    Shader operator=(Shader shader){
        shader.ID = Shader::ID;

        return shader;
    }

    GLuint id(){
        return ID;
    }

    void use(){
        glUseProgram(ID);
    }

    void setMat4(glm::mat4 mat, const char* name){
        GLuint loc = glGetUniformLocation(ID, name);
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));                        
    }

    void setVec3(glm::vec3 vec, const char* name){
        GLuint loc = glGetUniformLocation(ID, name);
        glUniform3fv(loc, 1, glm::value_ptr(vec));
    }

    void setFloat(float val, const char* name){        
        GLuint loc = glGetUniformLocation(ID, name);
        glUniform1f(loc, val);
    }

    void setInt(int val, const char* name){        
        GLuint loc = glGetUniformLocation(ID, name);
        glUniform1i(loc, val);
    }
    
    static Shader* createShader(const char* vert_path, const char* frag_path){
        Shader* shader = new Shader(vert_path, frag_path);
        return shader;
    }
};

#endif //__SHADER_H__
