//================================================
//敵処理
//Authore:加藤瑞葵
//================================================
#include "scene2D.h"
#include "manager.h"
#include "input_keyboard.h"
#include "enemy.h"
#include "enemy_Item_power.h"
#include "bullet.h"
#include "bullet_player.h"
#include "renderer.h"
#include "sound.h"
#include "scene.h"
#include "texture.h"
#include "mover.h"
#include "score.h"
#include "game01.h"
#include "explosion.h"
#include "sound.h"
#include "item.h"
#include "effect.h"
#include "tutorial.h"
#include "ui_move.h"

//================================================
//静的メンバ変数宣言
//================================================
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;				//共有テクスチャのポインタ

//================================================
//デフォルトコンストラクタ
//================================================
CEnemy::CEnemy(int nPriority) :CScene2D(nPriority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntFrame = 0;
	m_pMover = NULL;
	m_moverType = CMover::MOVER_TYPE_NONE;
	m_nLife = 0;
	m_nBulletCounter = 0;
	m_state = ENEMY_STATE_NONE;
	m_type = ENEMY_TYPE_NONE;
	m_nDamageCounter = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CEnemy::~CEnemy()
{

}

//================================================
//初期化処理
//================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	m_size = size;
	m_pos = pos;
	m_move = move;
	m_nCntFrame = 0;
	m_state = ENEMY_STATE_NORMAL;
	m_nDamageCounter = 0;

	//オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_ENEMY);

	CScene2D::Init(pos, size);
	return S_OK;
}

//================================================
//終了処理
//================================================
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//================================================
//更新処理
//================================================
void CEnemy::Update(void)
{
	//状態による色の変化処理
	StateColor();
	//当たり判定
	if (Collision() == true)
	{
		return;
	}
}

//================================================
//描画処理
//================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//================================================
//生成処理
//================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	//インスタンスの生成
	CEnemy *pEnemy = NULL;
	if (pEnemy == NULL)
	{
		pEnemy = new CEnemy;
		if (pEnemy != NULL)
		{
			pEnemy->Init(pos, size, move);
		}
	}
	return pEnemy;
}

