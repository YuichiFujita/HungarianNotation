//==========================================
//
//  プレイヤークラス(player.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "object2D.h"

//==========================================
//  クラス定義
//==========================================
class CPlayer : public CObject2D
{
public:

	//メンバ関数
	CPlayer();
	~CPlayer();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void GetVecInfo(D3DXVECTOR3* posCurrent, D3DXVECTOR3* posNext, D3DXVECTOR3* vecMove); //移動情報の取得

	//静的メンバ関数
	static CPlayer* Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize = VEC3_ONE, const D3DXVECTOR3& rRot = VEC3_ZERO, const D3DXCOLOR& rCol = XCOL_WHITE);

private:

	//メンバ変数
	D3DXVECTOR3 m_posNext;
	D3DXVECTOR3 m_vecMove;

};

#endif
