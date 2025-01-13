#ifndef BOT_H
#define BOT_H

#include "Entity.h"
#include "subelements/Pos.h"
#include "subelements/Presets.h"

class Bot : public Entity {
	
	private:

		float size;
		float angle;
		Presets presets;
		float lWheel;
		float rWheel;

	public:

		Bot (int id, Pos pos, float size, float angle, Presets presets, float lWheel, float rWheel);

		float getSize ();
		float getAngle ();
		Presets getPresets ();
		float getLWheel ();
		float getRWheel ();

		int setAngle (float newAngle);
		int setLWheel (float newLWheel);
		int setRWheel (float newRWheel);

};

#endif