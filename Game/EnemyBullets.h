#ifndef _ENEMYBULLETS_H_
#define _ENEMYBULLETS_H_
#include "CMOGO.h"

class EnemyBullet : public CMOGO
{
public:
	EnemyBullet(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF);
	~EnemyBullet();

	void Spawn(float _life, Vector3 _pos, Vector3 _dir, Vector3 _up);

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(ID3D11DeviceContext* _pd3dImmediateContext, CommonStates* _states, Camera* _cam) override;
	//virtual void  Collison(Matrix _collidingRadius, Matrix _personalRadius)override;
	bool isAlive(){ return m_alive; }

private:

	bool m_alive;
	float m_lifeLeft;
	Vector3 m_dir;
	Vector3 m_up;

};

#endif