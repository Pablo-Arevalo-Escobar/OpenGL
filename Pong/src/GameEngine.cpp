#include "GameEngine.h"
#include<GLFW/glfw3.h>
#include"resource_manager.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

//State Data


GameEngine::GameEngine()
{
}

void GameEngine::menu() {
     ImGui_ImplOpenGL3_NewFrame();
     ImGui_ImplGlfw_NewFrame();
     ImGui::NewFrame();

     {
        static int hWidth = 0;
        static int hHeight = 0;
        ImGui::Begin("DEBUG");                         
        ImGui::Text("PONG");
        ImGui::SliderInt("Width", &hWidth, 10, 100);          
        ImGui::SliderInt("Height", &hHeight, 10, 100);        

        if (ImGui::Button("Update"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        ImGui::SameLine();

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
     }
     ImGui::Render();
     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GameEngine::main_loop(float delta_time, float test)
{
    
    if (state == ENGINE_ACTIVE) {
        processInput(delta_time);
        update(test);
        render(test);
    }
    else if (state == ENGINE_MENU) {
        menu();
    }
    else if (state == ENGINE_WIN) {

    }
}

void GameEngine::init()
{
    //load shader
    ResourceManager::loadShader("src/shader/2d/shader.vert", "src/shader/2d/shader.frag", nullptr, "sprite");
    projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f);
    ResourceManager::getShader("sprite").use();
    ResourceManager::getShader("sprite").setMat4("projection", projection);

    //Define the border
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
    glGenVertexArrays(1, &background_vao);
    glGenBuffers(1, &background_vbo);
    glGenBuffers(1, &background_ebo);
    glBindVertexArray(background_vao);
    glBindBuffer(GL_ARRAY_BUFFER, background_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, background_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indices), square_indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    //Define Border Properties
    width_margin = width * 0.05;
    height_margin = height * 0.05;
    border_height = 0.8 * height;
    border_width = 0.005 * width;
    border_color = glm::vec3(1.0, 1.0, 1.0);

    border_positions[0] = glm::vec3(width_margin, height/2, 0);
    border_positions[1] = glm::vec3(width - width_margin, height / 2, 0);
    border_positions[2] = glm::vec3(width/2, height_margin, 0);
    border_positions[3] = glm::vec3(width/2, height - height_margin, 0);

    //Define Paddle Properties
    double midpoint_x = (((double)width) / 2.0);
    double midpoint_y = (((double)height) / 2.0);

    glm::vec3 STARTING_POSITIONS[3] = {
        glm::vec3(border_positions[0] + glm::vec3(width/20,0,1.0)),
        glm::vec3(border_positions[1] - glm::vec3((width / 20),0,0.0)),
        glm::vec3(glm::vec3(midpoint_x,midpoint_y,1.0))
    };

    paddle_size = glm::vec3(width * 0.025, height * 0.15, 1.0);
    paddles[0] = Paddle(STARTING_POSITIONS[0], paddle_size);
    paddles[1] = Paddle(STARTING_POSITIONS[1], paddle_size);
    paddles[0].velocity = glm::vec3(0, -100, 0)*5.0f;
    paddles[1].velocity = glm::vec3(0, -100, 0)*5.0f;
    paddles[0].score = 0;
    paddles[1].score = 0;
    paddles[0].init();

    border1_hit_time = 0.0;
    border2_hit_time = 0.0;
    //Define Ball starting position and direction
    ball = Ball(STARTING_POSITIONS[2], 1.0, 1.0);
    ball.init();
    //ball.toggleVec();


    //Define the text renderer
    text = TextRenderer(width, height);
    text.Load("res/fonts/Robtronika.ttf", 50);
}

void GameEngine::ball_collision(Ball& ball, Paddle& paddle) {
    glm::vec3 padl_position = paddle.pos;
    float pad1_left_bound = paddle.pos.x - paddle_size.x;
    float pad1_right_bound = paddle.pos.x + paddle_size.x;
    float padl_top_bound = paddle.pos.y - paddle_size.y;
    float padl_bottom_bound = paddle.pos.y + paddle_size.y;
    if ((ball.pos.y > padl_top_bound && ball.pos.y < padl_bottom_bound)) {
        if ((ball.pos.x > pad1_left_bound && ball.pos.x < pad1_right_bound)) {
            ball.velocity.x *= -1;
            if (paddle.pos.x > width / 2) {
                ball.pos.x = pad1_left_bound;
            }
            else {
                ball.pos.x = pad1_right_bound;
            }
        }
    }
}

void GameEngine::update(float ct)
{
    //Will most likely be some key processing which will determine the update calls on the paddles
    unsigned int hit_loc = ball.update();
    if (hit_loc == 0) {
        paddles[1].score += 1;
        border1_hit = true;
    }
    else if(border1_hit && (glfwGetTime()-border1_hit_time) > 1.0) {
        border1_hit = false;
    }
    if (hit_loc == 1) {
        paddles[0].score += 1;
        border2_hit = true;
    }
    else if(border2_hit && (glfwGetTime() - border2_hit_time) > 1.0) {
        border2_hit = false;
    }

    ////Update positions
    paddles[0].update();
    paddles[1].update();

    //Check for collision
    ball_collision(ball, paddles[0]);
    ball_collision(ball, paddles[1]);
}

void GameEngine::render(float ct)
{
    //Render Text - Done before the rest in order to avoid uneccsarily switching VAO
    //Title
    text.RenderText("PONG", 0.36 * width, 0.1 * height, 1.0f, border_color*0.5f);
    //Score
    text.RenderText(std::to_string(paddles[0].score), 0.15 * width, 0.1 * height, 1.0f, border_color);
    text.RenderText(std::to_string(paddles[1].score), 0.8 * width, 0.1 * height, 1.0f, border_color);

    //Render border
    glBindVertexArray(background_vao);
    ResourceManager::getShader("sprite").use();
    ResourceManager::getShader("sprite").setMat4("projection", projection);
    for (int i = 0; i < 4; i++) {
        glm::mat4 model(1.0f);
        model = glm::translate(model, border_positions[i]);
        if (i > 1) {
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
            model = glm::scale(model, glm::vec3(border_width, border_height*1.5, 0));
        }
        else {
            model = glm::scale(model, glm::vec3(border_width, border_height*1.1, 0));
        }
        if (i == 0 && border1_hit) {
            border_color = glm::vec3(1.0, 0.0, 0.0);
            border1_hit_time = ct;
        }
        else if (i == 1 && border2_hit) {
            border_color = glm::vec3(1.0, 0.0, 0.0);
            border2_hit_time = ct;
        }
        else {
            border_color = glm::vec3(1.0, 1.0, 1.0);
        }
        ResourceManager::getShader("sprite").setMat4("model", model);
        ResourceManager::getShader("sprite").setVec3("pixel_color", border_color);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    //Render Center Line
    glm::vec3 center_color(162.0 / 255.0, 152.0 / 255.0, 152.0 / 255.0);
    float step_size = ((float)height - 2*height_margin) / 14;
    for (int i = 0; i < 7; i++) {
        glm::mat4 model(1.0f);
        float step = step_size * i;
        glm::vec3 translation_up(width / 2, ((float)height / 2) - step, 1.0);
        glm::vec3 translation_down(width / 2, ((float)height / 2) + step, 1.0);

        if (i == 0)
        {
            model = glm::translate(model, translation_up);
            model = glm::scale(model, glm::vec3(border_width, border_height / 15, 0));
            ResourceManager::getShader("sprite").setMat4("model", model);
            ResourceManager::getShader("sprite").setVec3("pixel_color", border_color);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        else {
            //Upwards direction
            model = glm::translate(model, translation_up);
            model = glm::scale(model, glm::vec3(border_width, border_height / 15, 0));
            ResourceManager::getShader("sprite").setMat4("model", model);
            ResourceManager::getShader("sprite").setVec3("pixel_color", border_color);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            //downwards translation
            glm::mat4 model(1.0f);
            model = glm::translate(model, translation_down);
            model = glm::scale(model, glm::vec3(border_width, border_height / 15, 0));
            ResourceManager::getShader("sprite").setMat4("model", model);
            ResourceManager::getShader("sprite").setVec3("pixel_color", border_color);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        
    }

    //Render Paddles
    paddles[0].draw(ResourceManager::getShader("sprite"));
    paddles[1].draw(ResourceManager::getShader("sprite"));

    ////Render ball
    ball.draw(ResourceManager::getShader("sprite"));
}

void GameEngine::processInput(float dt)
{
    if (keys[GLFW_KEY_W]) {
      paddles[0].pos += paddles[0].velocity * dt;
    }
    if (keys[GLFW_KEY_S]) {
        paddles[0].pos -= paddles[0].velocity * dt;
    }
    if (keys[GLFW_KEY_UP]) {
        paddles[1].pos += paddles[1].velocity * dt;
    }
    if (keys[GLFW_KEY_DOWN]) {
        paddles[1].pos -= paddles[1].velocity * dt;
    }
    if (keys[GLFW_KEY_TAB]) {
        ball.drawVector = !ball.drawVector;
    }
}
