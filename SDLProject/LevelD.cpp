#include "LevelD.h"
#include "Utility.h"

#define LEVEL_WIDTH 30
#define LEVEL_HEIGHT 30

#include <cstdlib>
#include <ctime>


constexpr char SPRITESHEET_FILEPATH[] = "assets/player0.png",
           ENEMY_FILEPATH[]       = "assets/enemy.png";


unsigned int LEVEL4_DATA[] =
{
    22,21,21,22,23,24,21,22,23,21,22,23,24,21,22,23,24,23,24,21,21,22,23,24,22,23,21,22,23,24,
    22,21,21,22,23,24,21,22,23,21,22,23,24,21,22,23,24,23,24,21,21,22,23,24,22,23,21,22,23,24,
    22,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,23,24,
    22,30,125,145,146,125,125,125,125,125,125,125,125,125,125,125,126,127,128,128,125,126,127,125,126,127,128,32,23,24,
    22,30,125,143,144,127,143,144,125,143,125,126,127,128,125,126,127,143,144,128,128,128,125,125,126,143,144,32,23,24,
    31,31,153,133,134,135,153,153,133,134,135,153,153,133,134,135,153,153,133,134,135,125,126,127,126,127,128,32,23,24,
    31,31,153,153,153,133,134,135,153,153,154,155,153,153,133,134,135,133,134,135,155,125,126,127,125,126,127,32,22,23,
    22,21,30,125,126,133,125,126,127,125,125,125,126,127,128,125,126,127,128,133,133,125,126,127,128,127,145,32,22,23,
    22,21,30,125,126,133,125,126,127,126,143,144,126,127,128,143,144,125,126,133,154,125,126,127,128,127,128,32,24,23,
    21,22,30,143,144,133,125,126,145,145,128,125,126,127,143,144,128,125,126,133,133,125,126,127,145,127,128,32,24,23,
    21,22,30,125,126,133,128,127,128,145,126,127,125,126,127,128,125,126,127,154,114,125,126,127,128,127,128,32,24,23,
    21,21,30,125,145,133,143,144,126,125,126,127,144,126,125,126,127,126,127,133,133,127,128,128,125,126,127,32,24,23,
    21,22,30,125,125,133,127,125,126,127,128,127,128,125,126,127,128,128,145,114,154,125,126,127,128,128,128,32,24,23,
    21,22,55,56,38,38,56,56,56,56,87,87,87,87,87,87,87,88,56,91,91,56,56,56,56,56,56,57,24,23,
    21,22,23,21,109,109,21,21,21,22,21,22,23,24,21,22,23,21,22,91,91,22,23,24,24,21,22,23,24,23,
    21,22,23,21,109,109,21,21,22,21,21,22,23,24,21,22,23,21,22,109,109,22,23,24,24,21,22,23,24,23,
    21,21,1,2,2,2,2,2,2,2,3,22,23,24,21,22,23,21,22,109,109,22,23,24,24,21,22,23,24,23,
    21,21,30,125,129,130,129,130,126,127,32,22,23,1,2,2,2,2,2,2,2,2,2,2,2,2,3,23,24,23,
    21,21,30,143,144,127,125,125,126,127,32,21,22,30,125,126,125,126,127,125,126,127,127,125,126,127,32,23,24,23,
    21,21,30,125,126,127,145,146,147,148,32,21,22,30,125,129,130,147,127,125,126,127,146,147,148,127,32,22,23,24,
    21,21,30,145,145,146,148,125,126,127,32,21,22,30,125,126,125,125,126,125,126,127,129,130,126,127,32,22,23,24,
    21,21,30,125,126,143,144,125,126,127,32,21,22,30,125,145,146,125,146,125,126,127,127,125,126,127,32,22,23,24,
    21,22,30,125,126,127,125,145,146,127,32,21,22,30,125,125,126,125,126,125,126,127,147,125,126,127,32,1,2,3,
    21,22,30,143,144,127,129,130,126,127,32,21,22,30,125,126,127,125,129,125,125,125,125,125,125,126,127,143,31,126,
    21,22,30,145,146,147,148,143,144,127,32,21,22,30,146,145,146,125,126,125,126,125,126,127,127,127,127,31,126,143,
    21,22,30,125,143,144,125,143,144,127,32,21,21,30,125,126,127,125,126,127,125,126,127,125,126,127,32,86,56,56,
    21,22,30,125,126,127,125,129,130,127,32,23,21,30,125,126,145,146,147,148,125,146,129,130,126,127,32,22,23,24,
    21,21,86,87,88,88,88,88,87,88,89,23,21,30,125,125,125,146,147,125,125,126,127,125,126,127,32,22,23,24,
    21,21,22,21,22,23,24,23,21,22,21,22,21,86,87,88,87,87,87,87,87,87,87,87,87,88,89,21,22,23,
    21,21,22,21,22,23,24,24,24,21,21,22,23,21,22,21,22,23,24,22,23,21,22,21,22,23,24,21,22,23
};

