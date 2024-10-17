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
{       // Gestion des interactions tactiles
    int touchCount = GetTouchPointCount();

    // Gestion des interactions tactiles/souris
    if (touchCount > 1) {
        return true;
    } else {
        return false;
    }
}
