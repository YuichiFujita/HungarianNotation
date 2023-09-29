//============================================================
//
//	�����L���O�}�l�[�W���[�w�b�_�[ [resultManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _RANKINGMANAGER_H_
#define _RANKINGMANAGER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"

//************************************************************
//	�O���錾
//************************************************************
#define MAX_RANKKING	(5)			//�����L���O��
#define NUM_DIGIT		(8)			//�X�R�A�̌���
#define NUM_RANKING		(MAX_RANKKING * NUM_DIGIT)	// �����L���O�\���ɕK�v�ȃ|���S����

//************************************************************
//	�O���錾
//************************************************************
class CObject2D;		// �I�u�W�F�N�g2D�N���X
class CScore;			// �X�R�A�I�u�W�F�N�g�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �����L���O�}�l�[�W���[�N���X
class CRankingManager
{
public:
	// �e�N�X�`����
	typedef enum
	{
		TEXTURE_LENGTH = 0,		// �����e�N�X�`��
		TEXTURE_SCORE,			// �X�R�A�\���e�N�X�`��
		TEXTURE_MAX				// ���̗񋓌^�̑���
	}TEXTURE;

	// ��ԗ�
	typedef enum
	{
		STATE_NONE = 0,		// �������Ȃ����
		STATE_FADEIN,		// �t�F�[�h�C�����
		STATE_RANKING,		// �����L���O�\�����
		STATE_SCORE_WAIT,	// �X�R�A�\���ҋ@���
		STATE_SCORE,		// �X�R�A�\�����
		STATE_WAIT,			// �J�ڑҋ@���
		STATE_MAX			// ���̗񋓌^�̑���
	}STATE;

	// �R���X�g���N�^
	CRankingManager();

	// �f�X�g���N�^
	~CRankingManager();

	// �����o�֐�
	HRESULT Init(void);		// ������
	HRESULT Uninit(void);	// �I��
	void Update(void);		// �X�V

	// �ÓI�����o�֐�
	static CRankingManager *Create(void);	// ����
	static HRESULT Release(CRankingManager *&prRankingManager);	// �j��

private:
	// �����o�֐�
	void UpdateFade(void);		// �t�F�[�h�C��
	void UpdateRanking(void);	// �����L���O�\��
	void UpdateScore(void);		// �X�R�A�\��
	void UpdateBack(void);		// �J�ڌ���
	void ChangeAlpha(void);		// �����x�ύX
	void SkipStaging(void);		// ���o�X�L�b�v
	void SetTexRanking(void);	// �����L���O�\���̃e�N�X�`���ݒ�
	void Load(void);			// �����L���O�̓ǂݍ��ݏ���
	void Set(void);				// �����L���O�̐ݒ菈��
	bool UpdateDrawWait(const int nWait);	// �\���ҋ@

	// �ÓI�����o�ϐ�
	static const char *mc_apTextureFile[];	// �e�N�X�`���萔

	// �����o�ϐ�
	CObject2D *m_pRanking;	// �����L���O�w�i�̏��
	//CObject2D *m_pScoreLogo;	// �X�R�A���S�̏��
	CObject2D *m_pFade;		// �t�F�[�h�̏��
	CScore *m_pScore[MAX_RANKKING];		// �X�R�A�̏��
	STATE m_state;			// ���
	int m_nCounterState;	// ��ԊǗ��J�E���^�[
	int m_nCounterAlpha;	// �����L���O�̓����x�ύX�Ԋu
	int m_nScore[MAX_RANKKING];			// �����L���O
	int m_nRankUpdate;		// �����L���O�X�V�ԍ�
	float m_fScale;			// �|���S���g�嗦

};

#endif	// _RESULTMANAGER_H_
