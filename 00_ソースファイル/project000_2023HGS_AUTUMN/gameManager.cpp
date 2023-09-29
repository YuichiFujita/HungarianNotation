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
#include "sceneGame.h"
#include "player.h"
#include "map.h"
#include "enemy.h"
#include "score.h"
#include "timerManager.h"
#include "objectGauge2D.h"
#include "score.h"
#include "texture.h"

//==========================================
//  �ÓI�����o�֐��錾
//==========================================
CPlayer* CGameManager::m_pPlayer = nullptr;
CMap* CGameManager::m_pMap = nullptr;
CObject2D* CGameManager::m_pObject2D[2] = { nullptr , nullptr };

CGameManager::STATE CGameManager::m_state = STATE_START;

//************************************************************
//	�e�N���X [CGameManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CGameManager::CGameManager()
{
	m_curtainInterbal = 0;
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
	//CEnemy::Create(D3DXVECTOR3(640.0f, 100.0f, 0.0f), D3DXVECTOR3(100.0f, 10.0f, 0.0f), VEC3_ZERO, XCOL_WHITE, CEnemy::TYPE_STICK_SLIDE);
	m_pPlayer = CPlayer::Create(m_pMap->GetHeightMin(), D3DXVECTOR3(100.0f, 100.0f, 0.0f));

	m_pObject2D[0] = CObject2D::Create(D3DXVECTOR3(320.0f, 360.0f, 0.0f), D3DXVECTOR3(640.0f, 720.0f, 0.0f));
	m_pObject2D[1] = CObject2D::Create(D3DXVECTOR3(960.0f, 360.0f, 0.0f), D3DXVECTOR3(640.0f, 720.0f, 0.0f));

	m_pObject2D[0]->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\fade003.jpg"));
	m_pObject2D[1]->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\fade003.jpg"));

	m_state = STATE_START;

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CGameManager::Uninit(void)
{
	//���E�̔j��
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
	if (m_state == STATE_START)
	{
		m_curtainInterbal++;

		if (m_curtainInterbal > 30)
		{
			D3DXVECTOR3 scale;
			D3DXVECTOR3 pos;

			pos = m_pObject2D[0]->GetPosition();
			scale = m_pObject2D[0]->GetScaling();
			pos.x -= 4.0f;
			scale.x -= 8.0f;
			m_pObject2D[0]->SetPosition(pos);
			m_pObject2D[0]->SetScaling(scale);

			pos = m_pObject2D[1]->GetPosition();
			scale = m_pObject2D[1]->GetScaling();
			pos.x += 4.0f;
			scale.x -= 8.0f;
			m_pObject2D[1]->SetPosition(pos);
			m_pObject2D[1]->SetScaling(scale);

			if (m_pObject2D[0]->GetPosition().x < 0.0f)
			{
				CSceneGame::GetTimerManager()->Start();	// �v�����J�n
				m_state = STATE_NORMAL;
				m_pObject2D[0]->Uninit();
				m_pObject2D[1]->Uninit();
			}
		}
	}
	else
	{
		if (m_pMap != nullptr)
		{
			m_pMap->Update();
		}

		if (CSceneGame::GetTimerManager()->GetState() == CTimerManager::STATE_END)
		{ // �^�C�}�[�̌v�����I���ς݂̏ꍇ

			// ���U���g�ɑJ��
			TransitionResult(CRetentionManager::RESULT_CLEAR);
		}
		else if (CSceneGame::GetGameManager()->GetPlayer()->GetMiss())
		{ // �v���C���[�����S�����ꍇ

			// ���U���g�ɑJ�ڂ���
			TransitionResult(CRetentionManager::RESULT_FAILED);
		}
	}
}

//============================================================
//	���U���g�J�ڏ���
//============================================================
void CGameManager::TransitionResult(const CRetentionManager::RESULT result)
{
	// �|�C���^��錾
	CRetentionManager *pRetention = CManager::GetRetentionManager();	// �f�[�^�ۑ����

	// �N���A�󋵂�ݒ�
	pRetention->SetResult(result);

	// �l���X�R�A��ݒ�
	pRetention->SetScore(CSceneGame::GetScore()->Get());

	// ���U���g�ɑJ��
	CManager::SetScene(CScene::MODE_RESULT, 30);
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

