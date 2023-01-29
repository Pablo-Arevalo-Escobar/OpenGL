#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "Shader.h"


class Paddle
{

public:
    unsigned int score;
    glm::vec3 pos, scale, velocity;
    Paddle() : pos{ 0,0,0 }, scale(glm::vec3(1.0,1.0,1.0)) {}
    Paddle(glm::vec3 position, glm::vec3 size) : pos(position), scale(size) {}
    void init();
    void update();
    void draw(Shader shader);
private:
    static unsigned int vao, vbo, ebo;
};
