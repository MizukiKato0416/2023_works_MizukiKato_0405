//================================================
//マネージャ処理
//Author:加藤瑞葵
//================================================
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "title.h"
#include "tutorial.h"
#include "game01.h"
#include "result.h"
#include "menu.h"
#include "texture.h"
#include "x_load.h"
#include "fade.h"
#include "play_data.h"
#include "camera.h"
#include "light.h"
#include "pause.h"
#include "sound.h"
#include "motion.h"

//================================================
//静的メンバ変数宣言
//================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputPadX *CManager::m_pInputPadX = NULL;
CTitle *CManager::m_pTitle = NULL;
CTexture *CManager::m_pTexture = NULL;
CXload *CManager::m_pXload = NULL;
CFade *CManager::m_pFade = NULL;
CMenu *CManager::m_pMenu = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CGame01 *CManager::m_pGame01 = NULL;
CResult *CManager::m_pResult = NULL;
CManager::MODE CManager::m_mode = MODE_TITLE;
CPlayData *CManager::m_pPlayData = NULL;
CCamera *CManager::m_apCamera[MAX_CAMERA] = {};
CLight *CManager::m_apLight[MAX_LIGHT] = {};
CSound *CManager::m_pSound = NULL;
CMotion *CManager::m_pMotion = NULL;

