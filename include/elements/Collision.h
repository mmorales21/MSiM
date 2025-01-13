#ifndef COLLISION_H
#define COLLISION_H

#include "subelements/Pos.h"

using namespace std;

class Collision {

	private:

		int id;
		int tck;
		int id1;
		Pos pos;
		int id2;

	public:

		Collision (int id, int tck, Pos pos, int id1, int id2);

		int getId ();
		int getTck ();
		int getId1 ();
		Pos getPos ();
		int getId2 ();
	
};

#endif
