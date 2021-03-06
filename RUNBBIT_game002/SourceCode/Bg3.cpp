//=======================================================================
//ステージ1ゲーム背景に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "bg3.h"
#include "block.h"
#include "player.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================

LPDIRECT3DTEXTURE9 g_pTextureBg3 = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg3 = NULL;		//頂点バッファへのポインタ
float fPosTexU3;


//=======================================================================
//初期化処理
//=======================================================================
void InitBg3(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//bg003.png",
		&g_pTextureBg3);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBg3,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffBg3->Lock(0, 0, (void**)&pVtx, 0);


	pVtx[0].pos = D3DXVECTOR3(0.0f, 600.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH * 2.0f, 600.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH * 2.0f, SCREEN_HEIGHT, 0.0f);


	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;



	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 235);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 235);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 235);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 235);


	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffBg3->Unlock();
}


//=======================================================================
//終了処理
//=======================================================================
void UninitBg3(void)
{
	//テクスチャの破棄
	if (g_pTextureBg3 != NULL)
	{
		g_pTextureBg3->Release();
		g_pTextureBg3 = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBg3 != NULL)
	{
		g_pVtxBuffBg3->Release();
		g_pVtxBuffBg3 = NULL;
	}
}


//=======================================================================
//更新処理
//=======================================================================
void UpdateBg3(void)
{

	PLAYER *pPlayer;
	//ブロックの取得
	pPlayer = GetPlayer();

	BLOCK *pBlock2;
	//ブロックの取得
	pBlock2 = GetBlock2();



	if (pPlayer->pos.x >= SCREEN_WIDTH / 2.0f)
	{
		if (pBlock2->move.x > 0.0f)
		{
			fPosTexU3 += 0.0025f;
			if (fPosTexU3 >= 1.0f)
			{
				fPosTexU3 -= 1.0f;
			}
		}

		if (pPlayer->move.x > 0.0f)
		{
			fPosTexU3 += 0.001f * POLYGON_SPEED;
			if (fPosTexU3 >= 1.0f)
			{
				fPosTexU3 -= 1.0f;
			}
		}
	}

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffBg3->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(fPosTexU3, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fPosTexU3 + 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(fPosTexU3, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fPosTexU3 + 1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffBg3->Unlock();
}


//=======================================================================
//描画処理
//=======================================================================
void DrawBg3(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBg3, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定
	pDevice->SetTexture(0, g_pTextureBg3);	//テクスチャの設定
											//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,					//開始する頂点のインデックス
		2);					//描画するプリミティブ数
}