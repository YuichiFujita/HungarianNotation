//==========================================
//
//  �G�l�~�[�̏W�c(enemygroup.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMYGROUP_H_
#define _ENEMYGROUP_H_
#include "object.h"

//==========================================
//  �O���錾
//==========================================
class CEnemy;

//==========================================
//  �N���X��`
//==========================================
class CEnemyGroup : public CObject
{
public:

	//�����o�֐�
	CEnemyGroup();
	~CEnemyGroup();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }

	//�ÓI�����o�֐�
	static CEnemyGroup* Create(D3DXVECTOR3 pos, float fLength);

private:

#define NUM (4) //����

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	int m_nNum;
	CEnemy* m_pEnemy[NUM];
	float m_fAngle;
	float m_fLength;
};

#endif
