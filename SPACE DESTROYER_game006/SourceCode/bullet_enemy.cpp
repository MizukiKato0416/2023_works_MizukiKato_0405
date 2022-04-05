//================================================
//敵の弾処理
//Authore:加藤瑞葵
//================================================
#include "scene2D.h"
#include "scene.h"
#include "manager.h"
#include "bullet_enemy.h"
#include "renderer.h"
#include "explosion.h"
#include "sound.h"
#include "effect.h"
#include "game01.h"
#include "texture.h"
#include "player.h"
#include "life.h"
#include "boss.h"


#ifndef _DEBUG
//#define NDEBUG
#endif // !_DEBUG
#include <assert.h>

//================================================
//静的メンバ変数宣言
//================================================
LPDIRECT3DTEXTURE9 CBulletEnemy::m_pTexture = NULL;

//================================================
//デフォルトコンストラクタ
//================================================
CBulletEnemy::CBulletEnemy(int nPriority) :CBullet(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nType = BULLET_TYPE_NONE;
	m_fRot = 0.0f;
	m_fDistance = 0.0f;
	m_bHoming = false;
	m_nLaserCounter = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CBulletEnemy::~CBulletEnemy()
{

}

//================================================
//初期化処理
//================================================
HRESULT CBulletEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	m_pos = pos;
	m_fDistance = 0.0f;
	m_size = size;
	m_move = move;
	m_bHoming = true;
	m_nLaserCounter = 0;

	CBullet::Init(pos, size, move);

	//オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_BULLET_ENEMY);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CBulletEnemy::Uninit(void)
{
	CBullet::Uninit();
}

//================================================
//更新処理
//================================================
void CBulletEnemy::Update(void)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//位置取得
	//m_pos = GetPos();

	m_pos += m_move;		//移動量反映

	//位置反映
	CScene2D::SetPos(m_pos, m_size);

	//画面外に出たら
	if (m_pos.x + m_size.x / 2.0f < 0.0f || m_pos.x - m_size.x / 2.0f > SCREEN_WIDTH ||
		m_pos.y + m_size.y / 2.0f < 0.0f || m_pos.y - m_size.y / 2.0f > SCREEN_HEIGHT)
	{
		Uninit();
		return;
	}

	//プレイヤーを取得
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			//シーンのnCnt番目のポインタ取得
			CScene *pScene;
			pScene = CScene::GetScene(nCntScene, nCntPriority);

			if (pScene != NULL)
			{
				//オブジェクトタイプ取得
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				if (objType == CScene::OBJTYPE_PLAYER)
				{
					//シーンのポインタをプレイヤーの型にキャスト
					CPlayer *pPlayer = (CPlayer*)pScene;

					//プレイヤーの状態がダメージを受けている状態でないとき当たり判定を行う
					if (pPlayer->GetPlayerState() != CPlayer::PLAYER_STATE_DAMAGE)
					{
						//弾の当たり判定
						if (Collision(m_pos, pSound) == true)
						{
							return;
						}
					}
				}
			}
		}
	}

	//ゲームの状態を取得
	if (CManager::GetMode() == CManager::MODE_GAME01)
	{
		if (CManager::GetGame01()->GetState() == CGame01::GAME_STATE_CLEAR)
		{
			Uninit();
			return;
		}
	}

	//移動の設定
	MoveType();
}

//================================================
//描画処理
//================================================
void CBulletEnemy::Draw(void)
{
	CBullet::Draw();
}

//================================================
//生成処理
//================================================
CBulletEnemy *CBulletEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CBulletEnemy::BULLET_TYPE type, CTexture::TYPE textureType)
{
	//インスタンスの生成
	CBulletEnemy *pBulletEnemy = NULL;
	if (pBulletEnemy == NULL)
	{
		pBulletEnemy = new CBulletEnemy;
		if (pBulletEnemy != NULL)
		{
			pBulletEnemy->Init(pos, size, move);
			m_pTexture = CManager::GetTexture()->GetTexture(textureType);
			pBulletEnemy->BindTexture(m_pTexture);
			pBulletEnemy->m_nType = type;
		}
	}
	return pBulletEnemy;
}

