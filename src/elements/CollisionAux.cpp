#include <Box2D/Box2D.h>

#include "elements/CollisionAux.h"
#include "elements/subelements/Pos.h"


using namespace std;

CollisionAux::CollisionAux (int id, int tck, Pos pos, b2Body* id1, b2Body* id2) : id (id), 
					  tck (tck), pos (pos), id1 (id1), id2 (id2) {}

int CollisionAux::getId () {
	return id;
}

int CollisionAux::getTck () {
	return tck;
}

b2Body* CollisionAux::getId1 () {
	return id1;
}

Pos CollisionAux::getPos () {
	return pos;
}

b2Body* CollisionAux::getId2 () {
	return id2;
}
