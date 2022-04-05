//================================================
//�Q�[��01����
//Authore:��������
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
//�ÓI�����o�ϐ��錾
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
//�f�t�H���g�R���X�g���N�^
//================================================
CGame01::CGame01()
{
	m_state = CGame01::GAME_STATE_NONE;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CGame01::~CGame01()
{

}

//================================================
//����������
//================================================
HRESULT CGame01::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�ϐ��̏�����
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

	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//BGM�̍Đ�
	pSound->Play(CSound::SOUND_LABEL_GAME01_BGM);
	//�T�E���h�̉��ʒ���
	pSound->ControllVoice(CSound::SOUND_LABEL_GAME01_BGM, 0.5f);

	//�w�i�̐���
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	//�X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - (SCORE_POLYGON_WIDTH * MAX_SCORE_POLYGON / 2.0f), SCORE_POLYGON_HEIGHT / 2.0f, 0.0f),
								D3DXVECTOR3(SCORE_POLYGON_WIDTH, SCORE_POLYGON_HEIGHT, 0.0f));

	//���C�t�̐���
	m_pLife = CLife::Create(D3DXVECTOR3(0.0f + (LIFE_POLYGON_WIDTH * START_LIFE_POLYGON / 2.0f), LIFE_POLYGON_HEIGHT / 2.0f, 0.0f),
							D3DXVECTOR3(LIFE_POLYGON_WIDTH, LIFE_POLYGON_HEIGHT, 0.0f));

	//�v���C���[�̐���
	CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 400.0f, 0.0f), D3DXVECTOR3(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));


	//�t�@�C���ǂݍ��݂Ɏg���ϐ�
	char cReadStageText[MAX_STRINGS];
	int nCntEnemy = 0;			//�G�J�E���g�p
	int nCntBoss = 0;			//�{�X�J�E���g�p
	//txt�t�@�C���ǂݍ���
	FILE *pFile;
	pFile = fopen("data/STAGE/stage00.txt", "r");
	while (fgets(cReadStageText, MAX_STRINGS, pFile) != NULL)
	{
		if (strncmp("ENEMYSET", cReadStageText, 7) == 0)
		{
			fscanf(pFile, "%*s%*s%f%f", &m_enemyPos[nCntEnemy].x, &m_enemyPos[nCntEnemy].y);	//�ʒu
			fscanf(pFile, "%*s%*s%f%f", &m_enemyMove[nCntEnemy].x, &m_enemyMove[nCntEnemy].y);	//�ړ���
			fscanf(pFile, "%*s%*s%d", &m_enemyType[nCntEnemy]);									//���
			fscanf(pFile, "%*s%*s%d", &m_moverType[nCntEnemy]);									//�����̎��
			fscanf(pFile, "%*s%*s%d", &m_nFrameEnemy[nCntEnemy]);								//�o���^�C�~���O
			nCntEnemy++;
		}
		else if (strncmp("BOSSSET", cReadStageText, 6) == 0)
		{
			fscanf(pFile, "%*s%*s%f%f", &m_bossPos[nCntBoss].x, &m_bossPos[nCntBoss].y);		//�ʒu
			fscanf(pFile, "%*s%*s%d", &m_nFrameBoss[nCntBoss]);									//�o���^�C�~���O
			nCntBoss++;
		}
	}
	
	fclose(pFile);

	return S_OK;
}

