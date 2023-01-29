#pragma once
#include <glad/glad.h>
class Texture2D
{
public:
    unsigned int id;
    unsigned int width, height;
    unsigned int internal_format;
    unsigned int image_format;

    unsigned int wrap_mode_s, wrap_mode_t;
    unsigned int filter_min, filter_max;
    Texture2D();
    void generate(unsigned int width, unsigned int height, unsigned char* data);
    void  const bind();
};

