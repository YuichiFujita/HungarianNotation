//==========================================
//
//  �G�l�~�[�̏W�c(enemygroup.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemygroup.h"
#include "enemy.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemyGroup::CEnemyGroup() : CObject(CObject::LABEL_NONE)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNum = 0;
	for (int nCnt = 0; nCnt < 2;nCnt++)
	{
		m_pEnemy[nCnt] = nullptr;
	}
	m_fAngle = 0.0f;
	m_fLength = 0.0f;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemyGroup::~CEnemyGroup()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemyGroup::Init(void)
{
	m_fAngle = (D3DX_PI * 2.0f) / 2;

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3
		(
			m_pos.x + (sinf(m_rot.z + m_fAngle * (float)nCnt) * m_fLength),
			m_pos.y + (cosf(m_rot.z + m_fAngle * (float)nCnt) * m_fLength),
			0.0f
		);

		m_pEnemy[nCnt] = CEnemy::Create(pos,
			D3DXVECTOR3(SCREEN_WIDTH * 0.05f, SCREEN_HEIGHT * 0.05f, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
			CEnemy::TYPE_STICK);
	}

	return S_OK;
}

//==========================================
//  �I������
//=========================================
void CEnemyGroup::Uninit(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pEnemy[nCnt]->Uninit();
		m_pEnemy[nCnt] = nullptr;
	}

	Release();
}

//==========================================
//  �X�V����
//==========================================
void CEnemyGroup::Update(void)
{
	m_rot.z += 0.015f;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3
		(
			m_pos.x + (sinf(m_rot.z + m_fAngle * (float)nCnt) * m_fLength),
			m_pos.y + (cosf(m_rot.z + m_fAngle * (float)nCnt) * m_fLength),
			0.0f
		);

		if (m_pEnemy[nCnt] != nullptr)
		{
			m_pEnemy[nCnt]->SetPosition(pos);
		}
	}

	if (m_pos.y >= SCREEN_HEIGHT)
	{
		Uninit();
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pEnemy[nCnt]->Update();
	}
}

//==========================================
//  �`�揈��
//==========================================
void CEnemyGroup::Draw(void)
{

}

//==========================================
//  ��������
//==========================================
CEnemyGroup* CEnemyGroup::Create(D3DXVECTOR3 pos, float fLength)
{
	CEnemyGroup* pGroup = nullptr;

	if (pGroup == nullptr)
	{
		pGroup = new CEnemyGroup;

		if (pGroup != nullptr)
		{
			pGroup->m_pos = pos;
			pGroup->m_fLength = fLength;

			pGroup->Init();
		}
	}

	return pGroup;
}
