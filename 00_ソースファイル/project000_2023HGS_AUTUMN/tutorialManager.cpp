//============================================================
//
//	�`���[�g���A���}�l�[�W���[���� [tutorialManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "tutorialManager.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "texture.h"
#include "object2D.h"

//************************************************************
//	�}�N����`
//************************************************************
#define TUTORIAL_PRIO	(6)	// �`���[�g���A���̗D�揇��
#define BUTTON_POS		(D3DXVECTOR3(1100.0f,600.0f,0.0f))		//�{�^���̈ʒu
#define BUTTON_SIZE		(D3DXVECTOR3(300.0f,100.0f,0.0f))

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
const char *CTutorialManager::mc_apTextureFile[] =	// �e�N�X�`���萔
{
	"data\\TEXTURE\\player000.png",		// �{�^���e�N�X�`��
	"data\\TEXTURE\\tutorial000.png",	// �����e�N�X�`��1
	"data\\TEXTURE\\sky000.png",	// �����e�N�X�`��1
};

//************************************************************
//	�e�N���X [CTutorialManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CTutorialManager::CTutorialManager()
{
	// �����o�ϐ����N���A
	memset(&m_apExplain[0], 0, sizeof(m_apExplain));	// �����̏��
	m_state		= STATE_NONE;	// ���
	m_nCounterState = 0;		// ��ԊǗ��J�E���^�[
	m_nCounterExplain = 0;		// �����Ǘ��J�E���^�[
}

//============================================================
//	�f�X�g���N�^
//============================================================
CTutorialManager::~CTutorialManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CTutorialManager::Init(void)
{
	// �|�C���^��錾
	CTexture *pTexture = CManager::GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �����o�ϐ���������
	memset(&m_apExplain[0], 0, sizeof(m_apExplain));	// �����̏��
	m_state = STATE_NORMAL;			// ���
	m_nCounterState = 0;				// ��ԊǗ��J�E���^�[
	m_nCounterExplain = EXPLAIN_FIRST;	// �����Ǘ��J�E���^�[

	// �I��w�i�̐���
	m_apExplain[1] = CObject2D::Create
	( // ����
		SCREEN_CENT,	// �ʒu
		SCREEN_SIZE		// �傫��
	);
	if (m_apExplain[1] == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_apExplain[1]->SetPriority(TUTORIAL_PRIO);

	// �����e�N�X�`����o�^�E����
	m_apExplain[1]->BindTexture(pTexture->Regist(mc_apTextureFile[m_nCounterExplain]));


	// �{�^���̐���
	m_apExplain[0] = CObject2D::Create
	( // ����
		BUTTON_POS,	// �ʒu
		BUTTON_SIZE		// �傫��
	);
	if (m_apExplain[0] == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_apExplain[0]->SetPriority(TUTORIAL_PRIO);

	// �����e�N�X�`����o�^�E����
	m_apExplain[0]->BindTexture(pTexture->Regist(mc_apTextureFile[EXPLAIN_NORMAL]));

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
HRESULT CTutorialManager::Uninit(void)
{
	for (int nCntExplain = 0; nCntExplain < MAX_TUTORIAL; nCntExplain++)
	{
		// �����\���̏I��
		m_apExplain[nCntExplain]->Uninit();
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�X�V����
//============================================================
void CTutorialManager::Update(void)
{
	switch (m_state)
	{ // ��Ԃ��Ƃ̏���
	case STATE_NONE:	// �������Ȃ����

		// ����

		break;

	case STATE_NORMAL:	// �ʏ���

		//�`���[�g���A���X�e�b�v�X�V
		UpdateStep();

		break;

	default:	// ��O����
		assert(false);
		break;
	}

	for (int nCntExplain = 0; nCntExplain < MAX_TUTORIAL; nCntExplain++)
	{
		// �����\���̍X�V
		m_apExplain[nCntExplain]->Update();
	}
}

//============================================================
//	��������
//============================================================
CTutorialManager *CTutorialManager::Create(void)
{
	// �|�C���^��錾
	CTutorialManager *pTutorialManager = NULL;	// �`���[�g���A���}�l�[�W���[�����p

	if (pTutorialManager == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pTutorialManager = new CTutorialManager;	// �`���[�g���A���}�l�[�W���[
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pTutorialManager != NULL)
	{ // �g�p����Ă���ꍇ
		
		// �`���[�g���A���}�l�[�W���[�̏�����
		if (FAILED(pTutorialManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pTutorialManager;
			pTutorialManager = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pTutorialManager;
	}
	else { assert(false); return NULL; }	// �m�ێ��s
}

//============================================================
//	�j������
//============================================================
HRESULT CTutorialManager::Release(CTutorialManager *&prTutorialManager)
{
	if (prTutorialManager != NULL)
	{ // �g�p���̏ꍇ

		// �`���[�g���A���}�l�[�W���[�̏I��
		if (FAILED(prTutorialManager->Uninit()))
		{ // �j���Ɏ��s�����ꍇ

			// �������J��
			delete prTutorialManager;
			prTutorialManager = NULL;

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �������J��
		delete prTutorialManager;
		prTutorialManager = NULL;

		// ������Ԃ�
		return S_OK;
	}
	else { assert(false); return E_FAIL; }	// ��g�p��
}

//============================================================
//	�`���[�g���A���X�e�b�v�X�V����
//============================================================
void CTutorialManager::UpdateStep(void)
{
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		m_nCounterExplain++;		//���̃X�e�b�v��

		// �T�E���h�̍Đ�
		CManager::GetSound()->Play(CSound::LABEL_SE_DECISION_000);	// ���艹00
	}

	if (m_nCounterExplain >= EXPLAIN_MAX)
	{
		// �V�[���̐ݒ�
		CManager::SetScene(CScene::MODE_TITLE);	// �^�C�g�����
	}
	else if (m_nCounterExplain < EXPLAIN_MAX)
	{
		CTexture *pTexture = CManager::GetTexture();	// �e�N�X�`���ւ̃|�C���^

		// �����e�N�X�`����o�^�E����
		m_apExplain[1]->BindTexture(pTexture->Regist(mc_apTextureFile[m_nCounterExplain]));
	}
}