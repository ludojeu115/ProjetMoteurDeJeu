#ifndef MATERIAL_CUSTOM_HPP
#define MATERIAL_CUSTOM_HPP
#include "common/Material/material.hpp"

class Custom_Material : public virtual Material {
protected:
    GLuint shader = 0;
public:
    [[maybe_unused]] void setShader(GLuint shader);

    [[maybe_unused]] void addTexture(const char *name, Texture *tex);

    void bindTextures() const;

    void bindShader() const;

    GLuint getShader() const;
};

#endif //MOTEUR_DE_JEU_CUSTOM_HPP
