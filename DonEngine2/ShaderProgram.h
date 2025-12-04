#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

//A module for the Program that holds shader information
class ShaderProgram
{
public:
    GLuint programID;

    //method to compile and create the shaders->shaderProgram with the default vertex and fragment shaders
    void CreateShaderProgram(const char* vertexFile, const char* fragmentFile);

    //destructor for the shader program object
    ~ShaderProgram();

    //gets the program id Gluint for this object
    GLuint GetThis() { return this->programID; }

    //activates the shader program
    void Use() const;

private:
    std::string get_file_contents(const char* filename);
};

#endif // SHADERPROGRAM_H