//============================================================
//
//	�X�e�[�W�w�b�_�[ [stage.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _STAGE_H_
#define _STAGE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"

//************************************************************
//	�N���X��`
//************************************************************
// �X�e�[�W�N���X
class CStage
{
public:
	// ������
	typedef enum
	{
		LIMIT_BOX = 0,	// ��`�͈�
		LIMIT_CIRCLE,	// �~�͈�
		LIMIT_MAX		// ���̗񋓌^�̑���
	}LIMIT;

	// �R���X�g���N�^
	CStage();

	// �f�X�g���N�^
	~CStage();

	// �X�e�[�W�͈͍\����
	typedef struct
	{
		LIMIT mode;			// �������[�h
		D3DXVECTOR3 center;	// ���S���W
		float fNear;		// �����ʒu (�O)
		float fFar;			// �����ʒu (��)
		float fRight;		// �����ʒu (�E)
		float fLeft;		// �����ʒu (��)
		float fRadius;		// �����ʒu (���a)
		float fField;		// �����ʒu (�n��)
	}StageLimit;

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void SetStageLimit(const StageLimit& rLimit);	// �X�e�[�W�͈͐ݒ�
	StageLimit GetStageLimit(void) const;			// �X�e�[�W�͈͎擾
	void LimitPosition(D3DXVECTOR3& rPos, const float fRadius);						// �ʒu�␳
	bool LandPosition(D3DXVECTOR3& rPos, D3DXVECTOR3& rMove, const float fHeight);	// �͈͊O���n

	// �ÓI�����o�֐�
	static CStage *Create(void);				// ����
	static HRESULT Release(CStage *&prStage);	// �j��

private:
	// �ÓI�����o�֐�
	static void LoadSetup(CStage *pStage);	// �Z�b�g�A�b�v

	// �����o�ϐ�
	StageLimit m_stageLimit;	// �͈͏��
};

#endif	// _STAGE_H_
