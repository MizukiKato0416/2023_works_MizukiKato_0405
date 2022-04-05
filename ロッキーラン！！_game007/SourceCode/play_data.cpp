//================================================
//プレイデータ管理処理
//Author:加藤瑞葵
//================================================
#include "play_data.h"

//================================================
//静的メンバ変数宣言
//================================================
int CPlayData::m_nScore = 0;
int CPlayData::m_nWinNum = 0;

//================================================
//デフォルトコンストラクタ
//================================================
CPlayData::CPlayData()
{
	
}

//================================================
//デストラクタ
//================================================
CPlayData::~CPlayData()
{

}

//================================================
//初期化処理
//================================================
HRESULT CPlayData::Init(void)
{
	m_nScore = 0;
	m_nWinNum = 0;

	return S_OK;
}

//================================================
//終了処理
//================================================
void CPlayData::Uninit(void)
{
	
}

//================================================
//スコアの設定処理
//================================================
void CPlayData::SetScore(int nScore)
{
	m_nScore = nScore;
}

//================================================
//スコアの取得処理
//================================================
int CPlayData::GetScore(void)
{
	return m_nScore;
}

//================================================
//勝った個体識別番号の設定
//================================================
void CPlayData::SetWinNum(int nWinNum)
{
	m_nWinNum = nWinNum;
}

//================================================
//勝った個体識別番号の取得
//================================================
int CPlayData::GetWinNum(void)
{
	return m_nWinNum;
}