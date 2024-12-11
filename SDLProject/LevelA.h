#include "Scene.h"
#include "glm/vec3.hpp"

class LevelA : public Scene {
public:
    int ENEMY_COUNT = 2;
    
    ~LevelA();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
    glm::vec3 get_player_initial_position() const;
};
