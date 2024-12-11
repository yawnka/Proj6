#include "LevelC.h"
#include "Utility.h"

#define LEVEL_WIDTH 30
#define LEVEL_HEIGHT 30

#include <cstdlib>
#include <ctime>


constexpr char SPRITESHEET_FILEPATH[] = "assets/player0.png",
           ENEMY_FILEPATH[]       = "assets/enemy.png";


unsigned int LEVEL3_DATA[] =
{
    818,857,857,857,857,857,857,857,857,857,857,857,857,857,857,857,857,857,857,857,857,857,857,857,857,857,857,857,857,935,
    970,980,980,980,980,980,980,964,963,964,980,980,980,980,980,980,980,980,980,980,980,980,980,980,999,937,940,1001,980,826,
    970,980,980,980,980,980,980,980,980,980,980,980,980,980,961,961,961,964,964,961,964,964,964,964,826,409,536,537,538,538,
    970,980,964,964,964,964,961,961,964,963,964,980,980,980,980,980,980,980,980,980,980,980,980,980,826,409,536,537,538,538,
    970,980,980,980,980,980,980,980,980,980,980,980,980,980,980,980,980,961,980,980,980,980,980,980,826,533,533,973,980,826,
    970,980,980,980,980,980,980,980,980,980,980,980,961,980,980,999,937,937,938,937,940,938,940,938,937,571,571,1039,980,826,
    970,980,980,980,980,964,964,980,980,980,980,980,980,980,980,825,409,409,409,402,402,409,409,409,409,327,553,973,980,826,
    970,980,980,980,980,980,980,980,980,980,980,980,980,964,980,825,365,409,405,308,409,401,401,401,409,327,409,973,980,826,
    970,980,980,980,980,980,980,980,980,964,964,964,980,980,980,825,409,422,405,327,409,409,409,409,401,327,402,973,980,826,
    970,980,904,999,937,937,937,937,937,937,937,937,937,1001,980,825,409,441,405,328,363,363,363,363,363,370,364,973,980,826,
    970,980,923,826,409,409,409,409,409,409,409,409,409,970,980,825,409,460,402,327,401,401,409,405,401,409,409,973,980,826,
    970,964,923,826,409,423,424,425,426,409,409,404,409,970,980,825,422,479,402,327,401,419,420,420,420,421,409,973,980,826,
    970,980,923,826,409,442,443,444,439,421,404,404,409,970,980,825,441,409,409,327,409,438,439,439,439,440,409,973,980,826,
    970,980,923,826,409,461,462,463,439,440,409,404,409,970,980,825,460,402,409,327,409,457,458,458,458,459,409,973,980,826,
    970,980,942,826,409,409,457,439,439,459,409,404,409,970,980,825,479,422,401,327,401,409,409,409,402,401,409,973,980,826,
    970,980,980,826,409,409,409,458,459,409,409,409,409,970,980,825,409,441,400,328,363,363,363,363,364,409,409,973,980,826,
    970,980,964,826,404,401,404,409,409,404,401,409,409,970,980,825,409,460,400,327,409,305,306,306,306,306,307,973,980,826,
    970,980,980,826,409,409,409,409,409,409,409,409,409,970,980,825,400,479,401,327,409,324,325,325,325,325,326,973,980,826,
    970,964,980,1018,857,857,857,552,552,858,858,858,858,1020,980,825,409,405,402,327,401,343,344,344,344,344,345,973,980,826,
    970,980,980,999,938,938,938,534,534,938,938,938,938,1001,980,825,405,405,409,327,409,409,401,409,409,409,422,973,980,826,
    970,980,980,823,400,400,400,553,553,400,400,400,400,973,980,825,405,405,405,327,402,402,409,409,409,405,441,973,980,826,
    970,980,980,826,409,409,409,409,409,409,409,409,409,971,980,825,409,409,409,327,409,402,400,400,400,365,460,973,980,826,
    970,964,964,826,409,409,409,409,409,409,409,409,409,971,980,825,409,409,409,327,409,409,409,409,400,400,479,973,980,826,
    970,980,980,826,409,409,409,409,409,409,409,401,536,537,538,539,363,363,363,370,363,363,364,409,409,402,409,973,980,826,
    970,980,980,1016,401,409,409,409,401,401,401,401,536,537,538,539,363,363,363,363,363,363,363,363,363,363,364,973,980,826,
    537,538,539,401,409,409,409,409,409,409,409,409,409,971,980,825,409,409,400,400,400,400,402,402,402,402,409,973,980,826,
    537,538,539,409,409,401,409,409,409,409,409,409,409,971,980,825,401,365,400,401,402,402,400,400,400,409,409,973,980,826,
    970,980,962,935,409,409,409,409,409,409,409,409,409,971,980,825,409,400,476,477,478,409,409,409,365,478,409,973,980,826,
    970,980,962,1018,858,857,857,857,857,857,857,857,857,1020,980,1018,857,857,857,857,857,857,857,857,857,857,857,1020,964,826,
    899,962,980,980,962,980,980,980,962,980,962,980,962,980,980,980,980,980,980,980,980,980,980,980,980,980,980,980,980,1016
};

unsigned int SECOND_LAYER_LVL3DATA[] =
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
    