//================================================
//状態に応じた色に変化させる処理
//================================================
void CEnemy::StateColor(void)
{
	switch (m_state)
	{
	case ENEMY_STATE_NORMAL:
		break;
	case ENEMY_STATE_DAMAGE:
		//カウンターを加算
		m_nDamageCounter++;
		if (m_nDamageCounter >= ENEMY_DAMAGE_COUNT)
		{
			//カウンターを0にする
			m_nDamageCounter = 0;
			//状態をNORMALに戻す
			m_state = ENEMY_STATE_NORMAL;
			//色を元に戻す
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			//赤くする
			SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
		break;
	default:
		break;
	}
}

//================================================
//当たり判定処理
//================================================
bool CEnemy::Collision(void)
{
	//位置取得
	m_pos = GetPos();

	//スコアのポインタ取得
	CScore *pScore;
	pScore = CGame01::GetScore();

	bool bCol = false;

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

					if (m_pos.x + m_size.x / 2.0f >= BulletPlayerPos.x - BulletSize.x / 2.0f && m_pos.x - m_size.x / 2.0f <= BulletPlayerPos.x + BulletSize.x / 2.0f &&
						m_pos.y + m_size.y / 2.0f >= BulletPlayerPos.y - BulletSize.y / 2.0f && m_pos.y - m_size.y / 2.0f <= BulletPlayerPos.y + BulletSize.y / 2.0f)
					{
						//サウンド取得処理
						CSound *pSound;
						pSound = CManager::GetSound();
						//当たった判定
						bCol = true;
						//爆発の生成
						CExplosion::Create(BulletPlayerPos, D3DXVECTOR3(EXPLOSION_WIDTH, EXPLOSION_HEIGHT, 0.0f));
						//サウンドの再生
						pSound->Play(CSound::SOUND_LABEL_EXPLOSION_SE);	
						//敵の状態をダメージにする
						m_state = ENEMY_STATE_DAMAGE;
						//弾の破棄
						pScene->Uninit();
						//敵のライフを減らす
						m_nLife--;
						if (m_nLife <= 0)
						{
							m_nLife = 0;

							//敵の種類によって処理分岐
							switch (m_type)
							{
							case ENEMY_TYPE_FIGHTER:
								if (CManager::GetMode() == CManager::MODE_TUTORIAL)
								{
									CTutorial::SetEnemyKill(true);
								}
								else
								{
									//スコア加算
									pScore->AddScore(100);
									//アイテムの生成
									CItem::Create(m_pos, D3DXVECTOR3(ITEM_SCORE_WIDTH, ITEM_SCORE_HEIGHT, 0.0f), CItem::ITEM_TYPE_SCORE);
									//スコアのポリゴン生成
									CUiMove::Create(m_pos, D3DXVECTOR3(UI_ENEMY_KILL_SCORE_WIDTH, UI_ENEMY_KILL_SCORE_HEIGHT, 0.0f),
													D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_ENEMY_KILL_SCORE_100);
								}
								break;
							case ENEMY_TYPE_SPHERE:
								//スコア加算
								pScore->AddScore(400);
								//アイテムの生成
								CItem::Create(m_pos, D3DXVECTOR3(ITEM_SCORE_WIDTH, ITEM_SCORE_HEIGHT, 0.0f), CItem::ITEM_TYPE_SCORE);
								//スコアのポリゴン生成
								CUiMove::Create(m_pos, D3DXVECTOR3(UI_ENEMY_KILL_SCORE_WIDTH, UI_ENEMY_KILL_SCORE_HEIGHT, 0.0f),
												D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_ENEMY_KILL_SCORE_400);
								break;
							case ENEMY_TYPE_UFO:
								//スコア加算
								pScore->AddScore(200);
								//アイテムの生成
								CItem::Create(m_pos, D3DXVECTOR3(ITEM_SCORE_WIDTH, ITEM_SCORE_HEIGHT, 0.0f), CItem::ITEM_TYPE_SCORE);
								//スコアのポリゴン生成
								CUiMove::Create(m_pos, D3DXVECTOR3(UI_ENEMY_KILL_SCORE_WIDTH, UI_ENEMY_KILL_SCORE_HEIGHT, 0.0f),
												D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_ENEMY_KILL_SCORE_200);
								break;
							case ENEMY_TYPE_ITEM_POWER:
								if (CManager::GetMode() == CManager::MODE_TUTORIAL)
								{
									//アイテムの生成
									CItem::Create(m_pos, D3DXVECTOR3(ITEM_WIDTH, ITEM_HEIGHT, 0.0f), CItem::ITEM_TYPE_POWER);
								}
								else
								{
									//スコア加算
									pScore->AddScore(100);
									//アイテムの生成
									CItem::Create(m_pos, D3DXVECTOR3(ITEM_WIDTH, ITEM_HEIGHT, 0.0f), CItem::ITEM_TYPE_POWER);
									//スコアのポリゴン生成
									CUiMove::Create(m_pos, D3DXVECTOR3(UI_ENEMY_KILL_SCORE_WIDTH, UI_ENEMY_KILL_SCORE_HEIGHT, 0.0f),
													D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_ENEMY_KILL_SCORE_100);
								}
								break;
							case ENEMY_TYPE_ITEM_SPEED:
								if (CManager::GetMode() == CManager::MODE_TUTORIAL)
								{
									//アイテムの生成
									CItem::Create(m_pos, D3DXVECTOR3(ITEM_WIDTH, ITEM_HEIGHT, 0.0f), CItem::ITEM_TYPE_SPEED);
								}
								else
								{
									//スコア加算
									pScore->AddScore(100);
									//アイテムの生成
									CItem::Create(m_pos, D3DXVECTOR3(ITEM_WIDTH, ITEM_HEIGHT, 0.0f), CItem::ITEM_TYPE_SPEED);
									//スコアのポリゴン生成
									CUiMove::Create(m_pos, D3DXVECTOR3(UI_ENEMY_KILL_SCORE_WIDTH, UI_ENEMY_KILL_SCORE_HEIGHT, 0.0f), 
													D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_ENEMY_KILL_SCORE_100);
								}
								break;
							default:
								break;
							}
							//エフェクトの生成
							for (int nCntEffect = 0; nCntEffect < ENEMY_DELETE_EFFECT_IN_MAX; nCntEffect++)
							{
								CEffect::Create(m_pos, D3DXVECTOR3(ENEMY_DELETE_EFFECT_IN_SIZE, ENEMY_DELETE_EFFECT_IN_SIZE, 0.0f),
												D3DXVECTOR3(ENEMY_DELETE_EFFECT_IN_MOVE * cosf(((D3DX_PI * 2.0f) / ENEMY_DELETE_EFFECT_IN_MAX) * nCntEffect),
															ENEMY_DELETE_EFFECT_IN_MOVE * sinf(((D3DX_PI * 2.0f) / ENEMY_DELETE_EFFECT_IN_MAX) * nCntEffect), 0.0f),
												D3DXCOLOR(255.0f, 255.0f, 0.0f, 255.0f), CEffect::EFFECT_TYPE_NORMAL);
							}
							for (int nCntEffect = 0; nCntEffect < ENEMY_DELETE_EFFECT_OUT_MAX; nCntEffect++)
							{
								CEffect::Create(m_pos, D3DXVECTOR3(ENEMY_DELETE_EFFECT_OUT_SIZE, ENEMY_DELETE_EFFECT_OUT_SIZE, 0.0f),
												D3DXVECTOR3(ENEMY_DELETE_EFFECT_OUT_MOVE * cosf(((D3DX_PI * 2.0f) / ENEMY_DELETE_EFFECT_OUT_MAX) * nCntEffect),
															ENEMY_DELETE_EFFECT_OUT_MOVE * sinf(((D3DX_PI * 2.0f) / ENEMY_DELETE_EFFECT_OUT_MAX) * nCntEffect), 0.0f),
												D3DXCOLOR(0.0f, 120.0f, 255.0f, 255.0f), CEffect::EFFECT_TYPE_NORMAL);
							}
							//敵の破棄
							Uninit();
						}
						break;
					}
				}
			}
		}
	}
	return bCol;
}