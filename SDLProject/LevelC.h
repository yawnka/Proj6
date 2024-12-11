#include "Scene.h"
#include "glm/vec3.hpp"

class LevelC : public Scene {
public:
    int ENEMY_COUNT = 6;
    int ITEM_COUNT = 8;

    ~LevelC();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;

    glm::vec3 get_player_initial_position() const;

private:
    glm::vec3 player_initial_position = glm::vec3(1.5f, -25.47, 0.0f);
};
