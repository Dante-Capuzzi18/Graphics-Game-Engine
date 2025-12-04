#include "SimObject.h"

//CONSTRUCTORS
SimObject::SimObject(const char* name)
    : name(name), position(glm::vec3(0.0f, 0.0f, 0.0f)), rotation(glm::vec3(0.0f, 0.0f, 0.0f)), scale(glm::vec3(1.0f, 1.0f, 1.0f)), modelMatrix(glm::mat4(1.0f))
{
    UpdateModelMatrix();
}
SimObject::SimObject(const char* name, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : name(name), position(position), rotation(rotation), scale(scale), modelMatrix(glm::mat4(1.0f))
{
    UpdateModelMatrix();
}

//MODEL MATRIX
void SimObject::UpdateModelMatrix()
{
    //updates this transform
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, scale);

    for (auto& child : children)
    {
        child->UpdateModelMatrix();

        child->modelMatrix = modelMatrix * child->modelMatrix;
    }
}

void SimObject::Translate(float x, float y, float z)
{
    this->position += glm::vec3(x, y, z);
    UpdateModelMatrix();
}
void SimObject::Translate(glm::vec3 t)
{
    this->position += t;
    UpdateModelMatrix();
}

void SimObject::Rotate(float x, float y, float z)
{
    this->rotation += glm::vec3(x, y, z);
    UpdateModelMatrix();
}
void SimObject::Rotate(glm::vec3 r)
{
    this->rotation += r;
    UpdateModelMatrix();
}

void SimObject::Scale(float x, float y, float z)
{
    this->scale *= glm::vec3(x, y, z);
    UpdateModelMatrix();
}
void SimObject::Scale(glm::vec3 s)
{
    this->scale *= s;
    UpdateModelMatrix();
}

void SimObject::SetPosition(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
    UpdateModelMatrix();
}
void SimObject::SetPosition(glm::vec3 t)
{
    this->position = t;
    UpdateModelMatrix();
}

void SimObject::SetRotation(float x, float y, float z)
{
    this->rotation = glm::vec3(x, y, z);
    UpdateModelMatrix();
}
void SimObject::SetRotation(glm::vec3 r)
{
    this->rotation = r;
    UpdateModelMatrix();
}

void SimObject::SetScale(float x, float y, float z)
{
    this->scale = glm::vec3(x, y, z);
    UpdateModelMatrix();
}
void SimObject::SetScale(glm::vec3 s)
{
    this->scale = s;
    UpdateModelMatrix();
}

//CHILDREN
void SimObject::AddChild(SimObject* child)
{
    children.push_back(child);
}

//CLEANUP
void SimObject::Delete() {} // releases all data and deletes the object

//VIRTUAL METHODS
void SimObject::Draw(ShaderProgram shaderProgram)
{
    //passing this model matrix to the shader
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.programID, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

    //calling Draw() for all children
    for (auto& child : children)
    {
        child->Draw(shaderProgram);
    }
}