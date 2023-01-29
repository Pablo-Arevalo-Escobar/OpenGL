#include "texture2D.h"

Texture2D::Texture2D()
    : width(0), height(0), internal_format(GL_RGB), image_format(GL_RGB), wrap_mode_s(GL_REPEAT), wrap_mode_t(GL_REPEAT), filter_min(GL_LINEAR), filter_max(GL_LINEAR)
{
    glGenTextures(1, &this->id);
}


void Texture2D::generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->width = width;
    this->height = height;
    // create Texture
    glBindTexture(GL_TEXTURE_2D, this->id);
    glTexImage2D(GL_TEXTURE_2D, 0, this->internal_format, width, height, 0, this->image_format, GL_UNSIGNED_BYTE, data);
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_mode_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_mode_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max);
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void const Texture2D::bind()
{
    glBindTexture(GL_TEXTURE_2D, this->id);
}
