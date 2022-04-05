//=============================================================================
// メニュー星コントロール処理 [control_menu_star.cpp]
// Author : 寺下琉生
//=============================================================================
#include "control_menu_star.h"
#include "manager.h"
#include "menu.h"
#include "ui.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CControlMenuStar::CControlMenuStar()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CControlMenuStar::~CControlMenuStar()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CControlMenuStar::Init(void)
{
	m_fMaxMoveX = 10.0f;
	m_fMaxMoveY = 1.5f;
	m_nFrame = 0;
	m_col = STAR_COL;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CControlMenuStar::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CControlMenuStar::Update(CScene *pScene)
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


	if (pUi->GetUIType() == CUi::UI_TYPE_MENU_STAR)
	{
		m_nFrame++;


		m_move.x = -12.0f;
		m_move.y = 5.0f;

		// 位置やサイズの設定
		pUi->SetPos(pos, size);
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CControlMenuStar *CControlMenuStar::Create()
{
	//インスタンスの生成
	CControlMenuStar *pControlMenuStar = NULL;

	if (pControlMenuStar == NULL)
	{
		pControlMenuStar = new CControlMenuStar;

		if (pControlMenuStar != NULL)
		{
			pControlMenuStar->Init();
		}
	}

	return pControlMenuStar;
}