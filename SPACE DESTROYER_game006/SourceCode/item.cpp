//================================================
//アイテム処理
//Authore:加藤瑞葵
//================================================
#include "scene2D.h"
#include "manager.h"
#include "item.h"
#include "renderer.h"
#include "texture.h"
#include "player.h"
#include "game01.h"
#include "effect.h"
#include "score.h"
#include "tutorial.h"
#include "sound.h"
#include "ui_move.h"

//================================================
//静的メンバ変数宣言
//================================================
LPDIRECT3DTEXTURE9 CItem::m_pTexture = NULL;

//================================================
//デフォルトコンストラクタ
//================================================
CItem::CItem(int nPriority) :CScene2D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scrollSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = ITEM_TYPE_NONE;
	m_nEfectCounter = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CItem::~CItem()
{

}

//================================================
//初期化処理
//================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//チュートリアルの場合
	if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		m_scrollSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	else
	{
		m_scrollSpeed = D3DXVECTOR3(0.0f, ITEM_SCROLL_SPEED, 0.0f);
	}
	m_size = size;
	m_nEfectCounter = 0;

	//オブジェクトの種類の設定
	switch (m_type)
	{
	case ITEM_TYPE_SPEED:
		SetObjType(CScene::OBJTYPE_ITEM_SPEED);
		break;
	case ITEM_TYPE_POWER:
		SetObjType(CScene::OBJTYPE_ITEM_POWER);
		break;
	case ITEM_TYPE_SCORE:
		SetObjType(CScene::OBJTYPE_ITEM_SCORE);
		break;
	default:
		break;
	}

	return S_OK;
}

//================================================
//終了処理
//================================================
void CItem::Uninit(void)
{
	CScene2D::Uninit();
}

//================================================
//更新処理
//================================================
void CItem::Update(void)
{
	//位置を取得
	D3DXVECTOR3 pos = GetPos();
	pos += m_scrollSpeed;
	pos += m_move;		//移動量反映

	//動きの処理
	Move();

	//当たり判定
	if (Collision() == true)
	{
		return;
	}

	//位置を設定
	SetPos(pos, m_size);
}

//================================================
//描画処理
//================================================
void CItem::Draw(void)
{
	CScene2D::Draw();
}

//================================================
//生成処理
//================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CItem::ITEM_TYPE type)
{
	//インスタンスの生成
	CItem *pItem = NULL;
	if (pItem == NULL)
	{
		pItem = new CItem;
		if (pItem != NULL)
		{
			pItem->m_type = type;

			switch (type)
			{
			case ITEM_TYPE_SPEED:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_ITEM_SPEED);
				break;
			case ITEM_TYPE_POWER:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_ITEM_POWER);
				break;
			case ITEM_TYPE_SCORE:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_ITEM_SCORE);
				break;
			default:
				break;
			}
			pItem->Init(pos, size);
			pItem->BindTexture(m_pTexture);
		}
	}
	return pItem;
}

