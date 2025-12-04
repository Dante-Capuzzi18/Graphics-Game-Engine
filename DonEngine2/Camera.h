#ifndef CAMERA
#define CAMERA

#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <SDL2/SDL_opengl.h>
#include <iostream>

#include "SimObject.h"

//A scene object that displays the scene from a certain POV
class Camera : public SimObject
{
public:
    //CAMERA DATA
    float FOV, nearPlane, farPlane;
    int screenWidth;
    int screenHeight;

    //CAMERA MATRICES
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    //CONSTRUCTORS
    Camera(float FOV, float nearPlane, float farPlane, int screenHeight, int screenWidth);

    //TRANSFORM
    void SetPerspective(const char* id, float newValue); //will change a perspecive parameter for the camera, such as FOV
    void SetPerspective(float newFov, float newNearPlane, float newFarPlane);
    void SetScreenDimensions(int width, int height);

    //DRAW
    void Draw(ShaderProgram shaderProgram) override;
};

#endif // !CAMERA