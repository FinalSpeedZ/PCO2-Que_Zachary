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

bool increasePointLightIntensity = false;
bool decreasePointLightIntensity = false;
bool increaseDirectionLightIntensity = false;
bool decreaseDirectionLightIntensity = false;
float intensity_mod = 0.f;

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
    // arrow up
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        increasePointLightIntensity = true;
    // arrow down
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        decreasePointLightIntensity = true;
    // arrow left
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
        decreaseDirectionLightIntensity = true;
    // arrow right
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        increaseDirectionLightIntensity = true;

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
    // arrow up
    if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
        increasePointLightIntensity = false;
    // arrow down
    if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
        decreasePointLightIntensity = false;
    // arrow left
    if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
        decreaseDirectionLightIntensity = false;
    // arrow right
    if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
        increaseDirectionLightIntensity = false;

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
    // Controlling Light Source
    else
        if (increasePointLightIntensity) {
            intensity_mod += speed / 100.f;
            std::cout << "increase" << std::endl;
        }
        
        if (decreasePointLightIntensity) {
            intensity_mod -= speed / 100.f;
            std::cout << "decrease" << std::endl;
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
    Model lightModel = Model("3D/Light.obj", "", glm::vec3(10.f, 10.f, -15.f), glm::vec3(5.f), glm::vec3(0.f), glm::vec4(238.f/255.f, 228.f/255.f, 170.f/255.f, 1.f));

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

    /* Light Sources */
    // Direction Light: Position is at 4, 11, -3; Points at 0, 0, 0
    DirectionLight directionLight = DirectionLight(glm::vec3(4.f, 11.f, -3.f), glm::vec3(0.f), glm::vec3(1.f), 10.f);
    // Point Light: Position is at position of lightModel; color is color of lightModel
    PointLight pointLight = PointLight(lightModel.getPosition(), lightModel.getColor());

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

        /* Light Sources */
        // Direction Light
        directionLight.setMultiplier(directionLight.getMultiplier());
        // Point Light
        pointLight.setPos(lightModel.getPosition());
        pointLight.setColor(lightModel.getColor());
        
        /* Lighting in Shader Program */
        /* Direction Light */
        // Exists
        GLuint dl_existsAddress = glGetUniformLocation(shaderProgram, "dl_exists");
        glUniform1f(dl_existsAddress, false);
        // Direction
        GLuint dl_directionAddress = glGetUniformLocation(shaderProgram, "dl_direction");
        glUniform3fv(dl_directionAddress, 1, glm::value_ptr(directionLight.getDirection()));
        // Color
        GLuint dl_colorAddress = glGetUniformLocation(shaderProgram, "dl_color");
        glUniform3fv(dl_colorAddress, 1, glm::value_ptr(directionLight.getColor()));
        // Multiplier
        GLuint dl_multiplierAddress = glGetUniformLocation(shaderProgram, "dl_multiplier");
        glUniform1f(dl_multiplierAddress, directionLight.getMultiplier());
        // AmbientStr
        GLuint dl_ambientStrAddress = glGetUniformLocation(shaderProgram, "dl_ambientStr");
        glUniform1f(dl_ambientStrAddress, directionLight.getAmbientStr());
        // AmbientColor
        GLuint dl_ambientColorAddress = glGetUniformLocation(shaderProgram, "dl_ambientColor");
        glUniform3fv(dl_ambientColorAddress, 1, glm::value_ptr(directionLight.getAmbientColor()));
        // SpecStr
        GLuint dl_specStrAddress = glGetUniformLocation(shaderProgram, "dl_specStr");
        glUniform1f(dl_specStrAddress, directionLight.getSpecStr());
        // SpecPhong
        GLuint dl_specPhongAddress = glGetUniformLocation(shaderProgram, "dl_specPhong");
        glUniform1f(dl_specPhongAddress, directionLight.getSpecPhong());

        /* Point Light */
        // Exists
        GLuint pl_existsAddress = glGetUniformLocation(shaderProgram, "pl_exists");
        glUniform1f(pl_existsAddress, true);
        // Pos
        GLuint pl_posAddress = glGetUniformLocation(shaderProgram, "pl_pos");
        glUniform3fv(pl_posAddress, 1, glm::value_ptr(pointLight.getPos()));
        // Color
        GLuint pl_colorAddress = glGetUniformLocation(shaderProgram, "pl_color");
        glUniform3fv(pl_colorAddress, 1, glm::value_ptr(pointLight.getColor()));
        // Multiplier
        GLuint pl_multiplierAddress = glGetUniformLocation(shaderProgram, "pl_multiplier");
        glUniform1f(pl_multiplierAddress, pointLight.getMultiplier());
        // AmbientStr
        GLuint pl_ambientStrAddress = glGetUniformLocation(shaderProgram, "pl_ambientStr");
        glUniform1f(pl_ambientStrAddress, pointLight.getAmbientStr());
        // AmbientColor
        GLuint pl_ambientColorAddress = glGetUniformLocation(shaderProgram, "pl_ambientColor");
        glUniform3fv(pl_ambientColorAddress, 1, glm::value_ptr(pointLight.getAmbientColor()));
        // SpecStr
        GLuint pl_specStrAddress = glGetUniformLocation(shaderProgram, "pl_specStr");
        glUniform1f(pl_specStrAddress, pointLight.getSpecStr());
        // SpecPhong
        GLuint pl_specPhongAddress = glGetUniformLocation(shaderProgram, "pl_specPhong");
        glUniform1f(pl_specPhongAddress, pointLight.getSpecPhong());

        /* Update Point Light Intensity */
        if (!controllingMainObj) {
            if (increasePointLightIntensity) {
                pointLight.setMultiplier(pointLight.getMultiplier() + abs(intensity_mod));
            }
            if (decreasePointLightIntensity) {
                pointLight.setMultiplier(pointLight.getMultiplier() - abs(intensity_mod));
                glUniform1f(pl_multiplierAddress, pointLight.getMultiplier());
            }
        }

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

        // Reset lighting to render lightModel unaffected by light
        glUniform1f(dl_existsAddress, false);
        glUniform1f(pl_existsAddress, false);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}