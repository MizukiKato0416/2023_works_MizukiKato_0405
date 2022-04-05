//================================================
//チュートリアル処理
//Authore:加藤瑞葵
//================================================
#include "renderer.h"
#include "tutorial.h"
#include "manager.h"
#include "bg.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "fade.h"
#include "player.h"
#include "ui_rest.h"
#include "ui_move.h"
#include "enemy_fighter.h"
#include "enemy_Item_power.h"
#include "enemy_Item_speed.h"
#include "mover.h"
#include "sound.h"


//================================================
//静的メンバ変数宣言
//================================================
bool CTutorial::m_bEnemyKill = false;
bool CTutorial::m_bPowerUp = false;
bool CTutorial::m_bSpeedUp = false;
int CTutorial::m_nSelect = SELECT_TUTORIAL_PAUSE_TYPE_NONE;
bool CTutorial::m_bPause = false;

//================================================
//デフォルトコンストラクタ
//================================================
CTutorial::CTutorial()
{
	for (int nCntUi = 0; nCntUi < MAX_TUTORIAL_UI; nCntUi++)
	{
		m_pUi[nCntUi] = NULL;
	}
	m_phase = TUTORIAL_PHASE_NONE;
	m_nNextPhaseCounter = 0;
	for (int nCntKey = 0; nCntKey < MAX_PLAYER_CONTROL_KEY; nCntKey++)
	{
		m_bPlayerMove[nCntKey] = false;
	}
	m_bPlayerShoot = false;
	m_pPlayer = NULL;
	m_pEnemyItemPower = NULL;
	m_pEnemyItemSpeed = NULL;

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
	m_nNextPhaseCounter = 0;
	for (int nCntUi = 0; nCntUi < MAX_TUTORIAL_UI; nCntUi++)
	{
		m_pUi[nCntUi] = NULL;
	}
	for (int nCntKey = 0; nCntKey < MAX_PLAYER_CONTROL_KEY; nCntKey++)
	{
		m_bPlayerMove[nCntKey] = false;
	}
	m_bPlayerShoot = false;
	m_bEnemyKill = false;
	m_bPowerUp = false;
	m_bSpeedUp = false;
	m_nSelect = SELECT_TUTORIAL_PAUSE_TYPE_CONTINUE;

	//フェーズの設定
	m_phase = TUTORIAL_PHASE_FIRST_EXPLANATION;

	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//BGMの再生
	pSound->Play(CSound::SOUND_LABEL_GAME01_BGM);
	//サウンドの音量調整
	pSound->ControllVoice(CSound::SOUND_LABEL_GAME01_BGM, 0.5f);

	//背景の生成
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(TUTORIAL_PLAYER_POS_X, TUTORIAL_PLAYER_POS_Y, 0.0f), D3DXVECTOR3(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));

	return S_OK;
}

//================================================
//終了処理
//================================================
void CTutorial::Uninit(void)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();
	//BGMの停止
	pSound->Stop(CSound::SOUND_LABEL_GAME01_BGM);

	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CTutorial::Update(void)
{
	//フェード取得処理
	CFade *pFade;
	pFade = CManager::GetFade();

	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	if (m_bPause == false)
	{
		//フェーズごとの処理
		phase();
	}

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		//ポーズに関する処理
		Pause();
	}
}

//================================================
//描画処理
//================================================
void CTutorial::Draw(void)
{
	
}

