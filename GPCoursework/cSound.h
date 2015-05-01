/*
==========================================================================
cSound.h
==========================================================================
*/

#ifndef _SOUND_H
#define _SOUND_H

// OpenGL Headers
#include "GameConstants.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class cSound
{
private:

	char*        m_OALData;           //data for the buffer
	ALenum       m_OALFormat;         //buffer format
	ALsizei      m_OALFrequency;     //frequency
	long         m_OALBufferLen;      //bit depth
	int			 m_OALChannels;		  // Channels
	int			 m_OALSize;			  // Size
	int			 m_OALBitRate;		  // Bit Rate
	float        m_OALLength;		  // Length
	ALboolean    m_OALLoop;           //loop
	unsigned int m_OALSource;         //source
	ALuint       m_OALBuffer;         // Buffer
	ALboolean    m_OALbEAX;			  // for EAX 2.0 support
	ALboolean    m_alLoop;			  //loop

	struct FMTCHUNK {
		short format;
		short channels;
		unsigned long srate;
		unsigned long bps;
		short balign;
		short samp;
	};

	void LoadWAVInfo(ifstream &filename, string &name, unsigned int &size);

public:
	cSound();
	~cSound();

	void loadWAVFile(LPCSTR filename);
	void playAudio( ALboolean sndLoop);
	void stopAudio();
	void cleanUp();
};
#endif