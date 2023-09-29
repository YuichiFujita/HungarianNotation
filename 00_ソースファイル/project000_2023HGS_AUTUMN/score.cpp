//============================================================
//
//	�X�R�A���� [score.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "score.h"
#include "manager.h"
#include "renderer.h"
#include "value.h"
#include "texture.h"

//************************************************************
//	�}�N����`
//************************************************************
#define SCORE_PRIO	(6)	// �X�R�A�̗D�揇��

#define SCO_NUMMIN	(0)			// �ŏ��X�R�A
#define SCO_NUMMAX	(99999999)	// �ő�X�R�A

//************************************************************
//	�q�N���X [CScore] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CScore::CScore() : CObject(CObject::LABEL_NUMBER, DEFAULT_PRIO)
{
	// �����o�ϐ����N���A
	memset(&m_apValue[0], 0, sizeof(m_apValue));	// ���l�̏��
	m_pUnit	= NULL;				// �P�ʂ̏��
	m_pos	= VEC3_ZERO;		// �ʒu
	m_sizeValue = VEC3_ZERO;	// �����̑傫��
	m_sizeUnit = VEC3_ZERO;		// �P�ʂ̑傫��
	m_spaceValue = VEC3_ZERO;	// �����̋�
	m_spaceUnit = VEC3_ZERO;	// �P�ʂ̋�
	m_nNum	= 0;				// �X�R�A
}

//============================================================
//	�f�X�g���N�^
//============================================================
CScore::~CScore()
{

}

