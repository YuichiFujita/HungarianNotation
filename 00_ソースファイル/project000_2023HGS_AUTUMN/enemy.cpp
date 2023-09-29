//==========================================
//
//  �G�l�~�[�N���X(enemy.cpp)
//  Author : Riku Nakamura
//
//==========================================
#include "enemy.h"
#include "player.h"
#include "effect2D.h"
#include "input.h"
#include "objectGauge2D.h"
#include "manager.h"
#include "gameManager.h"
#include "debugproc.h"

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
	D3DXVECTOR3 rPos = GetPosition();
	D3DXVECTOR3 rSize = GetScaling();
	D3DXVECTOR3 rRot = GetRotation();

#ifdef _DEBUG
	if (CManager::GetKeyboard()->GetPress(DIK_I))
	{
		rPos += D3DXVECTOR3(0.0f, -2.0f, 0.0f);
	}
	if (CManager::GetKeyboard()->GetPress(DIK_K))
	{
		rPos += D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	}
	if (CManager::GetKeyboard()->GetPress(DIK_J))
	{
		rPos += D3DXVECTOR3(-2.0f, 0.0f, 0.0f);
	}
	if (CManager::GetKeyboard()->GetPress(DIK_L))
	{
		rPos += D3DXVECTOR3(2.0f, 0.0f, 0.0f);
	}

	if (CManager::GetKeyboard()->GetPress(DIK_U))
	{
		rRot += D3DXVECTOR3(0.0f, 0.0f, -0.01f);
	}
	if (CManager::GetKeyboard()->GetPress(DIK_O))
	{
		rRot += D3DXVECTOR3(0.0f, 0.0f, 0.01f);
	}
