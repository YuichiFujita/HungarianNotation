//============================================================
//
//	背景処理 [bg.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "sceneGame.h"
#include "gameManager.h"
#include "map.h"

//************************************************************
//	マクロ定義
//************************************************************
#define BG_PRIO	(0)	// 背景の優先順位

//************************************************************
//	静的メンバ変数宣言
//************************************************************
const char *CBg::mc_apTextureFile[] =	// テクスチャ定数
{
	"data\\TEXTURE\\bg000.png",	// 背景テクスチャ
};

//************************************************************
//	子クラス [CBg] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CBg::CBg() : CScroll2D(CObject::LABEL_BG, BG_PRIO)
{

}

//============================================================
//	デストラクタ
//============================================================
CBg::~CBg()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CBg::Init(void)
{
	// スクロール2Dの初期化
	if (FAILED(CScroll2D::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CBg::Uninit(void)
{
	// スクロール2Dの終了
	CScroll2D::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CBg::Update(void)
{
	if (CManager::GetScene()->GetMode() == CScene::MODE_GAME)
	{ // モードがゲームの場合

		// 縦座標の移動量設定
		SetMoveV(-(CSceneGame::GetGameManager()->GetMap()->GetWorldMove() * 0.005f));
	}

	// スクロール2Dの更新
	CScroll2D::Update();
}

//============================================================
//	描画処理
//============================================================
void CBg::Draw(void)
{
	// スクロール2Dの描画
	CScroll2D::Draw();
}

//============================================================
//	生成処理
//============================================================
CBg *CBg::Create
(
	const TEXTURE texture,		// テクスチャ
	const D3DXVECTOR3& rPos,	// 位置
	const D3DXVECTOR3& rSize	// 大きさ
)
{
	// ポインタを宣言
	CBg *pBg = NULL;	// 背景生成用

	if (pBg == NULL)
	{ // 使用されていない場合

		// メモリ確保
		pBg = new CBg;	// 背景
	}
	else { assert(false); return NULL; }	// 使用中

	if (pBg != NULL)
	{ // 確保に成功している場合

		// 背景の初期化
		if (FAILED(pBg->Init()))
		{ // 初期化に失敗した場合

			// メモリ開放
			delete pBg;
			pBg = NULL;

			// 失敗を返す
			return NULL;
		}

		// テクスチャを登録・割当
		pBg->BindTexture(CManager::GetTexture()->Regist(mc_apTextureFile[TEXTURE_BG]));

		// 位置を設定
		pBg->SetPosition(rPos);

		// 大きさを設定
		pBg->SetScaling(rSize);

		// 確保したアドレスを返す
		return pBg;
	}
	else { assert(false); return NULL; }	// 確保失敗
}
