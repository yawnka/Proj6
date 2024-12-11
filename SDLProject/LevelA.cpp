#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH 30
#define LEVEL_HEIGHT 30

#include <cstdlib>
#include <ctime>

constexpr int NUM_ITEMS = 4;

GLuint item_textures[NUM_ITEMS];

extern glm::vec3 player_initial_position;



constexpr char SPRITESHEET_FILEPATH[] = "assets/player0.png",
           ENEMY_FILEPATH[]       = "assets/enemy.png";


unsigned int LEVELA_DATA[] =
{
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 4, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    2, 2, 2, 2, 2, 0, 1, 1, 1, 0, 4, 4, 4, 3, 4, 4, 3, 3, 4, 4, 4, 4
};


unsigned int LEVEL1_DATA[] =
{
    21,21,21,21,22,23,24,24,21,21,21,22,23,24,24,24,24,21,22,23,24,21,21,21,22,23,24,24,24,21,
    21,22,23,21,22,23,24,21,22,21,21,22,23,24,21,21,21,22,21,22,23,24,21,21,22,23,24,24,24,21,
    21,22,23,21,22,23,24,23,21,22,21,22,23,24,21,21,21,22,21,22,23,24,24,21,21,22,23,24,21,22,
    21,22,23,21,21,22,23,24,21,21,22,23,24,24,24,24,21,22,23,21,22,23,24,22,21,22,23,24,21,22,
    21,22,23,21,21,22,23,24,21,21,22,23,24,24,21,21,22,23,24,23,21,22,23,24,23,21,22,23,24,23,
    21,22,21,22,21,21,22,23,24,21,22,23,24,24,23,21,22,23,24,23,21,22,23,24,23,21,22,23,24,23,
    21,22,21,22,21,21,22,23,24,21,22,23,24,24,21,21,22,23,24,23,24,21,22,23,24,21,22,23,24,24,
    21,22,21,22,21,22,21,22,23,24,22,23,24,24,23,21,22,23,21,22,23,21,22,23,24,24,21,22,23,24,
    21,22,21,22,21,22,21,1,2,2,133,155,2,2,2,2,2,2,2,2,2,2,2,3,23,24,21,22,23,24,
    21,22,21,22,21,22,21,30,145,115,133,133,115,115,115,115,115,115,115,115,115,115,144,32,22,23,24,22,23,24,
    21,21,22,23,21,22,23,30,115,130,155,133,115,144,143,115,115,115,115,143,145,115,115,32,22,23,24,22,23,24,
    21,21,22,23,21,22,23,30,146,115,133,133,128,115,115,115,115,143,115,115,143,115,115,32,21,22,23,24,23,24,
    21,21,22,23,21,22,23,30,144,115,133,133,115,115,115,115,115,115,115,130,115,115,143,32,23,21,22,23,24,23,
    21,21,22,23,21,22,23,30,115,115,133,133,115,115,115,115,130,115,115,115,115,115,115,32,23,21,22,23,24,23,
    21,22,23,24,21,22,23,30,144,115,131,132,115,115,146,115,145,115,143,128,115,115,143,32,23,24,21,22,23,24,
    21,22,23,24,23,21,22,30,115,115,151,152,115,115,143,115,115,115,115,115,115,115,115,32,23,24,21,22,23,24,
    21,22,23,24,23,21,22,30,115,115,135,134,115,115,144,115,145,115,143,133,115,130,115,32,22,23,21,22,23,24,
    21,22,23,24,23,21,22,30,115,115,133,153,133,115,128,115,115,115,133,133,115,115,115,32,22,23,21,22,23,24,
    21,22,23,24,23,21,22,30,115,128,115,133,153,133,133,133,133,133,133,154,133,133,133,154,22,23,21,22,23,24,
    21,22,23,24,23,21,22,30,130,145,115,115,115,133,133,154,133,133,154,133,133,133,133,153,22,23,21,22,23,24,
    21,22,23,24,24,21,22,30,130,130,115,146,144,115,115,115,115,115,115,115,115,144,145,155,22,21,22,23,24,24,
    21,22,23,24,24,23,21,55,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,57,22,21,22,23,24,23,
    22,23,24,24,24,23,21,22,23,24,23,24,21,22,23,24,21,22,23,24,22,21,21,22,21,21,22,23,24,23,
    22,23,24,24,24,23,21,22,23,24,23,24,21,22,23,24,21,22,23,24,22,21,21,22,21,22,23,24,24,23,
    22,23,24,24,24,22,21,22,23,24,23,24,22,21,22,23,21,22,23,24,23,21,21,22,21,22,23,24,24,23,
    22,23,24,24,24,22,23,21,22,23,24,24,21,21,22,23,21,22,23,24,23,21,21,22,21,22,23,24,24,23,
    22,23,24,23,24,22,23,21,22,23,24,24,21,22,21,22,21,22,23,24,23,21,21,22,21,22,23,24,24,24,
    22,23,24,23,24,22,23,21,22,23,24,24,21,22,23,21,21,22,23,21,22,23,24,21,22,23,24,22,23,24,
    22,23,24,23,24,22,23,21,22,23,24,24,21,22,23,24,21,22,23,21,22,23,24,21,22,23,24,22,23,24,
    22,23,24,23,24,22,23,24,21,22,23,24,21,22,23,24,21,22,23,21,22,23,24,24,24,24,24,22,23,24

};

