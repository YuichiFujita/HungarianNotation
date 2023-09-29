//==========================================
//
//  マップクラス(map.cpp)
//  Autho : Tomoya Kanazaki
//
//==========================================
#include "map.h"
#include "spot.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const CMap::DIFF CMap::m_Diff = { 100, 500, 50, SCREEN_WIDTH - 50 };

//==========================================
//  コンストラクタ
//==========================================
CMap::CMap()
{
	m_vecMove = 0.0f;
	for (int nCnt = 0; nCnt < NUM; nCnt++)
	{
		m_pSpot[nCnt] = nullptr;
	}
}

//==========================================
//  デストラクタ
//==========================================
CMap::~CMap()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CMap::Init(void)
{
	//座標生成処理
	SetSpot();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CMap::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM; nCnt++)
	{
		m_pSpot[nCnt]->Uninit();
	}
}

//==========================================
//  更新処理
//==========================================
void CMap::Update(void)
{
	//座標を生成
	SetSpot();
}

//==========================================
//  描画処理
//==========================================
void CMap::Draw(void)
{

}

//==========================================
//  座標生成処理
//==========================================
void CMap::SetSpot(void)
{
	for (int nCnt = 0; nCnt < NUM; nCnt++)
	{
		if (m_pSpot[nCnt] == nullptr)
		{
			//基準座標Yの取得
			float fHeight = (float)SCREEN_HEIGHT;
			if (nCnt != 0 && m_pSpot[nCnt - 1] != nullptr) //最初のアドレスでない かつ ひとつ前がnullじゃない
			{
				fHeight = m_pSpot[nCnt - 1]->GetPosHight(); //1つ前の座標を取得
			}
			else if (nCnt == 0) //最初のアドレス
			{
				if (m_pSpot[NUM - 1] != nullptr) //一番最後がnullじゃない
				{
					fHeight = m_pSpot[NUM - 1]->GetPosHight(); //一番最後の座標を取得
				}
			}

			//基準座標Yに乱数を加算
			fHeight -= (float)((rand() % (m_Diff.nMaxY + m_Diff.nMinY)) + m_Diff.nMinY);

			//座標Xの乱数を生成
			float fWidth = (float)((rand() % (m_Diff.nMaxX + m_Diff.nMinX)) + m_Diff.nMinX);

			//座標を生成
			m_pSpot[nCnt] = CSpot::Create(D3DXVECTOR3(fWidth, fHeight, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f));
		}
	}
}
