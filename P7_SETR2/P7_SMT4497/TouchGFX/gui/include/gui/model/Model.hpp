#ifndef MODEL_HPP
#define MODEL_HPP

#include <cstdint>

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
protected:
    ModelListener* modelListener;
    bool button_state; // estado del boton en la gui
    uint16_t temp; // estado del gauge en la gui
};

#endif // MODEL_HPP
