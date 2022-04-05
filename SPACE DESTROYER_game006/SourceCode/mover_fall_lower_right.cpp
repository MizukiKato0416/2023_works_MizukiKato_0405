//================================================
//下降して右下に行く動きの処理
//Authore:加藤瑞葵
//================================================
#include "mover_fall_lower_right.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CMoverFallLowerRight::CMoverFallLowerRight()
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
CMoverFallLowerRight::~CMoverFallLowerRight()
{

}

//================================================
//初期化処理
//================================================
HRESULT CMoverFallLowerRight::Init(void)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrameCounter = 0;
	m_moveType = MOVE_TYPE_FALL;

	return S_OK;
}

//================================================
//終了処理
//================================================
void CMoverFallLowerRight::Uninit(void)
{
	
}

//================================================
//更新処理
//================================================
void CMoverFallLowerRight::Update(void)
{
	//種別による動きの処理
	switch (m_moveType)
	{
	case MOVE_TYPE_FALL:
		m_move = D3DXVECTOR3(0.0f, MOVER_FALL_LOWER_RIGHT_SPEED, 0.0f);
		//下降している間カウントを加算
		m_nFrameCounter++;
		if (m_nFrameCounter >= MOVER_FALL_FINISH_COUNT)
		{
			//カウントをリセット
			m_nFrameCounter = 0;
			//次の動きに変える
			m_moveType = MOVE_TYPE_LOWER_RIGHT;
		}
		break;
	case MOVE_TYPE_LOWER_RIGHT:
		m_move = D3DXVECTOR3(cosf(1.0f / 4.0f * D3DX_PI) * MOVER_LOWER_RIGHT_SPEED, sinf(1.0f / 4.0f * D3DX_PI) * MOVER_LOWER_RIGHT_SPEED, 0.0f);
		break;
	default:
		break;
	}
}

//================================================
//生成処理
//================================================
CMoverFallLowerRight* CMoverFallLowerRight::Create(void)
{
	//インスタンスの生成
	CMoverFallLowerRight *pMoverFallLowerRight = NULL;
	if (pMoverFallLowerRight == NULL)
	{
		pMoverFallLowerRight = new CMoverFallLowerRight;
		if (pMoverFallLowerRight != NULL)
		{
			pMoverFallLowerRight->Init();
		}
	}
	return pMoverFallLowerRight;
}