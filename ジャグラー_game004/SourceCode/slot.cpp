//=======================================================================
//スロット部分に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#include "main.h"
#include "slot.h"
#include "input.h"
#include "score.h"
#include "databox.h"
#include "sound.h"


//=======================================================================
//グローバル変数宣言
//=======================================================================

LPDIRECT3DTEXTURE9 g_pTextureSlot = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSlot = NULL;		//頂点バッファへのポインタ
SLOT g_aSlot[MAX_SLOT];								//構造体
float g_fAcceleration;								//加速度
int g_nNumStopSlot;									//ストップさせたスロットの数
int g_nSlotCounter;									//スロットがそろった回数
int g_nScoreCounter;								//スコアを増やしている時間
bool g_bAcceleration;								//加速している状態かそうでないか
bool g_bScoreUp;									//スコアが上がる
bool g_bScoreUpStop;								//スコアを挙げるために必要
bool g_bSpin;										//回っているかどうか

//=======================================================================
//初期化処理
//=======================================================================
void InitSlot(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//初期化
	g_aSlot[0].firstmove = D3DXVECTOR3(SLOT_SPEED0, 0.0f, 0.0f);
	g_aSlot[1].firstmove = D3DXVECTOR3(SLOT_SPEED1, 0.0f, 0.0f);
	g_aSlot[2].firstmove = D3DXVECTOR3(SLOT_SPEED2, 0.0f, 0.0f);
	g_aSlot[3].firstmove = D3DXVECTOR3(SLOT_SPEED3, 0.0f, 0.0f);
	g_nNumStopSlot = 4;
	g_nScoreCounter = 0;
	g_nSlotCounter = 0;
	g_bAcceleration = false;
	g_bScoreUp = false;
	g_bScoreUpStop = false;
	g_bSpin = false;
	g_fAcceleration = SLOT_ACCEL;

	for (int nCntSlot = 0; nCntSlot < MAX_SLOT; nCntSlot++)
	{
		g_aSlot[nCntSlot].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSlot[nCntSlot].move = g_aSlot[nCntSlot].firstmove;
		g_aSlot[nCntSlot].fWidth = 0.0f;
		g_aSlot[nCntSlot].fHeight = 0.0f;
		g_aSlot[nCntSlot].fTexU = 0.0f;
		g_aSlot[nCntSlot].fStopTexU = 0.0f;
		g_aSlot[nCntSlot].bUse = false;
		g_aSlot[nCntSlot].bSpin = true;
		g_aSlot[nCntSlot].bStop = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//Round2.png",
		&g_pTextureSlot);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SLOT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSlot,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffSlot->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntSlot = 0; nCntSlot < MAX_SLOT; nCntSlot++)
	{
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

		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f / MAX_SLOT * nCntSlot);
		pVtx[1].tex = D3DXVECTOR2(1.0f / MAX_SLOT, 1.0f / MAX_SLOT * nCntSlot);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / MAX_SLOT * (nCntSlot + 1));
		pVtx[3].tex = D3DXVECTOR2(1.0f / MAX_SLOT, 1.0f / MAX_SLOT * (nCntSlot + 1));

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffSlot->Unlock();
}


//=======================================================================
//終了処理
//=======================================================================
void UninitSlot(void)
{
	//テクスチャの破棄
	if (g_pTextureSlot != NULL)
	{
		g_pTextureSlot->Release();
		g_pTextureSlot = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffSlot != NULL)
	{
		g_pVtxBuffSlot->Release();
		g_pVtxBuffSlot = NULL;
	}
}


