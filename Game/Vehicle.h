#ifndef _VEHICLE_H_
#define _VEHICLE_H_
#include "CMOGO.h"
#include <dinput.h>
using namespace DirectX;


class Vehicle : public CMOGO
{

public:
	Vehicle(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF);
	~Vehicle();

	virtual void Tick(GameData*_GD)override;//, unsigned char* _keyboardState) override;
	virtual void Draw(ID3D11DeviceContext* _pd3dImmediateContext, CommonStates* _states, Camera* _cam) override;
protected:
	//keyborad input stuff
	IDirectInput8*m_pDirectInput;
	IDirectInputDevice8*m_pkeyboard;
	
	unsigned char m_keyboardState[256];
	Matrix m_fudge;
};

#endif