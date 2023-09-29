//============================================================
//
//	�Q�[���}�l�[�W���[�w�b�_�[ [gameManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "retentionManager.h"

//==========================================
//  �O���錾
//==========================================
class CPlayer;
class CMap;
class CObjectGauge2D;
class CObject2D;

//************************************************************
//	�N���X��`
//************************************************************
// �Q�[���}�l�[�W���[�N���X
class CGameManager
{
public:
	// ��ԗ�
	typedef enum
	{
		STATE_NORMAL = 0,	// �ʏ���
		STATE_START,		// �J�n���
		STATE_MAX			// ���̗񋓌^�̑���
	}STATE;

	// �R���X�g���N�^
	CGameManager();

	// �f�X�g���N�^
	~CGameManager();

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void TransitionResult(const CRetentionManager::RESULT result);	// ���U���g�J��

	// �ÓI�����o�֐�
	static CGameManager *Create(void);	// ����
	static HRESULT Release(CGameManager *&prGameManager);	// �j��
	static CPlayer* GetPlayer(void) { return m_pPlayer; } //�v���C���[�̎擾
	static CMap* GetMap(void) { return m_pMap; } //���E�̎擾
	static CObjectGauge2D* GetObjectGauge2D(void) { return m_pObjectGauge2D; } //�Q�[�W�̎擾

private:

	//�����o�ϐ�
	STATE m_state; //���
	int m_curtainInterbal; //���

	//�ÓI�����o�ϐ�
	static CPlayer* m_pPlayer; //�v���C���[�̃|�C���^
	static CMap* m_pMap; //���E�̃|�C���^
	static CObjectGauge2D* m_pObjectGauge2D; //�Q�[�W�̃|�C���^
	static CObject2D* m_pObject2D[2]; //�Q�[�W�̃|�C���^

};

#endif	// _GAMEMANAGER_H_
