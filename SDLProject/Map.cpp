#include "Map.h"
#include <set>

Map::Map(int width, int height, unsigned int *level_data, GLuint texture_id, float tile_size,
         int tile_count_x, int tile_count_y, unsigned int *second_layer_data) :
    m_width(width), m_height(height), m_level_data(level_data), m_texture_id(texture_id),
    m_tile_size(tile_size), m_tile_count_x(tile_count_x), m_tile_count_y(tile_count_y),
    m_second_layer_data(second_layer_data)
{
    build();
    if (m_second_layer_data) build_second_layer();
}


void Map::build() {
    for (int y_coord = 0; y_coord < m_height; y_coord++) {
        for (int x_coord = 0; x_coord < m_width; x_coord++) {
            int tile = m_level_data[y_coord * m_width + x_coord];

            // Skip empty tiles
            if (tile == 0) continue;

            // Adjust for one-based tile indexing
            int tile_index = tile - 1;

            // UV coordinates
            float u_coord = (float)(tile_index % m_tile_count_x) / (float)m_tile_count_x;
            float v_coord = (float)(tile_index / m_tile_count_x) / (float)m_tile_count_y;

            float tile_width = 1.0f / (float)m_tile_count_x;
            float tile_height = 1.0f / (float)m_tile_count_y;

            float x_offset = -(m_tile_size / 2); // From center of tile
            float y_offset = (m_tile_size / 2);  // From center of tile

            // Vertices
            m_vertices.insert(m_vertices.end(), {
                x_offset + (m_tile_size * x_coord), y_offset + -m_tile_size * y_coord,
                x_offset + (m_tile_size * x_coord), y_offset + (-m_tile_size * y_coord) - m_tile_size,
                x_offset + (m_tile_size * x_coord) + m_tile_size, y_offset + (-m_tile_size * y_coord) - m_tile_size,
                x_offset + (m_tile_size * x_coord), y_offset + -m_tile_size * y_coord,
                x_offset + (m_tile_size * x_coord) + m_tile_size, y_offset + (-m_tile_size * y_coord) - m_tile_size,
                x_offset + (m_tile_size * x_coord) + m_tile_size, y_offset + -m_tile_size * y_coord
            });

            // Texture coordinates
            m_texture_coordinates.insert(m_texture_coordinates.end(), {
                u_coord, v_coord,
                u_coord, v_coord + tile_height,
                u_coord + tile_width, v_coord + tile_height,
                u_coord, v_coord,
                u_coord + tile_width, v_coord + tile_height,
                u_coord + tile_width, v_coord
            });
        }
    }

    // Bounds
    m_left_bound = 0 - (m_tile_size / 2);
    m_right_bound = (m_tile_size * m_width) - (m_tile_size / 2);
    m_top_bound = 0 + (m_tile_size / 2);
    m_bottom_bound = -(m_tile_size * m_height) + (m_tile_size / 2);
}

void Map::build_second_layer() {
    for (int y_coord = 0; y_coord < m_height; y_coord++) {
        for (int x_coord = 0; x_coord < m_width; x_coord++) {
            int tile = m_second_layer_data[y_coord * m_width + x_coord];

            // Skip empty tiles
            if (tile == 0) continue;

            // Adjust for one-based tile indexing
            int tile_index = tile - 1;

            // UV coordinates
            float u_coord = (float)(tile_index % m_tile_count_x) / (float)m_tile_count_x;
            float v_coord = (float)(tile_index / m_tile_count_x) / (float)m_tile_count_y;

            float tile_width = 1.0f / (float)m_tile_count_x;
            float tile_height = 1.0f / (float)m_tile_count_y;

            float x_offset = -(m_tile_size / 2); // From center of tile
            float y_offset = (m_tile_size / 2);  // From center of tile

            // Vertices for the second layer
            m_vertices.insert(m_vertices.end(), {
                x_offset + (m_tile_size * x_coord), y_offset + -m_tile_size * y_coord,
                x_offset + (m_tile_size * x_coord), y_offset + (-m_tile_size * y_coord) - m_tile_size,
                x_offset + (m_tile_size * x_coord) + m_tile_size, y_offset + (-m_tile_size * y_coord) - m_tile_size,
                x_offset + (m_tile_size * x_coord), y_offset + -m_tile_size * y_coord,
                x_offset + (m_tile_size * x_coord) + m_tile_size, y_offset + (-m_tile_size * y_coord) - m_tile_size,
                x_offset + (m_tile_size * x_coord) + m_tile_size, y_offset + -m_tile_size * y_coord
            });

            // Texture coordinates
            m_texture_coordinates.insert(m_texture_coordinates.end(), {
                u_coord, v_coord,
                u_coord, v_coord + tile_height,
                u_coord + tile_width, v_coord + tile_height,
                u_coord, v_coord,
                u_coord + tile_width, v_coord + tile_height,
                u_coord + tile_width, v_coord
            });
        }
    }
}



void Map::render(ShaderProgram *program)
{
    glm::mat4 model_matrix = glm::mat4(1.0f);
    program->set_model_matrix(model_matrix);

    glUseProgram(program->get_program_id());

    glVertexAttribPointer(program->get_position_attribute(), 2, GL_FLOAT, false, 0, m_vertices.data());
    glEnableVertexAttribArray(program->get_position_attribute());
    glVertexAttribPointer(program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, m_texture_coordinates.data());
    glEnableVertexAttribArray(program->get_tex_coordinate_attribute());

    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    // Draw the first layer
    glDrawArrays(GL_TRIANGLES, 0, (int)m_vertices.size() / 2);

    // Draw the second layer (if present)
    if (m_second_layer_data) {
        glDrawArrays(GL_TRIANGLES, (int)m_vertices.size() / 2, (int)m_vertices.size() / 2);
    }

    glDisableVertexAttribArray(program->get_position_attribute());
    glDisableVertexAttribArray(program->get_tex_coordinate_attribute());
}



bool Map::is_solid(glm::vec3 position, float *penetration_x, float *penetration_y) {
    *penetration_x = 0;
    *penetration_y = 0;

    if (position.x < m_left_bound || position.x > m_right_bound) return false;
    if (position.y > m_top_bound || position.y < m_bottom_bound) return false;

    int tile_x = floor((position.x + (m_tile_size / 2)) / m_tile_size);
    int tile_y = -(ceil(position.y - (m_tile_size / 2)) / m_tile_size);

    if (tile_x < 0 || tile_x >= m_width) return false;
    if (tile_y < 0 || tile_y >= m_height) return false;

    // Check the first layer
    int tile = m_level_data[tile_y * m_width + tile_x];

    // Check the second layer if available
    if (m_second_layer_data) {
        int second_layer_tile = m_second_layer_data[tile_y * m_width + tile_x];

        if (second_layer_tile != 0) {
            tile = second_layer_tile;
        }
    }

    // Define the set of solid tiles
    const std::set<int> solid_tiles = {21, 22, 23, 24, 26, 106, 28, 78, 79, 80, 50};

    if (solid_tiles.find(tile) != solid_tiles.end()) {
        float tile_center_x = (tile_x * m_tile_size);
        float tile_center_y = -(tile_y * m_tile_size);

        *penetration_x = (m_tile_size / 2) - fabs(position.x - tile_center_x);
        *penetration_y = (m_tile_size / 2) - fabs(position.y - tile_center_y);
        return true;
    }
    return false;
}