//================================================
//フェーズごとの処理
//================================================
void CTutorial::phase(void)
{
	//フェード取得処理
	CFade *pFade;
	pFade = CManager::GetFade();

	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//パッド取得処理
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	switch (m_phase)
	{
	case TUTORIAL_PHASE_FIRST_EXPLANATION:
		if (m_nNextPhaseCounter == 0)
		{
			//UIの生成
			m_pUi[0] = CUiRest::Create(D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_POS_X, UI_REST_TUTORIAL_EXPLANATION_POS_Y, 0.0f),
										D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_WIDTH, UI_REST_TUTORIAL_EXPLANATION_HEIGHT, 0.0f),
										CUiRest::UI_REST_TYPE_TUTORIAL_EXPLANATION_000);
		}
		//カウンターを加算
		m_nNextPhaseCounter++;
		//カウンターが120以上でRETURNキーまたはBボタンを押したら
		if ((pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true)
			&& m_nNextPhaseCounter >= TUTORIAL_NEXT_PHASE_COUNTER)
		{
			//SEの再生
			pSound->Play(CSound::SOUND_LABEL_NEXT_PAGE_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_NEXT_PAGE_SE, 1.2f);
			//カウンターを0にする
			m_nNextPhaseCounter = 0;
			//UIを破棄
			m_pUi[0]->Uninit();
			//次のフェーズへ
			m_phase = TUTORIAL_PHASE_PLAYER_CONTROL_EXPLANATION;
		}
		break;
	case TUTORIAL_PHASE_PLAYER_CONTROL_EXPLANATION:
		if (m_nNextPhaseCounter == 0)
		{
			//UIの生成
			m_pUi[0] = CUiRest::Create(D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_POS_X, UI_REST_TUTORIAL_EXPLANATION_POS_Y, 0.0f),
										D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_WIDTH, UI_REST_TUTORIAL_EXPLANATION_HEIGHT, 0.0f),
										CUiRest::UI_REST_TYPE_TUTORIAL_EXPLANATION_001);
		}
		//カウンターを加算
		m_nNextPhaseCounter++;
		//カウンターが120以上でRETURNキーまたはBボタンを押したら
		if ((pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true)
			&& m_nNextPhaseCounter >= TUTORIAL_NEXT_PHASE_COUNTER)
		{
			//SEの再生
			pSound->Play(CSound::SOUND_LABEL_NEXT_PAGE_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_NEXT_PAGE_SE, 1.2f);
			//カウンターを0にする
			m_nNextPhaseCounter = 0;
			//UIを破棄
			m_pUi[0]->Uninit();
			//次のフェーズへ
			m_phase = TUTORIAL_PHASE_PLAYER_CONTROL;
		}
		break;
	case TUTORIAL_PHASE_PLAYER_CONTROL:
		if (pInputKeyboard->GetPress(DIK_W) == true || pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_UP) == true)
		{
			m_bPlayerMove[0] = true;
		}
		if (pInputKeyboard->GetPress(DIK_A) == true || pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_LEFT) == true)
		{
			m_bPlayerMove[1] = true;
		}
		if (pInputKeyboard->GetPress(DIK_S) == true || pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_DOWN) == true)
		{
			m_bPlayerMove[2] = true;
		}
		if (pInputKeyboard->GetPress(DIK_D) == true || pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_RIGHT) == true)
		{
			m_bPlayerMove[3] = true;
		}

		if (m_bPlayerMove[0] == true && m_bPlayerMove[1] == true && m_bPlayerMove[2] == true && m_bPlayerMove[3] == true)
		{
			m_nNextPhaseCounter++;
			if (m_nNextPhaseCounter >= TUTORIAL_NEXT_PHASE_COUNTER)
			{
				//プレイヤーを破棄
				m_pPlayer->Uninit();
				//次のフェーズへ
				m_phase = TUTORIAL_PHASE_PLAYER_SHOOT_EXPLANATION;
				//カウンターを0にする
				m_nNextPhaseCounter = 0;
			}
		}
		break;
	case TUTORIAL_PHASE_PLAYER_SHOOT_EXPLANATION:
		if (m_nNextPhaseCounter == 0)
		{
			//SEの再生
			pSound->Play(CSound::SOUND_LABEL_NEXT_PAGE_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_NEXT_PAGE_SE, 1.2f);
			//プレイヤーの生成
			m_pPlayer = CPlayer::Create(D3DXVECTOR3(TUTORIAL_PLAYER_POS_X, TUTORIAL_PLAYER_POS_Y, 0.0f),
										D3DXVECTOR3(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));

			//敵の生成
			CEnemyFighter::Create(D3DXVECTOR3(TUTORIAL_ENEMY_POS_X, TUTORIAL_ENEMY_POS_Y, 0.0f),
									D3DXVECTOR3(ENEMY_FIGHTER_WIDTH, ENEMY_FIGHTER_HEIGHT, 0.0f),
									D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									CMover::MOVER_TYPE_NONE);

			//UIの生成
			m_pUi[0] = CUiRest::Create(D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_POS_X, UI_REST_TUTORIAL_EXPLANATION_POS_Y, 0.0f),
										D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_WIDTH, UI_REST_TUTORIAL_EXPLANATION_HEIGHT, 0.0f),
										CUiRest::UI_REST_TYPE_TUTORIAL_EXPLANATION_002);
		}
		//カウンターを加算
		m_nNextPhaseCounter++;
		//カウンターが120以上でRETURNキーまたはBボタンを押したら
		if ((pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true)
			&& m_nNextPhaseCounter >= TUTORIAL_NEXT_PHASE_COUNTER)
		{
			//SEの再生
			pSound->Play(CSound::SOUND_LABEL_NEXT_PAGE_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_NEXT_PAGE_SE, 1.2f);
			//カウンターを0にする
			m_nNextPhaseCounter = 0;
			//UIを破棄
			m_pUi[0]->Uninit();
			//次のフェーズへ
			m_phase = TUTORIAL_PHASE_PLAYER_SHOOT;
		}
		break;
	case TUTORIAL_PHASE_PLAYER_SHOOT:
		if (m_bEnemyKill == true)
		{
			//カウンターを加算
			m_nNextPhaseCounter++;
			if (m_nNextPhaseCounter >= TUTORIAL_NEXT_PHASE_COUNTER)
			{
				//プレイヤーを破棄
				m_pPlayer->Uninit();
				//次のフェーズへ
				m_phase = TUTORIAL_PHASE_ITEM_EXPLANATION_000;
				//カウンターを0にする
				m_nNextPhaseCounter = 0;
			}
		}
		break;
	case TUTORIAL_PHASE_ITEM_EXPLANATION_000:
		if (m_nNextPhaseCounter == 0)
		{
			//SEの再生
			pSound->Play(CSound::SOUND_LABEL_NEXT_PAGE_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_NEXT_PAGE_SE, 1.2f);
			//プレイヤーの生成
			m_pPlayer = CPlayer::Create(D3DXVECTOR3(TUTORIAL_PLAYER_POS_X, TUTORIAL_PLAYER_POS_Y, 0.0f),
										D3DXVECTOR3(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));

			//UIの生成
			m_pUi[0] = CUiRest::Create(D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_POS_X, UI_REST_TUTORIAL_EXPLANATION_POS_Y, 0.0f),
										D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_WIDTH, UI_REST_TUTORIAL_EXPLANATION_HEIGHT, 0.0f),
										CUiRest::UI_REST_TYPE_TUTORIAL_EXPLANATION_003);
		}
		//カウンターを加算
		m_nNextPhaseCounter++;
		//カウンターが120以上でRETURNキーまたはBボタンを押したら
		if ((pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true) &&
			m_nNextPhaseCounter >= TUTORIAL_NEXT_PHASE_COUNTER)
		{
			//SEの再生
			pSound->Play(CSound::SOUND_LABEL_NEXT_PAGE_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_NEXT_PAGE_SE, 1.2f);
			//カウンターを0にする
			m_nNextPhaseCounter = 0;
			//UIを破棄
			m_pUi[0]->Uninit();
			//次のフェーズへ
			m_phase = TUTORIAL_PHASE_ITEM_EXPLANATION_001;
		}
		break;
	case TUTORIAL_PHASE_ITEM_EXPLANATION_001:
		if (m_nNextPhaseCounter == 0)
		{
			//UIの生成
			m_pUi[0] = CUiRest::Create(D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_POS_X, UI_REST_TUTORIAL_EXPLANATION_POS_Y, 0.0f),
										D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_WIDTH, UI_REST_TUTORIAL_EXPLANATION_HEIGHT, 0.0f),
										CUiRest::UI_REST_TYPE_TUTORIAL_EXPLANATION_004);
			//敵の生成
			m_pEnemyItemPower = CEnemyItemPower::Create(D3DXVECTOR3(TUTORIAL_ENEMY_ITEM_POWER_POS_X, TUTORIAL_ENEMY_ITEM_POWER_POS_Y, 0.0f),
														D3DXVECTOR3(ENEMY_ITEM_POWER_WIDTH, ENEMY_ITEM_POWER_HEIGHT, 0.0f),
														D3DXVECTOR3(0.0f, 0.0f, 0.0f),
														CMover::MOVER_TYPE_NONE);

			//敵の生成
			m_pEnemyItemSpeed = CEnemyItemSpeed::Create(D3DXVECTOR3(TUTORIAL_ENEMY_ITEM_SPEED_POS_X, TUTORIAL_ENEMY_ITEM_SPEED_POS_Y, 0.0f),
														D3DXVECTOR3(ENEMY_ITEM_SPEED_WIDTH, ENEMY_ITEM_SPEED_HEIGHT, 0.0f),
														D3DXVECTOR3(0.0f, 0.0f, 0.0f),
														CMover::MOVER_TYPE_NONE);
		}
		//カウンターを加算
		m_nNextPhaseCounter++;
		//カウンターが120以上でRETURNキーまたはBボタンを押したら
		if ((pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true) &&
			m_nNextPhaseCounter >= TUTORIAL_NEXT_PHASE_COUNTER)
		{
			//SEの再生
			pSound->Play(CSound::SOUND_LABEL_NEXT_PAGE_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_NEXT_PAGE_SE, 1.2f);
			//カウンターを0にする
			m_nNextPhaseCounter = 0;
			//UIを破棄
			m_pUi[0]->Uninit();
			//次のフェーズへ
			m_phase = TUTORIAL_PHASE_PLAYER_LEVEL_UP_SHOOT;
		}
		break;
	case TUTORIAL_PHASE_PLAYER_LEVEL_UP_SHOOT:
		//パワーアップ、スピードアップした状態なら
		if (m_bPowerUp == true && m_bSpeedUp == true)
		{
			//カウンターを加算
			m_nNextPhaseCounter++;
			if (m_nNextPhaseCounter >= TUTORIAL_NEXT_PHASE_COUNTER)
			{
				//プレイヤーを破棄
				m_pPlayer->Uninit();
				//次のフェーズへ
				m_phase = TUTORIAL_PHASE_FINISH;
				//カウンターを0にする
				m_nNextPhaseCounter = 0;
			}
		}
		break;
	case TUTORIAL_PHASE_FINISH:
		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			if (m_nNextPhaseCounter == 0)
			{
				//SEの再生
				pSound->Play(CSound::SOUND_LABEL_NEXT_PAGE_SE);
				//サウンドの音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_NEXT_PAGE_SE, 1.2f);
				//プレイヤーの生成
				m_pPlayer = CPlayer::Create(D3DXVECTOR3(TUTORIAL_PLAYER_POS_X, TUTORIAL_PLAYER_POS_Y, 0.0f),
										D3DXVECTOR3(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));

				//UIの生成
				m_pUi[0] = CUiRest::Create(D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_POS_X, UI_REST_TUTORIAL_EXPLANATION_POS_Y, 0.0f),
											D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_WIDTH, UI_REST_TUTORIAL_EXPLANATION_HEIGHT, 0.0f),
											CUiRest::UI_REST_TYPE_TUTORIAL_EXPLANATION_005);
			}
			//カウンターを加算
			m_nNextPhaseCounter++;
			if ((pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true) &&
				m_nNextPhaseCounter >= TUTORIAL_NEXT_PHASE_COUNTER)
			{
				//SEの再生
				pSound->Play(CSound::SOUND_LABEL_NEXT_PAGE_SE);
				//サウンドの音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_NEXT_PAGE_SE, 1.2f);
				//カウンターを0にする
				m_nNextPhaseCounter = 0;
				//メニューに戻る
				pFade->SetFade(CManager::MODE_MENU);
			}
		}
		break;
	default:
		break;
	}
}

