//=============================================================================
// ゴールのポリゴンを出す処理 [control_goal.cpp]
// Author : 一戸健
//=============================================================================
#include "control_goal.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "title.h"
#include "ui.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CControlGoal::CControlGoal()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fMaxMove = 0.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CControlGoal::~CControlGoal()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CControlGoal::Init(void)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fMaxMove = 40.5f;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CControlGoal::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CControlGoal::Update(CScene *pScene)
{
	//引数のポインタをUiクラスのポインタにキャスト
	CUi *pUi = NULL;
	pUi = (CUi*)pScene;

	//UIの取得→オブジェクトの位置を取得
	D3DXVECTOR3 pos;
	pos = pUi->GetPos();

	//UIの取得→オブジェクトのサイズを取得
	D3DXVECTOR3 size;
	size = pUi->GetSize();

	// 画面横にいる時に
	if (pos.x < SCREEN_WIDTH / 2.0f)
	{
		m_move.x += 40.5f;
		pos += m_move;

		// 移動量が最大移動量を超えないようにする
		if (m_move.x >= m_fMaxMove)
		{
			m_move.x = m_fMaxMove;
		}
		else if (m_move.x <= -m_fMaxMove)
		{
			m_move.x = -m_fMaxMove;
		}
	}

	// 途中で止める(移動量を0にする)
	if (pos.x >= SCREEN_WIDTH / 2.0f)
	{
		m_move.x = 0.0f;
		pos.x = SCREEN_WIDTH / 2.0f;
		// 位置やサイズの設定
		pUi->SetPos(pos, size);
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CControlGoal *CControlGoal::Create()
{
	//インスタンスの生成
	CControlGoal *pControlGoal = NULL;

	if (pControlGoal == NULL)
	{
		pControlGoal = new CControlGoal;

		if (pControlGoal != NULL)
		{
			pControlGoal->Init();
		}
	}

	return pControlGoal;
}