//==========================================
//
//  エネミーマネージャ(enemymanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemymanager.h"
#include "sceneGame.h"
#include "timerManager.h"
#include "enemy.h"

//==========================================
//  コンストラクタ
//==========================================
CEnemyManager::CEnemyManager()
{
	m_nPopTime = 6;
}

//==========================================
//  デストラクタ
//==========================================
CEnemyManager::~CEnemyManager()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemyManager::Init(void)
{
	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CEnemyManager::Uninit(void)
{

}

//==========================================
//  更新処理
//==========================================
void CEnemyManager::Update(void)
{
	int nTime = CSceneGame::GetTimerManager()->GetSec();
	if (nTime % m_nPopTime)
	{
		CEnemy::Create
		(
			D3DXVECTOR3(SCREEN_CENT.x, -10.0f, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH * 0.05f, SCREEN_HEIGHT * 0.05f, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			CEnemy::TYPE_STICK_SLIDE
		);
	}
}

//==========================================
//  描画処理
//==========================================
void CEnemyManager::Draw(void)
{

}
