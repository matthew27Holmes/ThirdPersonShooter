#ifndef _GAME_H_
#define _GAME_H_
//=================================================================
//Basic Game Manager Class
//=================================================================

#include <windows.h>
#include <list>
#include "Effects.h"
#include "CommonStates.h"
#include "Vehicle.h"
#include <dinput.h>
#include"SpriteBatch.h"
#include"SpriteFont.h"

using std::list;
using std::unique_ptr;
using namespace DirectX;

// Forward declarations
class GameObject;
class Camera;
class TPSCamera;
class Game
{
public:

	Game(ID3D11Device* _pd3dDevice, HWND _hWnd, HINSTANCE _hInstance);
	virtual ~Game();
	bool Tick(); //tick the game state
	void Draw(ID3D11DeviceContext* _pd3dImmediateContext); //render the current game state
	bool ReadKeyboard();
	bool readMouse();

	
protected:
	wchar_t* charToWChar(char* text);

	DWORD m_playTime; //amount of time since the game started

	HWND m_hWnd;

	TPSCamera* TPS_cam; //principle camera
	Camera* m_cam;
	GameData* m_GD;
	Camera * currentCam;
	list<GameObject *> m_GameObjects; //data structure storing all GameObjects of this Game
	list<GameObject *> m_colliders;

	//required for the CMO model rendering system
	CommonStates* m_states;
	IEffectFactory* m_fxFactory;
	//keyborad input stuff
	IDirectInput8*m_pDirectInput;
	IDirectInputDevice8*m_pkeyboard;
	IDirectInputDevice8*m_pMouse;
	DIMOUSESTATE m_mouse_state;
	unsigned char m_keyboardState[256];
	unsigned char m_prevKeyboardState[256];
	unique_ptr<SpriteBatch> m_sprites;
	unique_ptr<SpriteFont> m_Font;
	GameState game_state = GameState::GS_ATTRACT;
	
};


#endif