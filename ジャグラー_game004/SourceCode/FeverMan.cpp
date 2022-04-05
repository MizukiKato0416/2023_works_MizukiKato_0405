#include "FeverMan.h"
#include "databox.h"

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFeverMan = NULL;		//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureFeverMan = NULL;		//テクスチャへのポインタ
float posYJump = SCREEN_HEIGHT;
float moveY = 0.0f;

//初期化処理
void InitFeverMan(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//デバイスのポインタ
	pDevice = GetDevice();				//デバイスを取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\FeverMan.png",
		&g_pTextureFeverMan);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFeverMan,
		NULL);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffFeverMan->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffFeverMan->Unlock();

	posYJump = SCREEN_HEIGHT;
	moveY = 0.0f;
}

//終了処理
void UninitFeverMan(void)
{
	//テクスチャ破棄
	if (g_pTextureFeverMan != NULL)
	{
		g_pTextureFeverMan->Release();
		g_pTextureFeverMan = NULL;
	}

	//頂点バッファ破棄
	if (g_pVtxBuffFeverMan != NULL)
	{
		g_pVtxBuffFeverMan->Release();
		g_pVtxBuffFeverMan = NULL;
	}
}

//更新処理
void UpdateFeverMan(void)
{
	//--------------------------------------------------------------
	//重力関係

	//ジャンプ
	if (posYJump >= SCREEN_HEIGHT)
	{
		moveY = -14.0f;
	}

	//重力を強める
	moveY += 1.0f;

	posYJump += moveY;

	//--------------------------------------------------------------

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffFeverMan->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0, posYJump - SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, posYJump - SCREEN_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0, posYJump, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, posYJump, 0.0f);

	//頂点バッファをアンロック
	g_pVtxBuffFeverMan->Unlock();
}

//描画処理
void DrawFeverMan(void)
{
	Data *pData;
	pData = GetData();

	LPDIRECT3DDEVICE9 pDevice;							//デバイスのポインタ
	pDevice = GetDevice();								//デバイスを取得

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffFeverMan,
		0,
		sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);									//頂点フォーマットの設定
	pDevice->SetTexture(0, g_pTextureFeverMan);		//テクスチャの設定

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,							//開始する頂点のインデックス
		2);							//プリミティブの数
}