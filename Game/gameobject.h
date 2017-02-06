#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H
//Base Game Object Class
#include "CommonStates.h"
#include "Collison.h"
#include "SimpleMath.h"
#include "GameData.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Camera;
struct ID3D11DeviceContext;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	//Setters
	void SetPos(Vector3 _pos) { m_pos = _pos; }
	void SetPitch(float _pitch) { m_pitch = _pitch; }
	void SetYaw(float _yaw) { m_yaw = _yaw; }
	void SetRoll(float _roll) { m_roll = _roll; }
	void SetPitchYawRoll(float _pitch, float _yaw, float _roll) { m_pitch = _pitch; m_yaw = _yaw; m_roll = _roll; }
	void SetWorldMat(Matrix _mat) { m_worldMat = _mat; }
	void SetAlive(bool _alive) { m_alive = _alive; }
	void SetRadius(float _radius) { m_radius = _radius; }

	Vector3 GetPos();
	float GetPitch();
	float GetYaw();
	float GetRoll();
	Matrix GetFudge();
	Matrix GetWorldMat();
	bool isAlive() { return m_alive; }
	float getRadius() { return m_radius; }
	Collison getType() { return collision_object; }

	virtual void Tick(GameData*_GD);
	virtual void Draw( ID3D11DeviceContext* _pd3dImmediateContext,  CommonStates* _states, Camera* _cam) = 0;
	virtual bool checkCollision(GameObject* other);
protected:
	Vector3 m_pos;
	//radius variables
	//Vector3 m_Rpos;
	//Vector3 m_radius;

	bool m_alive;
	float m_radius;

	float m_pitch, m_yaw, m_roll;
	Collison collision_object;
	Vector3 m_scale;
	Matrix m_worldMat;
	Matrix m_fudge;
	
};

#endif