//================================================
//�I������
//================================================
void CGame01::Uninit(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();
	//BGM�̒�~
	pSound->Stop(CSound::SOUND_LABEL_BOSS_BGM);
	pSound->Stop(CSound::SOUND_LABEL_GAME01_BGM);

	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CGame01::Update(void)
{
	//�t�F�[�h�擾����
	CFade *pFade;
	pFade = CManager::GetFade();

	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�p�b�h�擾����
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		//P�{�^���܂��̓X�^�[�g�{�^������������
		if (pInputKeyboard->GetTrigger(DIK_P) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_START) == true)
		{
			if (m_bPause == false)
			{
				//SE�̍Đ�
				pSound->Play(CSound::SOUND_LABEL_PAUSE_SE);
				//�T�E���h�̉��ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_PAUSE_SE, 4.0f);

				//�|�[�Y�ɂ���
				m_bPause = true;
				//UI�̐���
				m_pUi[0] = CUiRest::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(UI_REST_PAUSE_WIDTH, UI_REST_PAUSE_HEIGHT, 0.0f),
											CUiRest::UI_REST_TYPE_PAUSE);

				m_pUi[1] = CUiMove::Create(D3DXVECTOR3(UI_PAUSE_CONTINUE_POS_X, UI_PAUSE_CONTINUE_POS_Y, 0.0f), D3DXVECTOR3(UI_PAUSE_CONTINUE_WIDTH, UI_PAUSE_CONTINUE_HEIGHT, 0.0f),
											D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_PAUSE_CONTINUE);

				m_pUi[2] = CUiMove::Create(D3DXVECTOR3(UI_PAUSE_EXIT_POS_X, UI_PAUSE_EXIT_POS_Y, 0.0f), D3DXVECTOR3(UI_PAUSE_EXIT_WIDTH, UI_PAUSE_EXIT_HEIGHT, 0.0f),
											D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_PAUSE_EXIT);
			}
			else
			{
				//SE�̍Đ�
				pSound->Play(CSound::SOUND_LABEL_EXIT_SE);
				//�T�E���h�̉��ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_EXIT_SE, 1.2f);

				//UI������
				for (int nCntPauseUi = 0; nCntPauseUi < MAX_PAUSE_UI; nCntPauseUi++)
				{
					m_pUi[nCntPauseUi]->Uninit();
				}
				//�|�[�Y����������
				m_bPause = false;
				//�I������continue�ɖ߂�
				m_nSelect = SELECT_GAME01_PAUSE_TYPE_CONTINUE;
			}
		}


		if (m_bPause == true)
		{
			//�|�[�Y��ʂ�������
			//�I������
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
					//BGM�̍Đ�
					pSound->Play(CSound::SOUND_LABEL_CURSOR_SE);
					//�T�E���h�̉��ʒ���
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
					//BGM�̍Đ�
					pSound->Play(CSound::SOUND_LABEL_CURSOR_SE);
					//�T�E���h�̉��ʒ���
					pSound->ControllVoice(CSound::SOUND_LABEL_CURSOR_SE, 0.8f);
				}
			}

			//���菈��
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true)
			{
				switch (m_nSelect)
				{
				case SELECT_GAME01_PAUSE_TYPE_CONTINUE:
					//SE�̍Đ�
					pSound->Play(CSound::SOUND_LABEL_EXIT_SE);
					//�T�E���h�̉��ʒ���
					pSound->ControllVoice(CSound::SOUND_LABEL_EXIT_SE, 1.2f);

					//UI������
					for (int nCntPauseUi = 0; nCntPauseUi < MAX_PAUSE_UI; nCntPauseUi++)
					{
						m_pUi[nCntPauseUi]->Uninit();
					}
					//�I������continue�ɖ߂�
					m_nSelect = SELECT_GAME01_PAUSE_TYPE_CONTINUE;
					//�|�[�Y����������
					m_bPause = false;
					break;
				case SELECT_GAME01_PAUSE_TYPE_EXIT:
					//SE�̍Đ�
					pSound->Play(CSound::SOUND_LABEL_EXIT_TUTORIAL_SE);
					//�T�E���h�̉��ʒ���
					pSound->ControllVoice(CSound::SOUND_LABEL_EXIT_TUTORIAL_SE, 2.4f);
					//���j���[��ʂɖ߂�
					pFade->SetFade(CManager::MODE_MENU);
					//UI������
					for (int nCntPauseUi = 0; nCntPauseUi < MAX_PAUSE_UI; nCntPauseUi++)
					{
						m_pUi[nCntPauseUi]->Uninit();
					}
					//�I������continue�ɖ߂�
					m_nSelect = SELECT_GAME01_PAUSE_TYPE_CONTINUE;
					//�|�[�Y����������
					m_bPause = false;
					break;
				default:
					break;
				}
			}
		}


		//�|�[�Y��ʂ���Ȃ�������
		if (m_bPause == false)
		{
			m_nFrame++;

			//�G�̐���
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
			//�{�X�̐���
			for (int nCntBoss = 0; nCntBoss < STAGE01_MAX_BOSS; nCntBoss++)
			{
				if (m_nFrameBoss[nCntBoss] == m_nFrame)
				{
					m_pBoss = CBoss::Create(D3DXVECTOR3(m_bossPos[nCntBoss].x, m_bossPos[nCntBoss].y, 0.0f),
											D3DXVECTOR3(1.0f, 1.0f, 1.0f),
											D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					//BGM�̒�~
					pSound->Stop(CSound::SOUND_LABEL_GAME01_BGM);
					//BGM�̍Đ�
					pSound->Play(CSound::SOUND_LABEL_BOSS_BGM);
					//�T�E���h�̉��ʒ���
					pSound->ControllVoice(CSound::SOUND_LABEL_BOSS_BGM, 0.5f);
				}
			}

			//��Ԃɂ�鏈������
			State();
		}
	}
}

