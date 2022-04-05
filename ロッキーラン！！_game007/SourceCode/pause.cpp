//================================================
//ポーズ処理
//Authore:寺下琉生
//================================================
#include "renderer.h"
#include "pause.h"
#include "manager.h"
#include "texture.h"
#include "scene2D.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "fade.h"
#include "ui.h"
#include "sound.h"
#include "scene.h"
//================================================
//静的メンバ変数宣言
//================================================
bool CPause::m_bPause = false;			//ポーズ画面かどうか

//================================================
//デフォルトコンストラクタ
//================================================
CPause::CPause(int nPriority) :CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CPause::~CPause()
{

}

//================================================
//初期化処理
//================================================
HRESULT CPause::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;
	m_bPause = false;

	return S_OK;
}

//================================================
//終了処理
//================================================
void CPause::Uninit(void)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//今再生されてるサウンドを止める
	pSound->Stop();

	m_bPause = false;
	
	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CPause::Update(void)
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

	//Pキーかスタートボタンでポーズ
	if (pInputKeyboard->GetTrigger(DIK_P) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_START, 0) == true)
	{
		//モードがTUTORIALなら
		if (m_pManager->GetMode() == CManager::MODE_TUTORIAL)
		{
			pSound->ControllVoice(CSound::SOUND_LABEL_TUTORIAL_BGM, 0.1f);
		}
		//モードがGAME01なら
		if (m_pManager->GetMode() == CManager::MODE_GAME01)
		{
			pSound->ControllVoice(CSound::SOUND_LABEL_GAME_BGM, 0.1f);
		}

		pSound->Play(CSound::SOUND_LABEL_POSESCREEN_SE);

		if (m_bPause == false)
		{
			m_bPause = true;

			m_pScene2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + m_pos.x, SCREEN_HEIGHT / 2 + m_pos.y, 0.0f), D3DXVECTOR3(PAUSE_FRAME_SIXEX + m_size.x, PAUSE_FRAME_SIXEY + m_size.y, 0.0f), PRIORITY_UI);
			m_pScene2D->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_PAUSE_UI_FRAME));

			m_apSelect[SELECT_START] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + m_pos.x, PAUSE_START_BUTTON_POSY + PAUSE_CHOICES_SPACE + m_pos.y, 0.0f), D3DXVECTOR3(PAUSE_UI_SIZEX + m_size.x, PAUSE_UI_SIZEY + m_size.y, 0.0f), PRIORITY_UI, CUi::UI_TYPE_PAUSE_START);			//再開ボタン
			m_apSelect[SELECT_EXIT] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + m_pos.x, PAUSE_EXIT_BUTTON_POSY + PAUSE_CHOICES_SPACE + m_pos.y, 0.0f), D3DXVECTOR3(PAUSE_UI_SIZEX + m_size.x, PAUSE_UI_SIZEY + m_size.y, 0.0f), PRIORITY_UI, CUi::UI_TYPE_PAUSE_EXIT);				//メニューに戻るボタン
			m_apSelect[SELECT_RESTART] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + m_pos.x, PAUSE_RESTART_BUTTON_POSY + PAUSE_CHOICES_SPACE + m_pos.y, 0.0f), D3DXVECTOR3(PAUSE_UI_SIZEX + m_size.x, PAUSE_UI_SIZEY + m_size.y, 0.0f), PRIORITY_UI, CUi::UI_TYPE_PAUSE_RESTART);	//リスタートボタン

			m_nSelect = SELECT_START;			//最初は再開を選択中にする

			//再開を明るくする
			m_apSelect[SELECT_START]->SetCol(PAUSE_SELECT_COL);
			//それ以外を暗くする
			m_apSelect[SELECT_EXIT]->SetCol(PAUSE_DEFAULT_COL);
			m_apSelect[SELECT_RESTART]->SetCol(PAUSE_DEFAULT_COL);
		}
		else
		{
			//モードがTUTORIALなら
			if (m_pManager->GetMode() == CManager::MODE_TUTORIAL)
			{
				pSound->ControllVoice(CSound::SOUND_LABEL_TUTORIAL_BGM, 0.5f);
			}
			//モードがGAME01なら
			if (m_pManager->GetMode() == CManager::MODE_GAME01)
			{
				pSound->ControllVoice(CSound::SOUND_LABEL_GAME_BGM, 0.5f);
			}
			pSound->Play(CSound::SOUND_LABEL_POSESCREENCLOSE_SE);
			m_bPause = false;

			m_pScene2D->Uninit();
			delete m_pScene2D;
			m_pScene2D = NULL;
			for (int nCnt = 0; nCnt < SELECT_MAX; nCnt++)
			{
				m_apSelect[nCnt]->Uninit();
				delete m_apSelect[nCnt];
				m_apSelect[nCnt] = NULL;
			}
		}
	}


	if (m_bPause == true)
	{
		//各選択肢を選択中にENTERキー、Bボタンを押したら
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B, 0) == true)
		{
			switch (m_nSelect)
			{
			case SELECT_START:
				//決定SE再生
				pSound->Play(CSound::SOUND_LABEL_DECISION_SE);
				//音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_DECISION_SE, 2.0f);
				//ポーズしたところから再開(ポーズ画面の終了)
				m_bPause = false;
				break;
			case SELECT_EXIT:
				//決定SE再生
				pSound->Play(CSound::SOUND_LABEL_DECISION_SE);
				//音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_DECISION_SE, 2.0f);
				//メニュー画面に戻る
				m_bPause = false;
				if (pFade->GetFade() == CFade::FADE_NONE)
				{
				pFade->SetFade(CManager::MODE_MENU);
				}
				break;
			case SELECT_RESTART:
				//決定SE再生
				pSound->Play(CSound::SOUND_LABEL_DECISION_SE);
				//音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_DECISION_SE, 2.0f);

				//モードがTUTORIALなら
				if (m_pManager->GetMode() == CManager::MODE_TUTORIAL)
				{
					//チュートリアルを最初からやり直す
					m_bPause = false;
					if (pFade->GetFade() == CFade::FADE_NONE)
					{
						pFade->SetFade(CManager::MODE_TUTORIAL);
					}
				}
				//モードがGAME01なら
				if (m_pManager->GetMode() == CManager::MODE_GAME01)
				{
					//ゲームを最初からやり直す
					m_bPause = false;
					if (pFade->GetFade() == CFade::FADE_NONE)
					{
						pFade->SetFade(CManager::MODE_GAME01);
					}
				}
				break;
			default:
				break;
			}
			//サウンド調整
			pSound->ControllVoice(CSound::SOUND_LABEL_GAME_BGM, 0.5f);
			pSound->ControllVoice(CSound::SOUND_LABEL_TUTORIAL_BGM, 0.5f);

			m_pScene2D->Uninit();
			delete m_pScene2D;
			m_pScene2D = NULL;
			for (int nCnt = 0; nCnt < SELECT_MAX; nCnt++)
			{
				m_apSelect[nCnt]->Uninit();
				delete m_apSelect[nCnt];
				m_apSelect[nCnt] = NULL;
			}
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
				m_apSelect[m_nSelect]->SetCol(PAUSE_DEFAULT_COL);
				m_nSelect = SELECT_MAX - 1;
			}
			else
			{
				//選択SE再生
				pSound->Play(CSound::SOUND_LABEL_CHOICE_SE);
				m_apSelect[m_nSelect]->SetCol(PAUSE_DEFAULT_COL);
				m_nSelect--;
			}
			//選択されている選択肢を明るくする
			m_apSelect[m_nSelect]->SetCol(PAUSE_SELECT_COL);
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
				m_apSelect[m_nSelect]->SetCol(PAUSE_DEFAULT_COL);
				m_nSelect = 0;
			}
			else
			{
				//選択SE再生
				pSound->Play(CSound::SOUND_LABEL_CHOICE_SE);
				m_apSelect[m_nSelect]->SetCol(PAUSE_DEFAULT_COL);
				m_nSelect++;
			}
			m_apSelect[m_nSelect]->SetCol(PAUSE_SELECT_COL);
		}
	}
}

//================================================
//描画処理
//================================================
void CPause::Draw(void)
{

}

bool CPause::GetPause(void)
{
	return m_bPause;
}

bool CPause::SetPause(bool bPause)
{
	m_bPause = bPause;
	return m_bPause;
}
//================================================
//生成処理
//================================================
CPause* CPause::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンスの生成
	CPause *pPause = NULL;
	if (pPause == NULL)
	{
		pPause = new CPause;
		if (pPause != NULL)
		{
			pPause->Init(pos, size);
		}
	}
	return pPause;
}