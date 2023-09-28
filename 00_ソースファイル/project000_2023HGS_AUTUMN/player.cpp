//============================================================
//
//	プレイヤー処理 [player.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "player.h"
#include "manager.h"
#include "scene.h"
#include "sceneGame.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "camera.h"
#include "texture.h"
#include "collision.h"

#include "multiModel.h"
#include "objectGauge3D.h"
#include "shadow.h"
#include "stage.h"
#include "field.h"

//************************************************************
//	マクロ定義
//************************************************************
// セットアップテキスト相対パス
#define PLAYER_SETUP_TXT	"data\\TXT\\player.txt"

// プレイヤー基本情報
#define MAX_LIFE	(100)	// プレイヤー最大体力
#define JUMP_REV	(0.08f)	// 空中のプレイヤー移動量の減衰係数
#define LAND_REV	(0.2f)	// 地上のプレイヤー移動量の減衰係数
#define REV_ROTA	(0.15f)	// プレイヤー向き変更の減衰係数
#define JUMP		(20.0f)	// プレイヤージャンプ量
#define GRAVITY		(1.0f)	// プレイヤー重力
#define RADIUS		(20.0f)	// プレイヤー半径

// プレイヤー他クラス情報
#define SHADOW_SIZE	(D3DXVECTOR3(80.0f, 0.0f, 80.0f))	// 影の大きさ

#define GAUGE_CHANGE_FRAME	(6)			// 体力変動フレーム
#define GAUGE_PLUS_Y		(140.0f)	// 体力ゲージY位置加算量
#define GAUGE_GAUGESIZE		(D3DXVECTOR3(110.0f, 15.0f, 0.0f))	// ゲージ大きさ
#define GAUGE_FRONTCOL		(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))	// 表ゲージ色
#define GAUGE_BACKCOL		(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))	// 裏ゲージ色

//************************************************************
//	静的メンバ変数宣言
//************************************************************
const char *CPlayer::mc_apModelFile[] =	// モデル定数
{
	"data\\MODEL\\PLAYER\\00_waist.x",	// 腰
	"data\\MODEL\\PLAYER\\01_body.x",	// 体
	"data\\MODEL\\PLAYER\\02_cloak.x",	// マント
	"data\\MODEL\\PLAYER\\03_head.x",	// 頭
	"data\\MODEL\\PLAYER\\04_hat.x",	// 帽子
	"data\\MODEL\\PLAYER\\05_armUL.x",	// 左上腕
	"data\\MODEL\\PLAYER\\06_armUR.x",	// 右上腕
	"data\\MODEL\\PLAYER\\07_armDL.x",	// 左下腕
	"data\\MODEL\\PLAYER\\08_armDR.x",	// 右下腕
	"data\\MODEL\\PLAYER\\09_handL.x",	// 左手
	"data\\MODEL\\PLAYER\\10_handR.x",	// 右手
	"data\\MODEL\\PLAYER\\11_legUL.x",	// 左太もも
	"data\\MODEL\\PLAYER\\12_legUR.x",	// 右太もも
	"data\\MODEL\\PLAYER\\13_legDL.x",	// 左脛
	"data\\MODEL\\PLAYER\\14_legDR.x",	// 右脛
	"data\\MODEL\\PLAYER\\15_footL.x",	// 左足
	"data\\MODEL\\PLAYER\\16_footR.x",	// 右足
	"data\\MODEL\\PLAYER\\17_rod.x",	// 杖
};

//************************************************************
//	子クラス [CPlayer] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CPlayer::CPlayer() : CObjectChara(CObject::LABEL_PLAYER)
{
	// メンバ変数をクリア
	m_pLife			= NULL;			// 体力の情報
	m_pShadow		= NULL;			// 影の情報
	m_oldPos		= VEC3_ZERO;	// 過去位置
	m_move			= VEC3_ZERO;	// 移動量
	m_destRot		= VEC3_ZERO;	// 目標向き
	m_state			= STATE_NONE;	// 状態
	m_nCounterState	= 0;			// 状態管理カウンター
	m_nNumModel		= 0;			// パーツの総数
	m_bJump			= false;		// ジャンプ状況
}

