//================================================
//ランキング処理
//Authore:加藤瑞葵
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "renderer.h"
#include "score.h"
#include "manager.h"
#include "ranking.h"
#include "scene.h"
#include "play_data.h"
#include "number.h"
#include "result.h"

//================================================
//静的メンバ変数宣言
//================================================
CScore *CRanking::m_pScore[MAX_RANKING] = {};

//================================================
//デフォルトコンストラクタ
//================================================
CRanking::CRanking()
{
	for (int nCntRanking = 0; nCntRanking < MAX_SCORE_DATA; nCntRanking++)
	{
		m_nScore[nCntRanking] = 0;
	}
	m_nNowScore = 0;
	m_col.r = 0.0f;
	m_col.g = 0.0f;
	m_col.b = 0.0f;
	m_col.a = 0.0f;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CRanking::~CRanking()
{

}

//================================================
//初期化処理
//================================================
HRESULT CRanking::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//スコアの生成
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		m_pScore[nCntRanking] = CScore::Create(D3DXVECTOR3((pos.x), (float)(SCREEN_HEIGHT / (MAX_RANKING + 1)) * nCntRanking + (float)(SCREEN_HEIGHT / (MAX_RANKING + 1)), 0.0f),
												size);
	}

	//ロード処理
	FILE *pFile;
	pFile = fopen("data/ranking.txt", "r");
	if (pFile != NULL)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			fscanf(pFile, "%d", &m_nScore[nCntRanking]);
		}
	}
	else
	{
		printf("ファイルが開けませんでした\n");
	}
	fclose(pFile);

	//プレイデータの取得
	CPlayData *pPlayData = NULL;
	pPlayData = CManager::GetPlayData();

	//プレイデータに保存してある今回のスコアを変数に保存
	m_nScore[MAX_SCORE_DATA - 1] = pPlayData->GetScore();
	m_nNowScore = pPlayData->GetScore();

	//ソート
	for (int nCntRanking = 0; nCntRanking < MAX_SCORE_DATA; nCntRanking++)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_SCORE_DATA - 1; nCntRanking++)
		{
			if (m_nScore[nCntRanking] < m_nScore[nCntRanking + 1])
			{
				int nScore = m_nScore[nCntRanking];
				m_nScore[nCntRanking] = m_nScore[nCntRanking + 1];
				m_nScore[nCntRanking + 1] = nScore;
			}
		}
	}

	//スコアの設定
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		m_pScore[nCntRanking]->SetScore(m_nScore[nCntRanking]);
	}

	//セーブ処理
	pFile = fopen("data/ranking.txt", "w");
	if (pFile != NULL)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			fprintf(pFile, "%d\n", m_pScore[nCntRanking]->GetScore());
		}
	}
	else
	{
		printf("ファイルが開けませんでした\n");
	}
	fclose(pFile);

	//カラーの設定
	m_col.r = 255.0f;
	m_col.g = 0.0f;
	m_col.b = 0.0f;
	m_col.a = 255.0f;

	return S_OK;
}

//================================================
//終了処理
//================================================
void CRanking::Uninit(void)
{
	
}

//================================================
//更新処理
//================================================
void CRanking::Update(void)
{
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		if (m_nScore[nCntRanking] == m_nNowScore)
		{
			//カラーを薄くする
			m_col.a -= 255;
			if (m_col.r == 255)
			{
				m_col.r = 0;
				m_col.g = 255;
				m_col.b = 0;
			}
			else if(m_col.g == 255)
			{
				m_col.r = 0;
				m_col.g = 0;
				m_col.b = 255;
			}
			else if (m_col.b == 255)
			{
				m_col.r = 255;
				m_col.g = 0;
				m_col.b = 0;
			}

			if (m_col.a < 0)
			{
				m_col.a = 255;
			}

			for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
			{
				//ナンバーを取得してカラーを設定
				m_pScore[nCntRanking]->GetNumber(nCntNumber)->SetCol(m_col);
			}

			break;
		}
	}
}

//================================================
//描画処理
//================================================
void CRanking::Draw(void)
{
	
}

//================================================
//生成処理
//================================================
CRanking* CRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンスの生成
	CRanking *pRanking = NULL;
	if (pRanking == NULL)
	{
		pRanking = new CRanking;
		if (pRanking != NULL)
		{
			pRanking->Init(pos, size);
		}
	}
	return pRanking;
}

