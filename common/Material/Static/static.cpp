#include "common/Material/Static/static.hpp"
#include "common/Shaders/shader.hpp"
void Static_Material::bindTextures() const{
    for (int i = 0; i < textures.size(); i++) {
        GLuint textureID = textures[i].second->getID();
        if (textureID != 0) {
            GLint textureLoc = glGetUniformLocation(shader, textures[i].first);
            if (textureLoc != -1) {
                glUniform1i(textureLoc, i);
            } else {
                //std::cerr << "Uniform variable "<< i <<": " << textures[i].first << " not found in shader ( might have been optimised)" << std::endl;
            }
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, textureID);
        } else {
            std::cerr << "Invalid texture ID for " << textures[i].first << std::endl;
        }
    }
}

void Static_Material::bindShader() const {
    glUseProgram(shader);
}

GLuint Static_Material::getShader() const {
    return shader;
}

void Static_Material::loadShader() {
    if(shader==0){
        shader = LoadShaders(vertexShaderPath, fragmentShaderPath);
    }
}

Static_Material::Static_Material() : vertexShaderPath("vertex_shader.glsl"), fragmentShaderPath("Debug/UV/fragment_shader.glsl") {}