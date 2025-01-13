#ifndef COLLISIONAUX_H
#define COLLISIONAUX_H

#include <Box2D/Box2D.h>
#include "subelements/Pos.h"

using namespace std;

class CollisionAux {

	private:

		int id;
		int tck;
		b2Body* id1;
		Pos pos;
		b2Body* id2;

	public:

		CollisionAux (int id, int tck, Pos pos, b2Body* id1, b2Body* id2);

		int getId ();
		int getTck ();
		b2Body* getId1 ();
		Pos getPos ();
		b2Body* getId2 ();
	
};

#endif
