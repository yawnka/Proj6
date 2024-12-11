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
    590,552,552,552,552,552,552,552,552,552,552,552,552,552,552,552,552,552,552,552,552,552,552,552,552,552,552,552,552,612,
    666,676,676,676,676,658,676,676,676,676,676,658,676,676,676,676,676,676,676,676,676,676,676,676,676,676,659,676,676,522,
    666,676,676,676,676,676,676,676,676,676,676,676,658,676,676,676,676,676,676,658,676,676,676,676,676,659,676,676,676,522,
    666,659,695,634,636,636,634,634,636,634,634,634,634,634,634,634,634,634,634,636,636,636,636,636,636,636,697,676,658,522,
    666,676,520,105,105,105,105,105,105,105,105,4,105,105,105,105,105,105,105,105,105,105,105,105,105,105,666,676,676,522,
    666,676,520,105,97,98,99,100,101,102,103,23,102,1,2,2,2,2,2,3,119,120,121,61,105,105,666,658,676,522,
    666,658,520,105,105,61,105,105,105,105,105,23,105,20,21,21,21,21,21,22,138,139,140,141,105,105,666,676,676,522,
    666,676,520,105,105,105,97,98,99,101,102,23,104,39,40,40,40,40,40,41,157,158,159,160,105,105,666,676,676,522,
    232,233,234,115,116,117,105,105,105,105,105,23,97,98,99,100,101,102,103,105,176,177,178,179,105,105,666,676,676,522,
    232,233,234,58,59,59,59,7,59,59,59,59,59,59,59,59,59,59,59,59,7,59,59,59,60,61,666,676,676,522,
    666,676,522,153,154,155,23,23,105,105,105,105,105,105,105,105,105,105,105,105,23,105,105,105,105,105,666,676,659,522,
    666,676,522,97,98,99,42,23,102,138,139,140,141,98,99,100,101,102,97,98,23,100,101,102,103,163,666,676,676,522,
    666,676,522,105,105,105,105,23,105,157,158,159,160,105,101,102,103,104,105,105,23,105,105,105,105,182,666,658,676,522,
    666,658,522,105,97,98,99,23,101,102,103,105,105,105,105,105,105,105,105,101,23,103,104,105,163,105,666,676,676,522,
    666,676,522,105,101,102,103,23,105,105,61,105,105,105,101,102,1,2,2,3,23,101,102,103,182,105,666,676,676,522,
    666,676,522,105,105,105,229,42,105,101,102,103,104,105,99,100,39,40,40,41,42,229,105,105,105,105,666,658,676,522,
    666,676,714,554,554,554,230,230,554,554,554,554,554,554,554,554,554,554,554,554,248,248,554,554,554,554,716,676,676,522,
    666,676,676,676,676,676,230,230,676,676,676,676,676,658,676,676,676,676,676,676,230,230,676,676,676,676,658,676,659,522,
    666,658,659,658,676,676,230,230,676,676,676,658,659,676,676,676,676,676,676,658,230,230,676,676,659,676,676,676,676,522,
    666,676,658,676,676,676,230,230,676,676,676,676,676,658,676,676,695,634,634,634,249,249,634,634,634,634,634,697,676,522,
    666,676,695,633,633,633,249,249,636,636,636,636,636,697,676,676,522,105,105,105,4,105,105,105,105,105,105,666,676,522,
    666,676,521,105,105,105,105,105,105,105,1,2,3,668,676,676,522,105,105,97,23,99,100,101,102,103,105,666,658,522,
    666,676,521,97,98,99,100,101,102,103,20,21,22,668,676,676,522,97,98,99,23,101,102,103,105,105,105,666,676,522,
    666,676,521,105,105,124,97,101,102,103,39,40,41,668,676,676,522,101,102,103,23,105,100,101,102,103,105,666,676,522,
    666,676,521,123,124,143,105,105,105,105,105,123,124,668,676,676,522,101,102,103,23,105,105,105,105,105,232,233,234,235,
    666,658,521,142,143,162,105,105,105,105,105,142,143,668,676,676,522,97,98,99,81,59,59,59,59,60,232,233,234,235,
    666,658,521,161,162,105,105,105,105,105,161,162,105,668,658,676,522,105,105,105,105,101,102,103,104,105,105,666,676,522,
    666,676,521,180,97,101,102,103,104,105,103,181,105,668,676,659,522,105,97,98,99,100,101,102,103,105,105,666,676,522,
    666,676,714,555,555,555,555,555,555,555,555,555,555,716,676,676,714,555,555,555,555,555,555,555,555,555,555,716,658,522,
    595,633,633,633,633,633,633,633,633,633,633,633,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,712
};

unsigned int SECOND_LAYER_LVL4DATA[] =
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
    
LevelD::~LevelD()
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

void LevelD::initialise()
{
    m_number_of_enemies = 5;
    m_game_state.next_scene_id = -1;
    
    GLuint map_texture_id = Utility::load_texture("assets/mapv2.png");
    m_game_state.map = new Map(
        LEVEL_WIDTH,      // Width of the map in tiles
        LEVEL_HEIGHT,     // Height of the map in tiles
        LEVEL4_DATA,      // First layer tile data
        map_texture_id,   // Texture ID of the tileset
        1.0f,             // Tile size in game units
        19,               // Tile count (columns) in the tileset
        52,               // Tile count (rows) in the tileset
        SECOND_LAYER_LVL4DATA // Second layer tile data
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
    std::cout << "LevelD Initial Position: "
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

void LevelD::update(float delta_time)
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

