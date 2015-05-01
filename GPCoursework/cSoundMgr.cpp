/*
==================================================================================
cSoundMgr.cpp
==================================================================================
*/

#include "cSoundMgr.h"

cSoundMgr* cSoundMgr::pInstance = NULL;

/*
=================================================================================
Constructor
=================================================================================
*/
cSoundMgr::cSoundMgr()
{
	createContext();
}

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cSoundMgr* cSoundMgr::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cSoundMgr();
	}
	return cSoundMgr::pInstance;
}

void cSoundMgr::createContext()
{
	m_OALDevice = alcOpenDevice(NULL);
	if (m_OALDevice)
	{
		//Create a context
		m_OALContext = alcCreateContext(m_OALDevice, NULL);

		//Set active context
		alcMakeContextCurrent(m_OALContext);
	}
}

void cSoundMgr::add(LPCSTR sndName, LPCSTR fileName)
{
	if (!getSnd(sndName))
	{
		cSound * newSnd = new cSound();
		newSnd->loadWAVFile(fileName);
		gameSnds.insert(make_pair(sndName, newSnd));
	}
}

cSound* cSoundMgr::getSnd(LPCSTR sndName)
{
	map<LPCSTR, cSound*>::iterator snd = gameSnds.find(sndName);
	if (snd != gameSnds.end())
	{
		return snd->second;
	}
	else
	{
		return NULL;
	}
}

void cSoundMgr::deleteSnd()
{
	for (map<LPCSTR, cSound*>::iterator snd = gameSnds.begin(); snd != gameSnds.end(); ++snd)
	{
		delete snd->second;
	}
}


cSoundMgr::~cSoundMgr()
{
	m_OALContext = alcGetCurrentContext();

	//Get device for active context
	m_OALDevice = alcGetContextsDevice(m_OALContext);

	//Release context(s)
	alcDestroyContext(m_OALContext);

	//Close device
	alcCloseDevice(m_OALDevice);

}
