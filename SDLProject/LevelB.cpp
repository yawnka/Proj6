#include "LevelB.h"
#include "Utility.h"

#define LEVEL_WIDTH 30
#define LEVEL_HEIGHT 30

#include <cstdlib>
#include <ctime>


constexpr char SPRITESHEET_FILEPATH[] = "assets/player0.png",
           ENEMY_FILEPATH[]       = "assets/enemy.png";


unsigned int LEVEL2_DATA[] =
{
    22,23,24,24,22,23,24,24,23,24,24,22,23,24,22,23,24,23,24,22,23,21,22,23,24,21,22,23,24,24,
    22,23,24,24,22,23,24,22,23,24,22,23,24,21,22,23,24,23,24,22,23,21,22,23,24,21,22,23,24,23,
    22,23,24,24,22,23,24,22,23,24,22,23,24,21,22,23,24,23,24,22,21,22,23,24,23,21,22,23,24,23,
    22,23,24,21,22,23,24,23,24,24,23,24,23,21,22,23,24,23,24,22,21,22,23,24,23,21,22,23,24,23,
    22,23,24,22,23,24,24,23,24,24,23,24,23,21,22,23,24,23,24,22,21,22,23,24,22,21,22,23,24,23,
    22,23,24,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,24,22,23,
    22,23,24,30,145,146,147,148,144,144,144,144,144,144,144,144,144,144,144,144,143,143,143,143,144,31,32,24,22,23,
    22,23,24,30,145,125,126,127,128,143,143,145,146,147,148,144,126,127,127,143,125,126,127,128,143,144,32,24,22,23,
    22,23,24,30,145,146,147,148,143,144,114,115,114,115,148,143,143,143,143,125,126,127,128,143,144,144,32,24,22,23,
    21,22,23,30,145,125,126,127,128,125,125,145,146,147,114,125,126,127,128,125,126,127,128,143,143,144,32,21,22,23,
    21,22,23,30,114,115,147,148,143,144,125,145,146,147,148,125,126,143,143,144,125,126,127,128,144,127,32,21,22,23,
    21,22,23,30,143,114,115,127,143,144,125,126,114,115,114,115,126,143,144,126,125,125,126,127,128,127,32,21,22,23,
    21,22,23,30,143,125,126,127,128,144,127,125,114,115,147,125,126,127,128,126,114,115,147,148,144,127,32,21,22,23,
    21,22,23,30,143,114,114,115,125,143,125,126,127,128,146,125,126,127,128,126,145,146,147,148,144,127,32,21,22,23,
    21,22,23,30,114,115,115,127,125,143,143,145,146,147,125,126,127,128,144,127,125,114,115,143,144,127,32,21,22,23,
    21,22,23,30,143,114,115,114,115,143,114,115,126,127,145,146,147,148,143,144,125,126,127,114,115,127,32,21,22,23,
    21,22,23,30,143,145,146,147,148,114,115,144,126,127,126,143,144,126,143,125,126,127,128,143,144,127,32,21,22,23,
    21,22,23,30,143,114,115,125,114,115,115,143,144,127,126,143,144,126,127,125,126,127,128,143,144,127,32,21,22,23,
    21,22,23,30,114,114,114,114,114,115,125,143,144,125,126,143,144,126,127,143,144,114,115,143,144,127,32,21,22,23,
    21,22,23,30,114,115,126,143,144,127,125,125,126,127,128,144,114,115,127,143,114,115,126,114,115,144,32,21,22,23,
    21,22,23,30,114,125,126,127,128,115,126,143,144,125,143,145,125,126,127,128,125,126,127,128,143,144,32,21,22,23,
    22,21,22,30,114,115,114,115,127,125,126,143,144,125,143,144,125,125,114,145,146,147,114,115,143,144,32,21,22,23,
    22,21,22,30,114,115,143,145,125,126,127,128,126,127,128,148,148,114,115,127,143,114,125,126,127,128,32,21,22,23,
    22,21,22,30,114,115,143,144,127,125,143,144,126,125,126,127,128,115,115,126,143,144,125,126,143,144,32,21,22,23,
    22,21,22,30,114,114,115,147,114,115,144,144,114,115,114,115,115,114,125,126,127,128,125,143,144,144,32,21,22,23,
    22,21,22,30,114,145,146,125,126,127,128,127,114,115,115,145,114,115,148,144,144,114,125,126,127,128,32,21,22,23,
    22,21,22,30,114,114,115,143,144,114,115,115,114,114,115,143,144,144,144,144,144,114,115,143,144,144,32,21,22,23,
    22,21,22,86,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,57,21,22,23,
    21,22,21,22,23,21,22,23,24,24,21,21,22,23,24,21,22,23,24,22,23,24,24,21,22,23,21,21,22,23,
    21,22,21,22,21,21,21,22,23,24,21,21,22,23,24,21,22,23,24,22,23,24,24,21,22,23,21,21,22,23
};

