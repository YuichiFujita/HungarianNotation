//============================================================
//
//	�����L���O�}�l�[�W���[���� [resultManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "rankingManager.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "texture.h"
#include "object2D.h"
#include "score.h"
#include "timerManager.h"
#include "retentionManager.h"

//************************************************************
//	�}�N����`
//************************************************************
#define RESULT_PRIO	(6)		// �����L���O�̗D�揇��

#define INITCOL_FADE	(XCOL_AWHITE)	// ���l�̏����l
#define SETCOL_FADE	(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f))	// ���l�̒�~�l
#define SIZE_FADE	(SCREEN_SIZE * 0.95f)	// �t�F�[�h�̑傫��
#define ADD_ALPHA	(0.008f)	// ���l�̉��Z��

#define POS_RESULT_MISSION	(D3DXVECTOR3(360.0f, 170.0f, 0.0f))	// �����L���O�\����MISSION�ʒu
#define POS_RESULT_RESULT	(D3DXVECTOR3(920.0f, 170.0f, 0.0f))	// �����L���O�\����RESULT�ʒu
#define SIZE_RESULT			(D3DXVECTOR3(632.7f, 203.5f, 0.0f))	// �����L���O�\���̑傫��
#define SET_RESULT_SCALE	(15.0f)	// �����L���O�\���̏����g�嗦
#define SUB_RESULT_SCALE	(0.65f)	// �����L���O�\���g�嗦�̌��Z��

#define SCORE_WAIT_CNT	(10)	// �X�R�A�\����Ԃւ̕ύX�ҋ@�t���[����
#define POS_SCORE_LOGO	(D3DXVECTOR3(250.0f, 400.0f, 0.0f))		// �X�R�A���S�ʒu
#define SIZE_SCORE_LOGO	(D3DXVECTOR3(487.5f, 154.7f, 0.0f))		// �X�R�A���S�傫��
#define POS_SCORE		(D3DXVECTOR3(490.0f, 400.0f, 0.0f))		// �X�R�A�ʒu

#define SIZE_SCORE_VALUE	(D3DXVECTOR3(94.0f, 112.0f, 0.0f))				// �X�R�A�傫��
#define SIZE_SCORE_UNIT		(D3DXVECTOR3(94.0f, 112.0f, 0.0f))				// �X�R�A�傫��
#define SPACE_SCORE_VALUE	(D3DXVECTOR3(SIZE_SCORE_VALUE.x, 0.0f, 0.0f))	// �X�R�A��
#define SPACE_SCORE_UNIT	(D3DXVECTOR3(800.0f, 0.0f, 0.0f))				// �X�R�A��
#define SET_SCORE_SCALE	(8.0f)	// �X�R�A�\���̏����g�嗦
#define SUB_SCORE_SCALE	(0.4f)	// �X�R�A�\���g�嗦�̌��Z��

#define TIME_WAIT_CNT	(3)	// �^�C���\����Ԃւ̕ύX�ҋ@�t���[����
#define POS_TIME_LOGO	(D3DXVECTOR3(250.0f, 560.0f, 0.0f))			// �^�C�����S�ʒu
#define SIZE_TIME_LOGO	(D3DXVECTOR3(487.5f, 154.7f, 0.0f))			// �^�C�����S�傫��
#define POS_TIME		(D3DXVECTOR3(490.0f, 560.0f, 0.0f))			// �^�C���ʒu
#define SIZE_TIME_VAL	(D3DXVECTOR3(94.0f, 112.0f, 0.0f))			// �^�C�������傫��
#define SIZE_TIME_PART	(D3DXVECTOR3(48.0f, 112.0f, 0.0f))			// �^�C����؂�傫��
#define SPACE_TIME_VAL	(D3DXVECTOR3(SIZE_TIME_VAL.x, 0.0f, 0.0f))	// �^�C��������
#define SPACE_TIME_PART	(D3DXVECTOR3(SIZE_TIME_PART.x, 0.0f, 0.0f))	// �^�C����؂��
#define SET_TIME_SCALE	(8.0f)	// �^�C���\���̏����g�嗦
#define SUB_TIME_SCALE	(0.4f)	// �^�C���\���g�嗦�̌��Z��

