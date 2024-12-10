#include "Map.h"

Map::Map(const char* tmx_file, GLuint texture_id, float tile_size, int tile_count_x, int tile_count_y)
    : m_texture_id(texture_id), m_tile_size(tile_size), m_tile_count_x(tile_count_x), m_tile_count_y(tile_count_y) {

    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(tmx_file) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Failed to load TMX file: " << tmx_file << std::endl;
        return;
    }

    auto mapElement = doc.FirstChildElement("map");
    m_width = mapElement->IntAttribute("width");
    m_height = mapElement->IntAttribute("height");

    auto layerElement = mapElement->FirstChildElement("layer");
    while (layerElement) {
        auto dataElement = layerElement->FirstChildElement("data");
        std::string data = dataElement->GetText();

        // Decode CSV layer data
        std::vector<unsigned int> layer_data;
        std::stringstream ss(data);
        std::string token;
        while (std::getline(ss, token, ',')) {
            layer_data.push_back(std::stoi(token));
        }

        m_layers.push_back(layer_data); // Store layer data
        layerElement = layerElement->NextSiblingElement("layer");
    }

    build();
}


void Map::build() {
    for (int layer = 0; layer < m_layers.size(); ++layer) {
        for (int y = 0; y < m_height; ++y) {
            for (int x = 0; x < m_width; ++x) {
                int tile = m_layers[layer][y * m_width + x];
                if (tile == 0) continue;

                float u = (float)(tile % m_tile_count_x) / m_tile_count_x;
                float v = (float)(tile / m_tile_count_x) / m_tile_count_y;

                float tile_width = 1.0f / m_tile_count_x;
                float tile_height = 1.0f / m_tile_count_y;

                float x_offset = -(m_tile_size / 2);
                float y_offset = (m_tile_size / 2);

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
