#include "Enemy.h"
#include <time.h>
Enemy::Enemy(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, string _bulletFileName, int _numBullets) :CMOGO(_fileName, _pd3dDevice, _EF)
{
	m_alive = false;
	float speed = 3.0f;
	m_scale= Vector3(0.01f, 0.01f, 0.01f);
	m_fudge = Matrix::Identity;

	srand(time(NULL));
	for (int i = 0; i < _numBullets; i++)
	{
		m_EnemyBullet.push_back(new EnemyBullet(_bulletFileName, _pd3dDevice, _EF));
	}
	collision_object = Collison::ENEMY;
}
Enemy::~Enemy()
{}
void Enemy::Tick(GameData* _GD)
{
	srand(time(NULL));
	float spawnNumber;
	if (m_alive)
	{
		auto direction = m_target;
		direction.Normalize();
		float speed = 1.0f;
		m_pos += speed  * _GD->m_dt * m_target;
		Matrix scaleMat = Matrix::CreateScale(m_scale);
		Matrix transform = Matrix::CreateWorld(m_pos, -m_target, m_up);

		m_worldMat = m_fudge*scaleMat*transform;

		if (Vector3::Distance(m_pos, m_target) < 25.0f || Vector3::Distance(m_pos, m_target) > -25.0f)
		{
			m_target = Vector3((rand() % 50 + 0) - 25, 0.0f, (rand() % 50 + 0) - 25);
		}

		spawnNumber = (float)rand() / (float)RAND_MAX;

		for (list<EnemyBullet *>::iterator it = m_EnemyBullet.begin(); it != m_EnemyBullet.end(); it++)
		{
			if (spawnNumber < 0.2)
			{
				if ((*it)->isAlive() == false)
				{
					Vector3 enemybulletPos = Vector3::Zero;
					Vector3 enemybulletDir = Vector3::Forward;
					Vector3 enemybulletUp = Vector3::Up;

					enemybulletPos = Vector3::Transform(enemybulletPos, m_worldMat);
					enemybulletDir = Vector3::Transform(enemybulletDir, m_worldMat) - enemybulletPos;
					enemybulletUp = Vector3::Transform(enemybulletUp, m_worldMat) - enemybulletPos;


					enemybulletDir.Normalize();
					(*it)->Spawn(3.0f, enemybulletPos, enemybulletDir, enemybulletUp);
					break;
				}
			}
		}
		for (list<EnemyBullet *>::iterator it = m_EnemyBullet.begin(); it != m_EnemyBullet.end(); it++)
		{
			(*it)->Tick(_GD);
		}

		
	}
}
void Enemy::Draw(ID3D11DeviceContext* _pd3dImmediateContext, CommonStates* _states, Camera* _cam)
{
	if (m_alive)
	{
		for (list<EnemyBullet *>::iterator it = m_EnemyBullet.begin(); it != m_EnemyBullet.end(); it++)
		{
			(*it)->Draw(_pd3dImmediateContext, _states, _cam);
		}
		CMOGO::Draw(_pd3dImmediateContext, _states, _cam);
	}
}
void Enemy::Spawn(Vector3 _pos, Vector3 _up)
{
	m_alive = true;
	m_pos = _pos;
	m_up = _up;
	m_target = Vector3((rand() % 50 + 0) - 25, 0.0f, (rand() % 50 + 0) - 25);
}
	