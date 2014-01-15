#include "Generic_GameLibrary.h"
#include <stdlib.h>

void GglInputDevice_GetKeyboardState(void)
{
	GetKeyboardState(g_inputDevice.keyState);

	return ;
}

void GglInputDevice_Mouse(int in_button, int in_state, int in_x, int in_y)
{
	g_inputDevice.mouseButton	= in_button;
	g_inputDevice.mouseState	= in_state;
	g_inputDevice.mouseX		= in_x;
	g_inputDevice.mouseY		= in_y;

	return ;
}

void GglInputDevice_ShutDownKey(void)
{
	if(GglInputDevice_KeyDown(GIK_ESCAPE))
	{
		exit(0);
	}

	return ;
}

void GglInputDevice_MouseInit(void)
{
	g_inputDevice.mouseButton	= 0x00;
	g_inputDevice.mouseState	= 0x00;
	g_inputDevice.mouseX		= -1;
	g_inputDevice.mouseX		= -1;
	
	return ;
}

void GglInputDevice_AllInitialize(void)
{
	/*GglInputDevice_CommonKeyInit();
	GglInputDevice_SpecialKeyInit();*/
	GglInputDevice_MouseInit();

	return ;
}