#ifndef MATERIAL_HEIGHTMAP_HPP
#define MATERIAL_HEIGHTMAP_HPP
#include "common/Material/Static/static.hpp"

class Heightmap_Material : public Static_Material {
public:
    Heightmap_Material(Texture * heightmap, Texture * texture1, Texture * texture2, Texture * texture3 );
};

#endif