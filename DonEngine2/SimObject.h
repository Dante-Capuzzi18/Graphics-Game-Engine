#ifndef SIMOBJECT_H
#define SIMOBJECT_H

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <vector>

#include "ShaderProgram.h"

//A scene object that exists in world space
class SimObject
{
public:
    //TRANSFORM DATA
    const char* name;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 modelMatrix;

    //TREES/SCRIPT DATA
    std::vector<SimObject*> children;
    //std::vector<Scriptable> scripts;

    //CONSTRUCTORS
    SimObject(const char* name); //will make an object at the origin
    SimObject(const char* name, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale); //will make a new object at pos/rot/scl

    //MODEL MATRIX
    void UpdateModelMatrix(); //updates this model matrix and then updates all children matrices

    //TRANSFORM
    void Translate(float x, float y, float z); //will move the object in world space
    void Translate(glm::vec3 t);
    void Rotate(float x, float y, float z); //will rotate the object
    void Rotate(glm::vec3 r);
    void Scale(float x, float y, float z); //will scale the object
    void Scale(glm::vec3 s);
    void SetPosition(float x, float y, float z); //sets the position of the object in world space
    void SetPosition(glm::vec3 t);
    void SetRotation(float x, float y, float z); //sets the rotation of the object
    void SetRotation(glm::vec3 r);
    void SetScale(float x, float y, float z); //sets the scale of the object
    void SetScale(glm::vec3 s);

    //CHILDREN
    void AddChild(SimObject* child);

    //CLEANUP
    virtual void Delete();

    //VIRTUAL METHODS
    virtual void Draw(ShaderProgram shaderProgram); //Used in Model, Camera

    //CHECKERS
    virtual bool IsMesh() const { return false; }  //Used for checking if its a Mesh
};

#endif SIMOBJECT_H