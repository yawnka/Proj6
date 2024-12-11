#include "Scene.h"
#include "glm/vec3.hpp"

class LevelD : public Scene {
public:
    int ENEMY_COUNT = 8;
    int ITEM_COUNT = 10;

    ~LevelD();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;

    glm::vec3 get_player_initial_position() const;

private:
    glm::vec3 player_initial_position = glm::vec3(3.5f, -9.5, 0.0f);
};
