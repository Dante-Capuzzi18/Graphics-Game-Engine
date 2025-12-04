#include "SimObject.h"

//CONSTRUCTORS
SimObject::SimObject(const char* name)
    : name(name), position(glm::vec3(0.0f, 0.0f, 0.0f)), rotation(glm::vec3(0.0f, 0.0f, 0.0f)), scale(glm::vec3(1.0f, 1.0f, 1.0f)), modelMatrix(glm::mat4(1.0f))
{
    UpdateModelMatrix(glm::mat4(1.0));
}
SimObject::SimObject(const char* name, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : name(name), position(position), rotation(rotation), scale(scale), modelMatrix(glm::mat4(1.0f))
{
    UpdateModelMatrix(glm::mat4(1.0));
}

//MODEL MATRIX
void SimObject::UpdateModelMatrix(const glm::mat4& parent)
{
    //updates this transform
    glm::mat4 local = glm::mat4(1.0f);
    local = glm::translate(local, position);
    local = glm::rotate(local, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    local = glm::rotate(local, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    local = glm::rotate(local, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    local = glm::scale(local, scale);

    modelMatrix = parent * local;

    for (auto& child : children)
    {
        child->UpdateModelMatrix(modelMatrix);
    }
}

void SimObject::Translate(float x, float y, float z)
{
    this->position += glm::vec3(x, y, z);
    UpdateModelMatrix(glm::mat4(1.0));
}
void SimObject::Translate(glm::vec3 t)
{
    this->position += t;
    UpdateModelMatrix(glm::mat4(1.0));
}

void SimObject::Rotate(float x, float y, float z)
{
    this->rotation += glm::vec3(x, y, z);
    UpdateModelMatrix(glm::mat4(1.0));
}
void SimObject::Rotate(glm::vec3 r)
{
    this->rotation += r;
    UpdateModelMatrix(glm::mat4(1.0));
}

void SimObject::Scale(float x, float y, float z)
{
    this->scale *= glm::vec3(x, y, z);
    UpdateModelMatrix(glm::mat4(1.0));
}
void SimObject::Scale(glm::vec3 s)
{
    this->scale *= s;
    UpdateModelMatrix(glm::mat4(1.0));
}

void SimObject::SetPosition(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
    UpdateModelMatrix(glm::mat4(1.0));
}
void SimObject::SetPosition(glm::vec3 t)
{
    this->position = t;
    UpdateModelMatrix(glm::mat4(1.0));
}

void SimObject::SetRotation(float x, float y, float z)
{
    this->rotation = glm::vec3(x, y, z);
    UpdateModelMatrix(glm::mat4(1.0));
}
void SimObject::SetRotation(glm::vec3 r)
{
    this->rotation = r;
    UpdateModelMatrix(glm::mat4(1.0));
}

void SimObject::SetScale(float x, float y, float z)
{
    this->scale = glm::vec3(x, y, z);
    UpdateModelMatrix(glm::mat4(1.0));
}
void SimObject::SetScale(glm::vec3 s)
{
    this->scale = s;
    UpdateModelMatrix(glm::mat4(1.0));
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