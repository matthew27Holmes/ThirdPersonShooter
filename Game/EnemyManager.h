#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_
#include "gameobject.h"
#include <list>
#include "Model.h"
#include"Enemy.h"
#include <string>
#include <time.h>

using namespace std;
using namespace DirectX;

class Enemy;

class EnemyManager : public GameObject
{
public:
	EnemyManager(int _numEnemies, string _enemyFileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, string _EnemyBullet, int _numBeulets);
	~EnemyManager();

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(ID3D11DeviceContext* _pd3dImmediateContext, CommonStates* _states, Camera* _cam) override;
	list<Enemy*> getEnemy();

protected:
	list<Enemy*> m_Enemies;
};

#endif