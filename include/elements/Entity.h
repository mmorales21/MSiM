#ifndef ENTITY_H
#define ENTITY_H

#include "subelements/Pos.h"

class Entity {

	private:

		int id;
		Pos pos;

	public:

		Entity (int id, Pos pos);
		virtual ~Entity();

		int getId ();
		Pos& getPos ();
		int setPos (Pos newPos);

};

#endif