//=======================================================================
//ランキングに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
#include "main.h"
#include "score.h"
#include "runking.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureRunking = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRunking = NULL;		//頂点バッファへのポインタ
Runking g_aRunkingPolygon[MAX_RUNKING][MAX_SCORE_POLYGON];				//スコア
int g_aScore[MAX_RUNKING];
bool g_bData;
int g_nCol;
int g_nData;
int g_nCntFirst;
int g_newRunking;
bool g_bData2;
bool g_bCnt;

//=======================================================================
//初期化処理
//=======================================================================
void InitRunking(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//でアイスのポインタ
	int nCntScorePolygon;

	//デバイスの取得
	pDevice = GetDevice();

	//スコアの位置の初期化
	for (int nCntRunking = 0; nCntRunking < MAX_RUNKING - 1; nCntRunking++)
	{
		for (nCntScorePolygon = 0; nCntScorePolygon < MAX_SCORE_POLYGON; nCntScorePolygon++)
		{
			g_aRunkingPolygon[nCntRunking][nCntScorePolygon].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - (RUNKING_POLYGON_WIDTH * 3.5f) + (RUNKING_POLYGON_WIDTH * nCntScorePolygon) ,SCREEN_HEIGHT / 6.0f + (SCREEN_HEIGHT / 6.0f * nCntRunking), 0.0f);
			g_aRunkingPolygon[nCntRunking][nCntScorePolygon].bUse = true;
		}
		g_aScore[nCntRunking] = 0;
	}
	g_aScore[MAX_RUNKING - 1] = GetScore();
	g_bData = false;
	g_bData2 = false;
	g_bCnt = false;
	g_nCol = 0;
	g_newRunking = 0;
	g_nCntFirst = 0;
	g_nData = GetScore();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//score.png",
		&g_pTextureRunking);



	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE_POLYGON * MAX_RUNKING,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRunking,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffRunking->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntRunking = 0; nCntRunking < MAX_RUNKING - 1; nCntRunking++)
	{
		for (int nCntScorePolygon = 0; nCntScorePolygon < MAX_SCORE_POLYGON; nCntScorePolygon++)
		{
			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aRunkingPolygon[nCntRunking][nCntScorePolygon].pos.x - RUNKING_POLYGON_WIDTH / 2.0f, g_aRunkingPolygon[nCntRunking][nCntScorePolygon].pos.y - RUNKING_POLYGON_HEIGHT / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aRunkingPolygon[nCntRunking][nCntScorePolygon].pos.x + RUNKING_POLYGON_WIDTH / 2.0f, g_aRunkingPolygon[nCntRunking][nCntScorePolygon].pos.y - RUNKING_POLYGON_HEIGHT / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aRunkingPolygon[nCntRunking][nCntScorePolygon].pos.x - RUNKING_POLYGON_WIDTH / 2.0f, g_aRunkingPolygon[nCntRunking][nCntScorePolygon].pos.y + RUNKING_POLYGON_HEIGHT / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aRunkingPolygon[nCntRunking][nCntScorePolygon].pos.x + RUNKING_POLYGON_WIDTH / 2.0f, g_aRunkingPolygon[nCntRunking][nCntScorePolygon].pos.y + RUNKING_POLYGON_HEIGHT / 2.0f, 0.0f);

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
	}


	//頂点バッファをアンロックする
	g_pVtxBuffRunking->Unlock();

	
	int nCntRunking;
	//ロード処理
	FILE *pFile;

	pFile = fopen("score.txt", "r");
	if (pFile != NULL)
	{
		for (nCntRunking = 0; nCntRunking < MAX_RUNKING - 1; nCntRunking++)
		{
 			fscanf(pFile, "%d", &g_aScore[nCntRunking]);
		}
		fclose(pFile);
	}
	else
	{
		printf("ファイルが開けませんでした\n");
	}

}

