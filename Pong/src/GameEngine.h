#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "Ball.h"
#include "Paddle.h"
#include "TextRenderer.h"


enum EngineState {
    ENGINE_ACTIVE,
    ENGINE_MENU,
    ENGINE_WIN
};


class GameEngine
{
public:
    GameEngine();
    GameEngine(unsigned int height, unsigned int width) : height(height), width(width) { }
    void main_loop(float dt, float test);
    void init();
    void menu();
    void update(float ct);
    void processInput(float dt);
    void render(float ct);
    void ball_collision(Ball& ball, Paddle& paddle);

public:
    bool keys[1024];
private:
    EngineState state = ENGINE_ACTIVE;
    double border1_hit_time = 0;
    double border2_hit_time = 0;
    bool border1_hit = false;
    bool border2_hit = false;

    //Define Border Properties
    float width_margin;
    float height_margin;
    float border_height;
    float border_width;
    glm::vec3 border_color;
    glm::vec3 border_positions[4];
    glm::vec3 paddle_size;
    glm::mat4 projection;

    unsigned int width, height;
    const float ball_speed = 2;
    const float paddle_speed = 2;
    Paddle paddles[2];
    Ball ball;
    Shader shader;
    TextRenderer text;
    unsigned int background_vao, background_vbo, background_ebo;

};