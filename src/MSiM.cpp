#include "MSiM.h"

	MSiM::MSiM() {

		cout << "MSiM initialised correctly!" << endl;

		string folderPath = "../../storage";

		cout << filesystem::current_path() << endl;

		if (!filesystem::exists(folderPath)) {

			throw runtime_error("Failed to find the storage folder");

		} else {

			vector<string> fileList;

			for (const auto& entry: filesystem::directory_iterator(folderPath)) {
				if (entry.is_regular_file()) {
					fileList.push_back(entry.path().string());
				}
			}

			for (int i = 0; i < fileList.size(); i++) {

				worlds.insert({i+1, fileList[i]});

			}

		}

	}

	MSiM::~MSiM() {

		cout << "MSiM closed!" << endl;

	}

	void MSiM::showWorlds () {

		if (worlds.size() == 0){

			cout << "There are no worlds in the system" << endl;

		} else {

			cout << "Worlds in the system: " << endl;

			for (const auto& pair : worlds) {

				cout << "	- Id: " << pair.first << ", Path: " << pair.second << endl;

			}

		}

	}

	void MSiM::eraseWorld (int id) {

		filesystem::path file = worlds.find(id)->second;

		if (filesystem::exists(file)) {

			if (filesystem::remove(file)) {

				cout << "World with id (" << id << ") removed";
				worlds.erase(worlds.find(id));

			} else {

				cout << "World with id (" << id << ") was not erased. Something went wrong" << endl;

			}

		} else {

			throw runtime_error("Failed to find the world");

		}

	}

	int MSiM::insertWorld (string path) {

		filesystem::path sourceFile = path;

		string fileName = sourceFile.filename().string();

		filesystem::path destinationFile = "../../storage/" + fileName; 

		bool found = false;

		for (const auto& pair : worlds) {

			filesystem::path candidatePath = pair.second;

			string candidate = candidatePath.filename().string();

			if (candidate == fileName) {

				found = true;
				break;

			}

		}

		if (found) {

			throw runtime_error("There is already an existing world with that path filename in the system. Rename it");

		}

		try {

			filesystem::copy(sourceFile, destinationFile, filesystem::copy_options::overwrite_existing);

			worlds.insert({worlds.size()+1, destinationFile.string()});

			cout << "World inserted correctly" << endl;
			return worlds.size();

		} catch (const filesystem::filesystem_error& e) {

			cerr << "Something went wrong copying the file" << endl;
			return -1;

		}

	}

	int MSiM::createWorld(string filename) {

		string fileName = filename + ".txt";

		string destinationFile = "../../storage/" + fileName; 

		bool found = false;

		for (const auto& pair : worlds) {

			filesystem::path candidatePath = pair.second;

			string candidate = candidatePath.filename().string();

			if (candidate == fileName) {

				found = true;
				break;

			}

		}

		if (found) {

			throw runtime_error("There is already an existing world with that filename in the system. Rename it");

		}

		ofstream outFile(destinationFile);

		if (outFile.is_open()) {
			outFile.close();
			worlds.insert({worlds.size()+1, destinationFile});
			return worlds.size();
		} else {
			cerr << "Something went wrong creating the world" << endl;
			return -1;
		}

	}

	vector<string> MSiM::splitByComma(string& str) {
    	vector<std::string> res;
    	istringstream stream(str); 
    	string token;

   		while (getline(stream, token, ',')) { 
        	res.push_back(token);
    	}

    return res;
}

	World* MSiM::loadWorld (int id) {

		// Check if id is correct

		if (worlds.find(id) != worlds.end()) {

			World* world = new World();

			ifstream file(worlds.find(id)->second);

			if (!file.is_open()) {

				throw runtime_error("Cannot access the world file. Something went wrong");

			}

			string line;
			int nLine = 0;
			vector<string> tk;
			int botId = 0;

			while (getline(file, line)) {

				if (nLine == 0) {
					if (line != "[") {
						throw runtime_error("Wrong format at the file. Line: " + to_string(nLine));
					}
					nLine++;
				} else {

					if(line == "];") {
						nLine++;
						cout << "File loaded until line: " << nLine << endl;
						break;
					}

					if(line[1] == 'F' && line[2] == 'E' && line[3] == 'E') {

						line.erase (0,6);
						line.erase(line.length() - 2, 2);

						tk = splitByComma(line);

						if (tk.size() != 5) {
							throw runtime_error("Wrong format at the file. Line: " + to_string(nLine));
						} else {

							world->addFee(stof(tk[2]), stof(tk[3]), Pos(stof(tk[0]), stof(tk[1])), stof(tk[4]));

						}
						nLine++;
						continue;
					}

					if(line[1] == 'D' && line[2] == 'E' && line[3] == 'E') {

						line.erase (0,6);
						line.erase(line.length() - 2, 2);

						tk = splitByComma(line);

						if (tk.size() != 8) {
							throw runtime_error("Wrong format at the file. Line: " + to_string(nLine));
						} else {

							world->addDee(stof(tk[2]), stof(tk[3]), Pos(stof(tk[0]), stof(tk[1])), stof(tk[4]),
								Presets(stof(tk[5]), stof(tk[6]), stof(tk[7])));

						}
						nLine++;
						continue;
					}

					if(line[1] == 'B' && line[2] == 'O' && line[3] == 'T') {

						line.erase (0,6);
						line.erase(line.length() - 2, 2);

						tk = splitByComma(line);

						if (tk.size() != 9) {
							throw runtime_error("Wrong format at the file. Line: " + to_string(nLine));
						} else {

							botId = world->addBot(stof(tk[2]), Pos(stof(tk[0]), stof(tk[1])), stof(tk[3]),
								Presets(stof(tk[4]), stof(tk[5]), stof(tk[6])));
							world->setWheels(botId, stof(tk[7]), stof(tk[8]));

						}
						nLine++;
						continue;
					}

						throw runtime_error("Wrong format at the file. Line: " + to_string(nLine));

				}
				
			}

			file.close();

			return world;

		} else {

			throw runtime_error("Introduced id is not an existing world in the system");

		}

	}

	void MSiM::saveWorld(World* world, string filename) {

		int id = createWorld(filename);

		map<int, string> ids = world->getIds();

		vector<Fee*> fees;
		vector<Dee*> dees;
		vector<Bot*> bots;

		for (const auto& pair : ids) {
			
			int id = pair.first;
			string bodyType = pair.second;

			if (bodyType == "Fee") {

				fees.push_back(world->getFee(id));

			} 

			if (bodyType == "Dee") {

				dees.push_back(world->getDee(id));

			}

			if (bodyType == "Bot") {

				bots.push_back(world->getBot(id));

			}

		}

		ofstream op(worlds.find(id)->second);

		if (!op) {
			cerr << "Something went wrong saving the information into the file" << endl;
		}

		op << fixed << setprecision(1);

		op << "[" << endl;

		for (size_t i = 0; i < fees.size(); i++) {

			op << "(FEE,{" 	<< fees[i]->getPos().getX() << "f, " 
							<< fees[i]->getPos().getY() << "f, "
							<< fees[i]->getXSize() << "f, "
							<< fees[i]->getYSize() << "f, "
							<< fees[i]->getAngle() << "f})" << endl;

		}

		for (size_t i = 0; i < dees.size(); i++) {

			op << "(DEE,{" 	<< dees[i]->getPos().getX() << "f, " 
							<< dees[i]->getPos().getY() << "f, "
							<< dees[i]->getXSize() << "f, "
							<< dees[i]->getYSize() << "f, "
							<< dees[i]->getAngle() << "f, "
							<< dees[i]->getPresets().getDensity() << "f, "
							<< dees[i]->getPresets().getFriction() << "f, "
							<< dees[i]->getPresets().getRestitution() << "f})" << endl;

		}

		for (size_t i = 0; i < bots.size(); i++) {

			op << "(BOT,{" 	<< bots[i]->getPos().getX() << "f, " 
							<< bots[i]->getPos().getY() << "f, "
							<< bots[i]->getSize() << "f, "
							<< bots[i]->getAngle() << "f, "
							<< bots[i]->getPresets().getDensity() << "f, "
							<< bots[i]->getPresets().getFriction() << "f, "
							<< bots[i]->getPresets().getRestitution() << "f, "
							<< bots[i]->getLWheel() << "f, "
							<< bots[i]->getRWheel()	<< "f})" << endl;

		}

		op << "];" << endl;

		op.close();

		cout << "World saved!" << endl;


	}