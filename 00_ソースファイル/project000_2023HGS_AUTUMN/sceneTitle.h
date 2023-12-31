//============================================================
//
//	タイトル画面ヘッダー [sceneTitle.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _SCENE_TITLE_H_
#define _SCENE_TITLE_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "main.h"
#include "scene.h"

//************************************************************
//	前方宣言
//************************************************************
class CTitleManager;	// タイトルマネージャークラス
class CBg;				// 背景クラス

//************************************************************
//	クラス定義
//************************************************************
// タイトル画面クラス
class CSceneTitle : public CScene
{
public:
	// コンストラクタ
	CSceneTitle(const MODE mode);

	// デストラクタ
	~CSceneTitle();

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	HRESULT Uninit(void) override;	// 終了
	void Update(void) override;		// 更新
	void Draw(void) override;		// 描画

	// 静的メンバ関数
	static CTitleManager *GetTitleManager(void);	// タイトルマネージャー取得
	static CBg *GetBg(void);	// 背景取得

private:
	// 静的メンバ変数
	static CTitleManager *m_pTitleManager;	// タイトルマネージャー
	static CBg *m_pBg;	// 背景オブジェクト
};

#endif	// _SCENE_TITLE_H_
