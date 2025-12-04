#include "Camera.h"

Camera::Camera(float FOV, float nearPlane, float farPlane, int screenHeight, int screenWidth)
    : SimObject("MainCamera"), FOV(FOV), nearPlane(nearPlane), farPlane(farPlane), screenWidth(screenWidth), screenHeight(screenHeight), viewMatrix(glm::mat4(1.0f)), projectionMatrix(glm::mat4(1.0f))
{
    UpdateModelMatrix();
    this->SetPerspective(this->FOV, this->nearPlane, this->farPlane);
}

void Camera::SetPerspective(const char* id, float newValue)
{
    if (id == "FOV")
    {
        projectionMatrix = glm::perspective(glm::radians(newValue), (float)screenWidth / screenHeight, this->nearPlane, this->farPlane);
    }
    else if (id == "Near Plane")
    {
        projectionMatrix = glm::perspective(glm::radians(this->FOV), (float)screenWidth / screenHeight, newValue, this->farPlane);
    }
    else if (id == "Far Plane")
    {
        projectionMatrix = glm::perspective(glm::radians(this->FOV), (float)screenWidth / screenHeight, this->nearPlane, newValue);
    }
    else
    {
        std::cout << "Error with ChangePerspective(const char* id, float newValue), 'id' doesn't match any known types." << std::endl;
    }
}
void Camera::SetPerspective(float newFov, float newNearPlane, float newFarPlane)
{
    projectionMatrix = glm::perspective(glm::radians(newFov), (float)screenWidth / screenHeight, newNearPlane, newFarPlane);
}

void Camera::SetScreenDimensions(int width, int height)
{
    this->screenWidth = width;
    this->screenHeight = height;
}

void Camera::Draw(ShaderProgram shaderProgram)
{
    //passing in the view and projection matrices to the shader
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.programID, "view"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.programID, "proj"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    //calling Draw() for all children
    for (auto& child : children)
    {
        child->Draw(shaderProgram);
    }
}