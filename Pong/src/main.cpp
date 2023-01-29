#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "shader.h"
#include "util.h"
#include "GameEngine.h"
#include "TextRenderer.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

const unsigned int  WIDTH = 800;
const unsigned int  HEIGHT = 600;


//Loop Control
float deltaTime = 0.0f;
float lastFrame = 0.0f;


//Process Input
bool switchCase = false;
float alpha = 0.2;

//Camera Control
//Camera camera = Camera();
bool firstMouse = true;
float lastX = 400, lastY = 300;

int temp = 0;

GameEngine engine(HEIGHT, WIDTH);
int main(void)
{
    //Instantiating the GLFW window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    //glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    //Creating a window object
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    //Initializing GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, WIDTH, HEIGHT);
    stbi_set_flip_vertically_on_load(true);


    void framebuffer_size_callback(GLFWwindow * window, int width, int height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();



    //OPENGL SETTINGS
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    engine.init();
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    while (!glfwWindowShouldClose(window))
    {
       // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float currentFrame = glfwGetTime();
        int test = (int)currentFrame;
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        //wireframe = true;

        //input
        glfwSetKeyCallback(window, key_callback);
        engine.main_loop(deltaTime, test);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}




void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
  

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        engine.keys[GLFW_KEY_UP] = true;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        engine.keys[GLFW_KEY_DOWN] = true;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        engine.keys[GLFW_KEY_W] = true;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        engine.keys[GLFW_KEY_S] = true;
    }

    if (glfwGetKey(window, GLFW_KEY_TAB)) {
        engine.keys[GLFW_KEY_TAB] = true;
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_RELEASE)
            engine.keys[key] = false;
    }

}
