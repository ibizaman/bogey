#version 110

varying float fade_factor;
uniform sampler2D texture0;
uniform sampler2D texture1;

varying vec2 texcoord;

void main()
{
    gl_FragColor = mix(
        texture2D(texture0, texcoord),
        texture2D(texture1, texcoord),
        fade_factor
    );
}
