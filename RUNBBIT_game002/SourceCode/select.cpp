//=======================================================================
//メニュー選択に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "select.h"
#include "input.h"
#include "sound.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================

LPDIRECT3DTEXTURE9 g_apTextureSelect[SELECT_TYPE] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelect = NULL;		//頂点バッファへのポインタ
Select g_aSelect[MAX_SELECT];								//メニュー選択

//=======================================================================
//初期化処理
//=======================================================================
void InitSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//でアイスのポインタ
	int nCntSelect;

	//デバイスの取得
	pDevice = GetDevice();

	//メニューの初期化
	for (nCntSelect = 0; nCntSelect < MAX_SELECT; nCntSelect++)
	{
		g_aSelect[nCntSelect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSelect[nCntSelect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSelect[nCntSelect].fSelectWidth = 0;
		g_aSelect[nCntSelect].fSelectHeight = 0;
		g_aSelect[nCntSelect].bUse = false;
		g_aSelect[nCntSelect].bMenu1 = true;
		g_aSelect[nCntSelect].bMenu2 = false;
		g_aSelect[nCntSelect].bMenu3 = false;
	}


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//player000.png",
		&g_apTextureSelect[0]);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SELECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSelect,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntSelect = 0; nCntSelect < MAX_SELECT; nCntSelect++)
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

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffSelect->Unlock();
}

//=======================================================================
//終了処理
//=======================================================================
void UninitSelect(void)
{
	int nCntSelect;
	for (nCntSelect = 0; nCntSelect < SELECT_TYPE; nCntSelect++)
	{
		//テクスチャの破棄
		if (g_apTextureSelect[nCntSelect] != NULL)
		{
			g_apTextureSelect[nCntSelect]->Release();
			g_apTextureSelect[nCntSelect] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffSelect != NULL)
	{
		g_pVtxBuffSelect->Release();
		g_pVtxBuffSelect = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateSelect(void)
{
	//任意のキーが押されたかどうか
	if (GetKeyboardTrigger(DIK_DOWN) == true)
	{
		for (int nCntSelect = 0; nCntSelect < MAX_SELECT; nCntSelect++)
		{
			if (g_aSelect[nCntSelect].bMenu1 == true)
			{
				PlaySound(SOUND_LABEL_CURSOR);
				g_aSelect[nCntSelect].bMenu2 = true;
				g_aSelect[nCntSelect].bMenu1 = false;
			}
			else if (g_aSelect[nCntSelect].bMenu2 == true)
			{
				PlaySound(SOUND_LABEL_CURSOR);
				g_aSelect[nCntSelect].bMenu3 = true;
				g_aSelect[nCntSelect].bMenu2 = false;
			}
		}
	}
	else if (GetKeyboardTrigger(DIK_UP) == true)
	{
		for (int nCntSelect = 0; nCntSelect < MAX_SELECT; nCntSelect++)
		{
			if (g_aSelect[nCntSelect].bMenu3 == true)
			{
				PlaySound(SOUND_LABEL_CURSOR);
				g_aSelect[nCntSelect].bMenu2 = true;
				g_aSelect[nCntSelect].bMenu3 = false;
			}
			else if (g_aSelect[nCntSelect].bMenu2 == true)
			{
				PlaySound(SOUND_LABEL_CURSOR);
				g_aSelect[nCntSelect].bMenu1 = true;
				g_aSelect[nCntSelect].bMenu2 = false;
			}
		}
	}


	VERTEX_2D *pVtx;		//頂点情報へのポインタ
							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntSelect = 0; nCntSelect < MAX_SELECT; nCntSelect++)
	{
		if (g_aSelect[nCntSelect].bMenu1 == true)
		{
			if (g_aSelect[nCntSelect].nType == 0)
			{
				pVtx[0].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x - g_aSelect[nCntSelect].fSelectWidth / 2.0f, g_aSelect[nCntSelect].pos.y - g_aSelect[nCntSelect].fSelectHeight / 2.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x + g_aSelect[nCntSelect].fSelectWidth / 2.0f, g_aSelect[nCntSelect].pos.y - g_aSelect[nCntSelect].fSelectHeight / 2.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x - g_aSelect[nCntSelect].fSelectWidth / 2.0f, g_aSelect[nCntSelect].pos.y + g_aSelect[nCntSelect].fSelectHeight / 2.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x + g_aSelect[nCntSelect].fSelectWidth / 2.0f, g_aSelect[nCntSelect].pos.y + g_aSelect[nCntSelect].fSelectHeight / 2.0f, 0.0f);
			}
		}
		else if (g_aSelect[nCntSelect].bMenu2 == true)
		{
			if (g_aSelect[nCntSelect].nType == 0)
			{
				pVtx[0].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x - g_aSelect[nCntSelect].fSelectWidth / 2.0f, (g_aSelect[nCntSelect].pos.y * 2 - g_aSelect[nCntSelect].fSelectHeight / 2.0f), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x + g_aSelect[nCntSelect].fSelectWidth / 2.0f, (g_aSelect[nCntSelect].pos.y * 2 - g_aSelect[nCntSelect].fSelectHeight / 2.0f), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x - g_aSelect[nCntSelect].fSelectWidth / 2.0f, (g_aSelect[nCntSelect].pos.y * 2 + g_aSelect[nCntSelect].fSelectHeight / 2.0f), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x + g_aSelect[nCntSelect].fSelectWidth / 2.0f, (g_aSelect[nCntSelect].pos.y * 2 + g_aSelect[nCntSelect].fSelectHeight / 2.0f), 0.0f);
			}
		}
		else if (g_aSelect[nCntSelect].bMenu3 == true)
		{
			if (g_aSelect[nCntSelect].nType == 0)
			{
				pVtx[0].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x - g_aSelect[nCntSelect].fSelectWidth / 2.0f, (g_aSelect[nCntSelect].pos.y * 3 - g_aSelect[nCntSelect].fSelectHeight / 2.0f), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x + g_aSelect[nCntSelect].fSelectWidth / 2.0f, (g_aSelect[nCntSelect].pos.y * 3 - g_aSelect[nCntSelect].fSelectHeight / 2.0f), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x - g_aSelect[nCntSelect].fSelectWidth / 2.0f, (g_aSelect[nCntSelect].pos.y * 3 + g_aSelect[nCntSelect].fSelectHeight / 2.0f), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x + g_aSelect[nCntSelect].fSelectWidth / 2.0f, (g_aSelect[nCntSelect].pos.y * 3 + g_aSelect[nCntSelect].fSelectHeight / 2.0f), 0.0f);
			}
		}
	}
}

