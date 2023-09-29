//==========================================
//
//  エネミーマネージャ(enemymanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

//==========================================
//  クラス定義
//==========================================
class CEnemyManager
{
public:

	//メンバ関数
	CEnemyManager();
	~CEnemyManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	//メンバ変数
	int m_nPopTime;

};

#endif
