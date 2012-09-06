#include <GL/glfw.h>
#include <iostream>

void loop();
void draw();

int main(int argc, char* argv[])
{
    glfwInit();
    glfwOpenWindow(640, 480, 0,0,0, 0,0,0, GLFW_WINDOW);
    glfwDisable(GLFW_MOUSE_CURSOR);

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
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

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

        draw();
        glfwSwapBuffers();
    }
}

void draw()
{
    float triangle1[] = {0.0, 0.0,   0.5, 0.0,   0.0, 0.5};
    float triangle2[] = {-0.8, -0.8,   -0.3, -0.8,   -0.8, -0.3};

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, triangle1);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, triangle2);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);

    glFlush();
}
