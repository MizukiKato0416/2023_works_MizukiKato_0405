//=======================================================================
//メニューに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#include "main.h"
#include "menue.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "pad.h"
#include "ui.h"


//=======================================================================
//グローバル変数宣言
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureMenue = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMenue = NULL;		//頂点バッファへのポインタ

//=======================================================================
//初期化処理
//=======================================================================
void InitMenue(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//menue.jpg",
		&g_pTextureMenue);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMenue,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffMenue->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffMenue->Unlock();

	PlaySound(SOUND_LABEL_MENU_BGM);
	InitUi();
	SetUi(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 4.0f, 0.0f), UITYPE_GAMESTART, 600.0f, 75.0f);
	SetUi(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 4.0f * 2.0f, 0.0f), UITYPE_TUTORIAL, 600.0f, 75.0f);
	SetUi(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 4.0f * 3.0f, 0.0f), UITYPE_BACKTITLE, 600.0f, 75.0f);
}

//=======================================================================
//終了処理
//=======================================================================
void UninitMenue(void)
{
	UninitUi();
	StopSound(SOUND_LABEL_MENU_BGM);

	//テクスチャの破棄
	if (g_pTextureMenue != NULL)
	{
		g_pTextureMenue->Release();
		g_pTextureMenue = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMenue != NULL)
	{
		g_pVtxBuffMenue->Release();
		g_pVtxBuffMenue = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateMenue(void)
{
	int nSelect = GetPauseUi();
	UpdateUi();




	if (GetButtonTrigger(XINPUT_GAMEPAD_START) == true || GetKeyboardTrigger(DIK_SPACE) == true || GetButtonTrigger(XINPUT_GAMEPAD_B) == true)
	{
		if (nSelect == 0)
		{
			if (GetFade() == FADE_NONE)
			{
				SetFade(MODE_STAGE1);
				PlaySound(SOUND_LABEL_TITLE_DECIDE);
			}
		}
		else if (nSelect == 1)
		{
			if (GetFade() == FADE_NONE)
			{
				SetFade(MODE_DESCRIPTION);
				PlaySound(SOUND_LABEL_TITLE_DECIDE);
			}
		}
		else if (nSelect == 2)
		{
			if (GetFade() == FADE_NONE)
			{
				SetFade(MODE_TITLE);
				PlaySound(SOUND_LABEL_TITLE_DECIDE);
			}
		}
	}
}

//=======================================================================
//描画処理
//=======================================================================
void DrawMenue(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMenue, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定
	pDevice->SetTexture(0, g_pTextureMenue);	//テクスチャの設定
												//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,					//開始する頂点のインデックス
		2);					//描画するプリミティブ数

	DrawUi();
}