/**
* Author: Yanka Sikder
* Assignment: Final Proj 6 : Where's the Loot?
* Date due: 12/11/2024, 2:00pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Entity.h"

void Entity::ai_activate(Entity *player) {
    switch (m_ai_type) {
        case WALKER:
            ai_walk();
            break;
        case GUARD:
            ai_guard(player);
            break;
        case JUMPER:
            ai_jump();
            break;
        case PATROL:
            ai_patrol();
            break;
        case SHOOTER:
            ai_shoot(player);
        default:
            break;
    }
}

void Entity::ai_walk()
{
    m_movement = glm::vec3(-1.0f, 0.0f, 0.0f);
}

void Entity::ai_guard(Entity *player) {
    // Check if player is within a certain distance to activate the guard
    float activation_distance = 4.0f;
    float stop_distance = 1.0f; // Minimum distance to stop moving towards the player

    float distance_to_player = glm::distance(m_position, player->get_position());

    switch (m_ai_state) {
        case IDLE:
            if (distance_to_player < activation_distance) {
                m_ai_state = WALKING;
            }
            break;

        case WALKING:
            if (distance_to_player > activation_distance) {
                // If the player moves too far, return to IDLE state
                m_ai_state = IDLE;
                m_movement = glm::vec3(0.0f); // Stop movement
            } else if (distance_to_player > stop_distance) {
                // Move towards the player slowly
                glm::vec3 direction = player->get_position() - m_position;
                m_movement = glm::normalize(direction) * (m_speed * 0.2f); // Move at half speed
                // Update animations based on movement direction
                if (direction.x < 0) {
                    m_animation_indices = m_walking[LEFT];
                } else if (direction.x > 0) {
                    m_animation_indices = m_walking[RIGHT];
                }
                if (direction.y > 0) {
                    m_animation_indices = m_walking[UP];
                } else if (direction.y < 0) {
                    m_animation_indices = m_walking[DOWN];
                }
            } else {
                // Stop moving if close enough to the player
                m_movement = glm::vec3(0.0f);
            }
            break;
        default:
            break;
    }
}




void Entity::ai_jump() {
    if (m_ai_state == JUMPING && m_collided_bottom) {
        m_is_jumping = true;
    }
}

void Entity::ai_patrol() {
    if (m_ai_state != PATROLLING) return;

    //movement follows the one that i created in patrol to help with animation
    if (m_movement.x < 0) { // Moving left
        m_movement = glm::vec3(-1.0f, 0.0f, 0.0f);
        m_animation_indices = m_walking[0]; // left-facing animation frames
    } else { // Moving right
        m_movement = glm::vec3(1.0f, 0.0f, 0.0f);
        m_animation_indices = m_walking[1]; // right-facing animation frames
    }

    // Flip direction if a collision (into a wall) is detected
    if (m_collided_left) {
        m_movement.x = 1.0f;  // move right
        m_animation_indices = m_walking[1];
    } else if (m_collided_right) {
        m_movement.x = -1.0f; // move left
        m_animation_indices = m_walking[0];
    }
}


void Entity::ai_shoot(Entity* player) {
    if (!m_projectile_active) {
        m_projectile_position = m_position;
        m_projectile_active = true;
        m_projectile_speed = 5.0f;
    }
}


// Default constructor
Entity::Entity()
    : m_position(0.0f), m_movement(0.0f), m_scale(1.0f, 1.0f, 0.0f), m_model_matrix(1.0f),
    m_speed(0.0f), m_animation_cols(0), m_animation_frames(0), m_animation_index(0),
    m_animation_rows(0), m_animation_indices(nullptr), m_animation_time(0.0f),
    m_texture_id(0), m_velocity(0.0f), m_acceleration(0.0f), m_width(0.0f), m_height(0.0f)
{
    // Initialize m_walking with zeros or any default value
    for (int i = 0; i < SECONDS_PER_FRAME; ++i)
        for (int j = 0; j < SECONDS_PER_FRAME; ++j) m_walking[i][j] = 0;
}

// Parameterized constructor
Entity::Entity(GLuint texture_id, float speed, glm::vec3 acceleration, float jump_power, int walking[4][4], float animation_time,
    int animation_frames, int animation_index, int animation_cols,
    int animation_rows, float width, float height, EntityType EntityType)
    : m_position(0.0f), m_movement(0.0f), m_scale(1.0f, 1.0f, 0.0f), m_model_matrix(1.0f),
    m_speed(speed),m_acceleration(acceleration), m_jumping_power(jump_power), m_animation_cols(animation_cols),
    m_animation_frames(animation_frames), m_animation_index(animation_index),
    m_animation_rows(animation_rows), m_animation_indices(nullptr),
    m_animation_time(animation_time), m_texture_id(texture_id), m_velocity(0.0f),
    m_width(width), m_height(height), m_entity_type(EntityType)
{
    face_right();
    set_walking(walking);
}

// Simpler constructor for partial initialization
Entity::Entity(GLuint texture_id, float speed,  float width, float height, EntityType EntityType)
    : m_position(0.0f), m_movement(0.0f), m_scale(1.0f, 1.0f, 0.0f), m_model_matrix(1.0f),
    m_speed(speed), m_animation_cols(0), m_animation_frames(0), m_animation_index(0),
    m_animation_rows(0), m_animation_indices(nullptr), m_animation_time(0.0f),
    m_texture_id(texture_id), m_velocity(0.0f), m_acceleration(0.0f), m_width(width), m_height(height),m_entity_type(EntityType)
{
    // Initialize m_walking with zeros or any default value
    for (int i = 0; i < SECONDS_PER_FRAME; ++i)
        for (int j = 0; j < SECONDS_PER_FRAME; ++j) m_walking[i][j] = 0;
}


Entity::Entity(GLuint texture_id, float speed, float width, float height, EntityType EntityType, AIType AIType, AIState AIState): m_position(0.0f), m_movement(0.0f), m_scale(1.0f, 1.0f, 0.0f), m_model_matrix(1.0f),
m_speed(speed), m_animation_cols(0), m_animation_frames(0), m_animation_index(0),
m_animation_rows(0), m_animation_indices(nullptr), m_animation_time(0.0f),
m_texture_id(texture_id), m_velocity(0.0f), m_acceleration(0.0f), m_width(width), m_height(height),m_entity_type(EntityType), m_ai_type(AIType), m_ai_state(AIState)
{
// Initialize m_walking with zeros or any default value
for (int i = 0; i < SECONDS_PER_FRAME; ++i)
    for (int j = 0; j < SECONDS_PER_FRAME; ++j) m_walking[i][j] = 0;
}

Entity::~Entity() { }

void Entity::draw_sprite_from_texture_atlas(ShaderProgram* program, GLuint texture_id, int index)
{
    // Step 1: Calculate the UV location of the indexed frame
    float u_coord = (float)(index % m_animation_cols) / (float)m_animation_cols;
    float v_coord = (float)(index / m_animation_cols) / (float)m_animation_rows;

    // Step 2: Calculate its UV size
    float width = 1.0f / (float)m_animation_cols;
    float height = 1.0f / (float)m_animation_rows;

    // Step 3: Just as we have done before, match the texture coordinates to the vertices
    float tex_coords[] =
    {
        u_coord, v_coord + height, u_coord + width, v_coord + height, u_coord + width, v_coord,
        u_coord, v_coord + height, u_coord + width, v_coord, u_coord, v_coord
    };

    float vertices[] =
    {
        -0.5, -0.5, 0.5, -0.5,  0.5, 0.5,
        -0.5, -0.5, 0.5,  0.5, -0.5, 0.5
    };

    // Step 4: And render
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glVertexAttribPointer(program->get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->get_position_attribute());

    glVertexAttribPointer(program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, tex_coords);
    glEnableVertexAttribArray(program->get_tex_coordinate_attribute());

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(program->get_position_attribute());
    glDisableVertexAttribArray(program->get_tex_coordinate_attribute());
}

bool const Entity::check_collision(Entity* other) const
{
    float x_distance = fabs(m_position.x - other->m_position.x) - ((m_width + other->m_width) / 2.0f);
    float y_distance = fabs(m_position.y - other->m_position.y) - ((m_height + other->m_height) / 2.0f);

    return x_distance < 0.0f && y_distance < 0.0f;
}

void const Entity::check_collision_y(Entity* collidable_entities, int collidable_entity_count) {
    for (int i = 0; i < collidable_entity_count; i++) {
        Entity* collidable_entity = &collidable_entities[i];

        if (!collidable_entity->is_active()) continue;

        if (check_collision(collidable_entity)) {
            float y_distance = fabs(m_position.y - collidable_entity->m_position.y);
            float y_overlap = fabs(y_distance - (m_height / 2.0f) - (collidable_entity->m_height / 2.0f));

            if (m_movement.y > 0) { // Moving up
                m_position.y -= y_overlap;
                m_collided_top = true;
            } else if (m_movement.y < 0) { // Moving down
                m_position.y += y_overlap;
                m_collided_bottom = true;
            }
        }
    }
}


void const Entity::check_collision_x(Entity* collidable_entities, int collidable_entity_count) {
    for (int i = 0; i < collidable_entity_count; i++) {
        Entity* collidable_entity = &collidable_entities[i];

        if (!collidable_entity->is_active()) continue;

        if (check_collision(collidable_entity)) {
            float x_distance = fabs(m_position.x - collidable_entity->m_position.x);
            float x_overlap = fabs(x_distance - (m_width / 2.0f) - (collidable_entity->m_width / 2.0f));

            if (m_movement.x > 0) { // Moving right
                m_position.x -= x_overlap;
                m_collided_right = true;
            } else if (m_movement.x < 0) { // Moving left
                m_position.x += x_overlap;
                m_collided_left = true;
            }
        }
    }
}


void const Entity::check_collision_y(Map *map) {
    glm::vec3 top = glm::vec3(m_position.x, m_position.y + (m_height / 2), m_position.z);
    glm::vec3 bottom = glm::vec3(m_position.x, m_position.y - (m_height / 2), m_position.z);

    float penetration_x = 0;
    float penetration_y = 0;

    if (map->is_solid(top, &penetration_x, &penetration_y)) {
        if (m_velocity.y > 0) { // Moving up
            m_position.y -= penetration_y;
            m_collided_top = true;
        }
    }
    if (map->is_solid(bottom, &penetration_x, &penetration_y)) {
        if (m_velocity.y < 0) { // Moving down
            m_position.y += penetration_y;
            m_collided_bottom = true;
        }
    }
}



void const Entity::check_collision_x(Map *map) {
    glm::vec3 left = glm::vec3(m_position.x - (m_width / 2), m_position.y, m_position.z);
    glm::vec3 right = glm::vec3(m_position.x + (m_width / 2), m_position.y, m_position.z);

    float penetration_x = 0;
    float penetration_y = 0;

    if (map->is_solid(left, &penetration_x, &penetration_y)) {
        if (m_velocity.x < 0) { // Moving left
            m_position.x += penetration_x;
            m_collided_left = true;
        }
    }
    if (map->is_solid(right, &penetration_x, &penetration_y)) {
        if (m_velocity.x > 0) { // Moving right
            m_position.x -= penetration_x;
            m_collided_right = true;
        }
    }
}

void Entity::update(float delta_time, Entity *player, Entity *collidable_entities, int collidable_entity_count, Map *map)
{
    if (!m_is_active) return;

    // Reset collision flags
    m_collided_top = false;
    m_collided_bottom = false;
    m_collided_left = false;
    m_collided_right = false;

    // Activate AI if the entity is an enemy
    if (m_entity_type == ENEMY) ai_activate(player);

    // Handle projectile movement for shooting AI
    if (m_projectile_active) {
        m_projectile_position.x += m_projectile_speed * delta_time;

        // Deactivate projectile if it moves out of screen bounds
        if (m_projectile_position.x > map->get_right_bound() || m_projectile_position.x < map->get_left_bound()) {
            m_projectile_active = false;
        }
    }

    // Update animation only if the entity is moving
    if (glm::length(m_movement) != 0) {
        m_animation_time += delta_time;
        float frames_per_second = (float)1 / SECONDS_PER_FRAME;

        if (m_animation_time >= frames_per_second) {
            m_animation_time = 0.0f;
            m_animation_index++;

            if (m_animation_index >= m_animation_frames) {
                m_animation_index = 0;
            }
        }
    }

    // Calculate velocity based on movement and speed
    m_velocity.x = m_movement.x * m_speed;
    m_velocity.y = m_movement.y * m_speed; // Ensure y velocity is also updated
    m_velocity += m_acceleration * delta_time;

    // Update position based on velocity (y first, then x)
    m_position.y += m_velocity.y * delta_time;
    if (map) check_collision_y(map); // Skip if map collisions are disabled
    check_collision_y(collidable_entities, collidable_entity_count);

    m_position.x += m_velocity.x * delta_time;
    if (map) check_collision_x(map); // Skip if map collisions are disabled
    check_collision_x(collidable_entities, collidable_entity_count);

    // **Clamp the player's position to the map's bounds**
    if (map) {
        m_position.x = glm::clamp(
            m_position.x,
            map->get_left_bound() + (m_width / 2),  // Left boundary
            map->get_right_bound() - (m_width / 2) // Right boundary
        );
        m_position.y = glm::clamp(
            m_position.y,
            map->get_bottom_bound() + (m_height / 2),  // Bottom boundary
            map->get_top_bound() - (m_height / 2)      // Top boundary
        );
    }

    // Update model matrix for rendering
    m_model_matrix = glm::mat4(1.0f);
    m_model_matrix = glm::translate(m_model_matrix, m_position);
}



void Entity::render(ShaderProgram* program) {
    // Render the main entity
    m_model_matrix = glm::mat4(1.0f);
    m_model_matrix = glm::translate(m_model_matrix, m_position);
    m_model_matrix = glm::scale(m_model_matrix, glm::vec3(m_visual_scale, m_visual_scale, 1.0f));
    program->set_model_matrix(m_model_matrix);

    if (m_animation_indices != NULL) {
        draw_sprite_from_texture_atlas(program, m_texture_id, m_animation_indices[m_animation_index]);
    } else {
        float vertices[] = {
            -0.5, -0.5, 0.5, -0.5, 0.5, 0.5,
            -0.5, -0.5, 0.5, 0.5, -0.5, 0.5
        };
        float tex_coords[] = {
            0.0, 1.0, 1.0, 1.0, 1.0, 0.0,
            0.0, 1.0, 1.0, 0.0, 0.0, 0.0
        };

        glBindTexture(GL_TEXTURE_2D, m_texture_id);

        glVertexAttribPointer(program->get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
        glEnableVertexAttribArray(program->get_position_attribute());
        glVertexAttribPointer(program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, tex_coords);
        glEnableVertexAttribArray(program->get_tex_coordinate_attribute());

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glDisableVertexAttribArray(program->get_position_attribute());
        glDisableVertexAttribArray(program->get_tex_coordinate_attribute());
    }

    // Render the projectile if active
    if (m_projectile_active) {
        glm::mat4 projectile_matrix = glm::mat4(1.0f);
        projectile_matrix = glm::translate(projectile_matrix, m_projectile_position);
        program->set_model_matrix(projectile_matrix);

        float projectile_vertices[] = {
            -0.2f, -0.2f, 0.2f, -0.2f, 0.2f, 0.2f,
            -0.2f, -0.2f, 0.2f, 0.2f, -0.2f, 0.2f
        };

        float projectile_tex_coords[] = {
            0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
        };

        glBindTexture(GL_TEXTURE_2D, m_projectile_texture_id);

        glVertexAttribPointer(program->get_position_attribute(), 2, GL_FLOAT, false, 0, projectile_vertices);
        glEnableVertexAttribArray(program->get_position_attribute());
        glVertexAttribPointer(program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, projectile_tex_coords);
        glEnableVertexAttribArray(program->get_tex_coordinate_attribute());

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glDisableVertexAttribArray(program->get_position_attribute());
        glDisableVertexAttribArray(program->get_tex_coordinate_attribute());
    }
}
