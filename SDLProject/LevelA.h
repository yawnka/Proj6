#include "Scene.h"
#include "glm/vec3.hpp"

class LevelA : public Scene {
public:
    int ENEMY_COUNT = 2;
    int ITEM_COUNT = 4;

    ~LevelA();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;

    glm::vec3 get_player_initial_position() const; // Getter for initial position

private:
    glm::vec3 player_initial_position = glm::vec3(10.5f, -10.0f, 0.0f); // Initial position
};
