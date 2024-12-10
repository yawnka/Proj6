#include "Scene.h"

class LevelA : public Scene {
public:
    int ENEMY_COUNT = 2;
    
    ~LevelA();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
    GLuint map_texture_id;
};
