#include "TPSCamera.h"

 TPSCamera::TPSCamera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance, GameObject*_target, Vector3 _up, Vector3 _dpos) 
	 :Camera(_fieldOfView, _aspectRatio, _nearPlaneDistance, _farPlaneDistance, _target ->GetPos(), _up)
{
	m_targetObject = _target;
	m_dpos = _dpos;
}
 TPSCamera::~TPSCamera()
 {

 }

 void TPSCamera::Tick(GameData*_GD)
 {
	 //set up postion of camera and target postion of camera based on new position and orientation of target object 
	 Matrix rotCam = Matrix::CreateFromYawPitchRoll(m_targetObject->GetYaw(), 0.0f, 0.0f);

	 m_pos = Vector3::Transform(m_dpos, rotCam) + m_targetObject->GetPos();
	 m_target = m_targetObject->GetPos();

	
	 Camera::Tick(_GD);
	

 }
 