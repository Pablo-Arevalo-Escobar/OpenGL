#include "Ball.h"
#include "util.h"
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtc/constants.hpp>
#include <glm/gtx/vector_angle.hpp>

void Ball::init()
{
    //Code to generate a circle mesh
    util::make_circle(resolution);
    util::make_vector();
    velocity = glm::vec3(1.0, -1.0, 0.0) * 5.0f;
}

void Ball::resetVelocity()
{
    velocity = glm::vec3(1.0, -1.0, 0.0) * 5.0f;
}

unsigned int Ball::update()
{

    if (pos.x < 0 + (800 * 0.05)) {
        velocity.x *= -1;
        pos.x = 0 + (800 * 0.05);
        pos += velocity;
        return 0;
    }
    else if (pos.x > 800-(800 * 0.05))
    {
        velocity.x *= -1;
        pos.x = 800 - (800 * 0.05);
        pos += velocity;
        return 1;
    }

    if (pos.y < 0 + (600 * 0.05)) {
        velocity.y *= -1;
        pos.y = 0 + (600 * 0.05);


    }
    else if (pos.y > 600-(600 * 0.05))
    {
        velocity.y *= -1;
        pos.y = 600 - (600 * 0.05);

    }

    pos += velocity;
    return 2;
}



void Ball::draw(Shader shader)
{
    shader.use();
    glm::mat4 model(1.0f);
    model = glm::translate(model, pos);
    model = glm::scale(model, glm::vec3(10,10,1));
    shader.setMat4("model", model);
    shader.setVec3("pixel_color", glm::vec3(1,1,1));
    util::draw_circle();

    if (drawVector) {
        glm::vec3 original_position = glm::vec3(0.0, -1.0f, 0.0f);
        float dot_product = glm::dot(glm::normalize(velocity), original_position);
        float length_product = (velocity.length() * original_position.length());
        float angle = glm::acos(dot_product / length_product);
        angle = glm::orientedAngle(original_position, glm::normalize(-velocity), glm::vec3(0, 0, 1));

        model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        model = glm::scale(model, glm::vec3(50, 50, 1));
        model = glm::rotate(model, angle, glm::vec3(0, 0, 1));

        shader.setMat4("model", model);
        shader.setVec3("pixel_color", glm::vec3(1, 1, 0));
        util::draw_vector();
    }
   
}
