//================================================
//ゲーム01処理
//Authore:加藤瑞葵
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "renderer.h"
#include "game01.h"
#include "manager.h"
#include "player.h"
#include "bullet_player.h"
#include "explosion.h"
#include "bg.h"
#include "enemy_fighter.h"
#include "enemy_ufo.h"
#include "enemy_Item_power.h"
#include "enemy_Item_speed.h"
#include "enemy_sphere.h"
#include "enemy.h"
#include "score.h"
#include "number.h"
#include "polygon.h"
#include "life.h"
#include "effect.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "fade.h"
#include "boss.h"
#include "mover.h"
#include "ui_rest.h"
#include "ui_move.h"
#include "sound.h"

//================================================
//静的メンバ変数宣言
//================================================
CScore *CGame01::m_pScore = NULL;
CPolygon *CGame01::m_pPolygon = NULL;
CLife *CGame01::m_pLife = NULL;
CBoss *CGame01::m_pBoss = NULL;
CUi *CGame01::m_pUi[MAX_PAUSE_UI] = {};

int CGame01::m_nFrame = 0;
int CGame01::m_nFrameEnemy[STAGE01_MAX_ENEMY] = { 0 };
int CGame01::m_nFrameBoss[STAGE01_MAX_BOSS] = { 0 };
D3DXVECTOR3 CGame01::m_enemyPos[STAGE01_MAX_ENEMY] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f) };
D3DXVECTOR3 CGame01::m_enemyMove[STAGE01_MAX_ENEMY] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f) };
D3DXVECTOR3 CGame01::m_bossPos[STAGE01_MAX_BOSS] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f) };
CEnemy::ENEMY_TYPE CGame01::m_enemyType[STAGE01_MAX_ENEMY] = { CEnemy::ENEMY_TYPE_NONE };
CMover::MOVER_TYPE CGame01::m_moverType[STAGE01_MAX_ENEMY] = { CMover::MOVER_TYPE_NONE };
int CGame01::m_nSelect = SELECT_GAME01_PAUSE_TYPE_NONE;
bool CGame01::m_bPause = false;
int CGame01::m_nFinishCounter = 0;

