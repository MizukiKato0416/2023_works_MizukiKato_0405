//================================================
//右に行き停止する動きの処理
//Authore:加藤瑞葵
//================================================
#include "mover_right_stop.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CMoverRightStop::CMoverRightStop()
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
CMoverRightStop::~CMoverRightStop()
{

}

//================================================
//初期化処理
//================================================
HRESULT CMoverRightStop::Init(void)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrameCounter = 0;
	m_moveType = MOVE_TYPE_RIGHT;

	return S_OK;
}

//================================================
//終了処理
//================================================
void CMoverRightStop::Uninit(void)
{
	
}

//================================================
//更新処理
//================================================
void CMoverRightStop::Update(void)
{
	//種別による動きの処理
	switch (m_moveType)
	{
	case MOVE_TYPE_RIGHT:
		m_move = D3DXVECTOR3(MOVER_RIGHT_STOP_RIGHT_SPEED, 0.0f, 0.0f);
		//下降している間カウントを加算
		m_nFrameCounter++;
		if (m_nFrameCounter >= MOVER_RIGHT_STOP_RIGHT_FINISH_COUNT)
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
CMoverRightStop* CMoverRightStop::Create(void)
{
	//インスタンスの生成
	CMoverRightStop *pMoverRightStop = NULL;
	if (pMoverRightStop == NULL)
	{
		pMoverRightStop = new CMoverRightStop;
		if (pMoverRightStop != NULL)
		{
			pMoverRightStop->Init();
		}
	}
	return pMoverRightStop;
}