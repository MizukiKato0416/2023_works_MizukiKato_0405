//=======================================================================
//プレイヤーの弾に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "Bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "boss.h"
#include "score.h"
#include "EnemyBullet.h"
#include "sound.h"
#include "item.h"
#include "fade.h"



//========================================================
//マクロ定義
//========================================================
#define MAX_BULLET (128)				//弾の最大数
#define BULLET_TYPE (4)					//弾の種類

//========================================================
//弾の構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	float BulletHeight;	//弾の縦の大きさ
	float BulletWidth;	//弾の横の大きさ
	int nType;			//種類
	bool bUse;			//使用しているかどうか
} Bullet;

//========================================================
//グローバル変数
//========================================================
LPDIRECT3DTEXTURE9 g_apTextureBullet[BULLET_TYPE] = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		//頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];
int g_nCntItem;
int g_nCntHit;

//========================================================
//初期化処理
//========================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//でアイスのポインタ
	int nCntBullet;
	
	//デバイスの取得
	pDevice = GetDevice();

	g_nCntItem = 0;
	g_nCntHit = 0;
	//弾の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].BulletHeight = 0.0f;
		g_aBullet[nCntBullet].BulletWidth = 0.0f;
		g_aBullet[nCntBullet].nType = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//tennis-ball.png",
		&g_apTextureBullet[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//word_iya.png",
		&g_apTextureBullet[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//spword.png",
		&g_apTextureBullet[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//Zzz_Bullet.png",
		&g_apTextureBullet[3]);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//========================================================
//弾の終了処理
//========================================================
void UninitBullet(void)
{
	int nCntBullet;
	for (nCntBullet = 0; nCntBullet < BULLET_TYPE; nCntBullet++)
	{
		if (g_apTextureBullet[nCntBullet] != NULL)
		{
			//テクスチャの破棄
			g_apTextureBullet[nCntBullet]->Release();
			g_apTextureBullet[nCntBullet] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//========================================================
////弾の更新処理
//========================================================
void UpdateBullet(void)
{
	//-------------------------------------------------
	//弾の移動量、使用未使用の設定
	//-------------------------------------------------
	int nCntBullet;
	VERTEX_2D *pVtx;		//頂点情報へのポインタ
	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		
		if (g_aBullet[nCntBullet].bUse == true)
		{
		
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].BulletWidth, g_aBullet[nCntBullet].pos.y- g_aBullet[nCntBullet].BulletHeight,0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].BulletWidth, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].BulletHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].BulletWidth, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].BulletHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].BulletWidth, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].BulletHeight, 0.0f);
			
			if (g_aBullet[nCntBullet].pos.x >SCREEN_WIDTH+ g_aBullet[nCntBullet].BulletWidth)
			{
				g_aBullet[nCntBullet].bUse = false;		//使用していない状態にする
			}

			//-------------------------------------------------
			//敵と弾の当たり判定
			//-------------------------------------------------
			int nCntEnemy;
			Enemy *pEnemy;

			//敵の取得
			pEnemy = GetEnemy();

			for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{
				if (pEnemy->bUse == true)
				{
					if (g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + pEnemy->fEnemyWidth / 2.0f + g_aBullet[nCntBullet].BulletWidth &&
						g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - pEnemy->fEnemyWidth / 2.0f - g_aBullet[nCntBullet].BulletWidth &&
						g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + pEnemy->fEnemyHeight/2.0f + g_aBullet[nCntBullet].BulletHeight &&
						g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - pEnemy->fEnemyHeight / 2.0f - g_aBullet[nCntBullet].BulletHeight)
					{
						pEnemy->nLife -= 1;
						if (pEnemy->nLife > 0)
						{
							SetExplosion(g_aBullet[nCntBullet].pos + D3DXVECTOR3(g_aBullet[nCntBullet].BulletWidth, 0.0f, 0.0f), (1.0f, 0.0f, 0.0f, 0.0f));
						}
						else if (pEnemy->nLife <= 0)
						{
							g_nCntItem++;
							SetExplosion(pEnemy->pos, (1.0f, 0.0f, 0.0f, 0.0f));
							PlaySound(SOUND_LABEL_ENEMY_DAMAGE000);
							SetScore(50);
							if (g_nCntItem >= rand() % 10 + 5)
							{
								SetItem(pEnemy->pos, D3DXVECTOR3(1.0f, 0.0f, 0.0f), rand() % 2);
								g_nCntItem = 0;
							}
							pEnemy->bUse = false;
						}
						
						if (g_aBullet[nCntBullet].nType != 2)
						{
							g_aBullet[nCntBullet].bUse = false;
						}
						
					}
				}
			}

			//-------------------------------------------------
			//ボスと弾の当たり判定
			//-------------------------------------------------
			
			int nCntBoss;
			Boss *pBoss;
			pBoss = GetBoss();
			for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++, pBoss++)
			{
				if (pBoss->bUse == true)
				{
					
					if (GetMode() == MODE_STAGE1)
					{
						if (g_aBullet[nCntBullet].pos.x <= pBoss->pos.x + BOSS_WIDTH / 2.0f + g_aBullet[nCntBullet].BulletWidth &&
							g_aBullet[nCntBullet].pos.x >= pBoss->pos.x - BOSS_WIDTH / 2.0f + 65.0f - g_aBullet[nCntBullet].BulletWidth &&
							g_aBullet[nCntBullet].pos.y <= pBoss->pos.y + BOSS_HEIGHT / 2.0f -10.0f + g_aBullet[nCntBullet].BulletHeight &&
							g_aBullet[nCntBullet].pos.y >= pBoss->pos.y - BOSS_HEIGHT / 2.0f +15.0f - g_aBullet[nCntBullet].BulletHeight)
						{

							if (pBoss->pos.x <= SCREEN_WIDTH - (BOSS_WIDTH / 2) - 50.0f)
							{
								pBoss->nLife -= 1;
							}

							if (pBoss->nLife > 0)
							{
								SetExplosion(g_aBullet[nCntBullet].pos + D3DXVECTOR3(g_aBullet[nCntBullet].BulletWidth, 0.0f, 0.0f), (1.0f, 0.0f, 0.0f, 0.0f));
								SetScore(1000);

							}
							else if (pBoss->nLife <= 0)
							{
								SetExplosion(pBoss->pos, (1.0f, 0.0f, 0.0f, 0.0f));
								PlaySound(SOUND_LABEL_EXPLOTION000);
								SetScore(10000);

								pBoss->nLife = 0;
								SetFade(MODE_GAME);

								pBoss->bUse = false;
							}

							if (g_aBullet[nCntBullet].nType != 2)
							{
								g_aBullet[nCntBullet].bUse = false;
							}
							else
							{
								g_nCntHit++;
								if (g_nCntHit >= 10)
								{
									g_aBullet[nCntBullet].bUse = false;
									g_nCntHit = 0;
								}
							}
							
							
						
						}
					}

					else if (GetMode() == MODE_GAME)
					{
						if (g_aBullet[nCntBullet].pos.x <= pBoss->pos.x + BOSS_WIDTH / 2.0f + g_aBullet[nCntBullet].BulletWidth &&
							g_aBullet[nCntBullet].pos.x >= pBoss->pos.x - BOSS_WIDTH / 2.0f - g_aBullet[nCntBullet].BulletWidth &&
							g_aBullet[nCntBullet].pos.y <= pBoss->pos.y + BOSS_HEIGHT / 2.0f + g_aBullet[nCntBullet].BulletHeight &&
							g_aBullet[nCntBullet].pos.y >= pBoss->pos.y - BOSS_HEIGHT / 2.0f - g_aBullet[nCntBullet].BulletHeight)
						{

							if (pBoss->pos.x <= SCREEN_WIDTH - (BOSS_WIDTH / 2) - 50.0f)
							{
								pBoss->nLife -= 1;
							}

							if (pBoss->nLife > 0)
							{
								SetExplosion(g_aBullet[nCntBullet].pos + D3DXVECTOR3(g_aBullet[nCntBullet].BulletWidth, 0.0f, 0.0f), (1.0f, 0.0f, 0.0f, 0.0f));
								SetScore(3000);

							}
							else if (pBoss->nLife <= 0)
							{
								SetExplosion(pBoss->pos, (1.0f, 0.0f, 0.0f, 0.0f));
								PlaySound(SOUND_LABEL_EXPLOTION000);
								SetScore(500000);

								pBoss->nLife = 0;
								SetFade(MODE_STAGE3);

								pBoss->bUse = false;
							}

							if (g_aBullet[nCntBullet].nType != 2)
							{
								g_aBullet[nCntBullet].bUse = false;
							}
							else
							{
								g_nCntHit++;
								if (g_nCntHit >= 10)
								{
									g_aBullet[nCntBullet].bUse = false;
									g_nCntHit = 0;
								}
							}

							g_aBullet[nCntBullet].bUse = false;
						}
					}
					
					else if (GetMode() == MODE_STAGE3)
					{
						if (g_aBullet[nCntBullet].pos.x <= pBoss->pos.x + BOSS_WIDTH / 2.0f + g_aBullet[nCntBullet].BulletWidth &&
							g_aBullet[nCntBullet].pos.x >= pBoss->pos.x - BOSS_WIDTH / 2.0f - g_aBullet[nCntBullet].BulletWidth + 40.0f &&
							g_aBullet[nCntBullet].pos.y <= pBoss->pos.y + BOSS_HEIGHT / 2.0f + g_aBullet[nCntBullet].BulletHeight &&
							g_aBullet[nCntBullet].pos.y >= pBoss->pos.y - BOSS_HEIGHT / 2.0f - g_aBullet[nCntBullet].BulletHeight)
						{

							if (pBoss->pos.x <= SCREEN_WIDTH - (BOSS_WIDTH / 2) - 50.0f)
							{
								pBoss->nLife -= 1;
							}

							if (pBoss->nLife > 0)
							{
								SetExplosion(g_aBullet[nCntBullet].pos + D3DXVECTOR3(g_aBullet[nCntBullet].BulletWidth, 0.0f, 0.0f), (1.0f, 0.0f, 0.0f, 0.0f));
								SetScore(5000);

							}
							else if (pBoss->nLife <= 0)
							{
								SetExplosion(pBoss->pos, (1.0f, 0.0f, 0.0f, 0.0f));
								PlaySound(SOUND_LABEL_EXPLOTION000);
								SetScore(10000000);

								pBoss->nLife = 0;
								SetFade(MODE_RESULT);

								pBoss->bUse = false;
							}

							if (g_aBullet[nCntBullet].nType != 2)
							{
								g_aBullet[nCntBullet].bUse = false;
							}
							else
							{
								g_nCntHit++;
								if (g_nCntHit >= 10)
								{
									g_aBullet[nCntBullet].bUse = false;
									g_nCntHit = 0;
								}
							}

							g_aBullet[nCntBullet].bUse = false;
						}
					}
				}
			}

			//-------------------------------------------------
			//敵の弾と弾の当たり判定
			//-------------------------------------------------

			EnemyBullet*pEnemyBullet;
			int EnemyBulletnCnt;

			//弾の取得
			pEnemyBullet = GetEnemyBullet();
			for (EnemyBulletnCnt = 0; EnemyBulletnCnt < MAX_ENEMY_BULLET; EnemyBulletnCnt++, pEnemyBullet++)
			{
				if (pEnemyBullet->bUse == true)
				{
					if (g_aBullet[nCntBullet].pos.x <= pEnemyBullet->pos.x + pEnemyBullet->EnemyBulletWidth / 2.0f + g_aBullet[nCntBullet].BulletWidth  &&
						g_aBullet[nCntBullet].pos.x >= pEnemyBullet->pos.x - pEnemyBullet->EnemyBulletWidth / 2.0f - g_aBullet[nCntBullet].BulletWidth  &&
						g_aBullet[nCntBullet].pos.y <= pEnemyBullet->pos.y + pEnemyBullet->EnemyBulletHeight / 2.0f + g_aBullet[nCntBullet].BulletHeight  &&
						g_aBullet[nCntBullet].pos.y >= pEnemyBullet->pos.y - pEnemyBullet->EnemyBulletHeight / 2.0f - g_aBullet[nCntBullet].BulletHeight )
					{
						SetExplosion(g_aBullet[nCntBullet].pos, (1.0f, 0.0f, 0.0f, 0.0f));
						pEnemyBullet->bUse = false;
						if (g_aBullet[nCntBullet].nType != 2)
						{
							g_aBullet[nCntBullet].bUse = false;
						}
					}
				}
			}

		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//========================================================
//描画処理
//========================================================
void DrawBullet(void)
{
	int nCntBullet;

	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定


	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{

			pDevice->SetTexture(0, g_apTextureBullet[g_aBullet[nCntBullet].nType]);	//テクスチャの設定

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntBullet*4,					//描画を開始する頂点のインデックス
				2);					//描画するプリミティブ数
		}
	}
}

//========================================================
//弾の設定処理
//========================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType, float BulletHeight, float BulletWidth)
{
	int nCntBullet;
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].BulletWidth = BulletWidth;
			g_aBullet[nCntBullet].BulletHeight = BulletHeight;
			//頂点座標の設定
			
			VERTEX_2D *pVtx;		//頂点情報へのポインタ
									//頂点バッファをロックし、頂点データのポインタを取得
			g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntBullet * 4);

			
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].BulletWidth, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].BulletHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].BulletWidth, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].BulletHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].BulletWidth, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].BulletHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].BulletWidth, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].BulletHeight, 0.0f);
			
			//頂点バッファをアンロックする
			g_pVtxBuffBullet->Unlock();

			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nType = nType;
			g_aBullet[nCntBullet].bUse = true;
			break;
		}
	}
}
