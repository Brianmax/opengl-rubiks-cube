#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#define red glm::vec4(1.0,0.0,0.0,1.0)
#define green glm::vec4(0.0,1.0,0.0,1.0)
#define blue glm::vec4(0.0,0.0,1.0,1.0)
#define white glm::vec4(1.0,1.0,1.0,1.0)
#define orange glm::vec4(1.0,0.5,0.0,1.0)
#define yellow glm::vec4(1.0,1.0,0.0,1.0)
#define black glm::vec4(0.0,0.0,0.0,1.0)

float cube_vertices[] = {
        // up
        -0.2f, -0.2f, -0.2f,
        0.2f, -0.2f, -0.2f,
        0.2f,  0.2f, -0.2f,
        0.2f,  0.2f, -0.2f,
        -0.2f,  0.2f, -0.2f,
        -0.2f, -0.2f, -0.2f,

        -0.2f, -0.2f,  0.2f,
        0.2f, -0.2f,  0.2f,
        0.2f,  0.2f,  0.2f,
        0.2f,  0.2f,  0.2f,
        -0.2f,  0.2f,  0.2f,
        -0.2f, -0.2f,  0.2f,

        -0.2f,  0.2f,  0.2f,
        -0.2f,  0.2f, -0.2f,
        -0.2f, -0.2f, -0.2f,
        -0.2f, -0.2f, -0.2f,
        -0.2f, -0.2f,  0.2f,
        -0.2f,  0.2f,  0.2f,

        0.2f,  0.2f,  0.2f,
        0.2f,  0.2f, -0.2f,
        0.2f, -0.2f, -0.2f,
        0.2f, -0.2f, -0.2f,
        0.2f, -0.2f,  0.2f,
        0.2f,  0.2f,  0.2f,

        -0.2f, -0.2f, -0.2f,
        0.2f, -0.2f, -0.2f,
        0.2f, -0.2f,  0.2f,
        0.2f, -0.2f,  0.2f,
        -0.2f, -0.2f,  0.2f,
        -0.2f, -0.2f, -0.2f,

        -0.2f,  0.2f, -0.2f,
        0.2f,  0.2f, -0.2f,
        0.2f,  0.2f,  0.2f,
        0.2f,  0.2f,  0.2f,
        -0.2f,  0.2f,  0.2f,
        -0.2f,  0.2f, -0.2f
};
std::vector<glm::vec4> cubeColorsFront = {
    white, red, green, blue, orange, black
};
std::vector<glm::vec3> cubePositionsFront = {
        glm::vec3(-0.8f, -0.8f, 0.0f),
        glm::vec3(-0.3f, -0.8f, 0.0f),
        glm::vec3(0.2f, -0.8f, 0.0f),

        glm::vec3(-0.8f, -0.3f, 0.0f),
        glm::vec3(-0.3f, -0.3f, 0.0f),
        glm::vec3(0.2f, -0.3f, 0.0f),

        glm::vec3(-0.8f, 0.2f, 0.0f),
        glm::vec3(-0.3f, 0.2f, 0.0f),
        glm::vec3(0.2f, 0.2f, 0.0f),
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
std::vector<glm::vec3> cubePositionsBack {
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

std::vector<std::vector<glm::vec3>> positions = {cubePositionsFront, cubePositionsMiddle, cubePositionsBack};