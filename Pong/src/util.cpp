// Circle Vertex Definition

#pragma once
#include"util.h"
unsigned int circle_vao, circle_vbo, circle_ebo, circle_indices_size;
unsigned int vector_vao, vector_vbo, vector_ebo, vector_indices_size;
std::vector<std::string> util::split(std::string string, char delim) {
    std::vector<std::string> splitArr;
    int end = 0;
    while ((end = string.find(delim)) != std::string::npos)
    {
        splitArr.push_back(string.substr(0, end));
        string = string.substr(end + 1);
    }
    splitArr.push_back(string.substr(0, end));
    return splitArr;
}

glm::vec3 util::rotate_vec3(glm::vec3 vector, double angle)
{
    double x = vector.x;
    double y = vector.y;
    vector.x = (x * cos(angle)) - (y * sin(angle));
    vector.y = y * cos(angle) + x * sin(angle);
    return vector;
}



void util::make_vector() {
    float vertices[] = {
         0.05f,  0.75f, 0.0f,  // top right
         0.05f, -0.0f, 0.0f,  // bottom right
        -0.05f, -0.0f, 0.0f,  // bottom left
        -0.05f,  0.75f, 0.0f,   // top left 

        0.0f,1.0f,0.0f,
        -0.2f,0.75f,0.0f,
        0.2f,0.75f,0.0f
        

    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3,  // second Triangle
        4,5,6
    };
    glGenVertexArrays(1, &vector_vao);
    glGenBuffers(1, &vector_vbo);
    glGenBuffers(1, &vector_ebo);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(vector_vao);

    glBindBuffer(GL_ARRAY_BUFFER, vector_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vector_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
















    //float vertices[] = {
    //    -0.25f, 0.5f, 0.0f,
    //    -0.25f, -0.5f, 0.0f,
    //     0.25f, -0.5f,0.0f
    //     /*0.25f,0.5f,1.0f,

    //     -0.5f,0.5f,1.0f,
    //     0.5f,0.5f,1.0f,
    //     0.0f,0.75f,1.0f*/
    //};

    //unsigned int indices[]
    //{
    //    0,1,2
    //    /*2,3,0,
    //    4,5,6*/
    //};

    //glGenVertexArrays(1, &vector_vao);
    //glGenBuffers(1, &vector_vbo);
    //glGenBuffers(1, &vector_ebo);
    //glBindVertexArray(vector_vao);
    //glBindBuffer(GL_ARRAY_BUFFER, vector_vbo);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vector_ebo);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices), indices,
    //    GL_STATIC_DRAW);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
    //    (void*)0);
    //glEnableVertexAttribArray(0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vector_ebo);
}

void util::draw_vector() {
    glBindVertexArray(vector_vao);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void util::make_circle(float resolution) {
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;
    float angle = (2 * PI) / float(resolution);
    int vertex_number = resolution * 3;

    float x = 0;
    float y = 1;
    float x1, y1;
    glm::vec3 p0, p1;

    vertices.push_back(glm::vec3(0, 0, 0));
    vertices.push_back(glm::vec3(x, y, 0));
    for (int i = 0; i < resolution; i++) {
        p0 = glm::vec3(x, y, 0);
        x1 = x * cos(angle) - y * sin(angle);
        y1 = y * cos(angle) + x * sin(angle);
        p1 = glm::vec3(x1, y1, 0);
        x = x1;
        y = y1;
        vertices.push_back(p1);
        indices.push_back(i + 1);
        indices.push_back(0);
        indices.push_back(i + 2);
    }

    circle_indices_size = indices.size();
    //create vao
    glGenVertexArrays(1, &circle_vao);
    glGenBuffers(1, &circle_vbo);
    glGenBuffers(1, &circle_ebo);
    glBindVertexArray(circle_vao);
    glBindBuffer(GL_ARRAY_BUFFER, circle_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, circle_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0],
        GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
        (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, circle_ebo);
}

void util::draw_circle() {
    glBindVertexArray(circle_vao);
    glDrawElements(GL_TRIANGLES, circle_indices_size, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}