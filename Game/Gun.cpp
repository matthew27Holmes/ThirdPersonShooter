#include "Gun.h"
#include"GameData.h"
#include <dinput.h>


Gun::Gun(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, GameObject* _parent, string _bulletFileName, int _numBullets) : CMOGO(_fileName, _pd3dDevice, _EF)
{
	m_scale = Vector3(1.5f, 1.5f, 1.5f);
	m_fudge=Matrix::CreateFromYawPitchRoll(XM_PI,0.0f,0.0f)*Matrix::CreateTranslation(Vector3(0.0f,0.0f,0.0f));
	m_parent = _parent;
	m_pos = Vector3(0.0f, 150.0f, 0.0f);
	for (int i = 0; i < _numBullets; i++)
	{
		m_Bullets.push_back(new Bullet(_bulletFileName, _pd3dDevice, _EF));
	}
	collision_object = Collison::GUN;
}
Gun::~Gun()
{

}
void Gun::Tick(GameData* _GD)
{
	CMOGO::Tick(_GD);
	m_worldMat = m_fudge*m_worldMat;
	
	float rotSpeed = 10.0f*_GD->m_dt;
	float speed = 10.0f*_GD->m_dt;
	

	switch (_GD->m_GS)
	{

	case GS_PLAY_MAIN_CAM:


		if (_GD->m_keyboardState[DIK_A] & 0x80)
		{
			m_yaw += rotSpeed;
		}
		if (_GD->m_keyboardState[DIK_D] & 0x80)
		{
			m_yaw -= rotSpeed;
		}
		break;
	case GS_PLAY_TPS_CAM:
		//MOUSE CONTROL SCHEME HERE
		m_yaw += 0.01f*_GD->m_mouseState->lX;
		m_pitch += 0.01f*_GD->m_mouseState->lY;
		if (m_pitch >= 0.1*XM_PI)
		{
			m_pitch = 0.1*XM_PI;
		}
		if (m_pitch <= -0.1*XM_PI)
		{
			m_pitch = -0.1*XM_PI;
		}
		if (m_yaw >= 0.4*XM_PI)
		{
			m_yaw = 0.4*XM_PI;
		}
		if (m_yaw <= -0.4*XM_PI)
		{
			m_yaw = -0.4*XM_PI;
		}
		break;
	}
	if (m_parent)
	{
		m_worldMat = m_worldMat*m_parent->GetFudge().Invert()*m_parent->GetWorldMat();
	}
	if ((_GD->m_keyboardState[DIK_Z] & 0x80) && !(_GD->m_prevKeyboardState[DIK_Z] & 0x80))
	{
		for (list<Bullet *>::iterator it = m_Bullets.begin(); it != m_Bullets.end(); it++)
		{
			
			if ((*it)->isAlive()==false)
			{
				Vector3 bulletPos = Vector3::Zero;
				Vector3 bulletDir = Vector3::Forward;
				Vector3 bulletUp = Vector3::Up;

				bulletPos = Vector3::Transform(bulletPos, m_worldMat);
				bulletDir = Vector3::Transform(bulletDir, m_worldMat) - bulletPos;
				bulletUp = Vector3::Transform(bulletUp, m_worldMat) - bulletPos;


				bulletDir.Normalize();
				(*it)->Spawn(3.0f, bulletPos, bulletDir, bulletUp);
				break;
			}
			
		}
	}

	for (list<Bullet *>::iterator it = m_Bullets.begin(); it != m_Bullets.end(); it++)
	{
		(*it)->Tick(_GD);
	}
	
}
void Gun::Draw(ID3D11DeviceContext* _pd3dImmediateContext, CommonStates* _states, Camera* _cam)
{
	for (list<Bullet *>::iterator it = m_Bullets.begin(); it != m_Bullets.end(); it++)
	{
		(*it)->Draw(_pd3dImmediateContext, _states, _cam);
	}
	CMOGO::Draw(_pd3dImmediateContext, _states, _cam);
}
list<Bullet*> Gun::getBullets()
{
	return m_Bullets;
}