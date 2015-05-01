/*
=================
cLog.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cLog.h"

void cLog::render()
{
	//renderCollisionBox();
	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
	glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
	glVertex2f((textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f((textureWidth / 2), (textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cLog::update(float deltaTime)
{

	spritePos2D += spriteTranslation * deltaTime;

	setBoundingRect(&boundingRect);
	
	//Resetting the sprite to the left when it leaves the window
	if (spritePos2D.x > (1024 + 128))
	{
		spritePos2D.x = -64;
	}
}
/*
=================================================================
Sets the velocity for the Log
=================================================================
*/
void cLog::setLogVelocity(glm::vec2 AsteroidVel)
{
	logVelocity = AsteroidVel;
}
/*
=================================================================
Gets the Log velocity
=================================================================
*/
glm::vec2 cLog::getLogVelocity()
{
	return logVelocity;
}
/*
==========================================================================
Use this method to show the collision box.
==========================================================================
*/
void cLog::renderCollisionBox()
{
	glPushMatrix();

	glTranslatef(boundingRect.left, boundingRect.top, 0.0f);

	glColor3f(255.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);

	glVertex2f(0, 0);
	glVertex2f((boundingRect.right - boundingRect.left), 0);
	glVertex2f((boundingRect.right - boundingRect.left), (boundingRect.bottom - boundingRect.top));
	glVertex2f(0, (boundingRect.bottom - boundingRect.top));
	glEnd();

	glPopMatrix();
}