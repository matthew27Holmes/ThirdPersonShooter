#include "Game.h"
#include "gameobject.h"
#include "camera.h"
#include "TPSCamera.h";
#include "SimpleMath.h"
#include "CMOGO.h"
#include "terrain.h"
#include "Vehicle.h"
#include "Gun.h"
#include "Bullet.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "Audio.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Game::Game(ID3D11Device* _pd3dDevice, HWND _hWnd, HINSTANCE _hInstance) 
{
	//CoInitalizeEx()
	//hide the mouse pointer
	ShowCursor(false);
	m_GD = new GameData;
	m_GD->m_keyboardState = m_keyboardState;
	m_GD->m_prevKeyboardState = m_prevKeyboardState;
	m_GD->m_mouseState = &m_mouse_state;//test for mouse 

	m_pkeyboard = nullptr;
	m_pMouse = nullptr;
	m_pDirectInput = nullptr;
	//set up DirectXTK Effects system
	m_fxFactory = new EffectFactory(_pd3dDevice);

	//Tell the fxFactory to look to the correct build directory to pull stuff in from
#ifdef DEBUG
	((EffectFactory*)m_fxFactory)->SetDirectory(L"../Debug");
#else
	((EffectFactory*)m_fxFactory)->SetDirectory(L"../Release");
#endif

	// Create other render resources here
	m_states = new CommonStates(_pd3dDevice);

	//find how big my window is to correctly calculate my aspect ratio
	RECT rc;
	GetClientRect(_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	float AR = (float)width / (float)height;

	m_hWnd = _hWnd;

	//direct input stuff
	HRESULT hr = DirectInput8Create(_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL);
	hr = m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pkeyboard, NULL);
	hr = m_pkeyboard->SetDataFormat(&c_dfDIKeyboard);
	hr = m_pkeyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	hr = m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL);
	hr = m_pMouse->SetDataFormat(&c_dfDIMouse);
	hr = m_pMouse->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	//create a base camera
	m_cam = new Camera(0.25f * XM_PI, AR, 1.0f, 10000.0f, Vector3::Zero, Vector3::Up);
	m_cam->SetPos(Vector3(0.0f, 100.0f, 100.0f));
	m_GameObjects.push_back(m_cam);

	Terrain* pTerrain = new Terrain("desert fbx.cmo", _pd3dDevice, m_fxFactory,Vector3(0.0f,0.f,0.0f), XM_PI*0.5,0.0f,0.0f, Vector3::One);// add in more terrian objects

	m_GameObjects.push_back(pTerrain);

	Vehicle* pVehicle = new Vehicle("Eagle.cmo", _pd3dDevice, m_fxFactory);// add in more terrian objects
	m_GameObjects.push_back(pVehicle);

	Gun* pGun = new Gun("TankCannon.cmo", _pd3dDevice, m_fxFactory, pVehicle, "TankCannon.cmo",9);
	m_GameObjects.push_back(pGun);
	EnemyManager* pEnemyManager = new EnemyManager(50,"Eagle.cmo", _pd3dDevice, m_fxFactory, "TankCannon.cmo",1);
	m_GameObjects.push_back(pEnemyManager);

	TPS_cam = new TPSCamera(0.25f * XM_PI, AR, 1.0f, 10000.0f, pVehicle,Vector3::Up,Vector3(0.0f,20.0f,40.0f));
	m_GameObjects.push_back(TPS_cam);

	// Populate colliders list
	m_colliders.push_back(pVehicle);

	auto bullets = pGun->getBullets();
	for (auto bullet = bullets.begin(); bullet != bullets.end(); bullet++)
	{
		m_colliders.push_back((*bullet));
	}

	auto enemies = pEnemyManager->getEnemy();
	for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
	{
		m_colliders.push_back((*enemy));
	}
	
	m_colliders.push_back(pVehicle);
	m_colliders.push_back(pVehicle);


	//set stae on start up 
	m_GD->m_GS = GS_PLAY_TPS_CAM;
	currentCam = TPS_cam;
	//creat SpriteBatchStuff
	ID3D11DeviceContext*pd3dImmediateContext;
	_pd3dDevice->GetImmediateContext(&pd3dImmediateContext);
	m_sprites.reset(new SpriteBatch(pd3dImmediateContext));
	m_Font.reset(new SpriteFont(_pd3dDevice, L"italic.spritefont"));

};


