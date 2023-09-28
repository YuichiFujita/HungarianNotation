//============================================================
//
//	�v���C���[���� [player.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "player.h"
#include "manager.h"
#include "scene.h"
#include "sceneGame.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "camera.h"
#include "texture.h"
#include "collision.h"

#include "multiModel.h"
#include "objectGauge3D.h"
#include "shadow.h"
#include "stage.h"
#include "field.h"

//************************************************************
//	�}�N����`
//************************************************************
// �Z�b�g�A�b�v�e�L�X�g���΃p�X
#define PLAYER_SETUP_TXT	"data\\TXT\\player.txt"

// �v���C���[��{���
#define MAX_LIFE	(100)	// �v���C���[�ő�̗�
#define JUMP_REV	(0.08f)	// �󒆂̃v���C���[�ړ��ʂ̌����W��
#define LAND_REV	(0.2f)	// �n��̃v���C���[�ړ��ʂ̌����W��
#define REV_ROTA	(0.15f)	// �v���C���[�����ύX�̌����W��
#define JUMP		(20.0f)	// �v���C���[�W�����v��
#define GRAVITY		(1.0f)	// �v���C���[�d��
#define RADIUS		(20.0f)	// �v���C���[���a

// �v���C���[���N���X���
#define SHADOW_SIZE	(D3DXVECTOR3(80.0f, 0.0f, 80.0f))	// �e�̑傫��

#define GAUGE_CHANGE_FRAME	(6)			// �̗͕ϓ��t���[��
#define GAUGE_PLUS_Y		(140.0f)	// �̗̓Q�[�WY�ʒu���Z��
#define GAUGE_GAUGESIZE		(D3DXVECTOR3(110.0f, 15.0f, 0.0f))	// �Q�[�W�傫��
#define GAUGE_FRONTCOL		(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))	// �\�Q�[�W�F
#define GAUGE_BACKCOL		(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))	// ���Q�[�W�F

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
const char *CPlayer::mc_apModelFile[] =	// ���f���萔
{
	"data\\MODEL\\PLAYER\\00_waist.x",	// ��
	"data\\MODEL\\PLAYER\\01_body.x",	// ��
	"data\\MODEL\\PLAYER\\02_cloak.x",	// �}���g
	"data\\MODEL\\PLAYER\\03_head.x",	// ��
	"data\\MODEL\\PLAYER\\04_hat.x",	// �X�q
	"data\\MODEL\\PLAYER\\05_armUL.x",	// ����r
	"data\\MODEL\\PLAYER\\06_armUR.x",	// �E��r
	"data\\MODEL\\PLAYER\\07_armDL.x",	// �����r
	"data\\MODEL\\PLAYER\\08_armDR.x",	// �E���r
	"data\\MODEL\\PLAYER\\09_handL.x",	// ����
	"data\\MODEL\\PLAYER\\10_handR.x",	// �E��
	"data\\MODEL\\PLAYER\\11_legUL.x",	// ��������
	"data\\MODEL\\PLAYER\\12_legUR.x",	// �E������
	"data\\MODEL\\PLAYER\\13_legDL.x",	// ����
	"data\\MODEL\\PLAYER\\14_legDR.x",	// �E��
	"data\\MODEL\\PLAYER\\15_footL.x",	// ����
	"data\\MODEL\\PLAYER\\16_footR.x",	// �E��
	"data\\MODEL\\PLAYER\\17_rod.x",	// ��
};

//************************************************************
//	�q�N���X [CPlayer] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CPlayer::CPlayer() : CObjectChara(CObject::LABEL_PLAYER)
{
	// �����o�ϐ����N���A
	m_pLife			= NULL;			// �̗͂̏��
	m_pShadow		= NULL;			// �e�̏��
	m_oldPos		= VEC3_ZERO;	// �ߋ��ʒu
	m_move			= VEC3_ZERO;	// �ړ���
	m_destRot		= VEC3_ZERO;	// �ڕW����
	m_state			= STATE_NONE;	// ���
	m_nCounterState	= 0;			// ��ԊǗ��J�E���^�[
	m_nNumModel		= 0;			// �p�[�c�̑���
	m_bJump			= false;		// �W�����v��
}

