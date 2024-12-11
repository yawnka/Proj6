#define GL_SILENCE_DEPRECATION
#define GL_GLEXT_PROTOTYPES 1
#define FIXED_TIMESTEP 0.0166666f
#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8
#define LEVEL1_LEFT_EDGE 6.0f

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
#include "MainMenu.h"
#include "End.h"
#include "Effects.h"

// ––––– CONSTANTS ––––– //
constexpr int WINDOW_WIDTH  = 640*2,
          WINDOW_HEIGHT = 700;

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
MainMenu *g_main_menu;
End *g_end;


Effects *g_effects;
Scene   *g_levels[4];

SDL_Window* g_display_window;

AppStatus g_app_status = RUNNING;

ShaderProgram g_shader_program;
glm::mat4 g_view_matrix, g_projection_matrix;

float g_previous_ticks = 0.0f;
float g_accumulator = 0.0f;

bool g_is_colliding_bottom = false;

int curr_lives = 3;
glm::vec3 player_initial_position;

int NUM_ITEMS = 11;
int g_items_collected = 0;

// ––––– GENERAL FUNCTIONS ––––– //
void switch_to_scene(Scene *scene)
{
    // unfortunately the effects did not work as I wanted it to for extra credit, but I implemented
    // a baisc effect in the initialise function at the beginning for it!
//    g_effects = new Effects(g_projection_matrix, g_view_matrix);
//    g_effects->start(FADEOUT, 2.0f);
    g_current_scene = scene;
    g_current_scene->initialise(); // DON'T FORGET THIS STEP!
//    g_effects = new Effects(g_projection_matrix, g_view_matrix);
//    g_effects->start(FADEIN, 2.0f);
}


void initialise() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    g_display_window = SDL_CreateWindow("Adventurer Tale",
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    g_main_menu = new MainMenu();
    g_levelA = new LevelA();
    g_levelB = new LevelB();
    g_levelC = new LevelC();
    g_end = new End();

    g_levels[0] = g_levelA;
    g_levels[1] = g_levelB;
    g_levels[2] = g_levelC;
    g_levels[3] = g_end;

    //g_effects = new Effects(g_projection_matrix, g_view_matrix);
    // Start at MainMenu
    switch_to_scene(g_main_menu);
    g_effects = new Effects(g_projection_matrix, g_view_matrix);
    //g_effects->start(SHRINK, 1.5f);
    //g_effects->start(FADEIN, 4.0f);
    player_initial_position = glm::vec3(0.0f, 0.0f, 0.0f);
}


void process_input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            // End game
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                g_app_status = TERMINATED;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_q:
                        g_app_status = TERMINATED;
                        break;

                    case SDLK_p: // EXTRA CREDIT PSEUO MENU SCREEN FOR PAUSE WITH KEY PRESS P
                        if (g_app_status == RUNNING)
                        {
                            g_app_status = PAUSED;
                        }
                        break;

                    case SDLK_RETURN: // Enter key to handle on/off for pause screen
                        if (g_app_status == PAUSED)
                        {
                            g_app_status = RUNNING;
                        }
                        break;

                    default:
                        break;
                }

            default:
                break;
        }
    }

    if (g_app_status != RUNNING) return;

    // Handle player movement only if `player` exists
    if (g_current_scene->get_state().player)
    {
        g_current_scene->get_state().player->set_movement(glm::vec3(0.0f));

        const Uint8 *key_state = SDL_GetKeyboardState(NULL);
        if (key_state[SDL_SCANCODE_LEFT]) {
            g_current_scene->get_state().player->move_left();
        }
        if (key_state[SDL_SCANCODE_RIGHT]) {
            g_current_scene->get_state().player->move_right();
        }
        if (key_state[SDL_SCANCODE_UP]) {
            g_current_scene->get_state().player->move_up();
        }
        if (key_state[SDL_SCANCODE_DOWN]) {
            g_current_scene->get_state().player->move_down();
        }

        if (glm::length(g_current_scene->get_state().player->get_movement()) > 1.0f)
            g_current_scene->get_state().player->normalise_movement();
    }

    // Reset enemies' movement only if `enemies` exist
    if (g_current_scene->get_state().enemies)
    {
        g_current_scene->get_state().enemies->set_movement(glm::vec3(0.0f));
    }
}

