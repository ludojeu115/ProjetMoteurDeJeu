#include "texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "common/DataLoaders/Image/stb_image.h"
void Texture::createGLTexture()
{
    if (!loaded)
        load();

    glGenTextures(1, &textureID);
    if (textureID == 0 || !data)
    {
        throw std::runtime_error("Invalid texture data or ID");
    }
    glBindTexture(GL_TEXTURE_2D, textureID);

    GLenum format;
    switch (nbChannels) {
        case 1:
            format = GL_LUMINANCE;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
        default:
            format = GL_RGBA;
            break;

    }

    glTexImage2D(GL_TEXTURE_2D, 0, (GLint)format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error("Failed to create texture: " + std::to_string(error));
    }

    if ((width & (width - 1)) == 0 && (height & (height - 1)) == 0) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    error = glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error("Failed to generate Mipmap: " + std::to_string(error));
    }


    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    hasGLComponent = true;
}

void Texture::load()
{
    stbi_set_flip_vertically_on_load(true);
//    std::cout << "Loading texture: " << path << std::endl;
    data = stbi_load(("data/textures/"+path).c_str(), &width, &height, &nbChannels, 0);
//    std::cout << "  width: " << width << std::endl;
//    std::cout << "  height: " << height << std::endl;
//    std::cout << "  nbChannels: " << nbChannels << std::endl;
    if (data)
    {

        loaded = true;
    }
    else
    {
        throw std::runtime_error("Failed to load texture: " + path);
    }
}

bool Texture::isLoaded() const
{
    return loaded;
}

void Texture::bind()
{
    if (!isLoaded())
    {
        load();
        loaded = true;
    }
    glBindTexture(GL_TEXTURE_2D, textureID);
}


GLuint Texture::getID() const
{
    if (!loaded || !hasGLComponent)
    {
        // error
        throw std::runtime_error("Texture not loaded or no GL data");
    }
    return textureID;
}

[[maybe_unused]] int Texture::getWidth() const
{
    return width;
}

[[maybe_unused]] int Texture::getHeight() const
{
    return height;
}

[[maybe_unused]] glm::vec3 Texture::getPixel(int x, int y) const
{

    assert(data);
    if (x < 0 || x >= width || y < 0 || y >= height)
        return {0, 0, 0};
    if (nbChannels == 1) // grayscale
    {
        unsigned char *pixel = data + (y * width + x);
        return {(float)pixel[0] / 255.0f, (float)pixel[0] / 255.0f, (float)pixel[0] / 255.0f};
    }

    if (nbChannels<3)
        return {0, 0, 0};

    size_t p = (y * width + x) * nbChannels;
    return {(float)data[p] / 255.0f, (float)data[p + 1] / 255.0f, (float)data[p + 2] / 255.0f};


}

Texture::~Texture()
{
    if (loaded)
    {
        stbi_image_free(data);
    }
    if (hasGLComponent)
    {
        glDeleteTextures(1, &textureID);
    }
}

Texture::Texture(const std::string &path) {
    this->path = path;
    load();
    createGLTexture();
}

[[maybe_unused]] GLuint LoadTexture(const std::string &path) {
    Texture tex(path);
    return tex.getID();
}
