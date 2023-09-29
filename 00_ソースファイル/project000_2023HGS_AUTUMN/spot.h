//==========================================
//
//  �n�_�N���X(spot.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SPOT_H_
#define _SPOT_H_
#include "object2D.h"

//==========================================
//  �N���X��`
//==========================================
class CSpot : public CObject2D
{
public:

	//�����o�֐�
	CSpot();
	~CSpot();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	float GetPosHight(void) { return GetPosition().y; } //�����̎擾

	//�ÓI�����o�֐�
	static CSpot* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:

};

#endif