void update()
{
    if (g_app_status != RUNNING) return;
    
    if (curr_lives == 0) {
        g_app_status = PAUSED;
    }

    float ticks = (float)SDL_GetTicks() / MILLISECONDS_IN_SECOND;
    float delta_time = ticks - g_previous_ticks;
    g_previous_ticks = ticks;

    delta_time += g_accumulator;

    if (delta_time < FIXED_TIMESTEP)
    {
        g_accumulator = delta_time;
        return;
    }

    glm::vec3 player_pos(0.0f);
    if (g_current_scene->get_state().player)
    {
        player_pos = g_current_scene->get_state().player->get_position();
        //std::cout << "Player position: " << player_pos.x << " , " << player_pos.y << std::endl;
    }

    while (delta_time >= FIXED_TIMESTEP)
    {
        g_current_scene->update(FIXED_TIMESTEP);
        g_effects->update(FIXED_TIMESTEP);

        // Update player if it exists
        if (g_current_scene->get_state().player)
        {
            g_current_scene->get_state().player->update(FIXED_TIMESTEP,
                                                        g_current_scene->get_state().player,
                                                        g_current_scene->get_state().enemies,
                                                        g_current_scene->get_number_of_enemies(),
                                                        g_current_scene->get_state().map);
        }
        
        // Handle item collection and deactivation
        if (g_current_scene->get_state().items)
        {
            for (int i = 0; i < NUM_ITEMS; ++i)
            {
                Entity& item = g_current_scene->get_state().items[i];
                if (item.is_active() &&
                    g_current_scene->get_state().player->check_collision(&item))
                {
                    g_items_collected++;
                    item.deactivate();
                    g_current_scene->get_state().num_items_collected++;
                }
            }
        }

        // Update enemies if they exist
        if (g_current_scene->get_state().enemies)
        {
            for (int i = 0; i < g_current_scene->get_number_of_enemies(); i++)
            {
                Entity &enemy = g_current_scene->get_state().enemies[i];

                if (!enemy.is_active()) continue;

                enemy.ai_activate(g_current_scene->get_state().player);
                enemy.update(FIXED_TIMESTEP,
                             g_current_scene->get_state().player,
                             NULL,
                             NULL,
                             g_current_scene->get_state().map);

                // Collision checks only if player exists
                if (g_current_scene->get_state().player &&
                    g_current_scene->get_state().player->check_collision(&enemy))
                {
                    if (curr_lives > 0)
                    {
                        curr_lives -= 1;

                        // Fetch the initial position dynamically from the current scene
                        if (dynamic_cast<LevelA*>(g_current_scene)) {
                            player_initial_position = static_cast<LevelA*>(g_current_scene)->get_player_initial_position();
                        } else if (dynamic_cast<LevelB*>(g_current_scene)) {
                            player_initial_position = static_cast<LevelB*>(g_current_scene)->get_player_initial_position();
                        } else if (dynamic_cast<LevelC*>(g_current_scene)) {
                            player_initial_position = static_cast<LevelC*>(g_current_scene)->get_player_initial_position();
                        } else {
                            std::cerr << "Error: Unknown scene type!" << std::endl;
                        }

                        // Reset the player's position to the initial position
                        if (g_current_scene->get_state().player) {
                            g_current_scene->get_state().player->set_position(player_initial_position);
                        }
                    }
                    else
                    {
                        g_app_status = PAUSED; // End the game when lives reach zero
                        return;
                    }
                }

                // Manual collision checks for projectiles
                if (enemy.is_projectile_active() && g_current_scene->get_state().player)
                {
                    // Projectile boundaries
                    float proj_left = enemy.get_projectile_position().x - 0.1f;
                    float proj_right = enemy.get_projectile_position().x + 0.1f;
                    float proj_top = enemy.get_projectile_position().y + 0.1f;
                    float proj_bottom = enemy.get_projectile_position().y - 0.1f;

                    // Player boundaries
                    float player_left = player_pos.x - g_current_scene->get_state().player->get_width() / 2.0f;
                    float player_right = player_pos.x + g_current_scene->get_state().player->get_width() / 2.0f;
                    float player_top = player_pos.y + g_current_scene->get_state().player->get_height() / 2.0f;
                    float player_bottom = player_pos.y - g_current_scene->get_state().player->get_height() / 2.0f;

                    // Check collision between projectile and player
                    if (proj_right > player_left && proj_left < player_right &&
                        proj_top > player_bottom && proj_bottom < player_top)
                    {

                        if (curr_lives > 0)
                        {
                            curr_lives -= 1;

                            // Fetch the initial position dynamically from the current scene
                            if (dynamic_cast<LevelA*>(g_current_scene)) {
                                player_initial_position = static_cast<LevelA*>(g_current_scene)->get_player_initial_position();
                            } else if (dynamic_cast<LevelB*>(g_current_scene)) {
                                player_initial_position = static_cast<LevelB*>(g_current_scene)->get_player_initial_position();
                            } else {
                                std::cerr << "Error: Unknown scene type!" << std::endl;
                            }

                            // Reset the player's position to the initial position
                            if (g_current_scene->get_state().player) {
                                g_current_scene->get_state().player->set_position(player_initial_position);
                            }
                        }
                        else
                        {
                            g_app_status = PAUSED; // End the game when lives reach zero
                            return;
                        }
                    }
                }
            }
        }

        g_is_colliding_bottom = g_current_scene->get_state().player &&
                                g_current_scene->get_state().player->get_collided_bottom();

        delta_time -= FIXED_TIMESTEP;
    }

    g_accumulator = delta_time;

    // Prevent the camera from showing anything outside of the "edge" of the level
    //g_view_matrix = glm::mat4(1.0f);

    // Center the camera on the player without clamping to boundaries
    if (g_current_scene->get_state().player)
    {
        glm::vec3 player_pos = g_current_scene->get_state().player->get_position();

        // Update the view matrix to center on the player
        float camera_x = -player_pos.x;
        float camera_y = -player_pos.y;
        g_view_matrix = glm::mat4(1.0f);
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(camera_x, camera_y, 0));

        // Set the spotlight to follow the player's position
        g_shader_program.set_light_position_matrix(player_pos); // Ensure this function sets the light position in the shader
    }
    else
    {
        // Default camera and light position if no player exists
        g_view_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, 3.75f, 0.0f));
        g_shader_program.set_light_position_matrix(glm::vec3(0.0f, 0.0f, 0.0f)); // Default light position
    }


    if (g_current_scene->get_state().next_scene_id >= 0)
    {
        switch (g_current_scene->get_state().next_scene_id)
        {
        case 0:
            switch_to_scene(g_levelA);
            break;
        case 1:
            switch_to_scene(g_levelB);
            break;
        case 2:
            switch_to_scene(g_levelC);
            break;
        default:
            break;
        }
    }
}


