//================================================
//ボスの処理
//Authore:加藤瑞葵
//================================================
#include "renderer.h"
#include "scene2D.h"
#include "manager.h"
#include "boss.h"
#include "texture.h"
#include "sound.h"
#include "score.h"
#include "explosion.h"
#include "game01.h"
#include "item.h"
#include "bullet_player.h"
#include "player.h"
#include "life.h"
#include "bullet_enemy.h"
#include "effect.h"
#include "Input_pad_x.h"


//================================================
//静的メンバ変数宣言
//================================================
LPDIRECT3DTEXTURE9 CBoss::m_pTexture[MAX_BOSS_POLYGON] = {};

//================================================
//デフォルトコンストラクタ
//================================================
CBoss::CBoss(int nPriority) :CScene(nPriority)
{
	for (int nCntPolygon = 0; nCntPolygon < MAX_BOSS_POLYGON; nCntPolygon++)
	{
		m_apScene2D[nCntPolygon] = NULL;
		m_size[nCntPolygon] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pos[nCntPolygon] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_nBulletCounter[nCntPolygon] = 0;
		m_state[nCntPolygon] = BOSS_STATE_NONE;
		m_nDamageCounter[nCntPolygon] = 0;
		m_nLife[nCntPolygon] = 0;
	}

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_shootPhase = BOSS_BODY_SHOOT_PHASE_NONE;
	m_nNextPhase = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CBoss::~CBoss()
{

}

//================================================
//初期化処理
//================================================
HRESULT CBoss::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//変数初期化
	m_size[0] = D3DXVECTOR3(BOSS_WING_WIDTH, BOSS_WING_HEIGHT, 0.0f);
	m_size[1] = D3DXVECTOR3(BOSS_BODY_WIDTH, BOSS_BODY_HEIGHT, 0.0f);
	m_size[2] = D3DXVECTOR3(BOSS_CANNON_WIDTH, BOSS_CANNON_HEIGHT, 0.0f);
	m_size[3] = D3DXVECTOR3(BOSS_CANNON_WIDTH, BOSS_CANNON_HEIGHT, 0.0f);

	for (int nCntPolygon = 0; nCntPolygon < MAX_BOSS_POLYGON; nCntPolygon++)
	{
		m_size[nCntPolygon].x *= scale.x;
		m_size[nCntPolygon].y *= scale.y;
		m_size[nCntPolygon].z *= scale.z;

		m_nBulletCounter[nCntPolygon] = 0;
		m_state[nCntPolygon] = BOSS_STATE_NORMAL;
		m_nDamageCounter[nCntPolygon] = 0;
	}
	m_pos[0] = pos;
	m_pos[1] = pos;
	m_pos[2] = D3DXVECTOR3(pos.x + BOSS_CANNON_POS, pos.y, pos.z);
	m_pos[3] = D3DXVECTOR3(pos.x - BOSS_CANNON_POS, pos.y, pos.z);

	m_move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_nLife[0] = BOSS_WING_LIFE;
	m_nLife[1] = BOSS_BODY_LIFE;
	m_nLife[2] = BOSS_CANNON_LIFE;
	m_nLife[3] = BOSS_CANNON_LIFE;

	m_shootPhase = BOSS_BODY_SHOOT_PHASE_STRAIGHT;
	m_nNextPhase = 0;

	for (int nCntPolygon = 0; nCntPolygon < MAX_BOSS_POLYGON; nCntPolygon++)
	{
		//ポリゴンの生成
		m_apScene2D[nCntPolygon] = new CScene2D(PRIORITY_BOSS);
		m_apScene2D[nCntPolygon]->Init(pos, scale);

		//テクスチャの割り当て
		m_apScene2D[nCntPolygon]->BindTexture(m_pTexture[nCntPolygon]);

		//位置を設定
		m_apScene2D[nCntPolygon]->SetPos(m_pos[nCntPolygon], m_size[nCntPolygon]);
	}

	//オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_BOSS);

	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化

	return S_OK;
}

