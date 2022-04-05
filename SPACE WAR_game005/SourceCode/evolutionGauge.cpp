//=======================================================================
//進化ゲージに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#include "main.h"
#include "evolutionGauge.h"
#include "player.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================

LPDIRECT3DTEXTURE9 g_apTextureEvolutionGauge[EVOLUTION_GAUGETYPE_MAX] = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEvolutionGauge = NULL;		//頂点バッファへのポインタ
EvolutionGauge g_aEvolutionGauge[MAX_EVOLUTIONGAUGE];

//=======================================================================
//初期化処理
//=======================================================================
void InitEvolutionGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//でアイスのポインタ
	int nCntEvolutionGauge;

	//デバイスの取得
	pDevice = GetDevice();

	//ゲージの初期化
	for (nCntEvolutionGauge = 0; nCntEvolutionGauge < MAX_EVOLUTIONGAUGE; nCntEvolutionGauge++)
	{
		g_aEvolutionGauge[nCntEvolutionGauge].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEvolutionGauge[nCntEvolutionGauge].fWidth = 0.0f;
		g_aEvolutionGauge[nCntEvolutionGauge].fHeight = 0.0f;
		g_aEvolutionGauge[nCntEvolutionGauge].bUse = false;
		g_aEvolutionGauge[nCntEvolutionGauge].bEvolution = false;
		g_aEvolutionGauge[nCntEvolutionGauge].bGaugeMax = false;
		g_aEvolutionGauge[nCntEvolutionGauge].fCnt = 0.0f;
		g_aEvolutionGauge[nCntEvolutionGauge].nCounter = 0;
		g_aEvolutionGauge[nCntEvolutionGauge].nTransparency = 255;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//PlayerEvolution.png",
		&g_apTextureEvolutionGauge[0]);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EVOLUTIONGAUGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEvolutionGauge,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffEvolutionGauge->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntEvolutionGauge = 0; nCntEvolutionGauge < MAX_EVOLUTIONGAUGE; nCntEvolutionGauge++)
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

		pVtx[0].col = D3DCOLOR_RGBA(255, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEvolutionGauge->Unlock();
}

//=======================================================================
//終了処理
//=======================================================================
void UninitEvolutionGauge(void)
{
	//テクスチャの破棄
	for (int nCntTex = 0; nCntTex < EVOLUTION_GAUGETYPE_MAX; nCntTex++)
	{
		if (g_apTextureEvolutionGauge[nCntTex] != NULL)
		{
			g_apTextureEvolutionGauge[nCntTex]->Release();
			g_apTextureEvolutionGauge[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEvolutionGauge != NULL)
	{
		g_pVtxBuffEvolutionGauge->Release();
		g_pVtxBuffEvolutionGauge = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateEvolutionGauge(void)
{
	//プレイヤーの体力ゲージ処理
	PLAYER *pPlayer = GetPlayer();
	for (int nCntEvolutionGauge = 0; nCntEvolutionGauge < MAX_EVOLUTIONGAUGE; nCntEvolutionGauge++)
	{
		if (g_aEvolutionGauge[nCntEvolutionGauge].bUse == true)
		{
			VERTEX_2D *pVtx;		//頂点情報へのポインタ
									//頂点バッファをロックし、頂点データのポインタを取得
			g_pVtxBuffEvolutionGauge->Lock(0, 0, (void**)&pVtx, 0);

			if (pPlayer->bEvolution == true)
			{
				g_aEvolutionGauge[nCntEvolutionGauge].bEvolution = true;
			}

			if (g_aEvolutionGauge[nCntEvolutionGauge].bEvolution == true)
			{
				g_aEvolutionGauge[nCntEvolutionGauge].fCnt -= 0.02f;
				g_aEvolutionGauge[nCntEvolutionGauge].nCounter++;

				if (g_aEvolutionGauge[nCntEvolutionGauge].nCounter >= 5)
				{
					if (g_aEvolutionGauge[nCntEvolutionGauge].nTransparency == 255)
					{
						g_aEvolutionGauge[nCntEvolutionGauge].nTransparency = 0;
					}
					else if (g_aEvolutionGauge[nCntEvolutionGauge].nTransparency == 0)
					{
						g_aEvolutionGauge[nCntEvolutionGauge].nTransparency = 255;
					}
					g_aEvolutionGauge[nCntEvolutionGauge].nCounter = 0;
				}

				if (g_aEvolutionGauge[nCntEvolutionGauge].fCnt <= 0.0f)
				{
					g_aEvolutionGauge[nCntEvolutionGauge].fCnt = 0.0f;
					g_aEvolutionGauge[nCntEvolutionGauge].bEvolution = false;
					pPlayer->bEvolution = false;
					pPlayer->bDegenerate = true;
					g_aEvolutionGauge[nCntEvolutionGauge].nTransparency = 255;
					g_aEvolutionGauge[nCntEvolutionGauge].nCounter = 0;
				}
			}

			g_aEvolutionGauge[nCntEvolutionGauge].fWidth = (EVOLUTIONGAUGE_WIDTH / MAX_EVOLUTIONGAUGE_ADD) * g_aEvolutionGauge[nCntEvolutionGauge].fCnt;


			pVtx += (nCntEvolutionGauge * 4);

			pVtx[0].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x, g_aEvolutionGauge[nCntEvolutionGauge].pos.y - g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x + g_aEvolutionGauge[nCntEvolutionGauge].fWidth, g_aEvolutionGauge[nCntEvolutionGauge].pos.y - g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x, g_aEvolutionGauge[nCntEvolutionGauge].pos.y + g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x + g_aEvolutionGauge[nCntEvolutionGauge].fWidth, g_aEvolutionGauge[nCntEvolutionGauge].pos.y + g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);

			pVtx[0].col = D3DCOLOR_RGBA(255, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, 255);

			//頂点バッファをアンロックする
			g_pVtxBuffEvolutionGauge->Unlock();
		}
	}
}

//=======================================================================
//描画処理
//=======================================================================
void DrawEvolutionGauge(void)
{
	int nCntEvolutionGauge;

	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEvolutionGauge, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定

	for (nCntEvolutionGauge = 0; nCntEvolutionGauge < MAX_EVOLUTIONGAUGE; nCntEvolutionGauge++)
	{
		if (g_aEvolutionGauge[nCntEvolutionGauge].bUse == true)
		{
			pDevice->SetTexture(0, g_apTextureEvolutionGauge[g_aEvolutionGauge[nCntEvolutionGauge].nType]);	//テクスチャの設定
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntEvolutionGauge * 4,					//描画を開始する頂点のインデックス
				2);					//描画するプリミティブ数
		}
	}
}

//=======================================================================
//設定処理
//=======================================================================
void SetEvolutionGauge(D3DXVECTOR3 pos, EVOLUTION_GAUGETYPE nType, float fWidth, float fHeight)
{
	int nCntEvolutionGauge;
	for (nCntEvolutionGauge = 0; nCntEvolutionGauge < MAX_EVOLUTIONGAUGE; nCntEvolutionGauge++)
	{
		if (g_aEvolutionGauge[nCntEvolutionGauge].bUse == false)
		{
			g_aEvolutionGauge[nCntEvolutionGauge].pos = pos;
			g_aEvolutionGauge[nCntEvolutionGauge].fWidth = fWidth;
			g_aEvolutionGauge[nCntEvolutionGauge].fHeight = fHeight;
			g_aEvolutionGauge[nCntEvolutionGauge].nType = nType;
			g_aEvolutionGauge[nCntEvolutionGauge].bUse = true;


			//頂点座標の設定

			VERTEX_2D *pVtx;		//頂点情報へのポインタ
									//頂点バッファをロックし、頂点データのポインタを取得
			g_pVtxBuffEvolutionGauge->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntEvolutionGauge * 4);


			pVtx[0].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x , g_aEvolutionGauge[nCntEvolutionGauge].pos.y - g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x + g_aEvolutionGauge[nCntEvolutionGauge].fWidth, g_aEvolutionGauge[nCntEvolutionGauge].pos.y - g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x , g_aEvolutionGauge[nCntEvolutionGauge].pos.y + g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x + g_aEvolutionGauge[nCntEvolutionGauge].fWidth, g_aEvolutionGauge[nCntEvolutionGauge].pos.y + g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);

			//頂点バッファをアンロックする
			g_pVtxBuffEvolutionGauge->Unlock();
			break;
		}
	}
}

