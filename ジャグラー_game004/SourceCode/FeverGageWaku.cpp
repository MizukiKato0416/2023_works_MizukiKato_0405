#include "FeverGageWaku.h"
#include "databox.h"

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFeverGageWaku = NULL;		//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureFeverGageWaku = NULL;		//テクスチャへのポインタ

//初期化処理
void InitFeverGageWaku(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//デバイスのポインタ
	pDevice = GetDevice();				//デバイスを取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\GageWaku.png",
		&g_pTextureFeverGageWaku);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFeverGageWaku,
		NULL);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffFeverGageWaku->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0, 0.0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
	g_pVtxBuffFeverGageWaku->Unlock();
}

//終了処理
void UninitFeverGageWaku(void)
{
	//テクスチャ破棄
	if (g_pTextureFeverGageWaku != NULL)
	{
		g_pTextureFeverGageWaku->Release();
		g_pTextureFeverGageWaku = NULL;
	}

	//頂点バッファ破棄
	if (g_pVtxBuffFeverGageWaku != NULL)
	{
		g_pVtxBuffFeverGageWaku->Release();
		g_pVtxBuffFeverGageWaku = NULL;
	}
}

//更新処理
void UpdateFeverGageWaku(void)
{

}

//描画処理
void DrawFeverGageWaku(void)
{
	Data *pData;
	pData = GetData();

	LPDIRECT3DDEVICE9 pDevice;							//デバイスのポインタ
	pDevice = GetDevice();								//デバイスを取得

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffFeverGageWaku,
		0,
		sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);									//頂点フォーマットの設定
	pDevice->SetTexture(0, g_pTextureFeverGageWaku);		//テクスチャの設定

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,							//開始する頂点のインデックス
		2);							//プリミティブの数
}