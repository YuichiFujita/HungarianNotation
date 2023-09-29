//==========================================
//
//  �v���C���[�N���X(player.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "object2D.h"

//==========================================
//	�O���錾
//==========================================
class CObjectOrbit;	// �I�u�W�F�N�g�O�ՃN���X

//==========================================
//  �N���X��`
//==========================================
class CPlayer : public CObject2D
{
public:

	//�����o�֐�
	CPlayer();
	~CPlayer();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void GetVecInfo(D3DXVECTOR3* posCurrent, D3DXVECTOR3* posNext, D3DXVECTOR3* vecMove); //�ړ����̎擾

	//�ÓI�����o�֐�
	static CPlayer* Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize = VEC3_ONE, const D3DXVECTOR3& rRot = VEC3_ZERO, const D3DXCOLOR& rCol = XCOL_WHITE);

private:

	//�����o�֐�
	void Move(D3DXVECTOR3 pos); //�ړ�
	void Rotation(void); //��]

	//�����o�ϐ�
	CObjectOrbit *m_pOrbit;	// �I�u�W�F�N�g�O�ՃN���X
	D3DXVECTOR3 m_posNext;	// �����W
	D3DXVECTOR3 m_vecMove;	// �ړ��x�N�g��
};

#endif
