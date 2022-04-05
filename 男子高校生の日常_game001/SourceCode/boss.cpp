//=======================================================================
//ボスに関する処理
//Aouthor:　加藤　瑞葵
//=======================================================================

#include "main.h"
#include "boss.h"
#include "EnemyBullet.h"
#include "sound.h"
#include "fade.h"


//=======================================================================
//グローバル変数宣言
//=======================================================================

LPDIRECT3DTEXTURE9 g_apTextureBoss[4] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBoss = NULL;		//頂点バッファへのポインタ
Boss g_aBoss[MAX_BOSS];							//敵
int  g_EnemyBulletCnt;							//弾の間隔
int  g_EnemyBulletTypeCnt;							//弾の間隔


//=======================================================================
//初期化処理
//=======================================================================
void InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//でアイスのポインタ
	int nCntBoss;

	//デバイスの取得
	pDevice = GetDevice();

	//敵の初期化
	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		g_aBoss[nCntBoss].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].nType = 0;
		g_aBoss[nCntBoss].nCounterAnim = 0;
		g_aBoss[nCntBoss].nPatternAnim = 0;
		g_aBoss[nCntBoss].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//dog.png",
		&g_apTextureBoss[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//face_angry_woman5.png",
		&g_apTextureBoss[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//teachar.png",
		&g_apTextureBoss[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//enemy003.png",
		&g_apTextureBoss[3]);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BOSS,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBoss,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
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
	g_pVtxBuffBoss->Unlock();
}

//=======================================================================
//終了処理
//=======================================================================
void UninitBoss(void)
{
	int nCntBoss;
	for (nCntBoss = 0; nCntBoss < 4; nCntBoss++)
	{
		//テクスチャの破棄
		if (g_apTextureBoss[nCntBoss] != NULL)
		{
			g_apTextureBoss[nCntBoss]->Release();
			g_apTextureBoss[nCntBoss] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBoss != NULL)
	{
		g_pVtxBuffBoss->Release();
		g_pVtxBuffBoss = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateBoss(void)
{
	//========================================================
	//ボスの動き
	//========================================================
	int nCntBoss;
	VERTEX_2D *pVtx;		//頂点情報へのポインタ
							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{

		if (g_aBoss[nCntBoss].bUse == true)
		{
			g_aBoss[nCntBoss].nCounterAnim++;
			if (g_aBoss[nCntBoss].nCounterAnim == 200)
			{
				g_aBoss[nCntBoss].nCounterAnim = 0;		//カウンターを初期地に戻す
				g_aBoss[nCntBoss].nPatternAnim++;		//パターンNoを更新
				if (g_aBoss[nCntBoss].nPatternAnim > 1)
				{
					g_aBoss[nCntBoss].nPatternAnim = 0;
				}
				pVtx[0].tex = D3DXVECTOR2(g_aBoss[nCntBoss].nPatternAnim * 0.5f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aBoss[nCntBoss].nPatternAnim * 0.5f + 0.5f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aBoss[nCntBoss].nPatternAnim * 0.5f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aBoss[nCntBoss].nPatternAnim * 0.5f + 0.5f, 1.0f);
			}
			
			if (g_aBoss[nCntBoss].pos.x != SCREEN_WIDTH - (BOSS_WIDTH / 2) - 50.0f)
			{
				g_aBoss[nCntBoss].pos -= g_aBoss[nCntBoss].move;

			}

			pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_WIDTH / 2.0f, g_aBoss[nCntBoss].pos.y - BOSS_HEIGHT / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_WIDTH / 2.0f, g_aBoss[nCntBoss].pos.y - BOSS_HEIGHT / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_WIDTH / 2.0f, g_aBoss[nCntBoss].pos.y + BOSS_HEIGHT / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_WIDTH / 2.0f, g_aBoss[nCntBoss].pos.y + BOSS_HEIGHT / 2.0f, 0.0f);

			if (g_aBoss[nCntBoss].pos.x == SCREEN_WIDTH - (BOSS_WIDTH / 2) - 50.0f)
			{
				g_aBoss[nCntBoss].pos.x = SCREEN_WIDTH - (BOSS_WIDTH / 2) - 50.0f;

				g_EnemyBulletCnt++;
				if (g_EnemyBulletCnt == 150)
				{
					if (g_aBoss[nCntBoss].nLife <= 40)
					{
						if (g_EnemyBulletTypeCnt == 1)
						{
							if (GetMode() == MODE_GAME)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.2f, 0.0f), 0,15.0f,45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.5f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.8f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.2f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.5f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.8f, 0.0f), 0, 15.0f, 45.0f);
							}
							else if (GetMode() == MODE_STAGE1)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.2f, 0.0f), 6, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.5f, 0.0f), 5, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.8f, 0.0f), 4, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.2f, 0.0f),7, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.5f, 0.0f), 8, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.8f, 0.0f), 3, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
							}
							else if (GetMode() == MODE_STAGE3)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.2f, 0.0f), 9, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.8f, 0.0f), 5, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 1.5f, 0.0f), 4, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.2f, 0.0f), 3, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.8f, 0.0f), 3, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -1.5f, 0.0f), 10, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
							}
							g_EnemyBulletTypeCnt = 0;

						}
						else
						{
							if (GetMode() == MODE_GAME)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.0f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.4f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.9f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 1.4f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.4f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.9f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -1.4f, 0.0f), 0, 15.0f, 45.0f);
							}
							else if (GetMode() == MODE_STAGE1)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.0f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.4f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.9f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 1.4f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.4f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.9f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -1.4f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
							}
							else if (GetMode() == MODE_STAGE3)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.0f, 0.0f), 13, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.6f, 0.0f), 12, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 1.4f, 0.0f), 7, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 1.8f, 0.0f), 11, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.6f, 0.0f), 3, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -1.4f, 0.0f), 3, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -1.8f, 0.0f), 10, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
							}
							g_EnemyBulletTypeCnt++;


						}
						
					}

					else if (g_aBoss[nCntBoss].nLife > 40)
					{
						if (g_EnemyBulletTypeCnt == 1)
						{
							if (GetMode() == MODE_GAME)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, 0.5f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, 1.0f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, -0.5f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, -1.0f, 0.0f), 0, 15.0f, 45.0f);
							}
							else if (GetMode() == MODE_STAGE1)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, 0.5f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, 1.0f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, -0.5f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, -1.0f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
							}
							else if (GetMode() == MODE_STAGE3)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.2f, 0.0f), 9, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.8f, 0.0f), 5, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 1.5f, 0.0f), 4, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.2f, 0.0f), 3, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.8f, 0.0f), 3, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -1.5f, 0.0f), 10, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
							}
							g_EnemyBulletTypeCnt = 0;
						}
						else
						{
							if (GetMode() == MODE_GAME)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, 0.0f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, 0.4f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, -0.4f, 0.0f), 0, 15.0f, 45.0f);
							}
							else if (GetMode() == MODE_STAGE1)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, 0.0f, 0.0f), 2, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, 0.4f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, -0.4f, 0.0f), 3, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
							}
							else if (GetMode() == MODE_STAGE3)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.0f, 0.0f), 13, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.6f, 0.0f), 12, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 1.4f, 0.0f), 7, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 1.8f, 0.0f), 11, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.6f, 0.0f), 3, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -1.4f, 0.0f), 3, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -1.8f, 0.0f), 10, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
							}
							
							g_EnemyBulletTypeCnt++;
						}
						
					}

					
					g_EnemyBulletCnt = 0;
				}
				
			}


			if (g_aBoss[nCntBoss].pos.x <= 0 - BOSS_WIDTH)
			{
				g_aBoss[nCntBoss].bUse = false;		//使用していない状態にする
			}

		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBoss->Unlock();
}

