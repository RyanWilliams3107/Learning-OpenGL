#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "Shader.h"
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}



int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);



    if (glewInit() != GLEW_OK) {
        std::cout << "Error!" << std::endl;
    }

    Shader vs("../OpenGL/shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
    GLuint vertexShader = vs.getShader();

    Shader fs("../OpenGL/shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);
    GLuint fragmentShader = fs.getShader();

    ShaderProgram shaderProgram(vertexShader, fragmentShader);

    shaderProgram.linkShaderProgram();

    vs.~Shader();
    vs.~Shader();

    float positions[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f, 0.5f, 0.0f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
        3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        processInput(window);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.useShaderProgram();
        glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

#ifdef _WIN32
    FreeConsole();
#endif
    return 0;
}