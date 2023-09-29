//==========================================
//
//  �G�l�~�[�N���X(enemy.h)
//  Author : Riku Nakamura
//
//==========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "object2D.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemy : public CObject2D
{
public:

	// �G�l�~�[�^�C�v��
	typedef enum
	{
		TYPE_NONE = 0,		// �Ȃ�
		TYPE_STICK,			// ��]�_
		TYPE_STICK_SLIDE,	// ���ړ��_
		TYPE_CIRCLE,		// �������~
		TYPE_MAX			// ���̗񋓌^�̑���
	}TYPE;

	//�����o�֐�
	CEnemy();
	~CEnemy();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void SetType(TYPE type) { m_type = type; }
	TYPE GetType(void) { return m_type; }

	//�ÓI�����o�֐�
	static CEnemy* Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize = VEC3_ONE, const D3DXVECTOR3& rRot = VEC3_ZERO, const D3DXCOLOR& rCol = XCOL_WHITE, const TYPE type = TYPE_NONE);

private:

	//�����o�֐�
	void Collision(D3DXVECTOR3 rPos, D3DXVECTOR3 rSize, D3DXVECTOR3 rRot);

	//�����o�ϐ�
	TYPE m_type;

};

#endif
