#version 110

uniform float timer;
attribute vec4 position;

varying vec2 texcoord;
varying float fade_factor;

void main()
{
    mat3 window_scale = mat3(
        vec3(3.0/4.0, 0.0, 0.0),
        vec3(    0.0, 1.0, 0.0),
        vec3(    0.0, 0.0, 1.0)
    );
    mat3 rotation = mat3(
        vec3( cos(timer),  sin(timer),  0.0),
        vec3(-sin(timer),  cos(timer),  0.0),
        vec3(        0.0,         0.0,  1.0)
    );
    gl_Position = gl_ModelViewProjectionMatrix * vec4(window_scale * rotation * position.xyz, 1.0);
    texcoord = position.xz;
    fade_factor = sin(timer) * 0.5 + 0.5;
}
