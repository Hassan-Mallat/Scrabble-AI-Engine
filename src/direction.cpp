#include "direction.hpp"

Direction::Direction(Type dir) : direction(dir) {}

bool Direction::isHorizontal() const {
    return direction == HORIZONTAL;
}

bool Direction::isVertical() const {
    return direction == VERTICAL;
}

Direction::Type Direction::getType() const {
    return direction;
}