unsigned int SECOND_LAYER_LVL2DATA[] =
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,119,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,26,27,27,27,27,27,27,27,28,0,134,134,26,27,27,27,27,27,27,27,28,0,0,0,0,
    0,0,0,0,0,50,0,0,0,0,0,0,0,50,0,134,134,50,0,0,0,0,0,0,0,50,0,0,0,0,
    0,0,0,0,0,50,0,0,0,0,0,0,0,77,0,103,0,50,0,0,0,0,0,0,0,50,0,0,0,0,
    0,0,0,0,0,50,0,0,0,0,0,0,0,115,0,103,0,50,0,0,0,0,0,0,0,50,0,0,0,0,
    0,0,0,0,0,50,0,0,0,0,0,0,0,115,103,103,0,50,0,0,0,0,0,0,0,50,0,0,0,0,
    0,0,0,0,0,50,0,0,0,0,0,0,0,25,102,102,0,50,0,0,0,0,0,0,0,50,0,0,0,0,
    0,0,0,0,0,50,0,0,0,0,0,0,0,50,131,132,0,78,79,79,79,81,79,79,79,80,0,0,0,0,
    0,0,0,0,119,78,79,79,79,54,79,79,79,80,151,152,0,119,0,0,0,0,119,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,117,0,149,150,0,0,0,
    0,0,0,0,133,135,133,153,133,133,135,134,133,133,134,153,133,133,133,133,134,147,135,133,121,0,0,0,0,0,
    0,0,0,0,134,133,133,133,135,133,147,133,133,133,133,135,134,133,135,134,147,134,133,135,153,0,0,0,0,0,
    0,0,0,0,0,225,226,227,0,225,226,227,0,225,226,227,0,225,226,227,0,225,226,227,0,149,150,0,0,0,
    0,0,0,0,0,241,242,243,0,241,242,243,0,241,242,243,0,241,242,243,0,241,242,243,0,0,0,0,0,0,
    0,0,0,0,0,257,258,259,0,257,258,259,0,257,258,259,119,257,258,259,0,257,258,259,0,0,0,0,0,0,
    0,0,0,0,0,273,274,230,0,273,274,230,0,273,274,230,0,273,274,230,0,273,274,230,0,0,0,0,0,0,
    0,0,0,0,0,289,290,291,0,289,290,291,0,289,290,291,0,289,290,291,0,289,290,291,0,0,116,0,0,0,
    0,0,0,0,114,225,226,227,116,225,226,227,119,225,226,227,0,225,226,227,0,225,226,227,0,0,0,0,0,0,
    0,0,0,0,119,241,242,243,0,241,242,243,0,241,242,243,114,241,242,243,0,241,242,243,116,119,0,0,0,0,
    0,0,0,0,0,257,258,259,0,257,258,259,0,257,258,259,0,257,258,259,0,257,258,259,0,0,0,0,0,0,
    0,0,0,0,119,273,274,230,0,273,274,230,0,273,274,230,0,273,274,230,0,273,274,230,0,0,0,0,0,0,
    0,0,0,0,0,289,290,291,0,289,290,291,0,289,290,291,0,289,290,291,0,289,290,291,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
    
LevelB::~LevelB()
{
    delete [] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    delete[] m_game_state.items;
//    Mix_FreeChunk(m_game_state.jump_sfx);
//    Mix_FreeMusic(m_game_state.bgm);
    if (m_game_state.jump_sfx)
    {
        Mix_FreeChunk(m_game_state.jump_sfx);
        m_game_state.jump_sfx = nullptr;
    }

    if (m_game_state.bgm)
    {
        Mix_FreeMusic(m_game_state.bgm);
        m_game_state.bgm = nullptr;
    }
}

