#include "load.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

GLuint make_shader(GLenum type, const char* file_path)
{
    std::ifstream in(file_path);
    std::stringstream buffer;
    buffer << in.rdbuf();

    std::string source = buffer.str();
    GLint length = source.length();

    GLuint shader = glCreateShader(type);
    const char* source_char = source.c_str();
    glShaderSource(shader, 1, &source_char, &length);
    glCompileShader(shader);

    GLint shader_ok;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);

    if (!shader_ok) {
        std::cerr << "Failed to compile shader " << file_path << std::endl;
        std::cerr << source << std::endl;

        int log_length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

        std::vector<char> error_message(log_length);
        glGetShaderInfoLog(shader, log_length, NULL, &error_message[0]);
        std::cerr << &error_message[0] << std::endl;

        glDeleteShader(shader);
        return 0;
    }
 
    return shader;
}

GLuint make_program(GLuint vertex_shader, GLuint fragment_shader)
{
    GLint program_ok;

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &program_ok);
    if (!program_ok) {
        std::cerr << "Failed to link shader program" << std::endl;

        int log_length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

        std::vector<char> error_message(log_length);
        glGetProgramInfoLog(program, log_length, NULL, &error_message[0]);
        std::cerr << &error_message[0] << std::endl;

        glDeleteProgram(program);
        return 0;
    }

    return program;
}
