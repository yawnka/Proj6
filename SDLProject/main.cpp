#define GL_SILENCE_DEPRECATION
#define GL_GLEXT_PROTOTYPES 1
#define FIXED_TIMESTEP 0.0166666f
#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8
#define LEVEL1_LEFT_EDGE 5.0f

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "cmath"
#include <ctime>
#include <vector>
#include "Entity.h"
#include "Map.h"
#include "Utility.h"
#include "Scene.h"
#include "LevelA.h"
#include "LevelB.h"
#include "LevelC.h"
#include "Effects.h"

// ––––– CONSTANTS ––––– //
constexpr int WINDOW_WIDTH  = 640,
          WINDOW_HEIGHT = 480;

constexpr float BG_RED     = 0.1922f,
            BG_BLUE    = 0.549f,
            BG_GREEN   = 0.9059f,
            BG_OPACITY = 1.0f;

constexpr int VIEWPORT_X = 0,
          VIEWPORT_Y = 0,
          VIEWPORT_WIDTH  = WINDOW_WIDTH,
          VIEWPORT_HEIGHT = WINDOW_HEIGHT;

constexpr char V_SHADER_PATH[] = "shaders/vertex_lit.glsl",
           F_SHADER_PATH[] = "shaders/fragment_lit.glsl";

constexpr float MILLISECONDS_IN_SECOND = 1000.0;

enum AppStatus { RUNNING, PAUSED, TERMINATED };
// ––––– GLOBAL VARIABLES ––––– //

Scene  *g_current_scene;
LevelA *g_levelA;
LevelB *g_levelB;
LevelC *g_levelC;

Effects *g_effects;
Scene   *g_levels[3];

SDL_Window* g_display_window;

AppStatus g_app_status = RUNNING;

ShaderProgram g_shader_program;
glm::mat4 g_view_matrix, g_projection_matrix;

float g_previous_ticks = 0.0f;
float g_accumulator = 0.0f;

bool g_is_colliding_bottom = false;

int total_enemies_defeated = 0;
int total_enemies_count = 3;

int curr_lives = 3;

// ––––– GENERAL FUNCTIONS ––––– //
void switch_to_scene(Scene *scene)
{
    g_current_scene = scene;
    g_current_scene->initialise(); // DON'T FORGET THIS STEP!
}

void initialise()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    g_display_window = SDL_CreateWindow("Hello, Shaders!",
                                      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      WINDOW_WIDTH, WINDOW_HEIGHT,
                                      SDL_WINDOW_OPENGL);
    
    SDL_GLContext context = SDL_GL_CreateContext(g_display_window);
    SDL_GL_MakeCurrent(g_display_window, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(VIEWPORT_X, VIEWPORT_Y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    
    g_shader_program.load(V_SHADER_PATH, F_SHADER_PATH);
    
    g_view_matrix = glm::mat4(1.0f);
    g_projection_matrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    g_shader_program.set_projection_matrix(g_projection_matrix);
    g_shader_program.set_view_matrix(g_view_matrix);
    
    glUseProgram(g_shader_program.get_program_id());
    
    glClearColor(BG_RED, BG_BLUE, BG_GREEN, BG_OPACITY);
    
    // enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    g_levelA = new LevelA();
    g_levelB = new LevelB();
    g_levelC = new LevelC();
    
    g_levels[0] = g_levelA;
    g_levels[1] = g_levelB;
    g_levels[2] = g_levelC;
    
    // Start at level A
    switch_to_scene(g_levels[0]);
    
    g_effects = new Effects(g_projection_matrix, g_view_matrix);
    //g_effects->start(SHRINK, 2.0f);
}

void process_input()
{
    // VERY IMPORTANT: If nothing is pressed, we don't want to go anywhere
    g_current_scene->get_state().player->set_movement(glm::vec3(0.0f));
    g_current_scene->get_state().enemies->set_movement(glm::vec3(0.0f));
    
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type) {
            // End game
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                g_app_status = TERMINATED;
                break;
                
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_q:
                        // Quit the game with a keystroke
                        g_app_status = TERMINATED;
                        break;
                        
                    case SDLK_SPACE:
                        // Jump
                        if (g_current_scene->get_state().player->get_collided_bottom())
                        {
                            g_current_scene->get_state().player->jump();
                            Mix_PlayChannel(-1, g_current_scene->get_state().jump_sfx, 0);
                        }
                        break;
                        
                    default:
                        break;
                }
                
            default:
                break;
        }
    }
    
    const Uint8 *key_state = SDL_GetKeyboardState(NULL);

        if (key_state[SDL_SCANCODE_LEFT])        g_current_scene->get_state().player->move_left();
            else if (key_state[SDL_SCANCODE_RIGHT])  g_current_scene->get_state().player->move_right();
             
        if (glm::length( g_current_scene->get_state().player->get_movement()) > 1.0f)
            g_current_scene->get_state().player->normalise_movement();
}

