#include "Paddle.h"
#include <glm/gtc/matrix_transform.hpp>

unsigned int Paddle::vao{ 0 };
unsigned int Paddle::vbo{ 0 };
unsigned int Paddle::ebo{ 0 };


void Paddle::init()
{
    float square_vertices[] = {
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
       -0.5f,  0.5f, 0.0f
    };
    unsigned int square_indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indices), square_indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void Paddle::update()
{
    float paddle_top = pos.y - (0.5*scale.y);
    float paddle_bottom = pos.y + (0.5*scale.y);
    if (paddle_top < 0 + (600 * 0.05)) {
        pos.y = (0 + (600 * 0.05) + (0.5 * scale.y));

    }
    else if (paddle_bottom > 600 - (600 * 0.05))
    {
        pos.y = (600 - (600 * 0.05)) - (0.5 * scale.y);
    }
}

void Paddle::draw(Shader shader)
{
    glBindVertexArray(vao);
    glm::mat4 model(1.0f);
    model = glm::translate(model, pos);
    model = glm::scale(model, scale);
    shader.setMat4("model", model);
    shader.setVec3("pixel_color", glm::vec3(1.0,1.0,1.0));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}