unsigned int SECOND_LAYER_LVL4DATA[] =
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,149,0,0,149,0,0,0,0,0,0,0,0,0,0,0,26,27,27,27,27,27,27,27,27,27,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,50,0,150,0,0,0,0,0,0,50,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,50,0,0,0,0,0,0,0,0,50,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,149,50,0,0,0,
    0,0,0,0,0,0,26,27,27,27,27,81,27,27,27,27,27,28,0,149,27,27,27,108,27,27,53,0,0,0,
    0,0,0,0,0,0,50,0,0,0,0,0,0,0,0,0,0,50,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,50,0,0,0,0,0,0,0,0,0,150,50,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,50,0,0,0,0,0,0,0,0,0,0,50,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,50,0,0,0,150,0,0,0,0,0,0,50,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,51,52,52,52,52,52,52,52,52,52,52,53,0,0,0,0,0,0,0,0,150,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,149,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,133,133,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,149,0,0,0,0,0,0,150,0,0,133,133,153,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,153,133,153,0,0,149,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,133,133,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,153,133,153,0,0,0,0,0,0,0,0,0,
    0,0,0,225,226,227,0,0,0,0,0,0,0,0,150,0,0,0,0,133,133,0,0,0,0,0,0,0,0,0,
    0,0,0,241,242,243,230,134,135,0,0,0,0,0,0,0,0,0,0,133,134,133,133,133,133,133,133,0,0,0,
    0,0,0,257,258,259,153,154,155,0,0,0,0,0,0,0,0,0,0,133,133,133,133,133,133,134,100,0,0,0,
    0,0,0,273,274,275,76,133,75,0,0,0,0,0,149,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,149,289,290,291,0,0,0,231,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,149,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,149,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
    
