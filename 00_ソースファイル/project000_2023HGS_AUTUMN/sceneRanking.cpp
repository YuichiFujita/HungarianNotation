//============================================================
//
//	ランキング画面ヘッダー [sceneRanking.h]
//	Author：佐藤根詩音
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "sceneRanking.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "sound.h"
#include "rankingManager.h"
#include "stage.h"
#include "bg.h" 

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CRankingManager *CSceneRanking::m_pRankingManager = NULL;	// ランキングマネージャー
CBg *CSceneRanking::m_pBg = NULL;	// 背景オブジェクト

//************************************************************
//	子クラス [CSceneRanking] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CSceneRanking::CSceneRanking(const MODE mode) : CScene(mode)
{

}

//============================================================
//	デストラクタ
//============================================================
CSceneRanking::~CSceneRanking()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CSceneRanking::Init(void)
{
	// ポインタを宣言
	CTexture *pTexture = CManager::GetTexture();	// テクスチャへのポインタ

	//--------------------------------------------------------
	//	ランキングの初期化
	//--------------------------------------------------------
	// ランキングマネージャーの生成
	m_pRankingManager = CRankingManager::Create();

	if (m_pRankingManager == NULL)
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
	CManager::GetSound()->Play(CSound::LABEL_BGM_RANKING);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
HRESULT CSceneRanking::Uninit(void)
{
	// ランキングマネージャーの破棄
	if (FAILED(CRankingManager::Release(m_pRankingManager)))
	{ // 破棄に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// シーンの終了
	CScene::Uninit();

	// 終了済みのオブジェクトポインタをNULLにする
	m_pBg = NULL;		// 背景オブジェクト

	// 成功を返す
	return S_OK;
}

//============================================================
//	更新処理
//============================================================
void CSceneRanking::Update(void)
{
	if (m_pRankingManager != NULL)
	{ // 使用中の場合

		// ランキングマネージャーの更新
		m_pRankingManager->Update();
	}
	else { assert(false); }	// 非使用中

							// シーンの更新
	CScene::Update();
}

//============================================================
//	描画処理
//============================================================
void CSceneRanking::Draw(void)
{

}

//============================================================
//	ランキングマネージャー取得処理
//============================================================
CRankingManager *CSceneRanking::GetRankingManager(void)
{
	// ランキングマネージャーを返す
	return m_pRankingManager;
}