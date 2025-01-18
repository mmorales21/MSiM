#include "elements/Entity.h"
#include "elements/subelements/Pos.h"

Entity::Entity (int id, Pos pos) : id (id), pos (pos) {}
Entity::~Entity (){}

int Entity::getId () {
	return id;
}

Pos& Entity::getPos () {
	return pos;
}

int Entity::setPos (Pos newPos) {
	pos = newPos;
	return 0;
}
