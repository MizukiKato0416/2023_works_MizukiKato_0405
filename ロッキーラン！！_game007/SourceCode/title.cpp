//================================================
//タイトル処理
//Author:寺下琉生
//================================================
#include "renderer.h"
#include "title.h"
#include "manager.h"
#include "texture.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "fade.h"
#include "ui.h"
#include "scene2D.h"
#include "sound.h"
#include "manager.h"
#include "play_data.h"
//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CTitle::CTitle(int nPriority)
{
	memset(&m_apUi, NULL, sizeof(m_apUi));
	m_nTitleCounter = 0;
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
	//プレイデータにあるスコアを初期化
	CManager::GetPlayData()->SetScore(0);
	//プレイデータにある勝った個体識別番号を初期化
	CManager::GetPlayData()->SetWinNum(-1);

	m_nTitleCounter = 0;

	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();
	//BGM再生
	pSound->Play(CSound::SOUND_LABEL_TITLE_BGM);
	//音量調整
	pSound->ControllVoice(CSound::SOUND_LABEL_TITLE_BGM, 0.5f);

	m_pScene2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), PRIORITY_NONE);
	m_pScene2D->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TITLE_BG));

	m_apUi[0] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, TITLE_LOGO_POSY, 0.0f), D3DXVECTOR3(TITLE_LOGO_SIZEX, TITLE_LOGO_SIZEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_TITLE_LOGO);	//タイトルロゴ
	m_apUi[1] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, TITlE_PRESS_POSY, 0.0f), D3DXVECTOR3(TITlE_PRESS_SIZEX, TITlE_PRESS_SIZEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_TITLE_PRESS);	//Pressボタン
	m_apUi[2] = CUi::Create(D3DXVECTOR3(200.0f, TITlE_PLAYER_1P_POSY, 0.0f), D3DXVECTOR3(TITlE_PLAYER_1P_SIZEX, TITlE_PLAYER_1P_SIZEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_TITLE_PLAYER_1P);	//1P
	m_apUi[3] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, TITlE_PLAYER_2P_POSY, 0.0f), D3DXVECTOR3(TITlE_PLAYER_2P_SIZEX, TITlE_PLAYER_2P_SIZEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_TITLE_PLAYER_2P);	//2P

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

	//サウンド全部止める
	pSound->Stop();
	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CTitle::Update(void)
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

	//Enterキー、スタートボタン、Bボタンを押したら
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
		pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_START, 0) == true ||pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B, 0) == true)
	{
		//フェード取得処理
		CFade *pFade;
		pFade = CManager::GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			//決定SE再生
			pSound->Play(CSound::SOUND_LABEL_DECISION_SE);
			pFade->SetFade(CManager::MODE_MENU);
		}
	}

	//カウンターを増やす
	m_nTitleCounter++;
	if (m_nTitleCounter >= TITLE_TO_RESULT_COUNT)
	{
		m_nTitleCounter = 0;
		//フェード取得処理
		CFade *pFade;
		pFade = CManager::GetFade();

		//リザルトに遷移
		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_RESULT);
		}
	}
}

//================================================
//描画処理
//================================================
void CTitle::Draw(void)
{
	
}

//=============================================================================
//UI取得処理
//=============================================================================
CUi *CTitle::GetUi(void)
{
	return m_apUi[0];
} 