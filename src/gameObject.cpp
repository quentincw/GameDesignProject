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
    lastX = hitbox.x;
    lastY = hitbox.y;
    hitbox.x = x;
    hitbox.y = y;
}

void GameObject::setLastPosition(float x, float y) {
    lastX = x;
    lastY = y;
}

float GameObject::getLastX() {
    return lastX;
}

float GameObject::getLastY() {
    return lastY;
}

void GameObject::revertPosition() {
    hitbox.x = lastX;
    hitbox.y = lastY;
}

// calculates and returns the center point of the hitbox
Point GameObject::getCenter(Rectangle* rectangle) const {
    Point point;
    point.x = rectangle->x + (rectangle->width / 2);
    point.y = rectangle->y + (rectangle->height / 2);
    return point;
}