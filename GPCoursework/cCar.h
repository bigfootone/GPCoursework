/*
=================
cCar.h
- Header file for class definition - SPECIFICATION
- Header file for the Car class which is a child of cSprite class
=================
*/
#ifndef _CCAR_H
#define _CCAR_H
#include "cSprite.h"

class cCar : public cSprite
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