//============================================================
//	�f�X�g���N�^
//============================================================
CPlayer::~CPlayer()
{

}

//============================================================
//	����������
//============================================================
HRESULT CPlayer::Init(void)
{
	// �|�C���^��錾
	CTexture *pTexture = CManager::GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �����o�ϐ���������
	m_pLife			= NULL;			// �̗͂̏��
	m_pShadow		= NULL;			// �e�̏��
	m_oldPos		= VEC3_ZERO;	// �ߋ��ʒu
	m_move			= VEC3_ZERO;	// �ړ���
	m_destRot		= VEC3_ZERO;	// �ڕW����
	m_state			= STATE_NORMAL;	// ���
	m_nCounterState	= 0;			// ��ԊǗ��J�E���^�[
	m_nNumModel		= 0;			// �p�[�c�̑���
	m_bJump			= true;			// �W�����v��

	// �I�u�W�F�N�g�L�����N�^�[�̏�����
	if (FAILED(CObjectChara::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �Z�b�g�A�b�v�̓ǂݍ���
	LoadSetup();

	// ���f�����̐ݒ�
	SetModelInfo();

	// �̗͂̐���
	m_pLife = CObjectGauge3D::Create
	( // ����
		CObject::LABEL_GAUGE,			// �I�u�W�F�N�g���x��
		this,							// �Q�[�W�\���I�u�W�F�N�g
		MAX_LIFE,						// �ő�\���l
		GAUGE_CHANGE_FRAME,				// �\���l�ϓ��t���[��
		GAUGE_PLUS_Y,					// �\��Y�ʒu�̉��Z��
		GAUGE_GAUGESIZE,				// �Q�[�W�傫��
		GAUGE_FRONTCOL,					// �\�Q�[�W�F
		GAUGE_BACKCOL,					// ���Q�[�W�F
		true,							// �g�`���
		CObjectGauge3D::TYPE_PLAYER,	// �g���
		GAUGE_GAUGESIZE					// �g�傫��
	);
	if (UNUSED(m_pLife))
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �e�̐���
	m_pShadow = CShadow::Create(CShadow::TEXTURE_NORMAL, SHADOW_SIZE, this);
	if (UNUSED(m_pShadow))
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���[�V�����̐ݒ�
	SetMotion(MOTION_MOVE);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CPlayer::Uninit(void)
{
	// �e��j��
	m_pShadow->Uninit();

	// �I�u�W�F�N�g�L�����N�^�[�̏I��
	CObjectChara::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CPlayer::Update(void)
{
	// �ϐ���錾
	MOTION currentMotion = MOTION_MOVE;		// ���݂̃��[�V����

	// �ߋ��ʒu�̍X�V
	UpdateOldPosition();

	switch (m_state)
	{ // ��Ԃ��Ƃ̏���
	case STATE_NONE:
		break;

	case STATE_NORMAL:

		// �ʏ��Ԃ̍X�V
		currentMotion = UpdateNormal();

		break;

	case STATE_DEATH:
		break;

	default:
		assert(false);
		break;
	}

	// �e�̍X�V
	m_pShadow->Update();

	// ���[�V�����E�I�u�W�F�N�g�L�����N�^�[�̍X�V
	UpdateMotion(currentMotion);
}

//============================================================
//	�`�揈��
//============================================================
void CPlayer::Draw(void)
{
	// �I�u�W�F�N�g�L�����N�^�[�̕`��
	CObjectChara::Draw();
}

//============================================================
//	�q�b�g����
//============================================================
void CPlayer::Hit(const int nDmg)
{

#if 0	// TODO�FHit����

	// �ϐ���錾
	D3DXVECTOR3 pos = GetPosition();	// �v���C���[�ʒu

	if (IsDeath() != true)
	{ // ���S�t���O�������Ă��Ȃ��ꍇ

		if (m_state == STATE_NORMAL)
		{ // �ʏ��Ԃ̏ꍇ

			// �̗͂���_���[�W�����Z
			m_pLife->AddNum(-nDmg);

			if (m_pLife->GetNum() > 0)
			{ // �����Ă���ꍇ

				// �J�E���^�[��������
				m_nCounterState = 0;

				// ��Ԃ�ύX
				m_state = STATE_DAMAGE;	// �_���[�W���
			}
			else
			{ // ����ł���ꍇ

				// �J�E���^�[��������
				m_nCounterState = 0;

				// ��Ԃ�ύX
				m_state = STATE_DEATH;	// ���S���

				// ���[�V�����̐ݒ�
				SetMotion(MOTION_DEATH);	// ���S���[�V����

				// �T�E���h�̍Đ�
				CManager::GetSound()->Play(CSound::LABEL_SE_BREAK);	// �j��
			}
		}
	}

#endif

}

//============================================================
//	��������
//============================================================
CPlayer *CPlayer::Create
(
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXVECTOR3& rRot		// ����
)
{
	// �ϐ���錾
	D3DXVECTOR3 pos = rPos;		// ���W�ݒ�p

	// �|�C���^��錾
	CPlayer *pPlayer = NULL;	// �v���C���[�����p

	if (UNUSED(pPlayer))
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pPlayer = new CPlayer;	// �v���C���[
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pPlayer != NULL)
	{ // �g�p����Ă���ꍇ

		// �v���C���[�̏�����
		if (FAILED(pPlayer->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pPlayer;
			pPlayer = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �ʒu��ݒ�
		CScene::GetStage()->LimitPosition(pos, RADIUS);		// �X�e�[�W�͈͓��␳
		pos.y = CScene::GetField()->GetPositionHeight(pos);	// ������n�ʂɐݒ�
		pPlayer->SetPosition(pos);

		// ������ݒ�
		pPlayer->SetRotation(rRot);
	}

	// �m�ۂ����A�h���X��Ԃ�
	return pPlayer;
}

//============================================================
//	��Ԃ̐ݒ菈��
//============================================================
void CPlayer::SetState(const int nState)
{
	// �����̏�Ԃ�ݒ�
	m_state = (STATE)nState;
}

//============================================================
//	�X�V�󋵂̐ݒ菈��
//============================================================
void CPlayer::SetEnableUpdate(const bool bUpdate)
{
	// �����̍X�V�󋵂�ݒ�
	CObject::SetEnableUpdate(bUpdate);		// ���g
	m_pShadow->SetEnableUpdate(bUpdate);	// �e
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CPlayer::SetEnableDraw(const bool bDraw)
{
	// �����̕`��󋵂�ݒ�
	CObject::SetEnableDraw(bDraw);		// ���g
	m_pShadow->SetEnableDraw(bDraw);	// �e
}

//============================================================
//	�̗͂̕`��󋵂̐ݒ菈��
//============================================================
void CPlayer::SetEnableDrawLife(const bool bDraw)
{
	// �����̕`��󋵂�̗͂ɐݒ�
	m_pLife->SetEnableDraw(bDraw);
}

//============================================================
//	�}�g���b�N�X�擾����
//============================================================
D3DXMATRIX CPlayer::GetMtxWorld(void) const
{
	// �ϐ���錾
	D3DXMATRIX  mtxRot, mtxTrans, mtxWorld;	// �v�Z�p�}�g���b�N�X
	D3DXVECTOR3 posPlayer = GetPosition();	// �v���C���[�ʒu
	D3DXVECTOR3 rotPlayer = GetRotation();	// �v���C���[����

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotPlayer.y, rotPlayer.x, rotPlayer.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, posPlayer.x, posPlayer.y, posPlayer.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X��Ԃ�
	return mtxWorld;
}

//============================================================
//	�̗͎擾����
//============================================================
int CPlayer::GetLife(void) const
{
	// �̗͂�Ԃ�
	return m_pLife->GetNum();
}

//============================================================
//	�ő�̗͎擾����
//============================================================
int CPlayer::GetMaxLife(void) const
{
	// �ő�̗͂�Ԃ�
	return m_pLife->GetMaxNum();
}

//============================================================
//	��Ԏ擾����
//============================================================
int CPlayer::GetState(void) const
{
	// ��Ԃ�Ԃ�
	return m_state;
}

//============================================================
//	���a�擾����
//============================================================
float CPlayer::GetRadius(void) const
{
	// ���a��Ԃ�
	return RADIUS;
}

//============================================================
//	�ߋ��ʒu�̍X�V����
//============================================================
void CPlayer::UpdateOldPosition(void)
{
	// �ߋ��ʒu���X�V
	m_oldPos = GetPosition();
}

//============================================================
//	�ړ��ʁE�ڕW�����̍X�V����
//============================================================
CPlayer::MOTION CPlayer::UpdateMove(void)
{
	// �ϐ���錾
	D3DXVECTOR3 rotCamera = CManager::GetCamera()->GetRotation();	// �J�����̌���

	// �|�C���^��錾
	CInputKeyboard	*pKeyboard	= CManager::GetKeyboard();	// �L�[�{�[�h
	CInputPad		*pPad		= CManager::GetPad();		// �p�b�h

	if (pKeyboard->GetPress(DIK_W))
	{ // ���ړ��̑��삪�s��ꂽ�ꍇ

		if (pKeyboard->GetPress(DIK_A))
		{ // ���ړ��̑�����s��ꂽ�ꍇ (�����ړ�)

			// �ړ��ʂ��X�V
			m_move.x += sinf(rotCamera.y - (D3DX_PI * 0.25f)) * 2.0f;
			m_move.z += cosf(rotCamera.y - (D3DX_PI * 0.25f)) * 2.0f;

			// �ڕW�������X�V
			m_destRot.y = D3DXToRadian(135) + rotCamera.y;
		}
		else if (pKeyboard->GetPress(DIK_D))
		{ // �E�ړ��̑�����s��ꂽ�ꍇ (�E���ړ�)

			// �ړ��ʂ��X�V
			m_move.x -= sinf(rotCamera.y - (D3DX_PI * 0.75f)) * 2.0f;
			m_move.z -= cosf(rotCamera.y - (D3DX_PI * 0.75f)) * 2.0f;

			// �ڕW�������X�V
			m_destRot.y = D3DXToRadian(225) + rotCamera.y;
		}
		else
		{ // ���ړ��̑��삾�����s��ꂽ�ꍇ (���ړ�)

			// �ړ��ʂ��X�V
			m_move.x += sinf(rotCamera.y) * 2.0f;
			m_move.z += cosf(rotCamera.y) * 2.0f;

			// �ڕW�������X�V
			m_destRot.y = D3DXToRadian(180) + rotCamera.y;
		}
	}
	else if (pKeyboard->GetPress(DIK_S))
	{ // ��O�ړ��̑��삪�s��ꂽ�ꍇ

		if (pKeyboard->GetPress(DIK_A))
		{ // ���ړ��̑�����s��ꂽ�ꍇ (����O�ړ�)

			// �ړ��ʂ��X�V
			m_move.x += sinf(rotCamera.y - (D3DX_PI * 0.75f)) * 2.0f;
			m_move.z += cosf(rotCamera.y - (D3DX_PI * 0.75f)) * 2.0f;

			// �ڕW�������X�V
			m_destRot.y = D3DXToRadian(45) + rotCamera.y;
		}
		else if (pKeyboard->GetPress(DIK_D))
		{ // �E�ړ��̑�����s��ꂽ�ꍇ (�E��O�ړ�)

			// �ړ��ʂ��X�V
			m_move.x -= sinf(rotCamera.y - (D3DX_PI * 0.25f)) * 2.0f;
			m_move.z -= cosf(rotCamera.y - (D3DX_PI * 0.25f)) * 2.0f;

			// �ڕW�������X�V
			m_destRot.y = D3DXToRadian(315) + rotCamera.y;
		}
		else
		{ // ��O�ړ��̑��삾�����s��ꂽ�ꍇ (��O�ړ�)

			// �ړ��ʂ��X�V
			m_move.x -= sinf(rotCamera.y) * 2.0f;
			m_move.z -= cosf(rotCamera.y) * 2.0f;

			// �ڕW�������X�V
			m_destRot.y = D3DXToRadian(0) + rotCamera.y;
		}
	}
	else if (pKeyboard->GetPress(DIK_A))
	{ // ���ړ��̑��삪�s��ꂽ�ꍇ

		// �ړ��ʂ��X�V
		m_move.x += sinf(rotCamera.y - (D3DX_PI * 0.5f)) * 2.0f;
		m_move.z += cosf(rotCamera.y - (D3DX_PI * 0.5f)) * 2.0f;

		// �ڕW�������X�V
		m_destRot.y = D3DXToRadian(90) + rotCamera.y;
	}
	else if (pKeyboard->GetPress(DIK_D))
	{ // �E�ړ��̑��삪�s��ꂽ�ꍇ

		// �ړ��ʂ��X�V
		m_move.x -= sinf(rotCamera.y - (D3DX_PI * 0.5f)) * 2.0f;
		m_move.z -= cosf(rotCamera.y - (D3DX_PI * 0.5f)) * 2.0f;

		// �ڕW�������X�V
		m_destRot.y = D3DXToRadian(270) + rotCamera.y;
	}

	// ���V���[�V������Ԃ�
	return MOTION_MOVE;
}

//============================================================
//	�W�����v�̍X�V����
//============================================================
void CPlayer::UpdateJump(void)
{
	// �|�C���^��錾
	CInputKeyboard	*pKeyboard = CManager::GetKeyboard();	// �L�[�{�[�h
	CInputPad		*pPad = CManager::GetPad();				// �p�b�h

	if (m_bJump == false)
	{ // �W�����v���Ă��Ȃ��ꍇ

		if (pKeyboard->GetTrigger(DIK_SPACE))
		{ // �W�����v�̑��삪�s��ꂽ�ꍇ

			// ��ړ���
			m_move.y += JUMP;

			// �W�����v���Ă����Ԃɂ���
			m_bJump = true;
		}
	}
}

//============================================================
//	���n�󋵂̍X�V����
//============================================================
bool CPlayer::UpdateLanding(D3DXVECTOR3& rPos)
{
	// �ϐ���錾
	bool bLand = false;	// ���n��

	// ���n����
	if (CScene::GetField()->LandPosition(rPos, m_move)
	||  CScene::GetStage()->LandPosition(rPos, m_move, 0.0f))
	{ // �v���C���[�����n���Ă����ꍇ

		// ���n���Ă����Ԃɂ���
		bLand = true;

		// �W�����v���Ă��Ȃ���Ԃɂ���
		m_bJump = false;
	}
	else
	{ // ���n���Ă��Ȃ��ꍇ

		// �W�����v���Ă����Ԃɂ���
		m_bJump = true;
	}

	// ���n�󋵂�Ԃ�
	return bLand;
}

//============================================================
//	�ʒu�̍X�V����
//============================================================
void CPlayer::UpdatePosition(D3DXVECTOR3& rPos)
{
	// �d�͂����Z
	m_move.y -= GRAVITY;

	// �ړ��ʂ����Z
	rPos += m_move;

	// �ړ��ʂ�����
	if (m_bJump)
	{ // �󒆂̏ꍇ

		m_move.x += (0.0f - m_move.x) * JUMP_REV;
		m_move.z += (0.0f - m_move.z) * JUMP_REV;
	}
	else
	{ // �n��̏ꍇ

		m_move.x += (0.0f - m_move.x) * LAND_REV;
		m_move.z += (0.0f - m_move.z) * LAND_REV;
	}
}

//============================================================
//	�����̍X�V����
//============================================================
void CPlayer::UpdateRotation(D3DXVECTOR3& rRot)
{
	// �ϐ���錾
	float fDiffRot = 0.0f;	// ��������

	// �ڕW�����̐��K��
	useful::NormalizeRot(m_destRot.y);

	// �ڕW�����܂ł̍������v�Z
	fDiffRot = m_destRot.y - rRot.y;

	// ���������̐��K��
	useful::NormalizeRot(fDiffRot);

	// �����̍X�V
	rRot.y += fDiffRot * REV_ROTA;

	// �����̐��K��
	useful::NormalizeRot(rRot.y);
}

//============================================================
//	���[�V�����E�I�u�W�F�N�g�L�����N�^�[�̍X�V����
//============================================================
void CPlayer::UpdateMotion(int nMotion)
{
	// �ϐ���錾
	int nAnimMotion = GetMotionType();	// ���ݍĐ����̃��[�V����

	if (nMotion != NONE_IDX)
	{ // ���[�V�������ݒ肳��Ă���ꍇ

		if (IsMotionLoop(nAnimMotion))
		{ // ���[�v���郂�[�V�����������ꍇ

			if (nAnimMotion != nMotion)
			{ // ���݂̃��[�V�������Đ����̃��[�V�����ƈ�v���Ȃ��ꍇ

				// ���݂̃��[�V�����̐ݒ�
				SetMotion(nMotion);
			}
		}
	}

	// �I�u�W�F�N�g�L�����N�^�[�̍X�V
	CObjectChara::Update();

	// ���[�V�����̑J��
	if (IsMotionFinish())
	{ // ���[�V�������I�����Ă����ꍇ

		switch (GetMotionType())
		{ // ���[�V�����̎�ނ��Ƃ̏���
		case MOTION_BLOW_AWAY:	// ������я��

			// ����

			// �����𔲂���
			break;
		}
	}
}

//============================================================
//	�ʏ��Ԏ��̍X�V����
//============================================================
CPlayer::MOTION CPlayer::UpdateNormal(void)
{
	// �ϐ���錾
	MOTION currentMotion = MOTION_MOVE;		// ���݂̃��[�V����
	D3DXVECTOR3 posPlayer = GetPosition();	// �v���C���[�ʒu
	D3DXVECTOR3 rotPlayer = GetRotation();	// �v���C���[����

	// �|�C���^��錾
	CStage *pStage = CScene::GetStage();	// �X�e�[�W���

	if (pStage != NULL)
	{ // �X�e�[�W���g�p����Ă���ꍇ

		// �ړ�����
		currentMotion = UpdateMove();

		// �W�����v����
		UpdateJump();

		// �����X�V
		UpdateRotation(rotPlayer);

		// �ʒu�X�V
		UpdatePosition(posPlayer);

		// �X�e�[�W�͈͊O�̕␳
		pStage->LimitPosition(posPlayer, RADIUS);

		// ���n����
		UpdateLanding(posPlayer);
	}
	else { assert(false); return currentMotion; }	// ��g�p��

	// �ʒu���X�V
	SetPosition(posPlayer);

	// �������X�V
	SetRotation(rotPlayer);

	// ���݂̃��[�V������Ԃ�
	return currentMotion;
}

//============================================================
//	�Z�b�g�A�b�v����
//============================================================
void CPlayer::LoadSetup(void)
{
	// �ϐ���錾
	CMotion::MotionInfo info;		// �|�[�Y�̑���p
	D3DXVECTOR3 pos = VEC3_ZERO;	// �ʒu�̑���p
	D3DXVECTOR3 rot = VEC3_ZERO;	// �����̑���p
	int nLevel		= 0;	// ���x���̑���p
	int nID			= 0;	// �C���f�b�N�X�̑���p
	int nParentID	= 0;	// �e�C���f�b�N�X�̑���p
	int nNowPose	= 0;	// ���݂̃|�[�Y�ԍ�
	int nNowKey		= 0;	// ���݂̃L�[�ԍ�
	int nLoop		= 0;	// ���[�v��ON/OFF�̕ϊ��p
	int nEnd		= 0;	// �e�L�X�g�ǂݍ��ݏI���̊m�F�p

	// �ϐ��z���錾
	char aString[MAX_STRING];	// �e�L�X�g�̕�����̑���p

	// �|�C���^��錾
	FILE *pFile;	// �t�@�C���|�C���^

	// �|�[�Y����p�̕ϐ���������
	memset(&info, 0, sizeof(info));

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(PLAYER_SETUP_TXT, "r");

	if (pFile != NULL)
	{ // �t�@�C�����J�����ꍇ

		do
		{ // �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

			// �t�@�C�����當�����ǂݍ���
			nEnd = fscanf(pFile, "%s", &aString[0]);	// �e�L�X�g��ǂݍ��݂������� EOF ��Ԃ�

			// �L�����N�^�[�̐ݒ�
			if (strcmp(&aString[0], "CHARACTERSET") == 0)
			{ // �ǂݍ��񂾕����� CHARACTERSET �̏ꍇ

				do
				{ // �ǂݍ��񂾕����� END_CHARACTERSET �ł͂Ȃ��ꍇ���[�v

					// �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "PARTSSET") == 0)
					{ // �ǂݍ��񂾕����� PARTSSET �̏ꍇ

						do
						{ // �ǂݍ��񂾕����� END_PARTSSET �ł͂Ȃ��ꍇ���[�v

							// �t�@�C�����當�����ǂݍ���
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "INDEX") == 0)
							{ // �ǂݍ��񂾕����� INDEX �̏ꍇ

								fscanf(pFile, "%s", &aString[0]);	// = ��ǂݍ��� (�s�v)
								fscanf(pFile, "%d", &nID);			// ���f���̃C���f�b�N�X��ǂݍ���
							}
							else if (strcmp(&aString[0], "PARENT") == 0)
							{ // �ǂݍ��񂾕����� PARENT �̏ꍇ

								fscanf(pFile, "%s", &aString[0]);	// = ��ǂݍ��� (�s�v)
								fscanf(pFile, "%d", &nParentID);	// ���f���̐e�̃C���f�b�N�X��ǂݍ���
							}
							else if (strcmp(&aString[0], "POS") == 0)
							{ // �ǂݍ��񂾕����� POS �̏ꍇ

								fscanf(pFile, "%s", &aString[0]);	// = ��ǂݍ��� (�s�v)
								fscanf(pFile, "%f", &pos.x);		// X���W��ǂݍ���
								fscanf(pFile, "%f", &pos.y);		// Y���W��ǂݍ���
								fscanf(pFile, "%f", &pos.z);		// Z���W��ǂݍ���
							}
							else if (strcmp(&aString[0], "ROT") == 0)
							{ // �ǂݍ��񂾕����� ROT �̏ꍇ

								fscanf(pFile, "%s", &aString[0]);	// = ��ǂݍ��� (�s�v)
								fscanf(pFile, "%f", &rot.x);		// X������ǂݍ���
								fscanf(pFile, "%f", &rot.y);		// Y������ǂݍ���
								fscanf(pFile, "%f", &rot.z);		// Z������ǂݍ���
							}
						} while (strcmp(&aString[0], "END_PARTSSET") != 0);	// �ǂݍ��񂾕����� END_PARTSSET �ł͂Ȃ��ꍇ���[�v

						// �p�[�c���̐ݒ�
						CObjectChara::SetPartsInfo(nID, nParentID, pos, rot, mc_apModelFile[nID]);
					}
				} while (strcmp(&aString[0], "END_CHARACTERSET") != 0);		// �ǂݍ��񂾕����� END_CHARACTERSET �ł͂Ȃ��ꍇ���[�v
			}

			// ���[�V�����̐ݒ�
			else if (strcmp(&aString[0], "MOTIONSET") == 0)
			{ // �ǂݍ��񂾕����� MOTIONSET �̏ꍇ

				// ���݂̃|�[�Y�ԍ���������
				nNowPose = 0;

				do
				{ // �ǂݍ��񂾕����� END_MOTIONSET �ł͂Ȃ��ꍇ���[�v

					// �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "LOOP") == 0)
					{ // �ǂݍ��񂾕����� LOOP �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);	// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d", &nLoop);		// ���[�v��ON/OFF��ǂݍ���

						// �ǂݍ��񂾒l��bool�^�ɕϊ�
						info.bLoop = (nLoop == 0) ? false : true;
					}
					else if (strcmp(&aString[0], "NUM_KEY") == 0)
					{ // �ǂݍ��񂾕����� NUM_KEY �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);	// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d", &info.nNumKey);	// �L�[�̑�����ǂݍ���
					}
					else if (strcmp(&aString[0], "KEYSET") == 0)
					{ // �ǂݍ��񂾕����� KEYSET �̏ꍇ

						// ���݂̃L�[�ԍ���������
						nNowKey = 0;

						do
						{ // �ǂݍ��񂾕����� END_KEYSET �ł͂Ȃ��ꍇ���[�v

							// �t�@�C�����當�����ǂݍ���
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "FRAME") == 0)
							{ // �ǂݍ��񂾕����� FRAME �̏ꍇ

								fscanf(pFile, "%s", &aString[0]);						// = ��ǂݍ��� (�s�v)
								fscanf(pFile, "%d", &info.aKeyInfo[nNowPose].nFrame);	// �L�[���؂�ւ��܂ł̃t���[������ǂݍ���
							}
							else if (strcmp(&aString[0], "KEY") == 0)
							{ // �ǂݍ��񂾕����� KEY �̏ꍇ

								do
								{ // �ǂݍ��񂾕����� END_KEY �ł͂Ȃ��ꍇ���[�v

									// �t�@�C�����當�����ǂݍ���
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(&aString[0], "POS") == 0)
									{ // �ǂݍ��񂾕����� POS �̏ꍇ

										fscanf(pFile, "%s", &aString[0]);									// = ��ǂݍ��� (�s�v)
										fscanf(pFile, "%f", &info.aKeyInfo[nNowPose].aKey[nNowKey].pos.x);	// X�ʒu��ǂݍ���
										fscanf(pFile, "%f", &info.aKeyInfo[nNowPose].aKey[nNowKey].pos.y);	// Y�ʒu��ǂݍ���
										fscanf(pFile, "%f", &info.aKeyInfo[nNowPose].aKey[nNowKey].pos.z);	// Z�ʒu��ǂݍ���

										// �ǂݍ��񂾈ʒu�Ƀp�[�c�̏����ʒu�����Z
										info.aKeyInfo[nNowPose].aKey[nNowKey].pos += GetPartsPosition(nNowKey);
									}
									else if (strcmp(&aString[0], "ROT") == 0)
									{ // �ǂݍ��񂾕����� ROT �̏ꍇ

										fscanf(pFile, "%s", &aString[0]);									// = ��ǂݍ��� (�s�v)
										fscanf(pFile, "%f", &info.aKeyInfo[nNowPose].aKey[nNowKey].rot.x);	// X������ǂݍ���
										fscanf(pFile, "%f", &info.aKeyInfo[nNowPose].aKey[nNowKey].rot.y);	// Y������ǂݍ���
										fscanf(pFile, "%f", &info.aKeyInfo[nNowPose].aKey[nNowKey].rot.z);	// Z������ǂݍ���

										// �ǂݍ��񂾌����Ƀp�[�c�̏������������Z
										info.aKeyInfo[nNowPose].aKey[nNowKey].rot += GetPartsRotation(nNowKey);

										// ���������𐳋K��
										useful::NormalizeRot(info.aKeyInfo[nNowPose].aKey[nNowKey].rot.x);
										useful::NormalizeRot(info.aKeyInfo[nNowPose].aKey[nNowKey].rot.y);
										useful::NormalizeRot(info.aKeyInfo[nNowPose].aKey[nNowKey].rot.z);
									}

								} while (strcmp(&aString[0], "END_KEY") != 0);	// �ǂݍ��񂾕����� END_KEY �ł͂Ȃ��ꍇ���[�v

								// ���݂̃L�[�ԍ������Z
								nNowKey++;
							}
						} while (strcmp(&aString[0], "END_KEYSET") != 0);	// �ǂݍ��񂾕����� END_KEYSET �ł͂Ȃ��ꍇ���[�v

						// ���݂̃|�[�Y�ԍ������Z
						nNowPose++;
					}
				} while (strcmp(&aString[0], "END_MOTIONSET") != 0);	// �ǂݍ��񂾕����� END_MOTIONSET �ł͂Ȃ��ꍇ���[�v

				// ���[�V�������̐ݒ�
				CObjectChara::SetMotionInfo(info);
			}
		} while (nEnd != EOF);	// �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v
		
		// �t�@�C�������
		fclose(pFile);
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(NULL, "�v���C���[�Z�b�g�A�b�v�t�@�C���̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);
	}
}
