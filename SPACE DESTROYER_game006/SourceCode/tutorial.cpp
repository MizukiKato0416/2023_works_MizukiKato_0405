//================================================
//�`���[�g���A������
//Authore:��������
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
//�ÓI�����o�ϐ��錾
//================================================
bool CTutorial::m_bEnemyKill = false;
bool CTutorial::m_bPowerUp = false;
bool CTutorial::m_bSpeedUp = false;
int CTutorial::m_nSelect = SELECT_TUTORIAL_PAUSE_TYPE_NONE;
bool CTutorial::m_bPause = false;

//================================================
//�f�t�H���g�R���X�g���N�^
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
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CTutorial::~CTutorial()
{

}

//================================================
//����������
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

	//�t�F�[�Y�̐ݒ�
	m_phase = TUTORIAL_PHASE_FIRST_EXPLANATION;

	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//BGM�̍Đ�
	pSound->Play(CSound::SOUND_LABEL_GAME01_BGM);
	//�T�E���h�̉��ʒ���
	pSound->ControllVoice(CSound::SOUND_LABEL_GAME01_BGM, 0.5f);

	//�w�i�̐���
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(TUTORIAL_PLAYER_POS_X, TUTORIAL_PLAYER_POS_Y, 0.0f), D3DXVECTOR3(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));

	return S_OK;
}

//================================================
//�I������
//================================================
void CTutorial::Uninit(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();
	//BGM�̒�~
	pSound->Stop(CSound::SOUND_LABEL_GAME01_BGM);

	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CTutorial::Update(void)
{
	//�t�F�[�h�擾����
	CFade *pFade;
	pFade = CManager::GetFade();

	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	if (m_bPause == false)
	{
		//�t�F�[�Y���Ƃ̏���
		phase();
	}

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		//�|�[�Y�Ɋւ��鏈��
		Pause();
	}
}

//================================================
//�`�揈��
//================================================
void CTutorial::Draw(void)
{
	
}

