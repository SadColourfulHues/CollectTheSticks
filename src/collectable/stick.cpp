#include "stick.hpp"

using namespace game;

Stick::Stick()
{
}

Stick::~Stick()
{
}

void Stick::_ready()
{
    Sprite2D *sprite = static_cast<Sprite2D *>(get_node_or_null("Sprite2D"));

    if (sprite == nullptr)
    {
        ERR_PRINT("Stick: A stick node must have a Sprite2D child.");
        return;
    }

    RandomNumberGenerator p_random;
    p_random.randomize();

    sprite->set_frame(p_random.randi() % sprite->get_hframes());
}