//================================================
//タイトル処理
//Authore:加藤瑞葵
//================================================
#include "renderer.h"
#include "title.h"
#include "manager.h"
#include "bg.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "fade.h"
#include "sound.h"
#include "ui_move.h"
#include "play_data.h"
#include "player.h"


//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CTitle::CTitle()
{
	m_nResultCounter = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CTitle::~CTitle()
{

}

//================================================
//初期化処理
//================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//変数初期化
	m_nResultCounter = 0;

	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//BGMの再生
	pSound->Play(CSound::SOUND_LABEL_TITLE_BGM);
	//サウンドの音量調整
	pSound->ControllVoice(CSound::SOUND_LABEL_TITLE_BGM, 0.5f);

	//背景の生成
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	//UIの生成
	CUiMove::Create(D3DXVECTOR3(UI_TITLE_INIT_POS_X, UI_TITLE_INIT_POS_Y, 0.0f), D3DXVECTOR3(UI_TITLE_WIDTH, UI_TITLE_HEIGHT, 0.0f),
					D3DXVECTOR3(0.0f, UI_TITLE_MOVE_Y, 0.0f), CUiMove::UI_MOVE_TYPE_TITLE);

	//UIの生成
	CUiMove::Create(D3DXVECTOR3(UI_TITLE_PRESS_START_POS_X, UI_TITLE_PRESS_START_POS_Y, 0.0f), 
					D3DXVECTOR3(UI_TITLE_PRESS_START_WIDTH, UI_TITLE_PRESS_START_HEIGHT, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_PRESS_START);

	//プレイデータの取得
	CPlayData *pPlayData = NULL;
	pPlayData = CManager::GetPlayData();

	//プレイデータ初期化
	pPlayData->SetPlayerLife(MAX_PLAYER_INIT_LIFE);
	pPlayData->SetScore(0);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CTitle::Uninit(void)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();
	//BGMの停止
	pSound->Stop(CSound::SOUND_LABEL_TITLE_BGM);

	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CTitle::Update(void)
{
	//パッド取得処理
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//カウンターを加算
	m_nResultCounter++;

	if (m_nResultCounter >= TITLE_TO_RESULT_COUNT)
	{
		m_nResultCounter = 0;

		//フェード取得処理
		CFade *pFade;
		pFade = CManager::GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			//リザルトに行く
			pFade->SetFade(CManager::MODE_RESULT);
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||				//エンターキーが押されたら
		pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_START) == true ||	//startボタンが押されたら
		pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true)			//bボタンが押されたら
	{
		//フェード取得処理
		CFade *pFade;
		pFade = CManager::GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			//メニューに行く
			pFade->SetFade(CManager::MODE_MENU);
			//サウンド取得処理
			CSound *pSound;
			pSound = CManager::GetSound();
			//SEの再生
			pSound->Play(CSound::SOUND_LABEL_TITLE_START_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_TITLE_START_SE, 1.0f);
		}
	}
}

//================================================
//描画処理
//================================================
void CTitle::Draw(void)
{
	
}
