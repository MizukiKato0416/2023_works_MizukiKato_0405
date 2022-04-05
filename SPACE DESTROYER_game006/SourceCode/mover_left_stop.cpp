//================================================
//左に行き停止する動きの処理
//Authore:加藤瑞葵
//================================================
#include "mover_left_stop.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CMoverLeftStop::CMoverLeftStop()
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
CMoverLeftStop::~CMoverLeftStop()
{

}

//================================================
//初期化処理
//================================================
HRESULT CMoverLeftStop::Init(void)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrameCounter = 0;
	m_moveType = MOVE_TYPE_LEFT;

	return S_OK;
}

//================================================
//終了処理
//================================================
void CMoverLeftStop::Uninit(void)
{
	
}

//================================================
//更新処理
//================================================
void CMoverLeftStop::Update(void)
{
	//種別による動きの処理
	switch (m_moveType)
	{
	case MOVE_TYPE_LEFT:
		m_move = D3DXVECTOR3(MOVER_LEFT_STOP_LEFT_SPEED, 0.0f, 0.0f);
		//下降している間カウントを加算
		m_nFrameCounter++;
		if (m_nFrameCounter >= MOVER_LEFT_STOP_LEFT_FINISH_COUNT)
		{
			//カウントをリセット
			m_nFrameCounter = 0;
			//次の動きに変える
			m_moveType = MOVE_TYPE_STOP;
		}
		break;
	case MOVE_TYPE_STOP:
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		break;
	default:
		break;
	}
}

//================================================
//生成処理
//================================================
CMoverLeftStop* CMoverLeftStop::Create(void)
{
	//インスタンスの生成
	CMoverLeftStop *pMoverLeftStop = NULL;
	if (pMoverLeftStop == NULL)
	{
		pMoverLeftStop = new CMoverLeftStop;
		if (pMoverLeftStop != NULL)
		{
			pMoverLeftStop->Init();
		}
	}
	return pMoverLeftStop;
}