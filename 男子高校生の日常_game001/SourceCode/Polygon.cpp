//=======================================================================
//プレイヤーに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "Polygon.h"
#include "input.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "enemy.h"
#include "boss.h"
#include "explosion.h"
#include "item.h"
#include "life.h"
#include "special.h"
#include "sound.h"


//マクロ定義
#define POLYGON_WIDTH (65.0f*1.2)		//プレイヤーの幅
#define POLYGON_HEIGHT (100.0f*1.2)		//プレイヤーの高さ
#define POLYGON_SPEED (2.0f)			//プレイヤーの速さ
#define POLYGON_TYPE (3)				//プレイヤーの種類
#define PLAYER_HIT (0.0f)				//プレイヤーの当たり判定のマイナス

//=======================================================================
//グローバル変数宣言
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTexturePolygon[POLYGON_TYPE] = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;		//頂点バッファへのポインタ
int g_nCounterAnim;			//アニメーションカウンタ
int g_nCntEnemyAnim;		//敵のアニメーションカウンタ
int g_nPatternAnim;			//アニメーションパターンNo
int g_nPatternBullet;			//アニメーションパターンNo
bool g_bItem;					//必殺技の使用可能不可能
D3DXVECTOR3 g_posPolygon;		//ポリゴンの位置
D3DXVECTOR3 g_movePolygon;		//ポリゴンの移動量

