#include <GL/glfw.h>

void loop();
void draw();

int main(int argc, char* argv[])
{
    glfwInit();
    glfwOpenWindow(640, 480, 0,0,0, 0,0,0, GLFW_WINDOW);

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
    float t = 0;

    while (running) {
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslated(x,y,z);
        glRotated(t,0,1,0);

        draw();
        glfwSwapBuffers();

        if (glfwGetKey(GLFW_KEY_ESC)) {
            running = false;
        } else if (glfwGetKey('W')) {
            y += .0001;
        } else if (glfwGetKey('S')) {
            y -= .0001;
        } else if (glfwGetKey('D')) {
            x += .0001;
        } else if (glfwGetKey('A')) {
            x -= .0001;
        } else if (glfwGetKey('Q')) {
            t += .01;
        } else if (glfwGetKey('E')) {
            t -= .01;
        } else if (glfwGetKey('R')) {
            z -= .0001;
        } else if (glfwGetKey('F')) {
            z += .0001;
        }
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
