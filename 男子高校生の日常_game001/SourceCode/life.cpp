//=======================================================================
//プレイヤーのライフに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "life.h"
#include "item.h"
#include "sound.h"
#include "fade.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================

LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;		//頂点バッファへのポインタ
Life g_aLife[MAX_LIFE_POLYGON];							//ライフのポリゴン数
float g_fLife;											//ライフの値

//=======================================================================
//初期化処理
//=======================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//でアイスのポインタ
	int nCntLife;

	//デバイスの取得
	pDevice = GetDevice();

	//ライフの位置の初期化
	for (nCntLife = 0; nCntLife < MAX_LIFE_POLYGON; nCntLife++)
	{
		g_aLife[nCntLife].pos = D3DXVECTOR3((LIFE_WIDTH * nCntLife) + (LIFE_WIDTH / 2), LIFE_HEIGHT / 2, 0.0f);
		g_aLife[nCntLife].bUse = false;

	}

	g_fLife = 4.0f;				//ライフの値


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//life.png",
		&g_pTextureLife);



	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFE_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntLife = 0; nCntLife < MAX_LIFE_POLYGON; nCntLife++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x - (LIFE_WIDTH / 2) + (LIFE_WIDTH/4 * nCntLife), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + (LIFE_WIDTH / 2) + (LIFE_WIDTH/4 * nCntLife), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x - (LIFE_WIDTH / 2) + (LIFE_WIDTH/4 * nCntLife), LIFE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + (LIFE_WIDTH / 2) + (LIFE_WIDTH/4 * nCntLife), LIFE_HEIGHT, 0.0f);

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
	g_pVtxBuffLife->Unlock();
}

//=======================================================================
//終了処理
//=======================================================================
void UninitLife(void)
{
	//テクスチャの破棄
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateLife(void)
{
	int nCntLife;
	int nCnt;
	VERTEX_2D *pVtx;		//頂点情報へのポインタ
							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntLife = 0; nCntLife < MAX_LIFE_POLYGON; nCntLife++)
	{

		for (nCnt = 0; nCnt < MAX_LIFE_POLYGON; nCnt++)
		{
			if (g_fLife >= nCnt + 0.5f)
			{
				g_aLife[nCnt].bUse = true;
			}
			else
			{
				g_aLife[nCnt].bUse = false;
			}
		}
		

		if (g_aLife[nCntLife].bUse == true)
		{
			if (g_fLife == nCntLife+0.5f)
			{
				pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			else
			{
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
			}
		}



		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffLife->Unlock();





	if (g_fLife <= 0.0f && GetFade() == FADE_NONE)
	{
		if (GetMode() == MODE_STAGE1)
		{
			g_fLife = 0.0f;
			SetFade(MODE_GAMEOVER);
		}
		else if (GetMode() == MODE_GAME)
		{
			g_fLife = 0.0f;
			SetFade(MODE_GAMEOVER);
		}
		else if (GetMode() == MODE_STAGE3)
		{
			g_fLife = 0.0f;
			SetFade(MODE_GAMEOVER);
		}
	}
}

//=======================================================================
//描画処理
//=======================================================================
void DrawLife(void)
{
	int nCntLife;

	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定

	for (nCntLife = 0; nCntLife < MAX_LIFE_POLYGON; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == true)
		{
			//テクスチャ
			pDevice->SetTexture(0, g_pTextureLife);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntLife * 4,					//描画を開始する頂点のインデックス
				2);					//描画するプリミティブ数
		}
	}
}

//=======================================================================
//設定処理
//=======================================================================
void SetLife(float fLife)
{
	g_fLife -= fLife;
	if (g_fLife>8)
	{
		g_fLife = 8;
	}
}

//=======================================================================
//取得処理
//=======================================================================
Life *GetLife(void)
{
	return &g_aLife[0];
}