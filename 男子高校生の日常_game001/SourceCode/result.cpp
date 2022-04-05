//=======================================================================
//リザルトに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "result.h"
#include "sound.h"
#include "input.h"
#include "score.h"
#include "HiScore.h"
#include "fade.h"


//=======================================================================
//グローバル変数宣言
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;		//頂点バッファへのポインタ
int g_nCnt;

//=======================================================================
//初期化処理
//=======================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	g_nCnt = 0;			//初期化


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//result.png",
		&g_pTextureResult);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);


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
	g_pVtxBuffResult->Unlock();
	PlaySound(SOUND_LABEL_BGM003);

	InitScore();
	InitHiScore();

}

//=======================================================================
//終了処理
//=======================================================================
void UninitResult(void)
{
	StopSound(SOUND_LABEL_BGM003);
	//テクスチャの破棄
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}


	UninitScore();
	UninitHiScore();
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateResult(void)
{
	g_nCnt++;
	//スペースキーを押したときの処理
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		PlaySound(SOUND_LABEL_START001);
		SetFade(MODE_TITLE);
	}
	
	else if (g_nCnt == 10000)
	{
		g_nCnt = 0;
		SetFade(MODE_TITLE);
	}


	

	UpdateScore();
	UpdateHiScore();

}

//=======================================================================
//描画処理
//=======================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定
	pDevice->SetTexture(0, g_pTextureResult);	//テクスチャの設定
												//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,					//開始する頂点のインデックス
		2);					//描画するプリミティブ数

	DrawScore();
	DrawHiScore();
}