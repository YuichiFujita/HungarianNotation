//==========================================
//
//  地点クラス(spot.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "spot.h"
#include "manager.h"
#include "debugproc.h"

//==========================================
//  コンストラクタ
//==========================================
CSpot::CSpot() : CObject2D(LABEL_NONE)
{

}

//==========================================
//  デストラクタ
//==========================================
CSpot::~CSpot()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CSpot::Init(void)
{
	return CObject2D::Init();
}

//==========================================
//  終了処理
//==========================================
void CSpot::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CSpot::Update(void)
{
	CObject2D::Update();
	
	//デバッグ表示
	D3DXVECTOR3 pos = GetPosition();
}

//==========================================
//  描画処理
//==========================================
void CSpot::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  生成処理
//==========================================
CSpot* CSpot::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//オブジェクトを生成
	CSpot* pSpot = nullptr;

	//メモリを確保
	if (pSpot == nullptr)
	{
		pSpot = new CSpot;

		if (pSpot != nullptr)
		{
			//初期化処理
			pSpot->Init();

			//各データの設定
			pSpot->SetPosition(pos);
			pSpot->SetScaling(size);
			pSpot->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		}
	}

	return pSpot;
}