//============================================================
//	デストラクタ
//============================================================
CPlayer::~CPlayer()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CPlayer::Init(void)
{
	// ポインタを宣言
	CTexture *pTexture = CManager::GetTexture();	// テクスチャへのポインタ

	// メンバ変数を初期化
	m_pLife			= NULL;			// 体力の情報
	m_pShadow		= NULL;			// 影の情報
	m_oldPos		= VEC3_ZERO;	// 過去位置
	m_move			= VEC3_ZERO;	// 移動量
	m_destRot		= VEC3_ZERO;	// 目標向き
	m_state			= STATE_NORMAL;	// 状態
	m_nCounterState	= 0;			// 状態管理カウンター
	m_nNumModel		= 0;			// パーツの総数
	m_bJump			= true;			// ジャンプ状況

	// オブジェクトキャラクターの初期化
	if (FAILED(CObjectChara::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// セットアップの読み込み
	LoadSetup();

	// モデル情報の設定
	SetModelInfo();

	// 体力の生成
	m_pLife = CObjectGauge3D::Create
	( // 引数
		CObject::LABEL_GAUGE,			// オブジェクトラベル
		this,							// ゲージ表示オブジェクト
		MAX_LIFE,						// 最大表示値
		GAUGE_CHANGE_FRAME,				// 表示値変動フレーム
		GAUGE_PLUS_Y,					// 表示Y位置の加算量
		GAUGE_GAUGESIZE,				// ゲージ大きさ
		GAUGE_FRONTCOL,					// 表ゲージ色
		GAUGE_BACKCOL,					// 裏ゲージ色
		true,							// 枠描画状況
		CObjectGauge3D::TYPE_PLAYER,	// 枠種類
		GAUGE_GAUGESIZE					// 枠大きさ
	);
	if (UNUSED(m_pLife))
	{ // 非使用中の場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 影の生成
	m_pShadow = CShadow::Create(CShadow::TEXTURE_NORMAL, SHADOW_SIZE, this);
	if (UNUSED(m_pShadow))
	{ // 非使用中の場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// モーションの設定
	SetMotion(MOTION_MOVE);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CPlayer::Uninit(void)
{
	// 影を破棄
	m_pShadow->Uninit();

	// オブジェクトキャラクターの終了
	CObjectChara::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CPlayer::Update(void)
{
	// 変数を宣言
	MOTION currentMotion = MOTION_MOVE;		// 現在のモーション

	// 過去位置の更新
	UpdateOldPosition();

	switch (m_state)
	{ // 状態ごとの処理
	case STATE_NONE:
		break;

	case STATE_NORMAL:

		// 通常状態の更新
		currentMotion = UpdateNormal();

		break;

	case STATE_DEATH:
		break;

	default:
		assert(false);
		break;
	}

	// 影の更新
	m_pShadow->Update();

	// モーション・オブジェクトキャラクターの更新
	UpdateMotion(currentMotion);
}

//============================================================
//	描画処理
//============================================================
void CPlayer::Draw(void)
{
	// オブジェクトキャラクターの描画
	CObjectChara::Draw();
}

//============================================================
//	ヒット処理
//============================================================
void CPlayer::Hit(const int nDmg)
{

#if 0	// TODO：Hit処理

	// 変数を宣言
	D3DXVECTOR3 pos = GetPosition();	// プレイヤー位置

	if (IsDeath() != true)
	{ // 死亡フラグが立っていない場合

		if (m_state == STATE_NORMAL)
		{ // 通常状態の場合

			// 体力からダメージ分減算
			m_pLife->AddNum(-nDmg);

			if (m_pLife->GetNum() > 0)
			{ // 生きている場合

				// カウンターを初期化
				m_nCounterState = 0;

				// 状態を変更
				m_state = STATE_DAMAGE;	// ダメージ状態
			}
			else
			{ // 死んでいる場合

				// カウンターを初期化
				m_nCounterState = 0;

				// 状態を変更
				m_state = STATE_DEATH;	// 死亡状態

				// モーションの設定
				SetMotion(MOTION_DEATH);	// 死亡モーション

				// サウンドの再生
				CManager::GetSound()->Play(CSound::LABEL_SE_BREAK);	// 破壊音
			}
		}
	}

#endif

}

//============================================================
//	生成処理
//============================================================
CPlayer *CPlayer::Create
(
	const D3DXVECTOR3& rPos,	// 位置
	const D3DXVECTOR3& rRot		// 向き
)
{
	// 変数を宣言
	D3DXVECTOR3 pos = rPos;		// 座標設定用

	// ポインタを宣言
	CPlayer *pPlayer = NULL;	// プレイヤー生成用

	if (UNUSED(pPlayer))
	{ // 使用されていない場合

		// メモリ確保
		pPlayer = new CPlayer;	// プレイヤー
	}
	else { assert(false); return NULL; }	// 使用中

	if (pPlayer != NULL)
	{ // 使用されている場合

		// プレイヤーの初期化
		if (FAILED(pPlayer->Init()))
		{ // 初期化に失敗した場合

			// メモリ開放
			delete pPlayer;
			pPlayer = NULL;

			// 失敗を返す
			return NULL;
		}

		// 位置を設定
		CScene::GetStage()->LimitPosition(pos, RADIUS);		// ステージ範囲内補正
		pos.y = CScene::GetField()->GetPositionHeight(pos);	// 高さを地面に設定
		pPlayer->SetPosition(pos);

		// 向きを設定
		pPlayer->SetRotation(rRot);
	}

	// 確保したアドレスを返す
	return pPlayer;
}

//============================================================
//	状態の設定処理
//============================================================
void CPlayer::SetState(const int nState)
{
	// 引数の状態を設定
	m_state = (STATE)nState;
}

//============================================================
//	更新状況の設定処理
//============================================================
void CPlayer::SetEnableUpdate(const bool bUpdate)
{
	// 引数の更新状況を設定
	CObject::SetEnableUpdate(bUpdate);		// 自身
	m_pShadow->SetEnableUpdate(bUpdate);	// 影
}

//============================================================
//	描画状況の設定処理
//============================================================
void CPlayer::SetEnableDraw(const bool bDraw)
{
	// 引数の描画状況を設定
	CObject::SetEnableDraw(bDraw);		// 自身
	m_pShadow->SetEnableDraw(bDraw);	// 影
}

//============================================================
//	体力の描画状況の設定処理
//============================================================
void CPlayer::SetEnableDrawLife(const bool bDraw)
{
	// 引数の描画状況を体力に設定
	m_pLife->SetEnableDraw(bDraw);
}

//============================================================
//	マトリックス取得処理
//============================================================
D3DXMATRIX CPlayer::GetMtxWorld(void) const
{
	// 変数を宣言
	D3DXMATRIX  mtxRot, mtxTrans, mtxWorld;	// 計算用マトリックス
	D3DXVECTOR3 posPlayer = GetPosition();	// プレイヤー位置
	D3DXVECTOR3 rotPlayer = GetRotation();	// プレイヤー向き

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotPlayer.y, rotPlayer.x, rotPlayer.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, posPlayer.x, posPlayer.y, posPlayer.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ワールドマトリックスを返す
	return mtxWorld;
}

//============================================================
//	体力取得処理
//============================================================
int CPlayer::GetLife(void) const
{
	// 体力を返す
	return m_pLife->GetNum();
}

//============================================================
//	最大体力取得処理
//============================================================
int CPlayer::GetMaxLife(void) const
{
	// 最大体力を返す
	return m_pLife->GetMaxNum();
}

//============================================================
//	状態取得処理
//============================================================
int CPlayer::GetState(void) const
{
	// 状態を返す
	return m_state;
}

//============================================================
//	半径取得処理
//============================================================
float CPlayer::GetRadius(void) const
{
	// 半径を返す
	return RADIUS;
}

//============================================================
//	過去位置の更新処理
//============================================================
void CPlayer::UpdateOldPosition(void)
{
	// 過去位置を更新
	m_oldPos = GetPosition();
}

//============================================================
//	移動量・目標向きの更新処理
//============================================================
CPlayer::MOTION CPlayer::UpdateMove(void)
{
	// 変数を宣言
	D3DXVECTOR3 rotCamera = CManager::GetCamera()->GetRotation();	// カメラの向き

	// ポインタを宣言
	CInputKeyboard	*pKeyboard	= CManager::GetKeyboard();	// キーボード
	CInputPad		*pPad		= CManager::GetPad();		// パッド

	if (pKeyboard->GetPress(DIK_W))
	{ // 奥移動の操作が行われた場合

		if (pKeyboard->GetPress(DIK_A))
		{ // 左移動の操作も行われた場合 (左奥移動)

			// 移動量を更新
			m_move.x += sinf(rotCamera.y - (D3DX_PI * 0.25f)) * 2.0f;
			m_move.z += cosf(rotCamera.y - (D3DX_PI * 0.25f)) * 2.0f;

			// 目標向きを更新
			m_destRot.y = D3DXToRadian(135) + rotCamera.y;
		}
		else if (pKeyboard->GetPress(DIK_D))
		{ // 右移動の操作も行われた場合 (右奥移動)

			// 移動量を更新
			m_move.x -= sinf(rotCamera.y - (D3DX_PI * 0.75f)) * 2.0f;
			m_move.z -= cosf(rotCamera.y - (D3DX_PI * 0.75f)) * 2.0f;

			// 目標向きを更新
			m_destRot.y = D3DXToRadian(225) + rotCamera.y;
		}
		else
		{ // 奥移動の操作だけが行われた場合 (奥移動)

			// 移動量を更新
			m_move.x += sinf(rotCamera.y) * 2.0f;
			m_move.z += cosf(rotCamera.y) * 2.0f;

			// 目標向きを更新
			m_destRot.y = D3DXToRadian(180) + rotCamera.y;
		}
	}
	else if (pKeyboard->GetPress(DIK_S))
	{ // 手前移動の操作が行われた場合

		if (pKeyboard->GetPress(DIK_A))
		{ // 左移動の操作も行われた場合 (左手前移動)

			// 移動量を更新
			m_move.x += sinf(rotCamera.y - (D3DX_PI * 0.75f)) * 2.0f;
			m_move.z += cosf(rotCamera.y - (D3DX_PI * 0.75f)) * 2.0f;

			// 目標向きを更新
			m_destRot.y = D3DXToRadian(45) + rotCamera.y;
		}
		else if (pKeyboard->GetPress(DIK_D))
		{ // 右移動の操作も行われた場合 (右手前移動)

			// 移動量を更新
			m_move.x -= sinf(rotCamera.y - (D3DX_PI * 0.25f)) * 2.0f;
			m_move.z -= cosf(rotCamera.y - (D3DX_PI * 0.25f)) * 2.0f;

			// 目標向きを更新
			m_destRot.y = D3DXToRadian(315) + rotCamera.y;
		}
		else
		{ // 手前移動の操作だけが行われた場合 (手前移動)

			// 移動量を更新
			m_move.x -= sinf(rotCamera.y) * 2.0f;
			m_move.z -= cosf(rotCamera.y) * 2.0f;

			// 目標向きを更新
			m_destRot.y = D3DXToRadian(0) + rotCamera.y;
		}
	}
	else if (pKeyboard->GetPress(DIK_A))
	{ // 左移動の操作が行われた場合

		// 移動量を更新
		m_move.x += sinf(rotCamera.y - (D3DX_PI * 0.5f)) * 2.0f;
		m_move.z += cosf(rotCamera.y - (D3DX_PI * 0.5f)) * 2.0f;

		// 目標向きを更新
		m_destRot.y = D3DXToRadian(90) + rotCamera.y;
	}
	else if (pKeyboard->GetPress(DIK_D))
	{ // 右移動の操作が行われた場合

		// 移動量を更新
		m_move.x -= sinf(rotCamera.y - (D3DX_PI * 0.5f)) * 2.0f;
		m_move.z -= cosf(rotCamera.y - (D3DX_PI * 0.5f)) * 2.0f;

		// 目標向きを更新
		m_destRot.y = D3DXToRadian(270) + rotCamera.y;
	}

	// 浮遊モーションを返す
	return MOTION_MOVE;
}

//============================================================
//	ジャンプの更新処理
//============================================================
void CPlayer::UpdateJump(void)
{
	// ポインタを宣言
	CInputKeyboard	*pKeyboard = CManager::GetKeyboard();	// キーボード
	CInputPad		*pPad = CManager::GetPad();				// パッド

	if (m_bJump == false)
	{ // ジャンプしていない場合

		if (pKeyboard->GetTrigger(DIK_SPACE))
		{ // ジャンプの操作が行われた場合

			// 上移動量
			m_move.y += JUMP;

			// ジャンプしている状態にする
			m_bJump = true;
		}
	}
}

//============================================================
//	着地状況の更新処理
//============================================================
bool CPlayer::UpdateLanding(D3DXVECTOR3& rPos)
{
	// 変数を宣言
	bool bLand = false;	// 着地状況

	// 着地判定
	if (CScene::GetField()->LandPosition(rPos, m_move)
	||  CScene::GetStage()->LandPosition(rPos, m_move, 0.0f))
	{ // プレイヤーが着地していた場合

		// 着地している状態にする
		bLand = true;

		// ジャンプしていない状態にする
		m_bJump = false;
	}
	else
	{ // 着地していない場合

		// ジャンプしている状態にする
		m_bJump = true;
	}

	// 着地状況を返す
	return bLand;
}

//============================================================
//	位置の更新処理
//============================================================
void CPlayer::UpdatePosition(D3DXVECTOR3& rPos)
{
	// 重力を加算
	m_move.y -= GRAVITY;

	// 移動量を加算
	rPos += m_move;

	// 移動量を減衰
	if (m_bJump)
	{ // 空中の場合

		m_move.x += (0.0f - m_move.x) * JUMP_REV;
		m_move.z += (0.0f - m_move.z) * JUMP_REV;
	}
	else
	{ // 地上の場合

		m_move.x += (0.0f - m_move.x) * LAND_REV;
		m_move.z += (0.0f - m_move.z) * LAND_REV;
	}
}

//============================================================
//	向きの更新処理
//============================================================
void CPlayer::UpdateRotation(D3DXVECTOR3& rRot)
{
	// 変数を宣言
	float fDiffRot = 0.0f;	// 差分向き

	// 目標向きの正規化
	useful::NormalizeRot(m_destRot.y);

	// 目標向きまでの差分を計算
	fDiffRot = m_destRot.y - rRot.y;

	// 差分向きの正規化
	useful::NormalizeRot(fDiffRot);

	// 向きの更新
	rRot.y += fDiffRot * REV_ROTA;

	// 向きの正規化
	useful::NormalizeRot(rRot.y);
}

//============================================================
//	モーション・オブジェクトキャラクターの更新処理
//============================================================
void CPlayer::UpdateMotion(int nMotion)
{
	// 変数を宣言
	int nAnimMotion = GetMotionType();	// 現在再生中のモーション

	if (nMotion != NONE_IDX)
	{ // モーションが設定されている場合

		if (IsMotionLoop(nAnimMotion))
		{ // ループするモーションだった場合

			if (nAnimMotion != nMotion)
			{ // 現在のモーションが再生中のモーションと一致しない場合

				// 現在のモーションの設定
				SetMotion(nMotion);
			}
		}
	}

	// オブジェクトキャラクターの更新
	CObjectChara::Update();

	// モーションの遷移
	if (IsMotionFinish())
	{ // モーションが終了していた場合

		switch (GetMotionType())
		{ // モーションの種類ごとの処理
		case MOTION_BLOW_AWAY:	// 吹っ飛び状態

			// 無し

			// 処理を抜ける
			break;
		}
	}
}

//============================================================
//	通常状態時の更新処理
//============================================================
CPlayer::MOTION CPlayer::UpdateNormal(void)
{
	// 変数を宣言
	MOTION currentMotion = MOTION_MOVE;		// 現在のモーション
	D3DXVECTOR3 posPlayer = GetPosition();	// プレイヤー位置
	D3DXVECTOR3 rotPlayer = GetRotation();	// プレイヤー向き

	// ポインタを宣言
	CStage *pStage = CScene::GetStage();	// ステージ情報

	if (pStage != NULL)
	{ // ステージが使用されている場合

		// 移動操作
		currentMotion = UpdateMove();

		// ジャンプ操作
		UpdateJump();

		// 向き更新
		UpdateRotation(rotPlayer);

		// 位置更新
		UpdatePosition(posPlayer);

		// ステージ範囲外の補正
		pStage->LimitPosition(posPlayer, RADIUS);

		// 着地判定
		UpdateLanding(posPlayer);
	}
	else { assert(false); return currentMotion; }	// 非使用中

	// 位置を更新
	SetPosition(posPlayer);

	// 向きを更新
	SetRotation(rotPlayer);

	// 現在のモーションを返す
	return currentMotion;
}

//============================================================
//	セットアップ処理
//============================================================
void CPlayer::LoadSetup(void)
{
	// 変数を宣言
	CMotion::MotionInfo info;		// ポーズの代入用
	D3DXVECTOR3 pos = VEC3_ZERO;	// 位置の代入用
	D3DXVECTOR3 rot = VEC3_ZERO;	// 向きの代入用
	int nLevel		= 0;	// レベルの代入用
	int nID			= 0;	// インデックスの代入用
	int nParentID	= 0;	// 親インデックスの代入用
	int nNowPose	= 0;	// 現在のポーズ番号
	int nNowKey		= 0;	// 現在のキー番号
	int nLoop		= 0;	// ループのON/OFFの変換用
	int nEnd		= 0;	// テキスト読み込み終了の確認用

	// 変数配列を宣言
	char aString[MAX_STRING];	// テキストの文字列の代入用

	// ポインタを宣言
	FILE *pFile;	// ファイルポインタ

	// ポーズ代入用の変数を初期化
	memset(&info, 0, sizeof(info));

	// ファイルを読み込み形式で開く
	pFile = fopen(PLAYER_SETUP_TXT, "r");

	if (pFile != NULL)
	{ // ファイルが開けた場合

		do
		{ // 読み込んだ文字列が EOF ではない場合ループ

			// ファイルから文字列を読み込む
			nEnd = fscanf(pFile, "%s", &aString[0]);	// テキストを読み込みきったら EOF を返す

			// キャラクターの設定
			if (strcmp(&aString[0], "CHARACTERSET") == 0)
			{ // 読み込んだ文字列が CHARACTERSET の場合

				do
				{ // 読み込んだ文字列が END_CHARACTERSET ではない場合ループ

					// ファイルから文字列を読み込む
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "PARTSSET") == 0)
					{ // 読み込んだ文字列が PARTSSET の場合

						do
						{ // 読み込んだ文字列が END_PARTSSET ではない場合ループ

							// ファイルから文字列を読み込む
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "INDEX") == 0)
							{ // 読み込んだ文字列が INDEX の場合

								fscanf(pFile, "%s", &aString[0]);	// = を読み込む (不要)
								fscanf(pFile, "%d", &nID);			// モデルのインデックスを読み込む
							}
							else if (strcmp(&aString[0], "PARENT") == 0)
							{ // 読み込んだ文字列が PARENT の場合

								fscanf(pFile, "%s", &aString[0]);	// = を読み込む (不要)
								fscanf(pFile, "%d", &nParentID);	// モデルの親のインデックスを読み込む
							}
							else if (strcmp(&aString[0], "POS") == 0)
							{ // 読み込んだ文字列が POS の場合

								fscanf(pFile, "%s", &aString[0]);	// = を読み込む (不要)
								fscanf(pFile, "%f", &pos.x);		// X座標を読み込む
								fscanf(pFile, "%f", &pos.y);		// Y座標を読み込む
								fscanf(pFile, "%f", &pos.z);		// Z座標を読み込む
							}
							else if (strcmp(&aString[0], "ROT") == 0)
							{ // 読み込んだ文字列が ROT の場合

								fscanf(pFile, "%s", &aString[0]);	// = を読み込む (不要)
								fscanf(pFile, "%f", &rot.x);		// X向きを読み込む
								fscanf(pFile, "%f", &rot.y);		// Y向きを読み込む
								fscanf(pFile, "%f", &rot.z);		// Z向きを読み込む
							}
						} while (strcmp(&aString[0], "END_PARTSSET") != 0);	// 読み込んだ文字列が END_PARTSSET ではない場合ループ

						// パーツ情報の設定
						CObjectChara::SetPartsInfo(nID, nParentID, pos, rot, mc_apModelFile[nID]);
					}
				} while (strcmp(&aString[0], "END_CHARACTERSET") != 0);		// 読み込んだ文字列が END_CHARACTERSET ではない場合ループ
			}

			// モーションの設定
			else if (strcmp(&aString[0], "MOTIONSET") == 0)
			{ // 読み込んだ文字列が MOTIONSET の場合

				// 現在のポーズ番号を初期化
				nNowPose = 0;

				do
				{ // 読み込んだ文字列が END_MOTIONSET ではない場合ループ

					// ファイルから文字列を読み込む
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "LOOP") == 0)
					{ // 読み込んだ文字列が LOOP の場合

						fscanf(pFile, "%s", &aString[0]);	// = を読み込む (不要)
						fscanf(pFile, "%d", &nLoop);		// ループのON/OFFを読み込む

						// 読み込んだ値をbool型に変換
						info.bLoop = (nLoop == 0) ? false : true;
					}
					else if (strcmp(&aString[0], "NUM_KEY") == 0)
					{ // 読み込んだ文字列が NUM_KEY の場合

						fscanf(pFile, "%s", &aString[0]);	// = を読み込む (不要)
						fscanf(pFile, "%d", &info.nNumKey);	// キーの総数を読み込む
					}
					else if (strcmp(&aString[0], "KEYSET") == 0)
					{ // 読み込んだ文字列が KEYSET の場合

						// 現在のキー番号を初期化
						nNowKey = 0;

						do
						{ // 読み込んだ文字列が END_KEYSET ではない場合ループ

							// ファイルから文字列を読み込む
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "FRAME") == 0)
							{ // 読み込んだ文字列が FRAME の場合

								fscanf(pFile, "%s", &aString[0]);						// = を読み込む (不要)
								fscanf(pFile, "%d", &info.aKeyInfo[nNowPose].nFrame);	// キーが切り替わるまでのフレーム数を読み込む
							}
							else if (strcmp(&aString[0], "KEY") == 0)
							{ // 読み込んだ文字列が KEY の場合

								do
								{ // 読み込んだ文字列が END_KEY ではない場合ループ

									// ファイルから文字列を読み込む
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(&aString[0], "POS") == 0)
									{ // 読み込んだ文字列が POS の場合

										fscanf(pFile, "%s", &aString[0]);									// = を読み込む (不要)
										fscanf(pFile, "%f", &info.aKeyInfo[nNowPose].aKey[nNowKey].pos.x);	// X位置を読み込む
										fscanf(pFile, "%f", &info.aKeyInfo[nNowPose].aKey[nNowKey].pos.y);	// Y位置を読み込む
										fscanf(pFile, "%f", &info.aKeyInfo[nNowPose].aKey[nNowKey].pos.z);	// Z位置を読み込む

										// 読み込んだ位置にパーツの初期位置を加算
										info.aKeyInfo[nNowPose].aKey[nNowKey].pos += GetPartsPosition(nNowKey);
									}
									else if (strcmp(&aString[0], "ROT") == 0)
									{ // 読み込んだ文字列が ROT の場合

										fscanf(pFile, "%s", &aString[0]);									// = を読み込む (不要)
										fscanf(pFile, "%f", &info.aKeyInfo[nNowPose].aKey[nNowKey].rot.x);	// X向きを読み込む
										fscanf(pFile, "%f", &info.aKeyInfo[nNowPose].aKey[nNowKey].rot.y);	// Y向きを読み込む
										fscanf(pFile, "%f", &info.aKeyInfo[nNowPose].aKey[nNowKey].rot.z);	// Z向きを読み込む

										// 読み込んだ向きにパーツの初期向きを加算
										info.aKeyInfo[nNowPose].aKey[nNowKey].rot += GetPartsRotation(nNowKey);

										// 初期向きを正規化
										useful::NormalizeRot(info.aKeyInfo[nNowPose].aKey[nNowKey].rot.x);
										useful::NormalizeRot(info.aKeyInfo[nNowPose].aKey[nNowKey].rot.y);
										useful::NormalizeRot(info.aKeyInfo[nNowPose].aKey[nNowKey].rot.z);
									}

								} while (strcmp(&aString[0], "END_KEY") != 0);	// 読み込んだ文字列が END_KEY ではない場合ループ

								// 現在のキー番号を加算
								nNowKey++;
							}
						} while (strcmp(&aString[0], "END_KEYSET") != 0);	// 読み込んだ文字列が END_KEYSET ではない場合ループ

						// 現在のポーズ番号を加算
						nNowPose++;
					}
				} while (strcmp(&aString[0], "END_MOTIONSET") != 0);	// 読み込んだ文字列が END_MOTIONSET ではない場合ループ

				// モーション情報の設定
				CObjectChara::SetMotionInfo(info);
			}
		} while (nEnd != EOF);	// 読み込んだ文字列が EOF ではない場合ループ
		
		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{ // ファイルが開けなかった場合

		// エラーメッセージボックス
		MessageBox(NULL, "プレイヤーセットアップファイルの読み込みに失敗！", "警告！", MB_ICONWARNING);
	}
}
