#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
float cube_vertices[] = {
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