//================================================
//�^�C�g������
//Authore:��������
//================================================
#include "renderer.h"
#include "title.h"
#include "manager.h"
#include "bg.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "fade.h"
#include "sound.h"
#include "ui_move.h"
#include "play_data.h"
#include "player.h"


//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CTitle::CTitle()
{
	m_nResultCounter = 0;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CTitle::~CTitle()
{

}

//================================================
//����������
//================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�ϐ�������
	m_nResultCounter = 0;

	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//BGM�̍Đ�
	pSound->Play(CSound::SOUND_LABEL_TITLE_BGM);
	//�T�E���h�̉��ʒ���
	pSound->ControllVoice(CSound::SOUND_LABEL_TITLE_BGM, 0.5f);

	//�w�i�̐���
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	//UI�̐���
	CUiMove::Create(D3DXVECTOR3(UI_TITLE_INIT_POS_X, UI_TITLE_INIT_POS_Y, 0.0f), D3DXVECTOR3(UI_TITLE_WIDTH, UI_TITLE_HEIGHT, 0.0f),
					D3DXVECTOR3(0.0f, UI_TITLE_MOVE_Y, 0.0f), CUiMove::UI_MOVE_TYPE_TITLE);

	//UI�̐���
	CUiMove::Create(D3DXVECTOR3(UI_TITLE_PRESS_START_POS_X, UI_TITLE_PRESS_START_POS_Y, 0.0f), 
					D3DXVECTOR3(UI_TITLE_PRESS_START_WIDTH, UI_TITLE_PRESS_START_HEIGHT, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_PRESS_START);

	//�v���C�f�[�^�̎擾
	CPlayData *pPlayData = NULL;
	pPlayData = CManager::GetPlayData();

	//�v���C�f�[�^������
	pPlayData->SetPlayerLife(MAX_PLAYER_INIT_LIFE);
	pPlayData->SetScore(0);

	return S_OK;
}

//================================================
//�I������
//================================================
void CTitle::Uninit(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();
	//BGM�̒�~
	pSound->Stop(CSound::SOUND_LABEL_TITLE_BGM);

	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CTitle::Update(void)
{
	//�p�b�h�擾����
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�J�E���^�[�����Z
	m_nResultCounter++;

	if (m_nResultCounter >= TITLE_TO_RESULT_COUNT)
	{
		m_nResultCounter = 0;

		//�t�F�[�h�擾����
		CFade *pFade;
		pFade = CManager::GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			//���U���g�ɍs��
			pFade->SetFade(CManager::MODE_RESULT);
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||				//�G���^�[�L�[�������ꂽ��
		pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_START) == true ||	//start�{�^���������ꂽ��
		pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true)			//b�{�^���������ꂽ��
	{
		//�t�F�[�h�擾����
		CFade *pFade;
		pFade = CManager::GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			//���j���[�ɍs��
			pFade->SetFade(CManager::MODE_MENU);
			//�T�E���h�擾����
			CSound *pSound;
			pSound = CManager::GetSound();
			//SE�̍Đ�
			pSound->Play(CSound::SOUND_LABEL_TITLE_START_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_TITLE_START_SE, 1.0f);
		}
	}
}

//================================================
//�`�揈��
//================================================
void CTitle::Draw(void)
{
	
}