Game::~Game() 
{
	//tidy up of input stuff
	if (m_pkeyboard)
	{
		m_pkeyboard->Unacquire();
		m_pkeyboard->Release();
	}
	if (m_pDirectInput) m_pDirectInput->Release();
	//get rid of the game objects here
	for (list<GameObject *>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		delete (*it);
	}
	m_GameObjects.clear();
	delete m_GD;
};

bool Game::ReadKeyboard()
{
	//copy over keyboard state
	memcpy(m_prevKeyboardState, m_keyboardState, sizeof(unsigned char) * 256);
	//clear out previous state 
	ZeroMemory(&m_keyboardState, sizeof(m_keyboardState));
	//read the keycoard device
	HRESULT hr = m_pkeyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(hr))
	{
		//if the keyboard lost focus or was not acquired then tey to get control back 
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			m_pkeyboard->Acquire();
		}
		else
		{
			return false;
		}
	}
	return true;
}
bool Game::readMouse()
{
	//clear out previous state 
	ZeroMemory(&m_mouse_state, sizeof(DIMOUSESTATE));
	//read the mouse device
	HRESULT hr = m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouse_state);
	if (FAILED(hr))
	{
		//if the keyboard lost focus or was not acquired then tey to get control back 
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			m_pMouse->Acquire();
		}
		else
		{
			return false;
		}
	}
	return true;
}

wchar_t * Game::charToWChar(char * text)
{
	size_t size = strlen(text) + 1;
	static wchar_t* wa = NULL;
	if (wa)
	{
		delete[] wa;
		wa = NULL;
	}
	wa = new wchar_t[size];
		mbstowcs_s(nullptr, wa, size, text, size);
	return wa;
}
bool Game::Tick() 
{
	readMouse();
	ReadKeyboard();
	if (m_keyboardState[DIK_ESCAPE] & 0x80)
	{
		return false;
	}

	if ((m_keyboardState[DIK_SPACE] & 0x80) &&
		!(m_prevKeyboardState[DIK_SPACE] & 0x80))
	{
		if (m_GD->m_GS == GS_PLAY_MAIN_CAM)
		{
			m_GD->m_GS = GS_PLAY_TPS_CAM;
			currentCam = TPS_cam;
		}
		else
		{
			m_GD->m_GS = GS_PLAY_MAIN_CAM;
			currentCam = m_cam;
		}
	}


	//calculate frame time-step dt for passing down to game objects
	DWORD currentTime = GetTickCount();
	float  dt = min((float)(currentTime - m_playTime) / 1000.0f, 0.1f);
	m_playTime = currentTime;
	//update all objects

	// Check collisions
	for (auto iter = m_colliders.begin(); iter != m_colliders.end(); iter++)
	{
		if ((*iter)->isAlive())
		{
			for (auto iter2 = m_colliders.begin(); iter2 != m_colliders.end(); iter2++)
			{
				if ((*iter2)->isAlive() &&
					(*iter)->checkCollision((*iter2)))
				{
					//objects collided, do something
					if ((*iter)->getType() == Collison::BULLET
						&& (*iter2)->getType() == Collison::ENEMY)
					{
						(*iter)->SetAlive(false);
						(*iter2)->SetAlive(false);
					}
					if ((*iter)->getType() == Collison::ENEMYBULLET
						&& (*iter2)->getType() == Collison::PLAYER)
					{
						(*iter)->SetAlive(false);
						(*iter2)->SetAlive(false);
					}
				}
			}
		}
	}


	m_GD->m_dt = dt;
	for (list<GameObject *>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		if ((*it)->isAlive())
		{
			(*it)->Tick(m_GD);
		}
	}
	RECT window;
	GetWindowRect(m_hWnd, &window);
	SetCursorPos(0.5*(window.left + window.right), 0.5*(window.bottom + window.top));
	return true; 
};

void Game::Draw(ID3D11DeviceContext* _pd3dImmediateContext) 
{
	for (list<GameObject *>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{//draw all objects 
		(*it)->Draw(_pd3dImmediateContext, m_states, currentCam);
	}
	m_sprites->Begin();
	m_Font->DrawString(m_sprites.get(), charToWChar("TEST"), XMFLOAT2(100, 10), Colors::Yellow);
	m_sprites->End();
};