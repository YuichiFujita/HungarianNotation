//==========================================
//
//  �G�l�~�[�N���X(enemy.cpp)
//  Author : Riku Nakamura
//
//==========================================
#include "enemy.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy::CEnemy()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy::~CEnemy()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemy::Init(void)
{
	//������
	return CObject2D::Init();
}

//==========================================
//  �I������
//==========================================
void CEnemy::Uninit(void)
{
	//�I��
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy::Update(void)
{
	//�X�V
	CObject2D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy::Draw(void)
{
	//�`��
	CObject2D::Draw();
}

//==========================================
//  ��������
//==========================================
CEnemy* CEnemy::Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize, const D3DXVECTOR3& rRot, const D3DXCOLOR& rCol, const TYPE type)
{
	//�I�u�W�F�N�g�𐶐�
	CEnemy* pEnemy = nullptr;

	//���������m��
	if (pEnemy == nullptr)
	{
		pEnemy = new CEnemy;

		if (pEnemy != nullptr)
		{
			//����������
			pEnemy->Init();

			//�e�f�[�^�̐ݒ�
			pEnemy->SetPosition(rPos);
			pEnemy->SetScaling(rSize);
			pEnemy->SetRotation(rRot);
			pEnemy->SetColor(rCol);
			pEnemy->SetType(type);
			pEnemy->SetLabel(CObject::LABEL_ENEMY);
		}
	}

	return pEnemy;
}

//==========================================
//  �����蔻�菈��
//==========================================
void CEnemy::Collision(D3DXVECTOR3 rPos, D3DXVECTOR3 rSize, D3DXVECTOR3 rRot)
{
	
	float fLength = 0.0f;

	if (rSize.x > rSize.y)
	{
		fLength = rSize.x;
	}
	else
	{
		fLength = rSize.y;
	}
}

