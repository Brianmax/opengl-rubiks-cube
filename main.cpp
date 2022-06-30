#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <math.h>
#include "queue"
#include "utility"
#include "vertex.h"
#include "string"
#include "solver.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
unsigned int shaderProgram;
using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
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
"layout (location = 1) in vec2 aCoord;\n"
"out vec2 TexCoord;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main(){\n"
"	gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
"   TexCoord = vec2(aCoord.x, 1.0 - aCoord.y);\n"
"}\n";

// Basic fragment shader
const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D texture1;\n"
"uniform vec4 ourColor;\n"
"void main() {\n"
"	FragColor = texture(texture1, TexCoord);\n"
"}\n";

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//enum class rotation { front, back, down, up, right, left };
int rotation = 0;
bool bussy = false;



// 12 primeros - bordes
// 8 restantes - esquinas
string initialCube[] = { "UF", "UR", "UB", "UL", "DF", "DR", "DB", "DL", "FR", "FL", "BR", "BL", "UFR", "URB", "UBL", "ULF", "DRF", "DFL", "DLB", "DBR" };

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 2.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
// timing  

glm::vec3 computeCircumPoints(float r, double angle, glm::vec3 origin) {

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
    else if (faceId <= 3) {
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
float camY = 0.0;
bool up = true;
bool down = false;
void incrementHandler()
{
    if(up)
    {
        camY = camY + 0.03;
        if (camY > 7.0) {
            up = false;
            down = true;
        }
    }
    else if(down)
    {
        camY = camY - 0.03;
        if(camY < -7.0) {
            down = false;
            up = true;
        }
    }
}
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

int cubitoId = 0;
int camadaId = 0;


struct AnimationHandler {
    bool running;
    float speed;
    glm::vec3 increments;
    glm::vec3 currState;
    glm::vec3 initState;
    glm::vec3 finalState;
    AnimationHandler() {
        running = false;
    };
    void computeIncrements()
    {
        glm::vec3 increments = (finalState - initState) * speed;
    }
    void setAnimation(glm::vec3 initPos, glm::vec3 finalPos, float _speed)
    {
        initState = initPos;
        finalState = finalPos;
        currState = initState;
        speed = 1 / _speed;
        computeIncrements();
    }
    void execute()
    {
        if (currState == initState) running = true;
        if (running) {
            currState += increments;
            if (currState == finalState) running = false;
        }
    }
};

struct cubito {
    unsigned int VBO, VAO;
    vector<glm::vec3 > colors;
    glm::vec3 position;
    glm::vec3 translation;
    glm::vec3 animation;
    AnimationHandler ah;
    float angle;
    int id;
    int c_id;
    cubito(vector<glm::vec3> _colors, glm::vec3 _position)
    {
        c_id = camadaId;
        id = cubitoId;
        cubitoId++;
        colors = _colors;
        position = _position;
        angle = 0;
        translation = glm::vec3(0.0f, 0.0f, 0.0f);
        animation = glm::vec3(0.0f, 0.0f, 0.0f);

        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        //glBindVertexArray(0);
        //glBindVertexArray(0);
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
<<<<<<< HEAD
=======
    }
    void setAnimationVector(glm::vec3 animationVector)
    {
        ah.setAnimation(position, animationVector, 0.3);
    }
    bool isAnimationRunning() {
        return ah.running;
    }
    glm::vec3 getAnimationVector()
    {
        ah.execute();
        return ah.currState;
    }

    string getColors(int colorIdx)
    {
        if (colors[colorIdx] == orange)
            return "U";
        if (colors[colorIdx] == blue)
            return "R";
        if (colors[colorIdx] == white)
            return "F";
        if (colors[colorIdx] == green)
            return "L";
        if (colors[colorIdx] == red)
            return "D";
        if (colors[colorIdx] == yellow)
            return "B";
        else {
            return "-";
        }
>>>>>>> f15ec4a9875ff51d3a59757c4f77f5a8752faf1e
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
    void buildFace(vector<camada>& vc)
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



void swapCubieColors(vv3& colors, int faceId)
{
    vv3 tmp = colors;
    for (int i = 0; i < 4; i++)
    {
        pair<int, int> indexes = colorRotations[faceId][i];
        colors[indexes.second] = tmp[indexes.first];
    }
}



void swapFaceColors(Face& target, int faceId)
{
    vector<cubito> tmp;

    for (int i = 0; i < 9; i++)
    {
        tmp.push_back(*target.cubies[i]);
    }

    for (int i = 0; i < 8; i++)
    {
        pair<int, int> indexes = allDirectives[faceId][i];
        target.cubies[indexes.first]->colors = tmp[indexes.second].colors;
        target.cubies[indexes.first]->id = tmp[indexes.second].id;
        swapCubieColors(target.cubies[indexes.first]->colors, faceId);
        target.cubies[indexes.first]->reset();
    }
    target.cubies[4]->reset();
}
struct Cube
{
    unsigned int shaderP;
    vector<camada> camadasCube;
    Cube(unsigned int shaderProgram) {
        shaderP = shaderProgram;

        camada CamadaFront(coloresFront, cubePositionsFront);
        //cubitoId = 0;
        camadaId++;
        camada CamadaMiddle(coloresMiddle, cubePositionsMiddle);
        //cubitoId = 0;
        camadaId++;
        camada CamadaBack(coloresBack, cubePositionsBack);
        camadasCube.push_back(CamadaFront);
        camadasCube.push_back(CamadaMiddle);
        camadasCube.push_back(CamadaBack);
    }
    void draw()
    {
        incrementHandler();
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        const float radius = 5.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        float camYY = sin(glfwGetTime()) * radius;
        //glm::mat4 view = glm::lookAt(glm::vec3(camX, camY, camZ),glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 view = glm::lookAt(glm::vec3(camX, 0.0, camZ),glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));7
        //glm::mat4 view = glm::lookAt(glm::vec3(0.0, camYY, camZ),glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

        //glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

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

                bool animationRunning = camadasCube[i].arr[e].isAnimationRunning();

                if (!animationRunning) {
                    currCubitoModel = glm::rotate(currCubitoModel, glm::radians(camadasCube[i].arr[e].angle), axisRotationHandler());
                }
                else {
                    cout << "Running" << '\n';
                    currCubitoModel = glm::translate(currCubitoModel, camadasCube[i].arr[e].getAnimationVector());
                }

                glUniformMatrix4fv(currCubitoModelLoc, 1, GL_FALSE, &currCubitoModel[0][0]);
                glBindVertexArray(camadasCube[i].arr[e].VAO);
                int a = 0;
                for (int k = 0; k <= 30; k += 6)
                {
                    int t = k / 6;
                    glm::vec3 CurrColor = camadasCube[i].arr[e].colors[t];
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, texturesCube[i][e][a%7]);
                    glUseProgram(shaderP);
                    glBindVertexArray(camadasCube[i].arr[e].VAO);
                    glDrawArrays(GL_TRIANGLES, k, 6);
                    a++;
                }
            }
        }
    }
};
// DÍA DEL EXAMEN FINAL
// RETOS:
// 1. RESPIRAR
// 2. QUE SE ARME SOLO
// 3. CUBO DE CUBOS

// PARA EL JUEVES AVANCE

// PARA EL EXÁMEN:
// PRIMITIVAS DE TEXTURA
// 

double angle = 0;
double angleLimit = 89.0f;
double increment = 5;
std::vector<std::string> fnames = { "FRONT","BACK","LEFT","RIGHT","UP","DOWN" };
struct CubeController {
    queue<int> rotationsQueue;
    Cube* cube;
    vector<camada>* camadasCube;
    vector<string> input;
    vector<string> output;
    vector<Face> faces;

    CubeController() {
        cube = nullptr;
        camadasCube = nullptr;
        faces.resize(6);
        input.resize(21);
    }
    void setCubo(Cube& _cube)
    {
        camadasCube = &_cube.camadasCube;
        cube = &_cube;
        for (auto& face : faces)
            face.buildFace(*camadasCube);
        //printFaces();
        setInput();
        printInput();
    }


    void faceRotation(double angle, int faceId)
    {
        v3 origin = faces[faceId].cubies[4]->position;
        vector<cubito*>* currCubies = &faces[faceId].cubies;
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
        faces[faceId].cubies[5]->setRotation(computeCircumPoints(radiusEdge, angle + sum[5], origin, faceId), angle);
        faces[faceId].cubies[7]->setRotation(computeCircumPoints(radiusEdge, angle + sum[7], origin, faceId), angle);
    }

    void printFaces() {
        std::cout << "-----------------------------------------------------------------" << '\n';
        int j = 0;
        for (auto& face : faces) {
            std::cout << fnames[j] << '\n';
            int i = 1;
            for (auto& cubie : face.cubies)
            {
                if (i % 3 == 0) {
                    std::cout << cubie->id << '\n';
                    //std::cout << cubie->id << "(" << cubie->c_id << ") ";
                }
                else {
                    std::cout << cubie->id << " ";
                }

                i++;
            }
            j++;
            std::cout << '\n';
        }
        std::cout << "-----------------------------------------------------------------" << '\n';
    }

    void clearRotation()
    {
        camada* camada = &cube->camadasCube[0];
        for (int i = 0; i < 9; i++)
        {
            camada->arr[i].reset();
        }
    }

    void setRotationFlag(int newFlag, int times = 1)
    {
        for (int i = 0; i < times; i++)
        {
            rotationsQueue.push(newFlag);
        }
    }
    void printInput()
    {
        cout << "State: ";
        for (int i = 0; i < 20; i++)
            cout << input[i + 1] << " ";
        cout << '\n';
    }
    void setInput()
    {
        // frontFace 0, backFace 1, leftFace 2 , rightFace 3, upFace 4, downFace 5
        //En U -> 6 7 8 15 16 17 24 25 26
        //Indices:  1   3     5     7 
        //Orden: 1 - 5 - 7 - 3
        //En D -> 1 - 5 - 7 - 3
        //Middle -> F(5) - F(3) - B(5) - B(3)

        //En U -> 0 - 2 - 6 - 8
        //En D -> 0 - 2 - 6 - 8
        // 0 6 8 2

        vector<cubito*> state = {
            //Borders up
            faces[4].cubies[1],
            faces[4].cubies[5],
            faces[4].cubies[7],
            faces[4].cubies[3],
            // Borders down
            faces[5].cubies[1],
            faces[5].cubies[5],
            faces[5].cubies[7],
            faces[5].cubies[3],
            // Middle
            faces[0].cubies[5],
            faces[0].cubies[3],
            faces[1].cubies[5],
            faces[1].cubies[3],
            // Corners UP
            faces[4].cubies[2],
            faces[4].cubies[8],
            faces[4].cubies[6],
            faces[4].cubies[0],
            // Corners Down
            faces[5].cubies[2],
            faces[5].cubies[0],
            faces[5].cubies[6],
            faces[5].cubies[8]
        };
        //  B(0)    F(1)   L(2)   R(3)  D(4)  U(5)
        vector<vector<int>> colorIndexes = {
            //Borders up
            {5, 1},
            {5, 3},
            {5, 0},
            {5, 2},
            // Borders down
            {4, 1},
            {4, 3},
            {4, 0},
            {4, 2},
            // Middle
            {1, 3},
            {1, 2},
            {0, 3},
            {0, 2},
            // Corners UP
            {5, 1, 3},
            {5, 3, 0},
            {5, 0, 2},
            {5, 2, 1},
            // Corners Down
            {4, 3, 1},
            {4, 1, 2},
            {4, 2, 0},
            {4, 0, 3}
        };


        for (int i = 0; i < 20; i++) {
            input[i + 1] = "";
            for (auto& j : colorIndexes[i]) {
                input[i + 1].append(state[i]->getColors(j));
            }
        }
    }

    void rotationHandler()
    {
        if (!rotationsQueue.empty())
        {
            faceRotation(angle, rotationsQueue.front());
            axisRotation = rotationsQueue.front();

            if (angle <= angleLimit) {
                angle += increment;
            }
            else {
                angle = 0;
                swapFaceColors(faces[rotationsQueue.front()], rotationsQueue.front());
                rotationsQueue.pop();
            }
        }
    }
    vector<glm::vec3> animationVectors = {
    glm::vec3(0,0.4,0)
    };

    vector<vector<int>> animationDirectives = {
        //camada, indexCubo, vector
        {0, 1, 0}
    };

    void animate()
    {
        cout << "Animate" << '\n';
        int n = animationDirectives.size();
        for (int i = 0; i < n; i++)
        {
            int indexCamada = animationDirectives[i][0];
            int indexCubito = animationDirectives[i][1];
            int indexVector = animationDirectives[i][2];

            cube->camadasCube[indexCamada].arr[indexCubito].setAnimationVector(animationVectors[indexVector]);
        }
    }
    void solve()
    {
        setInput();
        printInput();
        cout << "Solution: ";
        output.clear();
        solver(input, output);
        cout << '\n';

        // front(0)  back(1) left(2) right(3) up(4) down(5)
        for (string& mov : output)
        {
            if (mov == "R1") setRotationFlag(3, 3);
            else if (mov == "R2") setRotationFlag(3, 2);
            else if (mov == "R3") setRotationFlag(3);

            else if (mov == "U1") setRotationFlag(4, 3);
            else if (mov == "U2") setRotationFlag(4, 2);
            else if (mov == "U3") setRotationFlag(4);

            else if (mov == "F1") setRotationFlag(0, 3);
            else if (mov == "F2") setRotationFlag(0, 2);
            else if (mov == "F3") setRotationFlag(0);

            else if (mov == "L1") setRotationFlag(2);
            else if (mov == "L2") setRotationFlag(2, 2);
            else if (mov == "L3") setRotationFlag(2, 3);

            else if (mov == "B1") setRotationFlag(1);
            else if (mov == "B2") setRotationFlag(1, 2);
            else if (mov == "B3") setRotationFlag(1, 3);

            else if (mov == "D1") setRotationFlag(5);
            else if (mov == "D2") setRotationFlag(5, 2);
            else if (mov == "D3") setRotationFlag(5, 3);
        }
    }
};


void handleAngle(double& angle)
{
    angle = angle < angleLimit ? angle += increment : 0;
}
CubeController cubeController;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);


    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetScrollCallback(window, scroll_callback);
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
    glGenTextures(55, &textures2[0]);
    for (int i = 0; i < 55; i++) {
        glBindTexture(GL_TEXTURE_2D, textures2[i]);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        //string tmp = "./image" + to_string(i + 1) + ".jpg";
        string tmp = "./img" + to_string(i + 1) + ".jpg";
        cout << "File: " << tmp << "    "<< textures[i] << endl;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char *data = stbi_load(tmp.c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        glUseProgram(shaderProgram);
        //ourShader.setInt("texture1", 0);
        int loc = glGetUniformLocation(shaderProgram, "texture1");
        glUniform1i(loc, 0);
    }
    glPointSize(8);
    glLineWidth(5);
    Cube cube = Cube(shaderProgram);
    cubeController.setCubo(cube);

    while (!glfwWindowShouldClose(window)) {
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
        cubeController.setRotationFlag(0);
    }
    if (key == GLFW_KEY_B && action == GLFW_PRESS)
    {
        cubeController.setRotationFlag(1);
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        cubeController.setRotationFlag(3);
    }
    if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        cubeController.setRotationFlag(2);
    }
    if (key == GLFW_KEY_U && action == GLFW_PRESS)
    {
        cubeController.setRotationFlag(4);
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        cubeController.setRotationFlag(5);
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        cubeController.solve();
    }
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        cubeController.animate();
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