//================================================
//デフォルトコンストラクタ
//================================================
CGame01::CGame01()
{
	m_state = CGame01::GAME_STATE_NONE;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CGame01::~CGame01()
{

}

//================================================
//初期化処理
//================================================
HRESULT CGame01::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//変数の初期化
	m_nFrame = 0;
	for (int nCntEnemy = 0; nCntEnemy < STAGE01_MAX_ENEMY; nCntEnemy++)
	{
		m_nFrameEnemy[nCntEnemy] = 0;
		m_enemyPos[nCntEnemy] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_enemyType[nCntEnemy] = CEnemy::ENEMY_TYPE_NONE;
	}
	m_nSelect = SELECT_GAME01_PAUSE_TYPE_CONTINUE;
	m_nFinishCounter = 0;
	m_state = CGame01::GAME_STATE_GAME;

	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//BGMの再生
	pSound->Play(CSound::SOUND_LABEL_GAME01_BGM);
	//サウンドの音量調整
	pSound->ControllVoice(CSound::SOUND_LABEL_GAME01_BGM, 0.5f);

	//背景の生成
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	//スコアの生成
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - (SCORE_POLYGON_WIDTH * MAX_SCORE_POLYGON / 2.0f), SCORE_POLYGON_HEIGHT / 2.0f, 0.0f),
								D3DXVECTOR3(SCORE_POLYGON_WIDTH, SCORE_POLYGON_HEIGHT, 0.0f));

	//ライフの生成
	m_pLife = CLife::Create(D3DXVECTOR3(0.0f + (LIFE_POLYGON_WIDTH * START_LIFE_POLYGON / 2.0f), LIFE_POLYGON_HEIGHT / 2.0f, 0.0f),
							D3DXVECTOR3(LIFE_POLYGON_WIDTH, LIFE_POLYGON_HEIGHT, 0.0f));

	//プレイヤーの生成
	CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 400.0f, 0.0f), D3DXVECTOR3(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));


	//ファイル読み込みに使う変数
	char cReadStageText[MAX_STRINGS];
	int nCntEnemy = 0;			//敵カウント用
	int nCntBoss = 0;			//ボスカウント用
	//txtファイル読み込み
	FILE *pFile;
	pFile = fopen("data/STAGE/stage00.txt", "r");
	while (fgets(cReadStageText, MAX_STRINGS, pFile) != NULL)
	{
		if (strncmp("ENEMYSET", cReadStageText, 7) == 0)
		{
			fscanf(pFile, "%*s%*s%f%f", &m_enemyPos[nCntEnemy].x, &m_enemyPos[nCntEnemy].y);	//位置
			fscanf(pFile, "%*s%*s%f%f", &m_enemyMove[nCntEnemy].x, &m_enemyMove[nCntEnemy].y);	//移動量
			fscanf(pFile, "%*s%*s%d", &m_enemyType[nCntEnemy]);									//種類
			fscanf(pFile, "%*s%*s%d", &m_moverType[nCntEnemy]);									//動きの種類
			fscanf(pFile, "%*s%*s%d", &m_nFrameEnemy[nCntEnemy]);								//出すタイミング
			nCntEnemy++;
		}
		else if (strncmp("BOSSSET", cReadStageText, 6) == 0)
		{
			fscanf(pFile, "%*s%*s%f%f", &m_bossPos[nCntBoss].x, &m_bossPos[nCntBoss].y);		//位置
			fscanf(pFile, "%*s%*s%d", &m_nFrameBoss[nCntBoss]);									//出すタイミング
			nCntBoss++;
		}
	}
	
	fclose(pFile);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CGame01::Uninit(void)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();
	//BGMの停止
	pSound->Stop(CSound::SOUND_LABEL_BOSS_BGM);
	pSound->Stop(CSound::SOUND_LABEL_GAME01_BGM);

	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CGame01::Update(void)
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

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		//Pボタンまたはスタートボタンを押したら
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
				m_pUi[0] = CUiRest::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(UI_REST_PAUSE_WIDTH, UI_REST_PAUSE_HEIGHT, 0.0f),
											CUiRest::UI_REST_TYPE_PAUSE);

				m_pUi[1] = CUiMove::Create(D3DXVECTOR3(UI_PAUSE_CONTINUE_POS_X, UI_PAUSE_CONTINUE_POS_Y, 0.0f), D3DXVECTOR3(UI_PAUSE_CONTINUE_WIDTH, UI_PAUSE_CONTINUE_HEIGHT, 0.0f),
											D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_PAUSE_CONTINUE);

				m_pUi[2] = CUiMove::Create(D3DXVECTOR3(UI_PAUSE_EXIT_POS_X, UI_PAUSE_EXIT_POS_Y, 0.0f), D3DXVECTOR3(UI_PAUSE_EXIT_WIDTH, UI_PAUSE_EXIT_HEIGHT, 0.0f),
											D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_PAUSE_EXIT);
			}
			else
			{
				//SEの再生
				pSound->Play(CSound::SOUND_LABEL_EXIT_SE);
				//サウンドの音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_EXIT_SE, 1.2f);

				//UIを消す
				for (int nCntPauseUi = 0; nCntPauseUi < MAX_PAUSE_UI; nCntPauseUi++)
				{
					m_pUi[nCntPauseUi]->Uninit();
				}
				//ポーズを解除する
				m_bPause = false;
				//選択肢をcontinueに戻す
				m_nSelect = SELECT_GAME01_PAUSE_TYPE_CONTINUE;
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
				if (m_nSelect < SELECT_GAME01_PAUSE_TYPE_CONTINUE)
				{
					m_nSelect = SELECT_GAME01_PAUSE_TYPE_CONTINUE;
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
				if (m_nSelect > SELECT_GAME01_PAUSE_TYPE_EXIT)
				{
					m_nSelect = SELECT_GAME01_PAUSE_TYPE_EXIT;
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
				case SELECT_GAME01_PAUSE_TYPE_CONTINUE:
					//SEの再生
					pSound->Play(CSound::SOUND_LABEL_EXIT_SE);
					//サウンドの音量調整
					pSound->ControllVoice(CSound::SOUND_LABEL_EXIT_SE, 1.2f);

					//UIを消す
					for (int nCntPauseUi = 0; nCntPauseUi < MAX_PAUSE_UI; nCntPauseUi++)
					{
						m_pUi[nCntPauseUi]->Uninit();
					}
					//選択肢をcontinueに戻す
					m_nSelect = SELECT_GAME01_PAUSE_TYPE_CONTINUE;
					//ポーズを解除する
					m_bPause = false;
					break;
				case SELECT_GAME01_PAUSE_TYPE_EXIT:
					//SEの再生
					pSound->Play(CSound::SOUND_LABEL_EXIT_TUTORIAL_SE);
					//サウンドの音量調整
					pSound->ControllVoice(CSound::SOUND_LABEL_EXIT_TUTORIAL_SE, 2.4f);
					//メニュー画面に戻る
					pFade->SetFade(CManager::MODE_MENU);
					//UIを消す
					for (int nCntPauseUi = 0; nCntPauseUi < MAX_PAUSE_UI; nCntPauseUi++)
					{
						m_pUi[nCntPauseUi]->Uninit();
					}
					//選択肢をcontinueに戻す
					m_nSelect = SELECT_GAME01_PAUSE_TYPE_CONTINUE;
					//ポーズを解除する
					m_bPause = false;
					break;
				default:
					break;
				}
			}
		}


		//ポーズ画面じゃなかったら
		if (m_bPause == false)
		{
			m_nFrame++;

			//敵の生成
			for (int nCntEnemy = 0; nCntEnemy < STAGE01_MAX_ENEMY; nCntEnemy++)
			{
				if (m_nFrameEnemy[nCntEnemy] == m_nFrame)
				{
					switch (m_enemyType[nCntEnemy])
					{
					case CEnemy::ENEMY_TYPE_FIGHTER:
						CEnemyFighter::Create(D3DXVECTOR3(m_enemyPos[nCntEnemy].x, m_enemyPos[nCntEnemy].y, 0.0f),
												D3DXVECTOR3(ENEMY_FIGHTER_WIDTH, ENEMY_FIGHTER_HEIGHT, 0.0f),
												D3DXVECTOR3(m_enemyMove[nCntEnemy].x, m_enemyMove[nCntEnemy].y, 0.0f),
												m_moverType[nCntEnemy]);
						break;
					case CEnemy::ENEMY_TYPE_UFO:
						CEnemyUfo::Create(D3DXVECTOR3(m_enemyPos[nCntEnemy].x, m_enemyPos[nCntEnemy].y, 0.0f),
											D3DXVECTOR3(ENEMY_UFO_WIDTH, ENEMY_UFO_HEIGHT, 0.0f),
											D3DXVECTOR3(m_enemyMove[nCntEnemy].x, m_enemyMove[nCntEnemy].y, 0.0f),
											m_moverType[nCntEnemy]);
						break;
					case CEnemy::ENEMY_TYPE_ITEM_POWER:
						CEnemyItemPower::Create(D3DXVECTOR3(m_enemyPos[nCntEnemy].x, m_enemyPos[nCntEnemy].y, 0.0f),
											D3DXVECTOR3(ENEMY_ITEM_POWER_WIDTH, ENEMY_ITEM_POWER_HEIGHT, 0.0f),
											D3DXVECTOR3(m_enemyMove[nCntEnemy].x, m_enemyMove[nCntEnemy].y, 0.0f),
											m_moverType[nCntEnemy]);
						break;
					case CEnemy::ENEMY_TYPE_ITEM_SPEED:
						CEnemyItemSpeed::Create(D3DXVECTOR3(m_enemyPos[nCntEnemy].x, m_enemyPos[nCntEnemy].y, 0.0f),
											D3DXVECTOR3(ENEMY_ITEM_SPEED_WIDTH, ENEMY_ITEM_SPEED_HEIGHT, 0.0f),
											D3DXVECTOR3(m_enemyMove[nCntEnemy].x, m_enemyMove[nCntEnemy].y, 0.0f),
											m_moverType[nCntEnemy]);
						break;
					case CEnemy::ENEMY_TYPE_SPHERE:
						CEnemySphere::Create(D3DXVECTOR3(m_enemyPos[nCntEnemy].x, m_enemyPos[nCntEnemy].y, 0.0f),
												D3DXVECTOR3(ENEMY_SPHERE_WIDTH, ENEMY_SPHERE_HEIGHT, 0.0f),
												D3DXVECTOR3(m_enemyMove[nCntEnemy].x, m_enemyMove[nCntEnemy].y, 0.0f),
												m_moverType[nCntEnemy]);
						break;
					default:
						break;
					}
				}
			}
			//ボスの生成
			for (int nCntBoss = 0; nCntBoss < STAGE01_MAX_BOSS; nCntBoss++)
			{
				if (m_nFrameBoss[nCntBoss] == m_nFrame)
				{
					m_pBoss = CBoss::Create(D3DXVECTOR3(m_bossPos[nCntBoss].x, m_bossPos[nCntBoss].y, 0.0f),
											D3DXVECTOR3(1.0f, 1.0f, 1.0f),
											D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					//BGMの停止
					pSound->Stop(CSound::SOUND_LABEL_GAME01_BGM);
					//BGMの再生
					pSound->Play(CSound::SOUND_LABEL_BOSS_BGM);
					//サウンドの音量調整
					pSound->ControllVoice(CSound::SOUND_LABEL_BOSS_BGM, 0.5f);
				}
			}

			//状態による処理分け
			State();
		}
	}
}

