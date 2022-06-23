#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
using namespace std;
#define red glm::vec3(1.0,0.0,0.0)
#define green glm::vec3(0.0,1.0,0.0)
#define blue glm::vec3(0.0,0.0,1.0)
#define white glm::vec3(1.0,1.0,1.0)
#define orange glm::vec3(1.0,0.5,0.0)
#define yellow glm::vec3(1.0,1.0,0.0)
#define black glm::vec3(0.0,0.0,0.0)
unsigned int textures[7] = {1,2,3,4,5,6,7};
float cube_vertices[] = {
        // back
        -0.2f, -0.2f, -0.2f, 0.0f, 0.0f,
        0.2f, -0.2f, -0.2f, 1.0f, 0.0f,
        0.2f,  0.2f, -0.2f, 1.0f, 1.0f,
        0.2f,  0.2f, -0.2f, 1.0f, 1.0f,
        -0.2f,  0.2f, -0.2f, 0.0f, 1.0f,
        -0.2f, -0.2f, -0.2f, 0.0f, 0.0f,
        //front
        -0.2f, -0.2f,  0.2f, 0.0f, 0.0f,
        0.2f, -0.2f,  0.2f, 1.0f, 0.0f,
        0.2f,  0.2f,  0.2f, 1.0f, 1.0f,
        0.2f,  0.2f,  0.2f, 1.0f, 1.0f,
        -0.2f,  0.2f,  0.2f, 0.0f, 1.0f,
        -0.2f, -0.2f,  0.2f, 0.0f, 0.0f,
        //left
        -0.2f,  0.2f,  0.2f, 0.0f, 0.0f,
        -0.2f,  0.2f, -0.2f, 1.0f, 0.0f,
        -0.2f, -0.2f, -0.2f, 1.0f, 1.0f,
        -0.2f, -0.2f, -0.2f, 1.0f, 1.0f,
        -0.2f, -0.2f,  0.2f, 0.0f, 1.0f,
        -0.2f,  0.2f,  0.2f, 0.0f, 0.0f,
        //right
        0.2f,  0.2f,  0.2f, 0.0f, 0.0f,
        0.2f,  0.2f, -0.2f, 1.0f, 0.0f,
        0.2f, -0.2f, -0.2f, 1.0f, 1.0f,
        0.2f, -0.2f, -0.2f, 1.0f, 1.0f,
        0.2f, -0.2f,  0.2f, 0.0f, 1.0f,
        0.2f,  0.2f,  0.2f, 0.0f, 0.0f,
        //down
        -0.2f, -0.2f, -0.2f, 0.0f, 0.0f,
        0.2f, -0.2f, -0.2f, 1.0f, 0.0f,
        0.2f, -0.2f,  0.2f, 1.0f, 1.0f,
        0.2f, -0.2f,  0.2f, 1.0f, 1.0f,
        -0.2f, -0.2f,  0.2f, 0.0f, 1.0f,
        -0.2f, -0.2f, -0.2f, 0.0f, 0.0f,
        //up
        -0.2f,  0.2f, -0.2f, 0.0f, 0.0f,
        0.2f,  0.2f, -0.2f, 1.0f, 0.0f,
        0.2f,  0.2f,  0.2f, 1.0f, 1.0f,
        0.2f,  0.2f,  0.2f, 1.0f, 1.0f,
        -0.2f,  0.2f,  0.2f, 0.0f, 1.0f,
        -0.2f,  0.2f, -0.2f, 0.0f, 0.0f,
};
#define blackT textures[6]
#define whiteT textures[5]
#define blueT textures[4]
#define greenT textures[3]
#define redT textures[2]
#define yellowT textures[1]
#define orangeT textures[0]


