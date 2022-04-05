//=======================================================================
//ゲージに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#include "main.h"
#include "life.h"
#include "player.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================

LPDIRECT3DTEXTURE9 g_apTextureLife[MAX_TYPE] = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;		//頂点バッファへのポインタ
Life g_aLife[MAX_LIFE];

//=======================================================================
//初期化処理
//=======================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//でアイスのポインタ
	int nCntLife;

	//デバイスの取得
	pDevice = GetDevice();

	//ゲージの初期化
	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		g_aLife[nCntLife].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLife[nCntLife].fWidth = 0.0f;
		g_aLife[nCntLife].fHeight = 0.0f;
		g_aLife[nCntLife].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//PlayerLife.png",
		&g_apTextureLife[0]);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
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
	g_pVtxBuffLife->Unlock();
}

//=======================================================================
//終了処理
//=======================================================================
void UninitLife(void)
{
	//テクスチャの破棄
	for (int nCntTex = 0; nCntTex < MAX_TYPE; nCntTex++)
	{
		if (g_apTextureLife[nCntTex] != NULL)
		{
			g_apTextureLife[nCntTex]->Release();
			g_apTextureLife[nCntTex] = NULL;
		}
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
	//プレイヤーの体力ゲージ処理
	PLAYER *pPlayer = GetPlayer();
	for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == true)
		{
			VERTEX_2D *pVtx;		//頂点情報へのポインタ
									//頂点バッファをロックし、頂点データのポインタを取得
			g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

			if (g_aLife[nCntLife].nType = GAUGETYPE_PLAYER)
			{
				


			}

			pVtx += (nCntLife * 4);


			pVtx[0].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x, g_aLife[nCntLife].pos.y - g_aLife[nCntLife].fHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + g_aLife[nCntLife].fWidth, g_aLife[nCntLife].pos.y - g_aLife[nCntLife].fHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x, g_aLife[nCntLife].pos.y + g_aLife[nCntLife].fHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + g_aLife[nCntLife].fWidth, g_aLife[nCntLife].pos.y + g_aLife[nCntLife].fHeight / 2.0f, 0.0f);

			//頂点バッファをアンロックする
			g_pVtxBuffLife->Unlock();
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

	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == true)
		{
			pDevice->SetTexture(0, g_apTextureLife[g_aLife[nCntLife].nType]);	//テクスチャの設定
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
void SetLife(D3DXVECTOR3 pos, GAUGETYPE nType, float fWidth, float fHeight)
{
	int nCntLife;
	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == false)
		{
			g_aLife[nCntLife].pos = pos;
			g_aLife[nCntLife].fWidth = fWidth;
			g_aLife[nCntLife].fHeight = fHeight;
			g_aLife[nCntLife].nType = nType;
			g_aLife[nCntLife].bUse = true;


			//頂点座標の設定

			VERTEX_2D *pVtx;		//頂点情報へのポインタ
									//頂点バッファをロックし、頂点データのポインタを取得
			g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntLife * 4);


			pVtx[0].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x , g_aLife[nCntLife].pos.y - g_aLife[nCntLife].fHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + g_aLife[nCntLife].fWidth, g_aLife[nCntLife].pos.y - g_aLife[nCntLife].fHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x , g_aLife[nCntLife].pos.y + g_aLife[nCntLife].fHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + g_aLife[nCntLife].fWidth, g_aLife[nCntLife].pos.y + g_aLife[nCntLife].fHeight / 2.0f, 0.0f);

			//頂点バッファをアンロックする
			g_pVtxBuffLife->Unlock();
			break;
		}
	}
}

//=======================================================================
//取得処理
//=======================================================================
Life *GetLife(void)
{
	return &g_aLife[0];
}
