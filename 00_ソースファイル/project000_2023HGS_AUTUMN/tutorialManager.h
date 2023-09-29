//============================================================
//
//	�`���[�g���A���}�l�[�W���[�w�b�_�[ [tutorialManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _TUTORIAL_MANAGER_H_
#define _TUTORIAL_MANAGER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"

//************************************************************
//	�}�N����`
//************************************************************
#define MAX_TUTORIAL		(2)		//�`���[�g���A���e�N�X�`���̐�

//************************************************************
//	�O���錾
//************************************************************
class CObject2D;	// �I�u�W�F�N�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �`���[�g���A���}�l�[�W���[�N���X
class CTutorialManager
{
public:
	// ������
	enum EXPLAIN
	{
		EXPLAIN_NORMAL = 0,	// �{�^���e�N�X�`��
		EXPLAIN_FIRST,		// �����e�N�X�`��1
		EXPLAIN_SECOND,		// �����e�N�X�`��2
		EXPLAIN_MAX			// ���̗񋓌^�̑���
	};

	// ��ԗ�
	enum STATE
	{
		STATE_NONE = 0,	// �������Ȃ����
		STATE_NORMAL,	// �ʏ���
		STATE_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CTutorialManager();

	// �f�X�g���N�^
	~CTutorialManager();

	// �����o�֐�
	HRESULT Init(void);		// ������
	HRESULT Uninit(void);	// �I��
	void Update(void);		// �X�V

	// �ÓI�����o�֐�
	static CTutorialManager *Create(void);	// ����
	static HRESULT Release(CTutorialManager *&prTutorialManager);	// �j��

private:
	void UpdateStep(void);		//�`���[�g���A���X�e�b�v�X�V����

	// �ÓI�����o�ϐ�
	static const char *mc_apTextureFile[];	// �e�N�X�`���萔

	// �����o�ϐ�
	CObject2D *m_apExplain[MAX_TUTORIAL];	// �����\���̏��
	STATE m_state;			// ���
	int m_nCounterState;	// ��ԊǗ��J�E���^�[
	int m_nCounterExplain;	// �����Ǘ��J�E���^�[
};

#endif	// _TUTORIAL_MANAGER_H_