//================================================
//描画処理
//================================================
void CGame01::Draw(void)
{
	
}

//=============================================================================
// 経過フレーム数取得処理
//=============================================================================
int CGame01::GetFrame(void)
{
	return m_nFrame;
}

//=============================================================================
// score取得処理
//=============================================================================
CScore* CGame01::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// polygon取得処理
//=============================================================================
CPolygon* CGame01::GetPolygon(void)
{
	return m_pPolygon;
}

//=============================================================================
// life取得処理
//=============================================================================
CLife* CGame01::GetLife(void)
{
	return m_pLife;
}

//=============================================================================
// boss取得処理
//=============================================================================
CBoss* CGame01::GetBoss(void)
{
	return m_pBoss;
}

//=============================================================================
// ポーズ取得処理
//=============================================================================
bool CGame01::GetPause(void)
{
	return m_bPause;
}

//=============================================================================
// 選択肢取得処理
//=============================================================================
int CGame01::GetSelect(void)
{
	return m_nSelect;
}

//=============================================================================
// ゲームの状態取得処理
//=============================================================================
CGame01::GAME_STATE CGame01::GetState(void)
{
	return m_state;
}

//=============================================================================
// ゲームの状態設定処理
//=============================================================================
void CGame01::SetState(CGame01::GAME_STATE state)
{
	m_state = state;
}

