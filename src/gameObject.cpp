#include <stdlib.h>
#include "gameObject.h"

GameObject::GameObject() {
    hitbox.x = 0;
    hitbox.y = 0;
    hitbox.height = 0;
    hitbox.width = 0;
}

// get the hitbox of the process
Rectangle GameObject::getHitbox() const {
    return hitbox;
}

// sets the position of the rectangle
void GameObject::setPosition(int x, int y) {
    hitbox.x = x;
    hitbox.y = y;
}

// calculates and returns the center point of the hitbox
Point GameObject::getCenter(Rectangle* rectangle) const {
    Point point;
    point.x = rectangle->x + (rectangle->width / 2);
    point.y = rectangle->y + (rectangle->height / 2);
    return point;
}