//==========================================
//
//  �G�l�~�[�}�l�[�W��(enemymanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

//==========================================
//  �N���X��`
//==========================================
class CEnemyManager
{
public:

	//�����o�֐�
	CEnemyManager();
	~CEnemyManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	//�����o�ϐ�
	int m_nPopTime;

};

#endif
