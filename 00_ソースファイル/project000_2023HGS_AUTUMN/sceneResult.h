//============================================================
//
//	リザルト画面ヘッダー [sceneResult.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _SCENE_RESULT_H_
#define _SCENE_RESULT_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "main.h"
#include "scene.h"

//************************************************************
//	前方宣言
//************************************************************
class CResultManager;	// リザルトマネージャークラス
class CBg;				// 背景クラス

//************************************************************
//	クラス定義
//************************************************************
// リザルト画面クラス
class CSceneResult : public CScene
{
public:
	// コンストラクタ
	CSceneResult(const MODE mode);

	// デストラクタ
	~CSceneResult();

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	HRESULT Uninit(void) override;	// 終了
	void Update(void) override;		// 更新
	void Draw(void) override;		// 描画

	// 静的メンバ関数
	static CResultManager *GetResultManager(void);	// リザルトマネージャー取得
	static CBg *GetBg(void);	// 背景取得

private:
	// 静的メンバ変数
	static CResultManager *m_pResultManager;	// リザルトマネージャー
	static CBg *m_pBg;	// 背景オブジェクト
};

#endif	// _SCENE_RESULT_H_
