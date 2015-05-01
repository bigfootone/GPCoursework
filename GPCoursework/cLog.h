/*
=================
cLog.h
- Header file for class definition - SPECIFICATION
- Header file for the Log class which is a child of cSprite class
=================
*/
#ifndef _CLOG_H
#define _CLOG_H
#include "cSprite.h"

class cLog : public cSprite
{
private:
	glm::vec2 logVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();		// Default render function
	void update(float deltaTime);		// Log update method
	void setLogVelocity(glm::vec2 asteroidVel);   // Sets the velocity for the log
	glm::vec2 getLogVelocity();				 // Gets the log velocity
	void renderCollisionBox();				// Use this function to show the collision box
};
#endif