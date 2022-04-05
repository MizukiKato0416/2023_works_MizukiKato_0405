//=======================================================================
//ルール画面に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "rule2.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "word.h"


//=======================================================================
//グローバル変数宣言
//=======================================================================

LPDIRECT3DTEXTURE9 g_pTextureRule2 = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRule2 = NULL;		//頂点バッファへのポインタ

//=======================================================================
//初期化処理
//=======================================================================
void InitRule2(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//rule.png",
		&g_pTextureRule2);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRule2,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffRule2->Lock(0, 0, (void**)&pVtx, 0);


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
	g_pVtxBuffRule2->Unlock();

	InitWord();
	SetWord(D3DXVECTOR3(SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT - 150.0f, 0.0f), 1, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 700.0f, 150.0f);
	SetWord(D3DXVECTOR3(SCREEN_WIDTH / 8.0f * 7.0f, 650.0f, 0.0f), 4, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 300.0f, 50.0f);
}


//=======================================================================
//終了処理
//=======================================================================
void UninitRule2(void)
{
	UninitWord();
	//テクスチャの破棄
	if (g_pTextureRule2 != NULL)
	{
		g_pTextureRule2->Release();
		g_pTextureRule2 = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRule2 != NULL)
	{
		g_pVtxBuffRule2->Release();
		g_pVtxBuffRule2 = NULL;
	}
}


//=======================================================================
//更新処理
//=======================================================================
void UpdateRule2(void)
{
	//スペースキーを押したときの処理
	if (GetMode() == MODE_RULE2)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			PlaySound(SOUND_LABEL_DECIDE);
			SetFade(MODE_TUTORIAL);
		}
	}

	UpdateWord();
}


//=======================================================================
//描画処理
//=======================================================================
void DrawRule2(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRule2, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定
	pDevice->SetTexture(0, g_pTextureRule2);	//テクスチャの設定
											//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,					//開始する頂点のインデックス
		2);					//描画するプリミティブ数

	DrawWord();
}