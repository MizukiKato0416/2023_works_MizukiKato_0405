#include "title_press_enter.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "databox.h"
#include "FeverMan.h"

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitlePressEnter = NULL;		//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureTitlePressEnter[2] = {};			//テクスチャへのポインタ

int nAlphaPressEnter = 0;		//PressEnterの透過度
bool bLockTitle = false;		//二回以上遷移しないようにロックするよ～～～～～～～～～
float fTex = 0.0f;				//テクスチャ座標
int nTime = 0;					//時間経過
bool b = false;

//初期化処理
void InitTitlePressEnter(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//デバイスのポインタ
	pDevice = GetDevice();				//デバイスを取得

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitlePressEnter,
		NULL);

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\titleText.png",
		&g_pTextureTitlePressEnter[0]);

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\press_enter.png",
		&g_pTextureTitlePressEnter[1]);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTitlePressEnter->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTitlePressEnter->Unlock();

	nAlphaPressEnter = 0;
	bLockTitle = false;
	fTex = 0.0f;
	nTime = 0;
	b = false;

	InitFeverMan();

	StopSound();
	PlaySound(SOUND_LABEL_DRUM_SE);
}

//終了処理
void UninitTitlePressEnter(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//テクスチャ破棄
		if (g_pTextureTitlePressEnter[nCnt] != NULL)
		{
			g_pTextureTitlePressEnter[nCnt]->Release();
			g_pTextureTitlePressEnter[nCnt] = NULL;
		}
	}

	//頂点バッファ破棄
	if (g_pVtxBuffTitlePressEnter != NULL)
	{
		g_pVtxBuffTitlePressEnter->Release();
		g_pVtxBuffTitlePressEnter = NULL;
	}
	UninitFeverMan();
}

//更新処理
void UpdateTitlePressEnter(void)
{
	Data *pData;
	pData = GetData();

	switch (pData->nTitleNum)
	{
	case 0:
		nTime++;

		if (nTime >= 64)
		{
			nTime = 64;
			fTex += 0.00165f;

			if ((fTex + 0.04f) >= 0.15f)fTex += 0.001f;
			if ((fTex + 0.04f) >= 0.3f)fTex += 0.0001f;
			if ((fTex + 0.04f) >= 0.5f)fTex += 0.001f;
			if ((fTex + 0.04f) >= 0.7f)fTex += 0.002f;
			if ((fTex + 0.04f) >= 0.9f)fTex += 0.002f;

			if ((fTex + 0.04f) >= 1.0f)
			{
				nTime = 0;
				fTex = 0.0f;
				pData->nTitleNum++;
				PlaySound(SOUND_LABEL_TITLE_BGM);
			}
		}
		break;

	case 1:
		nTime++;
		if (nTime >= 32)
		{
			nTime = 0;
			b = true;
		}
		if (b == true)
		{
			UpdateFeverMan();
		}

		if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
		{
			bLockTitle = true;
			PlaySound(SOUND_LABEL_TITLE_SE);
			SetFade(MODE_JUGGLER);
		}

		if (bLockTitle == true)
		{
			switch (nAlphaPressEnter)
			{
			case 0:
				nAlphaPressEnter = 255;
				break;

			case 255:
				nAlphaPressEnter = 0;
				break;
			}
		}
		break;
	}

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTitlePressEnter->Lock(0, 0, (void**)&pVtx, 0);

	switch (pData->nTitleNum)
	{
	case 0:
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(fTex, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(fTex + 0.04f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(fTex, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(fTex + 0.04f, 1.0f);
		break;

	case 1:
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		break;
	}

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255 - nAlphaPressEnter);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255 - nAlphaPressEnter);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255 - nAlphaPressEnter);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255 - nAlphaPressEnter);

	//頂点バッファをアンロック
	g_pVtxBuffTitlePressEnter->Unlock();
}

//描画処理
void DrawTitlePressEnter(void)
{
	Data *pData;
	pData = GetData();

	LPDIRECT3DDEVICE9 pDevice;							//デバイスのポインタ
	pDevice = GetDevice();								//デバイスを取得

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffTitlePressEnter,
		0,
		sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);											//頂点フォーマットの設定
	pDevice->SetTexture(0, g_pTextureTitlePressEnter[pData->nTitleNum]);	//テクスチャの設定

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,							//開始する頂点のインデックス
		2);							//プリミティブの数

	if (b == true)
	{
		DrawFeverMan();
	}
}