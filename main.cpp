#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <array>
#include "vertex.cpp"

using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// Variables for checking compilation/linking correctness
int success;
char infoLog[512];

// Basic vertex shader in GLSL (OpenGL Shading Language)
const char *vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "void main() {\n"
        "	gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
        "}\0";

// Basic fragment shader
const char *fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 ourColor;\n"
        "void main() {\n"
        "	FragColor = ourColor;\n"
        "}\0";

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
int len = 27;
struct cubito{
    unsigned int VBO, VAO;
    cubito()
    {
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
};
struct camada{
    vector<cubito> arr;
    camada()
    {
        for(int i = 0; i < 9; i++)
        {
            arr.emplace_back(cubito());
        }
    }
};

struct Cube
{
    unsigned int shaderP;
    Cube(unsigned int shaderProgram){
        shaderP = shaderProgram;
    }

    camada adelante = camada();
    camada medio = camada();
    camada atras = camada();

    glm::vec3 cubePositionsFront[9] = {
            glm::vec3(-0.8f, -0.8f, 0.0f),
            glm::vec3(-0.3f, -0.8f, 0.0f),
            glm::vec3(0.2f, -0.8f, 0.0f),

            glm::vec3(-0.8f, -0.3f, 0.0f),
            glm::vec3(-0.3f, -0.3f, 0.0f),
            glm::vec3(0.2f, -0.3f, 0.0f),

            glm::vec3(-0.8f, 0.2f, 0.0f),
            glm::vec3(-0.3f, 0.2f, 0.0f),
            glm::vec3(0.2f, 0.2f, 0.0f)
    };

    glm::vec3 cubePositionsMedium[9] = {
            glm::vec3( -0.8f,  -0.8f, -0.5f),
            glm::vec3( -0.3f,  -0.8f, -0.5f),
            glm::vec3( 0.2f,  -0.8f, -0.5f),

            glm::vec3( -0.8f,  -0.3f, -0.5f),
            glm::vec3( -0.3f,  -0.3f, -0.5f),
            glm::vec3( 0.2f,  -0.3f, -0.5f),

            glm::vec3( -0.8f,  0.2f, -0.5f),
            glm::vec3( -0.3f,  0.2f, -0.5f),
            glm::vec3( 0.2f,  0.2f, -0.5f)
    };

    glm::vec3 cubePositionsBack[9] = {
            glm::vec3( -0.8f,  -0.8f, -1.0f),
            glm::vec3( -0.3f,  -0.8f, -1.0f),
            glm::vec3( 0.2f,  -0.8f, -1.0f),

            glm::vec3( -0.8f,  -0.3f, -1.0f),
            glm::vec3( -0.3f,  -0.3f, -1.0f),
            glm::vec3( 0.2f,  -0.3f, -1.0f),

            glm::vec3( -0.8f,  0.2f, -1.0f),
            glm::vec3( -0.3f,  0.2f, -1.0f),
            glm::vec3( 0.2f,  0.2f, -1.0f)
    };

    vector<vector<glm::vec4>> cubeColorsFront;
    vector<vector<glm::vec4>> cubeColorsMedium;
    vector<vector<glm::vec4>> cubeColorsBack;

    void drawFront()
    {
        // Para todos los cubitos
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        unsigned int viewLoc  = glGetUniformLocation(shaderP, "view");
        unsigned int projectionLoc = glGetUniformLocation(shaderP,"projection");

        // pass them to the shaders (3 different ways)
        //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        //view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        glUseProgram(shaderP);

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projectionLoc,1, GL_FALSE, &projection[0][0]);