//================================================
//当たり判定処理
//================================================
bool CItem::Collision(void)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//判定のフラグ
	bool bCol = false;

	//位置取得
	D3DXVECTOR3 pos = GetPos();

	//オブジェクト分回す
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			//シーンのnCnt番目のポインタ取得
			CScene *pScene;
			pScene = CScene::GetScene(nCntScene, nCntPriority);

			if (pScene != NULL)
			{
				//オブジェクトのタイプを取得
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				if (objType == CScene::OBJTYPE_PLAYER)		//オブジェクトのタイプがPLAYERの時
				{
					//取得したオブジェクトの位置とサイズを取得
					D3DXVECTOR3 playerPos = pScene->GetPos();
					D3DXVECTOR3 Itemsize = pScene->GetSize();

					//当たり判定
					if (pos.x + m_size.x / 2.0f >= playerPos.x - Itemsize.x / 2.0f && pos.x - m_size.x / 2.0f <= playerPos.x + Itemsize.x / 2.0f &&
						pos.y + m_size.y / 2.0f >= playerPos.y - Itemsize.y / 2.0f && pos.y - m_size.y / 2.0f <= playerPos.y + Itemsize.y / 2.0f)
					{
						//プレイヤーを取得
						CPlayer *pPlayer = (CPlayer*)pScene;

						//アイテムのタイプによって処理を分ける
						switch (m_type)
						{
						case ITEM_TYPE_SPEED:
							//BGMの再生
							pSound->Play(CSound::SOUND_LABEL_ITEM_SPEED_SE);
							//サウンドの音量調整
							pSound->ControllVoice(CSound::SOUND_LABEL_ITEM_SPEED_SE, 1.7f);

							//チュートリアルの場合
							if (CManager::GetMode() == CManager::MODE_TUTORIAL)
							{
								CTutorial::SetSpeedUp(true);
							}

							//プレイヤーの次の弾を撃つまでの間隔のレベルを取得しレベルによって処理を分ける
							switch (pPlayer->GetBulletSpeedLevel())
							{
							case CPlayer::PLAYER_BULLET_SPEED_LEVEL_1:
								pPlayer->SetBulletSpeedLevel(CPlayer::PLAYER_BULLET_SPEED_LEVEL_2);
								break;
							case CPlayer::PLAYER_BULLET_SPEED_LEVEL_2:
								pPlayer->SetBulletSpeedLevel(CPlayer::PLAYER_BULLET_SPEED_LEVEL_3);
								break;
							case CPlayer::PLAYER_BULLET_SPEED_LEVEL_3:
								pPlayer->SetBulletSpeedLevel(CPlayer::PLAYER_BULLET_SPEED_LEVEL_3);
								break;
							default:
								break;
							}
							break;
						case ITEM_TYPE_POWER:
							//BGMの再生
							pSound->Play(CSound::SOUND_LABEL_ITEM_POWER_SE);
							//サウンドの音量調整
							pSound->ControllVoice(CSound::SOUND_LABEL_ITEM_POWER_SE, 1.7f);

							//チュートリアルの場合
							if (CManager::GetMode() == CManager::MODE_TUTORIAL)
							{
								CTutorial::SetPowerUp(true);
							}

							//プレイヤーの弾のレベルを取得しレベルによって処理を分ける
							switch (pPlayer->GetBulletPowerLevel())
							{
							case CPlayer::PLAYER_BULLET_SPEED_LEVEL_1:
								pPlayer->SetBulletPowerLevel(CPlayer::PLAYER_BULLET_POWER_LEVEL_2);
								break;
							case CPlayer::PLAYER_BULLET_SPEED_LEVEL_2:
								pPlayer->SetBulletPowerLevel(CPlayer::PLAYER_BULLET_POWER_LEVEL_3);
								break;
							case CPlayer::PLAYER_BULLET_SPEED_LEVEL_3:
								pPlayer->SetBulletPowerLevel(CPlayer::PLAYER_BULLET_POWER_LEVEL_3);
								break;
							default:
								break;
							}
							break;
						case ITEM_TYPE_SCORE:
							//スコアのポインタ取得
							CScore *pScore;
							pScore = CGame01::GetScore();
							//スコア加算
							pScore->AddScore(100);
							//スコアのポリゴン生成
							CUiMove::Create(D3DXVECTOR3(playerPos.x + 20.0f, playerPos.y - 20.0f, 0.0f), D3DXVECTOR3(UI_ENEMY_KILL_SCORE_WIDTH, UI_ENEMY_KILL_SCORE_HEIGHT, 0.0f),
											D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_ENEMY_KILL_SCORE_100);
							break;
						default:
							break;
						}
						//当たった判定
						bCol = true;
						//アイテムの破棄
						Uninit();
						break;
					}
				}
			}
		}
	}
	return bCol;
}

//================================================
//動きの処理
//================================================
void CItem::Move(void)
{
	//位置を取得
	D3DXVECTOR3 pos = GetPos();

	if (m_type == CItem::ITEM_TYPE_SCORE)
	{
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
						//シーンのポインタを敵の型にキャスト
						CPlayer *pPlayer = (CPlayer*)pScene;

						//プレイヤーの位置を取得
						D3DXVECTOR3 posPlayer = pPlayer->GetPos();
						//プレイヤーとアイテムの角度を計算
						float fTanR = atan2f(posPlayer.y - pos.y, posPlayer.x - pos.x);
						//プレイヤーに向かって行くよう移動量を計算
						m_move = D3DXVECTOR3(cosf(fTanR) * ITEM_COLECT_SPEED, sinf(fTanR) * ITEM_COLECT_SPEED, 0.0f);

						//エフェクトのカウンターを加算
						m_nEfectCounter++;
						if (m_nEfectCounter >= ITEM_EFFECT_INTERVAL)
						{
							//エフェクトの生成
							CEffect::Create(pos, m_size, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f),
											CEffect::EFFECT_TYPE_NORMAL);
							m_nEfectCounter = 0;
						}
					}
				}
			}
		}
	}
}