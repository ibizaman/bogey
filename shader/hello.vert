#version 110

uniform float timer;
attribute vec4 position;

varying vec2 texcoord;
varying float fade_factor;

void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * position;
    texcoord = vec2(position.x/4.0 + 0.5, position.y/3.0 + 0.5);
    fade_factor = sin(timer-1.57) * 0.5 + 0.5;
}
