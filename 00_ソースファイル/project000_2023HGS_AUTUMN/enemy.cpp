//==========================================
//
//  エネミークラス(enemy.cpp)
//  Author : Riku Nakamura
//
//==========================================
#include "enemy.h"
#include "player.h"
#include "effect2D.h"
#include "input.h"
#include "manager.h"
#include "gameManager.h"
#include "debugproc.h"

//==========================================
//  コンストラクタ
//==========================================
CEnemy::CEnemy()
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemy::~CEnemy()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy::Init(void)
{
	//初期化
	return CObject2D::Init();
}

//==========================================
//  終了処理
//==========================================
void CEnemy::Uninit(void)
{
	//終了
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemy::Update(void)
{
	D3DXVECTOR3 rPos = GetPosition();
	D3DXVECTOR3 rSize = GetScaling();
	D3DXVECTOR3 rRot = GetRotation();

#ifdef _DEBUG
		if (CManager::GetKeyboard()->GetPress(DIK_I))
		{
			rPos += D3DXVECTOR3(0.0f, -2.0f, 0.0f);
		}
		if (CManager::GetKeyboard()->GetPress(DIK_K))
		{
			rPos += D3DXVECTOR3(0.0f, 2.0f, 0.0f);
		}
		if (CManager::GetKeyboard()->GetPress(DIK_J))
		{
			rPos += D3DXVECTOR3(-2.0f, 0.0f, 0.0f);
		}
		if (CManager::GetKeyboard()->GetPress(DIK_L))
		{
			rPos += D3DXVECTOR3(2.0f, 0.0f, 0.0f);
		}

		if (CManager::GetKeyboard()->GetPress(DIK_U))
		{
			rRot += D3DXVECTOR3(0.0f, 0.0f, -0.01f);
		}
		if (CManager::GetKeyboard()->GetPress(DIK_O))
		{
			rRot += D3DXVECTOR3(0.0f, 0.0f, 0.01f);
		}
#endif

	Collision(GetPosition(), GetScaling(), GetRotation());

	SetPosition(rPos);
	SetScaling(rSize);
	SetRotation(rRot);

	//更新
	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemy::Draw(void)
{
	//描画
	CObject2D::Draw();
}

//==========================================
//  生成処理
//==========================================
CEnemy* CEnemy::Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize, const D3DXVECTOR3& rRot, const D3DXCOLOR& rCol, const TYPE type)
{
	//オブジェクトを生成
	CEnemy* pEnemy = nullptr;

	//メモリを確保
	if (pEnemy == nullptr)
	{
		pEnemy = new CEnemy;

		if (pEnemy != nullptr)
		{
			//初期化処理
			pEnemy->Init();

			//各データの設定
			pEnemy->SetPosition(rPos);
			pEnemy->SetScaling(rSize);
			pEnemy->SetRotation(rRot);
			pEnemy->SetColor(rCol);
			pEnemy->SetType(type);
			pEnemy->SetLabel(CObject::LABEL_ENEMY);
		}
	}

	return pEnemy;
}

//==========================================
//  当たり判定処理
//==========================================
void CEnemy::Collision(D3DXVECTOR3 rPos, D3DXVECTOR3 rSize, D3DXVECTOR3 rRot)
{
	D3DXVECTOR3 posCurrent;
	D3DXVECTOR3 posNext;
	D3DXVECTOR3 vecMove;

	D3DXVECTOR3 posEnd[2];

	CGameManager::GetPlayer()->GetVecInfo(&posCurrent, &posNext, &vecMove);

	vecMove = posNext - posCurrent;

	if (m_type == TYPE_STICK || m_type == TYPE_STICK_SLIDE)
	{
		float fLength = 0.0f;
		float fRate, fOutToPos, fOutToPosOld, fOutUnit, fOutRate;
		D3DXVECTOR3 vecLine, vecToPos, vecToPosOld;

		//棒の長さの基準計算
		if (rSize.x > rSize.y)
		{
			fLength = rSize.x * 0.5f;
		}
		else
		{
			fLength = rSize.y * 0.5f;
		}

		//棒の両端算出
		posEnd[0].x = rPos.x + fLength * cosf(-rRot.z);
		posEnd[0].y = rPos.y + fLength * sinf(-rRot.z);

		posEnd[1].x = rPos.x + fLength * cosf(-rRot.z + 3.1415f);
		posEnd[1].y = rPos.y + fLength * sinf(-rRot.z + 3.1415f);

		CEffect2D::Create
		(
			CEffect2D::TYPE_NORMAL,			// テクスチャ
			posEnd[0],	// 位置
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 移動量
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 向き
			XCOL_WHITE,		// 色
			1,			// 寿命
			10.0f,		// 半径
			0.0f,		// 半径の減算量
			0.0f,		// 透明度の減算量
			CObject::LABEL_EFFECT2D			// オブジェクトラベル
		);

		CEffect2D::Create
		(
			CEffect2D::TYPE_NORMAL,			// テクスチャ
			posEnd[1],	// 位置
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 移動量
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 向き
			XCOL_WHITE,		// 色
			1,			// 寿命
			10.0f,		// 半径
			0.0f,		// 半径の減算量
			0.0f,		// 透明度の減算量
			CObject::LABEL_EFFECT2D			// オブジェクトラベル
		);

		//基準点とプレイヤーの位置のベクトル
		vecToPos.x = posNext.x - posEnd[1].x;
		vecToPos.y = posNext.y - posEnd[1].y;

		//基準点とプレイヤーの前の位置のベクトル
		vecToPosOld.x = posCurrent.x - posEnd[1].x;
		vecToPosOld.y = posCurrent.y - posEnd[1].y;

		//板側面のベクトル
		vecLine.x = posEnd[0].x - posEnd[1].x;
		vecLine.y = posEnd[0].y - posEnd[1].y; 

		//側面とプレイヤーの位置の外積
		fOutToPos = (vecLine.x * vecToPos.y) - (vecLine.y * vecToPos.x);
		fOutToPosOld = (vecLine.x * vecToPosOld.y) - (vecLine.y * vecToPosOld.x);

		//交点計算
		fOutUnit = (vecLine.x * vecMove.y) - (vecLine.y * vecMove.x);
		fOutRate = (vecToPos.x * vecMove.y) - (vecToPos.y * vecMove.x);
		fRate = fOutRate / fOutUnit;

		CManager::GetDebugProc()->Print("棒の位置 : %f, %f\n", rPos.x, rPos.y);
		CManager::GetDebugProc()->Print("点棒の外積 : %f, %f, %f\n", fOutToPos, fOutToPosOld, fRate);

		//側面衝突判定
		if (fOutToPos * fOutToPosOld < 0.0f && fRate < 1.0f && fRate > 0.0f)
		{
			CManager::GetDebugProc()->Print("動くと当たるよ\n");
		}
		else
		{
			float rot[2], answer[2];
			D3DXVECTOR3 vec[2] = {};

			rot[0] = atan2f((posEnd[0].x - posCurrent.x), (posEnd[0].y - posCurrent.y)) - atan2f((posNext.x - posCurrent.x), (posNext.y - posCurrent.y));
			rot[1] = atan2f((posEnd[1].x - posCurrent.x), (posEnd[1].y - posCurrent.y)) - atan2f((posNext.x - posCurrent.x), (posNext.y - posCurrent.y));

			if (rot[0] > D3DX_PI)
			{
				rot[0] -= (D3DX_PI * 2);
			}
			else if (rot[0] < -D3DX_PI)
			{
				rot[0] += (D3DX_PI * 2);
			}

			if (rot[1] > D3DX_PI)
			{
				rot[1] -= (D3DX_PI * 2);
			}
			else if (rot[1] < -D3DX_PI)
			{
				rot[1] += (D3DX_PI * 2);
			}

			vec[0] = posEnd[0] - posCurrent;
			vec[1] = posEnd[1] - posCurrent;

			vec[0].z = 0.0f;
			vec[1].z = 0.0f;

			answer[0] = D3DXVec3Length(&vec[0]);
			answer[0] = answer[0] * sinf(rot[0]);
			answer[1] = D3DXVec3Length(&vec[1]);
			answer[1] = answer[1] * sinf(rot[1]);

			CManager::GetDebugProc()->Print("点棒の距離 : %f, %f\n", rot[0], rot[1]);
			CManager::GetDebugProc()->Print("点棒の距離 : %f, %f\n", answer[0], answer[1]);

			if ((rot[0] < 1.57f && rot[0] > -1.57f) ||
				(rot[1] < 1.57f && rot[1] > -1.57f))
			{
				if ((answer[0] < 30.0f && answer[0] > -30.0f) || (answer[1] < 30.0f && answer[1] > -30.0f))
				{
					CManager::GetDebugProc()->Print("端っこ当たるよ\n");
				}
				else if ((answer[0] < 60.0f && answer[0] > -60.0f) || (answer[1] < 60.0f && answer[1] > -60.0f))
				{
					CManager::GetDebugProc()->Print("動くとかするよ\n");
				}
			}
		}
	}
	else if (m_type == TYPE_CIRCLE)
	{

	}
}

