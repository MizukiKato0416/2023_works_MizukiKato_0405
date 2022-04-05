//================================================
//敵戦闘機の処理
//Authore:加藤瑞葵
//================================================
#include "scene2D.h"
#include "scene.h"
#include "manager.h"
#include "enemy_fighter.h"
#include "bullet_enemy.h"
#include "enemy.h"
#include "renderer.h"
#include "sound.h"
#include "texture.h"
#include "mover_fall_stop_rise.h"
#include "mover_right_stop_left.h"
#include "mover_left_stop_right.h"
#include "mover_right_stop.h"
#include "mover_left_stop.h"
#include "mover_fall_lower_left.h"
#include "mover_fall_lower_right.h"
#include "mover_fall_random_right_left.h"

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
CEnemyFighter::CEnemyFighter()
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
CEnemyFighter::~CEnemyFighter()
{

}

//================================================
//初期化処理
//================================================
HRESULT CEnemyFighter::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	m_pos = pos;
	m_size = size;
	m_move = move;
	m_type = ENEMY_TYPE_FIGHTER;
	m_nLife = ENEMY_FIGHTER_LIFE;

	CEnemy::Init(pos, size, move);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CEnemyFighter::Uninit(void)
{
	CEnemy::Uninit();
}

//================================================
//更新処理
//================================================
void CEnemyFighter::Update(void)
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

	//チュートリアルでは撃たないようにする
	if (CManager::GetMode() != CManager::MODE_TUTORIAL)
	{
		//弾を打つ処理
		ShootBullet();
	}

	//位置反映
	CScene2D::SetPos(m_pos, m_size);

	//敵の更新処理
	CEnemy::Update();
}

//================================================
//描画処理
//================================================
void CEnemyFighter::Draw(void)
{
	CEnemy::Draw();
}

//================================================
//生成処理
//================================================
CEnemyFighter *CEnemyFighter::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CMover::MOVER_TYPE moverType)
{
	//インスタンスの生成
	CEnemyFighter *pEnemyFighter = NULL;
	if (pEnemyFighter == NULL)
	{
		pEnemyFighter = new CEnemyFighter;
		if (pEnemyFighter != NULL)
		{
			//変数に代入
			pEnemyFighter->m_moverType = moverType;
			//ムーブクラスを生成
			switch (moverType)
			{
			case CMover::MOVER_TYPE_FALL_STOP_RISE:
				pEnemyFighter->m_pMover = CMoverFallStopRise::Create();
				break;
			case CMover::MOVER_TYPE_RIGHT_STOP_LEFT:
				pEnemyFighter->m_pMover = CMoverRightStopLeft::Create();
				break;
			case CMover::MOVER_TYPE_LEFT_STOP_RIGHT:
				pEnemyFighter->m_pMover = CMoverLeftStopRight::Create();
				break;
			case CMover::MOVER_TYPE_FALL_LOWER_LEFT:
				pEnemyFighter->m_pMover = CMoverFallLowerLeft::Create();
				break;
			case CMover::MOVER_TYPE_FALL_LOWER_RIGHT:
				pEnemyFighter->m_pMover = CMoverFallLowerRight::Create();
				break;
			case CMover::MOVER_TYPE_FALL_RANDOM_RIGHT_LEFT:
				pEnemyFighter->m_pMover = CMoverFallRandomRightLeft::Create();
				break;
			case CMover::MOVER_TYPE_RIGHT_STOP:
				pEnemyFighter->m_pMover = CMoverRightStop::Create();
				break;
			case CMover::MOVER_TYPE_LEFT_STOP:
				pEnemyFighter->m_pMover = CMoverLeftStop::Create();
				break;
			default:
				break;
			}
			//初期化処理
			pEnemyFighter->Init(pos, size, move);
			//テクスチャを取得
			m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_ENEMY_FIGHTER);
			//テクスチャを設定
			pEnemyFighter->BindTexture(m_pTexture);
		}
	}
	return pEnemyFighter;
}

//================================================
//移動量管理処理
//================================================
void CEnemyFighter::MoveType(void)
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
void CEnemyFighter::ShootBullet(void)
{
	//カウンターを加算
	m_nBulletCounter++;
	if (m_nBulletCounter >= ENEMY_FIGHTER_SHOOT_COUNTER)
	{
		m_nBulletCounter = 0;

		//サウンド取得処理
		CSound *pSound;
		pSound = CManager::GetSound();

		//弾の生成
		CBulletEnemy::Create(m_pos, D3DXVECTOR3(BULLET_ENEMY_WIDTH, BULLET_ENEMY_HEIGHT, 0.0f),
								D3DXVECTOR3(0.0f, BULLET_ENEMY_SPEED, 0.0f), CBulletEnemy::BULLET_TYPE_STRAIGHT, CTexture::TYPE_BULLET_SPHERE);
	}
}