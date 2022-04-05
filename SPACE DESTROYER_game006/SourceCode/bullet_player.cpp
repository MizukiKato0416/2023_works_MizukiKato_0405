//================================================
//プレイヤーの弾処理
//Authore:加藤瑞葵
//================================================
#include "scene2D.h"
#include "scene.h"
#include "manager.h"
#include "bullet_player.h"
#include "renderer.h"
#include "explosion.h"
#include "sound.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"
#include "game01.h"
#include "texture.h"
#include "item.h"

#ifndef _DEBUG
//#define NDEBUG
#endif // !_DEBUG
#include <assert.h>

//================================================
//静的メンバ変数宣言
//================================================
LPDIRECT3DTEXTURE9 CBulletPlayer::m_pTexture = NULL;

//================================================
//デフォルトコンストラクタ
//================================================
CBulletPlayer::CBulletPlayer(int nPriority) :CBullet(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bHoming = false;
	m_nType = BULLET_TYPE_NONE;
	m_nEfectCounter = 0;
	m_fRot = 0.0f;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CBulletPlayer::~CBulletPlayer()
{

}

//================================================
//初期化処理
//================================================
HRESULT CBulletPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, float fRot)
{
	m_pos = pos;
	m_size = size;
	m_move = move;
	m_nEfectCounter = 0;
	m_bHoming = true;
	m_fRot = fRot;

	CBullet::Init(pos, size, m_move);

	//オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_BULLET_PLAYER);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CBulletPlayer::Uninit(void)
{
	CBullet::Uninit();
}

//================================================
//更新処理
//================================================
void CBulletPlayer::Update(void)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//位置取得
	m_pos = GetPos();

	m_pos += m_move;		//移動量反映

	//エフェクトのカウンターを加算
	m_nEfectCounter++;
	if (m_nEfectCounter >= BULLET_PLAYER_EFFECT_INTERVAL)
	{
		//エフェクトの生成
		CEffect::Create(m_pos, D3DXVECTOR3(30.0f , 30.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(255.0f, 165.0f, 0.0f, 255.0f),
						CEffect::EFFECT_TYPE_NORMAL);
		m_nEfectCounter = 0;
	}

	//位置反映
	CScene2D::SetPos(m_pos, m_size, m_fRot);


	//画面外に出たら
	if (m_pos.x + m_size.x / 2.0f < 0.0f || m_pos.x - m_size.x / 2.0f > SCREEN_WIDTH ||
		m_pos.y + m_size.y / 2.0f < 0.0f || m_pos.y - m_size.y / 2.0f > SCREEN_HEIGHT)
	{
		Uninit();
		return;
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
void CBulletPlayer::Draw(void)
{
	CBullet::Draw();
}

//================================================
//生成処理
//================================================
CBulletPlayer *CBulletPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CBulletPlayer::BULLET_TYPE type, float fRot)
{
	//インスタンスの生成
	CBulletPlayer *pBulletPlayer = NULL;
	if (pBulletPlayer == NULL)
	{
		pBulletPlayer = new CBulletPlayer;
		if (pBulletPlayer != NULL)
		{
			pBulletPlayer->Init(pos, size, move, fRot);
			m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_BULLET_PLAYER_NORMAL);
			pBulletPlayer->BindTexture(m_pTexture);
			pBulletPlayer->m_nType = type;
		}
	}
	return pBulletPlayer;
}

//================================================
//当たり判定処理
//================================================
float CBulletPlayer::GetRot(void)
{
	return m_fRot;
}

//================================================
//移動量管理処理
//================================================
void CBulletPlayer::MoveType(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//敵と弾の角度計算用
	float fTanR = 0.0f;
	//敵のポインター
	CEnemy *pEnemy = NULL;
	//プレイヤーの位置保存用
	D3DXVECTOR3 posEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//敵と弾との距離
	float fDiffer = 0;

	switch (m_nType)
	{
	case BULLET_TYPE_STRAIGHT:
		break;

	case BULLET_TYPE_DIFFUSION:

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

					if (objType == CScene::OBJTYPE_ENEMY)
					{
						//シーンのポインタを敵の型にキャスト
						pEnemy = (CEnemy*)pScene;

						if (pEnemy != NULL)
						{
							//敵のの位置を取得
							posEnemy = pEnemy->GetPos();

							fDiffer = sqrtf(((posEnemy.x - m_pos.x) * (posEnemy.x - m_pos.x)) + ((posEnemy.y - m_pos.y) * (posEnemy.y - m_pos.y)));
							if (fDiffer >= BULLET_PLAYER_FINISH_HOMING)
							{
								if (m_bHoming == true)
								{
									//プレイヤーの弾と敵の角度を計算
									fTanR = atan2f(posEnemy.y - m_pos.y, posEnemy.x - m_pos.x);
									//敵に向かって行くよう移動量を計算
									m_move = D3DXVECTOR3(cosf(fTanR) * -BULLET_PLAYER_SPEED, sinf(fTanR) * -BULLET_PLAYER_SPEED, 0.0f);
								}
							}
							else
							{
								m_bHoming = false;
							}
							break;
						}
					}
				}
			}
		}
		break;
	default:
		assert(false);
		break;
	}
}