#ifndef MESH
#define MESH


#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <stb/stb_image.h>
#include <vector>
#include <filesystem>
#include <string>
#include <vector>

#include "ShaderProgram.h"
#include "SimObject.h"

struct Vertex
{
    glm::vec3 position, normal;
    glm::vec2 texCoord;
};
struct Texture
{
    std::string textureName; //name of the material texture
    const char* fileName = ""; //name of the texture file, gotten from location/name.obj as name.obj
};

//Stores a vertex and texture data, also position and rotation
class Mesh : public SimObject
{
public:
    // CONSTRUCTOR
    Mesh(const char* name, std::vector<Vertex> vertices, std::vector<int> indices, Texture texture)
        : SimObject(name), vertices(vertices), indices(indices), texture(texture) //its name will be the same as the texture name without the extension
    {
        gladLoadGL();

        //------TEXTURE------
        // Load texture from image
        int width, height, channels;
        stbi_set_flip_vertically_on_load(true); // Flip the texture vertically if needed
        unsigned char* image = stbi_load((std::filesystem::current_path() / "Textures" / texture.fileName).string().c_str(), &width, &height, &channels, STBI_rgb_alpha);

        // Generate the texture buffer and the texture pointer
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);

        // Configures the type of algorithm that is used to make the image smaller or bigger
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Configures the way the texture repeats (if it does at all)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Generating the texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Unbind the texture and image file
        stbi_image_free(image);
        glBindTexture(GL_TEXTURE_2D, 0);

        //------VERTEX BUFFER ARRAYS------
        // Create and bind VAO
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // Create and bind VBO
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        // Create and bind IBO (optional if you're using indices)
        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

        //------VERTEX->INDEX ASSIGNMENTS------
        // Set vertex attribute pointers for position, texture coordinate, and normal
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);  // Position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));  // Texture
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));  // Normal
        glEnableVertexAttribArray(2);

        //------UNBINDING VERTEX ARRAYS------
        // Unbind VAO, VBO, and IBO
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    };

    // DRAW METHOD
    void Draw(ShaderProgram shaderProgram) override
    {
        //passing this model matrix to the shader
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.programID, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

        // Binding texture and VAO, then drawing the mesh
        glBindTexture(GL_TEXTURE_2D, texID);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        //unbinding the VAO and the texture
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Delete() override
    {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &IBO);
        glDeleteVertexArrays(1, &VAO);
        glDeleteTextures(1, &texID);
    }
private:
    // MESH DATA
    unsigned int VAO, VBO, IBO, texID;
    std::vector<Vertex> vertices;
    std::vector<int> indices;
    Texture texture;
};

#endif MESH