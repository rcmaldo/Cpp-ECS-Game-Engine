/*
 * main.cpp
 *
 *  Created on: 16 Feb 2017
 *      Author: rcmal
 */

//Testmain

#include <iostream>

#include "Manager.h"
#include "Entities.h"

int main(int argc, char* argv[])
{
	Manager manager;
	manager.initSDL2(800, 600);

	imageV character{"V", "V.png", 0, 0, 0, 100, 100, 0, 0, true};

	manager.addComp(character.id, SpriteComponent::COMPNUM);
	SpriteComponent* spriteV = (dynamic_cast<SpriteComponent*>(manager.getComp(character.id, SpriteComponent::COMPNUM)));

	spriteV->setRenderer(manager.gRenderer);
	spriteV->setImage(character.imgPath);

	spriteV->setAll(&(character.layer), &(character.locX), &(character.locY), &(character.w), &(character.h), &(character.gloX), &(character.gloY), &(character.vis));

	bool isRunning = true;
	while (isRunning) {
		character.gloX++;
		SDL_Delay(500);
		manager.update();
	}

	return 0;
}


