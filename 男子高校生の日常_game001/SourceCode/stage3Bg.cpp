//=======================================================================
//ステージ3ゲーム背景に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "stage3Bg.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================

LPDIRECT3DTEXTURE9 g_pTextureStage3Bg = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStage3Bg = NULL;		//頂点バッファへのポインタ

//=======================================================================
//初期化処理
//=======================================================================
void InitStage3Bg(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//class_room.jpg",
		&g_pTextureStage3Bg);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStage3Bg,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffStage3Bg->Lock(0, 0, (void**)&pVtx, 0);


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
	g_pVtxBuffStage3Bg->Unlock();
}


//=======================================================================
//終了処理
//=======================================================================
void UninitStage3Bg(void)
{
	//テクスチャの破棄
	if (g_pTextureStage3Bg != NULL)
	{
		g_pTextureStage3Bg->Release();
		g_pTextureStage3Bg = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffStage3Bg != NULL)
	{
		g_pVtxBuffStage3Bg->Release();
		g_pVtxBuffStage3Bg = NULL;
	}
}


//=======================================================================
//更新処理
//=======================================================================
void UpdateStage3Bg(void)
{

}


//=======================================================================
//描画処理
//=======================================================================
void DrawStage3Bg(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffStage3Bg, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定
	pDevice->SetTexture(0, g_pTextureStage3Bg);	//テクスチャの設定
												//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,					//開始する頂点のインデックス
		2);					//描画するプリミティブ数
}