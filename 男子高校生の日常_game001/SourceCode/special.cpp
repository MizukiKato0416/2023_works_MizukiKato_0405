//=======================================================================
//必殺技のUIに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "special.h"
#include "item.h"
#include "life.h"
#include "fade.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================

LPDIRECT3DTEXTURE9 g_pTextureSpecial = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSpecial = NULL;	//頂点バッファへのポインタ
Special g_aSpecial;

//=======================================================================
//初期化処理
//=======================================================================
void InitSpecial(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//でアイスのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//位置の初期化
	g_aSpecial.pos = D3DXVECTOR3((SPECIAL_WIDTH / 2), LIFE_HEIGHT + SPECIAL_HEIGHT / 2, 0.0f);
	g_aSpecial.bUse = false;


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//SP_UI.png",
		&g_pTextureSpecial);



	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSpecial,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffSpecial->Lock(0, 0, (void**)&pVtx, 0);



	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_aSpecial.pos.x - (SPECIAL_WIDTH / 2), g_aSpecial.pos.y - SPECIAL_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aSpecial.pos.x + (SPECIAL_WIDTH / 2), g_aSpecial.pos.y - SPECIAL_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aSpecial.pos.x - (SPECIAL_WIDTH / 2), g_aSpecial.pos.y + SPECIAL_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aSpecial.pos.x + (SPECIAL_WIDTH / 2), g_aSpecial.pos.y + SPECIAL_HEIGHT / 2, 0.0f);

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
	g_pVtxBuffSpecial->Unlock();
}

//=======================================================================
//終了処理
//=======================================================================
void UninitSpecial(void)
{
	//テクスチャの破棄
	if (g_pTextureSpecial != NULL)
	{
		g_pTextureSpecial->Release();
		g_pTextureSpecial = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffSpecial != NULL)
	{
		g_pVtxBuffSpecial->Release();
		g_pVtxBuffSpecial = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateSpecial(void)
{
	VERTEX_2D *pVtx;		//頂点情報へのポインタ
	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffSpecial->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aSpecial.bUse == true)
	{
		pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	else if (g_aSpecial.bUse == false)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
	}



	//頂点バッファをアンロックする
	g_pVtxBuffSpecial->Unlock();

}

//=======================================================================
//描画処理
//=======================================================================
void DrawSpecial(void)
{

	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSpecial, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定

	//テクスチャ
	pDevice->SetTexture(0, g_pTextureSpecial);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,					//描画を開始する頂点のインデックス
		2);					//描画するプリミティブ数
}

//=======================================================================
//取得処理
//=======================================================================
Special *GetSpecial(void)
{
	return &g_aSpecial;
}
