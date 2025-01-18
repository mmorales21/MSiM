#include "elements/subelements/Presets.h"

Presets::Presets (float density, float friction, float restitution) : density (density), 
				  friction (friction), restitution (restitution) {}

float Presets::getDensity () {
	return density;
}

float Presets::getFriction () {
	return friction;
}

float Presets::getRestitution () {
	return restitution;
}
