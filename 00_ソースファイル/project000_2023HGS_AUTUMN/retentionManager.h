//============================================================
//
//	データ保存マネージャーヘッダー [retentionManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _RETENTION_MANAGER_H_
#define _RETENTION_MANAGER_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "main.h"

//************************************************************
//	クラス定義
//************************************************************
// データ保存マネージャークラス
class CRetentionManager
{
public:
	// リザルト列挙
	enum RESULT
	{
		RESULT_NONE,	// 無し
		RESULT_FAILED,	// クリア失敗
		RESULT_CLEAR,	// クリア成功
		RESULT_MAX		// この列挙型の総数
	};

	// コンストラクタ
	CRetentionManager();

	// デストラクタ
	~CRetentionManager();

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新

	// 静的メンバ関数
	static CRetentionManager *Create(void);	// 生成
	static HRESULT Release(CRetentionManager *&prRetentionManager);	// 破棄

	// メンバ関数
	void SetResult(const RESULT result);	// クリア状況設定
	void SetScore(const int nScore);		// 獲得スコア設定
	RESULT GetResult(void) const;			// クリア状況取得
	int GetScore(void) const;				// 獲得スコア取得

private:
	// メンバ変数
	RESULT m_result;	// クリア状況
	int m_nScore;		// 獲得スコア
};

#endif	// _RETENTION_MANAGER_H_
