#include "FeverGage.h"
#include "databox.h"

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFeverGage = NULL;		//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureFeverGage = NULL;		//テクスチャへのポインタ
int nTi = 0;

//初期化処理
void InitFeverGage(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//デバイスのポインタ
	pDevice = GetDevice();				//デバイスを取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\Gage.png",
		&g_pTextureFeverGage);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFeverGage,
		NULL);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffFeverGage->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(16.0f, 702.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(65.0f, 702.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(16.0f, 702.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(65.0f, 702.0f, 0.0f);

	//rhwの設定(1.0f固定)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

	//頂点バッファをアンロック
	g_pVtxBuffFeverGage->Unlock();
}

//終了処理
void UninitFeverGage(void)
{
	//テクスチャ破棄
	if (g_pTextureFeverGage != NULL)
	{
		g_pTextureFeverGage->Release();
		g_pTextureFeverGage = NULL;
	}

	//頂点バッファ破棄
	if (g_pVtxBuffFeverGage != NULL)
	{
		g_pVtxBuffFeverGage->Release();
		g_pVtxBuffFeverGage = NULL;
	}
}

//更新処理
void UpdateFeverGage(void)
{
	Data *pData;
	pData = GetData();

	pData->nFever--;

	if (pData->nFever <= 0.0f)	pData->nFever = 0.0f;

	if (pData->bOK == true)
	{
		pData->nFever += 100;
		pData->nFever = false;
	}

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffFeverGage->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(16.0f, 702.0f - pData->nFever, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(65.0f, 702.0f - pData->nFever, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(16.0f, 702.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(65.0f, 702.0f, 0.0f);

	//頂点バッファをアンロック
	g_pVtxBuffFeverGage->Unlock();
}

//描画処理
void DrawFeverGage(void)
{
	Data *pData;
	pData = GetData();

	LPDIRECT3DDEVICE9 pDevice;							//デバイスのポインタ
	pDevice = GetDevice();								//デバイスを取得

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffFeverGage,
		0,
		sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);									//頂点フォーマットの設定
	pDevice->SetTexture(0, g_pTextureFeverGage);		//テクスチャの設定

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,							//開始する頂点のインデックス
		2);							//プリミティブの数
}