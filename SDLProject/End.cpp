#include "End.h"
#include "Utility.h"

void End::initialise() {
    m_game_state.next_scene_id = -1; // No transition initially
    m_game_state.player = nullptr;  // No player in the menu
    m_game_state.enemies = nullptr; // No enemies in the menu
    m_game_state.map = nullptr;     // No map in the menu
}

void End::update(float delta_time) {
    // Nothing
}

void End::render(ShaderProgram *program) {
    glClearColor(0.37f, 0.45f, 0.55f, 1.0f); // ash blue color
    glClear(GL_COLOR_BUFFER_BIT);

    glm::vec3 title_position = glm::vec3(0.3f, -2.0f, 0.0f);
    Utility::draw_text(program, Utility::load_texture("assets/font1.png"), "Congrats Looter!", 0.6f, 0.02f, title_position);

    glm::vec3 loot_text = glm::vec3(0.9f, -4.0f, 0.0f);
    Utility::draw_text(program, Utility::load_texture("assets/font1.png"), "Loot collected:", 0.6f, 0.02f, loot_text);
    
    glm::vec3 total_loot = glm::vec3(5.0f, -5.0f, 0.0f);
    std::string items_message = std::to_string(m_items_collected);
    Utility::draw_text(program, Utility::load_texture("assets/font1.png"), items_message, 2.0f, 0.02f, total_loot);
}

void End::set_items_collected(int items_collected) {
    m_items_collected = items_collected;
}
