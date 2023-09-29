//==========================================
//
//  �}�b�v�N���X(map.cpp)
//  Autho : Tomoya Kanazaki
//
//==========================================
#include "map.h"
#include "spot.h"
#include "player.h"
#include "gameManager.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const CMap::DIFF CMap::m_Diff = { 100, 200, 100, SCREEN_WIDTH - 300 };
float CMap::m_vecMove = 1.0f;

//==========================================
//  �R���X�g���N�^
//==========================================
CMap::CMap()
{
	m_nCntAdd = 0;
	m_fSpeed = m_vecMove;
	for (int nCnt = 0; nCnt < NUM; nCnt++)
	{
		m_pSpot[nCnt] = nullptr;
	}
}

//==========================================
//  �f�X�g���N�^
//==========================================
CMap::~CMap()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CMap::Init(void)
{
	//���W��������
	SetSpot();

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CMap::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM; nCnt++)
	{
		m_pSpot[nCnt]->Uninit();
		m_pSpot[nCnt] = nullptr;
	}
}

//==========================================
//  �X�V����
//==========================================
void CMap::Update(void)
{
	//���E�̉���
	if (CGameManager::GetPlayer()->GetMuteki() && GetHeightNext().y <= 600.0f)
	{
		m_fSpeed = m_vecMove * 100.0f;
	}
	else if (GetHeightMin().y <= SCREEN_CENT.y)
	{
		m_fSpeed = m_vecMove * 20.0f;
	}
	else
	{
		m_fSpeed = m_vecMove;
	}

	//�ʒu���X�V
	for (int nCnt = 0; nCnt < NUM; nCnt++)
	{
		if (m_pSpot[nCnt] != nullptr)
		{
			D3DXVECTOR3 pos = m_pSpot[nCnt]->GetPosition();
			pos.y += m_fSpeed;
			m_pSpot[nCnt]->SetPosition(pos);
			m_pSpot[nCnt]->Update();
		}
	}
}

//==========================================
//  �`�揈��
//==========================================
void CMap::Draw(void)
{
	//�ʒu��`��
	for (int nCnt = 0; nCnt < NUM; nCnt++)
	{
		m_pSpot[nCnt]->Draw();
	}
}

//==========================================
//  ��ԒႢ�n�_�̎擾
//==========================================
D3DXVECTOR3 CMap::GetHeightMin(void)
{
	//�Ԃ�l�̂��߂̕ϐ�
	D3DXVECTOR3 pos;

	//�f�[�^��ۊ�
	float* pPos = new float[NUM];
	for (int nCnt = 0; nCnt < NUM; nCnt++)
	{
		if (m_pSpot[nCnt] != nullptr)
		{
			pPos[nCnt] = m_pSpot[nCnt]->GetPosHeight();
		}
		else
		{
			pPos[nCnt] = -10000000.0f;
		}
	}

	//�\�[�g����
	useful::SortNum(pPos, NUM);

	for (int nCnt = 0; nCnt < NUM; nCnt++)
	{
		if (m_pSpot[nCnt] != nullptr)
		{
			if (m_pSpot[nCnt]->GetPosHeight() == pPos[0])
			{
				pos = m_pSpot[nCnt]->GetPosition();
			}
		}
	}

	delete[] pPos;

	return pos;
}

//==========================================
//  ��ԖڂɒႢ�n�_�̎擾
//==========================================
D3DXVECTOR3 CMap::GetHeightNext(void)
{
	//�Ԃ�l�̂��߂̕ϐ�
	D3DXVECTOR3 pos;

	//�f�[�^��ۊ�
	float *pPos = new float[NUM];
	for (int nCnt = 0; nCnt < NUM; nCnt++)
	{
		if (m_pSpot[nCnt] != nullptr)
		{
			pPos[nCnt] = m_pSpot[nCnt]->GetPosHeight();
		}
		else
		{
			pPos[nCnt] = -10000000.0f;
		}
	}

	//�\�[�g����
	useful::SortNum(pPos, NUM);

	for (int nCnt = 0; nCnt < NUM; nCnt++)
	{
		if (m_pSpot[nCnt] != nullptr)
		{
			if (m_pSpot[nCnt]->GetPosHeight() == pPos[1])
			{
				pos = m_pSpot[nCnt]->GetPosition();
			}
		}
	}

	delete[] pPos;

	return pos;
}

//==========================================
//  ��ԎG�����E��
//==========================================
void CMap::DeleteMin(void)
{
	//�f�[�^��ۊ�
	float* pPos = new float[NUM];
	for (int nCnt = 0; nCnt < NUM; nCnt++)
	{
		if (m_pSpot[nCnt] != nullptr)
		{
			pPos[nCnt] = m_pSpot[nCnt]->GetPosHeight();
		}
		else
		{
			pPos[nCnt] = -10000000.0f;
		}
	}

	//�\�[�g����
	useful::SortNum(pPos, NUM);

	for (int nCnt = 0; nCnt < NUM; nCnt++)
	{
		if (m_pSpot[nCnt] != nullptr)
		{
			if (m_pSpot[nCnt]->GetPosHeight() == pPos[0])
			{
				m_pSpot[nCnt]->Uninit();
				m_pSpot[nCnt] = nullptr;
				delete[] pPos;

				//���W�𐶐�
				SetSpot();

				return;
			}
		}
	}
}

//==========================================
//  ���W��������
//==========================================
void CMap::SetSpot(void)
{
	for (int nCntSpot = 0; nCntSpot < NUM; nCntSpot++)
	{
		if (m_pSpot[nCntSpot] == nullptr)
		{
			//����WY�̎擾
			float fHeight = (float)SCREEN_HEIGHT;

			//�f�[�^��ۊ�
			float* pPos = new float[NUM];
			for (int nCnt = 0; nCnt < NUM; nCnt++)
			{
				if (m_pSpot[nCnt] != nullptr)
				{
					pPos[nCnt] = m_pSpot[nCnt]->GetPosHeight();
				}
				else
				{
					pPos[nCnt] = (float)SCREEN_HEIGHT;
				}
			}

			//�\�[�g����
			useful::SortNum(pPos, NUM);

			fHeight = pPos[NUM - 1];
			delete[] pPos;

			//����WY�ɗ��������Z
			if (fHeight >= SCREEN_HEIGHT)
			{
				fHeight = SCREEN_HEIGHT - 100.0f;
			}
			else
			{
				fHeight -= (float)((rand() % (m_Diff.nMaxY + m_Diff.nMinY)) + m_Diff.nMinY);
			}

			//���WX�̗����𐶐�
			float fWidth = (float)((rand() % (m_Diff.nMaxX + m_Diff.nMinX)) + m_Diff.nMinX);

			//���W�𐶐�
			m_pSpot[nCntSpot] = CSpot::Create(D3DXVECTOR3(fWidth, fHeight, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f));
		}
	}
}
