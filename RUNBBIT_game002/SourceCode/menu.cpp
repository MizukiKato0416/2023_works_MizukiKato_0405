//=======================================================================
//メニューに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "menu.h"
#include "select.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================

LPDIRECT3DTEXTURE9 g_apTextureMenu[MENU_TYPE] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMenu = NULL;		//頂点バッファへのポインタ
Menu g_aMenu[MAX_MENU];								//メニュー

//=======================================================================
//初期化処理
//=======================================================================
void InitMenu(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//でアイスのポインタ
	int nCntMenu;

	//デバイスの取得
	pDevice = GetDevice();

	//メニューの初期化
	for (nCntMenu = 0; nCntMenu < MAX_MENU; nCntMenu++)
	{
		g_aMenu[nCntMenu].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMenu[nCntMenu].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMenu[nCntMenu].fMenuWidth = 0;
		g_aMenu[nCntMenu].fMenuHeight = 0;
		g_aMenu[nCntMenu].bUse = false;
		g_aMenu[nCntMenu].bSelectUse = false;
	}
	g_aMenu[0].bSelectUse = true;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//gameStartUi.png",
		&g_apTextureMenu[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//tutorialUi.png",
		&g_apTextureMenu[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//titleUi.png",
		&g_apTextureMenu[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//continueUi.png",
		&g_apTextureMenu[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//restartUi.png",
		&g_apTextureMenu[4]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//exitUi.png",
		&g_apTextureMenu[5]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_MENU,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMenu,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffMenu->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMenu = 0; nCntMenu < MAX_MENU; nCntMenu++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		if (g_aMenu[nCntMenu].bSelectUse == true)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
		}
		else if (g_aMenu[nCntMenu].bSelectUse == false)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffMenu->Unlock();
}

//=======================================================================
//終了処理
//=======================================================================
void UninitMenu(void)
{
	int nCntMenu;
	for (nCntMenu = 0; nCntMenu < MENU_TYPE; nCntMenu++)
	{
		//テクスチャの破棄
		if (g_apTextureMenu[nCntMenu] != NULL)
		{
			g_apTextureMenu[nCntMenu]->Release();
			g_apTextureMenu[nCntMenu] = NULL;
		}
		g_aMenu[nCntMenu].bUse = false;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffMenu != NULL)
	{
		g_pVtxBuffMenu->Release();
		g_pVtxBuffMenu = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateMenu(void)
{
	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffMenu->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMenu = 0; nCntMenu < MENU_TYPE; nCntMenu++)
	{
		if (g_aMenu[nCntMenu].bUse == true)
		{
			if (g_aMenu[nCntMenu].bSelectUse == true)
			{
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
			}
			else if (g_aMenu[nCntMenu].bSelectUse == false)
			{
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			pVtx += 4;
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffMenu->Unlock();


	Select *pSelect;
	//セレクトの取得
	pSelect = GetSelect();

	if (pSelect->bMenu1 == true)
	{
		g_aMenu[0].bSelectUse = true;
		g_aMenu[1].bSelectUse = false;
		g_aMenu[2].bSelectUse = false;
	}
	else if (pSelect->bMenu2 == true)
	{
		g_aMenu[1].bSelectUse = true;
		g_aMenu[0].bSelectUse = false;
		g_aMenu[2].bSelectUse = false;
	}
	else if (pSelect->bMenu3 == true)
	{
		g_aMenu[2].bSelectUse = true;
		g_aMenu[0].bSelectUse = false;
		g_aMenu[1].bSelectUse = false;
	}
}

//=======================================================================
//描画処理
//=======================================================================
void DrawMenu(void)
{
	int nCntMenu;

	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMenu, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定

	for (nCntMenu = 0; nCntMenu < MAX_MENU; nCntMenu++)
	{
		if (g_aMenu[nCntMenu].bUse == true)
		{
			//テクスチャ
			pDevice->SetTexture(0, g_apTextureMenu[g_aMenu[nCntMenu].nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntMenu * 4,					//描画を開始する頂点のインデックス
				2);					//描画するプリミティブ数
		}
	}
}

//=======================================================================
//設定処理
//=======================================================================
void SetMenu(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 move, float fMenuWidth, float fMenuHeight)
{
	int nCntMenu;
	for (nCntMenu = 0; nCntMenu < MAX_MENU; nCntMenu++)
	{
		if (g_aMenu[nCntMenu].bUse == false)
		{
			g_aMenu[nCntMenu].pos = pos;
			g_aMenu[nCntMenu].fMenuWidth = fMenuWidth;
			g_aMenu[nCntMenu].fMenuHeight = fMenuHeight;
			//頂点座標の設定

			VERTEX_2D *pVtx;		//頂点情報へのポインタ
									//頂点バッファをロックし、頂点データのポインタを取得
			g_pVtxBuffMenu->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntMenu * 4);


			pVtx[0].pos = D3DXVECTOR3(g_aMenu[nCntMenu].pos.x - g_aMenu[nCntMenu].fMenuWidth / 2.0f, g_aMenu[nCntMenu].pos.y - g_aMenu[nCntMenu].fMenuHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aMenu[nCntMenu].pos.x + g_aMenu[nCntMenu].fMenuWidth / 2.0f, g_aMenu[nCntMenu].pos.y - g_aMenu[nCntMenu].fMenuHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aMenu[nCntMenu].pos.x - g_aMenu[nCntMenu].fMenuWidth / 2.0f, g_aMenu[nCntMenu].pos.y + g_aMenu[nCntMenu].fMenuHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aMenu[nCntMenu].pos.x + g_aMenu[nCntMenu].fMenuWidth / 2.0f, g_aMenu[nCntMenu].pos.y + g_aMenu[nCntMenu].fMenuHeight / 2.0f, 0.0f);

			//頂点バッファをアンロックする
			g_pVtxBuffMenu->Unlock();

			g_aMenu[nCntMenu].nType = nType;
			g_aMenu[nCntMenu].move = move;
			g_aMenu[nCntMenu].bUse = true;
			break;
		}
	}
}

//=======================================================================
//取得処理
//=======================================================================
Menu *GetMenu(void)
{
	return &g_aMenu[0];
}
