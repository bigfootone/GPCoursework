#ifndef _FROGGAME_H
#define _FROGGAME_H

// Card game headers
#include "cLog.h"
#include "cCar.h"
#include "cFrog.h"
#include "cCar2.h"
#include "cBkGround.h"

extern vector<cTexture*> theGameTextures;
extern vector<cLog*> theLogs;
extern vector<cCar*> theCars;
extern vector<cCar2*> theCars2;
extern gameState game_state;

#endif