#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "sender.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "offscreen.hpp"

void OnWindoSizeChangedCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void OnKeyboardInput(GLFWwindow* window)
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}


int main()
{
    int width = 800;
    int height = 600;

    // init glfw
    if(glfwInit()==GL_FALSE)
    {
        std::cerr << "can't initialize glfw" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(width, height, "ImageSharingSystem", NULL, NULL);
    if(window==NULL)
    {
        std::cerr << "failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    // init glew
    if(glewInit()!=GLEW_OK)
    {
        std::cerr << "can't initialize glew" << std::endl;
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, 800, 600);


    // set callback func
    glfwSetFramebufferSizeCallback(window, OnWindoSizeChangedCallback);


    // vertex buffer
    // generate vao
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    //generate vbo
    float vertices[] = {
        //positions         //colors          //texture coordinates
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



    Texture texture("../img/texture.png", true);
    Offscreen offscreen(width, height);
    Shader shader("../shader/triangle.vert", "../shader/triangle.frag");
    // position attribute
    GLint position = glGetAttribLocation(shader.GetProgram(), "aPosition");
    glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(position);
    // color attribute
    GLint color = glGetAttribLocation(shader.GetProgram(), "aColor");
    glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(color);
    // texture attribute
    GLint texCoord = glGetAttribLocation(shader.GetProgram(), "aTexCoord");
    glVertexAttribPointer(texCoord, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(texCoord);


    // prepare spout
    Sender sender(width, height);

    while(!glfwWindowShouldClose(window))
    {
        // check input
        OnKeyboardInput(window);

        // rendering process
        glClearColor(0.7f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw event
        // set uniform
        shader.Use();
        float time = glfwGetTime();
        float color = (sin(time) / 2.0f) + 0.5f;
        glm::vec4 inColor = glm::vec4(0.1f, color, 0.0f, 1.0f);
        shader.SetVec4("uniformColor", inColor);

        texture.Bind();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        sender.Connect(offscreen.GetFrameBuffer());
    }

    // release resources
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);

    // processing on exit
    glfwTerminate();
    return 0;
}