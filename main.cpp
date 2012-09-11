#include <GL/glew.h>
#include <GL/glfw.h>
#include <cmath>
#include "shader/load.h"
#include "texture/load.h"
#include "object/load.h"
#include <iostream>

void loop();
void render();
int make_resources(const char *vertex_shader_file);
void  update_timer();

struct Resources
{
    GLuint vertex_buffer, element_buffer;
    GLuint textures[2];

    GLuint vertex_shader, fragment_shader, program;
    
    struct {
        GLint timer;
        GLint textures[2];
    } uniforms;

    struct {
        GLint position;
    } attributes;

    GLfloat timer;
} resources;

static const GLfloat vertex_buffer_data[] = { 
    -1.0f, -1.0f, 0.0f, 1.0f,
	 1.0f, -1.0f, 0.0f, 1.0f,
	-1.0f,  1.0f, 0.0f, 1.0f,
	 1.0f,  1.0f, 0.0f, 1.0f
};
static const GLushort element_buffer_data[] = { 0, 1, 2, 3 };

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;
    glfwInit();
    glfwOpenWindow(400, 300, 0,0,0, 0,0,0, GLFW_WINDOW);
    glfwDisable(GLFW_MOUSE_CURSOR);
    glfwSetTime(0);
    glewInit();

    int resources_ok = make_resources(argc >= 2 ? argv[1] : "shader/hello.vert");
    if (!resources_ok) {
        std::cerr << "Resources not correctly loaded" << std::endl;
        return 1;
    }
    loop();

    glfwCloseWindow();
    glfwTerminate();
}

void loop()
{
    bool running = true;
    float x = 0;
    float y = 0;
    float z = 0;

    int m_x = 0;
    int m_y = 0;
    float t_x = 0;
    float t_y = 0;

    while (running) {
        glClear(GL_COLOR_BUFFER_BIT);

        if (glfwGetKey(GLFW_KEY_ESC)) {
            running = false;
        } else if (glfwGetKey('W')) {
            z += .0001;
        } else if (glfwGetKey('S')) {
            z -= .0001;
        } else if (glfwGetKey('D')) {
            x += .0001;
        } else if (glfwGetKey('A')) {
            x -= .0001;
        }

        glTranslated(x,y,z);

        int old_m_x = m_x;
        int old_m_y = m_y;
        glfwGetMousePos(&m_x, &m_y);

        float speed = 2.5;
        if (m_x - old_m_x > 0) {
            t_x += speed;
        } else if (m_x - old_m_x < 0) {
            t_x -= speed;
        }

        if (m_y - old_m_y > 0) {
            t_y += speed;
        } else if (m_y - old_m_y < 0) {
            t_y -= speed;
        }
        if (t_y > 89) {
            t_y = 89;
        } else if (t_y < -89) {
            t_y = -89;
        }
        glRotated(t_x, 0,1,0);
        glRotated(t_y, 1,0,0);

        update_timer();

        render();
        glfwSwapBuffers();
    }
}

void render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
    glUseProgram(resources.program);

    glUniform1f(resources.uniforms.timer, resources.timer);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, resources.textures[0]);
    glUniform1i(resources.uniforms.textures[0], 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, resources.textures[1]);
    glUniform1i(resources.uniforms.textures[1], 1);

    glBindBuffer(GL_ARRAY_BUFFER, resources.vertex_buffer);
    glVertexAttribPointer(
        resources.attributes.position,    /* attribute */
        4,                                /* size */
        GL_FLOAT,                         /* type */
        GL_FALSE,                         /* normalized? */
        sizeof(GLfloat)*4,                /* stride */
        (void*)0                          /* array buffer offset */
    );
    glEnableVertexAttribArray(resources.attributes.position);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resources.element_buffer);
    glDrawElements(
        GL_TRIANGLE_STRIP,  /* mode */
        4,                  /* count */
        GL_UNSIGNED_SHORT,  /* type */
        (void*)0            /* element array buffer offset */
    );

    glDisableVertexAttribArray(resources.attributes.position);
}

int make_resources(const char *vertex_shader_file)
{
    resources.vertex_buffer = make_buffer(
        GL_ARRAY_BUFFER,
        vertex_buffer_data,
        sizeof(vertex_buffer_data)
    );
    resources.element_buffer = make_buffer(
        GL_ELEMENT_ARRAY_BUFFER,
        element_buffer_data,
        sizeof(element_buffer_data)
    );

    resources.textures[0] = make_texture("texture/hello1.tga");
    resources.textures[1] = make_texture("texture/hello2.tga");
    if (resources.textures[0] == 0 || resources.textures[1] == 0) {
        return 0;
    }
    resources.vertex_shader = make_shader(
        GL_VERTEX_SHADER,
        vertex_shader_file
    );
    if (resources.vertex_shader == 0) {
        return 0;
    }

    resources.fragment_shader = make_shader(
        GL_FRAGMENT_SHADER,
        "shader/hello.frag"
    );
    if (resources.fragment_shader == 0) {
        return 0;
    }

    resources.program = make_program(
        resources.vertex_shader,
        resources.fragment_shader
    );
    if (resources.program == 0) {
        return 0;
    }

    resources.uniforms.timer
        = glGetUniformLocation(resources.program, "timer");
    resources.uniforms.textures[0]
        = glGetUniformLocation(resources.program, "textures[0]");
    resources.uniforms.textures[1]
        = glGetUniformLocation(resources.program, "textures[1]");

    resources.attributes.position
        = glGetAttribLocation(resources.program, "position");

    return 1;
}

void update_timer()
{
    float time = (float)glfwGetTime();
    resources.timer = time;
}
