#include "elements/CollisionListener.h"
#include <iostream>
#include <string>

using namespace std;

	CollisionListener::CollisionListener() : collisions{} {}

	CollisionListener::~CollisionListener(){}

	vector<CollisionAux> CollisionListener::getCollisions() {

		return collisions;

	}

	void CollisionListener::BeginContact(b2Contact* contact) {


		
		b2Body* pointerA = contact->GetFixtureA()->GetBody();
		b2Body* pointerB = contact->GetFixtureB()->GetBody();

		b2WorldManifold worldManifold;
		contact->GetWorldManifold(&worldManifold);

		float x = worldManifold.points[0].x;
		float y = worldManifold.points[0].y;

		Pos pos(x, y);

		CollisionAux c (0, 0, pos, pointerA, pointerB);

		collisions.push_back(c);

	//	cout << "Body " << pointerA << "and body " << pointerB << " collisioned at " 
	//	<< x << ", " << y << endl;

	}

	void CollisionListener::EndContact(b2Contact* contact) {

	}


