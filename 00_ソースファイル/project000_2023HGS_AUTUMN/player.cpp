//==========================================
//
//  �v���C���[�N���X(player.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "player.h"
#include "manager.h"
#include "gameManager.h"
#include "debugproc.h"
#include "input.h"
#include "texture.h"
#include "objectOrbit.h"
#include "map.h"

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
	m_pOrbit = CObjectOrbit::Create(this, XCOL_BLUE, CObjectOrbit::OFFSET_PLAYER, 10);
	m_pOrbit->SetLabel(LABEL_PLAYER);

	//���̒n�_���擾
	m_posNext = CGameManager::GetMap()->GetHeightNext();

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
	//���݂̒n�_���擾
	SetPosition(CGameManager::GetMap()->GetHeightMin());

	//���̒n�_���擾
	m_posNext = CGameManager::GetMap()->GetHeightNext();

	//���݂̍��W���擾
	D3DXVECTOR3 pos = GetPosition();

	//�ړ�����
	Move(pos);

	//��]����
	Rotation();

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
			pPlayer->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\player000.png"));
		}
	}

	return pPlayer;
}

//==========================================
//  �ړ�
//==========================================
void CPlayer::Move(D3DXVECTOR3 pos)
{
#ifdef _DEBUG
	if (CManager::GetKeyboard()->GetTrigger(DIK_W))
	{
		m_posNext = pos + D3DXVECTOR3(0.0f, -200.0f, 0.0f);
	}
	if (CManager::GetKeyboard()->GetTrigger(DIK_S))
	{
		m_posNext = pos + D3DXVECTOR3(0.0f, 200.0f, 0.0f);
	}
	if (CManager::GetKeyboard()->GetTrigger(DIK_A))
	{
		m_posNext = pos + D3DXVECTOR3(-200.0f, 0.0f, 0.0f);
	}
	if (CManager::GetKeyboard()->GetTrigger(DIK_D))
	{
		m_posNext = pos + D3DXVECTOR3(200.0f, 0.0f, 0.0f);
	}
#endif

	//�ړ��x�N�g�����Z�o
	m_vecMove = m_posNext - pos;

	//�ړ�
	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE) || CManager::GetPad()->GetTrigger(CInputPad::KEY_A) || CManager::GetMouse()->GetTrigger(CInputMouse::KEY_LEFT))
	{
		//�ړ����ݒ�
		SetPosition(m_posNext);
		
		//�G�����E��
		CGameManager::GetMap()->DeleteMin();

		//���̒n�_���擾
		m_posNext = CGameManager::GetMap()->GetHeightNext();

		//���E������
		CGameManager::GetMap()->SetAddMove(m_vecMove.y);
	}
}

//==========================================
//  ��]
//==========================================
void CPlayer::Rotation()
{
	//�p�x���擾
	D3DXVECTOR3 rot = GetRotation();

	//�ړ��x�N�g���̊p�x���Z�o
	float fAngle = atan2f(-m_vecMove.x, -m_vecMove.y);
	rot.z = fAngle;

	//�p�x��K�p
	SetRotation(rot);

	//�f�o�b�O�\��
	CManager::GetDebugProc()->Print("�v���C���[���� : %f\n", rot.z);
}
