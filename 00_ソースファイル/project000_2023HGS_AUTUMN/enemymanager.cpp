//==========================================
//
//  �G�l�~�[�}�l�[�W��(enemymanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemymanager.h"
#include "sceneGame.h"
#include "timerManager.h"
#include "enemy.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemyManager::CEnemyManager()
{
	m_nPopTime = 6;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemyManager::~CEnemyManager()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemyManager::Init(void)
{
	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CEnemyManager::Uninit(void)
{

}

//==========================================
//  �X�V����
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
//  �`�揈��
//==========================================
void CEnemyManager::Draw(void)
{

}