//=======================================================================
//更新処理
//=======================================================================
void UpdateSlot(void)
{
	Data *pData;
	pData = GetData();
	for (int nCntSlot = 0; nCntSlot < MAX_SLOT; nCntSlot++)
	{
		if (g_aSlot[nCntSlot].bUse == true)
		{
			if (g_bSpin == true)
			{
				g_aSlot[nCntSlot].fTexU += g_aSlot[nCntSlot].move.x;
			}

			if (g_bAcceleration == true)
			{
				g_aSlot[nCntSlot].move.x *= 0.95f;
				if (g_aSlot[nCntSlot].move.x > 0.0f && g_aSlot[nCntSlot].move.x <= g_aSlot[nCntSlot].firstmove.x)
				{
					g_aSlot[nCntSlot].move.x = g_aSlot[nCntSlot].firstmove.x;
				}
				else if (g_aSlot[nCntSlot].move.x < 0.0f && g_aSlot[nCntSlot].move.x >= g_aSlot[nCntSlot].firstmove.x)
				{
					g_aSlot[nCntSlot].move.x = g_aSlot[nCntSlot].firstmove.x;
				}
			}

			if (g_aSlot[nCntSlot].move.x == g_aSlot[nCntSlot].firstmove.x)
			{
				g_bAcceleration = false;
			}


			VERTEX_2D *pVtx;		//頂点情報へのポインタ
			//頂点バッファをロックし、頂点データのポインタを取得
			g_pVtxBuffSlot->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntSlot * 4);

			pVtx[0].tex = D3DXVECTOR2(g_aSlot[nCntSlot].fTexU, 1.0f / MAX_SLOT * nCntSlot);
			pVtx[1].tex = D3DXVECTOR2(g_aSlot[nCntSlot].fTexU + 1.0f / MAX_SLOT, 1.0f / MAX_SLOT * nCntSlot);
			pVtx[2].tex = D3DXVECTOR2(g_aSlot[nCntSlot].fTexU, 1.0f / MAX_SLOT * (nCntSlot + 1));
			pVtx[3].tex = D3DXVECTOR2(g_aSlot[nCntSlot].fTexU + 1.0f / MAX_SLOT, 1.0f / MAX_SLOT * (nCntSlot + 1));

			//頂点バッファをアンロックする
			g_pVtxBuffSlot->Unlock();
		}
	}

	//スロットを止める
	if (g_nNumStopSlot < MAX_SLOT)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetKeyboardTrigger(DIK_SPACE) == true)
		{
			//PlaySound(SOUND_LABEL_ENTER_SE);


			if (g_aSlot[g_nNumStopSlot].move.x > 0.0f)
			{
				if (g_aSlot[g_nNumStopSlot].fTexU > 0.0f && g_aSlot[g_nNumStopSlot].fTexU <= 0.25f)
				{
					g_aSlot[g_nNumStopSlot].fStopTexU = 0.25f;
				}
				else if (g_aSlot[g_nNumStopSlot].fTexU > 0.25f && g_aSlot[g_nNumStopSlot].fTexU <= 0.5f)
				{
					g_aSlot[g_nNumStopSlot].fStopTexU = 0.5f;
				}
				else if (g_aSlot[g_nNumStopSlot].fTexU > 0.5f && g_aSlot[g_nNumStopSlot].fTexU <= 0.75f)
				{
					g_aSlot[g_nNumStopSlot].fStopTexU = 0.75f;
				}
				else if (g_aSlot[g_nNumStopSlot].fTexU > 0.75f && g_aSlot[g_nNumStopSlot].fTexU <= 1.0f)
				{
					g_aSlot[g_nNumStopSlot].fStopTexU = 1.0f;
				}
			}
			else if (g_aSlot[g_nNumStopSlot].move.x < 0.0f)
			{
				if (g_aSlot[g_nNumStopSlot].fTexU >= 0.0f && g_aSlot[g_nNumStopSlot].fTexU < 0.25f)
				{
					g_aSlot[g_nNumStopSlot].fStopTexU = 0.0f;
				}
				else if (g_aSlot[g_nNumStopSlot].fTexU >= 0.25f && g_aSlot[g_nNumStopSlot].fTexU < 0.5f)
				{
					g_aSlot[g_nNumStopSlot].fStopTexU = 0.25f;
				}
				else if (g_aSlot[g_nNumStopSlot].fTexU >= 0.5f && g_aSlot[g_nNumStopSlot].fTexU < 0.75f)
				{
					g_aSlot[g_nNumStopSlot].fStopTexU = 0.5f;
				}
				else if (g_aSlot[g_nNumStopSlot].fTexU >= 0.75f && g_aSlot[g_nNumStopSlot].fTexU < 1.0f)
				{
					g_aSlot[g_nNumStopSlot].fStopTexU = 0.75f;
				}
			}
			
			g_aSlot[g_nNumStopSlot].bStop = true;

			g_nNumStopSlot++;
			
		}
	}

	for (int nCntSlot = 0; nCntSlot < MAX_SLOT; nCntSlot++)
	{
		if (g_aSlot[nCntSlot].bStop == true)
		{
			if (g_aSlot[nCntSlot].move.x > 0.0f && g_aSlot[nCntSlot].fTexU >= g_aSlot[nCntSlot].fStopTexU)
			{
				g_aSlot[nCntSlot].fTexU = g_aSlot[nCntSlot].fStopTexU;
				if(g_aSlot[nCntSlot].fTexU == 1.0f)
				{
					g_aSlot[nCntSlot].fTexU = 0.0f;
				}
				g_aSlot[nCntSlot].move.x = 0.0f;
				g_aSlot[nCntSlot].bStop = false;
			}
			else if (g_aSlot[nCntSlot].move.x < 0.0f && g_aSlot[nCntSlot].fTexU <= g_aSlot[nCntSlot].fStopTexU)
			{
				g_aSlot[nCntSlot].fTexU = g_aSlot[nCntSlot].fStopTexU;
				g_aSlot[nCntSlot].move.x = 0.0f;
				g_aSlot[nCntSlot].bStop = false;
			}
		}
	}

	//揃ったら
	if (g_nNumStopSlot >= MAX_SLOT && g_aSlot[0].bStop == false && g_aSlot[1].bStop == false && g_aSlot[2].bStop == false && g_aSlot[3].bStop == false)
	{
		StopSound(SOUND_LABEL_DRUM_SE);
		g_bSpin = false;
		if (g_aSlot[0].fTexU == g_aSlot[1].fTexU && g_aSlot[1].fTexU == g_aSlot[2].fTexU &&g_aSlot[2].fTexU == g_aSlot[3].fTexU && g_bScoreUp == true)
		{
			g_bScoreUpStop = true;
		}
	}

	if (g_bScoreUpStop == true)
	{
		g_nScoreCounter++;
		SetScore(10);
		if (g_nScoreCounter >= 100)
		{
			g_nScoreCounter = 0;
			g_bScoreUp = false;
			g_bScoreUpStop = false;

			pData->bOK = true;
		}
	}

	for (int nCntSlot = 0; nCntSlot < MAX_SLOT; nCntSlot++)
	{
		if (g_aSlot[nCntSlot].move.x > 0.0f && g_aSlot[nCntSlot].fTexU >= 1.0f)
		{
			g_aSlot[nCntSlot].fTexU = 0.0f;
		}
		else if (g_aSlot[nCntSlot].move.x < 0.0f && g_aSlot[nCntSlot].fTexU <= 0.0f)
		{
			g_aSlot[nCntSlot].fTexU = 1.0f;
		}
	}


	//スロットを回す
	if (g_nNumStopSlot >= MAX_SLOT && g_aSlot[0].bStop == false && g_aSlot[1].bStop == false && g_aSlot[2].bStop == false && g_aSlot[3].bStop == false)
	{
		if (g_aSlot[0].fTexU == g_aSlot[1].fTexU && g_aSlot[1].fTexU == g_aSlot[2].fTexU &&g_aSlot[2].fTexU == g_aSlot[3].fTexU && g_bScoreUpStop == false)
		{
			if (GetKeyboardTrigger(DIK_SPACE) == true || GetKeyboardTrigger(DIK_RETURN) == true)
			{
				PlaySound(SOUND_LABEL_SPACE_SE);
				PlaySound(SOUND_LABEL_ROLL_SE);
				if (g_aSlot[0].fTexU == g_aSlot[1].fTexU && g_aSlot[1].fTexU == g_aSlot[2].fTexU &&g_aSlot[2].fTexU == g_aSlot[3].fTexU)
				{
					g_aSlot[0].firstmove.x *= g_fAcceleration;
					g_aSlot[1].firstmove.x *= g_fAcceleration;
					g_aSlot[2].firstmove.x *= g_fAcceleration;
					g_aSlot[3].firstmove.x *= g_fAcceleration;
				}
				g_nNumStopSlot = 0;
				g_aSlot[0].move.x = g_aSlot[0].firstmove.x * 20.0f;
				g_aSlot[1].move.x = g_aSlot[1].firstmove.x * 20.0f;
				g_aSlot[2].move.x = g_aSlot[2].firstmove.x * 20.0f;
				g_aSlot[3].move.x = g_aSlot[3].firstmove.x * 20.0f;
				g_bAcceleration = true;
				//g_bScoreUpStop = false;
				g_bSpin = true;
				g_bScoreUp = true;
			}
		}
		else if(g_aSlot[0].fTexU != g_aSlot[1].fTexU || g_aSlot[1].fTexU != g_aSlot[2].fTexU || g_aSlot[2].fTexU != g_aSlot[3].fTexU)
		{
			if (GetKeyboardTrigger(DIK_SPACE) == true || GetKeyboardTrigger(DIK_RETURN) == true)
			{
				PlaySound(SOUND_LABEL_SPACE_SE);
				PlaySound(SOUND_LABEL_ROLL_SE);


				if (g_aSlot[0].fTexU == g_aSlot[1].fTexU && g_aSlot[1].fTexU == g_aSlot[2].fTexU &&g_aSlot[2].fTexU == g_aSlot[3].fTexU)
				{
					g_aSlot[0].firstmove.x *= g_fAcceleration;
					g_aSlot[1].firstmove.x *= g_fAcceleration;
					g_aSlot[2].firstmove.x *= g_fAcceleration;
					g_aSlot[3].firstmove.x *= g_fAcceleration;
				}
				g_nNumStopSlot = 0;
				g_aSlot[0].move.x = g_aSlot[0].firstmove.x * 20.0f;
				g_aSlot[1].move.x = g_aSlot[1].firstmove.x * 20.0f;
				g_aSlot[2].move.x = g_aSlot[2].firstmove.x * 20.0f;
				g_aSlot[3].move.x = g_aSlot[3].firstmove.x * 20.0f;
				g_bAcceleration = true;
				//g_bScoreUpStop = false;
				g_bSpin = true;
				g_bScoreUp = true;
			}
		}
		
	}
}


