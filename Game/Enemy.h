#ifndef _ENEMY_H_
#define _ENEMY_H_
#include<list>
#include "CMOGO.h"
#include"EnemyBullets.h"
#include"EnemyManager.h"
#include "Bullet.h"
#include"Gun.h"
class Gun;
class Bullet;
class EnemyManager;
class Enemy : public CMOGO
{
public:
	Enemy(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF,  string _bulletFileName, int _numBullets);
	~Enemy();

	void Spawn(Vector3 _pos, Vector3 _up);

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(ID3D11DeviceContext* _pd3dImmediateContext, CommonStates* _states, Camera* _cam) override;

protected:

	Matrix m_radius;
	Vector3 m_target; //I am traveling towards THIS location
	int X,Y,Z;
	Vector3 m_up;
	list<EnemyBullet*>m_EnemyBullet;
	
};

#endif