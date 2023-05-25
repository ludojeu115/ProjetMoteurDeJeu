#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdexcept> // pour std::runtime_error
class Texture
{
private:
    GLuint textureID{};
    int width{}, height{}, nbChannels{};
    unsigned char *data{};
    std::string path;
    bool loaded = false;
    bool hasGLComponent = false;
    void createGLTexture();
public:
    explicit Texture(const std::string& path);
    ~Texture();

    void load();
    void bind();
    [[nodiscard]] GLuint getID() const;
    [[nodiscard]] bool isLoaded() const;
    [[maybe_unused]] [[nodiscard]] int getWidth() const;
    [[maybe_unused]] [[nodiscard]] int getHeight() const;
    [[maybe_unused]] [[nodiscard]] glm::vec3 getPixel(int x, int y) const;




};

[[maybe_unused]] GLuint LoadTexture(const std::string& path);

#endif