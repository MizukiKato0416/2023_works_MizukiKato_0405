//=======================================================================
//時間に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include <math.h>
#include "main.h"
#include "time.h"
#include "fade.h"
#include "score.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		//頂点バッファへのポインタ
Time g_aTimePolygon[MAX_TIME_POLYGON];							//タイマーのポリゴン数
int g_nTime;								//タイマー
int g_nCntTime;								//タイマーを少しずつ減らすカウント

//=======================================================================
//初期化処理
//=======================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//でアイスのポインタ
	int nCntTime;

	//デバイスの取得
	pDevice = GetDevice();

	//スコアの位置の初期化

	for (nCntTime = 0; nCntTime < MAX_TIME_POLYGON; nCntTime++)
	{
		g_aTimePolygon[nCntTime].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (TIME_POLYGON_WIDTH*(MAX_TIME_POLYGON - nCntTime) + (TIME_POLYGON_WIDTH / 2)), TIME_POLYGON_HEIGHT / 2, 0.0f);
	}
	g_nTime = 60;
	g_nCntTime = 0;



	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//score.png",
		&g_pTextureTime);



	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntTime = 0; nCntTime < MAX_TIME_POLYGON; nCntTime++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (TIME_POLYGON_WIDTH*(MAX_TIME_POLYGON - nCntTime)), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (TIME_POLYGON_WIDTH*(MAX_TIME_POLYGON - nCntTime - 1)), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (TIME_POLYGON_WIDTH*(MAX_TIME_POLYGON - nCntTime)), TIME_POLYGON_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (TIME_POLYGON_WIDTH*(MAX_TIME_POLYGON - nCntTime - 1)), TIME_POLYGON_HEIGHT, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;

	}


	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();
}

//=======================================================================
//終了処理
//=======================================================================
void UninitTime(void)
{
	//テクスチャの破棄
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateTime(void)
{
	int nCntTime;
	VERTEX_2D *pVtx;		//頂点情報へのポインタ
							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	

	for (nCntTime = 0; nCntTime < MAX_TIME_POLYGON; nCntTime++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (TIME_POLYGON_WIDTH*(MAX_TIME_POLYGON - nCntTime)), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (TIME_POLYGON_WIDTH*(MAX_TIME_POLYGON - nCntTime - 1)), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (TIME_POLYGON_WIDTH*(MAX_TIME_POLYGON - nCntTime)), TIME_POLYGON_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (TIME_POLYGON_WIDTH*(MAX_TIME_POLYGON - nCntTime - 1)), TIME_POLYGON_HEIGHT, 0.0f);

		if (nCntTime == 0)
		{
			pVtx[0].tex = D3DXVECTOR2(g_nTime / (int)powf(10, 2)*0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_nTime / (int)powf(10, 2)*0.1f + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_nTime / (int)powf(10, 2)*0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_nTime / (int)powf(10, 2)*0.1f + 0.1f, 1.0f);
		}
		else if (nCntTime == 2)
		{
			pVtx[0].tex = D3DXVECTOR2(g_nTime % 10 * 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_nTime % 10 * 0.1f + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_nTime % 10 * 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_nTime % 10 * 0.1f + 0.1f, 1.0f);
		}
		else
		{
			pVtx[0].tex = D3DXVECTOR2(g_nTime % (int)powf(10, MAX_TIME_POLYGON - nCntTime) / (int)powf(10, 2 - nCntTime) *0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_nTime % (int)powf(10, MAX_TIME_POLYGON - nCntTime) / (int)powf(10, 2 - nCntTime)*0.1f + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_nTime % (int)powf(10, MAX_TIME_POLYGON - nCntTime) / (int)powf(10, 2 - nCntTime)*0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_nTime % (int)powf(10, MAX_TIME_POLYGON - nCntTime) / (int)powf(10, 2 - nCntTime)*0.1f + 0.1f, 1.0f);
		}

		pVtx += 4;
	}
	
	
	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();


	g_nCntTime++;
	if (g_nCntTime >= 120 && g_nTime != 0)
	{
		g_nTime--;
		g_nCntTime = 0;
	}

	if (g_nTime <= 0 && GetFade() == FADE_NONE)
	{
		g_nTime = 0;
		SetFade(MODE_RESULT);
	}
}

//=======================================================================
//描画処理
//=======================================================================
void DrawTime(void)
{
	int nCntTime;

	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定

	for (nCntTime = 0; nCntTime < MAX_TIME_POLYGON; nCntTime++)
	{
		//テクスチャ
		pDevice->SetTexture(0, g_pTextureTime);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
			nCntTime * 4,					//描画を開始する頂点のインデックス
			2);					//描画するプリミティブ数
	}
	
}

//=======================================================================
//設定処理
//=======================================================================
void SetTime(int nTime)
{
	g_nTime += nTime;
}

//=======================================================================
//取得処理
//=======================================================================
int GetTime(void)
{
	return g_nTime;
}
