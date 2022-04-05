//================================================
//敵UFOの処理
//Authore:加藤瑞葵
//================================================
#include "scene2D.h"
#include "scene.h"
#include "manager.h"
#include "enemy_ufo.h"
#include "enemy.h"
#include "renderer.h"
#include "sound.h"
#include "texture.h"
#include "bullet_enemy.h"
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
CEnemyUfo::CEnemyUfo()
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
CEnemyUfo::~CEnemyUfo()
{

}

//================================================
//初期化処理
//================================================
HRESULT CEnemyUfo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	m_pos = pos;
	m_size = size;
	m_move = move;
	m_type = ENEMY_TYPE_UFO;
	m_nLife = ENEMY_UFO_LIFE;

	CEnemy::Init(pos, size, move);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CEnemyUfo::Uninit(void)
{
	CEnemy::Uninit();
}

//================================================
//更新処理
//================================================
void CEnemyUfo::Update(void)
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
	//射撃処理
	ShootBullet();

	//位置反映
	CScene2D::SetPos(m_pos, m_size);

	//敵の更新処理
	CEnemy::Update();
}

//================================================
//描画処理
//================================================
void CEnemyUfo::Draw(void)
{
	CEnemy::Draw();
}

//================================================
//生成処理
//================================================
CEnemyUfo *CEnemyUfo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CMover::MOVER_TYPE moverType)
{
	//インスタンスの生成
	CEnemyUfo *pEnemyUfo = NULL;
	if (pEnemyUfo == NULL)
	{
		pEnemyUfo = new CEnemyUfo;
		if (pEnemyUfo != NULL)
		{
			//変数に代入
			pEnemyUfo->m_moverType = moverType;
			//ムーブクラスを生成
			switch (moverType)
			{
			case CMover::MOVER_TYPE_FALL_STOP_RISE:
				pEnemyUfo->m_pMover = CMoverFallStopRise::Create();
				break;
			case CMover::MOVER_TYPE_RIGHT_STOP_LEFT:
				pEnemyUfo->m_pMover = CMoverRightStopLeft::Create();
				break;
			case CMover::MOVER_TYPE_LEFT_STOP_RIGHT:
				pEnemyUfo->m_pMover = CMoverLeftStopRight::Create();
				break;
			case CMover::MOVER_TYPE_FALL_LOWER_LEFT:
				pEnemyUfo->m_pMover = CMoverFallLowerLeft::Create();
				break;
			case CMover::MOVER_TYPE_FALL_LOWER_RIGHT:
				pEnemyUfo->m_pMover = CMoverFallLowerRight::Create();
				break;
			case CMover::MOVER_TYPE_FALL_RANDOM_RIGHT_LEFT:
				pEnemyUfo->m_pMover = CMoverFallRandomRightLeft::Create();
				break;
			case CMover::MOVER_TYPE_RIGHT_STOP:
				pEnemyUfo->m_pMover = CMoverRightStop::Create();
				break;
			case CMover::MOVER_TYPE_LEFT_STOP:
				pEnemyUfo->m_pMover = CMoverLeftStop::Create();
				break;
			default:
				break;
			}
			//初期化
			pEnemyUfo->Init(pos, size, move);
			//テクスチャの取得
			m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_ENEMY_UFO);
			//テクスチャの設定
			pEnemyUfo->BindTexture(m_pTexture);
		}
	}
	return pEnemyUfo;
}

//================================================
//移動量管理処理
//================================================
void CEnemyUfo::MoveType(void)
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

//================================================
//射撃処理
//================================================
void CEnemyUfo::ShootBullet(void)
{
	//カウンターを加算
	m_nBulletCounter++;
	if (m_nBulletCounter >= ENEMY_UFO_SHOOT_COUNTER)
	{
		m_nBulletCounter = 0;

		//サウンド取得処理
		CSound *pSound;
		pSound = CManager::GetSound();

		//弾の生成
		CBulletEnemy::Create(m_pos, D3DXVECTOR3(BULLET_ENEMY_WIDTH, BULLET_ENEMY_HEIGHT, 0.0f),
							D3DXVECTOR3(0.0f, BULLET_ENEMY_HOMING_SPEED, 0.0f), CBulletEnemy::BULLET_TYPE_HOMING, CTexture::TYPE_BULLET_SPHERE);
	}
}