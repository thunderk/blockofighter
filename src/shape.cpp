#include "shape.h"

Shape::Shape(Object *object) { this->object = object; }

bool Shape::checkCollision(Object *target) { return false; }
bool Shape::checkCollisionPeer(Shape *target) { return false; }
bool Shape::checkCollisionPeer(SphereShape *target) { return false; }
bool Shape::checkCollisionPeer(MeshShape *target) { return false; }