#endif

	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE) || CManager::GetPad()->GetTrigger(CInputPad::KEY_A) || CManager::GetMouse()->GetTrigger(CInputMouse::KEY_LEFT))
	{
		Collision(GetPosition(), GetScaling(), GetRotation());
	}

	SetPosition(rPos);
	SetScaling(rSize);
	SetRotation(rRot);

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
	D3DXVECTOR3 posCurrent;
	D3DXVECTOR3 posNext;
	D3DXVECTOR3 vecMove;

	D3DXVECTOR3 posEnd[2];

	//�v���C���[�̈ړ������擾
	CGameManager::GetPlayer()->GetVecInfo(&posCurrent, &posNext, &vecMove);

	//�ړ��x�N�g��
	vecMove = posNext - posCurrent;

	if (m_type == TYPE_STICK || m_type == TYPE_STICK_SLIDE)
	{
		float fLength = 0.0f;
		float fRate, fOutToPos, fOutToPosOld, fOutUnit, fOutRate;
		D3DXVECTOR3 vecLine, vecToPos, vecToPosOld;

		//�_�̒����̊�v�Z
		if (rSize.x > rSize.y)
		{
			fLength = rSize.x * 0.5f;
		}
		else
		{
			fLength = rSize.y * 0.5f;
		}

		//�_�̗��[�Z�o
		posEnd[0].x = rPos.x + fLength * cosf(-rRot.z);
		posEnd[0].y = rPos.y + fLength * sinf(-rRot.z);

		posEnd[1].x = rPos.x + fLength * cosf(-rRot.z + 3.1415f);
		posEnd[1].y = rPos.y + fLength * sinf(-rRot.z + 3.1415f);

#ifdef _DEBUG
		CEffect2D::Create
		(
			CEffect2D::TYPE_NORMAL,			// �e�N�X�`��
			posEnd[0],						// �ʒu
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �ړ���
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// ����
			XCOL_WHITE,						// �F
			1,								// ����
			10.0f,							// ���a
			0.0f,							// ���a�̌��Z��
			0.0f,							// �����x�̌��Z��
			CObject::LABEL_EFFECT2D			// �I�u�W�F�N�g���x��
		);

		CEffect2D::Create
		(
			CEffect2D::TYPE_NORMAL,			// �e�N�X�`��
			posEnd[1],						// �ʒu
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �ړ���
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// ����
			XCOL_WHITE,						// �F
			1,								// ����
			10.0f,							// ���a
			0.0f,							// ���a�̌��Z��
			0.0f,							// �����x�̌��Z��
			CObject::LABEL_EFFECT2D			// �I�u�W�F�N�g���x��
		);

		CEffect2D::Create
		(
			CEffect2D::TYPE_NORMAL,			// �e�N�X�`��
			posCurrent,						// �ʒu
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �ړ���
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// ����
			XCOL_WHITE,						// �F
			1,								// ����
			10.0f,							// ���a
			0.0f,							// ���a�̌��Z��
			0.0f,							// �����x�̌��Z��
			CObject::LABEL_EFFECT2D			// �I�u�W�F�N�g���x��
		);

		CEffect2D::Create
		(
			CEffect2D::TYPE_NORMAL,			// �e�N�X�`��
			posNext,						// �ʒu
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �ړ���
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// ����
			XCOL_WHITE,						// �F
			1,								// ����
			10.0f,							// ���a
			0.0f,							// ���a�̌��Z��
			0.0f,							// �����x�̌��Z��
			CObject::LABEL_EFFECT2D			// �I�u�W�F�N�g���x��
		);
#endif

		//��_�ƃv���C���[�̈ʒu�̃x�N�g��
		vecToPos.x = posNext.x - posEnd[1].x;
		vecToPos.y = posNext.y - posEnd[1].y;

		//��_�ƃv���C���[�̑O�̈ʒu�̃x�N�g��
		vecToPosOld.x = posCurrent.x - posEnd[1].x;
		vecToPosOld.y = posCurrent.y - posEnd[1].y;

		//�_�̃x�N�g��
		vecLine.x = posEnd[0].x - posEnd[1].x;
		vecLine.y = posEnd[0].y - posEnd[1].y; 

		//�_�ƃv���C���[�̈ʒu�̊O��
		fOutToPos = (vecLine.x * vecToPos.y) - (vecLine.y * vecToPos.x);
		fOutToPosOld = (vecLine.x * vecToPosOld.y) - (vecLine.y * vecToPosOld.x);

		//��_�v�Z
		fOutUnit = (vecLine.x * vecMove.y) - (vecLine.y * vecMove.x);
		fOutRate = (vecToPos.x * vecMove.y) - (vecToPos.y * vecMove.x);
		fRate = fOutRate / fOutUnit;

		//���ʏՓ˔���
		if (fOutToPos * fOutToPosOld < 0.0f && fRate < 1.0f && fRate > 0.0f)
		{//�ړ��x�N�g���Ɩ_�̃x�N�g���Ɍ�_�����鎞
			CManager::GetDebugProc()->Print("�����Ɠ������\n");
		}
		else
		{//�Ȃ����͒[�����ƈړ��x�N�g���̋��������߂�

			float rot[2], answer[2];
			D3DXVECTOR3 vec[2] = {};

			//�v���C���[�̈ʒu���痼�[�ւ̊p�x���Z�o
			rot[0] = atan2f((posEnd[0].x - posCurrent.x), (posEnd[0].y - posCurrent.y)) - atan2f((posNext.x - posCurrent.x), (posNext.y - posCurrent.y));
			rot[1] = atan2f((posEnd[1].x - posCurrent.x), (posEnd[1].y - posCurrent.y)) - atan2f((posNext.x - posCurrent.x), (posNext.y - posCurrent.y));

			//�p�x�␳
			if (rot[0] > D3DX_PI)
			{
				rot[0] -= (D3DX_PI * 2);
			}
			else if (rot[0] < -D3DX_PI)
			{
				rot[0] += (D3DX_PI * 2);
			}

			if (rot[1] > D3DX_PI)
			{
				rot[1] -= (D3DX_PI * 2);
			}
			else if (rot[1] < -D3DX_PI)
			{
				rot[1] += (D3DX_PI * 2);
			}

			//���[�ƃv���C���[�ʒu�̃x�N�g��
			vec[0] = posEnd[0] - posCurrent;
			vec[1] = posEnd[1] - posCurrent;

			//Z��0����
			vec[0].z = 0.0f;
			vec[1].z = 0.0f;

			//���[�ƈړ��x�N�g���̋������Z�o
			answer[0] = D3DXVec3Length(&vec[0]);
			answer[0] = answer[0] * sinf(rot[0]);
			answer[1] = D3DXVec3Length(&vec[1]);
			answer[1] = answer[1] * sinf(rot[1]);

			//�ړ��x�N�g���Ɨ��[�ւ̊p�x���s�p���݊p��
			if ((rot[0] < 1.57f && rot[0] > -1.57f) ||
				(rot[1] < 1.57f && rot[1] > -1.57f))
			{//�s�p�̎�

				//�����ɂ���ďՓ˂������肩����
				if ((answer[0] < 30.0f && answer[0] > -30.0f) || (answer[1] < 30.0f && answer[1] > -30.0f))
				{
					CManager::GetDebugProc()->Print("�[�����������\n");
				}
				else if ((answer[0] < 80.0f && answer[0] > -80.0f) || (answer[1] < 80.0f && answer[1] > -80.0f))
				{
					CGameManager::GetObjectGauge2D()->AddNum(1);

					if (CGameManager::GetObjectGauge2D()->GetNum() == 10)
					{
						CGameManager::GetObjectGauge2D()->SetNum(0);
					}
				}
			}
		}
	}
}