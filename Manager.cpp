/*
 * Manager.cpp
 *
 *  Created on: 30 Oct 2017
 *      Author: rcmal
 */

#include "Manager.h"
#include "Component.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

Manager::Manager() {
	activeSDL2 = false;
	WindowWidth = 0; WindowHeight = 0;
	gWindow = nullptr;
	gScreenSurface = nullptr;
	gRenderer = nullptr;

	log = "";
}
Manager::Manager(int width, int height) {
	activeSDL2 = false;
	WindowWidth = width; WindowHeight = height;
	gWindow = nullptr;
	gScreenSurface = nullptr;
	gRenderer = nullptr;

	log = "";
}
Manager::~Manager() {
	for (int i = 0; i < _COMP_TOTAL; i++) {
		for (auto it = components[i].begin(); it != components[i].end(); it++) {
			delete *it;
		}
	}
	if (activeSDL2) {
		cleanSDL2();
	}
}

std::string Manager::getLog() { return log; }

bool Manager::initSDL2(int width, int height) {
	activeSDL2 = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		log += "SDL initialize fail. SDL Error: ";
		log += SDL_GetError();
		log += '\n';
		return false;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		log += "Warning: Linear texture filtering not enabled.\n";
	}

	WindowWidth = width;
	WindowHeight = height;
	//Create window
	gWindow = SDL_CreateWindow("ECS Engine Test", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WindowWidth,
			WindowHeight,
			SDL_WINDOW_SHOWN);
	if (gWindow == nullptr) {
		log += "Renderer could not be created. SDL Error: ";
		log += SDL_GetError();
		log += '\n';
		return false;
	}
	//Vsynced renderer for window
	gRenderer = SDL_CreateRenderer(gWindow, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == nullptr) {
		return false;
	}
	//Initialize renderer color
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Initialize PNG loading
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		log += "SDL_image could not initialize. SDL Error: ";
		log += SDL_GetError();
		log += '\n';
		return false;
	}

	//end
	return true;
}

void Manager::cleanSDL2() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = nullptr;
	gWindow = nullptr;

	IMG_Quit();
	SDL_Quit();
}

bool Manager::addComp(std::string name, int type) {
	switch (type) {
	case SpriteComponent::COMPNUM:
		components[type].push_back(new SpriteComponent(name));
		return true;
	default:
		return false;
	}
}

Component* Manager::getComp(std::string name, int type) {
	auto it = std::find_if(components[type].begin(),
							components[type].end(),
							[&name](Component* comp) { return comp->getId() == name; } );
	return *it;
} //MAYBE FIX THIS? or not

void Manager::update() {

	//For sprite comps
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );

	//All comps
	for (int i = 0; i < _COMP_TOTAL; i++) {
		for (auto it = components[i].begin(); it != components[i].end(); it++) {
			(*it)->update();
		}
	}

	//Render
	SDL_RenderPresent( gRenderer );
}
