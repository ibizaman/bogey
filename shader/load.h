#ifndef SHADER_LOAD_H
#define SHADER_LOAD_H

#include <OpenGL/gl.h>

GLuint make_shader(GLenum type, const char*);
GLuint make_program(GLuint, GLuint);

#endif
