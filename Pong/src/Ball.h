#pragma once
#include <glm/glm.hpp>
#include  "shader.h"
//For now constant speed
class Ball
{
private:
    
    float radius;
    float resolution = 50;
    static int vao, vbo, ebo;
public:
    glm::vec3 pos, velocity;
    bool drawVector = false;
    float speed;
    Ball() : pos{ 0,0,0 }, speed(1.0), radius(0.5), resolution(10.0) {}
    Ball(glm::vec3 position, float vel, float rad) : pos(position), speed(vel), radius(rad) {}
    void init();
    void resetVelocity();
    unsigned int update();
    void draw(Shader shader);
};
