//================================================
//下降して停止し上昇する動きの処理
//Authore:加藤瑞葵
//================================================
#include "mover_fall_stop_rise.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CMoverFallStopRise::CMoverFallStopRise()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrameCounter = 0;
	m_moveType = MOVE_TYPE_NONE;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CMoverFallStopRise::~CMoverFallStopRise()
{

}

//================================================
//初期化処理
//================================================
HRESULT CMoverFallStopRise::Init(void)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrameCounter = 0;
	m_moveType = MOVE_TYPE_FALL;

	return S_OK;
}

//================================================
//終了処理
//================================================
void CMoverFallStopRise::Uninit(void)
{
	
}

//================================================
//更新処理
//================================================
void CMoverFallStopRise::Update(void)
{
	//種別による動きの処理
	switch (m_moveType)
	{
	case MOVE_TYPE_FALL:
		m_move = D3DXVECTOR3(0.0f, MOVER_FALL_SPEED, 0.0f);
		//下降している間カウントを加算
		m_nFrameCounter++;
		if (m_nFrameCounter >= MOVER_FALL_FINISH_COUNT)
		{
			//カウントをリセット
			m_nFrameCounter = 0;
			//次の動きに変える
			m_moveType = MOVE_TYPE_STOP;
		}
		break;
	case MOVE_TYPE_STOP:
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//停止している間カウントを加算
		m_nFrameCounter++;
		if (m_nFrameCounter >= MOVER_STOP_FINISH_COUNT)
		{
			//カウントをリセット
			m_nFrameCounter = 0;
			//次の動きに変える
			m_moveType = MOVE_TYPE_RISE;
		}
		break;
	case MOVE_TYPE_RISE:
		m_move = D3DXVECTOR3(0.0f, MOVER_RISE_SPEED, 0.0f);
		break;
	default:
		break;
	}
}

//================================================
//生成処理
//================================================
CMoverFallStopRise* CMoverFallStopRise::Create(void)
{
	//インスタンスの生成
	CMoverFallStopRise *pMoverFallStopRise = NULL;
	if (pMoverFallStopRise == NULL)
	{
		pMoverFallStopRise = new CMoverFallStopRise;
		if (pMoverFallStopRise != NULL)
		{
			pMoverFallStopRise->Init();
		}
	}
	return pMoverFallStopRise;
}