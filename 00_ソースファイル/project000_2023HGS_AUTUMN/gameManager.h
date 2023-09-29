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

//==========================================
//  �O���錾
//==========================================
class CPlayer;
class CMap;

//************************************************************
//	�N���X��`
//************************************************************
// �Q�[���}�l�[�W���[�N���X
class CGameManager
{
public:
	// �R���X�g���N�^
	CGameManager();

	// �f�X�g���N�^
	~CGameManager();

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V

	// �ÓI�����o�֐�
	static CGameManager *Create(void);	// ����
	static HRESULT Release(CGameManager *&prGameManager);	// �j��
	static CPlayer* GetPlayer(void) { return m_pPlayer; } //�v���C���[�̎擾
	static CMap* GetMap(void) { return m_pMap; } //���E�̎擾

private:

	//�ÓI�����o�ϐ�
	static CPlayer* m_pPlayer; //�v���C���[�̃|�C���^
	static CMap* m_pMap; //���E�̃|�C���^

};

#endif	// _GAMEMANAGER_H_