void LevelB::initialise()
{
    m_number_of_enemies = 4;
    m_game_state.next_scene_id = -1;
    
    GLuint map_texture_id = Utility::load_texture("assets/farm_tileset.png");
    m_game_state.map = new Map(
        LEVEL_WIDTH,      // Width of the map in tiles
        LEVEL_HEIGHT,     // Height of the map in tiles
        LEVEL2_DATA,      // First layer tile data
        map_texture_id,   // Texture ID of the tileset
        1.0f,             // Tile size in game units
        16,               // Tile count (columns) in the tileset
        19,               // Tile count (rows) in the tileset
        SECOND_LAYER_LVL2DATA // Second layer tile data
    );
    
    GLuint* item_textures = new GLuint[ITEM_COUNT];
    // items!
    item_textures[0] = Utility::load_texture("assets/6.png");
    item_textures[1] = Utility::load_texture("assets/7.png");
    item_textures[2] = Utility::load_texture("assets/9.png");
    item_textures[3] = Utility::load_texture("assets/5.png");
    item_textures[4] = Utility::load_texture("assets/1.png");
    item_textures[5] = Utility::load_texture("assets/8.png");
    
    glm::vec3* item_positions = new glm::vec3[ITEM_COUNT] {
        glm::vec3(16.1f, -6.11f, 0.0f),
        glm::vec3(8.3f, -25.9f, 0.0f),
        glm::vec3(25.12f, -25.8f, 0.0f),
        glm::vec3(23.02f, -9.0f, 0.0f),
        glm::vec3(19.95f, -17.00f, 0.0f),
        glm::vec3(3.7f, -6.12f, 0.0f)
    };
    
    m_game_state.items = new Entity[ITEM_COUNT];

    for (int i = 0; i < ITEM_COUNT; i++) {
        // Assign textures and properties
        m_game_state.items[i] = Entity(
            item_textures[i % ITEM_COUNT], // Cycle through item textures
            0.0f,                        // Speed (not moving)
            0.5f,                        // Width
            0.5f,                        // Height
            ITEM                         // Entity type
        );

        m_game_state.items[i].set_position(item_positions[i]);
    }

    
    // Code from main.cpp's initialise()
    /**
     George's Stuff
     */
    // Existing
    int player_walking_animation[4][4] =
    {
        { 0, 1, 2, 3 },  // for PLAYER to move to the left,
        { 4, 5, 6, 7 }, // for PLAYER to move to the right,
        { 8, 9, 10, 11 }, // for PLAYER to move upwards,
        { 12, 13, 14, 15 }   // for PLAYER to move downwards
    };

    glm::vec3 acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    
    GLuint player_texture_id = Utility::load_texture(SPRITESHEET_FILEPATH);
    
    m_game_state.player = new Entity(
        player_texture_id,         // texture id
        3.0f,                      // speed
        acceleration,              // acceleration
        4.0f,                      // jumping power
        player_walking_animation,  // animation index sets
        0.0f,                      // animation time
        4,                         // animation frame amount
        0,                         // current animation index
        4,                         // animation column amount
        4,                         // animation row amount
        0.65f,                      // width
        0.65f,                      // height
        PLAYER
    );
    m_game_state.player->m_visual_scale = 2.0f;
    
    player_initial_position = glm::vec3(5.0f, -17.1f, 0.0f);
    m_game_state.player->set_position(player_initial_position);
    
    /**
    Enemies' stuff */
    GLuint enemy_texture_id = Utility::load_texture(ENEMY_FILEPATH);

    int enemy_walking_animation[4][4] = {
        {8, 9, 10, 11}, // Left
        {4, 5, 6, 7},   // Right
        {0, 1, 2, 3}, // Up
        {12, 13, 14, 15} // Down
    };
    m_game_state.enemies = new Entity[ENEMY_COUNT];
    glm::vec3 enemy_acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

    m_game_state.enemies = new Entity[ENEMY_COUNT];

    for (int i = 0; i < ENEMY_COUNT; ++i) {
        m_game_state.enemies[i] = Entity(
            enemy_texture_id,          // texture id
            2.0f,                      // speed
            enemy_acceleration,        // acceleration
            1.0f,                      // jumping power (or adjust as needed)
            enemy_walking_animation,   // animation frames
            0.0f,                      // animation time
            4,                         // animation frame amount
            0,                         // current animation index
            4,                         // animation column amount
            4,                         // animation row amount
            0.65f,                     // width
            0.65f,                     // height
            ENEMY                      // type
        );
        m_game_state.enemies[i].m_visual_scale = 1.0f; // scale of enemies
    }
    m_game_state.enemies[0].set_position(glm::vec3(9.7f, -10.2f, 0.0f));
    m_game_state.enemies[0].set_ai_type(GUARD);
    m_game_state.enemies[0].set_ai_state(IDLE);
    
    m_game_state.enemies[1].set_position(glm::vec3(16.0f, -16.125f, 0.0f));
    m_game_state.enemies[1].set_ai_type(PATROL);
    m_game_state.enemies[1].set_ai_state(PATROLLING);
    m_game_state.enemies[1].set_movement(glm::vec3(-1.0f, 0.0f, 0.0f));
    m_game_state.enemies[1].set_speed(1.5f);
    
    m_game_state.enemies[2].set_position(glm::vec3(18.1f, -10.7f, 0.0f));
    m_game_state.enemies[2].set_ai_type(PATROL);
    m_game_state.enemies[1].set_ai_state(PATROLLING);
    m_game_state.enemies[1].set_movement(glm::vec3(-1.0f, 0.0f, 0.0f));
    m_game_state.enemies[1].set_speed(1.5f);
    
    m_game_state.enemies[3].set_position(glm::vec3(21.4f, -22.64f, 0.0f));
    m_game_state.enemies[3].set_walking(enemy_walking_animation);
    m_game_state.enemies[3].set_ai_type(SHOOTER);
    m_game_state.enemies[3].set_ai_state(SHOOTING);
    m_game_state.enemies[3].set_jumping_power(2.0f);
    GLuint projectile_texture1 = Utility::load_texture("assets/bullet.png");
    m_game_state.enemies[3].set_projectile_texture(projectile_texture1);
    
    /**
     BGM and SFX
     */
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        std::cout << "Error initializing SDL_mixer: " << Mix_GetError() << std::endl;
    }

    // Load and play background music
    m_game_state.bgm = Mix_LoadMUS("assets/Village_Consort.mp3");
    if (!m_game_state.bgm)
    {
        std::cout << "Failed to load BGM: " << Mix_GetError() << std::endl;
    }
    else
    {
        Mix_PlayMusic(m_game_state.bgm, -1); // Play music in a loop
        Mix_VolumeMusic(MIX_MAX_VOLUME / 2); // Set volume to 50% of the max
    }
    
    m_game_state.jump_sfx = Mix_LoadWAV("assets/jump.wav");
}

