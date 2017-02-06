#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_
#include "GameState.h"
#include <dinput.h>


struct GameData
{
	float m_dt;
	unsigned char* m_keyboardState;
	unsigned char* m_prevKeyboardState;
	DIMOUSESTATE* m_mouseState;  //current mouse state
	GameState m_GS;   //curent game state
}; 
#endif
