//================================================
//メニュー処理
//Authore:寺下琉生
//================================================
#include "renderer.h"
#include "menu.h"
#include "manager.h"
#include "texture.h"
#include "scene2D.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "fade.h"
#include "ui.h"
#include "sound.h"

//================================================
//静的メンバ変数宣言
//================================================

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
	//BGM再生
	pSound->Play(CSound::SOUND_LABEL_MENU_BGM);
	//音量調整
	pSound->ControllVoice(CSound::SOUND_LABEL_MENU_BGM, 0.6f);

	m_pScene2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), PRIORITY_NONE);
	m_pScene2D->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_MENU_BG));

	m_pScene2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), PRIORITY_UI);
	m_pScene2D->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_MEMU_EXPLANATION_FRAME)); //説明枠

	m_pMenu = CUi::Create(D3DXVECTOR3(MENU_LOGO_POSX, MENU_LOGO_POSY, 0.0f), D3DXVECTOR3(MENU_LOGO_SIXEX, MENU_LOGO_SIXEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_MENU_LOGO); //メニューロゴ

	m_apSelect[SELECT_TUTORIAL] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, MENU_TUTORIAL_BUTTON_POSY + MENU_CHOICES_SPACE, 0.0f), D3DXVECTOR3(MENU_UI_SIZEX, MENU_UI_SIZEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_MENU_SELECT_TUTORIAL); //チュートリアルボタン
	m_apSelect[SELECT_GAME] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, MENU_GAME_BUTTON_POSY + MENU_CHOICES_SPACE, 0.0f), D3DXVECTOR3(MENU_UI_SIZEX, MENU_UI_SIZEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_MENU_SELECT_GAME);		     //ゲームボタン
	m_apSelect[SELECT_BACKTITLE] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, MENU_EXIT_BUTTON_POSY + MENU_CHOICES_SPACE, 0.0f), D3DXVECTOR3(MENU_UI_SIZEX, MENU_UI_SIZEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_MENU_SELECT_BACKTITLE);		     //終了ボタン

	m_apExplanation[EXPLANATION_TUTORIAL] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, MENU_EXPLANATION_POSY, 0.0f), D3DXVECTOR3(MENU_UI_SIZEX, MENU_UI_SIZEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_MENU_EXPLANATION_TUTORIAL);			 //チュートリアル説明
	m_apExplanation[EXPLANATION_GAME] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, MENU_EXPLANATION_POSY, 0.0f), D3DXVECTOR3(MENU_UI_SIZEX, MENU_UI_SIZEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_MENU_EXPLANATION_GAME);					 //ゲーム説明
	m_apExplanation[EXPLANATION_EXIT] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, MENU_EXPLANATION_POSY, 0.0f), D3DXVECTOR3(MENU_UI_SIZEX, MENU_UI_SIZEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_MENU_EXPLANATION_BACKTITLE);					 //終了説明

	m_nSelect = SELECT_TUTORIAL;			//最初はチュートリアルを選択中にする
	m_nExplanation = EXPLANATION_TUTORIAL;	//最初はチュートリアルの説明を表示する

	//チュートリアルを明るくする
	m_apSelect[SELECT_TUTORIAL]->SetCol(MENU_SELECT_COL);
	//それ以外を暗くする
	m_apSelect[SELECT_GAME]->SetCol(MENU_DEFAULT_COL);
	m_apSelect[SELECT_BACKTITLE]->SetCol(MENU_DEFAULT_COL);

	//チュートリアルの説明を明るくする
	m_apExplanation[EXPLANATION_TUTORIAL]->SetCol(MENU_SELECT_COL);
	//それ以外の説明を非表示にする
	m_apExplanation[EXPLANATION_GAME]->SetCol(MENU_HIDE);
	m_apExplanation[EXPLANATION_EXIT]->SetCol(MENU_HIDE);


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

	//サウンド全部止める
	pSound->Stop();
	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CMenu::Update(void)
{
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

	//各選択肢を選択中にENTERキー、スタートボタン、Bボタンを押したら
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
		pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_START, 0) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B, 0) == true)
	{
		switch (m_nSelect)
		{
		case SELECT_TUTORIAL:
			//チュートリアルに遷移
			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				//決定SE再生
				pSound->Play(CSound::SOUND_LABEL_DECISION_SE);
				//音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_DECISION_SE, 2.0f);
				pFade->SetFade(CManager::MODE_TUTORIAL);
			}
			break;
		case SELECT_GAME:
			//ゲーム画面に遷移
			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				//決定SE再生
				pSound->Play(CSound::SOUND_LABEL_DECISION_SE);
				//音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_DECISION_SE, 2.0f);
				pFade->SetFade(CManager::MODE_GAME01);
			}
			break;
		case SELECT_BACKTITLE:
			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				//決定SE再生
				pSound->Play(CSound::SOUND_LABEL_DECISION_SE);
				//音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_DECISION_SE, 2.0f);
				//タイトルに戻る
				pFade->SetFade(CManager::MODE_TITLE);
			}
			break;
		default:
			break;
		}
	}

	m_nSpan++;
	switch (m_nPattern)
	{
	case STARPATTERN_01:
		//4秒
		if (m_nSpan == 240)
		{
			m_apStar[0] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH, 60.0f, 0.0f), D3DXVECTOR3(250.0f, 250.0f, 0.0f), PRIORITY_NONE, CUi::UI_TYPE_MENU_STAR);
		}
		//6秒
		if (m_nSpan == 360)
		{
			m_apStar[1] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH, 40.0f, 0.0f), D3DXVECTOR3(175.0f, 175.0f, 0.0f), PRIORITY_NONE, CUi::UI_TYPE_MENU_STAR);
		}
		//6.5秒
		if (m_nSpan == 390)
		{
			m_apStar[2] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH, 100.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), PRIORITY_NONE, CUi::UI_TYPE_MENU_STAR);
			m_nSpan = 0;
			m_nPattern = STARPATTERN_02;
		}
		break;
	case STARPATTERN_02:
		//4秒
		if (m_nSpan == 240)
		{
			m_apStar[0] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH, 80.0f, 0.0f), D3DXVECTOR3(175.0f, 175.0f, 0.0f), PRIORITY_NONE, CUi::UI_TYPE_MENU_STAR);
		}
		//4.5秒
		if (m_nSpan == 270)
		{
			m_apStar[1] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH, 100.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), PRIORITY_NONE, CUi::UI_TYPE_MENU_STAR);
		}
		//5秒
		if (m_nSpan == 300)
		{
			m_apStar[2] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH, 60.0f, 0.0f), D3DXVECTOR3(250.0f, 250.0f, 0.0f), PRIORITY_NONE, CUi::UI_TYPE_MENU_STAR);
			m_nSpan = 0;
			m_nPattern = STARPATTERN_03;
		}
		break;
	case STARPATTERN_03:
		//4秒
		if (m_nSpan == 240)
		{
			m_apStar[0] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH, 60.0f, 0.0f), D3DXVECTOR3(250.0f, 250.0f, 0.0f), PRIORITY_NONE, CUi::UI_TYPE_MENU_STAR);
		}
		//5秒
		if (m_nSpan == 300)
		{
			m_apStar[1] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH, 60.0f, 0.0f), D3DXVECTOR3(250.0f, 250.0f, 0.0f), PRIORITY_NONE, CUi::UI_TYPE_MENU_STAR);
		}
		//6秒
		if (m_nSpan == 360)
		{
			m_apStar[2] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH, 60.0f, 0.0f), D3DXVECTOR3(250.0f, 250.0f, 0.0f), PRIORITY_NONE, CUi::UI_TYPE_MENU_STAR);
			m_nSpan = 0;
			m_nPattern = STARPATTERN_01;
		}
		break;
	}

	//Wキー、↑キーを押す、左スティックを上に倒したとき、十字キー上を押したとき
	if (pInputKeyboard->GetTrigger(DIK_W) == true || pInputKeyboard->GetTrigger(DIK_UP) == true ||
		pInputPadX->GetLeftStickTrigger(CInputPadX::STICKTYPE_UP, 0) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP, 0) == true)

	{

		//現在の選択肢切り替え
		if (m_nSelect <= 0)
		{
			//選択SE再生
			pSound->Play(CSound::SOUND_LABEL_CHOICE_SE);
			//選択されてない選択肢を暗くする
			m_apSelect[m_nSelect]->SetCol(MENU_DEFAULT_COL);
			//選択されてない選択肢の説明を非表示にする
			m_apExplanation[m_nExplanation]->SetCol(MENU_HIDE);
			//選択肢の切り替え
			m_nSelect = SELECT_MAX - 1;
			//説明の切り替え
			m_nExplanation = EXPLANATION_MAX - 1;
		}
		else
		{
			//選択SE再生
			pSound->Play(CSound::SOUND_LABEL_CHOICE_SE);
			//選択されてない選択肢を暗くする
			m_apSelect[m_nSelect]->SetCol(MENU_DEFAULT_COL);
			//選択されてない選択肢の説明を非表示にする
			m_apExplanation[m_nExplanation]->SetCol(MENU_HIDE);
			//選択肢の切り替え
			m_nSelect--;
			//説明の切り替え
			m_nExplanation--;
		}
		//選択されている選択肢を明るくする
		m_apSelect[m_nSelect]->SetCol(MENU_SELECT_COL);
		//選択されている選択肢の説明を明るくする
		m_apExplanation[m_nExplanation]->SetCol(MENU_SELECT_COL);
	}
	//Sキー、↓キーを押すまたは左スティックを下に倒したとき
	if (pInputKeyboard->GetTrigger(DIK_S) == true || pInputKeyboard->GetTrigger(DIK_DOWN) == true ||
		pInputPadX->GetLeftStickTrigger(CInputPadX::STICKTYPE_DOWN, 0) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN, 0) == true)
	{
		//現在の選択肢切り替え
		if (m_nSelect >= SELECT_MAX - 1)
		{
			//選択SE再生
			pSound->Play(CSound::SOUND_LABEL_CHOICE_SE);
			//選択されてない選択肢を暗くする
			m_apSelect[m_nSelect]->SetCol(MENU_DEFAULT_COL);
			//選択されてない選択肢の説明を非表示にする
			m_apExplanation[m_nExplanation]->SetCol(MENU_HIDE);
			//選択肢の切り替え
			m_nSelect = 0;
			//説明の切り替え
			m_nExplanation = 0;
		}
		else
		{
			//選択SE再生
			pSound->Play(CSound::SOUND_LABEL_CHOICE_SE);
			//選択されてない選択肢を暗くする
			m_apSelect[m_nSelect]->SetCol(MENU_DEFAULT_COL);
			//選択されてない選択肢の説明を非表示にする
			m_apExplanation[m_nExplanation]->SetCol(MENU_HIDE);
			//選択肢の切り替え
			m_nSelect++;
			//説明の切り替え
			m_nExplanation++;
		}
		//選択されている選択肢を明るくする
		m_apSelect[m_nSelect]->SetCol(MENU_SELECT_COL);
		//選択されている選択肢の説明を表示
		m_apExplanation[m_nExplanation]->SetCol(MENU_SELECT_COL);
	}
}

//================================================
//描画処理
//================================================
void CMenu::Draw(void)
{

}
