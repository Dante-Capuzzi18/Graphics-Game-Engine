#ifndef TEXTURE
#define TEXTURE

#include <string>

struct Texture 
{
    unsigned int id;
    std::string type;
    std::string path;

    Texture() : id() {};
};

#endif TEXTURE