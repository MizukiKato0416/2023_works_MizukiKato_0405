//=======================================================================
//ハイスコアに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
#include "main.h"
#include "HiScore.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureHiScore = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHiScore = NULL;		//頂点バッファへのポインタ
HiScore g_aHiScorePolygon[MAX_HI_SCORE_POLYGON];							//スコア
int g_aHiScore[2];										//0が新しいスコア

//=======================================================================
//初期化処理
//=======================================================================
void InitHiScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//でアイスのポインタ
	int nCntHiScore;

	//デバイスの取得
	pDevice = GetDevice();

	//スコアの位置の初期化
	for (nCntHiScore = 0; nCntHiScore < MAX_HI_SCORE_POLYGON; nCntHiScore++)
	{
		g_aHiScorePolygon[nCntHiScore].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore) + (HI_SCORE_POLYGON_WIDTH / 2)), HI_SCORE_POLYGON_POS_HEIGHT, 0.0f);
	}


	g_aHiScore[0] = 0;
	g_aHiScore[1] = 0;



	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//score.png",
		&g_pTextureHiScore);



	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_HI_SCORE_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHiScore,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffHiScore->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntHiScore = 0; nCntHiScore < MAX_HI_SCORE_POLYGON; nCntHiScore++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore)), HI_SCORE_POLYGON_POS_HEIGHT - HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore - 1)), HI_SCORE_POLYGON_POS_HEIGHT - HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore)), HI_SCORE_POLYGON_POS_HEIGHT + HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore - 1)), HI_SCORE_POLYGON_POS_HEIGHT + HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);

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
	g_pVtxBuffHiScore->Unlock();



	//ロード処理
	FILE *pFile;

	pFile = fopen("score.txt", "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &g_aHiScore[1]);
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
void UninitHiScore(void)
{
	//テクスチャの破棄
	if (g_pTextureHiScore != NULL)
	{
		g_pTextureHiScore->Release();
		g_pTextureHiScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffHiScore != NULL)
	{
		g_pVtxBuffHiScore->Release();
		g_pVtxBuffHiScore = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateHiScore(void)
{
	int nCntHiScore;
	VERTEX_2D *pVtx;		//頂点情報へのポインタ
							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffHiScore->Lock(0, 0, (void**)&pVtx, 0);

	
	if (g_aHiScore[0] >= g_aHiScore[1])
	{
		//セーブ処理
		FILE *pFile;
		pFile = fopen("score.txt", "w");
		if (pFile != NULL)
		{
			fprintf(pFile, "%d\n", g_aHiScore[0]);
			fclose(pFile);
		}
		else
		{
			printf("ファイルが開けませんでした");
		}

		for (nCntHiScore = 0; nCntHiScore < MAX_HI_SCORE_POLYGON; nCntHiScore++)
		{
			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore)), HI_SCORE_POLYGON_POS_HEIGHT - HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore - 1)), HI_SCORE_POLYGON_POS_HEIGHT - HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore)), HI_SCORE_POLYGON_POS_HEIGHT + HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore - 1)), HI_SCORE_POLYGON_POS_HEIGHT + HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);
			
			if (nCntHiScore == 0)
			{
				pVtx[0].tex = D3DXVECTOR2(g_aHiScore[0] / (int)powf(10, 7)*0.1f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aHiScore[0] / (int)powf(10, 7)*0.1f + 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aHiScore[0] / (int)powf(10, 7)*0.1f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aHiScore[0] / (int)powf(10, 7)*0.1f + 0.1f, 1.0f);
			}
			else if (nCntHiScore == 7)
			{
				pVtx[0].tex = D3DXVECTOR2(g_aHiScore[0] % 10 * 0.1f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aHiScore[0] % 10 * 0.1f + 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aHiScore[0] % 10 * 0.1f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aHiScore[0] % 10 * 0.1f + 0.1f, 1.0f);
			}
			else
			{
				pVtx[0].tex = D3DXVECTOR2(g_aHiScore[0] % (int)powf(10, MAX_HI_SCORE_POLYGON - nCntHiScore) / (int)powf(10, 7 - nCntHiScore) *0.1f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aHiScore[0] % (int)powf(10, MAX_HI_SCORE_POLYGON - nCntHiScore) / (int)powf(10, 7 - nCntHiScore)*0.1f + 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aHiScore[0] % (int)powf(10, MAX_HI_SCORE_POLYGON - nCntHiScore) / (int)powf(10, 7 - nCntHiScore)*0.1f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aHiScore[0] % (int)powf(10, MAX_HI_SCORE_POLYGON - nCntHiScore) / (int)powf(10, 7 - nCntHiScore)*0.1f + 0.1f, 1.0f);
			}

			pVtx += 4;
		}
	}
	else if (g_aHiScore[0] <= g_aHiScore[1])
	{
		for (nCntHiScore = 0; nCntHiScore < MAX_HI_SCORE_POLYGON; nCntHiScore++)
		{

			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore)), HI_SCORE_POLYGON_POS_HEIGHT - HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore - 1)), HI_SCORE_POLYGON_POS_HEIGHT - HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore)), HI_SCORE_POLYGON_POS_HEIGHT + HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore - 1)), HI_SCORE_POLYGON_POS_HEIGHT + HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);

			if (nCntHiScore == 0)
			{
				pVtx[0].tex = D3DXVECTOR2(g_aHiScore[1] / (int)powf(10, 7)*0.1f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aHiScore[1] / (int)powf(10, 7)*0.1f + 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aHiScore[1] / (int)powf(10, 7)*0.1f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aHiScore[1] / (int)powf(10, 7)*0.1f + 0.1f, 1.0f);
			}
			else if (nCntHiScore == 7)
			{
				pVtx[0].tex = D3DXVECTOR2(g_aHiScore[1] % 10 * 0.1f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aHiScore[1] % 10 * 0.1f + 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aHiScore[1] % 10 * 0.1f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aHiScore[1] % 10 * 0.1f + 0.1f, 1.0f);
			}
			else
			{
				pVtx[0].tex = D3DXVECTOR2(g_aHiScore[1] % (int)powf(10, MAX_HI_SCORE_POLYGON - nCntHiScore) / (int)powf(10, 7 - nCntHiScore) *0.1f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aHiScore[1] % (int)powf(10, MAX_HI_SCORE_POLYGON - nCntHiScore) / (int)powf(10, 7 - nCntHiScore)*0.1f + 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aHiScore[1] % (int)powf(10, MAX_HI_SCORE_POLYGON - nCntHiScore) / (int)powf(10, 7 - nCntHiScore)*0.1f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aHiScore[1] % (int)powf(10, MAX_HI_SCORE_POLYGON - nCntHiScore) / (int)powf(10, 7 - nCntHiScore)*0.1f + 0.1f, 1.0f);
			}

			pVtx += 4;
		}
	}
	


	//頂点バッファをアンロックする
	g_pVtxBuffHiScore->Unlock();


	
	
}

//=======================================================================
//描画処理
//=======================================================================
void DrawHiScore(void)
{
	int nCntHiScore;

	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffHiScore, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定

	for (nCntHiScore = 0; nCntHiScore < MAX_HI_SCORE_POLYGON; nCntHiScore++)
	{
		//テクスチャ
		pDevice->SetTexture(0, g_pTextureHiScore);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
			nCntHiScore * 4,					//描画を開始する頂点のインデックス
			2);					//描画するプリミティブ数
	}

}

//=======================================================================
//設定処理
//=======================================================================
void SetHiScore(int nHiScore)
{
	g_aHiScore[0] = nHiScore;
}
