#include "elements/Dee.h"
#include "elements/Entity.h"
#include "elements/subelements/Pos.h"
#include "elements/subelements/Presets.h"

Dee::Dee (int id, Pos pos, float xSize, float ySize, float angle, Presets presets) : 
		  Entity (id, pos), xSize (xSize), ySize (ySize), angle (angle), presets (presets) {}

float Dee::getXSize () {
	return xSize;
}

float Dee::getYSize () {
	return ySize;
}

float Dee::getAngle () {
	return angle;
}

Presets Dee::getPresets () {
	return presets;
}

void Dee::setAngle (float newAngle) {
	angle = newAngle;
}

