//=======================================================================
//静止画に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#include "main.h"
#include "picture.h"
#include "pad.h"
#include "sound.h"
#include "fade.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================

LPDIRECT3DTEXTURE9 g_apTexturePicture[PICTURETYPE_MAX] = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPicture = NULL;		//頂点バッファへのポインタ
PICTURE g_aPicture[MAX_PICTURE];
int g_nCntPage;

//=======================================================================
//初期化処理
//=======================================================================
void InitPicture(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//でアイスのポインタ
	int nCntPicture;

	//デバイスの取得
	pDevice = GetDevice();

	//ゲージの初期化
	for (nCntPicture = 0; nCntPicture < MAX_PICTURE; nCntPicture++)
	{
		g_aPicture[nCntPicture].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
		g_aPicture[nCntPicture].fWidth = SCREEN_WIDTH;
		g_aPicture[nCntPicture].fHeight = SCREEN_HEIGHT;
		g_aPicture[nCntPicture].nType = PICTURETYPE_CONTROL;
		g_aPicture[nCntPicture].bUse = true;
	}
	g_nCntPage = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/setsumei000.jpg",
		&g_apTexturePicture[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/setsumei001.jpg",
		&g_apTexturePicture[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/setsumei002.jpg",
		&g_apTexturePicture[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/sousa.jpg",
		&g_apTexturePicture[3]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PICTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPicture,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffPicture->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntPicture = 0; nCntPicture < MAX_PICTURE; nCntPicture++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x, g_aPicture[nCntPicture].pos.y - g_aPicture[nCntPicture].fHeight / 2.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x + g_aPicture[nCntPicture].fWidth, g_aPicture[nCntPicture].pos.y - g_aPicture[nCntPicture].fHeight / 2.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x, g_aPicture[nCntPicture].pos.y + g_aPicture[nCntPicture].fHeight / 2.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x + g_aPicture[nCntPicture].fWidth, g_aPicture[nCntPicture].pos.y + g_aPicture[nCntPicture].fHeight / 2.0f, 0.0f);

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

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPicture->Unlock();
}

//=======================================================================
//終了処理
//=======================================================================
void UninitPicture(void)
{
	//テクスチャの破棄
	for (int nCntTex = 0; nCntTex < PICTURETYPE_MAX; nCntTex++)
	{
		if (g_apTexturePicture[nCntTex] != NULL)
		{
			g_apTexturePicture[nCntTex]->Release();
			g_apTexturePicture[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPicture != NULL)
	{
		g_pVtxBuffPicture->Release();
		g_pVtxBuffPicture = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdatePicture(void)
{
	for (int nCntPicture = 0; nCntPicture < MAX_PICTURE; nCntPicture++)
	{
		if (g_aPicture[nCntPicture].bUse == true)
		{
			if (g_nCntPage == 0)
			{
				g_aPicture[nCntPicture].nType = PICTURETYPE_CONTROL;
			}
			else if (g_nCntPage == 1)
			{
				g_aPicture[nCntPicture].nType = PICTURETYPE_SETSUNEI000;
			}
			else if (g_nCntPage == 2)
			{
				g_aPicture[nCntPicture].nType = PICTURETYPE_SETSUNEI001;
			}
			else if (g_nCntPage == 3)
			{
				g_aPicture[nCntPicture].nType = PICTURETYPE_SETSUNEI002;
			}
		}
	}

	if (GetButtonTrigger(XINPUT_GAMEPAD_A) == true && g_nCntPage != 0)
	{
		g_nCntPage--;
		PlaySound(SOUND_LABEL_RETURN);
	}
	else if (GetButtonTrigger(XINPUT_GAMEPAD_B) == true && g_nCntPage != 3)
	{
		g_nCntPage++;
		PlaySound(SOUND_LABEL_RETURN);
	}
	else if((GetButtonTrigger(XINPUT_GAMEPAD_B) == true | GetButtonTrigger(XINPUT_GAMEPAD_START) == true) && g_nCntPage == 3 && GetFade() == FADE_NONE)
	{
		PlaySound(SOUND_LABEL_TITLE_DECIDE);
		SetFade(MODE_MENUE);
	}
	else if ((GetButtonTrigger(XINPUT_GAMEPAD_A) == true | GetButtonTrigger(XINPUT_GAMEPAD_START) == true) && g_nCntPage == 0 && GetFade() == FADE_NONE)
	{
		PlaySound(SOUND_LABEL_TITLE_DECIDE);
		SetFade(MODE_MENUE);
	}
}

//=======================================================================
//描画処理
//=======================================================================
void DrawPicture(void)
{
	int nCntPicture;

	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPicture, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定

	for (nCntPicture = 0; nCntPicture < MAX_PICTURE; nCntPicture++)
	{
		if (g_aPicture[nCntPicture].bUse == true)
		{
			pDevice->SetTexture(0, g_apTexturePicture[g_aPicture[nCntPicture].nType]);	//テクスチャの設定
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntPicture * 4,					//描画を開始する頂点のインデックス
				2);					//描画するプリミティブ数
		}
	}
}

//=======================================================================
//取得処理
//=======================================================================
PICTURE *GetPicture(void)
{
	return &g_aPicture[0];
}
