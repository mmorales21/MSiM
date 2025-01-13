#include <iostream>
#include "elements/World.h"
#include "MSiM.h"

using namespace std;

int main() {
	
	cout << "Running tests for MSiM..." << endl;

	MSiM msim;

	float norte = b2_pi / 2;
	float sur = -norte;
	float este = 0;
	float oeste = b2_pi;

	msim.showWorlds();

	int idWorld1 = 3;

	World* world1 = msim.loadWorld(idWorld1);

	int idWorld2 = msim.createWorld("Pruebas");

	World* world2 = msim.loadWorld(idWorld2);

	

	int box1 = world2->addDee(5.0f, 5.0f, Pos(25.0f, 25.0f), sur, Presets(0.5f, 0.5f, 0.5f));

	int box2 = world2->addDee(5.0f, 5.0f, Pos(-25.0f, -25.0f), norte, Presets(0.5f, 0.5f, 0.5f));

	int box3 = world2->addDee(5.0f, 5.0f, Pos(125.0f, 25.0f), sur, Presets(0.5f, 0.5f, 0.5f));

	int box4 = world2->addDee(5.0f, 5.0f, Pos(-125.0f, -25.0f), norte, Presets(0.5f, 0.5f, 0.5f));

	int box5 = world2->addDee(5.0f, 5.0f, Pos(225.0f, 25.0f), sur, Presets(0.5f, 0.5f, 0.5f));

	int box6 = world2->addDee(5.0f, 5.0f, Pos(-225.0f, -25.0f), norte, Presets(0.5f, 0.5f, 0.5f));


	int bot1 = world2->addBot(5.0f, Pos(50.0f, 50.0f), norte, Presets(0.5f, 0.5f, 0.5f));

	int bot2 = world2->addBot(5.0f, Pos(-50.0f, -50.0f), norte, Presets(0.5f, 0.5f, 0.5f));

	int bot3 = world2->addBot(5.0f, Pos(150.0f, 50.0f), norte, Presets(0.5f, 0.5f, 0.5f));

	int bot4 = world2->addBot(5.0f, Pos(-150.0f, -50.0f), norte, Presets(0.5f, 0.5f, 0.5f));

	int bot5 = world2->addBot(5.0f, Pos(250.0f, 50.0f), norte, Presets(0.5f, 0.5f, 0.5f));

	int bot6 = world2->addBot(5.0f, Pos(-250.0f, -50.0f), norte, Presets(0.5f, 0.5f, 0.5f));


	map<int, string> ids1 = world1->getIds();

	cout << endl << "Elementos del entorno de simulación id (" << idWorld1 << "):" << endl;

	for (auto iter = ids1.begin(); iter != ids1.end(); iter++){
		cout << "	- Id: " << iter->first << "  (" << iter->second << ")" << endl;
	}

	map<int, string> ids2 = world2->getIds();

	cout << endl << "Elementos del entorno de simulación id (" << idWorld2 << "):" << endl;

	for (auto iter = ids2.begin(); iter != ids2.end(); iter++){
		cout << "	- Id: " << iter->first << "  (" << iter->second << ")" << endl;
	}
	

	msim.eraseWorld(idWorld2);


/*

	int floor = world->addFee(100.0f, 5.0f, Pos (0.0f, -10.0f), oeste);

	int leftWall = world->addFee(5.0f, 100.0f, Pos(-95.0f, 95.0f), oeste);

	int rightWall = world->addFee(5.0f, 100.0f, Pos(95.0f, 95.0f), oeste);

	int top = world->addFee(100.0f, 5.0f, Pos (0.0f, 190.0f), oeste);


	int box1 = world->addDee(5.0f, 5.0f, Pos(25.0f, 25.0f), sur, Presets(0.5f, 0.5f, 0.5f));

	int box2 = world->addDee(5.0f, 5.0f, Pos(-25.0f, -25.0f), norte, Presets(0.5f, 0.5f, 0.5f));


	int bot1 = world->addBot(5.0f, Pos(50.0f, 50.0f), norte, Presets(0.5f, 0.5f, 0.5f));

	int bot2 = world->addBot(5.0f, Pos(-50.0f, -50.0f), norte, Presets(0.5f, 0.5f, 0.5f));


	// Probamos que se ha poblado el mundo de manera correcta

	cout << "Probamos si se ha poblado el mundo de manera correcta" << endl << endl;

	Fee* fl = world->getFee(floor);

	cout << "Fee con id(" << floor << "), Pos (0, -10) y ángulo " << oeste 
		 << " se ha guardado como:" <<endl;
	cout << "Fee con id(" << fl->getId() << "), Pos (" <<fl->getPos().getX() << ", " 
		 << fl->getPos().getY() << ") y ángulo " << fl->getAngle() << endl;

	Fee* lW = world->getFee(leftWall);

	cout << "Fee con id(" << leftWall << "), Pos (-95, 95) y ángulo " << oeste 
		 << " se ha guardado como:" <<endl;
	cout << "Fee con id(" << lW->getId() << "), Pos (" <<lW->getPos().getX() << ", " 
		 << lW->getPos().getY() << ") y ángulo " << lW->getAngle() << endl;

	Fee* rW = world->getFee(rightWall);

	cout << "Fee con id(" << rightWall << "), Pos (95, 95) y ángulo " << oeste 
		 << " se ha guardado como:" <<endl;
	cout << "Fee con id(" << rW->getId() << "), Pos (" <<rW->getPos().getX() << ", " 
		 << rW->getPos().getY() << ") y ángulo " << rW->getAngle() << endl;

	Fee* tp = world->getFee(top);

	cout << "Fee con id(" << top << "), Pos (0, 190) y ángulo " << oeste 
		 << " se ha guardado como:" <<endl;
	cout << "Fee con id(" << tp->getId() << "), Pos (" <<tp->getPos().getX() << ", " 
		 << tp->getPos().getY() << ") y ángulo " << tp->getAngle() << endl << endl;


	Dee* bx1 = world->getDee(box1);

	cout << "Dee con id(" << box1 << "), Pos (25, 25) y ángulo " << norte 
		 << " se ha guardado como:" <<endl;
	cout << "Dee con id(" << bx1->getId() << "), Pos (" <<bx1->getPos().getX() << ", " 
		 << bx1->getPos().getY() << ") y ángulo " << bx1->getAngle() << endl;

	Dee* bx2 = world->getDee(box2);

	cout << "Dee con id(" << box2 << "), Pos (-25, -25) y ángulo " << norte
		 << " se ha guardado como:" <<endl;
	cout << "Dee con id(" << bx2->getId() << "), Pos (" <<bx2->getPos().getX() << ", " 
		 << bx2->getPos().getY() << ") y ángulo " << bx2->getAngle() << endl << endl;


	Bot* bt1 = world->getBot(bot1);

	cout << "Bot con id(" << bot1 << "), Pos (50, 50) y ángulo " << norte 
		 << " se ha guardado como:" << endl;
	cout << "Bot con id(" << bt1->getId() << "), Pos (" <<bt1->getPos().getX() << ", " 
		 << bt1->getPos().getY() << ") y ángulo " << bt1->getAngle() << endl;

	Bot* bt2 = world->getBot(bot2);

	cout << "Bot con id(" << bot2 << "), Pos (-50, -50) y ángulo " << sur 
		 << " se ha guardado como:" <<endl;
	cout << "Bot con id(" << bt2->getId() << "), Pos (" <<bt2->getPos().getX() << ", " 
		 << bt2->getPos().getY() << ") y ángulo " << bt2->getAngle() << endl;

	cout << endl << endl << endl << endl;

	cout << "Ahora vamos a imprimir un movimiento de -5 en la rueda izquierda y -5 en la rueda derecha a bot1" << endl;

	world->setWheels(bot1, -5.0f, -5.0f);

	cout << endl << "Ya lo hemos ejecutado, comprobamos sus atributos" << endl;

	cout << bot1 << " tiene movimiento de " << world->getWheel(bot1, 0) << " en su rueda izquierda" 
		 << " y de " << world->getWheel(bot1, 1) << " en su rueda derecha" << endl;

	cout << endl << "Ahora hacemos que avance (60*10) + 1 = 601 ciclos el bot1. Entonces le pediremos su posición." << endl;
	cout << "Debería de encontrarse en el (50, 0)" << endl;

	for (int i = 0; i < 601; i++){

		world->tick();
		
	}

	vector<Collision> collisions = world->getCollisions();

	cout << "Tamaño del vector de colisiones: " << collisions.size() << endl;
	cout << world->getPos(bot1)->getX() << ", " << world->getPos(bot1)->getY() << endl;

	if (collisions.size() > 0) {

		cout << "BodyA: " << collisions[0].getId1() << " y BodyB: " << collisions[0].getId2() << endl; 

	}

	map<int, string> ids = world->getIds();

	cout << endl << "Elementos del entorno de simulación:" << endl;

	for (auto iter = ids.begin(); iter != ids.end(); iter++){
		cout << "	- Id: " << iter->first << "  (" << iter->second << ")" << endl;
	}

	//world->print(bot1, 400, 400);

	world->setWheels(bot2, 5.0f, 4.9f);

	for(int i = 0; i < 1000; i++){
		world->tick();
	}

	world->setWheels(bot2, -2.0f, -1.7f);

	for(int i = 0; i < 1000; i++){
		world->tick();
	}

	world->setWheels(bot2, 8.0f, 8.2f);

	for(int i = 0; i < 1000; i++){
		world->tick();
	}

	world->setWheels(bot2, -4.0f, 4.1f);

	for(int i = 0; i < 1000; i++){
		world->tick();
	}

*/
	// world->print(bot2, 400, 400);

/*

	cout << world->getPos(bot1)->getX() << ", " << world->getPos(bot1)->getY() << endl;

	cout << endl << "Si ahora estamos en el (50,0), nos faltarán 95 metros para llegar a " <<
	"colisionar con el elemento floor" << endl;
	cout << "95 metros a 5 metros segundo y 60 Hz, suponen 1140 ciclos. " << endl;
	cout << "Los ejecutamos hasta 1139, comprobammos las colisiones y volvemos a comprobar pasados 1141" << endl;

	for (int i = 0; i < 1139; i++){
		world->tick();
	}

	vector<Collision> collisions = world->getCollisions();

	cout << "Tamaño del vector de colisiones: " << collisions.size() << endl;
	cout << world->getPos(bot1)->getX() << ", " << world->getPos(bot1)->getY() << endl;

	for (int i = 0; i < 65; i++){
		world->tick();
	}



	collisions = world->getCollisions();
	cout << world->getPos(bot1)->getX() << ", " << world->getPos(bot1)->getY() << endl;

	cout << "Tamaño del vector de colisiones: " << collisions.size() << endl;
*/















//	msim.eraseWorld(idWorld);































/*
	int fee1 = world.addFee (5.0f, 200.0f, Pos(0.0f,  0.0f), 0.0f);

	cout << fee1 << endl;

	int dee1 = world.addDee (2.0f, 2.0f, Pos(20.0f, 20.0f), 2.0f, Presets(1.0f, 1.0f, 1.0f));

	cout << dee1 << endl;

	int bot1 = world.addBot(1.0f, Pos(200.0f, 150.0f), 1.0f, Presets(1.0f, 1.0f, 1.0f));

	cout << bot1 << endl;

	world.setWheels(bot1, -400.0f, -400.0f);

	for (int i = 0; i < 200; i++) {

		Pos* pos = world.getPos(bot1);
		cout << "Tick(" << i << ") 	Pos(" << pos->getX() << ", " << pos->getY() << ")" << endl;

		world.tick();

	}
/*
	for (int i = 0; i < 13500000; i++){

		world.tick();
	
	}

	world.setWheels(bot1, -200.0f, -200.720f);

	for (int i = 0; i < 13500000; i++){

		world.tick();
	
	}
*/
/*
	for (int i = 0; i < 10000; i++){

		world.tick();
	
	}

	world.setWheels (bot1, 200.0f, 150.0f);

	for (int i = 0; i < 5000; i++){

		world.tick();

	}

	world.setWheels (bot1, 280.0f, -800.0f);

	for (int i = 0; i < 5000; i++){

		world.tick();

	}

	world.setWheels (bot1, 280.0f, -100.0f);

	for (int i = 0; i < 5000; i++){

		world.tick();

	}

	world.setWheels (bot1, 5000.0f, 8900.0f);

	for (int i = 0; i < 2500000; i++){

		world.tick();

	}

	world.setWheels (bot1, -890.0f, -890.0f);

	for (int i = 0; i < 20; i++){

		world.tick();

	}
*/
/*	cout << "Llega"<<endl;

	world.print(bot1, 1920, 1024);

	world.tick();


	MSiM sim;

	sim.showWorlds();

	//sim.eraseWorld(2);

	//sim.insertWorld("/home/paco/Prueba.txt");

	World* world2 = sim.loadWorld(2);

	//sim.saveWorld(world2, "Juanito2");

	sim.showWorlds();

*/
	cout << "Test completed!" << endl;
	return 0;

}