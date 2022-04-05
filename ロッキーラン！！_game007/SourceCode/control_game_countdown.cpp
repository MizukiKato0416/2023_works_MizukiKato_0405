//=============================================================================
// ゲームカウントダウン処理 [control_game_countdown.cpp]
// Author : 寺下琉生
//=============================================================================
#include "control_game_countdown.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "game01.h"
#include "ui.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CControlGameCountdown::CControlGameCountdown()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CControlGameCountdown::~CControlGameCountdown()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CControlGameCountdown::Init(void)
{
	m_fMaxMove = 2.0f;
	m_nCount = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CControlGameCountdown::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CControlGameCountdown::Update(CScene *pScene)
{
	//引数のポインタをUiクラスのポインタにキャスト
	CUi *pUi = NULL;
	pUi = (CUi*)pScene;

	m_nCount++;

	//UIの取得→オブジェクトの位置を取得
	D3DXVECTOR3 pos;
	pos = pUi->GetPos();

	//UIの取得→オブジェクトのサイズを取得
	D3DXVECTOR3 size;
	size = pUi->GetSize();

	// 画面上にいる時に
	if (pos.y <= SCREEN_HEIGHT / 3.0f)
	{
		m_move.y += 1.5f;
	}
	// 途中で止める(移動量を0にする)
	else if (pos.y >= SCREEN_HEIGHT / 2)
	{
		m_move.y = 0.0f;
	}

	// 移動量が最大移動量を超えないようにする
	if (m_move.y >= m_fMaxMove)
	{
		m_move.y = m_fMaxMove;
	}
	else if (m_move.y <= -m_fMaxMove)
	{
		m_move.y = -m_fMaxMove;
	}

	// アルファ値を上げる(不透明にする)
	if (m_nCount % 2 == 0)
	{
		m_col.a += 0.05f;
	}

	if (m_col.a > 1.0f && m_nCount >= 70)
	{
		m_nCount = 0;
		m_col = 1.0f;
	}

	// m_fAlphaの値を透明度に入れる
	pUi->SetCol(m_col);

	// 位置やサイズの設定
	pUi->SetPos(pos, size);
}

//=============================================================================
// 生成処理
//=============================================================================
CControlGameCountdown *CControlGameCountdown::Create()
{
	//インスタンスの生成
	CControlGameCountdown *pControlGameCountdown = NULL;

	if (pControlGameCountdown == NULL)
	{
		pControlGameCountdown = new CControlGameCountdown;

		if (pControlGameCountdown != NULL)
		{
			pControlGameCountdown->Init();
		}
	}

	return pControlGameCountdown;
}