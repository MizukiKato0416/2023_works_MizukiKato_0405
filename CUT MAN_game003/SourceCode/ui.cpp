//=======================================================================
//変化のないUIに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#include "main.h"
#include "ui.h"
#include "player.h"
#include "stage1.h"
#include "pad.h"
#include "sound.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================

LPDIRECT3DTEXTURE9 g_apTextureUi[UITYPE_MAX] = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUi = NULL;		//頂点バッファへのポインタ
UI g_aUi[MAX_UI];
int g_nSelect;	//ポーズで何が選ばれているか

//=======================================================================
//初期化処理
//=======================================================================
void InitUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//でアイスのポインタ
	int nCntUi;

	//デバイスの取得
	pDevice = GetDevice();

	//ゲージの初期化
	for (nCntUi = 0; nCntUi < MAX_UI; nCntUi++)
	{
		g_aUi[nCntUi].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aUi[nCntUi].fWidth = 0.0f;
		g_aUi[nCntUi].fHeight = 0.0f;
		g_aUi[nCntUi].col = 0;
		g_aUi[nCntUi].bUse = false;
	}
	g_nSelect = 0;		//つづけるが選ばれている状態


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PlayerUi.png",
		&g_apTextureUi[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/title.png",
		&g_apTextureUi[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/start.png",
		&g_apTextureUi[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/pause.png",
		&g_apTextureUi[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/continue.png",
		&g_apTextureUi[4]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/exit.png",
		&g_apTextureUi[5]);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_UI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUi,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntUi = 0; nCntUi < MAX_UI; nCntUi++)
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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffUi->Unlock();
}

//=======================================================================
//終了処理
//=======================================================================
void UninitUi(void)
{
	//テクスチャの破棄
	for (int nCntTex = 0; nCntTex < UITYPE_MAX; nCntTex++)
	{
		if (g_apTextureUi[nCntTex] != NULL)
		{
			g_apTextureUi[nCntTex]->Release();
			g_apTextureUi[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffUi != NULL)
	{
		g_pVtxBuffUi->Release();
		g_pVtxBuffUi = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateUi(void)
{
	Stage1 *pStage1 = GetStage1();
	for (int nCntUi = 0; nCntUi < MAX_UI; nCntUi++)
	{
		if (g_aUi[nCntUi].bUse == true)
		{
			VERTEX_2D *pVtx;
			//頂点バッファをロックし、頂点データのポインタを取得
			g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);

			if (g_aUi[nCntUi].nType == UITYPE_TITLE)
			{
				if (g_aUi[nCntUi].pos.y >= MAX_TITLE_HEIGHT)
				{
					g_aUi[nCntUi].pos.y = MAX_TITLE_HEIGHT;
				}
				else
				{
					g_aUi[nCntUi].pos.y += 2;
				}
				pVtx += (nCntUi * 4);
				pVtx[0].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x, g_aUi[nCntUi].pos.y - g_aUi[nCntUi].fHeight / 2.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x + g_aUi[nCntUi].fWidth, g_aUi[nCntUi].pos.y - g_aUi[nCntUi].fHeight / 2.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x, g_aUi[nCntUi].pos.y + g_aUi[nCntUi].fHeight / 2.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x + g_aUi[nCntUi].fWidth, g_aUi[nCntUi].pos.y + g_aUi[nCntUi].fHeight / 2.0f, 0.0f);
				
			}
			else if (g_aUi[nCntUi].nType == UITYPE_START)
			{
				if (g_aUi[nCntUi].col >= 255)
				{
					g_aUi[nCntUi].col = 0;
				}
				pVtx += (nCntUi * 4);
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aUi[nCntUi].col);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aUi[nCntUi].col);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aUi[nCntUi].col);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aUi[nCntUi].col);
				
				g_aUi[nCntUi].col += 2;
			}
			else if (g_aUi[nCntUi].nType == UITYPE_CONTINUE || g_aUi[nCntUi].nType == UITYPE_EXIT)
			{
				if (g_aUi[nCntUi].nType == UITYPE_CONTINUE)
				{
					if (g_nSelect == 0)
					{
						g_aUi[nCntUi].col = 255;
					}
					else
					{
						g_aUi[nCntUi].col = 150;
					}
				}
				else if(g_aUi[nCntUi].nType == UITYPE_EXIT)
				{
					if (g_nSelect == 0)
					{
						g_aUi[nCntUi].col = 150;
					}
					else
					{
						g_aUi[nCntUi].col = 255;
					}
				}

				pVtx += (nCntUi * 4);
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aUi[nCntUi].col);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aUi[nCntUi].col);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aUi[nCntUi].col);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aUi[nCntUi].col);

				if (pStage1->bStop == true)
				{
					g_aUi[nCntUi].bUse = false;
				}

				if (GetLeftStick(STICKTYPE_UP) == true && g_nSelect == 1)
				{
					g_nSelect--;
					PlaySound(SOUND_LABEL_SELECT);
				}
				else if(GetLeftStick(STICKTYPE_DOWN) == true && g_nSelect == 0)
				{
					g_nSelect++;
					PlaySound(SOUND_LABEL_SELECT);
				}



			}
			else if (g_aUi[nCntUi].nType == UITYPE_PAUSE)
			{
				if (pStage1->bStop == true)
				{
					g_aUi[nCntUi].bUse = false;
				}
			}
			

			//頂点バッファをアンロックする
			g_pVtxBuffUi->Unlock();
		}
	}
}

//=======================================================================
//描画処理
//=======================================================================
void DrawUi(void)
{
	int nCntUi;

	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffUi, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定

	for (nCntUi = 0; nCntUi < UITYPE_MAX; nCntUi++)
	{
		if (g_aUi[nCntUi].bUse == true)
		{
			pDevice->SetTexture(0, g_apTextureUi[g_aUi[nCntUi].nType]);	//テクスチャの設定
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntUi * 4,					//描画を開始する頂点のインデックス
				2);					//描画するプリミティブ数
		}
	}
}

//=======================================================================
//設定処理
//=======================================================================
void SetUi(D3DXVECTOR3 pos, UITYPE nType, float fWidth, float fHeight)
{
	int nCntUi;
	for (nCntUi = 0; nCntUi < MAX_UI; nCntUi++)
	{
		if (g_aUi[nCntUi].bUse == false)
		{
			g_aUi[nCntUi].pos = pos;
			g_aUi[nCntUi].fWidth = fWidth;
			g_aUi[nCntUi].fHeight = fHeight;
			g_aUi[nCntUi].nType = nType;
			g_aUi[nCntUi].bUse = true;


			//頂点座標の設定

			VERTEX_2D *pVtx;		//頂点情報へのポインタ
									//頂点バッファをロックし、頂点データのポインタを取得
			g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntUi * 4);

			pVtx[0].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x , g_aUi[nCntUi].pos.y - g_aUi[nCntUi].fHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x + g_aUi[nCntUi].fWidth, g_aUi[nCntUi].pos.y - g_aUi[nCntUi].fHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x , g_aUi[nCntUi].pos.y + g_aUi[nCntUi].fHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x + g_aUi[nCntUi].fWidth, g_aUi[nCntUi].pos.y + g_aUi[nCntUi].fHeight / 2.0f, 0.0f);

			//頂点バッファをアンロックする
			g_pVtxBuffUi->Unlock();
			break;
		}
	}
}

//=======================================================================
//取得処理
//=======================================================================
UI *GetUi(void)
{
	return &g_aUi[0];
}

int GetPauseUi(void)
{
	return g_nSelect;
}