//================================================
//�t�F�[�Y���Ƃ̏���
//================================================
void CTutorial::phase(void)
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

	switch (m_phase)
	{
	case TUTORIAL_PHASE_FIRST_EXPLANATION:
		if (m_nNextPhaseCounter == 0)
		{
			//UI�̐���
			m_pUi[0] = CUiRest::Create(D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_POS_X, UI_REST_TUTORIAL_EXPLANATION_POS_Y, 0.0f),
										D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_WIDTH, UI_REST_TUTORIAL_EXPLANATION_HEIGHT, 0.0f),
										CUiRest::UI_REST_TYPE_TUTORIAL_EXPLANATION_000);
		}
		//�J�E���^�[�����Z
		m_nNextPhaseCounter++;
		//�J�E���^�[��120�ȏ��RETURN�L�[�܂���B�{�^������������
		if ((pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true)
			&& m_nNextPhaseCounter >= TUTORIAL_NEXT_PHASE_COUNTER)
		{
			//SE�̍Đ�
			pSound->Play(CSound::SOUND_LABEL_NEXT_PAGE_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_NEXT_PAGE_SE, 1.2f);
			//�J�E���^�[��0�ɂ���
			m_nNextPhaseCounter = 0;
			//UI��j��
			m_pUi[0]->Uninit();
			//���̃t�F�[�Y��
			m_phase = TUTORIAL_PHASE_PLAYER_CONTROL_EXPLANATION;
		}
		break;
	case TUTORIAL_PHASE_PLAYER_CONTROL_EXPLANATION:
		if (m_nNextPhaseCounter == 0)
		{
			//UI�̐���
			m_pUi[0] = CUiRest::Create(D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_POS_X, UI_REST_TUTORIAL_EXPLANATION_POS_Y, 0.0f),
										D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_WIDTH, UI_REST_TUTORIAL_EXPLANATION_HEIGHT, 0.0f),
										CUiRest::UI_REST_TYPE_TUTORIAL_EXPLANATION_001);
		}
		//�J�E���^�[�����Z
		m_nNextPhaseCounter++;
		//�J�E���^�[��120�ȏ��RETURN�L�[�܂���B�{�^������������
		if ((pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true)
			&& m_nNextPhaseCounter >= TUTORIAL_NEXT_PHASE_COUNTER)
		{
			//SE�̍Đ�
			pSound->Play(CSound::SOUND_LABEL_NEXT_PAGE_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_NEXT_PAGE_SE, 1.2f);
			//�J�E���^�[��0�ɂ���
			m_nNextPhaseCounter = 0;
			//UI��j��
			m_pUi[0]->Uninit();
			//���̃t�F�[�Y��
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
				//�v���C���[��j��
				m_pPlayer->Uninit();
				//���̃t�F�[�Y��
				m_phase = TUTORIAL_PHASE_PLAYER_SHOOT_EXPLANATION;
				//�J�E���^�[��0�ɂ���
				m_nNextPhaseCounter = 0;
			}
		}
		break;
	case TUTORIAL_PHASE_PLAYER_SHOOT_EXPLANATION:
		if (m_nNextPhaseCounter == 0)
		{
			//SE�̍Đ�
			pSound->Play(CSound::SOUND_LABEL_NEXT_PAGE_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_NEXT_PAGE_SE, 1.2f);
			//�v���C���[�̐���
			m_pPlayer = CPlayer::Create(D3DXVECTOR3(TUTORIAL_PLAYER_POS_X, TUTORIAL_PLAYER_POS_Y, 0.0f),
										D3DXVECTOR3(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));

			//�G�̐���
			CEnemyFighter::Create(D3DXVECTOR3(TUTORIAL_ENEMY_POS_X, TUTORIAL_ENEMY_POS_Y, 0.0f),
									D3DXVECTOR3(ENEMY_FIGHTER_WIDTH, ENEMY_FIGHTER_HEIGHT, 0.0f),
									D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									CMover::MOVER_TYPE_NONE);

			//UI�̐���
			m_pUi[0] = CUiRest::Create(D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_POS_X, UI_REST_TUTORIAL_EXPLANATION_POS_Y, 0.0f),
										D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_WIDTH, UI_REST_TUTORIAL_EXPLANATION_HEIGHT, 0.0f),
										CUiRest::UI_REST_TYPE_TUTORIAL_EXPLANATION_002);
		}
		//�J�E���^�[�����Z
		m_nNextPhaseCounter++;
		//�J�E���^�[��120�ȏ��RETURN�L�[�܂���B�{�^������������
		if ((pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true)
			&& m_nNextPhaseCounter >= TUTORIAL_NEXT_PHASE_COUNTER)
		{
			//SE�̍Đ�
			pSound->Play(CSound::SOUND_LABEL_NEXT_PAGE_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_NEXT_PAGE_SE, 1.2f);
			//�J�E���^�[��0�ɂ���
			m_nNextPhaseCounter = 0;
			//UI��j��
			m_pUi[0]->Uninit();
			//���̃t�F�[�Y��
			m_phase = TUTORIAL_PHASE_PLAYER_SHOOT;
		}
		break;
	case TUTORIAL_PHASE_PLAYER_SHOOT:
		if (m_bEnemyKill == true)
		{
			//�J�E���^�[�����Z
			m_nNextPhaseCounter++;
			if (m_nNextPhaseCounter >= TUTORIAL_NEXT_PHASE_COUNTER)
			{
				//�v���C���[��j��
				m_pPlayer->Uninit();
				//���̃t�F�[�Y��
				m_phase = TUTORIAL_PHASE_ITEM_EXPLANATION_000;
				//�J�E���^�[��0�ɂ���
				m_nNextPhaseCounter = 0;
			}
		}
		break;
	case TUTORIAL_PHASE_ITEM_EXPLANATION_000:
		if (m_nNextPhaseCounter == 0)
		{
			//SE�̍Đ�
			pSound->Play(CSound::SOUND_LABEL_NEXT_PAGE_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_NEXT_PAGE_SE, 1.2f);
			//�v���C���[�̐���
			m_pPlayer = CPlayer::Create(D3DXVECTOR3(TUTORIAL_PLAYER_POS_X, TUTORIAL_PLAYER_POS_Y, 0.0f),
										D3DXVECTOR3(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));

			//UI�̐���
			m_pUi[0] = CUiRest::Create(D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_POS_X, UI_REST_TUTORIAL_EXPLANATION_POS_Y, 0.0f),
										D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_WIDTH, UI_REST_TUTORIAL_EXPLANATION_HEIGHT, 0.0f),
										CUiRest::UI_REST_TYPE_TUTORIAL_EXPLANATION_003);
		}
		//�J�E���^�[�����Z
		m_nNextPhaseCounter++;
		//�J�E���^�[��120�ȏ��RETURN�L�[�܂���B�{�^������������
		if ((pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true) &&
			m_nNextPhaseCounter >= TUTORIAL_NEXT_PHASE_COUNTER)
		{
			//SE�̍Đ�
			pSound->Play(CSound::SOUND_LABEL_NEXT_PAGE_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_NEXT_PAGE_SE, 1.2f);
			//�J�E���^�[��0�ɂ���
			m_nNextPhaseCounter = 0;
			//UI��j��
			m_pUi[0]->Uninit();
			//���̃t�F�[�Y��
			m_phase = TUTORIAL_PHASE_ITEM_EXPLANATION_001;
		}
		break;
	case TUTORIAL_PHASE_ITEM_EXPLANATION_001:
		if (m_nNextPhaseCounter == 0)
		{
			//UI�̐���
			m_pUi[0] = CUiRest::Create(D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_POS_X, UI_REST_TUTORIAL_EXPLANATION_POS_Y, 0.0f),
										D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_WIDTH, UI_REST_TUTORIAL_EXPLANATION_HEIGHT, 0.0f),
										CUiRest::UI_REST_TYPE_TUTORIAL_EXPLANATION_004);
			//�G�̐���
			m_pEnemyItemPower = CEnemyItemPower::Create(D3DXVECTOR3(TUTORIAL_ENEMY_ITEM_POWER_POS_X, TUTORIAL_ENEMY_ITEM_POWER_POS_Y, 0.0f),
														D3DXVECTOR3(ENEMY_ITEM_POWER_WIDTH, ENEMY_ITEM_POWER_HEIGHT, 0.0f),
														D3DXVECTOR3(0.0f, 0.0f, 0.0f),
														CMover::MOVER_TYPE_NONE);

			//�G�̐���
			m_pEnemyItemSpeed = CEnemyItemSpeed::Create(D3DXVECTOR3(TUTORIAL_ENEMY_ITEM_SPEED_POS_X, TUTORIAL_ENEMY_ITEM_SPEED_POS_Y, 0.0f),
														D3DXVECTOR3(ENEMY_ITEM_SPEED_WIDTH, ENEMY_ITEM_SPEED_HEIGHT, 0.0f),
														D3DXVECTOR3(0.0f, 0.0f, 0.0f),
														CMover::MOVER_TYPE_NONE);
		}
		//�J�E���^�[�����Z
		m_nNextPhaseCounter++;
		//�J�E���^�[��120�ȏ��RETURN�L�[�܂���B�{�^������������
		if ((pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true) &&
			m_nNextPhaseCounter >= TUTORIAL_NEXT_PHASE_COUNTER)
		{
			//SE�̍Đ�
			pSound->Play(CSound::SOUND_LABEL_NEXT_PAGE_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_NEXT_PAGE_SE, 1.2f);
			//�J�E���^�[��0�ɂ���
			m_nNextPhaseCounter = 0;
			//UI��j��
			m_pUi[0]->Uninit();
			//���̃t�F�[�Y��
			m_phase = TUTORIAL_PHASE_PLAYER_LEVEL_UP_SHOOT;
		}
		break;
	case TUTORIAL_PHASE_PLAYER_LEVEL_UP_SHOOT:
		//�p���[�A�b�v�A�X�s�[�h�A�b�v������ԂȂ�
		if (m_bPowerUp == true && m_bSpeedUp == true)
		{
			//�J�E���^�[�����Z
			m_nNextPhaseCounter++;
			if (m_nNextPhaseCounter >= TUTORIAL_NEXT_PHASE_COUNTER)
			{
				//�v���C���[��j��
				m_pPlayer->Uninit();
				//���̃t�F�[�Y��
				m_phase = TUTORIAL_PHASE_FINISH;
				//�J�E���^�[��0�ɂ���
				m_nNextPhaseCounter = 0;
			}
		}
		break;
	case TUTORIAL_PHASE_FINISH:
		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			if (m_nNextPhaseCounter == 0)
			{
				//SE�̍Đ�
				pSound->Play(CSound::SOUND_LABEL_NEXT_PAGE_SE);
				//�T�E���h�̉��ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_NEXT_PAGE_SE, 1.2f);
				//�v���C���[�̐���
				m_pPlayer = CPlayer::Create(D3DXVECTOR3(TUTORIAL_PLAYER_POS_X, TUTORIAL_PLAYER_POS_Y, 0.0f),
										D3DXVECTOR3(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));

				//UI�̐���
				m_pUi[0] = CUiRest::Create(D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_POS_X, UI_REST_TUTORIAL_EXPLANATION_POS_Y, 0.0f),
											D3DXVECTOR3(UI_REST_TUTORIAL_EXPLANATION_WIDTH, UI_REST_TUTORIAL_EXPLANATION_HEIGHT, 0.0f),
											CUiRest::UI_REST_TYPE_TUTORIAL_EXPLANATION_005);
			}
			//�J�E���^�[�����Z
			m_nNextPhaseCounter++;
			if ((pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true) &&
				m_nNextPhaseCounter >= TUTORIAL_NEXT_PHASE_COUNTER)
			{
				//SE�̍Đ�
				pSound->Play(CSound::SOUND_LABEL_NEXT_PAGE_SE);
				//�T�E���h�̉��ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_NEXT_PAGE_SE, 1.2f);
				//�J�E���^�[��0�ɂ���
				m_nNextPhaseCounter = 0;
				//���j���[�ɖ߂�
				pFade->SetFade(CManager::MODE_MENU);
			}
		}
		break;
	default:
		break;
	}
}

