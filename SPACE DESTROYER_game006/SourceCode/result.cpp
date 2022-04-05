//================================================
//リザルト処理
//Authore:加藤瑞葵
//================================================
#include "renderer.h"
#include "result.h"
#include "manager.h"
#include "texture.h"
#include "bg.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "fade.h"
#include "ranking.h"
#include "number.h"
#include "sound.h"

//================================================
//静的メンバ変数宣言
//================================================
CBg *CResult::m_pBg = NULL;
CTexture *CResult::m_pTexture = NULL;
CRanking *CResult::m_pRanking = NULL;

//================================================
//デフォルトコンストラクタ
//================================================
CResult::CResult()
{
	m_nTitleCounter = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CResult::~CResult()
{

}

//================================================
//初期化処理
//================================================
HRESULT CResult::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//変数初期化
	m_nTitleCounter = 0;

	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//BGMの再生
	pSound->Play(CSound::SOUND_LABEL_RESULT_BGM);
	//サウンドの音量調整
	pSound->ControllVoice(CSound::SOUND_LABEL_RESULT_BGM, 0.5f);

	//背景の生成
	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	//背景の生成
	m_pScene2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
		CScene::PRIORITY_BG_0);
	//背景のテクスチャ割り当て
	m_pScene2D->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TYPE_BG_RESULT));

	//ランキングの生成
	m_pRanking = CRanking::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 0.0f, 0.0f), D3DXVECTOR3(RANKING_POLYGON_WIDTH, RANKING_POLYGON_HEIGHT, 0.0f));

	return S_OK;
}

//================================================
//終了処理
//================================================
void CResult::Uninit(void)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();
	//BGMの停止
	pSound->Stop(CSound::SOUND_LABEL_RESULT_BGM);

	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CResult::Update(void)
{
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//パッド取得処理
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//カウンターを加算
	m_nTitleCounter++;
	if (m_nTitleCounter >= RESULT_TO_TITLE_COUNT)
	{
		m_nTitleCounter = 0;

		//フェード取得処理
		CFade *pFade;
		pFade = CManager::GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			//タイトルに行く
			pFade->SetFade(CManager::MODE_TITLE);
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_START) == true || 
		pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true)
	{
		//フェード取得処理
		CFade *pFade;
		pFade = CManager::GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			//SEの再生
			pSound->Play(CSound::SOUND_LABEL_DECIDE_SE_00);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_DECIDE_SE_00, 0.8f);
			//タイトルに行く
			pFade->SetFade(CManager::MODE_TITLE);
		}
	}

	if (m_pRanking != NULL)
	{
		//更新処理
		m_pRanking->Update();
	}

}

//================================================
//描画処理
//================================================
void CResult::Draw(void)
{
	
}

//=============================================================================
// texture取得処理
//=============================================================================
CTexture* CResult::GetTexture(void)
{
	return m_pTexture;
}

//=============================================================================
// bg取得処理
//=============================================================================
CBg* CResult::GetBg(void)
{
	return m_pBg;
}

//=============================================================================
// ranking取得処理
//=============================================================================
CRanking* CResult::GetRanking(void)
{
	return m_pRanking;
}