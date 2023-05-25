#ifndef DRAWABLECOMPONENT_HPP
#define DRAWABLECOMPONENT_HPP

#include "component.hpp"
class DrawableComponent : public virtual Component
{
public:
    virtual void onDraw() = 0;
    DrawableComponent();
};

#endif //DRAWABLECOMPONENT_HPP