//================================================
//�G��|�����̂�ݒ肷�鏈��
//================================================
void CTutorial::SetEnemyKill(bool bEnemyKill)
{
	m_bEnemyKill = bEnemyKill;
}

//================================================
//�p���[�A�b�v�����̂�ݒ肷�鏈��
//================================================
void CTutorial::SetPowerUp(bool bPowerUp)
{
	m_bPowerUp = bPowerUp;
}

//================================================
//�X�s�[�h�A�b�v�����̂�ݒ肷�鏈��
//================================================
void CTutorial::SetSpeedUp(bool bSpeedUp)
{
	m_bSpeedUp = bSpeedUp;
}

//=============================================================================
// �|�[�Y�擾����
//=============================================================================
bool CTutorial::GetPause(void)
{
	return m_bPause;
}

//=============================================================================
// �I�����擾����
//=============================================================================
int CTutorial::GetSelect(void)
{
	return m_nSelect;
}

//=============================================================================
// �t�F�[�Y�擾����
//=============================================================================
CTutorial::TUTORIAL_PHASE CTutorial::GetPhase(void)
{
	return m_phase;
}

//=============================================================================
// �|�[�Y�Ɋւ��鏈��
//=============================================================================
void CTutorial::Pause(void)
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

	//P�{�^������������
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
			m_pUi[1] = CUiRest::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(UI_REST_PAUSE_WIDTH, UI_REST_PAUSE_HEIGHT, 0.0f),
										CUiRest::UI_REST_TYPE_PAUSE);

			m_pUi[2] = CUiMove::Create(D3DXVECTOR3(UI_PAUSE_CONTINUE_POS_X, UI_PAUSE_CONTINUE_POS_Y, 0.0f), D3DXVECTOR3(UI_PAUSE_CONTINUE_WIDTH, UI_PAUSE_CONTINUE_HEIGHT, 0.0f),
										D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_PAUSE_CONTINUE);

			m_pUi[3] = CUiMove::Create(D3DXVECTOR3(UI_PAUSE_EXIT_POS_X, UI_PAUSE_EXIT_POS_Y, 0.0f), D3DXVECTOR3(UI_PAUSE_EXIT_WIDTH, UI_PAUSE_EXIT_HEIGHT, 0.0f),
										D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_PAUSE_EXIT);
		}
		else
		{
			//SE�̍Đ�
			pSound->Play(CSound::SOUND_LABEL_EXIT_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_EXIT_SE, 1.2f);
			//UI������
			for (int nCntPauseUi = 1; nCntPauseUi < MAX_TUTORIL_PAUSE_UI + 1; nCntPauseUi++)
			{
				m_pUi[nCntPauseUi]->Uninit();
			}
			//�|�[�Y����������
			m_bPause = false;
			//�I������continue�ɖ߂�
			m_nSelect = SELECT_TUTORIAL_PAUSE_TYPE_CONTINUE;
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
			if (m_nSelect < SELECT_TUTORIAL_PAUSE_TYPE_CONTINUE)
			{
				m_nSelect = SELECT_TUTORIAL_PAUSE_TYPE_CONTINUE;
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
			if (m_nSelect > SELECT_TUTORIAL_PAUSE_TYPE_EXIT)
			{
				m_nSelect = SELECT_TUTORIAL_PAUSE_TYPE_EXIT;
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
			case SELECT_TUTORIAL_PAUSE_TYPE_CONTINUE:
				//SE�̍Đ�
				pSound->Play(CSound::SOUND_LABEL_EXIT_SE);
				//�T�E���h�̉��ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_EXIT_SE, 1.2f);
				//UI������
				for (int nCntPauseUi = 1; nCntPauseUi < MAX_TUTORIL_PAUSE_UI + 1; nCntPauseUi++)
				{
					m_pUi[nCntPauseUi]->Uninit();
				}
				//�I������continue�ɖ߂�
				m_nSelect = SELECT_TUTORIAL_PAUSE_TYPE_CONTINUE;
				//�|�[�Y����������
				m_bPause = false;
				break;
			case SELECT_TUTORIAL_PAUSE_TYPE_EXIT:
				//SE�̍Đ�
				pSound->Play(CSound::SOUND_LABEL_EXIT_TUTORIAL_SE);
				//�T�E���h�̉��ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_EXIT_TUTORIAL_SE, 2.4f);
				//���j���[��ʂɖ߂�
				pFade->SetFade(CManager::MODE_MENU);
				//UI������
				for (int nCntPauseUi = 1; nCntPauseUi < MAX_TUTORIL_PAUSE_UI + 1; nCntPauseUi++)
				{
					m_pUi[nCntPauseUi]->Uninit();
				}
				//�I������continue�ɖ߂�
				m_nSelect = SELECT_TUTORIAL_PAUSE_TYPE_CONTINUE;
				//�|�[�Y����������
				m_bPause = false;
				break;
			default:
				break;
			}
		}
	}
}