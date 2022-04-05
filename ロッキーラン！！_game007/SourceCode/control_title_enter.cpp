//=============================================================================
// タイトルエンター文字コントロール処理 [control_title_enter.cpp]
// Author : KUSAKARI KAKERU
//=============================================================================
#include "control_title_enter.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "title.h"
#include "ui.h"
#include "scene.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CControlTitleEnter::CControlTitleEnter()
{
	m_nCount = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_bAlphaUp = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CControlTitleEnter::~CControlTitleEnter()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CControlTitleEnter::Init(void)
{
	m_nCount = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_bAlphaUp = true;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CControlTitleEnter::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CControlTitleEnter::Update(CScene *pScene)
{
	//引数のポインタをUiクラスのポインタにキャスト
	CUi *pUi = NULL;
	pUi = (CUi*)pScene;

	D3DXVECTOR3 pos;
	pos = pUi->GetPos();

	m_nCount++;

	// アルファ値を下げる(透明にする)
	if (m_bAlphaUp == false)
	{
		if (m_nCount % 2 == 0)
		{
			m_col.a += -0.05f;
		}

		if (m_col.a < 0)
		{
			m_nCount = 0;
			m_col.a = 0;
			m_bAlphaUp = true;
		}
	}
	// アルファ値を上げる(不透明にする)
	else if (m_bAlphaUp == true)
	{
		if (m_nCount % 2 == 0)
		{
			m_col.a += 0.05f;
		}

		if (m_col.a > 1.0f && m_nCount >= 70)
		{
			m_nCount = 0;
			m_col.a = 1.0f;
			m_bAlphaUp = false;
		}
	}

	// m_fAlphaの値を透明度に入れる
	pUi->SetCol(m_col);
}

//=============================================================================
// 生成処理
//=============================================================================
CControlTitleEnter *CControlTitleEnter::Create()
{
	//インスタンスの生成
	CControlTitleEnter *pControlTitleEnter = NULL;

	if (pControlTitleEnter == NULL)
	{
		pControlTitleEnter = new CControlTitleEnter;

		if (pControlTitleEnter != NULL)
		{
			pControlTitleEnter->Init();
		}
	}

	return pControlTitleEnter;
}