/*
 * Entities.h
 *
 *  Created on: 4 Jul 2017
 *      Author: rcmal
 */

#ifndef ENTITIES_H_
#define ENTITIES_H_

#include <string>

struct imageV
{
	std::string id;
	std::string imgPath;

	int layer, locX, locY, w, h, gloX, gloY;
	bool vis;
};

#endif /* ENTITIES_H_ */
