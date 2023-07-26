/*
    Programming Challenge 2
    By: Zachary Que
*/

/* Include files */
#define STB_IMAGE_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#include "MainInclude.hpp"

// Models
#include "Model.hpp"

// Cameras
#include "MyCamera.hpp"
#include "PerspectiveCamera.hpp"
#include "OrthoCamera.hpp"

// Lights
#include "Light.hpp"
#include "DirectionLight.hpp"
#include "PointLight.hpp"

#include <iostream>

/* Namespaces */
using namespace models;
using namespace cameras;
using namespace lights;

/* Global Variables */
bool controllingMainObj = true;

bool rotatePosXAxis = false;
bool rotateNegXAxis = false;

bool rotatePosYAxis = false;
bool rotateNegYAxis = false;

bool rotatePosZAxis = false;
bool rotateNegZAxis = false;

bool space = false;

float x_axis_mod = 0.f;
float y_axis_mod = 0.f;
float z_axis_mod = 0.f;

bool changeProjection = false;
bool usePerspective = true;
bool useOrtho = false;

/* Keyboard Input Function */
void Key_Callback(
    GLFWwindow* window,
    int key,
    int scancode,
    int action,
    int mod) 
{
    float speed = 0.2f;

    /* Press Key */
    // W
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        rotatePosXAxis = true;
    // S
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        rotateNegXAxis = true;
    // A
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        rotatePosYAxis = true;
    // D
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        rotateNegYAxis = true;
    // Q
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        rotatePosZAxis = true;
    // E
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        rotateNegZAxis = true;
    // Space
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        space = true;
    // 1
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        usePerspective = true;
        useOrtho = false;
    }
    // 2
    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        usePerspective = false;
        useOrtho = true;
    }

    /* Release */
     // W
    if (key == GLFW_KEY_W && action == GLFW_RELEASE)
        rotatePosXAxis = false;
    // S
    if (key == GLFW_KEY_S && action == GLFW_RELEASE)
        rotateNegXAxis = false;
    // A
    if (key == GLFW_KEY_A && action == GLFW_RELEASE)
        rotatePosYAxis = false;
    // D
    if (key == GLFW_KEY_D && action == GLFW_RELEASE)
        rotateNegYAxis = false;
    // Q
    if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
        rotatePosZAxis = false;
    // E
    if (key == GLFW_KEY_E && action == GLFW_RELEASE)
        rotateNegZAxis = false;
    // Space
    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
        space = false;

    /* Update */
    // Change controlled object
    if (space)
        controllingMainObj = !controllingMainObj;



    // Main Obj
    if (controllingMainObj) {
        // Rotate along X axis
        if (rotatePosXAxis)
            x_axis_mod -= speed * 10;
        if (rotateNegXAxis)
            x_axis_mod += speed * 10;
        // Rotate along Y axis
        if (rotatePosYAxis)
            y_axis_mod += speed * 10;
        if (rotateNegYAxis)
            y_axis_mod -= speed * 10;
        // Rotate along Z axis
        if (rotatePosZAxis)
            z_axis_mod += speed * 10;
        if (rotateNegZAxis)
            z_axis_mod -= speed * 10;
    }
}

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    float width = 600.f;
    float height = 600.f;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow((int)width, (int)height, "Zachary Que", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();

    /* User Input */
    glfwSetKeyCallback(window, Key_Callback);

    glViewport(0, 0, (int)width, (int)height);

    /* Loading of 3D Models */
    // Main Object Model: https://www.cgtrader.com/items/3947399/download-page
    // Model y-axis offset is -4.5 to place it in the center
    Model objectModel = Model("3D/Object.obj", "3D/ObjectTexture.jpg", glm::vec3(0.f, -4.5f, 0.f), glm::vec3(7.f));
    // Light Source Model: https://www.cgtrader.com/items/3525927/download-page
    // Place Light Source Model -15 away from Main Object
    Model lightModel = Model("3D/Light.obj", "", glm::vec3(0.f, 0.f, -15.f), glm::vec3(3.f), glm::vec3(0.f), glm::vec4(238.f/255.f, 228.f/255.f, 170.f/255.f, 1.f));

    /* Load the vertex shader file into a string stream */
    std::fstream vertSrc("Shaders/sample.vert");
    std::stringstream vertBuff;
    // Add the file stream to the string stream
    vertBuff << vertSrc.rdbuf();
    // Convert the stream to a character array
    std::string vertS = vertBuff.str();
    const char* v = vertS.c_str();

    /* Load the fragment shader file into a string stream */
    std::fstream fragSrc("Shaders/sample.frag");
    std::stringstream fragBuff;
    // Add the file stream to the string stream
    fragBuff << fragSrc.rdbuf();
    // Convert the stream to a character array
    std::string fragS = fragBuff.str();
    const char* f = fragS.c_str();

    /* Create a vertex shader */
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Assign the source to the vertex shader
    glShaderSource(vertexShader, 1, &v, NULL);
    // Compile the vertex shader
    glCompileShader(vertexShader);

    /* Create a fragment shader */
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Assign the source to the fragment shader
    glShaderSource(fragShader, 1, &f, NULL);
    // Compile the fragment shader
    glCompileShader(fragShader);

    /* Create the shader program */
    GLuint shaderProgram = glCreateProgram();
    // Attach the compiled vertex shader
    glAttachShader(shaderProgram, vertexShader);
    // Attach the compiled fragment shader
    glAttachShader(shaderProgram, fragShader);
    // Finalize the compilation of the shaders
    glLinkProgram(shaderProgram);
    // Use the shader program
    glUseProgram(shaderProgram);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the depth buffer as well

        /* Camera (view/projection) to be used */
        MyCamera* camera = NULL;
        if (usePerspective) {
            PerspectiveCamera perspectiveCamera = PerspectiveCamera(60.f, height, width, 0.1f, 100.f,
                glm::vec3(0.f, 0.f, 15.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, -5.f));
            camera = &perspectiveCamera;
        }
        if (useOrtho) {
            OrthoCamera orthoCamera = OrthoCamera(-20.f, 20.f, -20.f, 20.f, -50.f, 100.f,
                glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, -10.f, 0.f));
            camera = &orthoCamera;
        }

        // If projection camera exists, use the projection camera's values
        if (camera != NULL) {
            /* VIEW MATRIX */
            camera->updateViewMatrix();
            unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
            glUniformMatrix4fv(viewLoc,
                1,
                GL_FALSE,
                glm::value_ptr(camera->getViewMatrix())
            );

            /* PROJECTION MATRIX */
            unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");
            glUniformMatrix4fv(projLoc,
                1,
                GL_FALSE,
                glm::value_ptr(camera->getProjMatrix())
            );
        }

        /* Lighting variables */
        glm::vec3 cameraPos = camera->getPos();
        /* Light variables */
        glm::vec3 lightPos = glm::vec3(4, 11, -3);
        glm::vec3 lightColor = glm::vec3(1, 1, 1);

        /* Ambient variables */
        // Ambient strength
        float ambientStr = 0.1f;
        // Ambient Color
        glm::vec3 ambientColor = lightColor;

        /* Specular variables */
        // Spec strength
        float specStr = 0.5f;
        // Spec phong
        float specPhong = 16;
        // Light pos address
        GLuint lightAddress = glGetUniformLocation(shaderProgram, "lightPos");
        glUniform3fv(lightAddress, 1, glm::value_ptr(lightPos));
        // Light Color 
        GLuint lightColorAddress = glGetUniformLocation(shaderProgram, "lightColor");
        glUniform3fv(lightColorAddress, 1, glm::value_ptr(lightColor));

        /* Ambient variables */
        // Ambient str address
        GLuint ambientStrAddress = glGetUniformLocation(shaderProgram, "ambientStr");
        glUniform1f(ambientStrAddress, ambientStr);
        // Light Color 
        GLuint ambientColorAddress = glGetUniformLocation(shaderProgram, "ambientColor");
        glUniform3fv(lightColorAddress, 1, glm::value_ptr(lightColor));

        /* Specular variables */
        // Get the address of the camera pos from the shader
        GLuint cameraPosAddress = glGetUniformLocation(shaderProgram, "cameraPos");
        glUniform3fv(cameraPosAddress, 1, glm::value_ptr(cameraPos));
        // Get the address of the spec str from the shader
        GLuint specStrAddress = glGetUniformLocation(shaderProgram, "specStr");
        glUniform1f(specStrAddress, specStr);
        // Get the address of the spec phong from the shader
        GLuint specPhongAddress = glGetUniformLocation(shaderProgram, "specPhong");
        glUniform1f(specPhongAddress, specPhong);

        /* Draw Light Object */
        /* Update Light Object */
        // Light source not selected
        if (controllingMainObj)
            lightModel.setColor(glm::vec4(238.f / 255.f, 228.f / 255.f, 170.f / 255.f, 1.f));
        // Light source selected
        else
            lightModel.setColor(glm::vec4(1.f, 1.f, 0.f, 1.f));

        GLuint colorAddress = glGetUniformLocation(shaderProgram, "color");
        glUniform4fv(colorAddress, 1, glm::value_ptr(lightModel.getColor()));
        lightModel.draw(&shaderProgram);

        // Reset shader program color
        glUniform4fv(colorAddress, 1, glm::value_ptr(objectModel.getColor()));

        /* Draw Main Object */
        /* Update Main Object */
        if (controllingMainObj)
            objectModel.setRotation(glm::vec3(objectModel.getRotation().x + x_axis_mod,
                objectModel.getRotation().y + y_axis_mod,
                objectModel.getRotation().z + z_axis_mod));
        x_axis_mod = 0.f;
        y_axis_mod = 0.f;
        z_axis_mod = 0.f;
        objectModel.draw(&shaderProgram);

        // Reset shader program lighting


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}