//=======================================================================
//描画処理
//=======================================================================
void DrawBoss(void)
{
	int nCntBoss;

	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBoss, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定

	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == true)
		{
			//テクスチャ
			pDevice->SetTexture(0, g_apTextureBoss[g_aBoss[nCntBoss].nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntBoss * 4,					//描画を開始する頂点のインデックス
				2);					//描画するプリミティブ数
		}
	}
}

//=======================================================================
//設定処理
//=======================================================================
void SetBoss(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 move,int nLife)
{
	int nCntBoss;
	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == false)
		{
			g_aBoss[nCntBoss].pos = pos;
			//頂点座標の設定

			VERTEX_2D *pVtx;		//頂点情報へのポインタ
									//頂点バッファをロックし、頂点データのポインタを取得
			g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntBoss * 4);


			pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_WIDTH / 2.0f, g_aBoss[nCntBoss].pos.y - BOSS_HEIGHT / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_WIDTH / 2.0f, g_aBoss[nCntBoss].pos.y - BOSS_HEIGHT / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_WIDTH / 2.0f, g_aBoss[nCntBoss].pos.y + BOSS_HEIGHT / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_WIDTH / 2.0f, g_aBoss[nCntBoss].pos.y + BOSS_HEIGHT / 2.0f, 0.0f);

			//頂点バッファをアンロックする
			g_pVtxBuffBoss->Unlock();

			g_aBoss[nCntBoss].nType = nType;
			g_aBoss[nCntBoss].nLife = nLife;
			g_aBoss[nCntBoss].move = move;
			g_aBoss[nCntBoss].bUse = true;
			break;
		}
	}
}

//=======================================================================
//取得処理
//=======================================================================
Boss *GetBoss(void)
{
	return &g_aBoss[0];
}