        for(int i = 0; i < 9; i++)
        {
            glm::mat4 currCubitoModel = glm::mat4(1.0f);
            currCubitoModel = glm::translate(currCubitoModel, cubePositionsFront[i]);
            unsigned int currCubitoModelLoc = glGetUniformLocation(shaderP, "model");
            unsigned int colLoc = glGetUniformLocation(shaderP, "ourColor");

            glUniformMatrix4fv(currCubitoModelLoc, 1, GL_FALSE, &currCubitoModel[0][0]);
            glUniform4f(colLoc, 0.0f, 1.0f, 0.0f, 1.0f);

            glBindVertexArray(adelante.arr[i].VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            cout << "y estamos aqui, rafaga" << endl;
        }
    }


};
int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);

    // 1. Build and compile our shader programs

    // Create a vertex shader object
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Attach the shader source code to the shader object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    // Compile the vertex shader dynamically
    glCompileShader(vertexShader);

    // Check if compilation was successful
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
        std::cout << infoLog << std::endl;
    }

    // Create a fragment shader object
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Attach the shader source code to the shader object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    // Compile the fragment shader dynamically
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
        std::cout << infoLog << std::endl;
    }


    // 2. Link shaders

    // Create a shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // Attach the compiled shaders to the shader program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check if linking was successful
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n";
        std::cout << infoLog << std::endl;
    }

    // Delete shader objects if we no longer need them anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // 3. Set up vertex data and configure vertex attributes

    // Define three vertices with 3D positions
    float vertices[] = {
            -0.2f, -0.2f, 0.0f,
            0.2f, -0.2f, 0.0f,
            0.0f,  0.2f, 0.0f
    };
    glEnable(GL_DEPTH_TEST);

    //Multiply(cube_vertices, 108);
    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
    //Multiply(cube_vertices, 24);
    // Generate vertex buffer object (VBO) and vertex array object (VAO)
    unsigned int arrVBO[len];
    unsigned int arrVAO[len];
    unsigned int arrEBO[1];
    glm::vec3 cubePositions[] = {
            glm::vec3( -0.8f,  -0.8f, 0.0f),
            glm::vec3( -0.3f,  -0.8f, 0.0f),
            glm::vec3( 0.2f,  -0.8f, 0.0f),

            glm::vec3( -0.8f,  -0.3f, 0.0f),
            glm::vec3( -0.3f,  -0.3f, 0.0f),
            glm::vec3( 0.2f,  -0.3f, 0.0f),

            glm::vec3( -0.8f,  0.2f, 0.0f),
            glm::vec3( -0.3f,  0.2f, 0.0f),
            glm::vec3( 0.2f,  0.2f, 0.0f),
            ////////////////////////////////////////////
            glm::vec3( -0.8f,  -0.8f, -0.5f),
            glm::vec3( -0.3f,  -0.8f, -0.5f),
            glm::vec3( 0.2f,  -0.8f, -0.5f),

            glm::vec3( -0.8f,  -0.3f, -0.5f),
            glm::vec3( -0.3f,  -0.3f, -0.5f),
            glm::vec3( 0.2f,  -0.3f, -0.5f),

            glm::vec3( -0.8f,  0.2f, -0.5f),
            glm::vec3( -0.3f,  0.2f, -0.5f),
            glm::vec3( 0.2f,  0.2f, -0.5f),

            //////////////////////////////////////////////

            glm::vec3( -0.8f,  -0.8f, -1.0f),
            glm::vec3( -0.3f,  -0.8f, -1.0f),
            glm::vec3( 0.2f,  -0.8f, -1.0f),

            glm::vec3( -0.8f,  -0.3f, -1.0f),
            glm::vec3( -0.3f,  -0.3f, -1.0f),
            glm::vec3( 0.2f,  -0.3f, -1.0f),

            glm::vec3( -0.8f,  0.2f, -1.0f),
            glm::vec3( -0.3f,  0.2f, -1.0f),
            glm::vec3( 0.2f,  0.2f, -1.0f),
    };
    /*for(int i = 0; i < len; i++)
    {
        glGenBuffers(1, &arrVBO[i]);
        glGenVertexArrays(1, &arrVAO[i]);

        glBindVertexArray(arrVAO[i]);

        glBindBuffer(GL_ARRAY_BUFFER, arrVBO[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        //printVertices(vertices, 9);
    }*/
    /* unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO, then bind VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copy the vertex data into the buffer's memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set attributes that describe how OpenGL should interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // Unbind so other calls won't modify VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); */
    glLineWidth(10);


    while (!glfwWindowShouldClose(window)) {

        processInput(window);
        Cube cube = Cube(shaderProgram);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        cube.drawFront();


        /*glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        unsigned int viewLoc  = glGetUniformLocation(shaderProgram, "view");
        unsigned int projectionLoc = glGetUniformLocation(shaderProgram,"projection");
        // pass them to the shaders (3 different ways)
        //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        const float radius = 10.0f;

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projectionLoc,1, GL_FALSE, &projection[0][0]);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
        /*glUseProgram(shaderProgram);
        glBindVertexArray(arrVAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);*/

        /*for(int i = 0; i < len; i++) {
            glm::mat4 model         = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            //float angle = 20.0f * i;
            //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
            glUseProgram(shaderProgram);
            glBindVertexArray(arrVAO[i]);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            //glDrawArrays(GL_LINE, 0, 36);
        }*/
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    const float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}