//================================================
//敵を倒したのを設定する処理
//================================================
void CTutorial::SetEnemyKill(bool bEnemyKill)
{
	m_bEnemyKill = bEnemyKill;
}

//================================================
//パワーアップしたのを設定する処理
//================================================
void CTutorial::SetPowerUp(bool bPowerUp)
{
	m_bPowerUp = bPowerUp;
}

//================================================
//スピードアップしたのを設定する処理
//================================================
void CTutorial::SetSpeedUp(bool bSpeedUp)
{
	m_bSpeedUp = bSpeedUp;
}

//=============================================================================
// ポーズ取得処理
//=============================================================================
bool CTutorial::GetPause(void)
{
	return m_bPause;
}

//=============================================================================
// 選択肢取得処理
//=============================================================================
int CTutorial::GetSelect(void)
{
	return m_nSelect;
}

//=============================================================================
// フェーズ取得処理
//=============================================================================
CTutorial::TUTORIAL_PHASE CTutorial::GetPhase(void)
{
	return m_phase;
}

//=============================================================================
// ポーズに関する処理
//=============================================================================
void CTutorial::Pause(void)
{
	//フェード取得処理
	CFade *pFade;
	pFade = CManager::GetFade();

	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//パッド取得処理
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//Pボタンを押したら
	if (pInputKeyboard->GetTrigger(DIK_P) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_START) == true)
	{
		if (m_bPause == false)
		{
			//SEの再生
			pSound->Play(CSound::SOUND_LABEL_PAUSE_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_PAUSE_SE, 4.0f);

			//ポーズにする
			m_bPause = true;
			//UIの生成
			m_pUi[1] = CUiRest::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(UI_REST_PAUSE_WIDTH, UI_REST_PAUSE_HEIGHT, 0.0f),
										CUiRest::UI_REST_TYPE_PAUSE);

			m_pUi[2] = CUiMove::Create(D3DXVECTOR3(UI_PAUSE_CONTINUE_POS_X, UI_PAUSE_CONTINUE_POS_Y, 0.0f), D3DXVECTOR3(UI_PAUSE_CONTINUE_WIDTH, UI_PAUSE_CONTINUE_HEIGHT, 0.0f),
										D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_PAUSE_CONTINUE);

			m_pUi[3] = CUiMove::Create(D3DXVECTOR3(UI_PAUSE_EXIT_POS_X, UI_PAUSE_EXIT_POS_Y, 0.0f), D3DXVECTOR3(UI_PAUSE_EXIT_WIDTH, UI_PAUSE_EXIT_HEIGHT, 0.0f),
										D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_PAUSE_EXIT);
		}
		else
		{
			//SEの再生
			pSound->Play(CSound::SOUND_LABEL_EXIT_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_EXIT_SE, 1.2f);
			//UIを消す
			for (int nCntPauseUi = 1; nCntPauseUi < MAX_TUTORIL_PAUSE_UI + 1; nCntPauseUi++)
			{
				m_pUi[nCntPauseUi]->Uninit();
			}
			//ポーズを解除する
			m_bPause = false;
			//選択肢をcontinueに戻す
			m_nSelect = SELECT_TUTORIAL_PAUSE_TYPE_CONTINUE;
		}
	}


	if (m_bPause == true)
	{
		//ポーズ画面だったら
		//選択処理
		if (pInputKeyboard->GetTrigger(DIK_UP) == true || pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_UP) == true ||
			pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP) == true)
		{
			m_nSelect--;
			if (m_nSelect < SELECT_TUTORIAL_PAUSE_TYPE_CONTINUE)
			{
				m_nSelect = SELECT_TUTORIAL_PAUSE_TYPE_CONTINUE;
			}
			else
			{
				//BGMの再生
				pSound->Play(CSound::SOUND_LABEL_CURSOR_SE);
				//サウンドの音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_CURSOR_SE, 0.8f);
			}
		}
		else if (pInputKeyboard->GetTrigger(DIK_DOWN) == true || pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_DOWN) == true ||
					pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN) == true)
		{
			m_nSelect++;
			if (m_nSelect > SELECT_TUTORIAL_PAUSE_TYPE_EXIT)
			{
				m_nSelect = SELECT_TUTORIAL_PAUSE_TYPE_EXIT;
			}
			else
			{
				//BGMの再生
				pSound->Play(CSound::SOUND_LABEL_CURSOR_SE);
				//サウンドの音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_CURSOR_SE, 0.8f);
			}
		}

		//決定処理
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true)
		{
			switch (m_nSelect)
			{
			case SELECT_TUTORIAL_PAUSE_TYPE_CONTINUE:
				//SEの再生
				pSound->Play(CSound::SOUND_LABEL_EXIT_SE);
				//サウンドの音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_EXIT_SE, 1.2f);
				//UIを消す
				for (int nCntPauseUi = 1; nCntPauseUi < MAX_TUTORIL_PAUSE_UI + 1; nCntPauseUi++)
				{
					m_pUi[nCntPauseUi]->Uninit();
				}
				//選択肢をcontinueに戻す
				m_nSelect = SELECT_TUTORIAL_PAUSE_TYPE_CONTINUE;
				//ポーズを解除する
				m_bPause = false;
				break;
			case SELECT_TUTORIAL_PAUSE_TYPE_EXIT:
				//SEの再生
				pSound->Play(CSound::SOUND_LABEL_EXIT_TUTORIAL_SE);
				//サウンドの音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_EXIT_TUTORIAL_SE, 2.4f);
				//メニュー画面に戻る
				pFade->SetFade(CManager::MODE_MENU);
				//UIを消す
				for (int nCntPauseUi = 1; nCntPauseUi < MAX_TUTORIL_PAUSE_UI + 1; nCntPauseUi++)
				{
					m_pUi[nCntPauseUi]->Uninit();
				}
				//選択肢をcontinueに戻す
				m_nSelect = SELECT_TUTORIAL_PAUSE_TYPE_CONTINUE;
				//ポーズを解除する
				m_bPause = false;
				break;
			default:
				break;
			}
		}
	}
}