#include "button.h"

Button::Button(Vector2 ButtonPosition, float ButtonRadius, Color Buttoncolor):
    pos(ButtonPosition),
    buttonradius(ButtonRadius),
    color(Buttoncolor),
    pressed(false)
{
    
}

void Button::draw()
{
    DrawCircleV(pos, buttonradius, (Color){170,170,170,120});
}

void Button::Update()
{
}

bool Button::ispressed()
{   
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointCircle(GetMousePosition(), pos, buttonradius)) {
        return true;
    } else {
        return false;
    }
}
