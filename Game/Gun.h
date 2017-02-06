#ifndef _GUN_H_
#define _GUN_H_
#include <list>
#include "CMOGO.h"
#include"GameData.h"
#include"Bullet.h"


class Gun :public CMOGO
{
public:
	Gun(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, GameObject* _parent,string _bulletFileName,int _numBullets);
	virtual ~Gun();
	virtual void Tick(GameData* _GD);
	virtual void Draw(ID3D11DeviceContext* _pd3dImmediateContext, CommonStates* _states, Camera* _cam) override;
	list<Bullet*> getBullets();
protected:
	GameObject* m_parent;
	Matrix m_fudge;
	list<Bullet*>m_Bullets;
};
#endif 