void update()
{
    if (g_app_status != RUNNING) return;
    float ticks = (float)SDL_GetTicks() / MILLISECONDS_IN_SECOND;
    float delta_time = ticks - g_previous_ticks;
    g_previous_ticks = ticks;
    
    delta_time += g_accumulator;
    
    if (delta_time < FIXED_TIMESTEP)
    {
        g_accumulator = delta_time;
        return;
    }
    
    glm::vec3 player_pos = g_current_scene->get_state().player->get_position();
    //int enemy_count = g_current_scene->get_number_of_enemies();
    
    while (delta_time >= FIXED_TIMESTEP) {
        g_current_scene->update(FIXED_TIMESTEP);
        g_effects->update(FIXED_TIMESTEP);
        // adding everything from previous main project
        g_current_scene->get_state().player->update(FIXED_TIMESTEP, g_current_scene->get_state().player, NULL, NULL, g_current_scene->get_state().map);
        for (int i = 0; i < g_current_scene->get_number_of_enemies(); i++) {
            if (!g_current_scene->get_state().enemies[i].is_active()) continue;

            g_current_scene->get_state().enemies[i].ai_activate(g_current_scene->get_state().player);
            g_current_scene->get_state().enemies[i].update(FIXED_TIMESTEP, g_current_scene->get_state().player, NULL, NULL, g_current_scene->get_state().map);

                // Check if player lands on top of the enemy to defeat it
                if (g_current_scene->get_state().player->check_collision(&g_current_scene->get_state().enemies[i])) {
                    if (g_current_scene->get_state().player->get_position().y > g_current_scene->get_state().enemies[i].get_position().y + g_current_scene->get_state().enemies[i].get_height() / 2.0f) {
                        g_current_scene->get_state().enemies[i].deactivate();
                        g_current_scene->get_state().enemies_defeated += 1;
                        total_enemies_defeated++;
                        // Ensure the projectile is deactivated if the enemy is a shooter
                        if (g_current_scene->get_state().enemies[i].get_ai_type() == SHOOTER) {
                            g_current_scene->get_state().enemies[i].set_projectile_active(false);
                        }

                        std::cout << "total enemies: " << total_enemies_count << std::endl;
                        std::cout << "enemies defeated: " << total_enemies_defeated << std::endl;
                        if (total_enemies_defeated == total_enemies_count) {
                            g_app_status = PAUSED;
                            return;
                        }
                    } else {
                        std::cout << "curr lives: " << curr_lives << std::endl;
                        if ( curr_lives > 0) {
                            curr_lives -= 1;
                        }
                        else {
                            g_app_status = PAUSED;
                            return;
                        }
                    }
                }

                // Check for collisions manually with the projectile since I couldnt get it to work correctly in Entity
                if (g_current_scene->get_state().enemies[i].is_projectile_active()) {
                    // Projectile boundaries
                    float proj_left = g_current_scene->get_state().enemies[i].get_projectile_position().x - 0.1f;
                    float proj_right = g_current_scene->get_state().enemies[i].get_projectile_position().x + 0.1f;
                    float proj_top = g_current_scene->get_state().enemies[i].get_projectile_position().y + 0.1f;
                    float proj_bottom = g_current_scene->get_state().enemies[i].get_projectile_position().y - 0.1f;

                    // Player boundaries
                    float player_left = player_pos.x - g_current_scene->get_state().player->get_width() / 2.0f;
                    float player_right = player_pos.x + g_current_scene->get_state().player->get_width() / 2.0f;
                    float player_top = player_pos.y + g_current_scene->get_state().player->get_height() / 2.0f;
                    float player_bottom = player_pos.y - g_current_scene->get_state().player->get_height() / 2.0f;

                    // Check collision between projectile and player
                    if (proj_right > player_left && proj_left < player_right &&
                        proj_top > player_bottom && proj_bottom < player_top) {
                        std::cout << "curr lives: " << curr_lives << std::endl;
                        if ( curr_lives > 0) {
                            curr_lives -= 1;
                        }
                        else {
                            g_app_status = PAUSED;
                            return;
                        }
                    }
                }
            }
        
//        if (g_is_colliding_bottom == false && g_current_scene->get_state().player->get_collided_bottom()) g_effects->start(SHAKE, 1.0f);
        
        g_is_colliding_bottom = g_current_scene->get_state().player->get_collided_bottom();
        
        // END
        delta_time -= FIXED_TIMESTEP;
    }
    
    g_accumulator = delta_time;
    
    // Prevent the camera from showing anything outside of the "edge" of the level
    g_view_matrix = glm::mat4(1.0f);
    
    if (g_current_scene->get_state().player->get_position().x > LEVEL1_LEFT_EDGE) {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(-g_current_scene->get_state().player->get_position().x, 3.75, 0));
    } else {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(-5, 3.75, 0));
    }
    
    if (g_current_scene == g_levelA && g_current_scene->get_state().player->get_position().y < -10.0f) switch_to_scene(g_levelB);
    if (g_current_scene == g_levelB && g_current_scene->get_state().player->get_position().y < -20.0f) switch_to_scene(g_levelC);
    
    g_view_matrix = glm::translate(g_view_matrix, g_effects->get_view_offset());
    g_shader_program.set_light_position_matrix(g_current_scene->get_state().player->get_position());
}

