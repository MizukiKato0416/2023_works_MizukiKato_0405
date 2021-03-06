//================================================
//ランキング処理
//Author:加藤瑞葵
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
#include "texture.h"
#include "ui.h"
#include "sound.h"

//================================================
//静的メンバ変数宣言
//================================================
CScore *CRanking::m_apScore[MAX_RANKING] = {};

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

	memset(&m_apUi, NULL, sizeof(m_apUi));
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
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		//スコアの生成
		m_apScore[nCntRanking] = CScore::Create(D3DXVECTOR3(pos.x, pos.y + (float)(SCREEN_HEIGHT / (MAX_RANKING + 1)) * nCntRanking + (float)(SCREEN_HEIGHT / (MAX_RANKING + 1)), 0.0f),
												size);

		//カンマの生成
		m_apUi[nCntRanking] = CUi::Create(D3DXVECTOR3(pos.x + 10.0f, pos.y + (float)(SCREEN_HEIGHT / (MAX_RANKING + 1)) * nCntRanking + (float)(SCREEN_HEIGHT / (MAX_RANKING + 1)), 0.0f),
			D3DXVECTOR3(80.0f, 80.0f, 0.0f), PRIORITY_UI, CUi::UI_TYPE_GAME_TIME_COMMA);

		//ランク生成
		m_apScene2D[nCntRanking] = CScene2D::Create(D3DXVECTOR3(RANKING_RANK_POLYGON_POS_X, pos.y + (float)(SCREEN_HEIGHT / (MAX_RANKING + 1)) * nCntRanking + (float)(SCREEN_HEIGHT / (MAX_RANKING + 1)), 0.0f),
													RANKING_RANK_POLYGON_SIZE, PRIORITY_UI);
		switch (nCntRanking)
		{
		case 0:
			m_apScene2D[nCntRanking]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_RESULT_UI_RANKING01));
			break;
		case 1:
			m_apScene2D[nCntRanking]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_RESULT_UI_RANKING02));
			break;
		case 2:
			m_apScene2D[nCntRanking]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_RESULT_UI_RANKING03));
			break;
		case 3:
			m_apScene2D[nCntRanking]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_RESULT_UI_RANKING04));
			break;
		case 4:
			m_apScene2D[nCntRanking]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_RESULT_UI_RANKING05));
			break;
		}
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
		for (int nCntRanking2 = 0; nCntRanking2 < MAX_SCORE_DATA - 1; nCntRanking2++)
		{
			//昇順で並べる
			if ((m_nScore[nCntRanking2] > m_nScore[nCntRanking2 + 1] && m_nScore[nCntRanking2 + 1] != 0) || m_nScore[nCntRanking2] == 0)
			{

			//if ((m_nScore[nCntRanking2] > m_nScore[nCntRanking2 + 1] && m_nScore[nCntRanking2] == 0) || m_nScore[nCntRanking2] == 0)

				int nScore = m_nScore[nCntRanking2];
				m_nScore[nCntRanking2] = m_nScore[nCntRanking2 + 1];
				m_nScore[nCntRanking2 + 1] = nScore;
			}
		}
	}

	//スコアの設定
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		m_apScore[nCntRanking]->SetScore(m_nScore[nCntRanking]);
	}

	//セーブ処理
	pFile = fopen("data/ranking.txt", "w");
	if (pFile != NULL)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			fprintf(pFile, "%d\n", m_apScore[nCntRanking]->GetScore());
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
	Release();
}

//================================================
//更新処理
//================================================
void CRanking::Update(void)
{
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		//スコアの位置取得処理
		D3DXVECTOR3 posScore = m_apScore[nCntRanking]->GetPos();
		//UIの位置とサイズ取得処理
		D3DXVECTOR3 posUi = m_apUi[nCntRanking]->GetPos();
		D3DXVECTOR3 sizeUi = m_apUi[nCntRanking]->GetSize();

		if (posScore.x > SCREEN_WIDTH / 2.0f)
		{
			if (nCntRanking > 0)
			{
				//スコアの位置取得処理
				D3DXVECTOR3 posScorePrev = m_apScore[nCntRanking - 1]->GetPos();
				if (posScorePrev.x <= SCREEN_WIDTH / 2.0f)
				{
					posScore.x += RANKING_MOVE_X;
					posUi.x += RANKING_MOVE_X;
				}
			}
			else
			{
				posScore.x += RANKING_MOVE_X;
				posUi.x += RANKING_MOVE_X;
			}
			if (posScore.x <= SCREEN_WIDTH / 2.0f)
			{
				posScore.x = SCREEN_WIDTH / 2.0f;

				//サウンド取得処理
				CSound *pSound;
				pSound = CManager::GetSound();

				pSound->Play(CSound::SOUND_LABEL_RANKING_SE);
				pSound->ControllVoice(CSound::SOUND_LABEL_RANKING_SE, 1.5f);

			}
			if (posUi.x <= SCREEN_WIDTH / 2.0f + 10.0f)
			{
				posUi.x = SCREEN_WIDTH / 2.0f + 10.0f;
			}
			//位置設定
			m_apScore[nCntRanking]->SetScorePos(posScore);
			m_apUi[nCntRanking]->SetPos(posUi, sizeUi);
		}
	}

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		if (m_nNowScore != 0 && m_nScore[nCntRanking] == m_nNowScore)
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
				m_apScore[nCntRanking]->GetNumber(nCntNumber)->SetCol(m_col);
				m_apUi[nCntRanking]->SetCol(m_col);
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