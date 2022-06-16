#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <math.h>
#include <array>
#include "queue"
#include "utility"
#include "vertex.h"
//#include "solver.h"

using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// Variables for checking compilation/linking correctness
int success;
char infoLog[512];

// Basic vertex shader in GLSL (OpenGL Shading Language)
const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main() {\n"
"	gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
"}\0";

// Basic fragment shader
const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main() {\n"
"	FragColor = ourColor;\n"
"}\0";

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

enum class rotation { front, back, down, up, right, left };

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
// timing  

glm::vec3 computeCircumPoints(float r, double angle, glm::vec3 origin){

    float initX = (origin.x) + r * cos(glm::radians(angle));
    float initY = (origin.y) + r * sin(glm::radians(angle));
    return glm::vec3(initX, initY, origin.z);
}

glm::vec3 computeCircumPoints(float r, double angle, glm::vec3 origin, int faceId) {

    if (faceId <= 1)
    {
        //fb
        float initX = (origin.x) + r * cos(glm::radians(angle));
        float initY = (origin.y) + r * sin(glm::radians(angle));
        return glm::vec3(initX, initY, origin.z);
    }
    else if(faceId <= 3) {
        //rl
        float initY = (origin.y) + r * cos(glm::radians(angle));
        float initZ = (origin.z) + r * sin(glm::radians(angle));
        return glm::vec3(origin.x, initY, initZ);
    }
    else {
        //ud
        float initZ = (origin.z) + r * cos(glm::radians(angle));
        float initX = (origin.x) + r * sin(glm::radians(angle));
        return glm::vec3(initX, origin.y, initZ);
    }
}
int axisRotation = 0;
int len = 3;
float radiusCorner = 0.71;
float radiusEdge = 0.5;
float radiusCenter = 0.0f;
int test = 55;



glm::vec3 axisRotationHandler()
{
    if (axisRotation <= 1)
    {
        return glm::vec3(0, 0, 1);
    }
    else if (axisRotation <= 3) {
        return glm::vec3(1, 0, 0);
    }
    else {
        return glm::vec3(0, 1, 0);
    }
}
struct cubito {
    unsigned int VBO, VAO;
    vector<glm::vec3 > colors;
    glm::vec3 position;
    glm::vec3 translation;
    float angle;
    cubito(vector<glm::vec3> _colors, glm::vec3 _position)
    {
        colors = _colors;
        position = _position;
        angle = 0;
        translation = glm::vec3(0.0f, 0.0f, 0.0f);

        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    void setRotation(glm::vec<3, float> _translation, float _angle)
    {
        translation = _translation;
        angle = _angle;
    }
    void reset()
    {
        translation = glm::vec3(0.0f, 0.0f, 0.0f);
        angle = 0;
    }
    glm::vec3 getPosition()
    {
        if (translation.x == 0 && translation.y == 0 && translation.z == 0)
        {
            return position;
        }
        return translation;        
    }
};



struct camada {
    vector<cubito> arr;
    camada(vvv3 camadaColors, vv3 positions)
    {
        for (int i = 0; i < 9; i++)
        {
            arr.emplace_back(cubito(camadaColors[i], positions[i]));
        }
    }
    void reset()
    {
        for (auto& cubie : arr)
            cubie.reset();
    }
};
int type = 0;
//Type
// frontFace 0, backFace 1, leftFace 2 , rightFace 3, upFace 4, downFace 5
struct Face {
    int _type;
    vector<cubito*> cubies;
    Face() {
        cubies.resize(9);
        _type = type;
        type++;
    }
    void buildFace( vector<camada>& vc)
    {
        for (int i = 0; i < 9; i++)
        {
            std::pair<int, int> indexes = allFaces[_type][i];
            cubies[i] = &vc[indexes.first].arr[indexes.second];
        }
    }
    void reset()
    {
        for (auto cubie : cubies)
            cubie->reset();
    }
};

void swapCubitoColors(vv3& colors)
{
    vv3 tmp = colors;
    for (int i = 0; i < 4; i++)
    {
        pair<int, int> indexes = clockWiseColorRotation[i];
        colors[indexes.second] = tmp[indexes.first];
    }
}

void swapCamadaColors(camada& target)
{
    camada tmp = target;
    for (int i = 0; i < 8; i++)
    {
        pair<int, int> indexes = FswapDirectives[i];
        target.arr[indexes.first].colors = tmp.arr[indexes.second].colors;
        swapCubitoColors(target.arr[indexes.first].colors);
        target.arr[indexes.first].reset();
    }
}

void swapCamadaColors(camada& target, int faceId)
{
    camada tmp = target;
    for (int i = 0; i < 8; i++)
    {
        pair<int, int> indexes = FswapDirectives[i];
        target.arr[indexes.first].colors = tmp.arr[indexes.second].colors;
        swapCubitoColors(target.arr[indexes.first].colors);
        target.arr[indexes.first].reset();
    }
}


struct Cube
{
    unsigned int shaderP;
    vector<camada> camadasCube;
    Cube(unsigned int shaderProgram) {
        shaderP = shaderProgram;
        camada CamadaFront(coloresFront, cubePositionsFront);
        camada CamadaMiddle(coloresMiddle, cubePositionsMiddle);
        camada CamadaBack(coloresBack, cubePositionsBack);
        camadasCube.push_back(CamadaFront);
        camadasCube.push_back(CamadaMiddle);
        camadasCube.push_back(CamadaBack);
    }
    void draw()
    {
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        unsigned int viewLoc = glGetUniformLocation(shaderP, "view");
        unsigned int projectionLoc = glGetUniformLocation(shaderP, "projection");

        glUseProgram(shaderP);

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);
        for (int i = 0; i < 3; i++)
        {
            for (int e = 0; e < 9; e++)
            {
                glm::mat4 currCubitoModel = glm::mat4(1.0f);
                currCubitoModel = glm::translate(currCubitoModel, camadasCube[i].arr[e].getPosition());

                unsigned int currCubitoModelLoc = glGetUniformLocation(shaderP, "model");
                unsigned int colLoc = glGetUniformLocation(shaderP, "ourColor");

                currCubitoModel = glm::rotate(currCubitoModel, glm::radians(camadasCube[i].arr[e].angle), axisRotationHandler());
                
                glUniformMatrix4fv(currCubitoModelLoc, 1, GL_FALSE, &currCubitoModel[0][0]);
                glBindVertexArray(camadasCube[i].arr[e].VAO);

                for (int k = 0; k <= 30; k += 6)
                {
                    int t = k / 6;
                    glm::vec3 CurrColor = camadasCube[i].arr[e].colors[t];
                    glUniform4f(colLoc, CurrColor[0], CurrColor[1], CurrColor[2], 1.0);
                    glDrawArrays(GL_TRIANGLES, k, 6);
                    glUniform4f(colLoc, 0, 0, 0, 1.0);
                    glDrawArrays(GL_LINE_STRIP, k, 6);
                }
            }
        }
    }
};

double angle = 0;
double angleLimit = 89.0f;
double increment = 2;

struct CubeController {
    queue<rotation> rotationsQueue;
    Cube* cube;
    vector<camada> *camadasCube;

    vector<Face> faces;

    CubeController() {
        cube = nullptr;
        camadasCube = nullptr;
        faces.resize(6);
    }
    void setCubo(Cube& _cube)
    {
        camadasCube = &_cube.camadasCube;
        cube = &_cube;
        for (auto& face : faces)
            face.buildFace(*camadasCube);
    }
    void camadaRotation(double angle, int axis) {
        camada * camada = &cube->camadasCube[axis];
        glm::vec3 origin = camada->arr[4].position;

        camada->arr[0].setRotation(computeCircumPoints(radiusCorner, angle + 225, origin), angle);
        camada->arr[2].setRotation(computeCircumPoints(radiusCorner, angle + 315, origin), angle);
        camada->arr[6].setRotation(computeCircumPoints(radiusCorner, angle + 135, origin), angle);
        camada->arr[8].setRotation(computeCircumPoints(radiusCorner, angle + 45, origin), angle);

        camada->arr[4].setRotation(computeCircumPoints(radiusCenter, angle, origin), angle);

        camada->arr[1].setRotation(computeCircumPoints(radiusEdge, angle + 270, origin), angle);
        camada->arr[3].setRotation(computeCircumPoints(radiusEdge, angle + 180, origin), angle);
        camada->arr[5].setRotation(computeCircumPoints(radiusEdge, angle, origin), angle);
        camada->arr[7].setRotation(computeCircumPoints(radiusEdge, angle + 90, origin), angle);
    }

    void faceRotation(double angle, int faceId)
    {
        v3 origin = faces[faceId].cubies[4]->position;
        vector<cubito*> *currCubies = &faces[faceId].cubies;
        auto sum = allAngleSums[faceId];
        /*for (int i = 0; i < 9; i++)
        {
            cout << sum[i] << '\n';
            faces[faceId].cubies[i]->setRotation(computeCircumPoints(radiusCorner, angle + sum[i], origin, faceId), angle);
        }*/
        faces[faceId].cubies[0]->setRotation(computeCircumPoints(radiusCorner, angle + sum[0], origin, faceId), angle);
        faces[faceId].cubies[2]->setRotation(computeCircumPoints(radiusCorner, angle + sum[2], origin, faceId), angle);
        faces[faceId].cubies[6]->setRotation(computeCircumPoints(radiusCorner, angle + sum[6], origin, faceId), angle);
        faces[faceId].cubies[8]->setRotation(computeCircumPoints(radiusCorner, angle + sum[8], origin, faceId), angle);

        faces[faceId].cubies[4]->setRotation(computeCircumPoints(radiusCenter, angle + sum[4], origin, faceId), angle);

        faces[faceId].cubies[1]->setRotation(computeCircumPoints(radiusEdge, angle + sum[1], origin, faceId), angle);
        faces[faceId].cubies[3]->setRotation(computeCircumPoints(radiusEdge, angle + sum[3], origin, faceId), angle);
        faces[faceId].cubies[5]->setRotation(computeCircumPoints(radiusEdge, angle+ sum[5], origin, faceId), angle);
        faces[faceId].cubies[7]->setRotation(computeCircumPoints(radiusEdge, angle + sum[7], origin, faceId), angle);
    }

    void clearRotation()
    {
        camada* camada = &cube->camadasCube[0];
        for (int i = 0; i < 9; i++)
        {
            camada->arr[i].reset();
        }
    }
   
    void setRotationFlag(rotation newFlag)
    { 
        rotationsQueue.push(newFlag);
    }

    void rotationHandler()
    {
        if (!rotationsQueue.empty())
        {
            switch (rotationsQueue.front())
            {
            case rotation::front:
                faceRotation(angle, 0);
                break;
            case rotation::back:
                faceRotation(angle, 1);
                break;
            case rotation::left:
                faceRotation(angle, 2);
                break;
            case rotation::right:
                faceRotation(angle, 3);
                break;
            case rotation::up:
                faceRotation(angle, 4);
                break;
            case rotation::down:
                faceRotation(angle, 5);
                break;
            default:
                break;
            }

            if (angle <= angleLimit) {
                angle += increment;
            }
            else {
                //cout<<rotationsQueue.size()<<" ";
                angle = 0;
                switch (rotationsQueue.front())
                {
                case rotation::front:
                    faces[0].reset();
                    //swapCamadaColors(cube->camadasCube[0]);
                    break; 
                case rotation::back:
                    faces[1].reset();
                    break;
                case rotation::left:
                    faces[2].reset();
                    break;

                case rotation::right:
                    faces[3].reset();
                    break;

                case rotation::up:
                    faces[4].reset();
                    break;

                case rotation::down:
                    faces[5].reset();
                    break;
                default:
                    break;
                }
                rotationsQueue.pop();
                //clearRotation();
            }
        }
    }
};

void handleAngle(double& angle)
{
    angle = angle < angleLimit ? angle+=increment : 0;
}
CubeController cubeController;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);


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


    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    glEnable(GL_DEPTH_TEST);
    glPointSize(8);
    glLineWidth(5);
    Cube cube = Cube(shaderProgram);
    cubeController.setCubo(cube);


    while (!glfwWindowShouldClose(window)){
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        cube.draw();
        cubeController.rotationHandler();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    const float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, 265) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, 264) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, 263) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, 262) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    //cout << key << '\n';
    if (key == GLFW_KEY_F && action == GLFW_PRESS)
    {
        axisRotation = 0;
        cubeController.setRotationFlag(rotation::front);
    }
    if (key == GLFW_KEY_B && action == GLFW_PRESS)
    {
        axisRotation = 1;
        cubeController.setRotationFlag(rotation::back);
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        axisRotation = 2;
        cubeController.setRotationFlag(rotation::right);
    }
    if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        axisRotation = 3;
        cubeController.setRotationFlag(rotation::left);
    }
    if (key == GLFW_KEY_U && action == GLFW_PRESS)
    {
        axisRotation = 4;
        cubeController.setRotationFlag(rotation::up);
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        axisRotation = 5;
        cubeController.setRotationFlag(rotation::down);
    }
    if (key == 93 && action == GLFW_PRESS)
    {
        test += 1;
    }
    if (key == 47 && action == GLFW_PRESS)
    {
        test -= 1;
    }
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

