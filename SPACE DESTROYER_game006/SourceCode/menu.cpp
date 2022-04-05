//================================================
//メニュー処理
//Authore:加藤瑞葵
//================================================
#include "renderer.h"
#include "menu.h"
#include "manager.h"
#include "texture.h"
#include "scene2D.h"
#include "ui_rest.h"
#include "ui_move.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "fade.h"
#include "sound.h"


//================================================
//静的メンバ変数宣言
//================================================
CScene2D *CMenu::m_pScene2D = NULL;
CTexture *CMenu::m_pTexture = NULL;
int CMenu::m_nSelect = SELECT_MENU_TYPE_NONE;
int CMenu::m_nCntFrame = 0;

//================================================
//デフォルトコンストラクタ
//================================================
CMenu::CMenu()
{

}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CMenu::~CMenu()
{

}

//================================================
//初期化処理
//================================================
HRESULT CMenu::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//BGMの再生
	pSound->Play(CSound::SOUND_LABEL_MENU_BGM);
	//サウンドの音量調整
	pSound->ControllVoice(CSound::SOUND_LABEL_MENU_BGM, 0.5f);

	m_nSelect = SELECT_MENU_TYPE_GAME_START;

	//背景の生成
	m_pScene2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
									CScene::PRIORITY_BG_0);
	//背景のテクスチャ割り当て
	m_pScene2D->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TYPE_BG_MENU));

	//UIの生成
	CUiMove::Create(D3DXVECTOR3(UI_MENU_CIRCLE_POS_X, UI_MENU_CIRCLE_INIT_POS_Y, 0.0f), D3DXVECTOR3(UI_MENU_CIRCLE_SMALL_WIDTH, UI_MENU_CIRCLE_SMALL_HEIGHT, 0.0f),
					D3DXVECTOR3(0.0f, UI_MENU_CIRCLE_INIT_MOVE, 0.0f), CUiMove::UI_MOVE_TYPE_MENU_CIRCLE_SMALL);

	CUiMove::Create(D3DXVECTOR3(UI_MENU_CIRCLE_POS_X, UI_MENU_CIRCLE_INIT_POS_Y, 0.0f), D3DXVECTOR3(UI_MENU_CIRCLE_BIG_WIDTH, UI_MENU_CIRCLE_BIG_HEIGHT, 0.0f),
					D3DXVECTOR3(0.0f, UI_MENU_CIRCLE_INIT_MOVE, 0.0f), CUiMove::UI_MOVE_TYPE_MENU_CIRCLE_BIG);

	CUiMove::Create(D3DXVECTOR3(UI_MENU_EXPLANATION_FALSE_POS_X, UI_MENU_EXPLANATION_FALSE_POS_Y, 0.0f), D3DXVECTOR3(UI_MENU_EXPLANATION_TUTORIAL_WIDTH, UI_MENU_EXPLANATION_TUTORIAL_HEIGHT, 0.0f),
					D3DXVECTOR3(0.0f, UI_MENU_FLOAT_MOVE, 0.0f), CUiMove::UI_MOVE_TYPE_MENU_EXPLANATION_TUTORIAL);

	CUiMove::Create(D3DXVECTOR3(UI_MENU_EXPLANATION_FALSE_POS_X, UI_MENU_EXPLANATION_FALSE_POS_Y, 0.0f), D3DXVECTOR3(UI_MENU_EXPLANATION_GAME_WIDTH, UI_MENU_EXPLANATION_GAME_HEIGHT, 0.0f),
					D3DXVECTOR3(UI_MENU_EXPLANATION_MOVE, UI_MENU_FLOAT_MOVE, 0.0f), CUiMove::UI_MOVE_TYPE_MENU_EXPLANATION_GAME);

	CUiMove::Create(D3DXVECTOR3(UI_MENU_EXPLANATION_FALSE_POS_X, UI_MENU_EXPLANATION_FALSE_POS_Y, 0.0f), D3DXVECTOR3(UI_MENU_EXPLANATION_EXIT_WIDTH, UI_MENU_EXPLANATION_EXIT_HEIGHT, 0.0f),
					D3DXVECTOR3(0.0f, UI_MENU_FLOAT_MOVE, 0.0f), CUiMove::UI_MOVE_TYPE_MENU_EXPLANATION_EXIT);

	CUiMove::Create(D3DXVECTOR3(UI_MENU_SELECT_FALSE_POS_X, UI_MENU_GAME_POS_Y, 0.0f), D3DXVECTOR3(UI_MENU_SELECT_TRUE_WIDTH, UI_MENU_SELECT_TRUE_HEIGHT, 0.0f),
					D3DXVECTOR3(UI_MENU_SELECT_INIT_MOVE, UI_MENU_FLOAT_MOVE, 0.0f), CUiMove::UI_MOVE_TYPE_MENU_GAME_START);

	CUiMove::Create(D3DXVECTOR3(UI_MENU_SELECT_FALSE_POS_X, UI_MENU_TUTORIAL_POS_Y, 0.0f), D3DXVECTOR3(UI_MENU_SELECT_FALSE_WIDTH, UI_MENU_SELECT_FALSE_HEIGHT, 0.0f),
					D3DXVECTOR3(UI_MENU_SELECT_INIT_MOVE, UI_MENU_FLOAT_MOVE, 0.0f), CUiMove::UI_MOVE_TYPE_MENU_TUTORIAL);

	CUiMove::Create(D3DXVECTOR3(UI_MENU_SELECT_FALSE_POS_X, UI_MENU_EXIT_POS_Y, 0.0f), D3DXVECTOR3(UI_MENU_SELECT_FALSE_WIDTH, UI_MENU_SELECT_FALSE_HEIGHT, 0.0f),
					D3DXVECTOR3(UI_MENU_SELECT_INIT_MOVE, UI_MENU_FLOAT_MOVE, 0.0f), CUiMove::UI_MOVE_TYPE_MENU_EXIT);

	CUiRest::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(UI_REST_MENU_BAND_WIDTH, UI_REST_MENU_BAND_HEIGHT, 0.0f),
					CUiRest::UI_REST_TYPE_MENU_BAND);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CMenu::Uninit(void)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();
	//BGMの停止
	pSound->Stop(CSound::SOUND_LABEL_MENU_BGM);

	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CMenu::Update(void)
{
	m_nCntFrame++;

	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//フェード取得処理
	CFade *pFade;
	pFade = CManager::GetFade();

	//パッド取得処理
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		//選択処理
		if (pInputKeyboard->GetTrigger(DIK_UP) == true ||
			pInputPadX->GetLeftStickTrigger(CInputPadX::STICKTYPE_UP) == true ||
			pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP) == true)
		{
			m_nSelect--;
			if (m_nSelect < SELECT_MENU_TYPE_TUTORIAL)
			{
				m_nSelect = SELECT_MENU_TYPE_TUTORIAL;
			}
			else
			{
				//BGMの再生
				pSound->Play(CSound::SOUND_LABEL_CURSOR_SE);
				//サウンドの音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_CURSOR_SE, 0.8f);
			}
		}
		else if (pInputKeyboard->GetTrigger(DIK_DOWN) == true ||
					pInputPadX->GetLeftStickTrigger(CInputPadX::STICKTYPE_DOWN) == true ||
					pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN) == true)
		{
			m_nSelect++;
			if (m_nSelect > SELECT_MENU_TYPE_EXIT)
			{
				m_nSelect = SELECT_MENU_TYPE_EXIT;
			}
			else
			{
				//SEの再生
				pSound->Play(CSound::SOUND_LABEL_CURSOR_SE);
				//サウンドの音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_CURSOR_SE, 0.8f);
			}
		}

		//決定処理
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_START) == true ||
			pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true)
		{
			switch (m_nSelect)
			{
			case SELECT_MENU_TYPE_TUTORIAL:
				pFade->SetFade(CManager::MODE_TUTORIAL);
				//SEの再生
				pSound->Play(CSound::SOUND_LABEL_DECIDE_SE_00);
				//サウンドの音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_DECIDE_SE_00, 0.8f);
				break;
			case SELECT_MENU_TYPE_GAME_START:
				pFade->SetFade(CManager::MODE_GAME01);
				//SEの再生
				pSound->Play(CSound::SOUND_LABEL_DECIDE_SE_00);
				//サウンドの音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_DECIDE_SE_00, 0.8f);
				break;
			case SELECT_MENU_TYPE_EXIT:
				pFade->SetFade(CManager::MODE_TITLE);
				//SEの再生
				pSound->Play(CSound::SOUND_LABEL_EXIT_SE);
				//サウンドの音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_EXIT_SE, 1.2f);
				break;
			default:
				break;
			}
		}
	}
}

//================================================
//描画処理
//================================================
void CMenu::Draw(void)
{
	
}

//=============================================================================
// texture取得処理
//=============================================================================
CTexture* CMenu::GetTexture(void)
{
	return m_pTexture;
}

//=============================================================================
// 選択肢取得処理
//=============================================================================
int CMenu::GetSelect(void)
{
	return m_nSelect;
}

//=============================================================================
// Frameカウント取得処理
//=============================================================================
int CMenu::GetFrame(void)
{
	return m_nCntFrame;
}

//=============================================================================
// Frameカウント設定処理
//=============================================================================
void CMenu::SetFrame(int nCntFrame)
{
	m_nCntFrame = nCntFrame;
}