/*
 * Component.h
 *
 *  Created on: 30 Oct 2017
 *      Author: rcmal
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>

#define _COMP_TOTAL 1
#define _IMAGE 0

class Component
{
private:
	bool active;
	std::string id;
	std::string log;

protected:
	void writeLog(std::string str) { log += str + '\n'; }

public:
	Component(std::string name) {
		active = true;
		id = name;
		log = id + "'s log:\n";
	}

	virtual ~Component() {}

	void activate() { active = true; }
	void deactivate() { active = false; }

	std::string getId() { return id; }
	bool operator==(const Component& other) const {
		return id == other.id;
	}

	std::string getLog() { return log; }

	virtual int getNum() const = 0;
	virtual void update() = 0;

};

class SpriteComponent : public Component
{
private:
	int *layer;

	int *_x, *_y, *_w, *_h, *_refX, *_refY;
	bool *visible;

	SDL_Renderer* renderer;
	SDL_Texture* image;

public:
	static const int COMPNUM = _IMAGE;

	SpriteComponent(std::string name);

	~SpriteComponent();

	void setRenderer(SDL_Renderer* ptr);

	bool setImage(std::string path);

	void setAll(int* l, int* x, int* y, int* w, int* h, int* rx, int* ry, bool* v);

	void setLayer(int *l);
	void setX(int* x);
	void setY(int* y);
	void setWidth(int* w);
	void setHeight(int* h);
	void setRefX(int* rx);
	void setRefY(int* ry);
	void setVisibility(bool *v);

	int getLayer() const;
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	int getRefX() const;
	int getRefY() const;
	bool getVisibility() const;

	void clean();

	int getNum() const;

	void update();
};

#endif /* COMPONENT_H_ */
