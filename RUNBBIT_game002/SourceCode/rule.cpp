//=======================================================================
//ルール画面に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "rule.h"
#include "input.h"
#include "fade.h"
#include "menu.h"
#include "select.h"
#include "sound.h"


//=======================================================================
//グローバル変数宣言
//=======================================================================

LPDIRECT3DTEXTURE9 g_pTextureRule = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRule = NULL;		//頂点バッファへのポインタ

//=======================================================================
//初期化処理
//=======================================================================
void InitRule(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//menu000.jpg",
		&g_pTextureRule);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRule,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffRule->Lock(0, 0, (void**)&pVtx, 0);


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
	g_pVtxBuffRule->Unlock();

	InitMenu();
	InitSelect();

	SetSelect(D3DXVECTOR3(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f, 0.0f), 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.0f, 70.0f);
	SetMenu(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 4.0f, 0.0f), 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400.0f * 1.2f, 70.0f * 1.2f);
	SetMenu(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 4.0f * 2.0f, 0.0f), 1, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400.0f * 1.2f, 70.0f * 1.2f);
	SetMenu(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 4.0f * 3.0f, 0.0f), 2, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400.0f * 1.2f, 70.0f * 1.2f);

	PlaySound(SOUND_LABEL_RESULT_BGM);

}


//=======================================================================
//終了処理
//=======================================================================
void UninitRule(void)
{
	//テクスチャの破棄
	if (g_pTextureRule != NULL)
	{
		g_pTextureRule->Release();
		g_pTextureRule = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRule != NULL)
	{
		g_pVtxBuffRule->Release();
		g_pVtxBuffRule = NULL;
	}

	UninitMenu();
	UninitSelect();
}


//=======================================================================
//更新処理
//=======================================================================
void UpdateRule(void)
{
	Select *pSelect;
	//セレクトの取得
	pSelect = GetSelect();

	//エンターを押したときの処理
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (pSelect->bMenu1 == true)
		{
			if (pSelect->nType == 0)
			{
				SetFade(MODE_STAGE1);
				PlaySound(SOUND_LABEL_DECIDE);
			}
		}
		else if (pSelect->bMenu2 == true)
		{
			if (pSelect->nType == 0)
			{
				SetFade(MODE_RULE2);
				PlaySound(SOUND_LABEL_DECIDE);
			}
		}
		else if (pSelect->bMenu3 == true)
		{
			if (pSelect->nType == 0)
			{
				SetFade(MODE_TITLE);
				PlaySound(SOUND_LABEL_RETURN);
			}
		}
	}
	
	UpdateMenu();
	UpdateSelect();
}


//=======================================================================
//描画処理
//=======================================================================
void DrawRule(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRule, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定
	pDevice->SetTexture(0, g_pTextureRule);	//テクスチャの設定
											//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,					//開始する頂点のインデックス
		2);					//描画するプリミティブ数


	DrawMenu();
	DrawSelect();
}