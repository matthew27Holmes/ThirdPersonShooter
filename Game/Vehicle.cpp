#include "Vehicle.h"
#include"GameData.h"
#include <dinput.h>

Vehicle::Vehicle(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF) : CMOGO(_fileName,_pd3dDevice,_EF)
{
	//any special set up for Vehicle goes here
	m_pitch = 0; //XM_PI*2.0;
	m_yaw = 0;
	m_roll = 0.0f;
	m_scale = Vector3(0.01f, 0.01f, 0.01f);
	m_fudge;
	collision_object = Collison::PLAYER;
	
}

Vehicle::~Vehicle()
{
	//tidy up anything I've created
}



void Vehicle::Tick(GameData*_GD)//, unsigned char* _keyboardState)
{
	//Keyboard control of the Vehicle
	float rotSpeed = 10.0f*_GD->m_dt;
	float speed = 10.0f*_GD->m_dt ;
	float newPosX = speed*sinf(m_yaw);
	float newPosY = speed*-sinf(m_pitch);
	float newPosZ = speed* cosf(m_yaw)*cosf(m_pitch);
	

	switch (_GD->m_GS)
	{

	case GS_PLAY_TPS_CAM :
		

		if (_GD->m_keyboardState[DIK_A] & 0x80)
		{
			m_yaw += rotSpeed;
		}
		if (_GD->m_keyboardState[DIK_D] & 0x80)
		{
			m_yaw -= rotSpeed;
		}
		if (_GD->m_keyboardState[DIK_UPARROW] & 0x80)
		{
			m_pos += Vector3(-newPosX, -newPosY, -newPosZ);
		}
		if (_GD->m_keyboardState[DIK_DOWNARROW] & 0x80)
		{
			m_pos += Vector3(newPosX, newPosY, newPosZ);
		}
		if (_GD->m_keyboardState[DIK_LEFTARROW] & 0x80)
		{
			m_pos -= Vector3(speed, 0.0f, 0.0f);
		}
		if (_GD->m_keyboardState[DIK_RIGHTARROW] & 0x80)
		{
			m_pos += Vector3(speed, 0.0f, 0.0f);
		}
		if (_GD->m_keyboardState[DIK_Q] & 0x80)
		{
			m_pos += Vector3(0.0f, speed, 0.0f);
		}
		if (_GD->m_keyboardState[DIK_E] & 0x80)
		{
			m_pos -= Vector3(0.0f, speed, 0.0f);
		}
		break;
	case GS_PLAY_MAIN_CAM:
		//MOUSE CONTROL SCHEME HERE
		m_pos.x += 0.01f*_GD->m_mouseState->lX;
		m_pos.z += 0.01f*_GD->m_mouseState->lY;
		break;
	}

	//apply my base behaviour
	CMOGO::Tick(_GD);// , _keyboardState);
	m_worldMat = m_fudge*m_worldMat;
}

void Vehicle::Draw(ID3D11DeviceContext* _pd3dImmediateContext, CommonStates* _states, Camera* _cam)
{
	//I'm still a CMOGO so that's what draws me
	CMOGO::Draw(_pd3dImmediateContext, _states, _cam);
}