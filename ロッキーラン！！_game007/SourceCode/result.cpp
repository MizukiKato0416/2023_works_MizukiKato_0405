//================================================
//リザルト処理
//Author: 寺下琉生
//================================================
#include "renderer.h"
#include "result.h"
#include "manager.h"
#include "texture.h"
#include "ranking.h"
#include "manager.h"
#include "input_keyboard.h"
#include "meshfield.h"
#include "meshsphere.h"
#include "model_single.h"
#include "input_pad_x.h"
#include "fade.h"
#include "sound.h"
#include "play_data.h"
#include "ui.h"
#include "motion_player.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CResult::CResult()
{
	memset(&m_apPlayer, NULL, sizeof(m_apPlayer));
	m_pMeshField = NULL;
	m_pMeshSphere = NULL;
	m_pRanking = NULL;
	memset(&m_apModelSingle, NULL, sizeof(m_apModelSingle));
	memset(&m_apUi, NULL, sizeof(m_apUi));
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
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();
	//BGM再生
	pSound->Play(CSound::SOUND_LABEL_RESULT_BGM);
	//音量調整
	pSound->ControllVoice(CSound::SOUND_LABEL_RESULT_BGM, 0.5f);

	if(CManager::GetPlayData()->GetWinNum() == -1)
	{
		m_pScene2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), PRIORITY_NONE);
		m_pScene2D->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_RESULT_BG));

		if (m_pRanking == NULL)
		{
			//ランキングの生成
			m_pRanking = CRanking::Create(D3DXVECTOR3(SCREEN_WIDTH + RANKING_POLYGON_WIDTH * MAX_SCORE_POLYGON / 2.0f, RESULT_RANKING_POSY, 0.0f),
											D3DXVECTOR3(RANKING_POLYGON_WIDTH, RANKING_POLYGON_HEIGHT, 0.0f));
		}
	}
	else
	{
		//メッシュスフィアの生成
		m_pMeshSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, -200.0f, 0.0f), D3DXVECTOR3(RESULT_WORLD_SIZE, RESULT_WORLD_SIZE, RESULT_WORLD_SIZE),
											D3DXVECTOR3(0.0f, 0.0f, 0.0f), 128, 32);
		m_pMeshSphere->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_SKY));

		//メッシュフィールドの生成
		m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, -200.0f, 0.0f), D3DXVECTOR3(RESULT_WORLD_SIZE, 0.0f, RESULT_WORLD_SIZE),
											D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2, 2);
		m_pMeshField->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TILE));

		//スタート床の生成
		m_apModelSingle[0] = CModelSingle::Create(D3DXVECTOR3(0.0f, 0.0f, -330.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_GOAL_FLOOR, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

		m_apModelSingle[1] = CModelSingle::Create(D3DXVECTOR3(0.0f, 10.0f, -330.0f + 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_BACKFENCE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

		m_apModelSingle[2] = CModelSingle::Create(D3DXVECTOR3(-310.0f, 10.0f, -330.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_SIDEFENCE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
		m_apModelSingle[3] = CModelSingle::Create(D3DXVECTOR3(310.0f, 10.0f, -330.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_SIDEFENCE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

		//ゴールの柱の生成
		m_apModelSingle[4] = CModelSingle::Create(D3DXVECTOR3(-280.0f, 0.0f, -330.0f - 99.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_GOAL_POLE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
		m_apModelSingle[5] = CModelSingle::Create(D3DXVECTOR3(280.0f, 0.0f, -330.0f - 99.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_GOAL_POLE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

		//ゴールの旗の生成
		m_apModelSingle[6] = CModelSingle::Create(D3DXVECTOR3(0.0f, 200.0f, -330.0f - 99.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_GOAL_FLAG, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

		//王冠の生成
		m_apModelSingle[7] = CModelSingle::Create(D3DXVECTOR3(0.0f, 10.0f, -330.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_RESULT_CROWN, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

		//気球の生成
		m_apModelSingle[7] = CModelSingle::Create(D3DXVECTOR3(-350.0f, 10.0f, -130.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_BALLOON, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
		m_apModelSingle[8] = CModelSingle::Create(D3DXVECTOR3(100.0f, -60.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_BALLOON, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
		m_apModelSingle[9] = CModelSingle::Create(D3DXVECTOR3(-100.0f, 10.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_BALLOON, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
		m_apModelSingle[10] = CModelSingle::Create(D3DXVECTOR3(400.0f, 10.0f, 450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_BALLOON, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	}
	
	int nNum = 0;
	switch (CManager::GetPlayData()->GetWinNum())
	{
	case 0:
		//プレイヤーの生成
		m_apPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, 60.0f, -330.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
		m_apPlayer[1] = CPlayer::Create(D3DXVECTOR3(50.0f, 60.0f, -330.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);

		//プレイヤーナンバー生成
		m_apUi[0] = CUi::Create(D3DXVECTOR3(RESULT_PLAYERNUMBER_POS_X + SCREEN_WIDTH, RESULT_PLAYERNUMBER_POS_Y, 0.0f),
								D3DXVECTOR3(RESULT_PLAYERNUMBER_SIZE_X, RESULT_PLAYERNUMBER_SIZE_Y, 0.0f), PRIORITY_UI, CUi::UI_TYPE_PLAYER_1P);
		//WinUI生成
		m_apUi[1] = CUi::Create(D3DXVECTOR3(RESULT_WIN_POS_X + SCREEN_WIDTH, RESULT_WIN_POS_Y, 0.0f),
								D3DXVECTOR3(RESULT_WIN_SIZE_X, RESULT_WIN_SIZE_Y, 0.0f), PRIORITY_UI, CUi::UI_TYPE_RESULT_WIN);

		break;
	case 1:
		//プレイヤーの生成
		m_apPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, 60.0f, -330.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
		m_apPlayer[1] = CPlayer::Create(D3DXVECTOR3(50.0f, 60.0f, -330.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

		//プレイヤーナンバー生成
		m_apUi[0] = CUi::Create(D3DXVECTOR3(RESULT_PLAYERNUMBER_POS_X + SCREEN_WIDTH, RESULT_PLAYERNUMBER_POS_Y, 0.0f),
								D3DXVECTOR3(RESULT_PLAYERNUMBER_SIZE_X, RESULT_PLAYERNUMBER_SIZE_Y, 0.0f), PRIORITY_UI, CUi::UI_TYPE_PLAYER_2P);
		//WinUI生成
		m_apUi[1] = CUi::Create(D3DXVECTOR3(RESULT_WIN_POS_X + SCREEN_WIDTH, RESULT_WIN_POS_Y, 0.0f),
								D3DXVECTOR3(RESULT_WIN_SIZE_X, RESULT_WIN_SIZE_Y, 0.0f), PRIORITY_UI, CUi::UI_TYPE_RESULT_WIN);
		break;
	default:
		break;
	}

	if (CManager::GetPlayData()->GetWinNum() != -1)
	{
		int nRandMotion = rand() % 4;
		//モーションの割り当て
		switch (nRandMotion)
		{
		case 0:
			m_apPlayer[0]->GetMotionPlayer()->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_GLAD_01);
			break;
		case 1:
			m_apPlayer[0]->GetMotionPlayer()->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_GLAD_02);
			break;
		case 2:
			m_apPlayer[0]->GetMotionPlayer()->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_GLAD_03);
			break;
		case 3:
			m_apPlayer[0]->GetMotionPlayer()->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_GLAD_04);
			break;
		default:
			break;
		}
		m_apPlayer[1]->GetMotionPlayer()->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_APPLAUSE);
	}

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

	//今再生されてるサウンドを止める
	pSound->Stop();

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

	//カウンターを加算
	m_nTitleCounter++;

	//UIの移動
	for (int nCntUi = 0; nCntUi < RESULT_MAX_UI; nCntUi++)
	{
		if (m_apUi[nCntUi] != NULL)
		{
			//位置とサイズ取得処理
			D3DXVECTOR3 pos = m_apUi[nCntUi]->GetPos();
			D3DXVECTOR3 size = m_apUi[nCntUi]->GetSize();

			switch (nCntUi)
			{
			case 0:
				if (pos.x > RESULT_PLAYERNUMBER_POS_X)
				{
					pos.x -= 30.0f;
					if (pos.x <= RESULT_PLAYERNUMBER_POS_X)
					{
						pos.x = RESULT_PLAYERNUMBER_POS_X;
					}
				}
				break;
			case 1:
				if (pos.x > RESULT_WIN_POS_X)
				{
					pos.x -= 30.0f;
					if (pos.x <= RESULT_WIN_POS_X)
					{
						pos.x = RESULT_WIN_POS_X;
					}
				}
				break;
			default:
				break;
			}
			m_apUi[nCntUi]->SetPos(pos, size);
		}
	}

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
	else if (m_nTitleCounter >= RESULT_TO_TITLE_COUNT / 3)
	{
		if (CManager::GetPlayData()->GetWinNum() != -1)
		{
			if (m_pRanking == NULL)
			{
				//ランキングの生成
				m_pRanking = CRanking::Create(D3DXVECTOR3(SCREEN_WIDTH + RANKING_POLYGON_WIDTH * MAX_SCORE_POLYGON / 2.0f, RESULT_RANKING_POSY, 0.0f),
												D3DXVECTOR3(RANKING_POLYGON_WIDTH, RANKING_POLYGON_HEIGHT, 0.0f));
			}
			for (int nCntUi = 0; nCntUi < RESULT_MAX_UI; nCntUi++)
			{
				if (m_apUi[nCntUi] != NULL)
				{
					m_apUi[nCntUi]->Uninit();
					m_apUi[nCntUi] = NULL;
				}
			}
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_START, 0) == true ||
		pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B, 0) == true)
	{
		//フェード取得処理
		CFade *pFade;
		pFade = CManager::GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			//タイトルに行く
			pFade->SetFade(CManager::MODE_TITLE);
		}
	}
}

//================================================
//描画処理
//================================================
void CResult::Draw(void)
{
	
}
