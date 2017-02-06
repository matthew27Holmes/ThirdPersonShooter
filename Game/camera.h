//base camera class
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "gameobject.h"

class Camera : public GameObject
{
public:
	Camera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance, Vector3 _target, Vector3 _up);
	~Camera();

	//getters
	Matrix const GetProj() { return m_projMat; };
	Matrix const GetView() { return m_viewMat; };

	virtual void Tick(GameData*_GD) ;

	virtual void Draw( ID3D11DeviceContext* _pd3dImmediateContext,  CommonStates* _states, Camera* _cam) override;

protected:

	//parameters for setting up a camera
	Matrix m_projMat;
	Matrix m_viewMat;

	float m_fieldOfView;
	float m_aspectRatio;
	float m_nearPlaneDistance;
	float m_farPlaneDistance;

	Vector3 m_target;
	Vector3 m_up;

};


#endif