//=======================================================================
//初期化処理
//=======================================================================
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//boy1.png",
		&g_pTexturePolygon[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//sleep_cry_man.png",
		&g_pTexturePolygon[1]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//school_sleep.png",
		&g_pTexturePolygon[2]);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	g_nCounterAnim = 0;		//カウンターを初期化
	g_nCntEnemyAnim = 0;		//敵のアニメーションカウンタを初期化
	g_nPatternAnim = 0;		//パターンNoを初期化
	g_nPatternBullet = 0;
	g_bItem = false;
	srand((unsigned int)time(NULL));


	g_posPolygon = D3DXVECTOR3(100, SCREEN_HEIGHT/2, 0.0f);
	g_movePolygon = D3DXVECTOR3(1.0f, 1.0f, 0.0f);

	pVtx[0].pos = D3DXVECTOR3(100 - POLYGON_WIDTH / 2, SCREEN_HEIGHT / 2 - POLYGON_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(100 + POLYGON_WIDTH / 2, SCREEN_HEIGHT / 2 - POLYGON_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(100 - POLYGON_WIDTH / 2, SCREEN_HEIGHT / 2 + POLYGON_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(100 + POLYGON_WIDTH / 2, SCREEN_HEIGHT / 2 + POLYGON_HEIGHT / 2, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	
	
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPolygon->Unlock();
}

//=======================================================================
//終了処理
//=======================================================================
void UninitPolygon(void)
{
	int nCntPolygon;
	for (nCntPolygon = 0; nCntPolygon < POLYGON_TYPE; nCntPolygon++)
	{
		//テクスチャの破棄
		if (g_pTexturePolygon[nCntPolygon] != NULL)
		{
			g_pTexturePolygon[nCntPolygon]->Release();
			g_pTexturePolygon[nCntPolygon] = NULL;
		}
	}
	

	//頂点バッファの破棄
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdatePolygon(void)
{
	g_nCounterAnim++;
	if (g_nCounterAnim == 90)
	{
		g_nCounterAnim = 0;		//カウンターを初期地に戻す
		g_nPatternAnim++;		//パターンNoを更新
		if (g_nPatternAnim > 1)
		{
			g_nPatternAnim = 0;
		}

		VERTEX_2D *pVtx;		//頂点情報へのポインタ
								//頂点バッファをロックし、頂点データのポインタを取得
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].tex = D3DXVECTOR2(g_nPatternAnim * 0.5f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_nPatternAnim * 0.5f + 0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_nPatternAnim * 0.5f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_nPatternAnim * 0.5f + 0.5f, 1.0f);


		//頂点バッファをアンロックする
		g_pVtxBuffPolygon->Unlock();
	}

	//任意のキーが押されたかどうか
	if (GetKeyboardPress(DIK_A) == true)
	{
		g_posPolygon.x -= POLYGON_SPEED;
		VERTEX_2D *pVtx;		//頂点情報へのポインタ
								//頂点バッファをロックし、頂点データのポインタを取得
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

		if (GetKeyboardPress(DIK_W) == true)
		{
			g_posPolygon.x += sinf(-D3DX_PI*0.75f)*POLYGON_SPEED;
			g_posPolygon.y += cosf(-D3DX_PI*0.75f)*POLYGON_SPEED;
			
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_posPolygon.x += sinf(-D3DX_PI*0.25f)*POLYGON_SPEED;
			g_posPolygon.y += cosf(-D3DX_PI*0.25f)*POLYGON_SPEED;
			
		}
		else
		{
			g_posPolygon.x += sinf(-D3DX_PI*0.5f)*POLYGON_SPEED;
			g_posPolygon.y += cosf(-D3DX_PI*0.5f)*POLYGON_SPEED;
			
		}

		pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_WIDTH/2, g_posPolygon.y - POLYGON_HEIGHT/2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y - POLYGON_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_WIDTH / 2, g_posPolygon.y + POLYGON_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y + POLYGON_HEIGHT / 2, 0.0f);
		
		//頂点バッファをアンロックする
		g_pVtxBuffPolygon->Unlock();
	}

	else if (GetKeyboardPress(DIK_D) == true)
	{
		g_posPolygon.x += POLYGON_SPEED;
		VERTEX_2D *pVtx;		//頂点情報へのポインタ
								//頂点バッファをロックし、頂点データのポインタを取得
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

		if (GetKeyboardPress(DIK_W) == true)
		{
			g_posPolygon.x += sinf(D3DX_PI*0.75f)*POLYGON_SPEED;
			g_posPolygon.y += cosf(D3DX_PI*0.75f)*POLYGON_SPEED;
			
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_posPolygon.x += sinf(D3DX_PI*0.25f)*POLYGON_SPEED;
			g_posPolygon.y += cosf(D3DX_PI*0.25f)*POLYGON_SPEED;
			
		}
		else
		{
			g_posPolygon.x += sinf(D3DX_PI*0.5f)*POLYGON_SPEED;
			g_posPolygon.y += cosf(D3DX_PI*0.5f)*POLYGON_SPEED;
		}

		pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_WIDTH / 2, g_posPolygon.y - POLYGON_HEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y - POLYGON_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_WIDTH / 2, g_posPolygon.y + POLYGON_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y + POLYGON_HEIGHT / 2, 0.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffPolygon->Unlock();
	}

	else if (GetKeyboardPress(DIK_S) == true)
	{
		g_posPolygon.y += POLYGON_SPEED;
		VERTEX_2D *pVtx;		//頂点情報へのポインタ
								//頂点バッファをロックし、頂点データのポインタを取得
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

		g_posPolygon.x += sinf(D3DX_PI*0.0f)*POLYGON_SPEED;
		g_posPolygon.y += cosf(D3DX_PI*0.0f)*POLYGON_SPEED;
		

		pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_WIDTH / 2, g_posPolygon.y - POLYGON_HEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y - POLYGON_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_WIDTH / 2, g_posPolygon.y + POLYGON_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y + POLYGON_HEIGHT / 2, 0.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffPolygon->Unlock();
	}

	else if (GetKeyboardPress(DIK_W) == true)
	{
		g_posPolygon.y -= POLYGON_SPEED;
		VERTEX_2D *pVtx;		//頂点情報へのポインタ
								//頂点バッファをロックし、頂点データのポインタを取得
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	

		g_posPolygon.x += sinf(D3DX_PI*1.0f)*POLYGON_SPEED;
		g_posPolygon.y += cosf(D3DX_PI*1.0f)*POLYGON_SPEED;

		pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_WIDTH / 2, g_posPolygon.y - POLYGON_HEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y - POLYGON_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_WIDTH / 2, g_posPolygon.y + POLYGON_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y + POLYGON_HEIGHT / 2, 0.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffPolygon->Unlock();
	}


	//スペースキーを押したときの処理
	if (GetKeyboardPress(DIK_SPACE) == true)
	{
		g_nPatternBullet++;
		if (g_nPatternBullet >= 40)
		{
			if (GetMode() == MODE_GAME)
			{
				PlaySound(SOUND_LABEL_shot000);
				SetBullet(D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y, g_posPolygon.z), D3DXVECTOR3(6.0f, 0.0f, 0.0f), 0, 15.0f, 15.0f);
			}
			else if (GetMode() == MODE_STAGE1)
			{
				PlaySound(SOUND_LABEL_shot000);
				SetBullet(D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y, g_posPolygon.z), D3DXVECTOR3(6.0f, 0.0f, 0.0f), 1, 20.0f, 20.0f);
			}
			else if (GetMode() == MODE_STAGE3)
			{
				PlaySound(SOUND_LABEL_shot000);
				SetBullet(D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y, g_posPolygon.z), D3DXVECTOR3(6.0f, -1.3f, 0.0f), 3, 15.0f, 15.0f);
				//SetBullet(D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y, g_posPolygon.z), D3DXVECTOR3(6.0f, -0.7f, 0.0f), 3, 15.0f, 15.0f);
				SetBullet(D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y, g_posPolygon.z), D3DXVECTOR3(6.0f, 0.0f, 0.0f), 3, 15.0f, 15.0f);
				//SetBullet(D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y, g_posPolygon.z), D3DXVECTOR3(6.0f, 0.7f, 0.0f), 3, 15.0f, 15.0f);
				SetBullet(D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y, g_posPolygon.z), D3DXVECTOR3(6.0f, 1.3f, 0.0f), 3, 15.0f, 15.0f);
			}
			g_nPatternBullet = 0;
		}
		
	}

	//コントロールキーを押したときの処理(必殺技処理)
	Special *pSpecial;
	//アイテムの取得
	pSpecial = GetSpecial();
	if (g_bItem == true)
	{
		if (GetKeyboardTrigger(DIK_LCONTROL) == true)
		{

			PlaySound(SOUND_LABEL_shotSP000);
			SetBullet(D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y, g_posPolygon.z), D3DXVECTOR3(6.0f, 0.0f, 0.0f), 2, 200.0f, 400.0f);
			g_bItem = false;
			pSpecial->bUse = false;
		}
	}

	//ボスの自動移動
	if (GetMode() == MODE_GAME)
	{
		SetBoss(D3DXVECTOR3(SCREEN_WIDTH + BOSS_WIDTH, SCREEN_HEIGHT / 2.0f, 0.0f), 0, D3DXVECTOR3(0.5f, 0.0f, 0.0f), 60);
	}
	else if (GetMode() == MODE_STAGE1)
	{
		SetBoss(D3DXVECTOR3(SCREEN_WIDTH + BOSS_WIDTH, SCREEN_HEIGHT / 2.0f, 0.0f),1, D3DXVECTOR3(0.5f, 0.0f, 0.0f), 60);
	}
	else if (GetMode() == MODE_STAGE3)
	{
		SetBoss(D3DXVECTOR3(SCREEN_WIDTH + BOSS_WIDTH, SCREEN_HEIGHT / 2.0f, 0.0f), 2, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 200);
	}

	g_nCntEnemyAnim++;		//敵のアニメーションカウンタ

	//敵の自動移動
	Enemy *pEnemy;
	//敵の取得
	pEnemy = GetEnemy();
	if (GetMode() == MODE_GAME)
	{
		if (g_nCntEnemyAnim >= rand() % 200 + 200)
		{
			SetEnemy(D3DXVECTOR3(SCREEN_WIDTH + pEnemy->fEnemyWidth, rand() % 120 + 80, 0.0f), 0, D3DXVECTOR3(1.2f, 0.0f, 0.0f), 2, 70.0f, 70.0f);
			SetEnemy(D3DXVECTOR3(SCREEN_WIDTH + pEnemy->fEnemyWidth, rand() % 100 + 300, 0.0f), 0, D3DXVECTOR3(1.2f, 0.0f, 0.0f), 2, 70.0f, 70.0f);
			SetEnemy(D3DXVECTOR3(SCREEN_WIDTH + pEnemy->fEnemyWidth, rand() % 100 + 500, 0.0f), 0, D3DXVECTOR3(1.2f, 0.0f, 0.0f), 2, 70.0f,70.0f);
			g_nCntEnemyAnim = 0;
		}
	}
	else if (GetMode() == MODE_STAGE1)
	{
		if (g_nCntEnemyAnim >= rand() % 350 + 300)
		{
			SetEnemy(D3DXVECTOR3(g_posPolygon.x, 0 - pEnemy->fEnemyHeight / 2, 0.0f), 1, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 1, 70.0f, 70.0f);
			SetEnemy(D3DXVECTOR3(rand() % 100 + (300 + pEnemy->fEnemyWidth / 2), 0 - pEnemy->fEnemyHeight / 2, 0.0f), 2, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 1, 70.0f, 70.0f);
			SetEnemy(D3DXVECTOR3(rand() % 100 + (550 + pEnemy->fEnemyWidth / 2), 0 - pEnemy->fEnemyHeight / 2, 0.0f), 1, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 1, 70.0f, 70.0f);
			g_nCntEnemyAnim = 0;
		}
	}
	else if (GetMode() == MODE_STAGE3)
	{
		if (g_nCntEnemyAnim >= rand() % 350 + 300)
		{
			SetEnemy(D3DXVECTOR3(SCREEN_WIDTH + pEnemy->fEnemyWidth, rand() % 120 + 80, 0.0f), 3, D3DXVECTOR3(2.2f, 0.0f, 0.0f), 2, 100.0f, 30.0f);
			SetEnemy(D3DXVECTOR3(SCREEN_WIDTH + pEnemy->fEnemyWidth, g_posPolygon.y, 0.0f), 3, D3DXVECTOR3(2.2f, 0.0f, 0.0f), 2, 100.0f, 30.0f);
			SetEnemy(D3DXVECTOR3(SCREEN_WIDTH + pEnemy->fEnemyWidth, rand() % 100 + 500, 0.0f), 3, D3DXVECTOR3(2.2f, 0.0f, 0.0f), 2, 100.0f, 30.0f);
			g_nCntEnemyAnim = 0;
		}
	}


	//敵がプレイヤーにあったった時の処理
	
	int nCntEnemy;
	//Enemy *pEnemy;

	//敵の取得
	//pEnemy = GetEnemy();
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			if (g_posPolygon.x <= pEnemy->pos.x + pEnemy->fEnemyWidth / 2.0f + POLYGON_WIDTH/2.0f- PLAYER_HIT &&
				g_posPolygon.x >= pEnemy->pos.x - pEnemy->fEnemyWidth / 2.0f - POLYGON_WIDTH / 2.0f + PLAYER_HIT &&
				g_posPolygon.y <= pEnemy->pos.y + pEnemy->fEnemyHeight / 2.0f + POLYGON_HEIGHT / 2.0f - PLAYER_HIT &&
				g_posPolygon.y >= pEnemy->pos.y - pEnemy->fEnemyHeight / 2.0f - POLYGON_HEIGHT / 2.0f + PLAYER_HIT)
			{
				SetExplosion(g_posPolygon, (1.0f, 0.0f, 0.0f, 0.0f));
				PlaySound(SOUND_LABEL_DAMAGE000);
				pEnemy->bUse = false;
				SetLife(0.5f);
			}
		}
	}


	

	
	//-------------------------------------------------
	//プレイヤーと弾の当たり判定
	//-------------------------------------------------
	EnemyBullet*pEnemyBullet;
	int EnemyBulletnCnt;

	//弾の取得
	pEnemyBullet = GetEnemyBullet();
	for (EnemyBulletnCnt = 0; EnemyBulletnCnt < MAX_ENEMY_BULLET; EnemyBulletnCnt++, pEnemyBullet++)
	{
		if (pEnemyBullet->bUse == true)
		{


			if (g_posPolygon.x <= pEnemyBullet->pos.x + pEnemyBullet->EnemyBulletWidth / 2.0f + POLYGON_WIDTH / 2.0f - PLAYER_HIT &&
				g_posPolygon.x >= pEnemyBullet->pos.x - pEnemyBullet->EnemyBulletWidth / 2.0f - POLYGON_WIDTH / 2.0f + PLAYER_HIT &&
				g_posPolygon.y <= pEnemyBullet->pos.y + pEnemyBullet->EnemyBulletHeight / 2.0f + POLYGON_HEIGHT / 2.0f - PLAYER_HIT &&
				g_posPolygon.y >= pEnemyBullet->pos.y - pEnemyBullet->EnemyBulletHeight / 2.0f - POLYGON_HEIGHT / 2.0f + PLAYER_HIT)
			{

				SetExplosion(g_posPolygon, (1.0f, 0.0f, 0.0f, 0.0f));
				PlaySound(SOUND_LABEL_DAMAGE000);
				pEnemyBullet->bUse = false;
				SetLife(0.5f);
			}
		}
	}

	//-------------------------------------------------
	//プレイヤーとアイテムの当たり判定
	//-------------------------------------------------
	Item *pItem;
	int nCntItem;

	//アイテムの取得
	pItem = GetItem();
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		if (pItem->bUse == true)
		{


			if (g_posPolygon.x <= pItem->pos.x + ITEM_WIDTH / 2.0f + POLYGON_WIDTH / 2.0f &&
				g_posPolygon.x >= pItem->pos.x - ITEM_WIDTH / 2.0f - POLYGON_WIDTH / 2.0f &&
				g_posPolygon.y <= pItem->pos.y + ITEM_HEIGHT / 2.0f + POLYGON_HEIGHT / 2.0f &&
				g_posPolygon.y >= pItem->pos.y - ITEM_HEIGHT / 2.0f - POLYGON_HEIGHT / 2.0f)
			{
				if (pItem->nType == 0)
				{
					PlaySound(SOUND_LABEL_CURE000);
					pItem->bUse = false;
					SetLife(-1.0f);
				}
				else if (pItem->nType == 1)
				{
					PlaySound(SOUND_LABEL_CURE000);
					pItem->bUse = false;
					if (g_bItem == false)
					{
						pSpecial->bUse = true;
						g_bItem = true;
					}
				}
			}
		}
	}

	//-------------------------------------------------
	//プレイヤーの移動制限
	//-------------------------------------------------


	VERTEX_2D *pVtx;		//頂点情報へのポインタ
							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);



	if (g_posPolygon.x <= 0.0f + POLYGON_WIDTH / 2.0f)
	{
		g_posPolygon.x = 0.0f + POLYGON_WIDTH / 2.0f;		//位置の更新
	}

	else if (g_posPolygon.x >= 700)
	{
		g_posPolygon.x = 700;	//位置の更新
	}

	if (g_posPolygon.y <= 0.0f + POLYGON_HEIGHT / 2.0f)
	{
		g_posPolygon.y = 0.0f + POLYGON_HEIGHT / 2.0f;		//位置の更新
	}

	else if (g_posPolygon.y >= SCREEN_HEIGHT - POLYGON_HEIGHT / 2.0f)
	{
		g_posPolygon.y = SCREEN_HEIGHT - POLYGON_HEIGHT / 2.0f;		//位置の更新
	}


	pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_WIDTH / 2, g_posPolygon.y - POLYGON_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y - POLYGON_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_WIDTH / 2, g_posPolygon.y + POLYGON_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y + POLYGON_HEIGHT / 2, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPolygon->Unlock();

}

//=======================================================================
//描画処理
//=======================================================================
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定

	if (GetMode() == MODE_GAME)
	{
		pDevice->SetTexture(0, g_pTexturePolygon[0]);	//テクスチャの設定
	}
	else if (GetMode() == MODE_STAGE1)
	{
		pDevice->SetTexture(0, g_pTexturePolygon[1]);	//テクスチャの設定
	}
	else if (GetMode() == MODE_STAGE3)
	{
		pDevice->SetTexture(0, g_pTexturePolygon[2]);	//テクスチャの設定
	}
	
												//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,					//開始する頂点のインデックス
		2);					//描画するプリミティブ数
}