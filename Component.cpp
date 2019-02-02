/*
 * Component.cpp
 *
 *  Created on: 30 Oct 2017
 *      Author: rcmal
 */

#include "Component.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

SpriteComponent::SpriteComponent(std::string name) : Component(name) {
	layer = nullptr;
	_x = nullptr; //Size and position of frame on image
	_y = nullptr;
	_w = nullptr;
	_h = nullptr;
	_refX = nullptr; //_ref is position on global screen
	_refY = nullptr;
	visible = nullptr;
	image = nullptr;
	renderer = nullptr;
}

SpriteComponent::~SpriteComponent() { clean(); }

void SpriteComponent::setRenderer(SDL_Renderer* ptr) { renderer = ptr; }

bool SpriteComponent::setImage(std::string path) {
	if (renderer == nullptr) {
		writeLog("Renderer is not set");
		return false;
	}
	if (image != nullptr) {
		SDL_DestroyTexture(image);
		image = nullptr;
	}
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr) {
		writeLog("Unable to load image " + path + ". SDL_image Error: " + IMG_GetError());
		return false;
	}
	//Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (newTexture == nullptr) {
		writeLog("Unable to create texture from " + path + ". SDL Error: " + SDL_GetError());
	}

	SDL_FreeSurface(loadedSurface);

	image = newTexture;
	return image != nullptr;
}

void SpriteComponent::setAll(int* l, int* x, int* y, int* w, int* h, int* rx, int* ry, bool* v) {
	layer = l; _x = x; _y = y; _w = w; _h = h; _refX = rx; _refY = ry; visible = v;
}

void SpriteComponent::setLayer(int *l) { layer = l; }
void SpriteComponent::setX(int* x) { _x = x; }
void SpriteComponent::setWidth(int* w) { _w = w; }
void SpriteComponent::setY(int* y) { _y = y; }
void SpriteComponent::setHeight(int* h) { _h = h; }
void SpriteComponent::setRefX(int* rx) { _refX = rx; }
void SpriteComponent::setRefY(int* ry) { _refY = ry; }
void SpriteComponent::setVisibility(bool *v) { visible = v; }

int SpriteComponent::getLayer() const { return *layer; }
int SpriteComponent::getX() const { return *_x; }
int SpriteComponent::getY() const { return *_y; }
int SpriteComponent::getWidth() const { return *_w; }
int SpriteComponent::getHeight() const { return *_h; }
int SpriteComponent::getRefX() const { return *_refX; }
int SpriteComponent::getRefY() const { return *_refY; }
bool SpriteComponent::getVisibility() const { return visible; }

void SpriteComponent::clean() {
	if (image != nullptr) {
		SDL_DestroyTexture(image);
		image = nullptr;
	}
}

int SpriteComponent::getNum() const { return SpriteComponent::COMPNUM; }

void SpriteComponent::update() {
	if (visible) {
		//Set render space
		SDL_Rect srcRect = {*_x, *_y, *_w, *_h};
		SDL_Rect dstRect = {*_refX, *_refY, *_w, *_h};

		//Render to screen
		SDL_RenderCopy(renderer, image, &srcRect, &dstRect);
	}
}


