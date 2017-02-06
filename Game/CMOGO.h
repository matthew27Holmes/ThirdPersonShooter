#ifndef _CMOGO_H_
#define _CMOGO_H_
#include "gameobject.h"
#include "Model.h"
#include <string>

using namespace std;
using namespace DirectX;

class CMOGO : public GameObject
{
public:
	CMOGO(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF);
	virtual ~CMOGO();

	virtual void Tick(GameData*_GD)override;// , unsigned char *_keyboardState);//override;
	virtual void Draw( ID3D11DeviceContext* _pd3dImmediateContext,  CommonStates* _states, Camera* _cam) override;


protected:
	unique_ptr<Model>  m_model;
};

#endif
