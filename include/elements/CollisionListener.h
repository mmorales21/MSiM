#ifndef COLLISIONLISTENER_H
#define COLLISIONLISTENER_H

#include <Box2D/Box2D.h>
#include <vector>
#include "elements/CollisionAux.h"

using namespace std;

class CollisionListener : public b2ContactListener {
	
	private:

		vector<CollisionAux> collisions;

	public:

		CollisionListener ();
		virtual ~CollisionListener ();

		vector<CollisionAux> getCollisions ();

		virtual void BeginContact (b2Contact* contact) override;
		virtual void EndContact (b2Contact* contact) override;

};

#endif