//=============================================================================
// 状態による処理わけ
//=============================================================================
void CGame01::State(void)
{
	//フェード取得処理
	CFade *pFade;
	pFade = CManager::GetFade();

	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	switch (m_state)
	{
	case GAME_STATE_GAME:
		break;
	case GAME_STATE_CLEAR:
		//カウンターを加算
		m_nFinishCounter++;
		//一定時間になったらgameClearのUIを生成
		if (m_nFinishCounter == 500)
		{
			//サウンドの再生
			pSound->Play(CSound::SOUND_LABEL_GAME_CLEAR_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_GAME_CLEAR_SE, 1.8f);

			CUiRest::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
							D3DXVECTOR3(UI_REST_GAME_CLEAR_WIDTH, UI_REST_GAME_CLEAR_HEIGHT, 0.0f),
							CUiRest::UI_REST_TYPE_GAME_CLEAR);
		}
		else if(m_nFinishCounter >= 800)
		{
			//リザルト画面に行く
			pFade->SetFade(CManager::MODE_RESULT);
		}
		break;
	case GAME_STATE_OVER:
		//カウンターを加算
		m_nFinishCounter++;
		//一定時間になったらgameOverのUIを生成
		if (m_nFinishCounter == 300)
		{
			CUiRest::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
							D3DXVECTOR3(UI_REST_GAME_OVER_WIDTH, UI_REST_GAME_OVER_HEIGHT, 0.0f),
							CUiRest::UI_REST_TYPE_GAME_OVER);
		}
		else if (m_nFinishCounter >= 600)
		{
			//メニュー画面に戻る
			pFade->SetFade(CManager::MODE_MENU);
		}
		break;
	default:
		break;
	}
}

//=============================================================================
//終了してからのフレーム数
//=============================================================================
int CGame01::GetFinishCounter(void)
{
	return m_nFinishCounter;
}