#pragma once
#include <vector>
#include <string>
#include <glad/glad.h>
#include<glm/glm.hpp>
#define PI 3.14159265

namespace util {
    std::vector<std::string> split(std::string string, char delim);
    glm::vec3 rotate_vec3(glm::vec3 vector, double angle);
    void make_vector();
    void make_circle(float resolution);
    void draw_vector();
    void draw_circle();
}


