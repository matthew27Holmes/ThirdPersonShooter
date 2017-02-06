#ifndef _BULLET_H_
#define _BULLET_H_
#include "CMOGO.h"
#include <list>
class Gun;

class Bullet : public CMOGO
{
public:
	Bullet(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF);
	~Bullet();

	void Spawn(float _life, Vector3 _pos, Vector3 _dir, Vector3 _up);

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(ID3D11DeviceContext* _pd3dImmediateContext, CommonStates* _states, Camera* _cam) override;


private:

	float m_lifeLeft;
	Vector3 m_dir;
	Vector3 m_up;

};

#endif