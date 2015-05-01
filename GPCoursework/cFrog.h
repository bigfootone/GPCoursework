/*
=================
cFrog.h
- Header file for class definition - SPECIFICATION
- Header file for the Frog class which is a child of cSprite class
=================
*/
#ifndef _CFROG_H
#define _CFROG_H
#include "cSprite.h"
#include "frogGame.h"

class cFrog : public cSprite
{
private:
	glm::vec2 frogVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();		// Default render function
	void update(float deltaTime);		// Frog update method
	void setFrogVelocity(glm::vec2 frogVel);   // Sets the velocity for the frog
	glm::vec2 getFrogVelocity();				 // Gets the frog velocity

};
#endif