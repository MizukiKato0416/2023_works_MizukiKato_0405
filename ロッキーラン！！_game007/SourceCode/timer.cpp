//================================================
//タイム処理
//Author:寺下琉生
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "renderer.h"
#include "timer.h"
#include "manager.h"
#include "number.h"
#include "ui.h"
#include "play_data.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CTimer::CTimer(int nPriority) : CScene(nPriority)
{
	m_nTime = START_TIME;
	m_pUi = NULL;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CTimer::~CTimer()
{

}

//================================================
//初期化処理
//================================================
HRESULT CTimer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//カンマの生成
	m_pUi = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, pos.y - 5.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), PRIORITY_UI, CUi::UI_TYPE_GAME_TIME_COMMA);

	for (int nCntNumber = 0; nCntNumber < MAX_TIME_POLYGON; nCntNumber++)
	{
		//小数点をつけるため、4つ目の数字からずらす
		if (nCntNumber >= 3)
		{
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(pos.x + 20.0f - (size.x * MAX_TIME_POLYGON / 2) + (size.x * nCntNumber) + (size.x / 2.0f), pos.y, 0.0f), size);
		}
		else
		{
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(pos.x - (size.x * MAX_TIME_POLYGON / 2) + (size.x * nCntNumber) + (size.x / 2.0f), pos.y, 0.0f), size);
		}
	}
	return S_OK;
}

//================================================
//終了処理
//================================================
void CTimer::Uninit(void)
{
	//プレイデータの取得
	CPlayData *pPlayData = NULL;
	pPlayData = CManager::GetPlayData();

	//スコアをプレイデータに保存
	pPlayData->SetScore(m_nTime);

	//ナンバーの破棄
	for (int nCntNumber = 0; nCntNumber < MAX_TIME_POLYGON; nCntNumber++)
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
void CTimer::Update(void)
{
	for (int nCntNumber = 0; nCntNumber < MAX_TIME_POLYGON; nCntNumber++)
	{
		if (nCntNumber == 0)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nTime / (int)powf(10, MAX_TIME_POLYGON - 1));
		}
		else if (nCntNumber == MAX_TIME_POLYGON - 1)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nTime % 10);
		}
		else
		{
			m_apNumber[nCntNumber]->SetNumber(m_nTime % (int)powf(10, MAX_TIME_POLYGON - (float)nCntNumber) / (int)powf(10, MAX_TIME_POLYGON - 1 - (float)nCntNumber));
		}
	}
}

//================================================
//描画処理
//================================================
void CTimer::Draw(void)
{
	for (int nCntNumber = 0; nCntNumber < MAX_TIME_POLYGON; nCntNumber++)
	{
		m_apNumber[nCntNumber]->Draw();
	}
}

//================================================
//生成処理
//================================================
CTimer* CTimer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンスの生成
	CTimer *pTimer = NULL;
	if (pTimer == NULL)
	{
		pTimer = new CTimer;
		if (pTimer != NULL)
		{
			pTimer->Init(pos, size);
		}
	}
	return pTimer;
}

//================================================
//スコア取得処理
//================================================
int CTimer::GetTime(void)
{
	return m_nTime;
}

//================================================
//スコア設定処理
//================================================
void CTimer::SetTime(int nTime)
{
	m_nTime = nTime;
}

//================================================
//スコア加算処理
//================================================
void CTimer::AddTime(int nValue)
{
	m_nTime += nValue;
}

//=============================================================================
// number取得処理
//=============================================================================
CNumber* CTimer::GetNumber(int nNumber)
{
	return m_apNumber[nNumber];
}