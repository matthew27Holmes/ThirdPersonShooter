//base camera class
#include"camera.h"


class TPSCamera :public Camera
{
public:
	TPSCamera(float _fieldOfView, float _aspectRatio, float _nearPlanetDistance, float _farPlanetDistance, GameObject* _target, Vector3 _up, Vector3 _dpos);
	virtual ~TPSCamera();
	virtual void Tick(GameData* _GD) override;
protected:
	GameObject* m_targetObject;
	Vector3 m_dpos;
	
};