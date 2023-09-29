//============================================================
//
//	�V�[������ [scene.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "sceneTitle.h"
#include "sceneTutorial.h"
#include "sceneGame.h"
#include "sceneResult.h"
#include "stage.h"

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CStage *CScene::m_pStage = NULL;	// �X�e�[�W

//************************************************************
//	�e�N���X [CScene] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CScene::CScene(const MODE mode)
{
	// �����o�ϐ����N���A
	m_mode = mode;	// ���[�h
}

//============================================================
//	�f�X�g���N�^
//============================================================
CScene::~CScene()
{

}

//============================================================
//	����������
//============================================================
HRESULT CScene::Init(void)
{
	// �X�e�[�W�̐���
	m_pStage = CStage::Create();
	if (m_pStage == NULL)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
HRESULT CScene::Uninit(void)
{
	// �X�e�[�W�̔j��
	if (FAILED(CStage::Release(m_pStage)))
	{ // �j���Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�X�V����
//============================================================
void CScene::Update(void)
{
	if (m_pStage != NULL)
	{ // �g�p���̏ꍇ

		// �X�e�[�W�̍X�V
		m_pStage->Update();
	}
	else { assert(false); }	// ��g�p��

	if (CManager::GetRenderer() != NULL)
	{ // �g�p���̏ꍇ

		// �����_���[�̍X�V
		CManager::GetRenderer()->Update();
	}
	else { assert(false); }	// ��g�p��
}

//============================================================
//	��������
//============================================================
CScene *CScene::Create(MODE mode)
{
	// �|�C���^��錾
	CScene *pScene = NULL;	// �V�[�������p

	if (pScene == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		switch (mode)
		{ // ���[�h���Ƃ̏���
		case MODE_TITLE:

			// �^�C�g����ʂ𐶐�
			pScene = new CSceneTitle(mode);

			break;

		case MODE_TUTORIAL:

			// �`���[�g���A����ʂ𐶐�
			pScene = new CSceneTutorial(mode);

			break;

		case MODE_GAME:

			// �Q�[����ʂ𐶐�
			pScene = new CSceneGame(mode);

			break;

		case MODE_RESULT:

			// ���U���g��ʂ𐶐�
			pScene = new CSceneResult(mode);

			break;

		default:	// ��O����
			assert(false);
			break;
		}
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pScene != NULL)
	{ // �m�ۂɐ������Ă���ꍇ

		// �V�[���̏�����
		if (FAILED(pScene->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �V�[���̏I��
			if (FAILED(pScene->Uninit()))
			{ // �V�[���̏I���Ɏ��s�����ꍇ

				// �������J��
				delete pScene;
				pScene = NULL;

				// ���s��Ԃ�
				assert(false);
				return NULL;
			}

			// �������J��
			delete pScene;
			pScene = NULL;

			// ���s��Ԃ�
			assert(false);
			return NULL;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pScene;
	}
	else { assert(false); return NULL; }	// �m�ێ��s
}

//============================================================
//	�j������
//============================================================
HRESULT CScene::Release(CScene *&prScene)
{
	if (prScene != NULL)
	{ // �g�p���̏ꍇ

		// �V�[���̏I��
		if (FAILED(prScene->Uninit()))
		{ // �V�[���̏I���Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �������J��
		delete prScene;
		prScene = NULL;

		// ������Ԃ�
		return S_OK;
	}
	else { assert(false); return E_FAIL; }	// ��g�p��
}

//============================================================
//	�X�e�[�W�擾����
//============================================================
CStage *CScene::GetStage(void)
{
	// �X�e�[�W�̃|�C���^��Ԃ�
	return m_pStage;
}

//============================================================
//	���[�h�̐ݒ菈��
//============================================================
void CScene::SetMode(const MODE mode)
{
	// �����̃��[�h��ݒ�
	m_mode = mode;
}

//============================================================
//	���[�h�擾����
//============================================================
CScene::MODE CScene::GetMode(void) const
{
	// ���݂̃��[�h��Ԃ�
	return m_mode;
}
