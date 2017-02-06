#include "Bullet.h"
#include "GameData.h"

#include <iostream>


Bullet::Bullet(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF) :CMOGO( _fileName, _pd3dDevice, _EF)
{
	m_alive = false;
	m_lifeLeft = 0.0f;
	m_fudge = Matrix::Identity;
	m_scale = Vector3(0.01f, 0.01f, 0.01f);
	m_radius = 1.0f;
	collision_object = Collison::BULLET;
}

Bullet::~Bullet()
{

}

void Bullet::Tick(GameData* _GD)
{
	if (m_alive)
	{ 
		m_lifeLeft -= _GD->m_dt;
		if (m_lifeLeft <= 0.0f)
		{
			m_alive = false;
			return;
		}

		float speed = 20.0f;

		m_pos -= speed * _GD->m_dt * m_dir;
	
		Matrix scaleMat = Matrix::CreateScale(m_scale);
		Matrix rotTransMat = Matrix::CreateWorld(m_pos, m_dir, m_up);
		m_worldMat = m_fudge*scaleMat*rotTransMat;
	}
}

void Bullet::Draw(ID3D11DeviceContext* _pd3dImmediateContext, CommonStates* _states, Camera* _cam)
{
	if (m_alive)
	{
		CMOGO::Draw(_pd3dImmediateContext, _states, _cam);
	}
}


void Bullet::Spawn(float _life, Vector3 _pos, Vector3 _dir,Vector3 _up)
{
	m_alive = true;
	m_lifeLeft = _life;
	m_pos = _pos;
	m_dir = _dir;
	m_up = _up;
	
}
