//================================================
//降下ながらランダムで左右に行く動きの処理
//Authore:加藤瑞葵
//================================================
#include "mover_fall_random_right_left.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CMoverFallRandomRightLeft::CMoverFallRandomRightLeft()
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
CMoverFallRandomRightLeft::~CMoverFallRandomRightLeft()
{

}

//================================================
//初期化処理
//================================================
HRESULT CMoverFallRandomRightLeft::Init(void)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrameCounter = 0;
	m_moveType = MOVE_TYPE_LOWER_LEFT;

	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化

	return S_OK;
}

//================================================
//終了処理
//================================================
void CMoverFallRandomRightLeft::Uninit(void)
{
	
}

//================================================
//更新処理
//================================================
void CMoverFallRandomRightLeft::Update(void)
{
	//下降している間カウントを加算
	m_nFrameCounter++;

	//種別による動きの処理
	switch (m_moveType)
	{
	case MOVE_TYPE_LOWER_LEFT:
		m_move = D3DXVECTOR3(cosf(3.0f / 4.0f * D3DX_PI) * MOVER_FALL_RANDOM_RIGHT_LEFT_SPEED,
							sinf(3.0f / 4.0f * D3DX_PI) * MOVER_FALL_RANDOM_RIGHT_LEFT_SPEED, 0.0f);
		if (m_nFrameCounter >= MOVER_RIGHT_LEFT_FINISH_COUNT)
		{
			//カウントをリセット
			m_nFrameCounter = 0;
			//次の動きに変える
			m_moveType = MOVE_TYPE_LOWER_RIGHT;
		}
		break;
	case MOVE_TYPE_LOWER_RIGHT:
		m_move = D3DXVECTOR3(cosf(1.0f / 4.0f * D3DX_PI) * MOVER_FALL_RANDOM_RIGHT_LEFT_SPEED,
							sinf(1.0f / 4.0f * D3DX_PI) * MOVER_FALL_RANDOM_RIGHT_LEFT_SPEED, 0.0f);
		if (m_nFrameCounter >= MOVER_RIGHT_LEFT_FINISH_COUNT)
		{
			//カウントをリセット
			m_nFrameCounter = 0;
			//次の動きに変える
			m_moveType = MOVE_TYPE_LOWER_LEFT;
		}
		break;
	default:
		break;
	}
}

//================================================
//生成処理
//================================================
CMoverFallRandomRightLeft* CMoverFallRandomRightLeft::Create(void)
{
	//インスタンスの生成
	CMoverFallRandomRightLeft *pMoverFallRandomRightLeft = NULL;
	if (pMoverFallRandomRightLeft == NULL)
	{
		pMoverFallRandomRightLeft = new CMoverFallRandomRightLeft;
		if (pMoverFallRandomRightLeft != NULL)
		{
			pMoverFallRandomRightLeft->Init();
		}
	}
	return pMoverFallRandomRightLeft;
}