//================================================
//�`�揈��
//================================================
void CGame01::Draw(void)
{
	
}

//=============================================================================
// �o�߃t���[�����擾����
//=============================================================================
int CGame01::GetFrame(void)
{
	return m_nFrame;
}

//=============================================================================
// score�擾����
//=============================================================================
CScore* CGame01::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// polygon�擾����
//=============================================================================
CPolygon* CGame01::GetPolygon(void)
{
	return m_pPolygon;
}

//=============================================================================
// life�擾����
//=============================================================================
CLife* CGame01::GetLife(void)
{
	return m_pLife;
}

//=============================================================================
// boss�擾����
//=============================================================================
CBoss* CGame01::GetBoss(void)
{
	return m_pBoss;
}

//=============================================================================
// �|�[�Y�擾����
//=============================================================================
bool CGame01::GetPause(void)
{
	return m_bPause;
}

//=============================================================================
// �I�����擾����
//=============================================================================
int CGame01::GetSelect(void)
{
	return m_nSelect;
}

//=============================================================================
// �Q�[���̏�Ԏ擾����
//=============================================================================
CGame01::GAME_STATE CGame01::GetState(void)
{
	return m_state;
}

//=============================================================================
// �Q�[���̏�Ԑݒ菈��
//=============================================================================
void CGame01::SetState(CGame01::GAME_STATE state)
{
	m_state = state;
}

//=============================================================================
// ��Ԃɂ�鏈���킯
//=============================================================================
void CGame01::State(void)
{
	//�t�F�[�h�擾����
	CFade *pFade;
	pFade = CManager::GetFade();

	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	switch (m_state)
	{
	case GAME_STATE_GAME:
		break;
	case GAME_STATE_CLEAR:
		//�J�E���^�[�����Z
		m_nFinishCounter++;
		//��莞�ԂɂȂ�����gameClear��UI�𐶐�
		if (m_nFinishCounter == 500)
		{
			//�T�E���h�̍Đ�
			pSound->Play(CSound::SOUND_LABEL_GAME_CLEAR_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_GAME_CLEAR_SE, 1.8f);

			CUiRest::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
							D3DXVECTOR3(UI_REST_GAME_CLEAR_WIDTH, UI_REST_GAME_CLEAR_HEIGHT, 0.0f),
							CUiRest::UI_REST_TYPE_GAME_CLEAR);
		}
		else if(m_nFinishCounter >= 800)
		{
			//���U���g��ʂɍs��
			pFade->SetFade(CManager::MODE_RESULT);
		}
		break;
	case GAME_STATE_OVER:
		//�J�E���^�[�����Z
		m_nFinishCounter++;
		//��莞�ԂɂȂ�����gameOver��UI�𐶐�
		if (m_nFinishCounter == 300)
		{
			CUiRest::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
							D3DXVECTOR3(UI_REST_GAME_OVER_WIDTH, UI_REST_GAME_OVER_HEIGHT, 0.0f),
							CUiRest::UI_REST_TYPE_GAME_OVER);
		}
		else if (m_nFinishCounter >= 600)
		{
			//���j���[��ʂɖ߂�
			pFade->SetFade(CManager::MODE_MENU);
		}
		break;
	default:
		break;
	}
}

//=============================================================================
//�I�����Ă���̃t���[����
//=============================================================================
int CGame01::GetFinishCounter(void)
{
	return m_nFinishCounter;
}