unsigned int SECOND_LAYER_LVL1DATA[] =
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,26,106,106,106,106,106,106,106,106,28,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,50,0,202,0,0,0,0,0,0,50,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,50,0,202,0,0,0,0,0,0,50,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,50,0,202,0,0,0,0,0,0,50,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,50,0,202,0,0,0,0,0,0,50,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,78,106,106,79,79,79,81,79,79,80,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,150,0,150,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,149,149,149,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
    
LevelA::~LevelA()
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

void LevelA::initialise()
{
    m_number_of_enemies = 2;
    m_game_state.next_scene_id = -1;
    
    GLuint map_texture_id = Utility::load_texture("assets/farm_tileset.png");
    m_game_state.map = new Map(
        LEVEL_WIDTH,      // Width of the map in tiles
        LEVEL_HEIGHT,     // Height of the map in tiles
        LEVEL1_DATA,      // First layer tile data
        map_texture_id,   // Texture ID of the tileset
        1.0f,             // Tile size in game units
        16,               // Tile count (columns) in the tileset
        19,               // Tile count (rows) in the tileset
        SECOND_LAYER_LVL1DATA // Second layer tile data
    );
    
    // items!
    item_textures[0] = Utility::load_texture("assets/1.png");
    item_textures[1] = Utility::load_texture("assets/6.png");
    item_textures[2] = Utility::load_texture("assets/8.png");
    item_textures[3] = Utility::load_texture("assets/9.png");
    
    constexpr int NUM_ITEMS = 4;
    glm::vec3 item_positions[NUM_ITEMS] = {
        glm::vec3(7.8f, -19.5f, 0.0f), // Item 1 position
        glm::vec3(22.0f, -8.8f, 0.0f), // Item 6 position
        glm::vec3(15.0f, -11.0f, 0.0f), // Item 8 position
        glm::vec3(12.8f, -9.0f, 0.0f)  // Item 9 position
    };
    
    m_game_state.items = new Entity[NUM_ITEMS];

    for (int i = 0; i < NUM_ITEMS; i++) {
        // Assign textures and properties
        m_game_state.items[i] = Entity(
            item_textures[i % NUM_ITEMS], // Cycle through item textures
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
    
    player_initial_position = glm::vec3(10.5f, -10.0f, 0.0f);
    m_game_state.player->set_position(player_initial_position);

    // Jumping
    m_game_state.player->set_jumping_power(5.0f);
    
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
    m_game_state.enemies[0].set_position(glm::vec3(8.0f, -14.0f, 0.0f));
    m_game_state.enemies[0].set_ai_type(GUARD);
    m_game_state.enemies[0].set_ai_state(IDLE);
    
    m_game_state.enemies[1].set_position(glm::vec3(16.0f, -16.125f, 0.0f));
    m_game_state.enemies[1].set_ai_type(PATROL);
    m_game_state.enemies[1].set_ai_state(PATROLLING);
    m_game_state.enemies[1].set_movement(glm::vec3(-1.0f, 0.0f, 0.0f));
    m_game_state.enemies[1].set_speed(1.5f);
    
    /**
     BGM and SFX
     */
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        std::cout << "Error initializing SDL_mixer: " << Mix_GetError() << std::endl;
    }

    // Load and play background music
    m_game_state.bgm = Mix_LoadMUS("assets/Cloud_Dancer.mp3");
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

void LevelA::update(float delta_time)
{
    m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, ENEMY_COUNT, m_game_state.map);
    
    for (int i = 0; i < m_number_of_enemies; i++)
    {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, NULL, NULL, m_game_state.map);
    }

    // Define the region for transitioning to the next scene
    float transition_min_x = 23.0f;   // Minimum x coordinate
    float transition_max_x = 25.0f;   // Maximum x coordinate
    float transition_min_y = -19.5f;  // Minimum y coordinate
    float transition_max_y = -17.0f;  // Maximum y coordinate

    for (int i = 0; i < NUM_ITEMS; i++) {
        if (m_game_state.items[i].is_active() && m_game_state.player->check_collision(&m_game_state.items[i])) {
            m_game_state.items[i].deactivate(); // Deactivate the item
            m_game_state.num_items_collected++; // Increment collected items
        }
    }
    // Get the player's current position
    glm::vec3 player_position = m_game_state.player->get_position();

    // Debugging: Log the player's position
    std::cout << "Player Position: (" << player_position.x << ", " << player_position.y << ")" << std::endl;

    // Add a small epsilon for floating-point comparison
    float epsilon = 0.01f;
    
    // Check if the player is within the transition region
    if (player_position.x >= transition_min_x - epsilon && player_position.x <= transition_max_x + epsilon &&
        player_position.y >= transition_min_y - epsilon && player_position.y <= transition_max_y + epsilon)
    {
        std::cout << "Transitioning to the next scene!" << std::endl; // Debugging message
        m_game_state.next_scene_id = 1; // Set the next scene ID
    }
}

void LevelA::render(ShaderProgram *program)
{
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    m_game_state.map->render(program);
    m_game_state.player->render(program);
    for (int i = 0; i < m_number_of_enemies; i++)
            m_game_state.enemies[i].render(program);
    for (int i = 0; i < NUM_ITEMS; i++) {
        if (m_game_state.items[i].is_active()) {
            m_game_state.items[i].render(program);
        }
    }

}

glm::vec3 LevelA::get_player_initial_position() const {
    return player_initial_position; // Return the stored initial position
}
