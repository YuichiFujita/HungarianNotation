//============================================================
//
//	リザルト画面処理 [sceneResult.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "sceneResult.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "sound.h"
#include "resultManager.h"
#include "stage.h"
#include "bg.h"

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CResultManager *CSceneResult::m_pResultManager = NULL;	// リザルトマネージャー
CBg *CSceneResult::m_pBg = NULL;	// 背景オブジェクト

//************************************************************
//	子クラス [CSceneResult] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CSceneResult::CSceneResult(const MODE mode) : CScene(mode)
{

}

//============================================================
//	デストラクタ
//============================================================
CSceneResult::~CSceneResult()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CSceneResult::Init(void)
{
	// ポインタを宣言
	CTexture *pTexture = CManager::GetTexture();	// テクスチャへのポインタ

	//--------------------------------------------------------
	//	リザルトの初期化
	//--------------------------------------------------------
	// リザルトマネージャーの生成
	m_pResultManager = CResultManager::Create();
	if (m_pResultManager == NULL)
	{ // 非使用中の場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 背景の生成
	m_pBg = CBg::Create(CBg::TEXTURE_BG, SCREEN_CENT, SCREEN_SIZE);
	if (m_pBg == NULL)
	{ // 非使用中の場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// シーンの初期化
	CScene::Init();

	//--------------------------------------------------------
	//	初期設定
	//--------------------------------------------------------
	// BGMの再生
	CManager::GetSound()->Play(CSound::LABEL_BGM_TITLE_RESULT);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
HRESULT CSceneResult::Uninit(void)
{
	// リザルトマネージャーの破棄
	if (FAILED(CResultManager::Release(m_pResultManager)))
	{ // 破棄に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 終了済みのオブジェクトポインタをNULLにする
	m_pBg = NULL;	// 背景オブジェクト

	// シーンの終了
	CScene::Uninit();

	// 成功を返す
	return S_OK;
}

//============================================================
//	更新処理
//============================================================
void CSceneResult::Update(void)
{
	if (m_pResultManager != NULL)
	{ // 使用中の場合

		// リザルトマネージャーの更新
		m_pResultManager->Update();
	}
	else { assert(false); }	// 非使用中

	// シーンの更新
	CScene::Update();
}

//============================================================
//	描画処理
//============================================================
void CSceneResult::Draw(void)
{

}

//============================================================
//	リザルトマネージャー取得処理
//============================================================
CResultManager *CSceneResult::GetResultManager(void)
{
	// リザルトマネージャーを返す
	return m_pResultManager;
}

//============================================================
//	背景取得処理
//============================================================
CBg *CSceneResult::GetBg(void)
{
	// 背景のポインタを返す
	return m_pBg;
}
