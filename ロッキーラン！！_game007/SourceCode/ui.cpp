//================================================
//UI処理
//Authore:寺下琉生
//================================================
#include "scene2D.h"
#include "scene.h"
#include "manager.h"
#include "ui.h"
#include "texture.h"
#include "control.h"
#include "control_title_logo.h"
#include "control_title_enter.h"
#include "control_title_1p.h"
#include "control_title_2p.h"
#include "control_menu_star.h"
#include "control_game_countdown.h"
#include "control_game_start.h"
#include "control_goal.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CUi::CUi(int nPriority) :CScene2D(nPriority)
{
	m_pControl = NULL;
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CUi::~CUi()
{

}

//================================================
//初期化処理
//================================================
HRESULT CUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);

	m_size = size;
	SetObjType(OBJTYPE_UI);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CUi::Uninit(void)
{
	CScene2D::Uninit();
}

//================================================
//更新処理
//================================================
void CUi::Update(void)
{
	if (m_pControl != NULL)
	{
		m_pControl->Update(this);

		// Scene2Dからposを取得
		D3DXVECTOR3 pos;
		pos = GetPos();

		m_size = GetSize();

		pos += m_pControl->GetMove();

		SetPos(pos, m_size);
	}
}

//================================================
//描画処理
//================================================
void CUi::Draw(void)
{
	CScene2D::Draw();
}

//================================================
//生成処理
//================================================
CUi* CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriolity, UI_TYPE type)
{
	//インスタンスの生成
	CUi *pUi = NULL;
	if (pUi == NULL)
	{
		pUi = new CUi(nPriolity);
		if (pUi != NULL)
		{
			// 指定したUIの種類でテクスチャを変える
			switch (type)
			{
			case UI_TYPE_TITLE_LOGO:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TITLE_UI_LOGO);
				pUi->m_pControl = CControlTitleLogo::Create();
				break;
			case UI_TYPE_TITLE_PRESS:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TITLE_UI_PRESS);
				pUi->m_pControl = CControlTitleEnter::Create();
				break;
			case UI_TYPE_TITLE_PLAYER_1P:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TITLE_UI_PLAYER_1P);
				pUi->m_pControl = CControlTitle1P::Create();
				break;
			case UI_TYPE_TITLE_PLAYER_2P:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TITLE_UI_PLAYER_2P);
				pUi->m_pControl = CControlTitle2P::Create();
				break;
			case UI_TYPE_MENU_LOGO:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_MENU_LOGO);
				break;
			case UI_TYPE_MENU_STAR:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_MENU_UI_STAR);
				pUi->m_pControl = CControlMenuStar::Create();
				break;
			case UI_TYPE_MENU_SELECT_TUTORIAL:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_MENU_UI_TUTORIAL);
				break;
			case UI_TYPE_MENU_SELECT_GAME:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_MENU_UI_GAME);
				break;
			case UI_TYPE_MENU_SELECT_BACKTITLE:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_MENU_UI_BACKTITLE);
				break;
			case UI_TYPE_MENU_EXPLANATION_TUTORIAL:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_MENU_UI_TUTORIAL_EXPLANATION);
				break;
			case UI_TYPE_MENU_EXPLANATION_GAME:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_MENU_UI_GAME_EXPLANATION);
				break;
			case UI_TYPE_MENU_EXPLANATION_BACKTITLE:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_MENU_UI_BACKTITLE_EXPLANATION);
				break;
			case UI_TYPE_TUTORIAL_EXPLANATION:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TUTORIAL_EXPLANATION);
				break;
			case UI_TYPE_GAME_COUNTDOWN03:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_GAME_UI_COUNTDOWN03);
				pUi->m_pControl = CControlGameCountdown::Create();
				break;
			case UI_TYPE_GAME_COUNTDOWN02:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_GAME_UI_COUNTDOWN02);
				pUi->m_pControl = CControlGameCountdown::Create();
				break;
			case UI_TYPE_GAME_COUNTDOWN01:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_GAME_UI_COUNTDOWN01);
				pUi->m_pControl = CControlGameCountdown::Create();
				break;
			case UI_TYPE_GAME_START:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_GAME_UI_START);
				pUi->m_pControl = CControlGameStart::Create();
				break;
			case UI_TYPE_GAME_GOAL:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_GAME_UI_CLEAR);
				pUi->m_pControl = CControlGoal::Create();
				break;
			case UI_TYPE_GAME_TIME_UP:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_GAME_UI_TIME_UP);
				break;
			case UI_TYPE_GAME_TIME_COMMA:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_COMMA);
				break;
			case UI_TYPE_RESULT_WIN:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_RESULT_UI_WIN);
				break;
			case UI_TYPE_RESULT_RANKING01:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_RESULT_UI_RANKING01);
				break;
			case UI_TYPE_RESULT_RANKING02:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_RESULT_UI_RANKING02);
				break;
			case UI_TYPE_RESULT_RANKING03:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_RESULT_UI_RANKING03);
				break;
			case UI_TYPE_RESULT_RANKING04:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_RESULT_UI_RANKING04);
				break;
			case UI_TYPE_RESULT_RANKING05:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_RESULT_UI_RANKING05);
				break;
			case UI_TYPE_PAUSE_FRAME:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_PAUSE_UI_FRAME);
				break;
			case UI_TYPE_PAUSE_START:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_PAUSE_UI_START);
				break;
			case UI_TYPE_PAUSE_EXIT:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_PAUSE_UI_EXIT);
				break;
			case UI_TYPE_PAUSE_RESTART:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_PAUSE_UI_RESTART);
				break;
			case UI_TYPE_PLAYER_1P:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_PLAYER_UI_1P);
				break;
			case UI_TYPE_PLAYER_2P:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_PLAYER_UI_2P);
				break;
			default:
				break;
			}
			pUi->BindTexture(pUi->m_pTexture);
			pUi->m_type = type;
			pUi->Init(pos, size);
		}
	}
	return pUi;
}

//================================================
//種類の取得
//================================================
CUi::UI_TYPE CUi::GetUIType(void)
{
	return m_type;
}