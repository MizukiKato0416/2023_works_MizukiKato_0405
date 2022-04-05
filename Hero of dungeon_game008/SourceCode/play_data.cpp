//================================================
//プレイデータ管理処理
//Author:KatoMizuki
//================================================
#include "play_data.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CPlayData::CPlayData()
{
	m_nHitPoint = 0;				
	m_nMagicPoint = 0;				
	m_nSpecialPoint = 0;			
	m_pHpGauge = nullptr;			
	m_pMpGauge = nullptr;			
	m_pSpGauge = nullptr;			
	m_nScore = 0;
	m_pScore = nullptr;
	m_nTime = 0;
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
	m_nHitPoint = 0;
	m_nMagicPoint = 0;
	m_nSpecialPoint = 0;
	m_pHpGauge = nullptr;
	m_pMpGauge = nullptr;
	m_pSpGauge = nullptr;
	m_nScore = 0;
	m_pScore = nullptr;
	m_nTime = 0;

	return S_OK;
}

//================================================
//終了処理
//================================================
void CPlayData::Uninit(void)
{
	
}
