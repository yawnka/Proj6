/**
* Author: Yanka Sikder
* Assignment: Final Proj 6 : Where's the Loot?
* Date due: 12/11/2024, 2:00pm
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
    
    glm::vec3 comment_position = glm::vec3(3.5f, -5.6f, 0.0f);
    std::string comment_message;

    if (m_items_collected < 5) {
        comment_message = "Noob status";
    } else if (m_items_collected > 10 && m_items_collected < 20) {
        comment_message = "Great job!";
    } else if (m_items_collected >= 20) {
        comment_message = "Master looter over here!";
    }

    Utility::draw_text(program, Utility::load_texture("assets/font1.png"), comment_message, 0.4f, 0.02f, comment_position);
}

void End::set_items_collected(int items_collected) {
    m_items_collected = items_collected;
}