void render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    g_shader_program.set_view_matrix(g_view_matrix);
    glUseProgram(g_shader_program.get_program_id());

    // Render the current scene (map, player, enemies)
    g_current_scene->render(&g_shader_program);

    if (g_current_scene->get_state().player)
    {
        glm::mat4 ui_view_matrix = glm::mat4(1.0f); // Identity matrix for UI rendering
        g_shader_program.set_view_matrix(ui_view_matrix);

        std::string livesText = "LIVES: " + std::to_string(curr_lives);
        glm::vec3 message_position = glm::vec3(-4.5f, 3.1f, 0.0f);

        Utility::draw_text(&g_shader_program, Utility::load_texture("assets/font1.png"), livesText, 0.4f, 0.05f, message_position);
        
        std::string itemsText = "ITEMS: " + std::to_string(g_items_collected);
        glm::vec3 items_position = glm::vec3(-4.5f, 2.6f, 0.0f);
        Utility::draw_text(&g_shader_program, Utility::load_texture("assets/font1.png"), itemsText, 0.4f, 0.05f, items_position);

        g_shader_program.set_view_matrix(g_view_matrix);
    }

    // Handle pause rendering
    if (g_app_status == PAUSED)
    {
        glm::mat4 ui_view_matrix = glm::mat4(1.0f);
        g_shader_program.set_view_matrix(ui_view_matrix);

        glm::vec3 message_position = glm::vec3(-1.5f, 1.0f, 0.0f);

        if (curr_lives == 0) //if player is dead, you lose!
        {
            Utility::draw_text(
                &g_shader_program,
                Utility::load_texture("assets/font1.png"),
                "You Lose!",
                0.6f, // Font size
                0.0f, // Spacing
                message_position
            );
        }
        else // if P is pressed so paused state, then the player paused the game, enter to unpause.
        {
            Utility::draw_text(
                &g_shader_program,
                Utility::load_texture("assets/font1.png"),
                "Press Enter to Resume",
                0.6f, // Font size
                0.0f, // Spacing
                message_position
            );
        }

        // Restoring the original game view matrix to everything is rendered correctly
        g_shader_program.set_view_matrix(g_view_matrix);
    }

    g_effects->render();

    SDL_GL_SwapWindow(g_display_window);
}



void shutdown()
{
    SDL_Quit();
    delete g_main_menu;
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
