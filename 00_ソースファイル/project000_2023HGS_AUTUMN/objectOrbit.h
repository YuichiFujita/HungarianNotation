//============================================================
//
//	�I�u�W�F�N�g�O�Ճw�b�_�[ [objectOrbit.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECT_ORBIT_H_
#define _OBJECT_ORBIT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "object.h"

//************************************************************
//	�}�N����`
//************************************************************
#define MAX_OFFSET		(2)		// �I�t�Z�b�g�̐�
#define DEFAULT_PART	(10)	// �f�t�H���g�̕�����
#define DEFAULT_TEXPART	(1)		// �f�t�H���g�̃e�N�X�`��������

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g�O�ՃN���X
class CObjectOrbit : public CObject
{
public:
	// �I�t�Z�b�g��
	enum OFFSET
	{
		OFFSET_PLAYER = 0,	// �v���C���[�I�t�Z�b�g
		OFFSET_MAX			// ���̗񋓌^�̑���
	};

	// ��ԗ�
	enum STATE
	{
		STATE_NONE = 0,	// �������Ȃ����
		STATE_NORMAL,	// �ʏ���
		STATE_VANISH,	// �������
		STATE_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CObjectOrbit();
	CObjectOrbit(const CObject::LABEL label, const int nPriority = DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectOrbit();

	// �O�Ս\����
	typedef struct
	{
		D3DXVECTOR3	aPos[MAX_OFFSET];		// ���[�̊�ʒu
		D3DXCOLOR	aCol[MAX_OFFSET];		// ���[�̊�F
		float		aOffset[MAX_OFFSET];	// ���[�̃I�t�Z�b�g
		D3DXVECTOR3	*pPosPoint;				// �e���_���W
		D3DXCOLOR	*pColPoint;				// �e���_�J���[
		CObject		*pParent;				// �e�I�u�W�F�N�g
		D3DXVECTOR3	posVanish;				// �����J�n���̐e�̈ʒu
		D3DXVECTOR3	rotVanish;				// �����J�n���̐e�̌���
		int nPart;		// ������
		int nTexPart;	// �e�N�X�`��������
		bool bAlpha;	// ��������
		bool bInit;		// ��������
	}Orbit;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	int GetState(void);	// ��Ԏ擾

	// �ÓI�����o�֐�
	static CObjectOrbit *Create	// ����
	( // ����
		CObject *pParent,		// �e�I�u�W�F�N�g
		const D3DXCOLOR& rCol,	// �F
		const OFFSET offset,	// �I�t�Z�b�g
		const int nPart = DEFAULT_PART,			// ������
		const int nTexPart = DEFAULT_TEXPART,	// �e�N�X�`��������
		const bool bAlpha = true				// ��������
	);

	// �����o�֐�
	void BindTexture(const int nTextureID);	// �e�N�X�`������
	void SetState(const STATE state);		// ��Ԑݒ�
	void SetParent(CObject *pParent);		// �e�I�u�W�F�N�g�ݒ�
	void SetColor(const D3DXCOLOR& rCol);	// �F�ݒ�
	void SetOffset(const OFFSET offset);	// �I�t�Z�b�g�ݒ�
	void SetTexPart(const int nTexPart);	// �e�N�X�`���������ݒ�
	void SetEnableAlpha(const bool bAlpha);	// �������󋵐ݒ�
	void SetEnableInit(const bool bInit);	// �������󋵐ݒ�
	HRESULT SetLength(const int nPart);		// �����ݒ�

protected:
	// �����o�֐�
	void SetVtx(void);	// ���_���̐ݒ�

private:
	// �ÓI�����o�ϐ�
	static const float mc_aOffset[][MAX_OFFSET];	// �I�t�Z�b�g�̈ʒu������

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	Orbit m_orbit;			// �O�Ղ̏��
	STATE m_state;			// ���
	int m_nCounterState;	// ��ԊǗ��J�E���^�[
	int m_nNumVtx;			// �K�v���_��
	int m_nTextureID;		// �e�N�X�`���C���f�b�N�X
};

#endif	// _OBJECT_ORBIT_H_
