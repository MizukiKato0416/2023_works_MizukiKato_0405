//================================================
//下降して左下に行く動きの処理
//Authore:加藤瑞葵
//================================================
#include "mover_fall_lower_left.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CMoverFallLowerLeft::CMoverFallLowerLeft()
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
CMoverFallLowerLeft::~CMoverFallLowerLeft()
{

}

//================================================
//初期化処理
//================================================
HRESULT CMoverFallLowerLeft::Init(void)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrameCounter = 0;
	m_moveType = MOVE_TYPE_FALL;

	return S_OK;
}

//================================================
//終了処理
//================================================
void CMoverFallLowerLeft::Uninit(void)
{
	
}

//================================================
//更新処理
//================================================
void CMoverFallLowerLeft::Update(void)
{
	//種別による動きの処理
	switch (m_moveType)
	{
	case MOVE_TYPE_FALL:
		m_move = D3DXVECTOR3(0.0f, MOVER_LOWER_LEFT_FALL_SPEED, 0.0f);
		//下降している間カウントを加算
		m_nFrameCounter++;
		if (m_nFrameCounter >= MOVER_FALL_FINISH_COUNT)
		{
			//カウントをリセット
			m_nFrameCounter = 0;
			//次の動きに変える
			m_moveType = MOVE_TYPE_LOWER_LEFT;
		}
		break;
	case MOVE_TYPE_LOWER_LEFT:
		m_move = D3DXVECTOR3(cosf(3.0f / 4.0f * D3DX_PI) * MOVER_LOWER_LEFT_SPEED, sinf(3.0f / 4.0f * D3DX_PI) * MOVER_LOWER_LEFT_SPEED, 0.0f);
		break;
	default:
		break;
	}
}

//================================================
//生成処理
//================================================
CMoverFallLowerLeft* CMoverFallLowerLeft::Create(void)
{
	//インスタンスの生成
	CMoverFallLowerLeft *pMoverFallLowerLeft = NULL;
	if (pMoverFallLowerLeft == NULL)
	{
		pMoverFallLowerLeft = new CMoverFallLowerLeft;
		if (pMoverFallLowerLeft != NULL)
		{
			pMoverFallLowerLeft->Init();
		}
	}
	return pMoverFallLowerLeft;
}