#include "elements/World.h"

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include <vector>
#include <map>
#include <iterator>
#include <iostream>
#include "elements/Entity.h"
#include "elements/Fee.h"
#include "elements/Dee.h"
#include "elements/Bot.h"
#include "elements/Collision.h"
#include "elements/CollisionListener.h"
#include "elements/subelements/Presets.h"
#include "elements/subelements/Pos.h"

using namespace std;

#define FEE_VAL 30000
#define DEE_VAL 20000
#define BOT_VAL 10000
#define ERR -99999

	World::World () 

		: 	world (b2Vec2 (0.0f, 0.0f), true),
			bodies {},
			ids {},
			collisions {},
			positions {},
			nTick (0),
			nFees (0),
			nDees (0),
			nBots (0)

		{

			world.SetContactListener(&collisionListener);

			cout << "World created without problems!" << endl;

		}

	World::~World () {

		for (auto& entry : bodies) {

			world.DestroyBody(entry.second);

		}

		cout << "World destroyed sucessfully!" << endl;

	}

	/*		Entities	*/

	// Adders

	int World::addFee (float xSize, float ySize, Pos pos, float angle) {

		try {

				b2BodyDef bodyDef;
				bodyDef.position.Set(pos.getX(), pos.getY());
				bodyDef.angle = angle;
				bodyDef.type = b2_staticBody;

				b2Body* body = world.CreateBody(&bodyDef);

				if (body == nullptr) {

					throw runtime_error("Failed to create the body at the engine");

				}

				b2PolygonShape box;
				box.SetAsBox(xSize, ySize);
				b2FixtureDef fixtureDef;
				fixtureDef.shape = &box;

				if (!body->CreateFixture(&fixtureDef)) {

					throw runtime_error("Failed to create the fixture for the body at the engine");

				}

				nFees++;

				int newId = FEE_VAL + nFees;

				bodies.insert({newId, body});
				ids.insert({newId, new Fee (newId, pos, xSize, ySize, angle)});

				vector<Pos> idPositions;

				idPositions.push_back(pos);

				positions.insert({newId, idPositions});

				return newId;

			} catch (const exception& e) {

				cerr << "Error: " << e.what() << endl;
				return 1;

			}

	}

	int World::addDee (float xSize, float ySize, Pos pos, float angle, Presets presets) {

			try {

				b2BodyDef bodyDef;
				bodyDef.position.Set(pos.getX(), pos.getY());
				bodyDef.angle = angle;
				bodyDef.type = b2_dynamicBody;

				b2Body* body = world.CreateBody(&bodyDef);

				if (body == nullptr) {

					throw runtime_error("Failed to create the body at the engine");

				}

				b2PolygonShape box;
				box.SetAsBox(xSize, ySize);

				b2FixtureDef fixtureDef;
				fixtureDef.shape = &box;
				fixtureDef.density = presets.getDensity();
				fixtureDef.friction = presets.getFriction();
				fixtureDef.restitution = presets.getRestitution();

				if (!body->CreateFixture(&fixtureDef)) {

					throw runtime_error("Failed to create the fixture for the body at the engine");

				}

				nDees++;

				int newId = DEE_VAL + nDees;

				bodies.insert({newId, body});
				ids.insert({newId, new Dee (newId, pos, xSize, ySize, angle, presets)});

				vector<Pos> idPositions;

				idPositions.push_back(pos);

				positions.insert({newId, idPositions});
				
				return newId;

			} catch (const exception& e) {

				cerr << "Error: " << e.what() << endl;
				return 1;

			}

	}

	int World::addBot (float size, Pos pos, float angle, Presets presets) {

		try {

				b2BodyDef bodyDef;
				bodyDef.position.Set(pos.getX(), pos.getY());
				bodyDef.angle = angle;
				bodyDef.type = b2_dynamicBody;

				b2Body* body = world.CreateBody(&bodyDef);

				if (body == nullptr) {

					throw runtime_error("Failed to create the body at the engine");

				}

				b2CircleShape circleShape;
				circleShape.m_radius = size;

				b2FixtureDef fixtureDef;
				fixtureDef.shape = &circleShape;
				fixtureDef.density = presets.getDensity();
				fixtureDef.friction = presets.getFriction();
				fixtureDef.restitution = presets.getRestitution();

				if (!body->CreateFixture(&fixtureDef)) {

					throw runtime_error("Failed to create the fixture for the body at the engine");

				}

				nBots++;
				int newId = BOT_VAL + nBots;

				bodies.insert({newId, body});
				ids.insert({newId, new Bot (newId, pos, size, angle, presets, 0.0f, 0.0f)});

				vector<Pos> idPositions;

				idPositions.push_back(pos);

				positions.insert({newId, idPositions});

				return newId;

			} catch (const exception& e) {

				cerr << "Error: " << e.what() << endl;
				return 1;

			}

	}

	// Getters

	Fee* World::getFee (int id) {

		if (isFee(id)) {

			auto iter = ids.find(id);

			if (iter != ids.end()) {

				return dynamic_cast<Fee*> (iter->second);

			} else {

				cerr << "Error: id (" << id << ") is not introduced in the system" << endl;
				return nullptr;

			}

		} else {	

			cerr << "Error: id (" << id << ") is not a Fee" << endl;
			return nullptr;

		}

	}

	Dee* World::getDee (int id) {

		if (isDee(id)) {

			auto iter = ids.find(id);

			if (iter != ids.end()) {

				return dynamic_cast<Dee*> (iter->second);

			} else {

				cerr << "Error: id (" << id << ") is not introduced in the system" << endl;
				return nullptr;

			}

		} else {	

			cerr << "Error: id (" << id << ") is not a Dee" << endl;
			return nullptr;

		}

	}

	Bot* World::getBot (int id) {

		if (isBot(id)) {

			auto iter = ids.find(id);

			if (iter != ids.end()) {

				return dynamic_cast<Bot*> (iter->second);

			} else {

				cerr << "Error: id (" << id << ") is not introduced in the system" << endl;
				return nullptr;

			}

		} else {	

			cerr << "Error: id (" << id << ") is not a Bot" << endl;
			return nullptr;

		}

	}

	// Checkers

	int World::isFee (int id) {
		
		int n = id - FEE_VAL;

		if (n > 0 && n < 10000) {

			return 1;

		} else {

			return 0;

		}

	}

	int World::isDee (int id) {

		int n = id - DEE_VAL;

		if (n > 0 && n < 10000) {

			return 1;

		} else {

			return 0;

		}

	}

	int World::isBot (int id) {

		int n = id - BOT_VAL;

		if (n > 0 && n < 10000) {

			return 1;

		} else {

			return 0;

		}

	}

	/*		Parameters		*/

	Pos* World::getPos (int id) {

		auto iter = ids.find(id);

		if (iter != ids.end()) {

			return &(iter->second->getPos());
		
		} else {

			cerr << "Error: id (" << id << ") is not introduced in the system" << endl;
			return nullptr;

		}

	}

	float World::getAngle (int id) {

		auto iter = ids.find(id);

		if (iter != ids.end()) {

			if (isFee(id)) {

				return (dynamic_cast<Fee*> (iter->second)->getAngle());

			}

			if (isDee(id)) {

				return (dynamic_cast<Dee*> (iter->second)->getAngle());

			}

			if (isBot(id)) {

				return (dynamic_cast<Bot*> (iter->second)->getAngle());

			}

			return ERR;

		} else {

			cerr << "Error: id (" << id << ") is not introduced in the system" << endl;
			return ERR;

		}

	}
	
	/*		Wheels		*/

	float World::getWheel (int id, int wheel) {

		if (wheel != 0 && wheel != 1) {

			cerr << "Error: wheel introduced as parameter is not 0 (left) or 1 (right)" << endl;
			return -999;

		}

		auto iter = ids.find(id);

		if (iter != ids.end()) {

			if (isBot(id) == 1) {

				if (wheel == 0) {

					return (dynamic_cast<Bot*> (iter->second)->getLWheel());

				} else {

					return (dynamic_cast<Bot*> (iter->second)->getRWheel());

				}

			} else {

				cerr << "Error: id (" << id << ") is not a Bot object" << endl;
				return ERR;

			}

		} else {

			cerr << "Error: id (" << id << ") is not introduced in the system" << endl;
			return ERR;

		}

	}

	int World::setWheels (int id, float left, float right) {

		auto iter = ids.find(id);

		if (iter != ids.end()) {

			if (isBot(id)) {

			try {

					b2Body* body = bodies.find(id)->second;

					float size = (dynamic_cast<Bot*> (iter->second))->getSize();

					float angle = (dynamic_cast<Bot*> (iter->second))->getAngle();

					// Coger con pinzas

					float x = ((left + right) / 2) * cos (angle);
					float y = ((left + right) / 2) * sin (angle);
					float w = (right - left) / (size/2);

					b2Vec2 newVelocity(x, y);

					body->SetLinearVelocity(newVelocity);

					body->SetAngularVelocity(w);

					(dynamic_cast<Bot*> (ids.find(id)->second))->setLWheel(left);
					(dynamic_cast<Bot*> (ids.find(id)->second))->setRWheel(right);

				} catch (const exception& e) {

					cerr << "Error: " << e.what() << endl;
					return ERR;

				}

				return 0;

			} else {

				cerr << "Error: id (" << id << ") is not a Bot object" << endl;
				return ERR;

			}

		} else {

			cerr << "Error: id (" << id << ") is not introduced in the system" << endl;
			return ERR;

		}

	}

	/* 		Collisions		*/

	vector <Collision> World::getCollisions () {

		return collisions;

	}

	/*		System		*/

	void World::tick () {

		world.Step(1.0f / 60.0f, 8, 3);
		nTick++;

		// Update information

		for (const auto& pair : bodies) {

			int id = pair.first;

			b2Body* body = pair.second;

			b2Vec2 position = body->GetPosition();

			positions[id].push_back(Pos(position.x, position.y));

			// cout << id << endl;

			// cout << isFee(id) << "  " << isDee(id) << "  " << isBot(id) << endl;

			if (isBot(id) || isDee(id)) {
			
				float angle = body->GetAngle();

				auto iter = ids.find(id);

				if (iter != ids.end()) {

					iter->second->setPos(Pos(position.x, position.y));

					if (isDee(id)) {
					
						(dynamic_cast<Dee*> (iter->second))->setAngle(angle);

					}

					if (isBot(id)) {

						(dynamic_cast<Bot*> (iter->second))->setAngle(angle);

						// setWheels
				
					}
					
				}

			}

		}

		// getCollisions

		size_t nCollisions = collisions.size();

		vector<CollisionAux> worldCollisions = collisionListener.getCollisions();

		size_t nWCollisions = worldCollisions.size();

		if (nCollisions < nWCollisions) {

			for (size_t i = nCollisions; i < nWCollisions; ++i) {

				CollisionAux c = worldCollisions[i];

				b2Body* idTarget1 = c.getId1();
				b2Body* idTarget2 = c.getId2();

				int id1 = -1;
				int id2 = -1;

				for (const auto& entry : bodies) {

					int key = entry.first;
					b2Body* body = entry.second;

					if (id1 == -1) {

						if (body == idTarget1) {

							id1 = key;
							continue;

						}

						if (body == idTarget2) {

							id2 = key;
							continue;

						}

					}

					if (id2 == -1) {

						if (body == idTarget1) {

							id1 = key;
							continue;

						}

						if (body == idTarget2) {

							id2 = key;
							continue;

						}

					}

					if (id1 != -1 && id2 != -1) {

						break;

					}

				}

				Pos pos = c.getPos();

				Collision newCollision (collisions.size(), nTick, pos, id1, id2);
				collisions.push_back(newCollision);

			}

		}

	}

	void World::print (int id, int x, int y) {

		sf::VideoMode videoMode(x,y);

		sf::RenderWindow window(videoMode, "Ruta de elemento");

		float a = (x) * -0.5f;
		float b = (y) * -0.5f;
		float c = (x) * 1.0f;
		float d = (y) * 1.0f;
 
		sf::View view(sf::FloatRect(a, b, c, d));
		
		window.setView(view);

		window.setVerticalSyncEnabled(false);

		vector<Pos> positionsTarget = positions[id]; 

		vector<sf::Vertex> lines;

		vector<sf::Vector2f> points;

		cout << positionsTarget[0].getX() << "  " << positionsTarget[0].getY() << endl;

		for (size_t i = 0; i < positionsTarget.size() - 1; ++i) {

				float x1 = positionsTarget[i].getX();
				float y1 = -positionsTarget[i].getY();

				points.push_back(sf::Vector2f(x1, y1));

		}

		sf::VertexArray vertexArray (sf::Points, points.size());

		for (size_t i = 0; i < points.size(); i++){
			vertexArray[i].position = points[i];
			vertexArray[i].color = sf::Color::Magenta;
		}

		

		cout << lines.size() << endl;

		while (window.isOpen()) {

			sf::Event event;

			while (window.pollEvent(event)) {

				if (event.type == sf::Event::Closed)
					window.close();

			}

			window.clear(sf::Color::Black);


			sf::Vertex line1[] = {
				sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Color::White),
				sf::Vertex(sf::Vector2f(c, 0.0f), sf::Color::White)
			};

			window.draw(line1,2,sf::Lines);

			sf::Vertex line2[] = {
				sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Color::White),
				sf::Vertex(sf::Vector2f(-c, 0.0f), sf::Color::White)
			};

			window.draw(line2,2,sf::Lines);

			sf::Vertex line3[] = {
				sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Color::White),
				sf::Vertex(sf::Vector2f(0.0f, y), sf::Color::White)
			};

			window.draw(line3,2,sf::Lines);

			sf::Vertex line4[] = {
				sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Color::White),
				sf::Vertex(sf::Vector2f(0.0f, -y), sf::Color::White)
			};

			window.draw(line4,2,sf::Lines);

			window.draw(vertexArray);

			sf::CircleShape shape1 (3.0f);
			shape1.setFillColor(sf::Color::Red);
			shape1.setPosition(positionsTarget[0].getX(), -positionsTarget[0].getY());
			window.draw(shape1);

			sf::CircleShape shape2 (3.0f);
			shape2.setFillColor(sf::Color::Blue);
			shape2.setPosition(positionsTarget[positionsTarget.size()].getX(), -positionsTarget[positionsTarget.size()].getY());
			window.draw(shape2);

			window.display();

		}

	}

	map<int,string> World::getIds () {

		map<int,string> res;

		for (const auto& pair : bodies) {
			int id = pair.first;

			if (isFee(id)) {
				res.insert({id, "Fee"});
			} else {
				if (isDee(id)) {
					res.insert({id, "Dee"});
				} else {
					if (isBot(id)) {
						res.insert({id, "Bot"});
					} else {
						throw runtime_error("Something happpened with id: " + to_string(id));
					}
				}
			}
		}

		return res;

	}
	
