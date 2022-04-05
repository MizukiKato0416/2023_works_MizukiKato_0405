//=======================================================================
//ワードに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "word.h"
#include "input.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================

LPDIRECT3DTEXTURE9 g_apTextureWord[WORD_TYPE] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWord = NULL;		//頂点バッファへのポインタ
Word g_aWord[MAX_WORD];								//メニュー
float g_fCnt;
float g_nCnt1;

//=======================================================================
//初期化処理
//=======================================================================
void InitWord(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//でアイスのポインタ
	int nCntWord;

	//デバイスの取得
	pDevice = GetDevice();

	//メニューの初期化
	for (nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		g_aWord[nCntWord].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWord[nCntWord].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWord[nCntWord].fWordWidth = 0;
		g_aWord[nCntWord].nType = 0;
		g_aWord[nCntWord].nCnt = 0;
		g_aWord[nCntWord].fWordHeight = 0;
		g_aWord[nCntWord].bUse = false;
	}
	g_fCnt = 0.001f;
	g_nCnt1 = 1;



	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//pause.png",
		&g_apTextureWord[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//word_ninjin.png",
		&g_apTextureWord[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//title_word.png",
		&g_apTextureWord[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//word_ninjin.png",
		&g_apTextureWord[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//pushEnter.png",
		&g_apTextureWord[4]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//timeUp.png",
		&g_apTextureWord[5]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_WORD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWord,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffWord->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
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
	g_pVtxBuffWord->Unlock();
}

//=======================================================================
//終了処理
//=======================================================================
void UninitWord(void)
{

	for (int nCntWord1 = 0; nCntWord1 < MAX_WORD; nCntWord1++)
	{
		g_aWord[nCntWord1].bUse = false;
	}

	int nCntWord;
	for (nCntWord = 0; nCntWord < WORD_TYPE; nCntWord++)
	{
		//テクスチャの破棄
		if (g_apTextureWord[nCntWord] != NULL)
		{
			g_apTextureWord[nCntWord]->Release();
			g_apTextureWord[nCntWord] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffWord != NULL)
	{
		g_pVtxBuffWord->Release();
		g_pVtxBuffWord = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateWord(void)
{
	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffWord->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		g_aWord[nCntWord].pos += g_aWord[nCntWord].move;
		if (g_aWord[nCntWord].nType == 1)
		{
			g_nCnt1++;
			g_aWord[nCntWord].fWordWidth += g_aWord[nCntWord].fWordWidth * g_fCnt;
			g_aWord[nCntWord].fWordHeight += g_aWord[nCntWord].fWordHeight * g_fCnt;
			if (g_nCnt1 >= 200)
			{
				g_fCnt = 0.0f;
			}
		}
		else if (g_aWord[nCntWord].nType == 2)
		{
			if (g_aWord[nCntWord].pos.y >= 200.0f)
			{
				g_aWord[nCntWord].move.y = 0.0f;
			}

			if (GetKeyboardPress(DIK_RIGHT) == true || GetKeyboardPress(DIK_D) == true)
			{
				g_aWord[nCntWord].move.x = 1.0f;
			}
			else if (GetKeyboardPress(DIK_LEFT) == true || GetKeyboardPress(DIK_A) == true)
			{
				g_aWord[nCntWord].move.x = -1.0f;
			}
			else if (GetKeyboardPress(DIK_RIGHT) == false && GetKeyboardPress(DIK_D) == false)
			{
				g_aWord[nCntWord].move.x = 0.0f;
			}
			else if (GetKeyboardPress(DIK_LEFT) == false && GetKeyboardPress(DIK_A) == false)
			{
				g_aWord[nCntWord].move.x = 0.0f;
			}

		}
		else if (g_aWord[nCntWord].nType == 4)
		{
			g_aWord[nCntWord].nCnt++;
			if (g_aWord[nCntWord].nCnt >= 100)
			{
				if (g_aWord[nCntWord].bUse == true)
				{
					g_aWord[nCntWord].bUse = false;
				}
				else if (g_aWord[nCntWord].bUse == false)
				{
					g_aWord[nCntWord].bUse = true;
				}
				g_aWord[nCntWord].nCnt = 0;
			}
		}


		pVtx[0].pos = D3DXVECTOR3(g_aWord[nCntWord].pos.x - g_aWord[nCntWord].fWordWidth / 2.0f, g_aWord[nCntWord].pos.y - g_aWord[nCntWord].fWordHeight / 2.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aWord[nCntWord].pos.x + g_aWord[nCntWord].fWordWidth / 2.0f, g_aWord[nCntWord].pos.y - g_aWord[nCntWord].fWordHeight / 2.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aWord[nCntWord].pos.x - g_aWord[nCntWord].fWordWidth / 2.0f, g_aWord[nCntWord].pos.y + g_aWord[nCntWord].fWordHeight / 2.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aWord[nCntWord].pos.x + g_aWord[nCntWord].fWordWidth / 2.0f, g_aWord[nCntWord].pos.y + g_aWord[nCntWord].fWordHeight / 2.0f, 0.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffWord->Unlock();
}

//=======================================================================
//描画処理
//=======================================================================
void DrawWord(void)
{
	int nCntWord;

	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffWord, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定

	for (nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (g_aWord[nCntWord].bUse == true)
		{
			//テクスチャ
			pDevice->SetTexture(0, g_apTextureWord[g_aWord[nCntWord].nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntWord * 4,					//描画を開始する頂点のインデックス
				2);					//描画するプリミティブ数
		}
	}
}

//=======================================================================
//設定処理
//=======================================================================
void SetWord(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 move, float fWordWidth, float fWordHeight)
{
	int nCntWord;
	for (nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (g_aWord[nCntWord].bUse == false)
		{
			g_aWord[nCntWord].pos = pos;
			g_aWord[nCntWord].fWordWidth = fWordWidth;
			g_aWord[nCntWord].fWordHeight = fWordHeight;
			//頂点座標の設定

			VERTEX_2D *pVtx;		//頂点情報へのポインタ
									//頂点バッファをロックし、頂点データのポインタを取得
			g_pVtxBuffWord->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntWord * 4);


			pVtx[0].pos = D3DXVECTOR3(g_aWord[nCntWord].pos.x - g_aWord[nCntWord].fWordWidth / 2.0f, g_aWord[nCntWord].pos.y - g_aWord[nCntWord].fWordHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aWord[nCntWord].pos.x + g_aWord[nCntWord].fWordWidth / 2.0f, g_aWord[nCntWord].pos.y - g_aWord[nCntWord].fWordHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aWord[nCntWord].pos.x - g_aWord[nCntWord].fWordWidth / 2.0f, g_aWord[nCntWord].pos.y + g_aWord[nCntWord].fWordHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aWord[nCntWord].pos.x + g_aWord[nCntWord].fWordWidth / 2.0f, g_aWord[nCntWord].pos.y + g_aWord[nCntWord].fWordHeight / 2.0f, 0.0f);

			//頂点バッファをアンロックする
			g_pVtxBuffWord->Unlock();

			g_aWord[nCntWord].nType = nType;
			g_aWord[nCntWord].move = move;
			g_aWord[nCntWord].bUse = true;
			break;
		}
	}
}

//=======================================================================
//取得処理
//=======================================================================
Word *GetWord(void)
{
	return &g_aWord[0];
}
