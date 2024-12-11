#pragma once
#include "Scene.h"

class End : public Scene {
public:
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
    
    void set_items_collected(int items_collected);
private:
    int m_items_collected = 0;
};
