//================================================
//マネージャ処理
//Authore:加藤瑞葵
//================================================
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "sound.h"
#include "texture.h"
#include "title.h"
#include "tutorial.h"
#include "game01.h"
#include "result.h"
#include "menu.h"
#include "fade.h"
#include "play_data.h"

//================================================
//静的メンバ変数宣言
//================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputPadX *CManager::m_pInputPadX = NULL;
CSound *CManager::m_pSound = NULL;
CTexture *CManager::m_pTexture = NULL;
CFade *CManager::m_pFade = NULL;
CPlayData *CManager::m_pPlayData = NULL;

CTitle *CManager::m_pTitle = NULL;
CMenu *CManager::m_pMenu = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CGame01 *CManager::m_pGame01 = NULL;
CResult *CManager::m_pResult = NULL;
CManager::MODE CManager::m_mode = MODE_TITLE;

//================================================
//デフォルトコンストラクタ
//================================================
CManager::CManager()
{
	
}

//================================================
//デストラクタ
//================================================
CManager::~CManager()
{

}

//================================================
//初期化処理
//================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//レンダリングクラスの生成
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
		if (m_pRenderer != NULL)
		{
			m_pRenderer->Init(hWnd, bWindow);
		}
	}

	//テクスチャクラスの生成
	if (m_pTexture == NULL)
	{
		m_pTexture = new CTexture;
		if (m_pTexture != NULL)
		{
			m_pTexture->Init();
		}
	}

	//キーボードクラスの生成
	if (m_pInputKeyboard == NULL)
	{
		m_pInputKeyboard = new CInputKeyboard;
		if (m_pInputKeyboard != NULL)
		{
			m_pInputKeyboard->Init(hInstance, hWnd);
		}
	}

	//パッドクラスの生成
	if (m_pInputPadX == NULL)
	{
		m_pInputPadX = new CInputPadX;
		if (m_pInputPadX != NULL)
		{
			m_pInputPadX->Init(hInstance, hWnd);
		}
	}

	//サウンドクラスの生成
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
		if (m_pSound != NULL)
		{
			m_pSound->Init(hWnd);
		}
	}

	//プレイデータクラスの生成
	if (m_pPlayData == NULL)
	{
		m_pPlayData = new CPlayData;
		if (m_pPlayData != NULL)
		{
			m_pPlayData->Init();
		}
	}

	//フェードクラスの生成
	m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
							D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
							MODE_TITLE);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CManager::Uninit(void)
{
	//全てのオブジェクトの破棄
	CScene::ReleaseAll();

	//テクスチャクラスの破棄
	if (m_pTexture != NULL)
	{
		//終了処理
		m_pTexture->Uninit();

		//メモリの開放
		delete m_pTexture;
		m_pTexture = NULL;
	}

	//プレイデータクラスの破棄
	if (m_pPlayData != NULL)
	{
		//終了処理
		m_pPlayData->Uninit();
	
		//メモリの開放
		delete m_pPlayData;
		m_pPlayData = NULL;
	}

	//サウンドクラスの破棄
	if (m_pSound != NULL)
	{
		//終了処理
		m_pSound->Uninit();

		//メモリの開放
		delete m_pSound;
		m_pSound = NULL;
	}

	//パッドクラスの破棄
	if (m_pInputPadX != NULL)
	{
		//終了処理
		m_pInputPadX->Uninit();

		//メモリの開放
		delete m_pInputPadX;
		m_pInputPadX = NULL;
	}

	//キーボードクラスの破棄
	if (m_pInputKeyboard != NULL)
	{
		//終了処理
		m_pInputKeyboard->Uninit();

		//メモリの開放
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//レンダラークラスの破棄
	if (m_pRenderer != NULL)
	{
		//終了処理
		m_pRenderer->Uninit();

		//メモリの開放
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//================================================
//更新処理
//================================================
void CManager::Update(void)
{
	//キーボード
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	//パッド
	if (m_pInputPadX != NULL)
	{
		m_pInputPadX->Update();
	}

	//レンダラー
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
}

//================================================
//描画処理
//================================================
void CManager::Draw(void)
{
	//レンダラー
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=======================================================================
//設定処理
//=======================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;
	case MODE_MENU:
		if (m_pMenu != NULL)
		{
			m_pMenu->Uninit();
			m_pMenu = NULL;
		}
		break;
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			m_pTutorial = NULL;
		}
		break;
	case MODE_GAME01:
		if (m_pGame01 != NULL)
		{
			m_pGame01->Uninit();
			m_pGame01 = NULL;
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;
	}

	//全てのオブジェクトの破棄
	CScene::ReleaseAll();

	m_mode = mode;

	switch (mode)
	{
	case MODE_TITLE:
		//タイトルクラスの生成
		if (m_pTitle == NULL)
		{
			m_pTitle = new CTitle;
			if (m_pTitle != NULL)
			{
				m_pTitle->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}
		break;
	case MODE_MENU:
		//メニュークラスの生成
		if (m_pMenu == NULL)
		{
			m_pMenu = new CMenu;
			if (m_pMenu != NULL)
			{
				m_pMenu->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}
		break;
	case MODE_TUTORIAL:
		//メニュークラスの生成
		if (m_pTutorial == NULL)
		{
			m_pTutorial = new CTutorial;
			if (m_pTutorial != NULL)
			{
				m_pTutorial->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}
		break;
	case MODE_GAME01:
		//ゲーム01クラスの生成
		if (m_pGame01 == NULL)
		{
			m_pGame01 = new CGame01;
			if (m_pGame01 != NULL)
			{
				m_pGame01->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}
		break;
	case MODE_RESULT:
		//リザルトクラスの生成
		if (m_pResult == NULL)
		{
			m_pResult = new CResult;
			if (m_pResult != NULL)
			{
				m_pResult->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}
		break;
	}
}

//=============================================================================
// mode取得処理
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
// Renderer取得処理
//=============================================================================
CRenderer* CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// InputKeyboard取得処理
//=============================================================================
CInputKeyboard* CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
// InputKeyboard取得処理
//=============================================================================
CInputPadX* CManager::GetInputPadX(void)
{
	return m_pInputPadX;
}

//=============================================================================
// sound取得処理
//=============================================================================
CSound* CManager::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
// texture取得処理
//=============================================================================
CTexture* CManager::GetTexture(void)
{
	return m_pTexture;
}

//=============================================================================
// fade取得処理
//=============================================================================
CFade* CManager::GetFade(void)
{
	return m_pFade;
}

//=============================================================================
// play_data取得処理
//=============================================================================
CPlayData* CManager::GetPlayData(void)
{
	return m_pPlayData;
}

//=============================================================================
// title取得処理
//=============================================================================
CTitle* CManager::GetTitle(void)
{
	return m_pTitle;
}

//=============================================================================
// menu取得処理
//=============================================================================
CMenu* CManager::GetMenu(void)
{
	return m_pMenu;
}

//=============================================================================
// tutorial取得処理
//=============================================================================
CTutorial* CManager::GetTutorial(void)
{
	return m_pTutorial;
}

//=============================================================================
// game01取得処理
//=============================================================================
CGame01* CManager::GetGame01(void)
{
	return m_pGame01;
}

//=============================================================================
// result取得処理
//=============================================================================
CResult* CManager::GetResult(void)
{
	return m_pResult;
}