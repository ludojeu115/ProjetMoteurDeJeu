#version 330 core

in vec3 o_positionWorld;
in vec3 o_normalWorld;
in vec2 o_uv0;
out vec4 FragColor;

uniform vec4 color;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D heightMap;

void main() {
    float height = texture(heightMap, o_uv0).r;
    if(height<0.3) {
        FragColor = texture(texture1, o_uv0);
    } else if(height<0.6) {
        FragColor = texture(texture2, o_uv0);
    } else {
        FragColor = texture(texture3, o_uv0);
    }

}