//=======================================================================
//描画処理
//=======================================================================
void DrawSlot(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSlot, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定

	for (int nCntSlot = 0; nCntSlot < MAX_SLOT; nCntSlot++)
	{
		if (g_aSlot[nCntSlot].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureSlot);	//テクスチャの設定
													//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntSlot * 4,					//開始する頂点のインデックス
				2);					//描画するプリミティブ数
		}
	}
}

//=======================================================================
//設定処理
//=======================================================================
void SetSlot(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	for (int nCntSlot = 0; nCntSlot < MAX_SLOT; nCntSlot++)
	{
		if (g_aSlot[nCntSlot].bUse == false)
		{
			g_aSlot[nCntSlot].pos = pos;
			g_aSlot[nCntSlot].fWidth = fWidth;
			g_aSlot[nCntSlot].fHeight = fHeight;
			g_aSlot[nCntSlot].bUse = true;

			//頂点座標の設定

			VERTEX_2D *pVtx;		//頂点情報へのポインタ
									//頂点バッファをロックし、頂点データのポインタを取得
			g_pVtxBuffSlot->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntSlot * 4);

			pVtx[0].pos = D3DXVECTOR3(g_aSlot[nCntSlot].pos.x - g_aSlot[nCntSlot].fWidth / 2.0f, g_aSlot[nCntSlot].pos.y - g_aSlot[nCntSlot].fHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aSlot[nCntSlot].pos.x + g_aSlot[nCntSlot].fWidth / 2.0f, g_aSlot[nCntSlot].pos.y - g_aSlot[nCntSlot].fHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aSlot[nCntSlot].pos.x - g_aSlot[nCntSlot].fWidth / 2.0f, g_aSlot[nCntSlot].pos.y + g_aSlot[nCntSlot].fHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aSlot[nCntSlot].pos.x + g_aSlot[nCntSlot].fWidth / 2.0f, g_aSlot[nCntSlot].pos.y + g_aSlot[nCntSlot].fHeight / 2.0f, 0.0f);

			//頂点バッファをアンロックする
			g_pVtxBuffSlot->Unlock();

			break;
		}
	}
}

//=======================================================================
//取得処理
//=======================================================================
SLOT *GetSlot(void)
{
	return &g_aSlot[0];
}