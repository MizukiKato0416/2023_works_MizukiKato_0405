//=======================================================================
//変化のないMASKに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#include "main.h"
#include "mask.h"
#include "player.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================

LPDIRECT3DTEXTURE9 g_apTextureMask[MASKTYPE_MAX] = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMask = NULL;		//頂点バッファへのポインタ
MASK g_aMask[MAX_MASK];
int g_nCntDamage;	//ダメージ時表示時間

//=======================================================================
//初期化処理
//=======================================================================
void InitMask(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//でアイスのポインタ
	int nCntMask;

	//デバイスの取得
	pDevice = GetDevice();

	//ゲージの初期化
	for (nCntMask = 0; nCntMask < MAX_MASK; nCntMask++)
	{
		g_aMask[nCntMask].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMask[nCntMask].fWidth = 0.0f;
		g_aMask[nCntMask].fHeight = 0.0f;
		g_aMask[nCntMask].col = 0;
		g_aMask[nCntMask].bUse = false;
	}
	g_nCntDamage = 0;


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/damage02.png",
		&g_apTextureMask[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/gameOver.png",
		&g_apTextureMask[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/timeUp.png",
		&g_apTextureMask[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_MASK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMask,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffMask->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntMask = 0; nCntMask < MAX_MASK; nCntMask++)
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
	g_pVtxBuffMask->Unlock();
}

//=======================================================================
//終了処理
//=======================================================================
void UninitMask(void)
{
	//テクスチャの破棄
	for (int nCntTex = 0; nCntTex < MASKTYPE_MAX; nCntTex++)
	{
		if (g_apTextureMask[nCntTex] != NULL)
		{
			g_apTextureMask[nCntTex]->Release();
			g_apTextureMask[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMask != NULL)
	{
		g_pVtxBuffMask->Release();
		g_pVtxBuffMask = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateMask(void)
{
	for (int nCntMask = 0; nCntMask < MAX_MASK; nCntMask++)
	{
		if (g_aMask[nCntMask].bUse == true)
		{
			VERTEX_2D *pVtx;
			//頂点バッファをロックし、頂点データのポインタを取得
			g_pVtxBuffMask->Lock(0, 0, (void**)&pVtx, 0);

			if (g_aMask[nCntMask].nType == MASKTYPE_DAMAGE)
			{
				g_nCntDamage++;
				if (g_nCntDamage > 20)
				{
					g_nCntDamage = 0;
					g_aMask[nCntMask].bUse = false;
				}
			}
			else if (g_aMask[nCntMask].nType == MASKTYPE_TIMEUP)
			{
				if (g_aMask[nCntMask].pos.y >= SCREEN_HEIGHT / 2.0f)
				{

				}
				else
				{
					g_aMask[nCntMask].pos.y += 10.0f;
				}
			}
			//頂点バッファをアンロックする
			g_pVtxBuffMask->Unlock();
		}
	}
}

//=======================================================================
//描画処理
//=======================================================================
void DrawMask(void)
{
	int nCntMask;

	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMask, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定

	for (nCntMask = 0; nCntMask < MASKTYPE_MAX; nCntMask++)
	{
		if (g_aMask[nCntMask].bUse == true)
		{
			pDevice->SetTexture(0, g_apTextureMask[g_aMask[nCntMask].nType]);	//テクスチャの設定
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntMask * 4,					//描画を開始する頂点のインデックス
				2);					//描画するプリミティブ数
		}
	}
}

//=======================================================================
//設定処理
//=======================================================================
void SetMask(D3DXVECTOR3 pos, MASKTYPE nType, float fWidth, float fHeight)
{
	int nCntMask;
	for (nCntMask = 0; nCntMask < MAX_MASK; nCntMask++)
	{
		if (g_aMask[nCntMask].bUse == false)
		{
			g_aMask[nCntMask].pos = pos;
			g_aMask[nCntMask].fWidth = fWidth;
			g_aMask[nCntMask].fHeight = fHeight;
			g_aMask[nCntMask].nType = nType;
			g_aMask[nCntMask].bUse = true;


			//頂点座標の設定

			VERTEX_2D *pVtx;		//頂点情報へのポインタ
									//頂点バッファをロックし、頂点データのポインタを取得
			g_pVtxBuffMask->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntMask * 4);

			pVtx[0].pos = D3DXVECTOR3(g_aMask[nCntMask].pos.x , g_aMask[nCntMask].pos.y - g_aMask[nCntMask].fHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aMask[nCntMask].pos.x + g_aMask[nCntMask].fWidth, g_aMask[nCntMask].pos.y - g_aMask[nCntMask].fHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aMask[nCntMask].pos.x , g_aMask[nCntMask].pos.y + g_aMask[nCntMask].fHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aMask[nCntMask].pos.x + g_aMask[nCntMask].fWidth, g_aMask[nCntMask].pos.y + g_aMask[nCntMask].fHeight / 2.0f, 0.0f);

			//頂点バッファをアンロックする
			g_pVtxBuffMask->Unlock();
			break;
		}
	}
}

//=======================================================================
//取得処理
//=======================================================================
MASK *GetMask(void)
{
	return &g_aMask[0];
}
