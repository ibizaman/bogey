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

    while (running) {
        draw();
        glfwSwapBuffers();

        if (glfwGetKey(GLFW_KEY_ESC)) {
            running = false;
        }
    }
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

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
