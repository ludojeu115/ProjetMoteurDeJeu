#include "heightmap.hpp"


[[maybe_unused]] Heightmap_Material::Heightmap_Material(Texture *heightmap, Texture *texture1, Texture *texture2, Texture *texture3) {
    vertexShaderPath="vertex_shader.glsl";
    fragmentShaderPath="HeightMap/fragment_shader.glsl";
    loadShader();
    textures.clear();
    textures.push_back(ShaderTexturePair("Heightmap", heightmap));
    textures.push_back(ShaderTexturePair("texture1", texture1));
    textures.push_back(ShaderTexturePair("texture2", texture2));
    textures.push_back(ShaderTexturePair("texture3", texture3));

}
GLuint Static_Material::shader=0;