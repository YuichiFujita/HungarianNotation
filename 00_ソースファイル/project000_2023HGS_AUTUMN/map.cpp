//==========================================
//
//  �}�b�v�N���X(map.cpp)
//  Autho : Tomoya Kanazaki
//
//==========================================
#include "map.h"
#include "spot.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const CMap::DIFF CMap::m_Diff = { 100, 500, 50, SCREEN_WIDTH - 50 };

//==========================================
//  �R���X�g���N�^
//==========================================
CMap::CMap()
{
	m_vecMove = 0.0f;
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
	}
}

//==========================================
//  �X�V����
//==========================================
void CMap::Update(void)
{
	//���W�𐶐�
	SetSpot();
}

//==========================================
//  �`�揈��
//==========================================
void CMap::Draw(void)
{

}

//==========================================
//  ���W��������
//==========================================
void CMap::SetSpot(void)
{
	for (int nCnt = 0; nCnt < NUM; nCnt++)
	{
		if (m_pSpot[nCnt] == nullptr)
		{
			//����WY�̎擾
			float fHeight = (float)SCREEN_HEIGHT;
			if (nCnt != 0 && m_pSpot[nCnt - 1] != nullptr) //�ŏ��̃A�h���X�łȂ� ���� �ЂƂO��null����Ȃ�
			{
				fHeight = m_pSpot[nCnt - 1]->GetPosHight(); //1�O�̍��W���擾
			}
			else if (nCnt == 0) //�ŏ��̃A�h���X
			{
				if (m_pSpot[NUM - 1] != nullptr) //��ԍŌオnull����Ȃ�
				{
					fHeight = m_pSpot[NUM - 1]->GetPosHight(); //��ԍŌ�̍��W���擾
				}
			}

			//����WY�ɗ��������Z
			fHeight -= (float)((rand() % (m_Diff.nMaxY + m_Diff.nMinY)) + m_Diff.nMinY);

			//���WX�̗����𐶐�
			float fWidth = (float)((rand() % (m_Diff.nMaxX + m_Diff.nMinX)) + m_Diff.nMinX);

			//���W�𐶐�
			m_pSpot[nCnt] = CSpot::Create(D3DXVECTOR3(fWidth, fHeight, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f));
		}
	}
}
