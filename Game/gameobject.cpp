#include "gameobject.h"


GameObject::GameObject()
{
	int m = 0.0f;
	//set the Gameobject to the origin with no rotation and unit scaling 
	m_pos = Vector3::Zero;
	m_pitch = 0.0f;
	m_yaw = 0.0f;
	m_roll = 0.0f;
	m_scale = Vector3::One;
	m_alive = true;
	m_radius = 5.0f;

	m_worldMat = Matrix::Identity;
	m_fudge = Matrix::Identity;
	collision_object = Collison::GAMEOBJECT;
}

GameObject::~GameObject()
{}

Vector3 GameObject::GetPos()
{
	return m_pos;
}
float GameObject::GetPitch()
{
	return m_pitch;
}
float GameObject::GetRoll()
{
	return m_roll;
}
float GameObject::GetYaw()
{
	return m_yaw;
}
Matrix GameObject::GetFudge()
{
	return m_fudge;
}

Matrix GameObject::GetWorldMat()
{
	return m_worldMat;
}
void GameObject::Tick(GameData* _GD)
{
	//build up the world matrix depending on the new position of the GameObject
	//the assumption is that this class will be inherited by the class that ACTUALLY changes this
	Matrix  scaleMat	= Matrix::CreateScale(m_scale*1.3);
	Matrix  rotMat		= Matrix::CreateFromYawPitchRoll( m_yaw, m_pitch, m_roll ); 
	Matrix  transMat	= Matrix::CreateTranslation(m_pos );

	m_worldMat = m_fudge*scaleMat * rotMat * transMat;
}
bool GameObject::checkCollision(GameObject* other)
{
	return (Vector3::Distance(m_pos, other->GetPos()) < m_radius + other->getRadius());
}