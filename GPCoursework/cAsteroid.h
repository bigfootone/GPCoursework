/*
=================
cAsteroid.h
- Header file for class definition - SPECIFICATION
- Header file for the Rocket class which is a child of cSprite class
=================
*/
#ifndef _CASTEROID_H
#define _CASTEROID_H
#include "cSprite.h"

class cAsteroid : public cSprite
{
private:
	glm::vec2 asteroidVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();		// Default render function
	void update(float deltaTime);		// Rocket update method
	void setAsteroidVelocity(glm::vec2 asteroidVel);   // Sets the velocity for the rocket
	glm::vec2 getAsteroidVelocity();				 // Gets the rocket velocity
	void renderCollisionBox();				// Use this function to show the collision box
};
#endif