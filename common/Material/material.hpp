#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <vector>
#include <utility>

#include "common/Texture/texture.hpp"

#include <GL/glew.h>

typedef std::pair<const char *, Texture *> ShaderTexturePair;

class Material {

protected:

    std::vector<ShaderTexturePair> textures;
public:
    Material() = default;

    ~Material() = default;

    virtual void bindTextures() const = 0;

    virtual void bindShader() const = 0;

    virtual GLuint getShader() const = 0;
};

#endif