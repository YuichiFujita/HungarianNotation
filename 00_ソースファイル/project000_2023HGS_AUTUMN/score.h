//============================================================
//
//	�X�R�A�w�b�_�[ [score.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SCORE_H_
#define _SCORE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "object.h"

//************************************************************
//	�}�N����`
//************************************************************
#define MAX_SCORE	(8)	// �X�R�A�̌���

//************************************************************
//	�O���錾
//************************************************************
class CValue;		// �����N���X
class CObject2D;	// �I�u�W�F�N�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �X�R�A�N���X
class CScore : public CObject
{
public:
	// �R���X�g���N�^
	CScore();

	// �f�X�g���N�^
	~CScore();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

	// �ÓI�����o�֐�
	static CScore *Create	// ����
	( // ����
		const D3DXVECTOR3& rPos,		// �ʒu
		const D3DXVECTOR3& rSizeValue,	// �����̑傫��
		const D3DXVECTOR3& rSizeUnit,	// �P�ʂ̑傫��
		const D3DXVECTOR3& rSpaceValue,	// �����̋�
		const D3DXVECTOR3& rSpaceUnit	// �P�ʂ̋�
	);

	// �����o�֐�
	void Add(const int nNum);	// ���Z
	void Set(const int nNum);	// �ݒ�
	int  Get(void);				// �擾
	void SetPosition(const D3DXVECTOR3& rPos);		// �ʒu�ݒ�
	void SetScalingValue(const D3DXVECTOR3& rSize);	// �����̑傫���ݒ�
	void SetScalingUnit(const D3DXVECTOR3& rSize);	// �P�ʂ̑傫���ݒ�
	void SetColor(const D3DXCOLOR& rCol);			// �F�ݒ�
	void SetSpaceValue(const D3DXVECTOR3& rSpace);	// �����̋󔒐ݒ�
	void SetSpaceUnit(const D3DXVECTOR3& rSpace);	// �P�ʂ̋󔒐ݒ�
	void SetPriority(const int nPriority);			// �D�揇�ʐݒ�
	void SetEnableUpdate(const bool bUpdate);		// �X�V�󋵐ݒ�
	void SetEnableDraw(const bool bDraw);			// �`��󋵐ݒ�
	D3DXVECTOR3 GetPosition(void) const;			// �ʒu�擾
	D3DXVECTOR3 GetScaling(void) const;				// �傫���擾
	D3DXVECTOR3 GetSpace(void) const;				// �󔒎擾

private:
	// �����o�֐�
	void SetDrawUnit(void);		// �P�ʂ̕\���ݒ�
	void SetDrawValue(void);	// �����̕\���ݒ�
	void SetTexNum(void);		// �����̃e�N�X�`�����W�ݒ�

	// �����o�ϐ�
	CValue *m_apValue[MAX_SCORE];	// ���l�̏��
	CObject2D *m_pUnit;				// �P�ʂ̏��
	D3DXVECTOR3 m_pos;				// �ʒu
	D3DXVECTOR3 m_sizeValue;		// �����̑傫��
	D3DXVECTOR3 m_sizeUnit;			// �P�ʂ̑傫��
	D3DXVECTOR3 m_spaceValue;		// �����̋�
	D3DXVECTOR3 m_spaceUnit;		// �P�ʂ̋�
	int m_nNum;						// �X�R�A
};

#endif	// _SCORE_H_
