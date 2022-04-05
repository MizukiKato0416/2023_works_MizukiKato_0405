#//=============================================================================
// 上下する壁のコントロール処理 [control_up_down_wall.cpp]
// Author : KUSAKARI KAKERU
//=============================================================================
#include "control_up_down_wall.h"
#include "manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CControlUpDownWall::CControlUpDownWall()
{
	m_fMoveLength = 0;
	m_nWaitTime = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CControlUpDownWall::~CControlUpDownWall()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CControlUpDownWall::Init(void)
{
	// 時刻を使って乱数の初期化
	srand((unsigned int)time(NULL));

	m_fMoveLength = 0;
	m_nWaitTime = 50;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CControlUpDownWall::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CControlUpDownWall::Update(CScene *pScene)
{
	// m_bUpDownがfalseの時に上昇
	if (m_bUpDown == false)
	{
		// 移動できる範囲外になったら下降に切り替える
		if (m_fMoveLength > m_moveLimit)
		{
			m_nWaitTime--;

			//待機時間の間は移動量を0に
			m_move.y = 0;

			//待機時間が0になったら
			if (m_nWaitTime <= 0)
			{
				m_fMoveLength = 0;
				m_bUpDown = true;
			}
		}
		else
		{
			m_move.y += MOVE_UPDOWN_WALL_SPEED;
			m_fMoveLength += MOVE_UPDOWN_WALL_SPEED;
		}
	}
	// m_bUpDownがtrueの時に下降
	else if (m_bUpDown == true)
	{
		// 移動できる範囲外になったら上昇に切り替える
		if (m_fMoveLength < -m_moveLimit)
		{
			m_move.y = 0;
			m_fMoveLength = 0;

			//待機時間をランダムに変更(数は50～350)
			int nRumdomNumber = rand() % 300 + 50;
			m_nWaitTime = nRumdomNumber;

			m_bUpDown = false;
		}
		else
		{
			m_move.y -= MOVE_UPDOWN_WALL_SPEED;
			m_fMoveLength -= MOVE_UPDOWN_WALL_SPEED;
		}
	}

	// 最大移動量
	if (m_move.y > MAX_UPDOWN_WALL_SPEED)
	{
		m_move.y = MAX_UPDOWN_WALL_SPEED;
	}

	if (m_move.y < -MAX_UPDOWN_WALL_SPEED)
	{
		m_move.y = -MAX_UPDOWN_WALL_SPEED;
	}
}

//================================================
//生成処理
//================================================
CControlUpDownWall *CControlUpDownWall::Create(UP_DOWN_WALL type, float moveLimit)
{
	//インスタンスの生成
	CControlUpDownWall *pControlUpDownWall = NULL;
	if (pControlUpDownWall == NULL)
	{
		pControlUpDownWall = new CControlUpDownWall;
		if (pControlUpDownWall != NULL)
		{
			switch (type)
			{
			case UP_WALL:
				pControlUpDownWall->m_bUpDown = false;
				break;

			case DOWN_WALL:
				pControlUpDownWall->m_bUpDown = true;
				break;

			default:
				break;
			}

			pControlUpDownWall->m_moveLimit = moveLimit;
			pControlUpDownWall->Init();
		}
	}
	return pControlUpDownWall;
}