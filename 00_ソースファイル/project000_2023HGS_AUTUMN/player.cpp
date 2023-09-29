//==========================================
//
//  �v���C���[�N���X(player.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "player.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "objectOrbit.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CPlayer::CPlayer() : CObject2D(LABEL_PLAYER)
{
	m_pOrbit = NULL;
	m_posNext = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==========================================
//  �f�X�g���N�^
//==========================================
CPlayer::~CPlayer()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CPlayer::Init(void)
{
	// �O�Ղ̐���
	m_pOrbit = CObjectOrbit::Create(this, XCOL_BLUE, CObjectOrbit::OFFSET_PLAYER);
	m_pOrbit->SetLabel(LABEL_PLAYER);

	//������
	return CObject2D::Init();
}

//==========================================
//  �I������
//==========================================
void CPlayer::Uninit(void)
{
	//�I��
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CPlayer::Update(void)
{
	//���݂̍��W���擾
	D3DXVECTOR3 pos = GetPosition();

	//�ړ�
	if(CManager::GetKeyboard()->GetTrigger(DIK_SPACE) || CManager::GetPad()->GetTrigger(CInputPad::KEY_A) || CManager::GetMouse()->GetTrigger(CInputMouse::KEY_LEFT))
	{

	}

#ifdef _DEBUG
	if (CManager::GetKeyboard()->GetTrigger(DIK_W))
	{
		m_posNext = pos + D3DXVECTOR3(0.0f, -200.0f, 0.0f);
		SetPosition(m_posNext);
	}
	if (CManager::GetKeyboard()->GetTrigger(DIK_S))
	{
		m_posNext = pos + D3DXVECTOR3(0.0f, 200.0f, 0.0f);
		SetPosition(m_posNext);
	}
	if (CManager::GetKeyboard()->GetTrigger(DIK_A))
	{
		m_posNext = pos + D3DXVECTOR3(-200.0f, 0.0f, 0.0f);
		SetPosition(m_posNext);
	}
	if (CManager::GetKeyboard()->GetTrigger(DIK_D))
	{
		m_posNext = pos + D3DXVECTOR3(200.0f, 0.0f, 0.0f);
		SetPosition(m_posNext);
	}
#endif

	//�X�V
	CObject2D::Update();

	//�f�o�b�O�\��
	CManager::GetDebugProc()->Print("�v���C���[�����\n");
	CManager::GetDebugProc()->Print("�v���C���[���W : ( %f, %f )\n", pos.x, pos.y);
}

//==========================================
//  �`�揈��
//==========================================
void CPlayer::Draw(void)
{
	//�`��
	CObject2D::Draw();
}

//==========================================
//  �ړ����̎擾
//==========================================
void CPlayer::GetVecInfo(D3DXVECTOR3* posCurrent, D3DXVECTOR3* posNext, D3DXVECTOR3* vecMove)
{
	*posCurrent = GetPosition();
	*posNext = m_posNext;
	*vecMove = m_vecMove;
}

//==========================================
//  ��������
//==========================================
CPlayer* CPlayer::Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize, const D3DXVECTOR3& rRot, const D3DXCOLOR& rCol)
{
	//�I�u�W�F�N�g�𐶐�
	CPlayer* pPlayer = nullptr;

	//���������m��
	if (pPlayer == nullptr)
	{
		pPlayer = new CPlayer;

		if (pPlayer != nullptr)
		{
			//����������
			pPlayer->Init();

			//�e�f�[�^�̐ݒ�
			pPlayer->SetPosition(rPos);
			pPlayer->SetScaling(rSize);
			pPlayer->SetRotation(rRot);
			pPlayer->SetColor(rCol);
		}
	}

	return pPlayer;
}
