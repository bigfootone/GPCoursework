/*
==========================================================================
cSoundMgr.h
==========================================================================
*/

#ifndef _SOUNDMGR_H
#define _SOUNDMGR_H

// OpenGL Headers
#include "GameConstants.h"
#include "cSound.h"


using namespace std;

class cSoundMgr
{
private:
	static cSoundMgr* pInstance;
	ALCcontext *m_OALContext;
	ALCdevice *m_OALDevice;

protected:
	cSoundMgr();
	~cSoundMgr();
	map <LPCSTR, cSound*> gameSnds;
	void createContext();

public:
	void add(LPCSTR sndName, LPCSTR fileName);
	cSound* getSnd(LPCSTR sndName);
	void deleteSnd();
	static cSoundMgr* getInstance();
};
#endif