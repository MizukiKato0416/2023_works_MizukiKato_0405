//=======================================================================
//ステージ1ゲーム背景に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "bg.h"
#include "player.h"
#include "block.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================

LPDIRECT3DTEXTURE9 g_pTextureBg = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = NULL;		//頂点バッファへのポインタ
float fPosTexU;

//=======================================================================
//初期化処理
//=======================================================================
void InitBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//初期化
	fPosTexU = 0.0f;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//bg001.jpg",
		&g_pTextureBg);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBg,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);


	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);


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

	//頂点バッファをアンロックする
	g_pVtxBuffBg->Unlock();
}


//=======================================================================
//終了処理
//=======================================================================
void UninitBg(void)
{
	//テクスチャの破棄
	if (g_pTextureBg != NULL)
	{
		g_pTextureBg->Release();
		g_pTextureBg = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBg != NULL)
	{
		g_pVtxBuffBg->Release();
		g_pVtxBuffBg = NULL;
	}
}


//=======================================================================
//更新処理
//=======================================================================
void UpdateBg(void)
{
	PLAYER *pPlayer;
	//ブロックの取得
	pPlayer = GetPlayer();

	BLOCK *pBlock2;
	//ブロックの取得
	pBlock2 = GetBlock2();

	


	if (pPlayer->pos.x >= SCROLE_START_POS)
	{
		if (pBlock2->move.x > 0.0f)
		{
			fPosTexU += 0.00025f;
			if (fPosTexU >= 1.0f)
			{
				fPosTexU -= 1.0f;
			}
		}
		
		if (pPlayer->move.x > 0.0f)
		{
			fPosTexU += 0.0002f * POLYGON_SPEED;
			if (fPosTexU >= 1.0f)
			{
				fPosTexU -= 1.0f;
			}
		}
		
	}


	VERTEX_2D *pVtx;		//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(fPosTexU, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fPosTexU + 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(fPosTexU, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fPosTexU + 1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffBg->Unlock();

}


//=======================================================================
//描画処理
//=======================================================================
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBg, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定
	pDevice->SetTexture(0, g_pTextureBg);	//テクスチャの設定
											//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,					//開始する頂点のインデックス
		2);					//描画するプリミティブ数
}