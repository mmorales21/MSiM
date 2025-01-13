#ifndef MSIM_H
#define MSIM_H

#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <iomanip>

#include "elements/World.h"
#include "elements/Entity.h"
#include "elements/Fee.h"
#include "elements/Dee.h"
#include "elements/Bot.h"
#include "elements/Collision.h"
#include "elements/CollisionListener.h"
#include "elements/subelements/Presets.h"
#include "elements/subelements/Pos.h"

using namespace std;

class MSiM {

	private:

		map<int, string> worlds;
		vector<string> splitByComma (string& str);

	public:

		MSiM();
		~MSiM();

		World* loadWorld (int id);
		void showWorlds ();
		int createWorld (string filename);
		int insertWorld (string path);
		void saveWorld (World* world, string filename);
		void eraseWorld (int id);
		
	
};

#endif