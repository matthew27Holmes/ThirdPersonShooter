#include"EnemyManager.h"
#include <time.h>
EnemyManager::EnemyManager(int _numEnemies, string _enemyFileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, string _EnemyBullet, int _numBeulets)
{
	for (int i = 0; i < _numEnemies; i++)
	{
		m_Enemies.push_back(new Enemy(_enemyFileName, _pd3dDevice, _EF, _EnemyBullet, _numBeulets));
	}
	collision_object = Collison::ENENYMANGER;
	//srand(time(NULL));
}
EnemyManager::~EnemyManager()
{
}
void EnemyManager::Tick(GameData* _GD)
{
	srand(time(NULL));
	float spawnNumber;
	for (list<Enemy *>::iterator it = m_Enemies.begin(); it != m_Enemies.end(); it++)
	{
		spawnNumber = (float)rand() / (float)RAND_MAX;
		if (spawnNumber < 0.2*_GD->m_dt)
		{
			if (!(*it)->isAlive())
			{
				Vector3 EnemyUp = Vector3::Up;
				Vector3 EnemyPos = Vector3::Transform(Vector3((rand() % 50 + 0) - 25, 0.0f, (rand() % 50 + 0) - 25), m_fudge.Invert()* m_worldMat);
				EnemyUp = Vector3::Transform(EnemyUp, m_worldMat) - m_pos;

				(*it)->Spawn(EnemyPos, EnemyUp);
				break;
			}
		}
	}
	for (list<Enemy *>::iterator it = m_Enemies.begin(); it != m_Enemies.end(); it++)
	{
		if ((*it)->isAlive())
		{
			(*it)->Tick(_GD);
		}
	}
}
void EnemyManager::Draw(ID3D11DeviceContext* _pd3dImmediateContext, CommonStates* _states, Camera* _cam)
{
	for (list<Enemy *>::iterator it = m_Enemies.begin(); it != m_Enemies.end(); it++)
	{
		(*it)->Draw(_pd3dImmediateContext, _states, _cam);
	}
	
}
list<Enemy*> EnemyManager::getEnemy()
{
	return m_Enemies;
}