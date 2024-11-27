/**
* Author: Yanka Sikder
* Assignment: Platformer
* Date due: 2023-11-26, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#include "End.h"
#include "Utility.h"

void End::initialise() {
    m_game_state.next_scene_id = -1; // No transition initially
    m_game_state.player = nullptr;  // No player in the menu
    m_game_state.enemies = nullptr; // No enemies in the menu
    m_game_state.map = nullptr;     // No map in the menu
}

void End::update(float delta_time) {
    // nothing
}

void End::render(ShaderProgram *program) {
    glClearColor(0.37f, 0.45f, 0.55f, 1.0f); // ash blue color

    glClear(GL_COLOR_BUFFER_BIT);

    glm::vec3 title_position = glm::vec3(4.0f, -3.0f, 0.0f);
    Utility::draw_text(program, Utility::load_texture("assets/font1.png"), "The End", 0.4f, 0.02f, title_position);

    glm::vec3 prompt_position = glm::vec3(4.0f, -5.0f, 0.0f);
    Utility::draw_text(program, Utility::load_texture("assets/font1.png"), "You Won!", 0.4f, 0.02f, prompt_position);
}
