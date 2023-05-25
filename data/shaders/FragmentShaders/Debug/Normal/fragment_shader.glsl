#version 330 core

in vec3 o_positionWorld;
in vec3 o_normalWorld;
in vec2 o_uv0;
out vec4 FragColor;


void main() {

    // DEBUG: normal
    //FragColor = vec4(1.0,0.0,0.0, 1.0);
    FragColor = vec4(0.5 * o_normalWorld + vec3(0.5) , 1.0);

}
