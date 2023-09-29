//==========================================
//
//  プレイヤークラス(player.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "player.h"

//==========================================
//  コンストラクタ
//==========================================
CPlayer::CPlayer()
{
	m_posNext = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==========================================
//  デストラクタ
//==========================================
CPlayer::~CPlayer()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CPlayer::Init(void)
{
	//初期化
	return CObject2D::Init();
}

//==========================================
//  終了処理
//==========================================
void CPlayer::Uninit(void)
{
	//終了
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CPlayer::Update(void)
{
	//更新
	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CPlayer::Draw(void)
{
	//描画
	CObject2D::Draw();
}

//==========================================
//  移動情報の取得
//==========================================
void CPlayer::GetVecInfo(D3DXVECTOR3* posCurrent, D3DXVECTOR3* posNext, D3DXVECTOR3* vecMove)
{
	*posCurrent = GetPosition();
	*posNext = m_posNext;
	*vecMove = m_vecMove;
}

//==========================================
//  生成処理
//==========================================
CPlayer* CPlayer::Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize, const D3DXVECTOR3& rRot, const D3DXCOLOR& rCol)
{
	//オブジェクトを生成
	CPlayer* pPlayer = nullptr;

	//メモリを確保
	if (pPlayer == nullptr)
	{
		pPlayer = new CPlayer;

		if (pPlayer != nullptr)
		{
			//初期化処理
			pPlayer->Init();

			//各データの設定
			pPlayer->SetPosition(rPos);
			pPlayer->SetScaling(rSize);
			pPlayer->SetRotation(rRot);
			pPlayer->SetColor(rCol);
		}
	}

	return pPlayer;
}
