#ifndef MATERIAL_STATIC_HPP
#define MATERIAL_STATIC_HPP
#include "common/Material/material.hpp"

class Static_Material : public virtual Material {
protected:
    static GLuint shader;
    const char *vertexShaderPath ="vertex_shader.glsl";//default vertex shader
    const char *fragmentShaderPath = "Debug/Normal/fragment_shader.glsl";//default fragment shader
    void loadShader();
public:

    Static_Material();

    void bindTextures() const override;

    void bindShader() const override;

    GLuint getShader() const override;
};



#endif