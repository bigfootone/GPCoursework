/*
=================
cFrog.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cFrog.h"

void cFrog::render()
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

void cFrog::update(float deltaTime)
{

	if (m_InputMgr->isKeyDown(VK_RIGHT))
	{
		spritePos2D.x += 20; //Move sprite on the x axis
	}
	if (m_InputMgr->isKeyDown(VK_LEFT))
	{
		spritePos2D.x -= 20;
	}
	if (m_InputMgr->isKeyDown(VK_UP))
	{
		spritePos2D.y -= 20;
	}
	if (m_InputMgr->isKeyDown(VK_DOWN))
	{
		spritePos2D.y += 20;
	}

	if (spritePos2D.y < 20)
	{
		game_state = WIN;
		m_SoundMgr->getSnd("CarEnter")->playAudio(AL_TRUE);
	}

	setBoundingRect(&boundingRect);

	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/
	for (vector<cCar*>::iterator carIterartor = theCars.begin(); carIterartor != theCars.end(); ++carIterartor)
	{
		(*carIterartor)->update(deltaTime);

			if (this->collidedWith(this->getBoundingRect(), (*carIterartor)->getBoundingRect()))
			{
				game_state = GAMEOVER;
				m_SoundMgr->getSnd("CarSplat")->playAudio(AL_TRUE);

			}
	}

	for (vector<cCar2*>::iterator car2Iterartor = theCars2.begin(); car2Iterartor != theCars2.end(); ++car2Iterartor)
	{
		(*car2Iterartor)->update(deltaTime);

		if (this->collidedWith(this->getBoundingRect(), (*car2Iterartor)->getBoundingRect()))
		{
			game_state = GAMEOVER;
			m_SoundMgr->getSnd("CarSplat")->playAudio(AL_TRUE);

		}
	}



	for (vector<cLog*>::iterator logIterartor = theLogs.begin(); logIterartor != theLogs.end(); ++logIterartor)
	{
		(*logIterartor)->update(deltaTime);
		if (this->collidedWith(this->getBoundingRect(), (*logIterartor)->getBoundingRect()))
		{
			game_state = GAMEOVER;
			m_SoundMgr->getSnd("CarSplat")->playAudio(AL_TRUE);
		}

	}



}
/*
=================================================================
Sets the velocity for the frog
=================================================================
*/
void cFrog::setFrogVelocity(glm::vec2 rocketVel)
{
	frogVelocity = rocketVel;
}