std::vector<glm::vec3> cubeColorsFront = {
    yellow, white, green, blue, red, orange
};
typedef glm::vec3 v3;
typedef std::vector<glm::vec3> vv3;
typedef std::vector<vv3> vvv3;
std::vector<std::vector<glm::vec3 > > coloresFront {
    //  B       F       L      R     D     U
    vv3{black, white, green, black, red, black}, //0
    vv3{black, white, black, black, red, black}, //1
    vv3{black, white, black, blue, red, black}, //2

    vv3{black, white, green, black, black, black}, //3
    vv3{black, white, black, black, black, black}, //4
    vv3{black, white, black, blue, black, black}, //5

    vv3{black, white, green, black, black, orange}, //6
    vv3{black, white, black, black, black, orange}, //7
    vv3{black, white, black, blue, black, orange}, //8
};
vector<vector<unsigned int> > texturesFront {
    {blackT, whiteT, greenT, blackT, redT, blackT},
    {blackT, whiteT, blackT, blackT, redT, blackT},
    {blackT, whiteT, blackT, blueT, redT, blackT},

    {blackT, whiteT, greenT, blackT, blackT, blackT},
    {blackT, whiteT, blackT, blackT, blackT, blackT},
    {blackT, whiteT, blackT, blueT, blackT, blackT},

    {blackT, whiteT, greenT, blackT, blackT, orangeT},
    {blackT, whiteT, blackT, blackT, blackT, orangeT},
    {blackT, whiteT, blackT, blueT, blackT, orangeT},
    };
// orange - blue
// blue - red
// green - orange
// red - green

//black, white, black, blue, black, orange
//black, white, black, blue, red, black
// 0 - 6, 




std::vector<std::vector<glm::vec3 > > coloresMiddle {
        //  B       F       L      R     D     U
        vv3{black, black, green, black, red, black},
        vv3{black, black, black, black, red, black},
        vv3{black, black, black, blue, red, black},

        vv3{black, black, green, black, black, black},
        vv3{black, black, black, black, black, black},
        vv3{black, black, black, blue, black, black},

        vv3{black, black, green, black, black, orange},
        vv3{black, black, black, black, black, orange},
        vv3{black, black, black, blue, black, orange}
};

std::vector<std::vector<unsigned int > > texturesMiddle {
        //  B       F       L      R     D     U
        {blackT, blackT, greenT, blackT, redT, blackT},
        {blackT, blackT, blackT, blackT, redT, blackT},
        {blackT, blackT, blackT, blueT, redT, blackT},

        {blackT, blackT, greenT, blackT, blackT, blackT},
        {blackT, blackT, blackT, blackT, blackT, blackT},
        {blackT, blackT, blackT, blueT, blackT, blackT},

        {blackT, blackT, greenT, blackT, blackT, orangeT},
        {blackT, blackT, blackT, blackT, blackT, orangeT},
        {blackT, blackT, blackT, blueT, blackT, orangeT}
};
std::vector<std::vector<glm::vec3 > > coloresBack {
        //  B       F       L      R      D      U
        vv3{yellow, black, green, black, red, black},
        vv3{yellow, black, black, black, red, black},
        vv3{yellow, black, black, blue, red, black},

        vv3{yellow, black, green, black, black, black},
        vv3{yellow, black, black, black, black, black},
        vv3{yellow, black, black, blue, black, black},

        vv3{yellow, black, green, black, black, orange},
        vv3{yellow, black, black, black, black, orange},
        vv3{yellow, black, black, blue, black, orange}
};