//=======================================================================
//ゲージ増加処理
//=======================================================================
void SetAddEvolutionGauge(float fGauge)
{
	for (int nCntEvolutionGauge = 0; nCntEvolutionGauge < MAX_EVOLUTIONGAUGE; nCntEvolutionGauge++)
	{
		if (g_aEvolutionGauge[nCntEvolutionGauge].bUse == true)
		{
			if (g_aEvolutionGauge[nCntEvolutionGauge].bEvolution == false)
			{
				g_aEvolutionGauge[nCntEvolutionGauge].fCnt += fGauge;
			}

			if (g_aEvolutionGauge[nCntEvolutionGauge].nType == EVOLUTION_GAUGETYPE_PLAYER)
			{
				if (g_aEvolutionGauge[nCntEvolutionGauge].fCnt >= MAX_EVOLUTIONGAUGE_ADD)
				{
					g_aEvolutionGauge[nCntEvolutionGauge].fCnt = MAX_EVOLUTIONGAUGE_ADD;
					g_aEvolutionGauge[nCntEvolutionGauge].bGaugeMax = true;
				}
				else
				{
					g_aEvolutionGauge[nCntEvolutionGauge].bGaugeMax = false;
				}
			}

			g_aEvolutionGauge[nCntEvolutionGauge].fWidth = (EVOLUTIONGAUGE_WIDTH / MAX_EVOLUTIONGAUGE_ADD) * g_aEvolutionGauge[nCntEvolutionGauge].fCnt;

			//頂点座標の設定

			VERTEX_2D *pVtx;		//頂点情報へのポインタ
									//頂点バッファをロックし、頂点データのポインタを取得
			g_pVtxBuffEvolutionGauge->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntEvolutionGauge * 4);


			pVtx[0].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x, g_aEvolutionGauge[nCntEvolutionGauge].pos.y - g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x + g_aEvolutionGauge[nCntEvolutionGauge].fWidth, g_aEvolutionGauge[nCntEvolutionGauge].pos.y - g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x, g_aEvolutionGauge[nCntEvolutionGauge].pos.y + g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x + g_aEvolutionGauge[nCntEvolutionGauge].fWidth, g_aEvolutionGauge[nCntEvolutionGauge].pos.y + g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);

			//頂点バッファをアンロックする
			g_pVtxBuffEvolutionGauge->Unlock();
		}
	}
}


//=======================================================================
//取得処理
//=======================================================================
EvolutionGauge *GetEvolutionGauge(void)
{
	return &g_aEvolutionGauge[0];
}
