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
            
            if (tile >= 305) {
                tile_index = tile - 305; // Offset for the second tileset
            } else {
                tile_index = tile - 1; // Offset for the first tileset
            }

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

    int tile = m_level_data[tile_y * m_width + tile_x];

    // If there's a second layer, check it for non-zero tiles
    int second_layer_tile = 0;
    if (m_second_layer_data) {
        int second_layer_tile = m_second_layer_data[tile_y * m_width + tile_x];

        if (second_layer_tile != 0) {
            tile = second_layer_tile;
        }
    }

    // Tile IDs for tileset offsets
    const int tileset1_firstgid = 1;
    const int tileset2_firstgid = 305;

    const std::set<int> tileset1_solid_tiles = {21, 22, 23, 24, 26, 106, 28, 78, 79, 80, 50};
    // this whole thing is happening because of some dumb issue with tiled randomly incorporating two tilesets in one.. like what??
    const std::set<int> tileset2_solid_tiles = {970 - 305, 826 - 305, 818 - 305, 899 - 305, 857 - 305,
                                                964 - 305, 962 - 305, 904 - 305, 932 - 305, 942 - 305,
                                                999 - 305, 1018 - 305, 858 - 305, 938 - 305, 1001 - 305,
                                                1020 - 305, 980 - 305, 825 - 305, 973 - 305, 1039 - 305,
                                                940 - 305, 937 - 305, 971 - 305, 825 - 305, 964 - 305};

    // Check if the tile belongs to tileset2
    if (tile >= tileset2_firstgid) {
        int relative_tile = tile - tileset2_firstgid; // Calculate relative ID for tileset2
        if (tileset2_solid_tiles.find(relative_tile) != tileset2_solid_tiles.end()) {
            float tile_center_x = (tile_x * m_tile_size);
            float tile_center_y = -(tile_y * m_tile_size);

            *penetration_x = (m_tile_size / 2) - fabs(position.x - tile_center_x);
            *penetration_y = (m_tile_size / 2) - fabs(position.y - tile_center_y);
            return true;
        }
    }

    // Check if the tile belongs to tileset1 + this handles layer 2 as well.
    if (tile >= tileset1_firstgid && tile < tileset2_firstgid) {
        if (tileset1_solid_tiles.find(tile) != tileset1_solid_tiles.end()) {
            float tile_center_x = (tile_x * m_tile_size);
            float tile_center_y = -(tile_y * m_tile_size);

            *penetration_x = (m_tile_size / 2) - fabs(position.x - tile_center_x);
            *penetration_y = (m_tile_size / 2) - fabs(position.y - tile_center_y);
            return true;
        }
        return false;
    }

    // Check the second layer for tileset2
    if (second_layer_tile >= tileset2_firstgid) {
        int relative_tile = second_layer_tile - tileset2_firstgid; // Calculate relative ID for tileset2
        if (tileset2_solid_tiles.find(relative_tile) != tileset2_solid_tiles.end()) {
            float tile_center_x = (tile_x * m_tile_size);
            float tile_center_y = -(tile_y * m_tile_size);

            *penetration_x = (m_tile_size / 2) - fabs(position.x - tile_center_x);
            *penetration_y = (m_tile_size / 2) - fabs(position.y - tile_center_y);
            return true;
        }
    }
    return false;
}