//================================================
//当たり判定処理
//================================================
bool CBulletEnemy::Collision(D3DXVECTOR3 pos, CSound *pSound)
{
	bool bCol = false;		//当たったかどうかのフラグ

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			//シーンのnCnt番目のポインタ取得
			CScene *pScene;
			pScene = CScene::GetScene(nCntScene, nCntPriority);

			if (pScene != NULL)
			{
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				if (objType == CScene::OBJTYPE_PLAYER)
				{
					D3DXVECTOR3 PlayerPos = pScene->GetPos();
					D3DXVECTOR3 PlayerSize = pScene->GetSize();
					if (pos.x + m_size.x / 2.0f >= PlayerPos.x - PlayerSize.x / 2.0f + PLAYER_COLLISION_ENEMY_BULLET_ADJUST &&
						pos.x - m_size.x / 2.0f <= PlayerPos.x + PlayerSize.x / 2.0f - PLAYER_COLLISION_ENEMY_BULLET_ADJUST &&
						pos.y + m_size.y / 2.0f >= PlayerPos.y - PlayerSize.y / 2.0f + PLAYER_COLLISION_ENEMY_BULLET_ADJUST &&
						pos.y - m_size.y / 2.0f <= PlayerPos.y + PlayerSize.y / 2.0f - PLAYER_COLLISION_ENEMY_BULLET_ADJUST)
					{
						//シーンのポインタをプレイヤーの型にキャスト
						CPlayer *pPlayer = (CPlayer*)pScene;

						//当たった判定
						bCol = true;
						//爆発の生成
						CExplosion::Create(PlayerPos, D3DXVECTOR3(EXPLOSION_WIDTH, EXPLOSION_HEIGHT, 0.0f));
						//サウンドの再生
						pSound->Play(CSound::SOUND_LABEL_EXPLOSION_SE);
						if (m_nType != BULLET_TYPE_LASER)
						{
							//弾の破棄
							Uninit();
						}
						//プレイヤーの状態を設定
						pPlayer->SetPlayerState(CPlayer::PLAYER_STATE_DAMAGE);
						//ライフのポインタ取得
						CLife *pLife;
						pLife = CGame01::GetLife();
						//プレイヤーのライフを減らす
						pPlayer->SetLife(-1);
						//ライフを設定
						pLife->SubtractLife(1);
						
						break;
					}
				}
			}
		}
	}
	return bCol;
}

//================================================
//移動量管理処理
//================================================
void CBulletEnemy::MoveType(void)
{
	//プレイヤーと弾の角度計算用
	float fTanR = 0.0f;
	//プレイヤーのポインター
	CPlayer *pPlayer = NULL;
	//プレイヤーの位置保存用
	D3DXVECTOR3 posPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//プレイヤーとの距離
	float fDiffer = 0;

	switch (m_nType)
	{
	case BULLET_TYPE_STRAIGHT:
		break;
	case BULLET_TYPE_HOMING:
		for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
		{
			for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
			{
				//シーンのnCnt番目のポインタ取得
				CScene *pScene;
				pScene = CScene::GetScene(nCntScene, nCntPriority);

				if (pScene != NULL)
				{
					//オブジェクトタイプ取得
					CScene::OBJTYPE objType;
					objType = pScene->GetObjType();

					if (objType == CScene::OBJTYPE_PLAYER)
					{
						//シーンのポインタをプレイヤーの型にキャスト
						pPlayer = (CPlayer*)pScene;

						//プレイヤーの位置を取得
						posPlayer = pPlayer->GetPos();

						fDiffer = sqrtf(((posPlayer.x - m_pos.x) * (posPlayer.x - m_pos.x)) + ((posPlayer.y - m_pos.y) * (posPlayer.y - m_pos.y)));
						if (fDiffer >= BULLET_ENEMY_FINISH_HOMING)
						{
							if (m_bHoming == true)
							{
								//プレイヤーと敵の弾の角度を計算
								fTanR = atan2f(posPlayer.y - m_pos.y, posPlayer.x - m_pos.x);
								//プレイヤーに向かって行くよう移動量を計算
								m_move = D3DXVECTOR3(cosf(fTanR) * BULLET_ENEMY_HOMING_SPEED, sinf(fTanR) * BULLET_ENEMY_HOMING_SPEED, 0.0f);
							}
						}
						else
						{
							m_bHoming = false;
						}
					}
				}
			}
		}
		break;
	case BULLET_TYPE_LASER:
		//カウンターを加算
		m_nLaserCounter++;
		
		if (m_nLaserCounter >= BOSS_BODY_SHOOT_LASER_TIME)
		{
			if (m_size.x <= 0.0f)
			{
				m_nLaserCounter = 0;
				m_size.x = 0.0f;
				Uninit();
			}
			else
			{
				//サイズを徐々に小さくする
				m_size.x -= 4.0f;
			}
		}
		else
		{
			//サイズを既定の大きさに保持する
			if (m_size.y >= BULLET_ENEMY_BOSS_LASER_HEIGHT)
			{
				m_size.y = BULLET_ENEMY_BOSS_LASER_HEIGHT;
			}
			else
			{
				//サイズを徐々に大きくする
				m_size.y += 20.0f;
				//y軸にサイズを伸ばした分位置のy座標を移動させる
				m_pos.y += 10.0f;
			}
			if (m_size.x >= BULLET_ENEMY_BOSS_LASER_WIDTH)
			{
				m_size.x = BULLET_ENEMY_BOSS_LASER_WIDTH;
			}
			else
			{
				//サイズを徐々に大きくする
				m_size.x += 5.0f;
			}

		}


		break;
	default:
		//assert(false);
		break;
	}
}