//============================================================
//
//	プレイヤーヘッダー [player.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "main.h"
#include "objectChara.h"

//************************************************************
//	前方宣言
//************************************************************
class CObjectGauge3D;	// オブジェクトゲージ3Dクラス
class CShadow;			// 影クラス

//************************************************************
//	クラス定義
//************************************************************
// プレイヤークラス
class CPlayer : public CObjectChara
{
public:
	// モデル列挙
	typedef enum
	{
		MODEL_WAIST,	// 腰
		MODEL_BODY,		// 体
		MODEL_CLOAK,	// マント
		MODEL_HEAD,		// 頭
		MODEL_HAT,		// 帽子
		MODEL_ARMUL,	// 左上腕
		MODEL_ARMUR,	// 右上腕
		MODEL_ARMDL,	// 左下腕
		MODEL_ARMDR,	// 右下腕
		MODEL_HANDL,	// 左手
		MODEL_HANDR,	// 右手
		MODEL_LEGUL,	// 左太もも
		MODEL_LEGUR,	// 右太もも
		MODEL_LEGDL,	// 左脛
		MODEL_LEGDR,	// 右脛
		MODEL_FOOTL,	// 左足
		MODEL_FOOTR,	// 右足
		MODEL_ROD,		// 杖
		MODEL_MAX		// この列挙型の総数
	}MODEL;

	// モーション列挙
	typedef enum
	{
		MOTION_MOVE = 0,		// 浮遊モーション
		MOTION_ACCELE,			// 加速モーション
		MOTION_DECELE,			// 減速モーション
		MOTION_ACTION_LEFT,		// 左アクションモーション
		MOTION_ACTION_RIGHT,	// 右アクションモーション
		MOTION_ACTION_FAR,		// 奥アクションモーション
		MOTION_ACTION_NEAR,		// 手前アクションモーション
		MOTION_BLOW_AWAY,		// 吹っ飛びモーション
		MOTION_DEATH,			// 死亡モーション
		MOTION_MAX				// この列挙型の総数
	}MOTION;

	// 状態列挙
	typedef enum
	{
		STATE_NONE = 0,		// 何もしない状態
		STATE_NORMAL,		// 通常状態
		STATE_DEATH,		// 死亡状態
		STATE_MAX			// この列挙型の総数
	}STATE;

	// コンストラクタ
	CPlayer();

	// デストラクタ
	~CPlayer();

	// オーバーライド関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	void Hit(const int nDmg);	// ヒット

	// 静的メンバ関数
	static CPlayer *Create	// 生成
	( // 引数
		const D3DXVECTOR3& rPos,	// 位置
		const D3DXVECTOR3& rRot		// 向き
	);

	// メンバ関数
	void SetState(const int nState);			// 状態設定
	void SetEnableUpdate(const bool bUpdate);	// 更新状況設定
	void SetEnableDraw(const bool bDraw);		// 描画状況設定
	void SetEnableDrawLife(const bool bDraw);	// 体力の描画状況設定

	D3DXMATRIX GetMtxWorld(void) const;	// マトリックス取得
	int GetState(void) const;			// 状態取得
	float GetRadius(void) const;		// 半径取得
	int GetLife(void) const;			// 体力取得
	int GetMaxLife(void) const;			// 最大体力取得

private:
	// メンバ関数
	void LoadSetup(void);	// セットアップ

	void UpdateOldPosition(void);			// 過去位置の更新
	MOTION UpdateMove(void);				// 移動量・目標向きの更新
	void UpdateJump(void);					// ジャンプの更新
	bool UpdateLanding(D3DXVECTOR3& rPos);	// 着地状況の更新
	void UpdatePosition(D3DXVECTOR3& rPos);	// 位置の更新
	void UpdateRotation(D3DXVECTOR3& rRot);	// 向きの更新
	void UpdateMotion(int nMotion);			// モーション・オブジェクトキャラクターの更新

	MOTION UpdateNormal(void);	// 通常状態時の更新

	// 静的メンバ変数
	static const char *mc_apModelFile[];	// モデル定数

	// メンバ変数
	CObjectGauge3D	*m_pLife;	// 体力の情報
	CShadow			*m_pShadow;	// 影の情報

	D3DXVECTOR3	m_oldPos;		// 過去位置
	D3DXVECTOR3	m_move;			// 移動量
	D3DXVECTOR3	m_destRot;		// 目標向き
	STATE	m_state;			// 状態
	int		m_nCounterState;	// 状態管理カウンター
	int		m_nNumModel;		// パーツの総数
	bool	m_bJump;			// ジャンプ状況
};

#endif	// _PLAYER_H_