LevelC::~LevelC()
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

void LevelC::initialise()
{
    m_number_of_enemies = 5;
    m_game_state.next_scene_id = -1;
    
    GLuint map_texture_id = Utility::load_texture("assets/mapv2.png");
    m_game_state.map = new Map(
        LEVEL_WIDTH,      // Width of the map in tiles
        LEVEL_HEIGHT,     // Height of the map in tiles
        LEVEL3_DATA,      // First layer tile data
        map_texture_id,   // Texture ID of the tileset
        1.0f,             // Tile size in game units
        19,               // Tile count (columns) in the tileset
        52,               // Tile count (rows) in the tileset
        SECOND_LAYER_LVL3DATA // Second layer tile data
    );
    
    GLuint* item_textures = new GLuint[ITEM_COUNT];
    // items!
    item_textures[0] = Utility::load_texture("assets/2.png");
    item_textures[1] = Utility::load_texture("assets/3.png");
    item_textures[2] = Utility::load_texture("assets/4.png");
    item_textures[3] = Utility::load_texture("assets/5.png");
    item_textures[4] = Utility::load_texture("assets/6.png");
    item_textures[5] = Utility::load_texture("assets/8.png");
    
    glm::vec3* item_positions = new glm::vec3[ITEM_COUNT] {
        glm::vec3(5.5f, -11.2f, 0.0f),
        glm::vec3(24.9f, -26.9f, 0.0f),
        glm::vec3(22.8f, -9.0f, 0.0f),
        glm::vec3(16.8f, -6.0f, 0.0f),
        glm::vec3(7.9f, -19.65f, 0.0f),
        glm::vec3(25.0f, -17.2f, 0.0f)
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
    
    player_initial_position = glm::vec3(1.5f, -25.47, 0.0f);
    //player_initial_position = glm::vec3(10.5f, -10.0f, 0.0f);
    m_game_state.player->set_position(player_initial_position);
    std::cout << "LevelC Initial Position: "
              << player_initial_position.x << ", "
              << player_initial_position.y << ", "
              << player_initial_position.z << std::endl;

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
    m_game_state.enemies[0].set_position(glm::vec3(9.0f, -13.0f, 0.0f));
    m_game_state.enemies[0].set_ai_type(GUARD);
    m_game_state.enemies[0].set_ai_state(IDLE);
    
    m_game_state.enemies[1].set_position(glm::vec3(20.5f, -27.175f, 0.0f));
    m_game_state.enemies[1].set_ai_type(PATROL);
    m_game_state.enemies[1].set_ai_state(PATROLLING);
    m_game_state.enemies[1].set_movement(glm::vec3(-1.0f, 0.0f, 0.0f));
    m_game_state.enemies[1].set_speed(1.5f);

    m_game_state.enemies[2].set_position(glm::vec3(15.9f, -15.8f, 0.0f));
    m_game_state.enemies[2].set_walking(enemy_walking_animation);
    m_game_state.enemies[2].set_ai_type(SHOOTER);
    m_game_state.enemies[2].set_ai_state(SHOOTING);
    GLuint projectile_texture1 = Utility::load_texture("assets/bullet.png");
    m_game_state.enemies[2].set_projectile_texture(projectile_texture1);
    
    m_game_state.enemies[3].set_position(glm::vec3(15.9f, -17.83f, 0.0f));
    m_game_state.enemies[3].set_walking(enemy_walking_animation);
    m_game_state.enemies[3].set_ai_type(SHOOTER);
    m_game_state.enemies[3].set_ai_state(SHOOTING);
    m_game_state.enemies[3].set_projectile_texture(projectile_texture1);
    
    m_game_state.enemies[4].set_position(glm::vec3(22.0f, -7.2f, 0.0f));
    m_game_state.enemies[4].set_ai_type(GUARD);
    m_game_state.enemies[4].set_ai_state(IDLE);
    
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

void LevelC::update(float delta_time)
{
    m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, ENEMY_COUNT, m_game_state.map);
    
    for (int i = 0; i < m_number_of_enemies; i++)
    {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, NULL, NULL, m_game_state.map);
    }

    float transition_min_x = 29.0f;
    float transition_max_x = 29.5f;
    float transition_min_y = -3.3f;
    float transition_max_y = -1.5f;

    // Get the player's current position
    glm::vec3 player_position = m_game_state.player->get_position();
    
    //debugging commands
    std::cout << "Transition Region: X(" << transition_min_x << ", " << transition_max_x
              << "), Y(" << transition_min_y << ", " << transition_max_y << ")" << std::endl;
    std::cout << "Player Position: (" << player_position.x << ", " << player_position.y << ")" << std::endl;

    // Add a small epsilon for floating-point comparison
    float epsilon = 0.01f;
    
    if (player_position.x >= transition_min_x - epsilon && player_position.x <= transition_max_x + epsilon &&
        player_position.y >= transition_min_y - epsilon && player_position.y <= transition_max_y + epsilon)
    {
        m_game_state.next_scene_id = 3;
    }

}

void LevelC::render(ShaderProgram *program)
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

glm::vec3 LevelC::get_player_initial_position() const {
    return player_initial_position;
}

