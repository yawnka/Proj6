#include "LevelA.h"
#include "Utility.h"
#include "tinyxml2.h"

#define LEVEL_WIDTH 32
#define LEVEL_HEIGHT 32

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


LevelA::~LevelA()
{
    delete [] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
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
    
    GLuint map_texture_id = Utility::load_texture("assets/mainlevbuild.png");
    m_game_state.map = new Map("assets/map1.tmx", map_texture_id, 16.0f, 64, 40);

    //GLuint map_texture_id = Utility::load_texture("assets/tileset_summer2.png");
    //m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELA_DATA, map_texture_id, 1.0f,6, 1);
    
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
    
    m_game_state.player->set_position(glm::vec3(2.5f, 0.0f, 0.0f));

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
    m_game_state.enemies[0].set_position(glm::vec3(8.0f, -3.0f, 0.0f));
    m_game_state.enemies[0].set_ai_type(PATROL);
    m_game_state.enemies[0].set_ai_state(PATROLLING);
    m_game_state.enemies[0].set_speed(1.5f);
    
    m_game_state.enemies[1].set_position(glm::vec3(16.0f, -5.125f, 0.0f));
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
    
    //if (m_game_state.player->get_position().y < -10.0f) m_game_state.next_scene_id = 1;
    float rightmost_edge = LEVEL_WIDTH * 1.0f;
    if (m_game_state.player->get_position().x > rightmost_edge)
    {
        //g_effects->start(FADEOUT, 2.0f); // Optional: Add a fade-out effect before switching scenes
        m_game_state.next_scene_id = 1;
    }
}

void LevelA::render(ShaderProgram *program)
{
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

    // Render all layers of the map
    for (int i = 0; i < m_game_state.map->get_layer_count(); ++i) {
        m_game_state.map->render_layer(program, i);
    }

    m_game_state.player->render(program);
    for (int i = 0; i < m_number_of_enemies; ++i) {
        m_game_state.enemies[i].render(program);
    }
}
