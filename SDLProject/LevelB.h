#include "Scene.h"
#include "glm/vec3.hpp"

class LevelB : public Scene {
public:
    int ENEMY_COUNT = 3;
    int ITEM_COUNT = 4;

    ~LevelB();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;

    glm::vec3 get_player_initial_position() const;

private:
    glm::vec3 player_initial_position = glm::vec3(7.0f, 0.0f, 0.0f);
};