//================================================
//デフォルトコンストラクタ
//================================================
CManager::CManager()
{
	memset(&m_apCamera, NULL, sizeof(m_apCamera));
	memset(&m_apLight, NULL, sizeof(m_apLight));
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
	//時刻で初期化
	srand((unsigned int)time(NULL));

	POINT screenPos;
	GetCursorPos(&screenPos);
	SetCursorPos(0, 0);
	ShowCursor(true);

	//サウンドクラスの生成
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
		if (m_pSound != NULL)
		{
			m_pSound->Init(hWnd);
		}
	}

	//レンダリングクラスの生成
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
		if (m_pRenderer != NULL)
		{
			m_pRenderer->Init(hWnd, bWindow);
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

	//テクスチャクラスの生成
	if (m_pTexture == NULL)
	{
		m_pTexture = new CTexture;
		if (m_pTexture != NULL)
		{
			m_pTexture->Init();
		}
	}

	//xファイル読み込みクラスの生成
	if (m_pXload == NULL)
	{
		m_pXload = new CXload;
		if (m_pXload != NULL)
		{
			m_pXload->Init();
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

	//モーションクラスの生成
	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;
		if (m_pMotion != NULL)
		{
			m_pMotion->Init();
		}
	}

	//ライトの生成
	m_apLight[0] = CLight::Create(D3DXVECTOR3(-0.4f, -0.2f, 0.4f), D3DXVECTOR3(400.0f, 800.0f, -400.0f));
	m_apLight[1] = CLight::Create(D3DXVECTOR3(0.4f, 0.8f, -0.4f), D3DXVECTOR3(-100.0f, 0.0f, 100.0f));
	m_apLight[2] = CLight::Create(D3DXVECTOR3(0.0f, -0.4f, 0.4f), D3DXVECTOR3(100.0f, 0.0f, -100.0f));

	//カメラの生成
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		m_apCamera[nCntCamera] = CCamera::Create(D3DXVECTOR3(0.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
													SCREEN_WIDTH / MAX_CAMERA * nCntCamera, 0.0f,
													SCREEN_WIDTH / MAX_CAMERA, SCREEN_HEIGHT);
		m_apCamera[nCntCamera]->SetNum(nCntCamera);
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

	//モーションクラスの破棄
	if (m_pMotion != NULL)
	{
		//終了処理
		m_pMotion->Uninit();

		//メモリの開放
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//カメラの破棄
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		if (m_apCamera[nCntCamera] != NULL)
		{
			//終了処理
			m_apCamera[nCntCamera]->Uninit();

			//メモリの開放
			delete m_apCamera[nCntCamera];
			m_apCamera[nCntCamera] = NULL;
		}
	}

	//ライトの破棄
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		if (m_apLight[nCntLight] != NULL)
		{
			m_apLight[nCntLight]->Uninit();
			delete m_apLight[nCntLight];
			m_apLight[nCntLight] = NULL;
		}
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

	//Xファイル読み込みクラスの破棄
	if (m_pXload != NULL)
	{
		//終了処理
		m_pXload->Uninit();

		//メモリの開放
		delete m_pXload;
		m_pXload = NULL;
	}

	//テクスチャクラスの破棄
	if (m_pTexture != NULL)
	{
		//終了処理
		m_pTexture->Uninit();

		//メモリの開放
		delete m_pTexture;
		m_pTexture = NULL;
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

	//サウンドクラスの破棄
	if (m_pSound != NULL)
	{
		//終了処理
		m_pSound->Uninit();

		//メモリの開放
		delete m_pSound;
		m_pSound = NULL;
	}
}

//================================================
//更新処理
//================================================
void CManager::Update(void)
{
	if (CPause::GetPause() == false)
	{
		for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
		{
			//カメラの更新処理
			if (m_apCamera[nCntCamera] != NULL)
			{
				m_apCamera[nCntCamera]->Update();
			}
		}
	}

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
		//チュートリアルクラスの生成
		if (m_pTutorial == NULL)
		{
			m_pTutorial = new CTutorial;
			if (m_pTutorial != NULL)
			{
				//カメラの破棄
				for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
				{
					if (m_apCamera[nCntCamera] != NULL)
					{
						//終了処理
						m_apCamera[nCntCamera]->Uninit();

						//メモリの開放
						delete m_apCamera[nCntCamera];
						m_apCamera[nCntCamera] = NULL;
					}
				}

				//カメラの生成
				for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
				{
					m_apCamera[nCntCamera] = CCamera::Create(D3DXVECTOR3(0.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
															SCREEN_WIDTH / MAX_CAMERA * nCntCamera, 0.0f,
															SCREEN_WIDTH / MAX_CAMERA, SCREEN_HEIGHT);
					m_apCamera[nCntCamera]->SetNum(nCntCamera);
				}

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
				//カメラの破棄
				for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
				{
					if (m_apCamera[nCntCamera] != NULL)
					{
						//終了処理
						m_apCamera[nCntCamera]->Uninit();

						//メモリの開放
						delete m_apCamera[nCntCamera];
						m_apCamera[nCntCamera] = NULL;
					}
				}

				//カメラの生成
				for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
				{
					m_apCamera[nCntCamera] = CCamera::Create(D3DXVECTOR3(0.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
															SCREEN_WIDTH / MAX_CAMERA * nCntCamera, 0.0f,
															SCREEN_WIDTH / MAX_CAMERA, SCREEN_HEIGHT);
					m_apCamera[nCntCamera]->SetNum(nCntCamera);
				}

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
				//カメラの破棄
				for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
				{
					if (m_apCamera[nCntCamera] != NULL)
					{
						//終了処理
						m_apCamera[nCntCamera]->Uninit();

						//メモリの開放
						delete m_apCamera[nCntCamera];
						m_apCamera[nCntCamera] = NULL;
					}
				}

				//カメラの生成
				for (int nCntCamera = 0; nCntCamera < MAX_RESULT_CAMERA; nCntCamera++)
				{
					m_apCamera[nCntCamera] = CCamera::Create(D3DXVECTOR3(0.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
																SCREEN_WIDTH / MAX_RESULT_CAMERA * nCntCamera, 0.0f,
																SCREEN_WIDTH / MAX_RESULT_CAMERA, SCREEN_HEIGHT);
					m_apCamera[nCntCamera]->SetNum(nCntCamera);
				}

				m_pResult->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}
		break;
	}
}


//=============================================================================
// モード取得処理
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
// fade取得処理
//=============================================================================
CFade* CManager::GetFade(void)
{
	return m_pFade;
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

//=============================================================================
// texture取得処理
//=============================================================================
CTexture* CManager::GetTexture(void)
{
	return m_pTexture;
}

//=============================================================================
// Xload取得処理
//=============================================================================
CXload* CManager::GetXload(void)
{
	return m_pXload;
}

//=============================================================================
// play_data取得処理
//=============================================================================
CPlayData* CManager::GetPlayData(void)
{
	return m_pPlayData;
}

//=============================================================================
// camera取得処理
//=============================================================================
CCamera** CManager::GetCamera(void)
{
	return &m_apCamera[0];
}

//=============================================================================
// light取得処理
//=============================================================================
CLight* CManager::GetLight(void)
{
	return m_apLight[0];
}

//=============================================================================
// sound取得処理
//=============================================================================
CSound* CManager::GetSound(void)
{
	return m_pSound;
}