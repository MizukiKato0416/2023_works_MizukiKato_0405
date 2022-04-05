//================================================
//タイトル処理
//Author:KatoMizuki
//================================================
#include "tutorial.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_d.h"
#include "fade.h"
#include "manager.h"
#include "texture.h"
#include "sound.h"

//================================================
//マクロ定義
//================================================

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CTutorial::CTutorial(int nPriority):CObject(nPriority)
{
	memset(m_pObject2D, NULL, sizeof(m_pObject2D[TUTORIAL_MAX_TYPE]));
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CTutorial::~CTutorial()
{

}

//================================================
//初期化処理
//================================================
HRESULT CTutorial::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//BGM再生
	pSound->Play(CSound::SOUND_LABEL_MENU_BGM);

	//チュートリアルの生成
	m_pObject2D[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 
									   D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_UI);
	m_pObject2D[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_TUTORIAL_01"));

	return S_OK;
}

//================================================
//終了処理
//================================================
void CTutorial::Uninit(void)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//BGM再生
	pSound->Stop(CSound::SOUND_LABEL_MENU_BGM);

	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CTutorial::Update(void)
{
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//パッドD取得処理
	CInputPadD *pInputPadD;
	pInputPadD = CManager::GetInstance()->GetInputPadD();


	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//Enterキー、スタートボタンを押したら
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadD->GetTrigger(CInputPadD::START) == true)
	{
		//1枚目が生成されていたら
		if (m_pObject2D[0] != nullptr)
		{
			//SE再生
			pSound->Play(CSound::SOUND_LABEL_DECIDE_SE);

			//消す
			m_pObject2D[0]->Uninit();
			m_pObject2D[0] = nullptr;

			//2枚目を生成
			m_pObject2D[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 
									           D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_UI);
			m_pObject2D[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_TUTORIAL_02"));
		}
		else if (m_pObject2D[1] != nullptr)
		{//2枚目が生成されていたら
			//フェード取得処理
			CFade *pFade;
			pFade = CManager::GetInstance()->GetFade();

			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				//SE再生
				pSound->Play(CSound::SOUND_LABEL_DECIDE_SE);

				pFade->SetFade(CManager::MODE::MENU);
			}
		}
	}
}

//================================================
//描画処理
//================================================
void CTutorial::Draw(void)
{
	
}
