/*
 * Manager.h
 *
 *  Created on: 11 Feb 2017
 *      Author: rcmal
 */

//NOTES:
//	NO COLOR KEYING in SpriteComponent setImage(std::string) : bool

#ifndef MANAGER_H_
#define MANAGER_H_

#include <string>
#include <vector>
#include <algorithm>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#define _COMP_TOTAL 1
#define _IMAGE 0

class Manager
{
private:
	SDL_Window* gWindow;
	SDL_Surface* gScreenSurface;

public:
	SDL_Renderer* gRenderer;

private:
	bool activeSDL2;
	int WindowWidth, WindowHeight;

	std::vector<Component*> components[_COMP_TOTAL];

	//Log
	std::string log;

public:

	std::string getLog();

	//SDL2 stuff---------------------------------------------------------------------
	bool initSDL2(int width, int height);

	void cleanSDL2();

	//Components----------------------------------------------------------------------
	bool addComp(std::string name, int type);

	Component* getComp(std::string name, int type);

	//Update-------------------------------------------------------------------------
	void update();

	//(De)Constructor-----------------------------------------------------------------
	Manager();
	Manager(int width, int height);
	~Manager();
};



#endif /* MANAGER_H_ */
