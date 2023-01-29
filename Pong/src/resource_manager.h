/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#pragma once
#include <map>
#include <string>
#include <glad/glad.h>
#include "texture2D.h"
#include "shader.h"

class ResourceManager
{
public:
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture2D> textures;
    static Shader loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
    static Shader getShader(std::string name);
    static Texture2D loadTexture(const char* file, bool alpha, std::string name);
    static Texture2D getTexture(std::string name);
    static void Clear();

private:
    ResourceManager() {}
    static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
    static Texture2D loadTextureFromFile(const char* file, bool alpha);
};