std::vector<std::vector<unsigned int > > texturesBack {
        //  B       F       L      R      D      U
        {yellowT, blackT, greenT, blackT, redT, blackT},
        {yellowT, blackT, blackT, blackT, redT, blackT},
        {yellowT, blackT, blackT, blueT, redT, blackT},

        {yellowT, blackT, greenT, blackT, blackT, blackT},
        {yellowT, blackT, blackT, blackT, blackT, blackT},
        {yellowT, blackT, blackT, blueT, blackT, blackT},

        {yellowT, blackT, greenT, blackT, blackT, orangeT},
        {yellowT, blackT, blackT, blackT, blackT, orangeT},
        {yellowT, blackT, blackT, blueT, blackT, orangeT}
};
vector<vector<vector<unsigned int>>> texturesCube = {texturesFront, texturesMiddle, texturesBack};
//CUBOS SEPARADOS
std::vector<glm::vec3> cubePositionsFront = {
        glm::vec3(-0.8f, -0.8f, 0.0f), //C 0
        glm::vec3(-0.3f, -0.8f, 0.0f), //E 1
        glm::vec3(0.2f, -0.8f, 0.0f), //C 2

        glm::vec3(-0.8f, -0.3f, 0.0f), //E 3
        glm::vec3(-0.3f, -0.3f, 0.0f), //M 4
        glm::vec3(0.2f, -0.3f, 0.0f), //E 5

        glm::vec3(-0.8f, 0.2f, 0.0f), //C 6
        glm::vec3(-0.3f, 0.2f, 0.0f), //E 7
        glm::vec3(0.2f, 0.2f, 0.0f), //C 8
};
std::vector<glm::vec3> cubePositionsMiddle = {
        glm::vec3(-0.8f, -0.8f, -0.5f),
        glm::vec3(-0.3f, -0.8f, -0.5f),
        glm::vec3(0.2f, -0.8f, -0.5f),

        glm::vec3(-0.8f, -0.3f, -0.5f),
        glm::vec3(-0.3f, -0.3f, -0.5f),
        glm::vec3(0.2f, -0.3f, -0.5f),

        glm::vec3(-0.8f, 0.2f, -0.5f),
        glm::vec3(-0.3f, 0.2f, -0.5f),
        glm::vec3(0.2f, 0.2f, -0.5f),
};
std::vector<glm::vec3> cubePositionsBack{
        glm::vec3(-0.8f,  -0.8f, -1.0f),
        glm::vec3(-0.3f,  -0.8f, -1.0f),
        glm::vec3(0.2f,  -0.8f, -1.0f),

        glm::vec3(-0.8f,  -0.3f, -1.0f),
        glm::vec3(-0.3f,  -0.3f, -1.0f),
        glm::vec3(0.2f,  -0.3f, -1.0f),

        glm::vec3(-0.8f,  0.2f, -1.0f),
        glm::vec3(-0.3f,  0.2f, -1.0f),
        glm::vec3(0.2f,  0.2f, -1.0f)
};

std::vector<std::vector<glm::vec3>> positions = {cubePositionsFront, cubePositionsMiddle, cubePositionsBack};

#include<utility>

typedef std::vector<std::pair<int, int>> vp;

vp FswapDirectives = {
    std::make_pair(5, 1),
    std::make_pair(7, 5),
    std::make_pair(3, 7),
    std::make_pair(1, 3),
    std::make_pair(2, 0),
    std::make_pair(8, 2),
    std::make_pair(6, 8),
    std::make_pair(0, 6)
};

vp BswapDirectives = {
    std::make_pair(5, 1),
    std::make_pair(7, 5),
    std::make_pair(3, 7),
    std::make_pair(1, 3),
    std::make_pair(2, 0),
    std::make_pair(8, 2),
    std::make_pair(6, 8),
    std::make_pair(0, 6)
};
vp LswapDirectives = {
    std::make_pair(1, 5),
    std::make_pair(5, 7),
    std::make_pair(7, 3),
    std::make_pair(3, 1),
    std::make_pair(0, 2),
    std::make_pair(2, 8),
    std::make_pair(8, 6),
    std::make_pair(6, 0)
};
vp RswapDirectives = {
    std::make_pair(5, 1),
    std::make_pair(7, 5),
    std::make_pair(3, 7),
    std::make_pair(1, 3),
    std::make_pair(2, 0),
    std::make_pair(8, 2),
    std::make_pair(6, 8),
    std::make_pair(0, 6)
};
vp UswapDirectives = {
    std::make_pair(5, 1),
    std::make_pair(7, 5),
    std::make_pair(3, 7),
    std::make_pair(1, 3),
    std::make_pair(2, 0),
    std::make_pair(8, 2),
    std::make_pair(6, 8),
    std::make_pair(0, 6)
};
vp DswapDirectives = {
    std::make_pair(5, 1),
    std::make_pair(7, 5),
    std::make_pair(3, 7),
    std::make_pair(1, 3),
    std::make_pair(2, 0),
    std::make_pair(8, 2),
    std::make_pair(6, 8),
    std::make_pair(0, 6)
};

std::vector<vp> allDirectives = { FswapDirectives, BswapDirectives,LswapDirectives,RswapDirectives,UswapDirectives,DswapDirectives };