//================================================
//終了処理
//================================================
void CBoss::Uninit(void)
{
	for (int nCntPolygon = 0; nCntPolygon < MAX_BOSS_POLYGON; nCntPolygon++)
	{
		if (m_apScene2D[nCntPolygon] != NULL)
		{
			m_apScene2D[nCntPolygon]->Uninit();
			m_apScene2D[nCntPolygon] = NULL;
		}
	}

	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CBoss::Update(void)
{
	//ゲームクリア時の処理
	if (CManager::GetGame01()->GetState() == CGame01::GAME_STATE_CLEAR)
	{
		if (GameClear() == true)
		{
			return;
		}
	}
	else if(CManager::GetGame01()->GetState() == CGame01::GAME_STATE_GAME)
	{
		for (int nCntPolygon = 0; nCntPolygon < MAX_BOSS_POLYGON; nCntPolygon++)
		{
			if (m_apScene2D[nCntPolygon] != NULL)
			{
				//位置を取得
				m_pos[nCntPolygon] = m_apScene2D[nCntPolygon]->GetPos();
				//移動量を位置に反映
				m_pos[nCntPolygon] += m_move;

				if (m_pos[nCntPolygon].y >= 100.0f)
				{
					m_pos[nCntPolygon].y = 100.0f;
				}

				//位置を設定
				m_apScene2D[nCntPolygon]->SetPos(m_pos[nCntPolygon], m_size[nCntPolygon]);
				SetPos(m_pos[nCntPolygon]);
				//サイズを設定
				SetSize(m_size[nCntPolygon]);
				//状態によって色を変える
				StateColor(nCntPolygon);
				//射撃処理
				if (nCntPolygon != 0)	//羽には射撃処理を行わせない
				{
					Shoot(nCntPolygon);
				}
			}
		}

		//当たり判定
		if (CollisionPlayerBullet() == true)
		{
			return;
		}
	}
}

//================================================
//描画処理
//================================================
void CBoss::Draw(void)
{
	
}

//================================================
//生成処理
//================================================
CBoss* CBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move)
{
	//インスタンスの生成
	CBoss *pBoss = NULL;
	if (pBoss == NULL)
	{
		pBoss = new CBoss;
		if (pBoss != NULL)
		{
			//テクスチャ割り当て
			m_pTexture[0] = CManager::GetTexture()->GetTexture(CTexture::TYPE_BOSS_WING);
			m_pTexture[1] = CManager::GetTexture()->GetTexture(CTexture::TYPE_BOSS_BODY);
			m_pTexture[2] = CManager::GetTexture()->GetTexture(CTexture::TYPE_BOSS_CANNON);
			m_pTexture[3] = CManager::GetTexture()->GetTexture(CTexture::TYPE_BOSS_CANNON);
			pBoss->Init(pos, scale);
		}
	}
	return pBoss;
}

