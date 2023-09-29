//==========================================
//
//  �n�_�N���X(spot.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "spot.h"
#include "manager.h"
#include "debugproc.h"
#include "enemygroup.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CSpot::CSpot() : CObject2D(LABEL_NONE)
{
	m_pGroup = NULL;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CSpot::~CSpot()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CSpot::Init(void)
{
	return CObject2D::Init();
}

//==========================================
//  �I������
//==========================================
void CSpot::Uninit(void)
{
	if (m_pGroup != nullptr)
	{
		m_pGroup->Uninit();
		m_pGroup = nullptr;
	}

	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CSpot::Update(void)
{
	if (m_pGroup != nullptr)
	{
		m_pGroup->SetPos(GetPosition());
		m_pGroup->Update();
	}

	CObject2D::Update();
	
	//�f�o�b�O�\��
	D3DXVECTOR3 pos = GetPosition();
}

//==========================================
//  �`�揈��
//==========================================
void CSpot::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  ��������
//==========================================
CSpot* CSpot::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�I�u�W�F�N�g�𐶐�
	CSpot* pSpot = nullptr;

	//���������m��
	if (pSpot == nullptr)
	{
		pSpot = new CSpot;

		if (pSpot != nullptr)
		{
			//����������
			pSpot->Init();

			//�e�f�[�^�̐ݒ�
			pSpot->SetPosition(pos);
			pSpot->SetScaling(size);
			pSpot->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

			pSpot->m_pGroup = CEnemyGroup::Create(pSpot->GetPosition(), (float)((rand() % 300) + 200));
		}
	}

	return pSpot;
}
