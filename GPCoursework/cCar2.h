/*
=================
cCar2.h
- Header file for class definition - SPECIFICATION
- Header file for the Car class which is a child of cSprite class
=================
*/
#ifndef _CCAR2_H
#define _CCAR2_H
#include "cSprite.h"

class cCar2 : public cSprite
{
private:
	glm::vec2 carVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();		// Default render function
	void update(float deltaTime);		// Car update method
	void setCarVelocity(glm::vec2 carVel);   // Sets the velocity for the car
	glm::vec2 getCarVelocity();				 // Gets the car velocity
	void renderCollisionBox();				// Use this function to show the collision box
};
#endif