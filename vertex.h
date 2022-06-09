#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#define red glm::vec3(1.0,0.0,0.0)
#define green glm::vec3(0.0,1.0,0.0)
#define blue glm::vec3(0.0,0.0,1.0)
#define white glm::vec3(1.0,1.0,1.0)
#define orange glm::vec3(1.0,0.5,0.0)
#define yellow glm::vec3(1.0,1.0,0.0)
#define black glm::vec3(0.0,0.0,0.0)

float cube_vertices[] = {
        // back
        -0.2f, -0.2f, -0.2f,
        0.2f, -0.2f, -0.2f,
        0.2f,  0.2f, -0.2f,
        0.2f,  0.2f, -0.2f,
        -0.2f,  0.2f, -0.2f,
        -0.2f, -0.2f, -0.2f,
        //front
        -0.2f, -0.2f,  0.2f,
        0.2f, -0.2f,  0.2f,
        0.2f,  0.2f,  0.2f,
        0.2f,  0.2f,  0.2f,
        -0.2f,  0.2f,  0.2f,
        -0.2f, -0.2f,  0.2f,
        //left
        -0.2f,  0.2f,  0.2f,
        -0.2f,  0.2f, -0.2f,
        -0.2f, -0.2f, -0.2f,
        -0.2f, -0.2f, -0.2f,
        -0.2f, -0.2f,  0.2f,
        -0.2f,  0.2f,  0.2f,
        //right
        0.2f,  0.2f,  0.2f,
        0.2f,  0.2f, -0.2f,
        0.2f, -0.2f, -0.2f,
        0.2f, -0.2f, -0.2f,
        0.2f, -0.2f,  0.2f,
        0.2f,  0.2f,  0.2f,
        //down
        -0.2f, -0.2f, -0.2f,
        0.2f, -0.2f, -0.2f,
        0.2f, -0.2f,  0.2f,
        0.2f, -0.2f,  0.2f,
        -0.2f, -0.2f,  0.2f,
        -0.2f, -0.2f, -0.2f,
        //up
        -0.2f,  0.2f, -0.2f,
        0.2f,  0.2f, -0.2f,
        0.2f,  0.2f,  0.2f,
        0.2f,  0.2f,  0.2f,
        -0.2f,  0.2f,  0.2f,
        -0.2f,  0.2f, -0.2f
};
std::vector<glm::vec3> cubeColorsFront = {
    yellow, white, green, blue, red, orange
};
typedef std::vector<glm::vec3> vv3;
typedef std::vector<vv3> vvv3;
std::vector<std::vector<glm::vec3 > > coloresFront {
    //  B       F       L      R     D     U
    vv3{black, white, green, black, red, black},
    vv3{black, white, black, black, red, black},
    vv3{black, white, black, blue, red, black},

    vv3{black, white, green, black, black, black},
    vv3{black, white, black, black, black, black},
    vv3{black, white, black, blue, black, black},

    vv3{black, white, green, black, black, orange},
    vv3{black, white, black, black, black, orange},
    vv3{black, white, black, blue, black, orange},
};


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