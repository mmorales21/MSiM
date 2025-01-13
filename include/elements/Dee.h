#ifndef DEE_H
#define DEE_H

#include "Entity.h"
#include "subelements/Pos.h"
#include "subelements/Presets.h"

class Dee : public Entity {
	
	private:

		float xSize;
		float ySize;
		float angle;
		Presets presets;

	public:

		Dee (int id, Pos pos, float xSize, float ySize, float angle, Presets presets);

		float getXSize ();
		float getYSize ();
		float getAngle ();
		void setAngle (float newAngle);
		Presets getPresets ();

};

#endif