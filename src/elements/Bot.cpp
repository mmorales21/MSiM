#include "elements/Bot.h"
#include "elements/Entity.h"
#include "elements/subelements/Pos.h"
#include "elements/subelements/Presets.h"

Bot::Bot (int id, Pos pos, float size, float angle, Presets presets, float lWheel, 
	float rWheel) : Entity (id, pos), size (size), angle (angle), presets (presets),
	lWheel (lWheel), rWheel (rWheel) {}

float Bot::getSize () {
	return size;
}

float Bot::getAngle () {
	return angle;
}

Presets Bot::getPresets () {
	return presets;
}

float Bot::getLWheel () {
	return lWheel;
}

float Bot::getRWheel () {
	return rWheel;
}

int Bot::setAngle (float newAngle) {
	angle = newAngle;
	return 0;
}

int Bot::setLWheel (float newLWheel) {
	lWheel = newLWheel;
	return 0;
}

int Bot::setRWheel (float newRWheel) {
	rWheel = newRWheel;
	return 0;
}
