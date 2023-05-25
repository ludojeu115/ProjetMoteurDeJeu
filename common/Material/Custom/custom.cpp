#include "common/Material/Custom/custom.hpp"

[[maybe_unused]] void Custom_Material::addTexture(const char *name, Texture *tex) { this->textures.emplace_back(name, tex); };

[[maybe_unused]] void Custom_Material::setShader(const GLuint shader) { this->shader = shader; }

void Custom_Material::bindTextures() const{
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

void Custom_Material::bindShader() const {
    glUseProgram(shader);
}

[[maybe_unused]] GLuint Custom_Material::getShader() const {
    return shader;
}