void LevelB::update(float delta_time)
{
    m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, ENEMY_COUNT, m_game_state.map);
    
    for (int i = 0; i < m_number_of_enemies; i++)
    {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, NULL, NULL, m_game_state.map);
    }

    float transition_min_x = 26.0f;
    float transition_max_x = 26.5f;
    float transition_min_y = -17.1f;
    float transition_max_y = -15.9f;

    // Get the player's current position
    glm::vec3 player_position = m_game_state.player->get_position();
    
    //debugging command
    std::cout << "Player Position: (" << player_position.x << ", " << player_position.y << ")" << std::endl;

    // Add a small epsilon for floating-point comparison
    float epsilon = 0.01f;
    
    if (player_position.x >= transition_min_x - epsilon && player_position.x <= transition_max_x + epsilon &&
        player_position.y >= transition_min_y - epsilon && player_position.y <= transition_max_y + epsilon)
    {
        m_game_state.next_scene_id = 2;
    }

}

void LevelB::render(ShaderProgram *program)
{
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    m_game_state.map->render(program);
    m_game_state.player->render(program);
    for (int i = 0; i < m_number_of_enemies; i++)
            m_game_state.enemies[i].render(program);
    for (int i = 0; i < ITEM_COUNT; i++) {
        if (m_game_state.items[i].is_active()) {
            m_game_state.items[i].render(program);
        }
    }

}

glm::vec3 LevelB::get_player_initial_position() const {
    return player_initial_position;
}