//=======================================================================
//描画処理
//=======================================================================
void DrawSelect(void)
{
	int nCntSelect;

	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSelect, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定

	for (nCntSelect = 0; nCntSelect < MAX_SELECT; nCntSelect++)
	{
		if (g_aSelect[nCntSelect].bUse == true)
		{
			//テクスチャ
			pDevice->SetTexture(0, g_apTextureSelect[g_aSelect[nCntSelect].nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntSelect * 4,					//描画を開始する頂点のインデックス
				2);					//描画するプリミティブ数
		}
	}
}

//=======================================================================
//設定処理
//=======================================================================
void SetSelect(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 move, float fSelectWidth, float fSelectHeight)
{
	int nCntSelect;
	for (nCntSelect = 0; nCntSelect < MAX_SELECT; nCntSelect++)
	{
		if (g_aSelect[nCntSelect].bUse == false)
		{
			g_aSelect[nCntSelect].pos = pos;
			g_aSelect[nCntSelect].fSelectWidth = fSelectWidth;
			g_aSelect[nCntSelect].fSelectHeight = fSelectHeight;
			//頂点座標の設定

			VERTEX_2D *pVtx;		//頂点情報へのポインタ
									//頂点バッファをロックし、頂点データのポインタを取得
			g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntSelect * 4);


			pVtx[0].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x - g_aSelect[nCntSelect].fSelectWidth / 2.0f, g_aSelect[nCntSelect].pos.y - g_aSelect[nCntSelect].fSelectHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x + g_aSelect[nCntSelect].fSelectWidth / 2.0f, g_aSelect[nCntSelect].pos.y - g_aSelect[nCntSelect].fSelectHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x - g_aSelect[nCntSelect].fSelectWidth / 2.0f, g_aSelect[nCntSelect].pos.y + g_aSelect[nCntSelect].fSelectHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x + g_aSelect[nCntSelect].fSelectWidth / 2.0f, g_aSelect[nCntSelect].pos.y + g_aSelect[nCntSelect].fSelectHeight / 2.0f, 0.0f);

			//頂点バッファをアンロックする
			g_pVtxBuffSelect->Unlock();

			g_aSelect[nCntSelect].nType = nType;
			g_aSelect[nCntSelect].move = move;
			g_aSelect[nCntSelect].bUse = true;
			break;
		}
	}
}

//=======================================================================
//取得処理
//=======================================================================
Select *GetSelect(void)
{
	return &g_aSelect[0];
}
