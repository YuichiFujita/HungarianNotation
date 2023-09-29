//==========================================
//
//  エネミークラス(enemy.cpp)
//  Author : Riku Nakamura
//
//==========================================
#include "enemy.h"

//==========================================
//  コンストラクタ
//==========================================
CEnemy::CEnemy()
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemy::~CEnemy()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy::Init(void)
{
	//初期化
	return CObject2D::Init();
}

//==========================================
//  終了処理
//==========================================
void CEnemy::Uninit(void)
{
	//終了
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemy::Update(void)
{
	//更新
	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemy::Draw(void)
{
	//描画
	CObject2D::Draw();
}

//==========================================
//  生成処理
//==========================================
CEnemy* CEnemy::Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize, const D3DXVECTOR3& rRot, const D3DXCOLOR& rCol, const TYPE type)
{
	//オブジェクトを生成
	CEnemy* pEnemy = nullptr;

	//メモリを確保
	if (pEnemy == nullptr)
	{
		pEnemy = new CEnemy;

		if (pEnemy != nullptr)
		{
			//初期化処理
			pEnemy->Init();

			//各データの設定
			pEnemy->SetPosition(rPos);
			pEnemy->SetScaling(rSize);
			pEnemy->SetRotation(rRot);
			pEnemy->SetColor(rCol);
			pEnemy->SetType(type);
			pEnemy->SetLabel(CObject::LABEL_ENEMY);
		}
	}

	return pEnemy;
}

//==========================================
//  当たり判定処理
//==========================================
void CEnemy::Collision(D3DXVECTOR3 rPos, D3DXVECTOR3 rSize, D3DXVECTOR3 rRot)
{
	
	float fLength = 0.0f;

	if (rSize.x > rSize.y)
	{
		fLength = rSize.x;
	}
	else
	{
		fLength = rSize.y;
	}
}

