//================================================
//スコア処理
//Author:加藤瑞葵
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "renderer.h"
#include "score.h"
#include "manager.h"
#include "number.h"
#include "play_data.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CScore::CScore(int nPriority) :CScene(nPriority)
{
	m_nScore = MAX_SCORE;
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CScore::~CScore()
{

}

//================================================
//初期化処理
//================================================
HRESULT CScore::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		//小数点をつけるため、4つ目の数字からずらす
		if (nCntNumber >= MAX_SCORE_POLYGON / 2)
		{
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(pos.x + 20.0f - (size.x * MAX_SCORE_POLYGON / 2) + (size.x * nCntNumber) + (size.x / 2.0f), pos.y, 0.0f), size);
		}
		else
		{
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(pos.x - (size.x * MAX_SCORE_POLYGON / 2) + (size.x * nCntNumber) + (size.x / 2.0f), pos.y, 0.0f), size);
		}
	}
	m_size = size;
	m_pos = pos;

	SetPos(m_pos);
	SetSize(m_size);
	return S_OK;
}

//================================================
//終了処理
//================================================
void CScore::Uninit(void)
{
	//ナンバーの破棄
	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		if (m_apNumber[nCntNumber] != NULL)
		{
			m_apNumber[nCntNumber]->Uninit();
			delete m_apNumber[nCntNumber];
			m_apNumber[nCntNumber] = NULL;
		}
	}

	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CScore::Update(void)
{
	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		if (nCntNumber == 0)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nScore / (int)powf(10, MAX_SCORE_POLYGON - 1));
		}
		else if (nCntNumber == MAX_SCORE_POLYGON - 1)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nScore % 10);
		}
		else
		{
			m_apNumber[nCntNumber]->SetNumber(m_nScore % (int)powf(10, MAX_SCORE_POLYGON - (float)nCntNumber) / (int)powf(10, MAX_SCORE_POLYGON - 1 - (float)nCntNumber));
		}
	}
}

//================================================
//描画処理
//================================================
void CScore::Draw(void)
{
	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		m_apNumber[nCntNumber]->Draw();
	}
}

//================================================
//生成処理
//================================================
CScore* CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンスの生成
	CScore *pScore = NULL;
	if (pScore == NULL)
	{
		pScore = new CScore;
		if (pScore != NULL)
		{
			pScore->Init(pos, size);
		}
	}
	return pScore;
}

//================================================
//スコア取得処理
//================================================
int CScore::GetScore(void)
{
	return m_nScore;
}

//================================================
//スコア設定処理
//================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}

//================================================
//スコア加算処理
//================================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
}

//=============================================================================
// number取得処理
//=============================================================================
CNumber* CScore::GetNumber(int nNumber)
{
	return m_apNumber[nNumber];
}

//================================================
//スコア位置設定処理
//================================================
void CScore::SetScorePos(D3DXVECTOR3 pos)
{
	//位置設定
	m_pos = pos;
	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		//小数点をつけるため、4つ目の数字からずらす
		if (nCntNumber >= MAX_SCORE_POLYGON / 2)
		{
			m_apNumber[nCntNumber]->SetPos(D3DXVECTOR3(pos.x + 20.0f - (m_size.x * MAX_SCORE_POLYGON / 2) + (m_size.x * nCntNumber) + (m_size.x / 2.0f), pos.y, 0.0f));
		}
		else
		{
			m_apNumber[nCntNumber]->SetPos(D3DXVECTOR3(pos.x - (m_size.x * MAX_SCORE_POLYGON / 2) + (m_size.x * nCntNumber) + (m_size.x / 2.0f), pos.y, 0.0f));
		}
	}
	//位置を設定
	SetPos(m_pos);
}