#ifndef WORLD_H
#define WORLD_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include <vector>
#include <map>
#include <iostream>

#include "Entity.h"
#include "Fee.h"
#include "Dee.h"
#include "Bot.h"
#include "Collision.h"
#include "CollisionListener.h"
#include "subelements/Presets.h"
#include "subelements/Pos.h"

using namespace std;

class World {

	private: 

		b2World world;

		CollisionListener collisionListener;

		map <int, b2Body*> bodies;

		map <int, Entity*> ids;
		vector <Collision> collisions;
		map <int, vector <Pos>> positions;

		int nTick;
		int nFees;
		int nDees;
		int nBots;

	public:

		World ();
		~World ();

		/*		Entities	*/

		// Adders

		int addFee (float xSize, float ySize, Pos pos, float angle);
		int addDee (float xSize, float ySize, Pos pos, float angle, Presets presets);
		int addBot (float size, Pos pos, float angle, Presets presets);

		// Getters

		Fee* getFee (int id);
		Dee* getDee (int id);
		Bot* getBot (int id);

		// Checkers

		int isFee (int id);
		int isDee (int id);
		int isBot (int id);

		/*		Parameters		*/

		Pos* getPos (int id);
		// int setPos (int id, Pos pos);
		float getAngle (int id);

		/*		Wheels		*/

		float getWheel (int id, int wheel);
		int setWheels (int id, float left, float right);

		/* 		Collisions		*/

		vector <Collision> getCollisions ();

		/*		System		*/

		void tick ();

		void print (int id, int x, int y);

		map<int, string> getIds ();

};

#endif