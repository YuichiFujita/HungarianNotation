//============================================================
//
//	ランキングマネージャー処理 [resultManager.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "rankingManager.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "texture.h"
#include "object2D.h"
#include "score.h"
#include "timerManager.h"
#include "retentionManager.h"

//************************************************************
//	マクロ定義
//************************************************************
#define RESULT_PRIO	(6)		// ランキングの優先順位

#define INITCOL_FADE	(XCOL_AWHITE)	// α値の初期値
#define SETCOL_FADE	(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f))	// α値の停止値
#define SIZE_FADE	(SCREEN_SIZE * 0.95f)	// フェードの大きさ
#define ADD_ALPHA	(0.008f)	// α値の加算量

#define POS_RESULT_MISSION	(D3DXVECTOR3(360.0f, 170.0f, 0.0f))	// ランキング表示のMISSION位置
#define POS_RESULT_RESULT	(D3DXVECTOR3(920.0f, 170.0f, 0.0f))	// ランキング表示のRESULT位置
#define SIZE_RESULT			(D3DXVECTOR3(632.7f, 203.5f, 0.0f))	// ランキング表示の大きさ
#define SET_RESULT_SCALE	(15.0f)	// ランキング表示の初期拡大率
#define SUB_RESULT_SCALE	(0.65f)	// ランキング表示拡大率の減算量

#define SCORE_WAIT_CNT	(10)	// スコア表示状態への変更待機フレーム数
#define POS_SCORE_LOGO	(D3DXVECTOR3(250.0f, 400.0f, 0.0f))		// スコアロゴ位置
#define SIZE_SCORE_LOGO	(D3DXVECTOR3(487.5f, 154.7f, 0.0f))		// スコアロゴ大きさ
#define POS_SCORE		(D3DXVECTOR3(490.0f, 400.0f, 0.0f))		// スコア位置
#define SIZE_SCORE		(D3DXVECTOR3(94.0f, 112.0f, 0.0f))		// スコア大きさ
#define SPACE_SCORE		(D3DXVECTOR3(SIZE_SCORE.x, 0.0f, 0.0f))	// スコア空白
#define SET_SCORE_SCALE	(8.0f)	// スコア表示の初期拡大率
#define SUB_SCORE_SCALE	(0.4f)	// スコア表示拡大率の減算量

#define TIME_WAIT_CNT	(3)	// タイム表示状態への変更待機フレーム数
#define POS_TIME_LOGO	(D3DXVECTOR3(250.0f, 560.0f, 0.0f))			// タイムロゴ位置
#define SIZE_TIME_LOGO	(D3DXVECTOR3(487.5f, 154.7f, 0.0f))			// タイムロゴ大きさ
#define POS_TIME		(D3DXVECTOR3(490.0f, 560.0f, 0.0f))			// タイム位置
#define SIZE_TIME_VAL	(D3DXVECTOR3(94.0f, 112.0f, 0.0f))			// タイム数字大きさ
#define SIZE_TIME_PART	(D3DXVECTOR3(48.0f, 112.0f, 0.0f))			// タイム区切り大きさ
#define SPACE_TIME_VAL	(D3DXVECTOR3(SIZE_TIME_VAL.x, 0.0f, 0.0f))	// タイム数字空白
#define SPACE_TIME_PART	(D3DXVECTOR3(SIZE_TIME_PART.x, 0.0f, 0.0f))	// タイム区切り空白
#define SET_TIME_SCALE	(8.0f)	// タイム表示の初期拡大率
#define SUB_TIME_SCALE	(0.4f)	// タイム表示拡大率の減算量


#define FILE_RANK		"data\\TEXT\\ranking.txt"		//ランキングファイル
#define SCORE_WIDTH		(50.0f * 0.5f)		//一桁の横の長さ
#define SCORE_HEIGHT	(100.0f * 0.5f)		//一桁の縦の長さ
#define SCORE_INTER		(110.0f)				//スコアの間隔(横)
#define NUM_TEX			(10)				//テクスチャの数字の数
#define TRANS_TIME		(60 * 10)			//遷移するまでの時間

//************************************************************
//	静的メンバ変数宣言
//************************************************************
const char *CRankingManager::mc_apTextureFile[] =	// テクスチャ定数
{
	NULL,	// 背景テクスチャ
	"data\\TEXTURE\\result003.png",	// スコア表示テクスチャ
};

