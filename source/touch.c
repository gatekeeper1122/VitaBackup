/*
		
		Taken from VitaComix by Arkanite.
		A manga/comic book reader for the Playstation Vita
		
		File: touch.c
		
*/
#include <malloc.h>

#include "touch.h"

#define lerp(value, from_max, to_max) ((((value * 10) * (to_max * 10)) / (from_max * 10)) / 10)

typedef struct 
{
	SceInt posX;
	SceInt posY;
	SceInt held;
	SceInt pressed;
	SceInt pressedPrev;
	SceInt released;
	SceInt releasedPrev;
} touchStateData;

touchStateData* touchState;

SceInt touchInit(SceVoid) 
{
	sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, 1);
	
	touchState = malloc(sizeof(touchStateData));
	touchState->posX = 0;
	touchState->posY = 0;
	touchState->held = 0;
	touchState->pressed = 0;
	touchState->pressedPrev = 0;
	touchState->released = 0;
	touchState->releasedPrev = 0;
	
	return 1;
}

SceInt Touch_GetX(SceVoid) 
{
	return touchState->posX;
}

SceInt Touch_GetY(SceVoid) 
{
	return touchState->posY;
}

SceInt Touch_CheckPressed(SceVoid) 
{
	return touchState->pressed;
}

SceInt Touch_CheckReleased(SceVoid) 
{
	return touchState->released;
}

SceInt Touch_CheckHeld(SceVoid) 
{
	return touchState->held;
}
	
SceVoid Touch_Update(SceVoid) 
{
	sceTouchPeek(SCE_TOUCH_PORT_FRONT, &touch, 1);
	
	if (touch.reportNum > 0) 
	{
		touchState->held = 1;
		touchState->posX = (lerp(touch.report[0].x, 1919, 960));
		touchState->posY = (lerp(touch.report[0].y, 1087, 544));
		touchState->released = 0;
		touchState->releasedPrev = 0;
		if (touchState->pressedPrev == 0) 
		{
			touchState->pressedPrev = 1;
			touchState->pressed = 1;
		}
		else 
			touchState->pressed = 0;
	}
	else 
	{
		touchState->held = 0;
		touchState->pressed = 0;
		touchState->pressedPrev = 0;
		if (touchState->releasedPrev == 0) 
		{
			touchState->releasedPrev = 1;
			touchState->released = 1;
		}
		else 
			touchState->released = 0;
	}
}