LevelD::~LevelD()
{
    delete [] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    delete[] m_game_state.items;
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

void LevelD::initialise()
{
    m_number_of_enemies = 8;
    m_game_state.next_scene_id = -1;
    
    GLuint map_texture_id = Utility::load_texture("assets/farm_tileset.png");
    m_game_state.map = new Map(
        LEVEL_WIDTH,      // Width of the map in tiles
        LEVEL_HEIGHT,     // Height of the map in tiles
        LEVEL4_DATA,      // First layer tile data
        map_texture_id,   // Texture ID of the tileset
        1.0f,             // Tile size in game units
        16,               // Tile count (columns) in the tileset
        19,               // Tile count (rows) in the tileset
        SECOND_LAYER_LVL4DATA // Second layer tile data
    );
    
    GLuint* item_textures = new GLuint[ITEM_COUNT];
    // items!
    item_textures[0] = Utility::load_texture("assets/11.png");
    item_textures[1] = Utility::load_texture("assets/3.png");
    item_textures[2] = Utility::load_texture("assets/10.png");
    item_textures[3] = Utility::load_texture("assets/5.png");
    item_textures[4] = Utility::load_texture("assets/6.png");
    item_textures[5] = Utility::load_texture("assets/8.png");
    item_textures[6] = Utility::load_texture("assets/1.png");
    item_textures[7] = Utility::load_texture("assets/9.png");
    item_textures[8] = Utility::load_texture("assets/2.png");
    item_textures[8] = Utility::load_texture("assets/4.png");
    
    glm::vec3* item_positions = new glm::vec3[ITEM_COUNT] {
        glm::vec3(3.16f, -2.8f, 0.0f),
        glm::vec3(7.11f, -23.9f, 0.0f),
        glm::vec3(9.25f, -16.84f, 0.0f),
        glm::vec3(7.1f, -10.48f, 0.0f),
        glm::vec3(15.91f, -10.83f, 0.0f),
        glm::vec3(21.95f, -5.4f, 0.0f),
        glm::vec3(24.2f, -9.9f, 0.0f),
        glm::vec3(24.2f, -26.92f, 0.0f),
        glm::vec3(20.2f, -9.9f, 0.0f),
        glm::vec3(20.0f, -11.23f, 0.0f)
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
    
    player_initial_position = glm::vec3(3.5f, -9.5, 0.0f);
    //player_initial_position = glm::vec3(10.5f, -10.0f, 0.0f);
    m_game_state.player->set_position(player_initial_position);
    std::cout << "LevelD Initial Position: "
              << player_initial_position.x << ", "
              << player_initial_position.y << ", "
              << player_initial_position.z << std::endl;
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
    m_game_state.enemies[0].set_position(glm::vec3(15.875f, -8.5365f, 0.0f));
    m_game_state.enemies[0].set_ai_type(GUARD);
    m_game_state.enemies[0].set_ai_state(IDLE);
    
    m_game_state.enemies[1].set_position(glm::vec3(4.0f, -21.01f, 0.0f));
    m_game_state.enemies[1].set_ai_type(PATROL);
    m_game_state.enemies[1].set_ai_state(PATROLLING);
    m_game_state.enemies[1].set_movement(glm::vec3(-1.0f, 0.0f, 0.0f));
    m_game_state.enemies[1].set_speed(1.5f);

    
    m_game_state.enemies[2].set_position(glm::vec3(18.88f, -14.3f, 0.0f));
    m_game_state.enemies[2].set_walking(enemy_walking_animation);
    m_game_state.enemies[2].set_ai_type(SHOOTER);
    m_game_state.enemies[2].set_ai_state(SHOOTING);
    GLuint projectile_texture2 = Utility::load_texture("assets/bullet2.png");
    m_game_state.enemies[2].set_projectile_texture(projectile_texture2);
    
    m_game_state.enemies[3].set_position(glm::vec3(18.88f, -15.3f, 0.0f));
    m_game_state.enemies[3].set_walking(enemy_walking_animation);
    m_game_state.enemies[3].set_ai_type(SHOOTER);
    m_game_state.enemies[3].set_ai_state(SHOOTING);
    m_game_state.enemies[3].set_projectile_texture(projectile_texture2);
    
    m_game_state.enemies[4].set_position(glm::vec3(23.47f, -20.1f, 0.0f));
    m_game_state.enemies[4].set_ai_type(GUARD);
    m_game_state.enemies[4].set_ai_state(IDLE);
    
    m_game_state.enemies[5].set_position(glm::vec3(25.0f, -3.89f, 0.0f));
    m_game_state.enemies[5].set_ai_type(PATROL);
    m_game_state.enemies[5].set_ai_state(PATROLLING);
    m_game_state.enemies[5].set_movement(glm::vec3(-1.0f, 0.0f, 0.0f));
    m_game_state.enemies[5].set_speed(1.5f);
    
    m_game_state.enemies[6].set_position(glm::vec3(15.9f, -22.83f, 0.0f));
    m_game_state.enemies[6].set_walking(enemy_walking_animation);
    m_game_state.enemies[6].set_ai_type(SHOOTER);
    m_game_state.enemies[6].set_ai_state(SHOOTING);
    GLuint projectile_texture1 = Utility::load_texture("assets/bullet.png");
    m_game_state.enemies[6].set_projectile_texture(projectile_texture1);
    
    m_game_state.enemies[7].set_position(glm::vec3(22.01f, -12.1f, 0.0f));
    m_game_state.enemies[7].set_ai_type(PATROL);
    m_game_state.enemies[7].set_ai_state(PATROLLING);
    m_game_state.enemies[7].set_movement(glm::vec3(-1.0f, 0.0f, 0.0f));
    m_game_state.enemies[7].set_speed(1.5f);
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

void LevelD::update(float delta_time)
{
    m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, ENEMY_COUNT, m_game_state.map);
    
    for (int i = 0; i < m_number_of_enemies; i++)
    {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, NULL, NULL, m_game_state.map);
    }

    float transition_min_x = 29.0f;
    float transition_max_x = 29.5f;
    float transition_min_y = -24.3f;
    float transition_max_y = -23.1f;

    // Get the player's current position
    glm::vec3 player_position = m_game_state.player->get_position();
    
    //debugging command
    std::cout << "Player Position: (" << player_position.x << ", " << player_position.y << ")" << std::endl;

    // Add a small epsilon for floating-point comparison
    float epsilon = 0.01f;
    
    if (player_position.x >= transition_min_x - epsilon && player_position.x <= transition_max_x + epsilon &&
        player_position.y >= transition_min_y - epsilon && player_position.y <= transition_max_y + epsilon)
    {
        m_game_state.next_scene_id = 4;
    }

}

void LevelD::render(ShaderProgram *program)
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

glm::vec3 LevelD::get_player_initial_position() const {
    return player_initial_position;
}