//************************************************************
//	親クラス [CRankingManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CRankingManager::CRankingManager()
{
	// メンバ変数をクリア
	//memset(&m_apRanking[0], 0, sizeof(m_apRanking));	// ランキング表示の情報
	memset(&m_pScore[0], 0, sizeof(m_pScore));	// スコア表示の情報

	//m_pRanking		= NULL;			//ランキング背景の情報
	//m_pScoreLogo	= NULL;			// スコアロゴの情報
	//m_pTimeLogo		= NULL;			// タイムロゴの情報
	m_pFade			= NULL;			// フェードの情報
	//m_pScore		= NULL;			// スコアの情報
	//m_pTime			= NULL;			// タイムの情報
	m_state			= STATE_NONE;	// 状態
	m_nCounterState	= 0;			// 状態管理カウンター
	m_fScale		= 0.0f;			// ポリゴン拡大率
}

//============================================================
//	デストラクタ
//============================================================
CRankingManager::~CRankingManager()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CRankingManager::Init(void)
{
	// 変数配列を宣言
	D3DXVECTOR3 aPosRanking[] =	// ランキングの位置
	{ // 初期値
		POS_RESULT_MISSION,	// MISSION位置
		POS_RESULT_RESULT,	// RESULT位置
	};

	// ポインタを宣言
	CTexture *pTexture = CManager::GetTexture();	// テクスチャへのポインタ

	// メンバ変数を初期化
	//memset(&m_apRanking[0], 0, sizeof(m_apRanking));	// ランキング表示の情報
	memset(&m_pScore[0], 0, sizeof(m_pScore));	// スコア表示の情報

	//m_pRanking = NULL;			//ランキング背景の情報
	//m_pScoreLogo = NULL;			// スコアロゴの情報
	//m_pTimeLogo		= NULL;			// タイムロゴの情報
	m_pFade = NULL;			// フェードの情報
	//m_pScore		= NULL;			// スコアの情報
	//m_pTime			= NULL;			// タイムの情報
	m_state = STATE_FADEIN;	// 状態
	m_nCounterState = 0;			// 状態管理カウンター
	m_fScale = 0.0f;			// ポリゴン拡大率

	//--------------------------------------------------------
	//	フェードの生成・設定
	//--------------------------------------------------------
	// フェードの生成
	m_pFade = CObject2D::Create
	( // 引数
		SCREEN_CENT,	// 位置
		SIZE_FADE,		// 大きさ
		VEC3_ZERO,		// 向き
		INITCOL_FADE	// 色
	);
	if (m_pFade == NULL)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pFade->SetPriority(RESULT_PRIO);

	//--------------------------------------------------------
	//	ランキング表示の生成・設定
	//--------------------------------------------------------

	//	// ランキング表示の生成
	//m_pRanking = CObject2D::Create
	//( // 引数
	//	POS_RESULT_MISSION,			// 位置
	//	SIZE_RESULT * SET_RESULT_SCALE	// 大きさ
	//);
	//if (m_pRanking == NULL)
	//{ // 生成に失敗した場合

	//	// 失敗を返す
	//	assert(false);
	//	return E_FAIL;
	//}

	//// 優先順位を設定
	//m_pRanking->SetPriority(RESULT_PRIO);

	//// 描画をしない設定にする
	//m_pRanking->SetEnableDraw(false);

	//// ランキング表示のテクスチャを設定
	//SetTexRanking();

	//--------------------------------------------------------
	//	スコア表示の生成・設定
	//--------------------------------------------------------
	for (int nCntScore = 0; nCntScore < MAX_RANKKING; nCntScore++)
	{
		// スコアオブジェクトの生成
		m_pScore[nCntScore] = CScore::Create
		( // 引数
			D3DXVECTOR3(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.25f + (nCntScore * SCORE_INTER), 0.0f),						// 位置
			SIZE_SCORE * SET_SCORE_SCALE,	// 大きさ
			SPACE_SCORE						// 空白
		);
		if (m_pScore[nCntScore] == NULL)
		{ // 非使用中の場合

			// 失敗を返す
			assert(false);
			return E_FAIL;
		}

		// 優先順位を設定
		m_pScore[nCntScore]->SetPriority(RESULT_PRIO);

		// 描画をしない設定にする
		m_pScore[nCntScore]->SetEnableDraw(false);

		// スコアを設定
		m_pScore[nCntScore]->Set(CManager::GetRetentionManager()->GetScore());
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
HRESULT CRankingManager::Uninit(void)
{
	// ランキング背景の終了
	//m_pRanking->Uninit();

	// スコアロゴ表示の終了
	//m_pScoreLogo->Uninit();

	// フェードの終了
	m_pFade->Uninit();

	for (int nCntScore = 0; nCntScore < MAX_RANKKING; nCntScore++)
	{
		// 終了済みのオブジェクトポインタをNULLにする
		m_pScore[nCntScore] = NULL;	// スコアオブジェクト
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	更新処理
//============================================================
void CRankingManager::Update(void)
{
	// 遷移決定の更新
	UpdateBack();

	switch (m_state)
	{ // 状態ごとの処理
	case STATE_NONE:	// 何もしない状態

		// 無し

		break;

	case STATE_FADEIN:	// フェードイン状態

		// フェードインの更新
		UpdateFade();

		break;

	//case STATE_RANKING:	// ランキング表示状態

	//	// ランキング表示の更新
	//	UpdateRanking();

	//	break;

	case STATE_SCORE_WAIT:	// スコア表示待機状態

		// 表示待機の更新
		if (UpdateDrawWait(SCORE_WAIT_CNT))
		{ // 待機完了の場合

			// スコア表示の拡大率を設定
			m_fScale = SET_SCORE_SCALE;

			// スコア表示の描画開始
			//m_pScoreLogo->SetEnableDraw(true);

			for (int nCntScore = 0; nCntScore < MAX_RANKKING; nCntScore++)
			{
				m_pScore[nCntScore]->SetEnableDraw(true);
			}

			// 状態を変更
			m_state = STATE_SCORE;	// スコア表示状態
		}

		break;

	case STATE_SCORE:	// スコア表示状態

		// スコア表示の更新
		UpdateScore();

		break;

	case STATE_WAIT:	// 遷移待機状態

		// 無し

		break;

	default:	// 例外処理
		assert(false);
		break;
	}

	// ランキング表示の更新
	//m_pRanking->Update();

	// スコアロゴ表示の更新
	//m_pScoreLogo->Update();

	// フェードの更新
	m_pFade->Update();
}

//============================================================
//	生成処理
//============================================================
CRankingManager *CRankingManager::Create(void)
{
	// ポインタを宣言
	CRankingManager *pRankingManager = NULL;	// ランキングマネージャー生成用

	if (pRankingManager == NULL)
	{ // 使用されていない場合

		// メモリ確保
		pRankingManager = new CRankingManager;	// ランキングマネージャー
	}
	else { assert(false); return NULL; }	// 使用中

	if (pRankingManager != NULL)
	{ // 使用されている場合
		
		// ランキングマネージャーの初期化
		if (FAILED(pRankingManager->Init()))
		{ // 初期化に失敗した場合

			// メモリ開放
			delete pRankingManager;
			pRankingManager = NULL;

			// 失敗を返す
			return NULL;
		}

		// 確保したアドレスを返す
		return pRankingManager;
	}
	else { assert(false); return NULL; }	// 確保失敗
}

//============================================================
//	破棄処理
//============================================================
HRESULT CRankingManager::Release(CRankingManager *&prRankingManager)
{
	if (prRankingManager != NULL)
	{ // 使用中の場合

		// ランキングマネージャーの終了
		if (FAILED(prRankingManager->Uninit()))
		{ // 破棄に失敗した場合

			// メモリ開放
			delete prRankingManager;
			prRankingManager = NULL;

			// 失敗を返す
			assert(false);
			return E_FAIL;
		}

		// メモリ開放
		delete prRankingManager;
		prRankingManager = NULL;

		// 成功を返す
		return S_OK;
	}
	else { assert(false); return E_FAIL; }	// 非使用中
}

//============================================================
//	フェードインの更新処理
//============================================================
void CRankingManager::UpdateFade(void)
{
	// 変数を宣言
	D3DXCOLOR colFade = m_pFade->GetColor();	// フェードの色

	if (colFade.a < SETCOL_FADE.a)
	{ // 透明量が設定値未満の場合

		// 透明度を加算
		colFade.a += ADD_ALPHA;
	}
	else
	{ // 透明量が設定値以上の場合

		// 透明度を補正
		colFade.a = SETCOL_FADE.a;

		// ランキング表示の描画開始
		//m_pRanking->SetEnableDraw(true);

		// ランキング表示の拡大率を設定
		m_fScale = SET_RESULT_SCALE;

		// 状態を変更
		m_state = STATE_SCORE_WAIT;	// ランキング表示状態
	}

	// 透明度を反映
	m_pFade->SetColor(colFade);
}

//============================================================
//	ランキング表示の更新処理
//============================================================
void CRankingManager::UpdateRanking(void)
{
	if (m_fScale > 1.0f)
	{ // 拡大率が最小値より大きい場合

		// 拡大率を減算
		m_fScale -= SUB_RESULT_SCALE;

		// ランキング表示の大きさを設定
		//m_pRanking->SetScaling(SIZE_RESULT * m_fScale);
	}
	else
	{ // 拡大率が最小値以下の場合

		// ランキング表示の大きさを設定
		//m_pRanking->SetScaling(SIZE_RESULT);

		// 状態を変更
		m_state = STATE_SCORE_WAIT;	// スコア表示待機状態

		// サウンドの再生
		CManager::GetSound()->Play(CSound::LABEL_SE_DECISION_001);	// 決定音01
	}
}

//============================================================
//	スコア表示の更新処理
//============================================================
void CRankingManager::UpdateScore(void)
{
	if (m_fScale > 1.0f)
	{ // 拡大率が最小値より大きい場合

		// 拡大率を減算
		m_fScale -= SUB_SCORE_SCALE;

		// スコア表示の大きさを設定
		//m_pScoreLogo->SetScaling(SIZE_SCORE_LOGO * m_fScale);

		for (int nCntScore = 0; nCntScore < MAX_RANKKING; nCntScore++)
		{
			m_pScore[nCntScore]->SetScaling(SIZE_SCORE * m_fScale);
		}
	}
	else
	{ // 拡大率が最小値以下の場合

		// 拡大率を補正
		m_fScale = 1.0f;

		// スコア表示の大きさを設定
		//m_pScoreLogo->SetScaling(SIZE_SCORE_LOGO);

		for (int nCntScore = 0; nCntScore < MAX_RANKKING; nCntScore++)
		{
			m_pScore[nCntScore]->SetScaling(SIZE_SCORE);

		}

		// 状態を変更
		m_state = STATE_WAIT;	// タイム表示待機状態

		// サウンドの再生
		CManager::GetSound()->Play(CSound::LABEL_SE_DECISION_001);	// 決定音01
	}
}

//============================================================
//	遷移決定の更新処理
//============================================================
void CRankingManager::UpdateBack(void)
{
	// ポインタを宣言
	CInputKeyboard	*pKeyboard	= CManager::GetKeyboard();	// キーボード
	CInputPad		*pPad		= CManager::GetPad();		// パッド

	if (pKeyboard->GetTrigger(DIK_RETURN)
	||  pKeyboard->GetTrigger(DIK_SPACE)
	||  pPad->GetTrigger(CInputPad::KEY_A)
	||  pPad->GetTrigger(CInputPad::KEY_B)
	||  pPad->GetTrigger(CInputPad::KEY_X)
	||  pPad->GetTrigger(CInputPad::KEY_Y)
	||  pPad->GetTrigger(CInputPad::KEY_START))
	{
		if (m_state != STATE_WAIT)
		{ // 遷移待機状態ではない場合

			// 演出スキップ
			SkipStaging();

			// サウンドの再生
			CManager::GetSound()->Play(CSound::LABEL_SE_DECISION_001);	// 決定音01
		}
		else
		{ // 遷移待機状態の場合

			if (CManager::GetFade()->GetState() == CFade::FADE_NONE)
			{ // フェード中ではない場合

				// シーンの設定
				CManager::SetScene(CScene::MODE_TITLE);	// タイトル画面

				// サウンドの再生
				CManager::GetSound()->Play(CSound::LABEL_SE_DECISION_000);	// 決定音00
			}
		}
	}
}

//============================================================
//	演出スキップ処理
//============================================================
void CRankingManager::SkipStaging(void)
{
	// ランキング表示の描画をONにし、大きさを設定
	//for (int nCntRanking = 0; nCntRanking < NUM_RANKING; nCntRanking++)
	//{ // ランキング表示の総数分繰り返す

	//	// ランキング表示の描画開始
	//	m_pRanking->SetEnableDraw(true);

	//	// ランキング表示の大きさを設定
	//	m_pRanking->SetScaling(SIZE_RESULT);
	//}

	// スコア表示をONにする
	//m_pScoreLogo->SetEnableDraw(true);

	for (int nCntScore = 0; nCntScore < MAX_RANKKING; nCntScore++)
	{
		m_pScore[nCntScore]->SetEnableDraw(true);
	}

	// スコア表示の大きさを設定
	//m_pScoreLogo->SetScaling(SIZE_SCORE_LOGO);

	for (int nCntScore = 0; nCntScore < MAX_RANKKING; nCntScore++)
	{
		m_pScore[nCntScore]->SetScaling(SIZE_SCORE);
	}

	// フェードの透明度を設定
	m_pFade->SetColor(SETCOL_FADE);

	// 状態を変更
	m_state = STATE_WAIT;	// 遷移待機状態
}

//============================================================
//	ランキング表示のテクスチャの設定処理
//============================================================
void CRankingManager::SetTexRanking(void)
{
	// ポインタを宣言
	CTexture *pTexture = CManager::GetTexture();	// テクスチャへのポインタ

	// 背景テクスチャを登録・割当
	//m_pRanking->BindTexture(pTexture->Regist(mc_apTextureFile[TEXTURE_BACK]));
}

//============================================================
//	表示待機処理
//============================================================
bool CRankingManager::UpdateDrawWait(const int nWait)
{
	if (m_nCounterState < nWait)
	{ // カウンターが待機カウントまで達していない場合

		// カウンターを加算
		m_nCounterState++;

		// 待機未完了を返す
		return false;
	}
	else
	{ // カウンターが待機完了した場合

		// カウンターを初期化
		m_nCounterState = 0;

		// 待機完了を返す
		return true;
	}
}
