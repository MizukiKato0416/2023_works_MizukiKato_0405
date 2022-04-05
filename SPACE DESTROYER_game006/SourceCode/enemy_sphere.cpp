//================================================
//球体型敵の処理
//Authore:加藤瑞葵
//================================================
#include "scene2D.h"
#include "scene.h"
#include "manager.h"
#include "enemy_sphere.h"
#include "enemy.h"
#include "renderer.h"
#include "sound.h"
#include "texture.h"
#include "mover_fall_stop_rise.h"
#include "mover_right_stop_left.h"
#include "mover_left_stop_right.h"
#include "mover_fall_lower_left.h"
#include "mover_fall_lower_right.h"
#include "mover_fall_random_right_left.h"
#include "mover_right_stop.h"
#include "mover_left_stop.h"

#ifndef _DEBUG
//#define NDEBUG
#endif // !_DEBUG
#include <assert.h>

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CEnemySphere::CEnemySphere()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CEnemySphere::~CEnemySphere()
{

}

//================================================
//初期化処理
//================================================
HRESULT CEnemySphere::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	m_pos = pos;
	m_size = size;
	m_move = move;
	m_type = ENEMY_TYPE_SPHERE;
	m_nLife = ENEMY_SPHERE_LIFE;

	CEnemy::Init(pos, size, move);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CEnemySphere::Uninit(void)
{
	CEnemy::Uninit();
}

//================================================
//更新処理
//================================================
void CEnemySphere::Update(void)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//位置取得
	m_pos = GetPos();

	m_pos += m_move;		//移動量反映

	//画面外に出たら
	if (m_pos.x + m_size.x / 2.0f < 0.0f || m_pos.x - m_size.x / 2.0f > SCREEN_WIDTH ||
		m_pos.y + m_size.y / 2.0f < 0.0f || m_pos.y - m_size.y / 2.0f > SCREEN_HEIGHT)
	{
		Uninit();
		return;
	}

	//移動の設定
	MoveType();

	//位置反映
	CScene2D::SetPos(m_pos, m_size);

	//敵の更新処理
	CEnemy::Update();
}

//================================================
//描画処理
//================================================
void CEnemySphere::Draw(void)
{
	CEnemy::Draw();
}

//================================================
//生成処理
//================================================
CEnemySphere *CEnemySphere::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CMover::MOVER_TYPE moverType)
{
	//インスタンスの生成
	CEnemySphere *pEnemySphere = NULL;
	if (pEnemySphere == NULL)
	{
		pEnemySphere = new CEnemySphere;
		if (pEnemySphere != NULL)
		{
			//変数に代入
			pEnemySphere->m_moverType = moverType;
			//ムーブクラスを生成
			switch (moverType)
			{
			case CMover::MOVER_TYPE_FALL_STOP_RISE:
				pEnemySphere->m_pMover = CMoverFallStopRise::Create();
				break;
			case CMover::MOVER_TYPE_RIGHT_STOP_LEFT:
				pEnemySphere->m_pMover = CMoverRightStopLeft::Create();
				break;
			case CMover::MOVER_TYPE_LEFT_STOP_RIGHT:
				pEnemySphere->m_pMover = CMoverLeftStopRight::Create();
				break;
			case CMover::MOVER_TYPE_FALL_LOWER_LEFT:
				pEnemySphere->m_pMover = CMoverFallLowerLeft::Create();
				break;
			case CMover::MOVER_TYPE_FALL_LOWER_RIGHT:
				pEnemySphere->m_pMover = CMoverFallLowerRight::Create();
				break;
			case CMover::MOVER_TYPE_FALL_RANDOM_RIGHT_LEFT:
				pEnemySphere->m_pMover = CMoverFallRandomRightLeft::Create();
				break;
			case CMover::MOVER_TYPE_RIGHT_STOP:
				pEnemySphere->m_pMover = CMoverRightStop::Create();
				break;
			case CMover::MOVER_TYPE_LEFT_STOP:
				pEnemySphere->m_pMover = CMoverLeftStop::Create();
				break;
			default:
				break;
			}
			//初期化処理
			pEnemySphere->Init(pos, size, move);
			//テクスチャを取得
			m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_ENEMY_SPHERE);
			//テクスチャを設定
			pEnemySphere->BindTexture(m_pTexture);
		}
	}
	return pEnemySphere;
}

//================================================
//移動量管理処理
//================================================
void CEnemySphere::MoveType(void)
{
	if (m_moverType != CMover::MOVER_TYPE_NONE)
	{
		//ムーブクラスのアップデートを呼び出す
		m_pMover->Update();

		//移動量を取得
		D3DXVECTOR3 move = m_pMover->GetMove();
		m_move = move;
	}
}