vp FColorRotation = {
    std::make_pair(5, 2),
    std::make_pair(3, 5),
    std::make_pair(4, 3),
    std::make_pair(2, 4)
};
vp BColorRotation = {
    std::make_pair(5, 2),
    std::make_pair(3, 5),
    std::make_pair(4, 3),
    std::make_pair(2, 4)
};
vp LColorRotation = {
    std::make_pair(1, 4),
    std::make_pair(4, 0),
    std::make_pair(0, 5),
    std::make_pair(5, 1)
};
vp RColorRotation = {
    std::make_pair(1, 4),
    std::make_pair(4, 0),
    std::make_pair(0, 5),
    std::make_pair(5, 1)
};
vp UColorRotation = {
    std::make_pair(1, 3),
    std::make_pair(3, 0),
    std::make_pair(0, 2),
    std::make_pair(2, 1)
};
vp DColorRotation = {
    std::make_pair(1, 3),
    std::make_pair(3, 0),
    std::make_pair(0, 2),
    std::make_pair(2, 1)
};

std::vector<vp> colorRotations = { FColorRotation, BColorRotation, LColorRotation, RColorRotation, UColorRotation, DColorRotation };

//Faces
vp frontFace = {
    // (camada, indice)
    std::make_pair(0, 0),
    std::make_pair(0, 1),
    std::make_pair(0, 2),
    std::make_pair(0, 3),
    std::make_pair(0, 4),
    std::make_pair(0, 5),
    std::make_pair(0, 6),
    std::make_pair(0, 7),
    std::make_pair(0, 8),
};
vp backFace = {
    // (camada, indice)
    std::make_pair(2, 0),
    std::make_pair(2, 1),
    std::make_pair(2, 2),
    std::make_pair(2, 3),
    std::make_pair(2, 4),
    std::make_pair(2, 5),
    std::make_pair(2, 6),
    std::make_pair(2, 7),
    std::make_pair(2, 8)
};

vp rightFace = {
    // (camada, indice)
    std::make_pair(0, 2),
    std::make_pair(1, 2),
    std::make_pair(2, 2),
    std::make_pair(0, 5),
    std::make_pair(1, 5),
    std::make_pair(2, 5),
    std::make_pair(0, 8),
    std::make_pair(1, 8),
    std::make_pair(2, 8)
};
vp leftFace = {
    // (camada, indice)
    std::make_pair(2, 0),
    std::make_pair(1, 0),
    std::make_pair(0, 0),
    std::make_pair(2, 3),
    std::make_pair(1, 3),
    std::make_pair(0, 3),
    std::make_pair(2, 6),
    std::make_pair(1, 6),
    std::make_pair(0, 6)
};

vp upFace = {
    // (camada, indice)
    std::make_pair(0, 6),
    std::make_pair(0, 7),
    std::make_pair(0, 8),
    std::make_pair(1, 6),
    std::make_pair(1, 7),
    std::make_pair(1, 8),
    std::make_pair(2, 6),
    std::make_pair(2, 7),
    std::make_pair(2, 8)
};

vp downFace = {
    // (camada, indice)
    std::make_pair(0, 0),
    std::make_pair(0, 1),
    std::make_pair(0, 2),
    std::make_pair(1, 0),
    std::make_pair(1, 1),
    std::make_pair(1, 2),
    std::make_pair(2, 0),
    std::make_pair(2, 1),
    std::make_pair(2, 2)
};

typedef std::vector<vp> vvp;
vvp allFaces = { frontFace, backFace, leftFace, rightFace, upFace, downFace };


std::vector<int> angleSumF = { 225,270,315,180,0,0,135,90,45 };
std::vector<int> angleSumB = { 225,270,315,180,0,0,135,90,45 };
//std::vector<int> angleSumL = { 225,270,315,180,0,0,135,90,45 };
std::vector<int> angleSumL = { 225,180,135,270,0,90,315,0,45 };
std::vector<int> angleSumR = { 135,180,225,90,0,270,45,0,315 };
std::vector<int> angleSumU = { 315,0,45,270,0,90,225,180,135 };
std::vector<int> angleSumD = { 315,0,45,270,0,90,225,180,135 };

//std::vector<int> angleSumR = { 0,0,0,0,0,0,0,0,0 };
std::vector<std::vector<int>> allAngleSums = { angleSumF, angleSumB, angleSumL,angleSumR ,angleSumU,angleSumD };