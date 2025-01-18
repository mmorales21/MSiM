#include "elements/Collision.h"
#include "elements/subelements/Pos.h"


using namespace std;

Collision::Collision (int id, int tck, Pos pos, int id1, int id2) : id (id), 
					  tck (tck), pos (pos), id1 (id1), id2 (id2) {}

int Collision::getId () {
	return id;
}

int Collision::getTck () {
	return tck;
}

int Collision::getId1 () {
	return id1;
}

Pos Collision::getPos () {
	return pos;
}

int Collision::getId2 () {
	return id2;
}
