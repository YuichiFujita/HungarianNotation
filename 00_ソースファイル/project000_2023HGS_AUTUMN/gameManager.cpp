//============================================================
//
//	�Q�[���}�l�[�W���[���� [gameManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "gameManager.h"
#include "manager.h"
#include "player.h"
#include "map.h"
#include "enemy.h"

//==========================================
//  �ÓI�����o�֐��錾
//==========================================
CPlayer* CGameManager::m_pPlayer = nullptr;
CMap* CGameManager::m_pMap = nullptr;

//************************************************************
//	�e�N���X [CGameManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CGameManager::CGameManager()
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CGameManager::~CGameManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CGameManager::Init(void)
{
	//���E�̐���
	if (m_pMap == nullptr)
	{
		m_pMap = new CMap;
		m_pMap->Init();
	}

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(m_pMap->GetHeightMin(), D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(640.0f, 100.0f, 0.0f), D3DXVECTOR3(100.0f, 10.0f, 0.0f), VEC3_ZERO, XCOL_WHITE, CEnemy::TYPE_STICK);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CGameManager::Uninit(void)
{
	if (m_pMap != nullptr)
	{
		m_pMap->Uninit();
		delete m_pMap;
		m_pMap = nullptr;
	}
}

//============================================================
//	�X�V����
//============================================================
void CGameManager::Update(void)
{
	if (m_pMap != nullptr)
	{
		m_pMap->Update();
	}
}

//============================================================
//	��������
//============================================================
CGameManager *CGameManager::Create(void)
{
	// �|�C���^��錾
	CGameManager *pGameManager = NULL;	// �Q�[���}�l�[�W���[�����p

	if (pGameManager == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pGameManager = new CGameManager;	// �Q�[���}�l�[�W���[
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pGameManager != NULL)
	{ // �g�p����Ă���ꍇ
		
		// �Q�[���}�l�[�W���[�̏�����
		if (FAILED(pGameManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pGameManager;
			pGameManager = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pGameManager;
	}
	else { assert(false); return NULL; }	// �m�ێ��s
}

//============================================================
//	�j������
//============================================================
HRESULT CGameManager::Release(CGameManager *&prGameManager)
{
	if (prGameManager != NULL)
	{ // �g�p���̏ꍇ

		// �Q�[���}�l�[�W���[�̏I��
		prGameManager->Uninit();

		// �������J��
		delete prGameManager;
		prGameManager = NULL;

		// ������Ԃ�
		return S_OK;
	}
	else { assert(false); return E_FAIL; }	// ��g�p��
}