#define RANKING_POS		(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 65.0f, 0.0f))		//�����e�N�X�`���̈ʒu
#define RANKING_SIZE	(D3DXVECTOR3(280.0f, 120.0f, 0.0f))					//�����e�N�X�`���̃T�C�Y
#define RANKING_DEF_SIZE	(D3DXVECTOR3(10.0f, 50.0f, 0.0f))					//�����e�N�X�`���̃T�C�Y
#define FILE_RANK		"data\\TXT\\ranking.txt"		//�����L���O�t�@�C��
#define SCORE_INTER		(115.0f)			//�X�R�A�̊Ԋu(��)
#define ALPHA_TIME		(40)				//�����x�ύX����

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
const char *CRankingManager::mc_apTextureFile[] =	// �e�N�X�`���萔
{
	"data\\TEXTURE\\length000.png",	// �����e�N�X�`��
	"data\\TEXTURE\\result003.png",	// �X�R�A�\���e�N�X�`��
};

//************************************************************
//	�e�N���X [CRankingManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CRankingManager::CRankingManager()
{
	// �����o�ϐ����N���A
	//memset(&m_apRanking[0], 0, sizeof(m_apRanking));	// �����L���O�\���̏��
	memset(&m_pScore[0], 0, sizeof(m_pScore));	// �X�R�A�\���̏��
	memset(&m_nScore[0], 0, sizeof(m_nScore));	// �X�R�A�\���̏��

	m_pRanking		= NULL;			//�����L���O�w�i�̏��
	//m_pScoreLogo	= NULL;			// �X�R�A���S�̏��
	//m_pTimeLogo		= NULL;			// �^�C�����S�̏��
	m_pFade			= NULL;			// �t�F�[�h�̏��
	//m_pScore		= NULL;			// �X�R�A�̏��
	//m_pTime			= NULL;			// �^�C���̏��
	m_state			= STATE_NONE;	// ���
	m_nCounterState	= 0;			// ��ԊǗ��J�E���^�[
	m_nCounterAlpha = 0;			// �����L���O�̓����x�ύX�Ԋu
	m_nRankUpdate = -1;				// �����L���O�X�V�ԍ�
	m_fScale		= 0.0f;			// �|���S���g�嗦
}

