#include "elements/Fee.h"
#include "elements/Entity.h"
#include "elements/subelements/Pos.h"

Fee::Fee (int id, Pos pos, float xSize, float ySize, float angle) : Entity (id, pos), 
		  xSize (xSize), ySize (ySize), angle (angle) {}

float Fee::getXSize () {
	return xSize;
}

float Fee::getYSize () {
	return ySize;
}

float Fee::getAngle () {
	return angle;
}
