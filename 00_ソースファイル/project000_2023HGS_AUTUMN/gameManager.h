//============================================================
//
//	ゲームマネージャーヘッダー [gameManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "main.h"

//==========================================
//  前方宣言
//==========================================
class CPlayer;
class CMap;

//************************************************************
//	クラス定義
//************************************************************
// ゲームマネージャークラス
class CGameManager
{
public:
	// コンストラクタ
	CGameManager();

	// デストラクタ
	~CGameManager();

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新

	// 静的メンバ関数
	static CGameManager *Create(void);	// 生成
	static HRESULT Release(CGameManager *&prGameManager);	// 破棄
	static CPlayer* GetPlayer(void) { return m_pPlayer; } //プレイヤーの取得
	static CMap* GetMap(void) { return m_pMap; } //世界の取得

private:

	//静的メンバ変数
	static CPlayer* m_pPlayer; //プレイヤーのポインタ
	static CMap* m_pMap; //世界のポインタ

};

#endif	// _GAMEMANAGER_H_