//============================================================
//	�f�X�g���N�^
//============================================================
CRankingManager::~CRankingManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CRankingManager::Init(void)
{
	// �ϐ��z���錾
	D3DXVECTOR3 aPosRanking[] =	// �����L���O�̈ʒu
	{ // �����l
		POS_RESULT_MISSION,	// MISSION�ʒu
		POS_RESULT_RESULT,	// RESULT�ʒu
	};

	// �|�C���^��錾
	CTexture *pTexture = CManager::GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �����o�ϐ���������
	//memset(&m_apRanking[0], 0, sizeof(m_apRanking));	// �����L���O�\���̏��
	memset(&m_pScore[0], 0, sizeof(m_pScore));	// �X�R�A�\���̏��

	m_pRanking = NULL;			//�����L���O�w�i�̏��
	//m_pScoreLogo = NULL;			// �X�R�A���S�̏��
	//m_pTimeLogo		= NULL;			// �^�C�����S�̏��
	m_pFade = NULL;			// �t�F�[�h�̏��
	//m_pScore		= NULL;			// �X�R�A�̏��
	//m_pTime			= NULL;			// �^�C���̏��
	m_state = STATE_FADEIN;	// ���
	m_nCounterState = 0;			// ��ԊǗ��J�E���^�[
	m_fScale = 0.0f;			// �|���S���g�嗦

	//--------------------------------------------------------
	//	�t�F�[�h�̐����E�ݒ�
	//--------------------------------------------------------
	// �t�F�[�h�̐���
	m_pFade = CObject2D::Create
	( // ����
		SCREEN_CENT,	// �ʒu
		SIZE_FADE,		// �傫��
		VEC3_ZERO,		// ����
		INITCOL_FADE	// �F
	);
	if (m_pFade == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pFade->SetPriority(RESULT_PRIO);

	//--------------------------------------------------------
	//	�����L���O�\���̐����E�ݒ�
	//--------------------------------------------------------

	// �����L���O�\���̐���
	m_pRanking = CObject2D::Create
	( // ����
		RANKING_POS,			// �ʒu
		RANKING_DEF_SIZE	// �傫��
	);
	if (m_pRanking == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pRanking->SetPriority(RESULT_PRIO);

	// �`������Ȃ��ݒ�ɂ���
	m_pRanking->SetEnableDraw(false);

	// �����L���O�\���̃e�N�X�`����ݒ�
	SetTexRanking();

	//--------------------------------------------------------
	//	�X�R�A�\���̐����E�ݒ�
	//--------------------------------------------------------

	//�����L���O�̃��[�h
	Load();

	//�����L���O�̐ݒ菈��
	Set();

	for (int nCntScore = 0; nCntScore < MAX_RANKKING; nCntScore++)
	{
		// �X�R�A�I�u�W�F�N�g�̐���
		m_pScore[nCntScore] = CScore::Create
		( // ����
			D3DXVECTOR3(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.25f + (nCntScore * SCORE_INTER), 0.0f),						// �ʒu
			SIZE_SCORE_VALUE * SET_SCORE_SCALE,	// �傫��
			SIZE_SCORE_UNIT * SET_SCORE_SCALE,	// �傫��
			SPACE_SCORE_VALUE,					// ��
			SPACE_SCORE_UNIT					// ��
		);
		if (m_pScore[nCntScore] == NULL)
		{ // ��g�p���̏ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �D�揇�ʂ�ݒ�
		m_pScore[nCntScore]->SetPriority(RESULT_PRIO);

		// �`������Ȃ��ݒ�ɂ���
		m_pScore[nCntScore]->SetEnableDraw(false);

		// �X�R�A��ݒ�
		m_pScore[nCntScore]->Set(m_nScore[nCntScore]);
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
HRESULT CRankingManager::Uninit(void)
{
	// �����L���O�w�i�̏I��
	m_pRanking->Uninit();

	// �X�R�A���S�\���̏I��
	//m_pScoreLogo->Uninit();

	// �t�F�[�h�̏I��
	m_pFade->Uninit();

	for (int nCntScore = 0; nCntScore < MAX_RANKKING; nCntScore++)
	{
		// �I���ς݂̃I�u�W�F�N�g�|�C���^��NULL�ɂ���
		m_pScore[nCntScore] = NULL;	// �X�R�A�I�u�W�F�N�g
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�X�V����
//============================================================
void CRankingManager::Update(void)
{
	// �J�ڌ���̍X�V
	UpdateBack();

	switch (m_state)
	{ // ��Ԃ��Ƃ̏���
	case STATE_NONE:	// �������Ȃ����

		// ����

		break;

	case STATE_FADEIN:	// �t�F�[�h�C�����

		// �t�F�[�h�C���̍X�V
		UpdateFade();

		break;

	case STATE_RANKING:	// �����L���O�\�����

		// �����L���O�\���̍X�V
		UpdateRanking();

		break;

	case STATE_SCORE_WAIT:	// �X�R�A�\���ҋ@���

		// �\���ҋ@�̍X�V
		if (UpdateDrawWait(SCORE_WAIT_CNT))
		{ // �ҋ@�����̏ꍇ

			// �X�R�A�\���̊g�嗦��ݒ�
			m_fScale = SET_SCORE_SCALE;

			// �X�R�A�\���̕`��J�n
			//m_pScoreLogo->SetEnableDraw(true);

			for (int nCntScore = 0; nCntScore < MAX_RANKKING; nCntScore++)
			{
				m_pScore[nCntScore]->SetEnableDraw(true);
			}

			// ��Ԃ�ύX
			m_state = STATE_SCORE;	// �X�R�A�\�����
		}

		break;

	case STATE_SCORE:	// �X�R�A�\�����

		// �X�R�A�\���̍X�V
		UpdateScore();

		break;

	case STATE_WAIT:	// �J�ڑҋ@���

		// ����

		break;

	default:	// ��O����
		assert(false);
		break;
	}

	// �����L���O�\���̍X�V
	m_pRanking->Update();

	// �X�R�A���S�\���̍X�V
	//m_pScoreLogo->Update();

	//�X�R�A�̓����x�ύX����
	ChangeAlpha();

	// �t�F�[�h�̍X�V
	m_pFade->Update();
}

//============================================================
//	��������
//============================================================
CRankingManager *CRankingManager::Create(void)
{
	// �|�C���^��錾
	CRankingManager *pRankingManager = NULL;	// �����L���O�}�l�[�W���[�����p

	if (pRankingManager == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pRankingManager = new CRankingManager;	// �����L���O�}�l�[�W���[
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pRankingManager != NULL)
	{ // �g�p����Ă���ꍇ
		
		// �����L���O�}�l�[�W���[�̏�����
		if (FAILED(pRankingManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pRankingManager;
			pRankingManager = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pRankingManager;
	}
	else { assert(false); return NULL; }	// �m�ێ��s
}

//============================================================
//	�j������
//============================================================
HRESULT CRankingManager::Release(CRankingManager *&prRankingManager)
{
	if (prRankingManager != NULL)
	{ // �g�p���̏ꍇ

		// �����L���O�}�l�[�W���[�̏I��
		if (FAILED(prRankingManager->Uninit()))
		{ // �j���Ɏ��s�����ꍇ

			// �������J��
			delete prRankingManager;
			prRankingManager = NULL;

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �������J��
		delete prRankingManager;
		prRankingManager = NULL;

		// ������Ԃ�
		return S_OK;
	}
	else { assert(false); return E_FAIL; }	// ��g�p��
}

//============================================================
//	�t�F�[�h�C���̍X�V����
//============================================================
void CRankingManager::UpdateFade(void)
{
	// �ϐ���錾
	D3DXCOLOR colFade = m_pFade->GetColor();	// �t�F�[�h�̐F

	if (colFade.a < SETCOL_FADE.a)
	{ // �����ʂ��ݒ�l�����̏ꍇ

		// �����x�����Z
		colFade.a += ADD_ALPHA;
	}
	else
	{ // �����ʂ��ݒ�l�ȏ�̏ꍇ

		// �����x��␳
		colFade.a = SETCOL_FADE.a;

		// �����L���O�\���̕`��J�n
		m_pRanking->SetEnableDraw(true);

		// �����L���O�\���̊g�嗦��ݒ�
		m_fScale = SET_RESULT_SCALE;

		// ��Ԃ�ύX
		m_state = STATE_RANKING;	// �����L���O�\�����
	}

	// �����x�𔽉f
	m_pFade->SetColor(colFade);
}

//============================================================
//	�����L���O�\���̍X�V����
//============================================================
void CRankingManager::UpdateRanking(void)
{
	if (m_fScale > 1.0f)
	{ // �g�嗦���ŏ��l���傫���ꍇ

		// �g�嗦�����Z
		m_fScale -= SUB_RESULT_SCALE;

		// �����L���O�\���̑傫����ݒ�
		m_pRanking->SetScaling(RANKING_SIZE * m_fScale);
	}
	else
	{ // �g�嗦���ŏ��l�ȉ��̏ꍇ

		// �����L���O�\���̑傫����ݒ�
		m_pRanking->SetScaling(RANKING_SIZE);

		// ��Ԃ�ύX
		m_state = STATE_SCORE_WAIT;	// �X�R�A�\���ҋ@���

		// �T�E���h�̍Đ�
		CManager::GetSound()->Play(CSound::LABEL_SE_DECISION_001);	// ���艹01
	}
}

//============================================================
//	�X�R�A�\���̍X�V����
//============================================================
void CRankingManager::UpdateScore(void)
{
	if (m_fScale > 1.0f)
	{ // �g�嗦���ŏ��l���傫���ꍇ

		// �g�嗦�����Z
		m_fScale -= SUB_SCORE_SCALE;

		// �X�R�A�\���̑傫����ݒ�
		//m_pScoreLogo->SetScaling(SIZE_SCORE_LOGO * m_fScale);

		for (int nCntScore = 0; nCntScore < MAX_RANKKING; nCntScore++)
		{
			m_pScore[nCntScore]->SetScalingValue(SIZE_SCORE_VALUE * m_fScale);
			m_pScore[nCntScore]->SetScalingUnit(SIZE_SCORE_UNIT * m_fScale);
		}
	}
	else
	{ // �g�嗦���ŏ��l�ȉ��̏ꍇ

		// �g�嗦��␳
		m_fScale = 1.0f;

		// �X�R�A�\���̑傫����ݒ�
		//m_pScoreLogo->SetScaling(SIZE_SCORE_LOGO);

		for (int nCntScore = 0; nCntScore < MAX_RANKKING; nCntScore++)
		{
			m_pScore[nCntScore]->SetScalingValue(SIZE_SCORE_VALUE);
			m_pScore[nCntScore]->SetScalingUnit(SIZE_SCORE_UNIT);
		}

		// ��Ԃ�ύX
		m_state = STATE_WAIT;	// �^�C���\���ҋ@���

		// �T�E���h�̍Đ�
		CManager::GetSound()->Play(CSound::LABEL_SE_DECISION_001);	// ���艹01
	}
}

//============================================================
//	�J�ڌ���̍X�V����
//============================================================
void CRankingManager::UpdateBack(void)
{
	// �|�C���^��錾
	CInputKeyboard	*pKeyboard	= CManager::GetKeyboard();	// �L�[�{�[�h
	CInputPad		*pPad		= CManager::GetPad();		// �p�b�h

	if (pKeyboard->GetTrigger(DIK_RETURN)
	||  pKeyboard->GetTrigger(DIK_SPACE)
	||  pPad->GetTrigger(CInputPad::KEY_A)
	||  pPad->GetTrigger(CInputPad::KEY_B)
	||  pPad->GetTrigger(CInputPad::KEY_X)
	||  pPad->GetTrigger(CInputPad::KEY_Y)
	||  pPad->GetTrigger(CInputPad::KEY_START))
	{
		if (m_state != STATE_WAIT)
		{ // �J�ڑҋ@��Ԃł͂Ȃ��ꍇ

			// ���o�X�L�b�v
			SkipStaging();

			// �T�E���h�̍Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_DECISION_001);	// ���艹01
		}
		else
		{ // �J�ڑҋ@��Ԃ̏ꍇ

			if (CManager::GetFade()->GetState() == CFade::FADE_NONE)
			{ // �t�F�[�h���ł͂Ȃ��ꍇ

				// �V�[���̐ݒ�
				CManager::SetScene(CScene::MODE_TITLE);	// �^�C�g�����

				// �T�E���h�̍Đ�
				CManager::GetSound()->Play(CSound::LABEL_SE_DECISION_000);	// ���艹00
			}
		}
	}
}

//============================================================
//	�����x�̕ύX����
//============================================================
void CRankingManager::ChangeAlpha(void)
{
	if (m_nRankUpdate >= 0)
	{//�����L���O�X�V���ꂽ��

		if (m_nCounterAlpha >= ALPHA_TIME * 2)
		{
			//�X�V���ꂽ�̃X�R�A�̐F�߂�
			m_pScore[m_nRankUpdate]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			m_nCounterAlpha = 0;
		}
		else if (m_nCounterAlpha >= ALPHA_TIME)
		{//��莞�Ԃ�������

			//�X�V���ꂽ�X�R�A�̐F�ύX
			m_pScore[m_nRankUpdate]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		}
	}

	m_nCounterAlpha++;		//�����x�ύX�J�E���^�[���Z
}

//============================================================
//	���o�X�L�b�v����
//============================================================
void CRankingManager::SkipStaging(void)
{
	// �����L���O�\���̕`���ON�ɂ��A�傫����ݒ�
	for (int nCntRanking = 0; nCntRanking < NUM_RANKING; nCntRanking++)
	{ // �����L���O�\���̑������J��Ԃ�

		// �����L���O�\���̕`��J�n
		m_pRanking->SetEnableDraw(true);

		// �����L���O�\���̑傫����ݒ�
		m_pRanking->SetScaling(RANKING_SIZE);
	}

	// �X�R�A�\����ON�ɂ���
	//m_pScoreLogo->SetEnableDraw(true);

	for (int nCntScore = 0; nCntScore < MAX_RANKKING; nCntScore++)
	{
		m_pScore[nCntScore]->SetEnableDraw(true);
	}

	// �X�R�A�\���̑傫����ݒ�
	//m_pScoreLogo->SetScaling(SIZE_SCORE_LOGO);

	for (int nCntScore = 0; nCntScore < MAX_RANKKING; nCntScore++)
	{
		m_pScore[nCntScore]->SetScalingValue(SIZE_SCORE_VALUE);
		m_pScore[nCntScore]->SetScalingUnit(SIZE_SCORE_UNIT);
	}

	// �t�F�[�h�̓����x��ݒ�
	m_pFade->SetColor(SETCOL_FADE);

	// ��Ԃ�ύX
	m_state = STATE_WAIT;	// �J�ڑҋ@���
}

//============================================================
//	�����L���O�\���̃e�N�X�`���̐ݒ菈��
//============================================================
void CRankingManager::SetTexRanking(void)
{
	// �|�C���^��錾
	CTexture *pTexture = CManager::GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �w�i�e�N�X�`����o�^�E����
	m_pRanking->BindTexture(pTexture->Regist(mc_apTextureFile[TEXTURE_LENGTH]));
}

//============================================================
//	�\���ҋ@����
//============================================================
bool CRankingManager::UpdateDrawWait(const int nWait)
{
	if (m_nCounterState < nWait)
	{ // �J�E���^�[���ҋ@�J�E���g�܂ŒB���Ă��Ȃ��ꍇ

		// �J�E���^�[�����Z
		m_nCounterState++;

		// �ҋ@��������Ԃ�
		return false;
	}
	else
	{ // �J�E���^�[���ҋ@���������ꍇ

		// �J�E���^�[��������
		m_nCounterState = 0;

		// �ҋ@������Ԃ�
		return true;
	}
}

//============================================================
//	�����L���O�̓ǂݍ��ݏ���
//============================================================
void CRankingManager::Load(void)
{
	FILE *pFile;
	int nCntRank;

	//�����L���O���̏����ݒ�
	for (nCntRank = 0; nCntRank < MAX_RANKKING; nCntRank++)
	{
		m_nScore[nCntRank] = 0;								//�����L���O�̏�����
	}

	//�t�@�C����ǂݍ���
	pFile = fopen(FILE_RANK, "r");

	if (pFile != NULL)
	{//�t�@�C��������ꍇ

		for (nCntRank = 0; nCntRank < MAX_RANKKING; nCntRank++)
		{
			fscanf(pFile, "%d", &m_nScore[nCntRank]);
		}

		//�t�@�C�������
		fclose(pFile);
	}
}

//============================================================
//	�����L���O�ݒ菈��
//============================================================
void CRankingManager::Set(void)
{
	FILE *pFile;
	int nNewRanking;
	int nTemp;

	nNewRanking = CManager::GetRetentionManager()->GetScore();

	if (nNewRanking > m_nScore[MAX_RANKKING - 1])
	{//�V�����X�R�A���ŉ��ʂ�荂��������

		m_nScore[MAX_RANKKING - 1] = nNewRanking;		//�ŉ��ʂɐV�����X�R�A���

		//���݂̏���
		for (int nCntRank = 0; nCntRank < MAX_RANKKING - 1; nCntRank++)
		{
			//���̏���
			for (int nCntData = nCntRank + 1; nCntData < MAX_RANKKING; nCntData++)
			{
				if (m_nScore[nCntRank] < m_nScore[nCntData])
				{//�X�R�A����������

					//�X�R�A����ւ�
					nTemp = m_nScore[nCntRank];
					m_nScore[nCntRank] = m_nScore[nCntData];
					m_nScore[nCntData] = nTemp;
				}
			}
		}

		//�X�V�����NNo.�ύX
		for (int nCntRank = 0; nCntRank < MAX_RANKKING; nCntRank++)
		{
			//�����L���O�X�R�A�̕��בւ�
			if (nNewRanking == m_nScore[nCntRank])
			{
				m_nRankUpdate = nCntRank;
			}
		}
	}

	//�����L���O�ۑ�
	pFile = fopen(FILE_RANK, "w");			//�t�@�C���ǂݍ���

	if (pFile != NULL)
	{//�t�@�C��������ꍇ

		for (int nCntRank = 0; nCntRank < MAX_RANKKING; nCntRank++)
		{//�f�[�^���Z�[�u����

			fprintf(pFile, "%d\n", m_nScore[nCntRank]);
		}

		//�t�@�C�������
		fclose(pFile);
	}
}