//================================================
//状態に応じた色に変化させる処理
//================================================
void CBoss::StateColor(int nCntPolygon)
{
	switch (m_state[nCntPolygon])
	{
	case BOSS_STATE_NORMAL:
		break;
	case BOSS_STATE_DAMAGE:
		//カウンターを加算
		m_nDamageCounter[nCntPolygon]++;
		if (m_nDamageCounter[nCntPolygon] >= BOSS_DAMAGE_COUNT)
		{
			//カウンターを0にする
			m_nDamageCounter[nCntPolygon] = 0;
			//状態をNORMALに戻す
			m_state[nCntPolygon] = BOSS_STATE_NORMAL;
			//色を元に戻す
			m_apScene2D[nCntPolygon]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			//赤くする
			m_apScene2D[nCntPolygon]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
		break;
	default:
		break;
	}
}

//================================================
//プレイヤーの弾との当たり判定処理
//================================================
bool CBoss::CollisionPlayerBullet(void)
{
	bool bCol = false;	//当たったかどうかのフラグ

	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//スコアのポインタ取得
	CScore *pScore;
	pScore = CGame01::GetScore();

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

				if (objType == CScene::OBJTYPE_BULLET_PLAYER)
				{
					//弾のサイズと位置取得
					D3DXVECTOR3 BulletPlayerPos = pScene->GetPos();
					D3DXVECTOR3 BulletPlayerSize = pScene->GetSize();
					//弾の向き取得
					CBulletPlayer *pBulletPlayer = (CBulletPlayer*)pScene;
					float fBulletPlayerRot = pBulletPlayer->GetRot();
					//サイズを弾の向きによって調整
					D3DXVECTOR3 BulletSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					if (fBulletPlayerRot == 0.0f)
					{
						BulletSize = D3DXVECTOR3(BulletPlayerSize.x, BulletPlayerSize.y, 0.0f);
					}
					else
					{
						BulletSize = D3DXVECTOR3(BulletPlayerSize.y, BulletPlayerSize.x, 0.0f);
					}


					for (int nCntPolygon = 0; nCntPolygon < MAX_BOSS_POLYGON; nCntPolygon++)
					{
						if (m_apScene2D[nCntPolygon] != NULL)
						{
							float fAdjust = 0;		//当たり判定調整用

							//当たり判定を調節
							if (nCntPolygon == 0)
							{
								fAdjust = BOSS_WING_COLLISION_ADJUST;
							}
							else if (nCntPolygon == 1)
							{
								fAdjust = BOSS_BODY_COLLISION_ADJUST;
							}
							else
							{
								fAdjust = BOSS_CANNON_COLLISION_ADJUST;
							}

							if (m_pos[nCntPolygon].x + m_size[nCntPolygon].x / 2.0f >= BulletPlayerPos.x - BulletSize.x / 2.0f &&
								m_pos[nCntPolygon].x - m_size[nCntPolygon].x / 2.0f <= BulletPlayerPos.x + BulletSize.x / 2.0f &&
								m_pos[nCntPolygon].y + m_size[nCntPolygon].y / 2.0f + fAdjust >= BulletPlayerPos.y - BulletSize.y / 2.0f &&
								m_pos[nCntPolygon].y - m_size[nCntPolygon].y / 2.0f <= BulletPlayerPos.y + BulletSize.y / 2.0f)
							{
								//当たった判定
								bCol = true;
								//爆発の生成
								CExplosion::Create(BulletPlayerPos, D3DXVECTOR3(EXPLOSION_WIDTH, EXPLOSION_HEIGHT, 0.0f));
								//サウンドの再生
								pSound->Play(CSound::SOUND_LABEL_EXPLOSION_SE);

								//羽はダメージを受けない
								if (nCntPolygon != 0)
								{
									//アイテムの生成
									CItem::Create(BulletPlayerPos, D3DXVECTOR3(ITEM_SCORE_WIDTH, ITEM_SCORE_HEIGHT, 0.0f), CItem::ITEM_TYPE_SCORE);
									//スコア加算
									pScore->AddScore(100);
									//当たった部位をダメージ状態にする
									m_state[nCntPolygon] = BOSS_STATE_DAMAGE;
									//ライフを減らす
									m_nLife[nCntPolygon]--;
								}
								
								//ライフが0になったら
								if (m_nLife[nCntPolygon] <= 0)
								{
									m_nLife[nCntPolygon] = 0;
									//体のライフが0になったら
									if (nCntPolygon == 1)
									{
										//ゲームクリアにする
										CManager::GetGame01()->SetState(CGame01::GAME_STATE_CLEAR);
										//状態を元に戻す
										m_state[nCntPolygon] = BOSS_STATE_NORMAL;
										//色を元に戻す
										m_apScene2D[nCntPolygon]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
										//カウンターを0にする
										m_nDamageCounter[nCntPolygon] = 0;
									}
									else
									{
										//ライフが0になった部位を破棄
										m_apScene2D[nCntPolygon]->Uninit();
										m_apScene2D[nCntPolygon] = NULL;
									}
								}
								//弾の破棄
								pScene->Uninit();
								return bCol;
							}
						}
					}
				}
				else if (objType == CScene::OBJTYPE_PLAYER)
				{
					//プレイヤーのサイズと位置取得
					D3DXVECTOR3 PlayerPos = pScene->GetPos();
					D3DXVECTOR3 PlayerSize = pScene->GetSize();

					for (int nCntPolygon = 0; nCntPolygon < MAX_BOSS_POLYGON; nCntPolygon++)
					{
						if (m_apScene2D[nCntPolygon] != NULL)
						{
							float fAdjust = 0;		//当たり判定調整用

													//当たり判定を調節
							if (nCntPolygon == 0)
							{
								fAdjust = BOSS_BODY_COLLISION_PLAYER_ADJUST;
							}
							else if (nCntPolygon == 1)
							{
								fAdjust = BOSS_BODY_COLLISION_PLAYER_ADJUST;
							}
							else
							{
								fAdjust = BOSS_CANNON_COLLISION_PLAYER_ADJUST;
							}

							if (m_pos[nCntPolygon].x + m_size[nCntPolygon].x / 2.0f >= PlayerPos.x - PlayerSize.x / 2.0f &&
								m_pos[nCntPolygon].x - m_size[nCntPolygon].x / 2.0f <= PlayerPos.x + PlayerSize.x / 2.0f &&
								m_pos[nCntPolygon].y + m_size[nCntPolygon].y / 2.0f + fAdjust >= PlayerPos.y - PlayerSize.y / 2.0f &&
								m_pos[nCntPolygon].y - m_size[nCntPolygon].y / 2.0f <= PlayerPos.y + PlayerSize.y / 2.0f)
							{
								//シーンのポインタをプレイヤーの型にキャスト
								CPlayer *pPlayer = (CPlayer*)pScene;

								if (pPlayer->GetPlayerState() != CPlayer::PLAYER_STATE_DAMAGE)
								{
									//当たった判定
									bCol = true;
									//爆発の生成
									CExplosion::Create(PlayerPos, D3DXVECTOR3(EXPLOSION_WIDTH, EXPLOSION_HEIGHT, 0.0f));
									//サウンドの再生
									pSound->Play(CSound::SOUND_LABEL_EXPLOSION_SE);
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
			}
		}
	}
	return bCol;
}

//================================================
//射撃処理
//================================================
void CBoss::Shoot(int nCntPolygon)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//カウンターを加算
	m_nBulletCounter[nCntPolygon]++;
	if (nCntPolygon == 1)
	{
		BodyShoot(nCntPolygon);
	}
	else
	{
		if (m_nBulletCounter[nCntPolygon] >= BOSS_CANNON_SHOOT_COUNTER)
		{
			m_nBulletCounter[nCntPolygon] = 0;

			//弾の生成
			CBulletEnemy::Create(D3DXVECTOR3(m_pos[nCntPolygon].x - BOSS_CANNON_SHOOT_ADJUST_X, m_pos[nCntPolygon].y + BOSS_CANNON_SHOOT_ADJUST_Y, 0.0f),
									D3DXVECTOR3(BULLET_ENEMY_BOSS_CANNON_HOMING_WIDTH, BULLET_ENEMY_BOSS_CANNON_HOMING_HEIGHT, 0.0f),
									D3DXVECTOR3(0.0f, BULLET_ENEMY_HOMING_SPEED, 0.0f), CBulletEnemy::BULLET_TYPE_HOMING,
									CTexture::TYPE_BULLET_SPHERE);
			//弾の生成
			CBulletEnemy::Create(D3DXVECTOR3(m_pos[nCntPolygon].x + BOSS_CANNON_SHOOT_ADJUST_X, m_pos[nCntPolygon].y + BOSS_CANNON_SHOOT_ADJUST_Y, 0.0f),
									D3DXVECTOR3(BULLET_ENEMY_BOSS_CANNON_HOMING_WIDTH, BULLET_ENEMY_BOSS_CANNON_HOMING_HEIGHT, 0.0f),
									D3DXVECTOR3(0.0f, BULLET_ENEMY_HOMING_SPEED, 0.0f), CBulletEnemy::BULLET_TYPE_HOMING,
									CTexture::TYPE_BULLET_SPHERE);
		}
	}
}

//================================================
////体部分の射撃処理処理
//================================================
void CBoss::BodyShoot(int nCntPolygon)
{
	//パッド取得処理
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//次のフェーズに行くまでのカウンターを加算
	m_nNextPhase++;


	//フェーズ別に処理を分ける
	switch (m_shootPhase)
	{
	case BOSS_BODY_SHOOT_PHASE_STRAIGHT:
		if (m_nBulletCounter[nCntPolygon] == BOSS_BODY_SHOOT_STRAIGHT_COUNT_0)
		{
			//サウンドの再生
			pSound->Play(CSound::SOUND_LABEL_BOSS_BULLET_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_BOSS_BULLET_SE, 1.6f);

			//弾の生成
			CBulletEnemy::Create(D3DXVECTOR3(m_pos[nCntPolygon].x - BOSS_BODY_SHOOT_STRAIGHT_ADJUST, m_pos[nCntPolygon].y + BOSS_BODY_SHOOT_ADJUST_Y, 0.0f),
									D3DXVECTOR3(BULLET_ENEMY_BOSS_STRAIGHT_WIDTH, BULLET_ENEMY_BOSS_STRAIGHT_HEIGHT, 0.0f),
									D3DXVECTOR3(0.0f, BULLET_ENEMY_SPEED, 0.0f), CBulletEnemy::BULLET_TYPE_STRAIGHT,
									CTexture::TYPE_BULLET_BOSS_STRAIGHT);

			//弾の生成
			CBulletEnemy::Create(D3DXVECTOR3(m_pos[nCntPolygon].x + BOSS_BODY_SHOOT_STRAIGHT_ADJUST, m_pos[nCntPolygon].y + BOSS_BODY_SHOOT_ADJUST_Y, 0.0f),
									D3DXVECTOR3(BULLET_ENEMY_BOSS_STRAIGHT_WIDTH, BULLET_ENEMY_BOSS_STRAIGHT_HEIGHT, 0.0f),
									D3DXVECTOR3(0.0f, BULLET_ENEMY_SPEED, 0.0f), CBulletEnemy::BULLET_TYPE_STRAIGHT, 
									CTexture::TYPE_BULLET_BOSS_STRAIGHT);
		}
		else if (m_nBulletCounter[nCntPolygon] >= BOSS_BODY_SHOOT_STRAIGHT_COUNT_1)
		{
			//サウンドの再生
			pSound->Play(CSound::SOUND_LABEL_BOSS_BULLET_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_BOSS_BULLET_SE, 1.6f);

			//弾の生成
			CBulletEnemy::Create(D3DXVECTOR3(m_pos[nCntPolygon].x, m_pos[nCntPolygon].y + BOSS_BODY_SHOOT_ADJUST_Y, 0.0f),
									D3DXVECTOR3(BULLET_ENEMY_BOSS_STRAIGHT_WIDTH, BULLET_ENEMY_BOSS_STRAIGHT_HEIGHT, 0.0f),
									D3DXVECTOR3(0.0f, BULLET_ENEMY_SPEED, 0.0f), CBulletEnemy::BULLET_TYPE_STRAIGHT, 
									CTexture::TYPE_BULLET_BOSS_STRAIGHT);

			m_nBulletCounter[nCntPolygon] = 0;
		}

		//一定時間を超えたら次のフェーズに移行
		if (m_nNextPhase >= BOSS_BODY_SHOOT_STRAIGHT_PHASE_COUNT)
		{
			m_nBulletCounter[nCntPolygon] = 0;
			m_nNextPhase = 0;
			m_shootPhase = BOSS_BODY_SHOOT_PHASE_DIFFUSION_00;
		}
		break;
	case BOSS_BODY_SHOOT_PHASE_DIFFUSION_00:
		if (m_nBulletCounter[nCntPolygon] == BOSS_BODY_SHOOT_DIFFUSION_00_COUNT)
		{
			//サウンドの再生
			pSound->Play(CSound::SOUND_LABEL_BOSS_BULLET_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_BOSS_BULLET_SE, 1.6f);

			for (int nCntBullet = 0; nCntBullet < BOSS_BODY_SHOOT_DIFFUSION_00_NUM; nCntBullet++)
			{
				//弾の生成
				CBulletEnemy::Create(D3DXVECTOR3(m_pos[nCntPolygon].x, m_pos[nCntPolygon].y + BOSS_BODY_SHOOT_ADJUST_Y, 0.0f),
										D3DXVECTOR3(BULLET_ENEMY_BOSS_DIFFUSION_WIDTH, BULLET_ENEMY_BOSS_DIFFUSION_HEIGHT, 0.0f),
										D3DXVECTOR3(BULLET_ENEMY_SPEED * cosf((D3DX_PI / (float)(BOSS_BODY_SHOOT_DIFFUSION_00_NUM + 1) * (nCntBullet + 1))),
													BULLET_ENEMY_SPEED * sinf((D3DX_PI / (float)(BOSS_BODY_SHOOT_DIFFUSION_00_NUM + 1) * (nCntBullet + 1))), 0.0f),
										CBulletEnemy::BULLET_TYPE_STRAIGHT, CTexture::TYPE_BULLET_SPHERE);
			}
		}
		else if(m_nBulletCounter[nCntPolygon] >= BOSS_BODY_SHOOT_DIFFUSION_01_COUNT)
		{
			//サウンドの再生
			pSound->Play(CSound::SOUND_LABEL_BOSS_BULLET_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_BOSS_BULLET_SE, 1.6f);

			for (int nCntBullet = 0; nCntBullet < BOSS_BODY_SHOOT_DIFFUSION_01_NUM; nCntBullet++)
			{
				//弾の生成
				CBulletEnemy::Create(D3DXVECTOR3(m_pos[nCntPolygon].x, m_pos[nCntPolygon].y + BOSS_BODY_SHOOT_ADJUST_Y, 0.0f),
										D3DXVECTOR3(BULLET_ENEMY_BOSS_DIFFUSION_WIDTH, BULLET_ENEMY_BOSS_DIFFUSION_HEIGHT, 0.0f),
										D3DXVECTOR3(BULLET_ENEMY_SPEED * cosf((D3DX_PI / (float)(BOSS_BODY_SHOOT_DIFFUSION_01_NUM + 1) * (nCntBullet + 1))),
													BULLET_ENEMY_SPEED * sinf((D3DX_PI / (float)(BOSS_BODY_SHOOT_DIFFUSION_01_NUM + 1) * (nCntBullet + 1))), 0.0f),
										CBulletEnemy::BULLET_TYPE_STRAIGHT, CTexture::TYPE_BULLET_SPHERE);
			}
			m_nBulletCounter[nCntPolygon] = 0;
		}

		//一定時間を超えたら次のフェーズに移行
		if (m_nNextPhase >= BOSS_BODY_SHOOT_DIFFUSION_PHASE_COUNT)
		{
			m_nBulletCounter[nCntPolygon] = 0;
			m_nNextPhase = 0;
			m_shootPhase = BOSS_BODY_SHOOT_PHASE_LASER;
		}
		break;
	case BOSS_BODY_SHOOT_PHASE_LASER:
		if (m_nBulletCounter[nCntPolygon] <= BOSS_BODY_SHOOT_LASER_EFFECT_TIME)
		{
			if (m_nBulletCounter[nCntPolygon] % BOSS_BODY_SHOOT_LASER_EFFECT_COUNT == 0)
			{
				for (int nCntEffect = 0; nCntEffect < BOSS_BODY_SHOOT_LASER_EFFECT_NUM; nCntEffect++)
				{
					//エフェクト生成
					CEffect::Create(D3DXVECTOR3(m_pos[nCntPolygon].x + BOSS_BODY_SHOOT_LASER_EFFECT_ADJUST * cosf((D3DX_PI / (float)(BOSS_BODY_SHOOT_LASER_EFFECT_NUM + 1) * (nCntEffect + 1))),
												m_pos[nCntPolygon].y + BOSS_BODY_SHOOT_LASER_EFFECT_ADJUST  * sinf((D3DX_PI / (float)(BOSS_BODY_SHOOT_LASER_EFFECT_NUM + 1) * (nCntEffect + 1))), 0.0f),
									D3DXVECTOR3(0.1f, 0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									D3DXCOLOR(255.0f, 0.0f, 255.0f, 255.0f), CEffect::EFFECT_TYPE_BOSS_LASER);
				}
			}
		}
		else if (m_nBulletCounter[nCntPolygon] == BOSS_BODY_SHOOT_LASER_COUNT)
		{
			//サウンドの再生
			pSound->Play(CSound::SOUND_LABEL_BOSS_LASER_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_BOSS_LASER_SE, 2.8f);

			//弾の生成
			CBulletEnemy::Create(D3DXVECTOR3(m_pos[nCntPolygon].x, m_pos[nCntPolygon].y + BOSS_BODY_SHOOT_ADJUST_Y, 0.0f),
									D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									D3DXVECTOR3(0.0f, 0.0f, 0.0f), CBulletEnemy::BULLET_TYPE_LASER,
									CTexture::TYPE_BULLET_BOSS_LASER);

			//バイブレーション設定
			pInputPadX->SetVibration(60000, 60000, BOSS_BODY_SHOOT_LASER_TIME);

		}
		//一定時間を超えたら次のフェーズに移行
		if (m_nNextPhase >= BOSS_BODY_SHOOT_LASER_PHASE_COUNT)
		{
			m_nBulletCounter[nCntPolygon] = 0;
			m_nNextPhase = 0;
			m_shootPhase = BOSS_BODY_SHOOT_PHASE_HOMING;
		}
		break;
	case BOSS_BODY_SHOOT_PHASE_HOMING:
		if (m_nBulletCounter[nCntPolygon] % BOSS_BODY_SHOOT_HOMING_COUNT == 0)
		{
			//サウンドの再生
			pSound->Play(CSound::SOUND_LABEL_BOSS_BULLET_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_BOSS_BULLET_SE, 1.6f);

			//弾の生成
			CBulletEnemy::Create(D3DXVECTOR3(m_pos[nCntPolygon].x + BOSS_CANNON_SHOOT_ADJUST_X, m_pos[nCntPolygon].y + BOSS_CANNON_SHOOT_ADJUST_Y, 0.0f),
									D3DXVECTOR3(BULLET_ENEMY_BOSS_BODY_HOMING_WIDTH, BULLET_ENEMY_BOSS_BODY_HOMING_HEIGHT, 0.0f),
									D3DXVECTOR3(0.0f, BULLET_ENEMY_HOMING_SPEED, 0.0f), CBulletEnemy::BULLET_TYPE_HOMING,
									CTexture::TYPE_BULLET_BOSS_BODY_HOMING);
		}
		//一定時間を超えたら次のフェーズに移行
		if (m_nNextPhase >= BOSS_BODY_SHOOT_HOMING_PHASE_COUNT)
		{
			m_nBulletCounter[nCntPolygon] = 0;
			m_nNextPhase = 0;
			m_shootPhase = BOSS_BODY_SHOOT_PHASE_STRAIGHT;
		}
		break;
	default:
		break;
	}
}

//================================================
//体の位置取得処理
//================================================
D3DXVECTOR3 CBoss::GetBodyPos(void)
{
	return m_pos[1];
}

//================================================
//ゲームクリア時の処理
//================================================
bool CBoss::GameClear(void)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//フレーム数取得
	int nClearCounter = CGame01::GetFinishCounter();

	if (nClearCounter == BOSS_CLEAR_UNINIT_COUNT)
	{
		//ボスを破棄
		Uninit();
		return true;
	}
	else
	{
		if (nClearCounter % BOSS_CLEAR_EXPLOSION_COUNT == 0)
		{
			//サウンドの再生
			pSound->Play(CSound::SOUND_LABEL_DIE_EXPLOSION_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_BOSS_BULLET_SE, 1.6f);

			//爆発の生成
			CExplosion::Create(D3DXVECTOR3(BOSS_CLEAR_EXPLOSION_POS_X, BOSS_CLEAR_EXPLOSION_POS_Y, 0.0f),
								D3DXVECTOR3(EXPLOSION_BOSS_UNINIT_WIDTH, EXPLOSION_BOSS_UNINIT_HEIGHT, 0.0f));
		}
	}
	return false;
}
