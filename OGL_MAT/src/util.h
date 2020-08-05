#include <stdio.h>
#include <stdlib.h> 

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