void render()
{
    g_shader_program.set_view_matrix(g_view_matrix);
    glClear(GL_COLOR_BUFFER_BIT);
 
    glUseProgram(g_shader_program.get_program_id());
    g_current_scene->render(&g_shader_program);
    
    int enemy_count = g_current_scene->get_number_of_enemies();
    
    if (g_app_status == PAUSED) {
        glm::vec3 player_position = g_current_scene->get_state().player->get_position();
        glm::vec3 message_position = player_position + glm::vec3(-1.5f, 0.5f, 0.0f);

        if (total_enemies_defeated== total_enemies_count) {
            // Display "You Win" text
            Utility::draw_text(
                &g_shader_program,
                Utility::load_texture("assets/font1.png"),
                "You Win!",
                0.8f,    // Font size
                0.05f,   // Spacing
                message_position
            );
        } else {
            // Display "You Lose" text
            Utility::draw_text(
                &g_shader_program,
                Utility::load_texture("assets/font1.png"),
                "You Lose!",
                0.8f,    // Font size
                0.05f,   // Spacing
                message_position
            );
        }
    }
    
    g_effects->render();
    
    SDL_GL_SwapWindow(g_display_window);
}

void shutdown()
{
    SDL_Quit();
    
    delete g_levelA;
    delete g_levelB;
    delete g_levelC;
    delete g_effects;
}

// ––––– DRIVER GAME LOOP ––––– //
int main(int argc, char* argv[])
{
    initialise();
    
    while (g_app_status != TERMINATED)
        {
            process_input();
            
            if (g_app_status == RUNNING) {
                update();
            }
            if (g_current_scene->get_state().next_scene_id >= 0) switch_to_scene(g_levels[g_current_scene->get_state().next_scene_id]);
            
            render();
        }
    
    shutdown();
    return 0;
}
