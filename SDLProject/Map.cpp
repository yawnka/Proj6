#include "Map.h"

Map::Map(GLuint texture_id, float tile_size, int tile_count_x, int tile_count_y,
         const std::vector<unsigned int>& layer1, const std::vector<unsigned int>& layer2)
    : m_texture_id(texture_id), m_tile_size(tile_size), m_tile_count_x(tile_count_x), m_tile_count_y(tile_count_y) {
    m_width = 32;  // Replace with your map's width
    m_height = 32; // Replace with your map's height

    // Store layers in the internal vector
    m_layers.push_back(layer1); // First layer
    m_layers.push_back(layer2); // Second layer

    // Build the map based on these layers
    build();
}

void Map::build() {
    for (int layer = 0; layer < m_layers.size(); ++layer) {
        for (int y = 0; y < m_height; ++y) {
            for (int x = 0; x < m_width; ++x) {
                int tile = m_layers[layer][y * m_width + x] - 1; // Adjust for 1-based indexing
                if (tile < 0) continue;

                // Calculate UV coordinates
                float tile_width = 1.0f / m_tile_count_x; // 1.0f / 64
                float tile_height = 1.0f / m_tile_count_y; // 1.0f / 40

                float u = (tile % m_tile_count_x) * tile_width;
                float v = (tile / m_tile_count_x) * tile_height;

                float x_offset = -(m_tile_size / 2);
                float y_offset = (m_tile_size / 2);
                
                std::cout << "Tile: " << tile << ", U: " << u << ", V: " << v << std::endl;

                m_vertices.insert(m_vertices.end(), {
                    x_offset + (m_tile_size * x), y_offset + -(m_tile_size * y),
                    x_offset + (m_tile_size * x), y_offset + -(m_tile_size * y) - m_tile_size,
                    x_offset + (m_tile_size * x) + m_tile_size, y_offset + -(m_tile_size * y) - m_tile_size,
                    x_offset + (m_tile_size * x), y_offset + -(m_tile_size * y),
                    x_offset + (m_tile_size * x) + m_tile_size, y_offset + -(m_tile_size * y) - m_tile_size,
                    x_offset + (m_tile_size * x) + m_tile_size, y_offset + -(m_tile_size * y),
                });

                m_texture_coordinates.insert(m_texture_coordinates.end(), {
                    u, v,
                    u, v + tile_height,
                    u + tile_width, v + tile_height,
                    u, v,
                    u + tile_width, v + tile_height,
                    u + tile_width, v
                });
            }
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
    
    glDrawArrays(GL_TRIANGLES, 0, (int) m_vertices.size() / 2);
    glDisableVertexAttribArray(program->get_position_attribute());
    glDisableVertexAttribArray(program->get_tex_coordinate_attribute());
}

bool Map::is_solid(glm::vec3 position, float *penetration_x, float *penetration_y)
{
    // The penetration between the map and the object
    // The reason why these are pointers is because we want to reassign values
    // to them in case that we are colliding. That way the object that originally
    // passed them as values will keep track of these distances
    // inb4: we're passing by reference
    *penetration_x = 0;
    *penetration_y = 0;
    
    return false;
}

void Map::render_layer(ShaderProgram* program, int layer_index) {
    if (layer_index < 0 || layer_index >= m_layers.size()) return;

    glm::mat4 model_matrix = glm::mat4(1.0f);
    program->set_model_matrix(model_matrix);

    glUseProgram(program->get_program_id());

    glVertexAttribPointer(program->get_position_attribute(), 2, GL_FLOAT, false, 0, m_vertices.data());
    glEnableVertexAttribArray(program->get_position_attribute());
    glVertexAttribPointer(program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, m_texture_coordinates.data());
    glEnableVertexAttribArray(program->get_tex_coordinate_attribute());

    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glDrawArrays(GL_TRIANGLES, 0, (int)m_vertices.size() / 2);
    glDisableVertexAttribArray(program->get_position_attribute());
    glDisableVertexAttribArray(program->get_tex_coordinate_attribute());
}

int Map::get_layer_count() const {
    return m_layers.size();
}