//============================================================
//	����������
//============================================================
HRESULT CScore::Init(void)
{
	// �����o�ϐ���������
	memset(&m_apValue[0], 0, sizeof(m_apValue));	// ���l�̏��
	m_pUnit	= NULL;				// �P�ʂ̏��
	m_pos	= VEC3_ZERO;		// �ʒu
	m_sizeValue = VEC3_ZERO;	// �����̑傫��
	m_sizeUnit = VEC3_ZERO;		// �P�ʂ̑傫��
	m_spaceValue = VEC3_ZERO;	// �����̋�
	m_spaceUnit = VEC3_ZERO;	// �P�ʂ̋�
	m_nNum	= 0;				// �X�R�A

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{ // �X�R�A�̌������J��Ԃ�

		// �����̐���
		m_apValue[nCntScore] = CValue::Create(CValue::TEXTURE_MAGIC_GREEN);
		if (m_apValue[nCntScore] == NULL)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �D�揇�ʂ�ݒ�
		m_apValue[nCntScore]->SetPriority(SCORE_PRIO);
	}

	// �P�ʂ̐���
	m_pUnit = CObject2D::Create(VEC3_ZERO);
	if (m_pUnit == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pUnit->SetPriority(SCORE_PRIO);

	m_pUnit->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\unit000.png"));

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CScore::Uninit(void)
{
	// �����I�u�W�F�N�g��j��
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{ // �X�R�A�̌������J��Ԃ�

		// �����̏I��
		m_apValue[nCntScore]->Uninit();
	}

	// �P�ʂ̏I��
	m_pUnit->Uninit();

	// ���g�̃I�u�W�F�N�g��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CScore::Update(void)
{
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{ // �X�R�A�̌������J��Ԃ�

		// �����̍X�V
		m_apValue[nCntScore]->Update();
	}

	// �P�ʂ̍X�V
	m_pUnit->Update();
}

//============================================================
//	�`�揈��
//============================================================
void CScore::Draw(void)
{

}

//============================================================
//	��������
//============================================================
CScore *CScore::Create
(
	const D3DXVECTOR3& rPos,		// �ʒu
	const D3DXVECTOR3& rSizeValue,	// �����̑傫��
	const D3DXVECTOR3& rSizeUnit,	// �P�ʂ̑傫��
	const D3DXVECTOR3& rSpaceValue,	// �����̋�
	const D3DXVECTOR3& rSpaceUnit	// �P�ʂ̋�
)
{
	// �|�C���^��錾
	CScore *pScore = NULL;		// �X�R�A�����p

	if (pScore == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pScore = new CScore;	// �X�R�A
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pScore != NULL)
	{ // �m�ۂɐ������Ă���ꍇ

		// �X�R�A�̏�����
		if (FAILED(pScore->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pScore;
			pScore = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �ʒu��ݒ�
		pScore->SetPosition(rPos);

		// �傫����ݒ�
		pScore->SetScalingValue(rSizeValue);
		pScore->SetScalingUnit(rSizeUnit);

		// �󔒂�ݒ�
		pScore->SetSpaceValue(rSpaceValue);
		pScore->SetSpaceUnit(rSpaceUnit);

		// �m�ۂ����A�h���X��Ԃ�
		return pScore;
	}
	else { assert(false); return NULL; }	// �m�ێ��s
}

//============================================================
//	���Z����
//============================================================
void CScore::Add(const int nNum)
{
	// �X�R�A�����������Z
	m_nNum += nNum;

	// �X�R�A�̕␳
	useful::LimitNum(m_nNum, SCO_NUMMIN, SCO_NUMMAX);

	// �����̃e�N�X�`�����W�̐ݒ�
	SetTexNum();
}

//============================================================
//	�ݒ菈��
//============================================================
void CScore::Set(const int nNum)
{
	// �X�R�A�������̒l�ɐݒ�
	m_nNum = nNum;

	// �X�R�A�̕␳
	useful::LimitNum(m_nNum, SCO_NUMMIN, SCO_NUMMAX);

	// �����̃e�N�X�`�����W�̐ݒ�
	SetTexNum();
}

//============================================================
//	�擾����
//============================================================
int CScore::Get(void)
{
	// �X�R�A�̒l��Ԃ�
	return m_nNum;
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CScore::SetPosition(const D3DXVECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pos = rPos;

	// �����̕\���ݒ�
	SetDrawValue();

	// �P�ʂ̕\���ݒ�
	SetDrawUnit();
}

//============================================================
//	�����̑傫���ݒ菈��
//============================================================
void CScore::SetScalingValue(const D3DXVECTOR3& rSize)
{
	// �����̑傫����ݒ�
	m_sizeValue = rSize;

	// �����̕\���ݒ�
	SetDrawValue();
}

//============================================================
//	�P�ʂ̑傫���ݒ菈��
//============================================================
void CScore::SetScalingUnit(const D3DXVECTOR3& rSize)
{
	// �����̑傫����ݒ�
	m_sizeUnit = rSize;

	// �P�ʂ̕\���ݒ�
	SetDrawUnit();
}

//============================================================
//	�F�̐ݒ菈��
//============================================================
void CScore::SetColor(const D3DXCOLOR& rCol)
{
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{ // �����̑������J��Ԃ�

		// �����̐F��ݒ�
		m_apValue[nCntScore]->SetColor(rCol);
	}
}

//============================================================
//	�����̋󔒂̐ݒ菈��
//============================================================
void CScore::SetSpaceValue(const D3DXVECTOR3& rSpace)
{
	// �����̋󔒂�ݒ�
	m_spaceValue = rSpace;

	// �����̕\���ݒ�
	SetDrawValue();
}

//============================================================
//	�P�ʂ̋󔒂̐ݒ菈��
//============================================================
void CScore::SetSpaceUnit(const D3DXVECTOR3& rSpace)
{
	// �����̋󔒂�ݒ�
	m_spaceUnit = rSpace;

	// �P�ʂ̕\���ݒ�
	SetDrawUnit();
}

//============================================================
//	�D�揇�ʂ̐ݒ菈��
//============================================================
void CScore::SetPriority(const int nPriority)
{
	// ���g�̗D�揇�ʂ�ݒ�
	CObject::SetPriority(nPriority);

	if (m_apValue[0] != NULL)
	{ // �X�R�A�̐擪�̐��l���g�p����Ă���ꍇ

		// �����I�u�W�F�N�g�̗D�揇�ʂ�ݒ�
		for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{ // �X�R�A�̌������J��Ԃ�

			m_apValue[nCntScore]->SetPriority(nPriority);
		}
	}
	else { assert(false); }	// ��g�p��
}

//============================================================
//	�X�V�󋵂̐ݒ菈��
//============================================================
void CScore::SetEnableUpdate(const bool bUpdate)
{
	// ���g�̍X�V�󋵂�ݒ�
	CObject::SetEnableUpdate(bUpdate);

	if (m_apValue[0] != NULL)
	{ // �X�R�A�̐擪�̐��l���g�p����Ă���ꍇ

		// �����I�u�W�F�N�g�̍X�V�󋵂�ݒ�
		for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{ // �X�R�A�̌������J��Ԃ�

			m_apValue[nCntScore]->SetEnableUpdate(bUpdate);
		}
	}
	else { assert(false); }	// ��g�p��
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CScore::SetEnableDraw(const bool bDraw)
{
	// ���g�̕`��󋵂�ݒ�
	CObject::SetEnableDraw(bDraw);

	if (m_apValue[0] != NULL)
	{ // �X�R�A�̐擪�̐��l���g�p����Ă���ꍇ

		// �����I�u�W�F�N�g�̕`��󋵂�ݒ�
		for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{ // �X�R�A�̌������J��Ԃ�

			m_apValue[nCntScore]->SetEnableDraw(bDraw);
		}
	}
	else { assert(false); }	// ��g�p��

	m_pUnit->SetEnableDraw(bDraw);
}

//============================================================
//	�ʒu�擾����
//============================================================
D3DXVECTOR3 CScore::GetPosition(void) const
{
	// �ʒu��Ԃ�
	return m_pos;
}

//============================================================
//	�傫���擾����
//============================================================
D3DXVECTOR3 CScore::GetScaling(void) const
{
	// �傫����Ԃ�
	return m_sizeValue;
}

//============================================================
//	�󔒎擾����
//============================================================
D3DXVECTOR3 CScore::GetSpace(void) const
{
	// �󔒂�Ԃ�
	return m_spaceValue;
}

//============================================================
//	�P�ʂ̕\���ݒ菈��
//============================================================
void CScore::SetDrawUnit(void)
{
	if (m_apValue[0] != NULL)
	{ // �X�R�A�̐擪�̐��l���g�p����Ă���ꍇ

		// �P�ʂ̈ʒu��ݒ�
		m_pUnit->SetPosition(m_pos + m_spaceUnit);

		// �P�ʂ̑傫����ݒ�
		m_pUnit->SetScaling(m_sizeUnit);
	}
	else { assert(false); }	// ��g�p��
}

//============================================================
//	�����̕\���ݒ菈��
//============================================================
void CScore::SetDrawValue(void)
{
	if (m_apValue[0] != NULL)
	{ // �X�R�A�̐擪�̐��l���g�p����Ă���ꍇ

		for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{ // �X�R�A�̌������J��Ԃ�

			// �����̈ʒu��ݒ�
			m_apValue[nCntScore]->SetPosition(m_pos + (m_spaceValue * (float)nCntScore));

			// �����̑傫����ݒ�
			m_apValue[nCntScore]->SetScaling(m_sizeValue);
		}
	}
	else { assert(false); }	// ��g�p��
}

//============================================================
//	�����̃e�N�X�`�����W�̐ݒ菈��
//============================================================
void CScore::SetTexNum(void)
{
	// �ϐ���錾
	int aNumDivide[MAX_SCORE];	// �������Ƃ̕���p

	// �X�R�A���������Ƃɕ���
	useful::DivideDigitNum
	( // ����
		&aNumDivide[0],	// �������ʂ̊i�[�z��
		m_nNum,			// �������鐔�l
		MAX_SCORE		// �������鐔���̌���
	);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{ // �X�R�A�̌������J��Ԃ�

		// �����̐ݒ�
		m_apValue[nCntScore]->SetNumber(aNumDivide[nCntScore]);
	}
}
