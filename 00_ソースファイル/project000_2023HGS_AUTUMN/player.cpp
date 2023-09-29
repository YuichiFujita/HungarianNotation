//==========================================
//
//  �v���C���[�N���X(player.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "player.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CPlayer::CPlayer()
{
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
	//�X�V
	CObject2D::Update();
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
