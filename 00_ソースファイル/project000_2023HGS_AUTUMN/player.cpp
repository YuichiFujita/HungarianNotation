//==========================================
//
//  プレイヤークラス(player.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "player.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "objectOrbit.h"

//==========================================
//  コンストラクタ
//==========================================
CPlayer::CPlayer() : CObject2D(LABEL_PLAYER)
{
	m_pOrbit = NULL;
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
	// 軌跡の生成
	m_pOrbit = CObjectOrbit::Create(this, XCOL_BLUE, CObjectOrbit::OFFSET_PLAYER);
	m_pOrbit->SetLabel(LABEL_PLAYER);

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
	//現在の座標を取得
	D3DXVECTOR3 pos = GetPosition();

	//移動
	if(CManager::GetKeyboard()->GetTrigger(DIK_SPACE) || CManager::GetPad()->GetTrigger(CInputPad::KEY_A) || CManager::GetMouse()->GetTrigger(CInputMouse::KEY_LEFT))
	{

	}

#ifdef _DEBUG
	if (CManager::GetKeyboard()->GetTrigger(DIK_W))
	{
		m_posNext = pos + D3DXVECTOR3(0.0f, -200.0f, 0.0f);
		SetPosition(m_posNext);
	}
	if (CManager::GetKeyboard()->GetTrigger(DIK_S))
	{
		m_posNext = pos + D3DXVECTOR3(0.0f, 200.0f, 0.0f);
		SetPosition(m_posNext);
	}
	if (CManager::GetKeyboard()->GetTrigger(DIK_A))
	{
		m_posNext = pos + D3DXVECTOR3(-200.0f, 0.0f, 0.0f);
		SetPosition(m_posNext);
	}
	if (CManager::GetKeyboard()->GetTrigger(DIK_D))
	{
		m_posNext = pos + D3DXVECTOR3(200.0f, 0.0f, 0.0f);
		SetPosition(m_posNext);
	}
#endif

	//更新
	CObject2D::Update();

	//デバッグ表示
	CManager::GetDebugProc()->Print("プレイヤーいるよ\n");
	CManager::GetDebugProc()->Print("プレイヤー座標 : ( %f, %f )\n", pos.x, pos.y);
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
