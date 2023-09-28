//============================================================
//
//	�v���C���[�w�b�_�[ [player.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "objectChara.h"

//************************************************************
//	�O���錾
//************************************************************
class CObjectGauge3D;	// �I�u�W�F�N�g�Q�[�W3D�N���X
class CShadow;			// �e�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �v���C���[�N���X
class CPlayer : public CObjectChara
{
public:
	// ���f����
	typedef enum
	{
		MODEL_WAIST,	// ��
		MODEL_BODY,		// ��
		MODEL_CLOAK,	// �}���g
		MODEL_HEAD,		// ��
		MODEL_HAT,		// �X�q
		MODEL_ARMUL,	// ����r
		MODEL_ARMUR,	// �E��r
		MODEL_ARMDL,	// �����r
		MODEL_ARMDR,	// �E���r
		MODEL_HANDL,	// ����
		MODEL_HANDR,	// �E��
		MODEL_LEGUL,	// ��������
		MODEL_LEGUR,	// �E������
		MODEL_LEGDL,	// ����
		MODEL_LEGDR,	// �E��
		MODEL_FOOTL,	// ����
		MODEL_FOOTR,	// �E��
		MODEL_ROD,		// ��
		MODEL_MAX		// ���̗񋓌^�̑���
	}MODEL;

	// ���[�V������
	typedef enum
	{
		MOTION_MOVE = 0,		// ���V���[�V����
		MOTION_ACCELE,			// �������[�V����
		MOTION_DECELE,			// �������[�V����
		MOTION_ACTION_LEFT,		// ���A�N�V�������[�V����
		MOTION_ACTION_RIGHT,	// �E�A�N�V�������[�V����
		MOTION_ACTION_FAR,		// ���A�N�V�������[�V����
		MOTION_ACTION_NEAR,		// ��O�A�N�V�������[�V����
		MOTION_BLOW_AWAY,		// ������у��[�V����
		MOTION_DEATH,			// ���S���[�V����
		MOTION_MAX				// ���̗񋓌^�̑���
	}MOTION;

	// ��ԗ�
	typedef enum
	{
		STATE_NONE = 0,		// �������Ȃ����
		STATE_NORMAL,		// �ʏ���
		STATE_DEATH,		// ���S���
		STATE_MAX			// ���̗񋓌^�̑���
	}STATE;

	// �R���X�g���N�^
	CPlayer();

	// �f�X�g���N�^
	~CPlayer();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	void Hit(const int nDmg);	// �q�b�g

	// �ÓI�����o�֐�
	static CPlayer *Create	// ����
	( // ����
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rRot		// ����
	);

	// �����o�֐�
	void SetState(const int nState);			// ��Ԑݒ�
	void SetEnableUpdate(const bool bUpdate);	// �X�V�󋵐ݒ�
	void SetEnableDraw(const bool bDraw);		// �`��󋵐ݒ�
	void SetEnableDrawLife(const bool bDraw);	// �̗͂̕`��󋵐ݒ�

	D3DXMATRIX GetMtxWorld(void) const;	// �}�g���b�N�X�擾
	int GetState(void) const;			// ��Ԏ擾
	float GetRadius(void) const;		// ���a�擾
	int GetLife(void) const;			// �̗͎擾
	int GetMaxLife(void) const;			// �ő�̗͎擾

private:
	// �����o�֐�
	void LoadSetup(void);	// �Z�b�g�A�b�v

	void UpdateOldPosition(void);			// �ߋ��ʒu�̍X�V
	MOTION UpdateMove(void);				// �ړ��ʁE�ڕW�����̍X�V
	void UpdateJump(void);					// �W�����v�̍X�V
	bool UpdateLanding(D3DXVECTOR3& rPos);	// ���n�󋵂̍X�V
	void UpdatePosition(D3DXVECTOR3& rPos);	// �ʒu�̍X�V
	void UpdateRotation(D3DXVECTOR3& rRot);	// �����̍X�V
	void UpdateMotion(int nMotion);			// ���[�V�����E�I�u�W�F�N�g�L�����N�^�[�̍X�V

	MOTION UpdateNormal(void);	// �ʏ��Ԏ��̍X�V

	// �ÓI�����o�ϐ�
	static const char *mc_apModelFile[];	// ���f���萔

	// �����o�ϐ�
	CObjectGauge3D	*m_pLife;	// �̗͂̏��
	CShadow			*m_pShadow;	// �e�̏��

	D3DXVECTOR3	m_oldPos;		// �ߋ��ʒu
	D3DXVECTOR3	m_move;			// �ړ���
	D3DXVECTOR3	m_destRot;		// �ڕW����
	STATE	m_state;			// ���
	int		m_nCounterState;	// ��ԊǗ��J�E���^�[
	int		m_nNumModel;		// �p�[�c�̑���
	bool	m_bJump;			// �W�����v��
};

#endif	// _PLAYER_H_
