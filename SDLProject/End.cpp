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
    //glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // grey Solid color background
    //glClearColor(1.1f, 1.1f, 1.1f, 1.0f); // white Solid color background
    glClearColor(0.8f, 0.9f, 0.75f, 1.0f); // Light matcha green Solid color background

    glClear(GL_COLOR_BUFFER_BIT);

    glm::vec3 title_position = glm::vec3(1.0f, -2.0f, 0.0f);
    Utility::draw_text(program, Utility::load_texture("assets/font1.png"), "The End", 0.4f, 0.02f, title_position);

    glm::vec3 prompt_position = glm::vec3(1.0f, -4.0f, 0.0f);
    Utility::draw_text(program, Utility::load_texture("assets/font1.png"), "You Won!", 0.4f, 0.02f, prompt_position);
}
