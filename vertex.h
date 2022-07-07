#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
using namespace std;
//#define red glm::vec3(1.0,0.0,0.0)
//#define green glm::vec3(0.0,1.0,0.0)
//#define blue glm::vec3(0.0,0.0,1.0)
//#define white glm::vec3(1.0,1.0,1.0)
//#define orange glm::vec3(1.0,0.5,0.0)
//#define yellow glm::vec3(1.0,1.0,0.0)
//#define black glm::vec3(0.0,0.0,0.0)

unsigned int textures2[54] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54};
//c
vector<unsigned int> orangeT={textures2[6],textures2[7],textures2[8],textures2[3],textures2[4],textures2[5],textures2[0],textures2[1],textures2[2]};
vector<unsigned int> yellowT={textures2[15],textures2[16],textures2[17],textures2[12],textures2[13],textures2[14],textures2[9],textures2[10],textures2[11]};
vector<unsigned int> blueT={textures2[33],textures2[34],textures2[35],textures2[30],textures2[31],textures2[32],textures2[27],textures2[28],textures2[29]};
vector<unsigned int> redT={textures2[24],textures2[25],textures2[26],textures2[21],textures2[22],textures2[23],textures2[18],textures2[19],textures2[20]};
vector<unsigned int> greenT={textures2[24],textures2[25],textures2[26],textures2[21],textures2[22],textures2[23],textures2[18],textures2[19],textures2[20]};
vector<unsigned int> whiteT={textures2[51], textures2[52], textures2[53], textures2[48], textures2[49] , textures2[50] , textures2[45] , textures2[46] , textures2[47]};

#define	M1 textures2[6]
#define M2 textures2[7]
#define M3 textures2[8]
#define M4 textures2[3]
#define M5 textures2[4]
#define M6 textures2[5]
#define M7 textures2[0]
#define M8 textures2[1]
#define M9 textures2[2]

#define C1 textures2[15]
#define C2 textures2[16]
#define C3 textures2[17]
#define C4 textures2[12]
#define C5 textures2[13]
#define C6 textures2[14]
#define C7 textures2[9]
#define C8 textures2[10]
#define C9 textures2[11]

#define g1 textures2[24]
#define g2 textures2[25]
#define g3 textures2[26]
#define g4 textures2[21]
#define g5 textures2[22]
#define g6 textures2[23]
#define g7 textures2[18]
#define g8 textures2[19]
#define g9 textures2[20]

#define P1 textures2[33]
#define P2 textures2[34]
#define P3 textures2[35]
#define P4 textures2[30]
#define P5 textures2[31]
#define P6 textures2[32]
#define P7 textures2[27]
#define P8 textures2[28]
#define P9 textures2[29]

#define s1 textures2[42]
#define s2 textures2[43]
#define s3 textures2[44]
#define s4 textures2[39]
#define s5 textures2[40]
#define s6 textures2[41]
#define s7 textures2[36]
#define s8 textures2[37]
#define s9 textures2[38]

#define u1 textures2[51]
#define u2 textures2[52]
#define u3 textures2[53]
#define u4 textures2[48]
#define u5 textures2[49]
#define u6 textures2[50]
#define u7 textures2[45]
#define u8 textures2[46]
#define u9 textures2[47]
#define blackT textures2[55]



vector< vector <unsigned int> > texturesFront {
        //  B      F     L     R      D     U
        {blackT,  M7,  u1,  blackT,   g1, blackT},
        {blackT,  M8, blackT, blackT, g2, blackT},
        {blackT,  M3, blackT, P1,     g3, blackT},

        {blackT, M4,   u4,  blackT, blackT, blackT},
        {blackT, M5, blackT, blackT, blackT, blackT},
        {blackT, M6, blackT, P4, blackT, blackT},

        {blackT, M1, u7, blackT, blackT, s1},
        {blackT, M2, blackT, blackT, blackT, s2},
        {blackT, M9, blackT, P7, blackT, s3}
};

typedef vector<vector<unsigned int >> vv;
std::vector<std::vector<unsigned int > > texturesMiddle {
        //  B       F       L      R     D     U
        {blackT, blackT,    u2,  blackT, g4, blackT},
        {blackT, blackT,  blackT, blackT,g5, blackT},
        {blackT, blackT,  blackT, P2,    g6, blackT},

        {blackT, blackT, u5, blackT, blackT, blackT},
        {blackT, blackT, blackT, blackT, blackT, blackT},
        {blackT, blackT, blackT, P5, blackT, blackT},

        {blackT, blackT, u8, blackT, blackT, s4},
        {blackT, blackT, blackT, blackT, blackT, s5},
        {blackT, blackT, blackT, P8, blackT, s6}
};

std::vector<std::vector<unsigned int >> texturesBack {
        //  B       F       L       R      D      U
        {C7,      blackT,  u3,    blackT, g7,   blackT},
        {C8,      blackT, blackT, blackT, g8,   blackT},
        {C9,      blackT, blackT, P3,  g9,   blackT},

        {C4,      blackT,  u6,    blackT, blackT, blackT},
        {C5,      blackT, blackT, blackT, blackT, blackT},
        {C6,      blackT, blackT,    P6,  blackT, blackT},

        {C1,      blackT, u9, blackT, blackT, s7},
        {C2,      blackT, blackT, blackT, blackT, s8},
        {C3,      blackT, blackT, P9, blackT, s9}
};
vector<vector<vector<unsigned int>>> texturesCube = {texturesFront, texturesMiddle, texturesBack};
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
        -0.2f,  0.2f, -0.2f, 0.0f, 0.0f
};

typedef glm::vec3 v3;
typedef std::vector<glm::vec3> vv3;
typedef std::vector<vv3> vvv3;

//vector<glm::vec3> colors = { red, green, blue, white, orange, yellow, black };
// red(0), green(1), blue, white, orange, yellow, black
/*std::vector<std::vector<glm::vec3 > > coloresFront {
        //  B(0)    F(1)   L(2)   R(3)  D(4)  U(5)
        vv3{black, white, green, black, red, black}, //0
        vv3{black, white, black, black, red, black}, //1
        vv3{black, white, black, blue, red, black}, //2

        vv3{black, white, green, black, black, black}, //3
        vv3{black, white, black, black, black, black}, //4
        vv3{black, white, black, blue, black, black}, //5

        vv3{black, white, green, black, black, orange}, //6
        vv3{black, white, black, black, black, orange}, //7
        vv3{black, white, black, blue, black, orange}, //8
};*/

/*std::vector<std::vector<glm::vec3 > > coloresMiddle {
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
};*/
/*std::vector<std::vector<glm::vec3 > > coloresBack {
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
};*/


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
        std::make_pair(0, 6), // 0
        std::make_pair(0, 7), // 1
        std::make_pair(0, 8), // 2
        std::make_pair(1, 6), // 3
        std::make_pair(1, 7), // 4
        std::make_pair(1, 8), // 5
        std::make_pair(2, 6), // 6
        std::make_pair(2, 7), // 7
        std::make_pair(2, 8)  // 8
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