//=======================================================================
//終了処理
//=======================================================================
void UninitRunking(void)
{
	for (int nCntRunking = 0; nCntRunking < MAX_RUNKING - 1; nCntRunking++)
	{
		for (int nCntScorePolygon = 0; nCntScorePolygon < MAX_SCORE_POLYGON; nCntScorePolygon++)
		{
			g_aRunkingPolygon[nCntRunking][nCntScorePolygon].bUse = false;
		}
	}


	//テクスチャの破棄
	if (g_pTextureRunking != NULL)
	{
		g_pTextureRunking->Release();
		g_pTextureRunking = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRunking != NULL)
	{
		g_pVtxBuffRunking->Release();
		g_pVtxBuffRunking = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateRunking(void)
{
	//スコアの取得
	int nCntRunking;
	
	//=======================================================================
	//ソート処理
	//=======================================================================

	int nCnt, nCnt2, nSubData = 0;


	for (nCnt = 0; nCnt < MAX_RUNKING -1; nCnt++)
	{
		for (nCnt2 = 0; nCnt2 < MAX_RUNKING; nCnt2++)
		{
			if (g_aScore[nCnt] < g_aScore[nCnt + 1])
			{
				nSubData = g_aScore[nCnt];
				g_aScore[nCnt] = g_aScore[nCnt + 1];
				g_aScore[nCnt + 1] = nSubData;
			}			
		}
	}


	//=======================================================================
	//セーブ処理
	//=======================================================================
	FILE *pFile;
	pFile = fopen("score.txt", "w");
	if (pFile != NULL)
	{
		for (nCntRunking = 0; nCntRunking < MAX_RUNKING; nCntRunking++)
		{
			fprintf(pFile, "%d\n", g_aScore[nCntRunking]);
		}
		fclose(pFile);
	}
	else
	{
		printf("ファイルが開けませんでした");
	}

	VERTEX_2D *pVtx;		//頂点情報へのポインタ
							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffRunking->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aScore[0] >= g_aScore[1] && g_aScore[1] >= g_aScore[2] &&
		g_aScore[2] >= g_aScore[3] && g_aScore[3] >= g_aScore[4])
	{
		g_bCnt = true;
	}


	for (nCntRunking = 0; nCntRunking < MAX_RUNKING - 1; nCntRunking++)
	{
		for (int nCntScorePolygon = 0; nCntScorePolygon < MAX_SCORE_POLYGON; nCntScorePolygon++)
		{
			if (g_aRunkingPolygon[nCntRunking][nCntScorePolygon].bUse == true)
			{
				if (nCntScorePolygon == 0)
				{
					pVtx[0].tex = D3DXVECTOR2(g_aScore[nCntRunking] / (int)powf(10, 7)*0.1f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(g_aScore[nCntRunking] / (int)powf(10, 7)*0.1f + 0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(g_aScore[nCntRunking] / (int)powf(10, 7)*0.1f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(g_aScore[nCntRunking] / (int)powf(10, 7)*0.1f + 0.1f, 1.0f);
				}
				else if (nCntScorePolygon == 7)
				{
					pVtx[0].tex = D3DXVECTOR2(g_aScore[nCntRunking] % 10 * 0.1f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(g_aScore[nCntRunking] % 10 * 0.1f + 0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(g_aScore[nCntRunking] % 10 * 0.1f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(g_aScore[nCntRunking] % 10 * 0.1f + 0.1f, 1.0f);
				}
				else
				{
					pVtx[0].tex = D3DXVECTOR2(g_aScore[nCntRunking] % (int)powf(10, MAX_SCORE_POLYGON - nCntScorePolygon) / (int)powf(10, 7 - nCntScorePolygon) *0.1f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(g_aScore[nCntRunking] % (int)powf(10, MAX_SCORE_POLYGON - nCntScorePolygon) / (int)powf(10, 7 - nCntScorePolygon)*0.1f + 0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(g_aScore[nCntRunking] % (int)powf(10, MAX_SCORE_POLYGON - nCntScorePolygon) / (int)powf(10, 7 - nCntScorePolygon)*0.1f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(g_aScore[nCntRunking] % (int)powf(10, MAX_SCORE_POLYGON - nCntScorePolygon) / (int)powf(10, 7 - nCntScorePolygon)*0.1f + 0.1f, 1.0f);
				}
			}

			if (g_bCnt == true)
			{
				if (g_aScore[nCntRunking] == g_nData && g_bData2 == false)
				{
					g_bData2 = true;
					g_newRunking = nCntRunking;
				}

				g_nCol++;
				if (g_nCol >= 800)
				{
					if (g_aRunkingPolygon[g_newRunking][nCntScorePolygon].bUse == false)
					{
						for (int nCnt3 = 0; nCnt3 < MAX_SCORE_POLYGON; nCnt3++)
						{
							g_aRunkingPolygon[g_newRunking][nCnt3].bUse = true;
						}
					}
					else if (g_aRunkingPolygon[g_newRunking][nCntScorePolygon].bUse == true)
					{
						for (int nCnt3 = 0; nCnt3 < MAX_SCORE_POLYGON; nCnt3++)
						{
							g_aRunkingPolygon[g_newRunking][nCnt3].bUse = false;
						}
					}
					g_nCol = 0;
				}
			}

			pVtx += 4;
		}
	}


	//頂点バッファをアンロックする
	g_pVtxBuffRunking->Unlock();



}

//=======================================================================
//描画処理
//=======================================================================
void DrawRunking(void)
{
	int nCntRunking;

	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRunking, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定

	int nCnt=0;
	
	for (nCntRunking = 0; nCntRunking < MAX_RUNKING - 1; nCntRunking++)
	{
		for (int nCntScorePolygon = 0; nCntScorePolygon < MAX_SCORE_POLYGON; nCntScorePolygon++)
		{
			if (g_aRunkingPolygon[nCntRunking][nCntScorePolygon].bUse == true)
			{
				//テクスチャ
				pDevice->SetTexture(0, g_pTextureRunking);

				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
					nCnt * 4,					//描画を開始する頂点のインデックス
					2);					//描画するプリミティブ数
			}
			nCnt++;
		}
	}
	
}

//=======================================================================
//設定処理
//=======================================================================
void SetRunking(int nRunking)
{
	//g_aRunking[0][0] += nRunking;
}

