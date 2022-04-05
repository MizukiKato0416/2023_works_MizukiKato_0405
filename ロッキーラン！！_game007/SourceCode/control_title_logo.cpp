//=============================================================================
// タイトルロゴコントロール処理 [control_title_logo.cpp]
// Author : KUSAKARI KAKERU
//=============================================================================
#include "control_title_logo.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "title.h"
#include "ui.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CControlTitleLogo::CControlTitleLogo()
{
	
}

//=============================================================================
// デストラクタ
//=============================================================================
CControlTitleLogo::~CControlTitleLogo()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CControlTitleLogo::Init(void)
{
	m_fMaxMove = 1.5f;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CControlTitleLogo::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CControlTitleLogo::Update(CScene *pScene)
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

	// 画面上にいる時に
	if (pos.y <= SCREEN_HEIGHT / 3.0f)
	{
		m_move.y += 1.5f;
	}
	// 途中で止める(移動量を0にする)
	else if (pos.y >= SCREEN_HEIGHT / 2.6f)
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

	// 位置やサイズの設定
	pUi->SetPos(pos, size);
}

//=============================================================================
// 生成処理
//=============================================================================
CControlTitleLogo *CControlTitleLogo::Create()
{
	//インスタンスの生成
	CControlTitleLogo *pControlTitleLogo = NULL;

	if (pControlTitleLogo == NULL)
	{
		pControlTitleLogo = new CControlTitleLogo;

		if (pControlTitleLogo != NULL)
		{
			pControlTitleLogo->Init();
		}
	}

	return pControlTitleLogo;
}