#ifndef FEE_H
#define FEE_H

#include "Entity.h"
#include "subelements/Pos.h"

class Fee : public Entity {
	
	private:

		float xSize;
		float ySize;
		float angle;

	public:

		Fee (int id, Pos pos, float xSize, float ySize, float angle);

		float getXSize ();
		float getYSize ();
		float getAngle ();

};

#endif