//================================================
//���j���[����
//Authore:��������
//================================================
#include "renderer.h"
#include "menu.h"
#include "manager.h"
#include "texture.h"
#include "scene2D.h"
#include "ui_rest.h"
#include "ui_move.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "fade.h"
#include "sound.h"


//================================================
//�ÓI�����o�ϐ��錾
//================================================
CScene2D *CMenu::m_pScene2D = NULL;
CTexture *CMenu::m_pTexture = NULL;
int CMenu::m_nSelect = SELECT_MENU_TYPE_NONE;
int CMenu::m_nCntFrame = 0;

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CMenu::CMenu()
{

}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CMenu::~CMenu()
{

}

//================================================
//����������
//================================================
HRESULT CMenu::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//BGM�̍Đ�
	pSound->Play(CSound::SOUND_LABEL_MENU_BGM);
	//�T�E���h�̉��ʒ���
	pSound->ControllVoice(CSound::SOUND_LABEL_MENU_BGM, 0.5f);

	m_nSelect = SELECT_MENU_TYPE_GAME_START;

	//�w�i�̐���
	m_pScene2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
									CScene::PRIORITY_BG_0);
	//�w�i�̃e�N�X�`�����蓖��
	m_pScene2D->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TYPE_BG_MENU));

	//UI�̐���
	CUiMove::Create(D3DXVECTOR3(UI_MENU_CIRCLE_POS_X, UI_MENU_CIRCLE_INIT_POS_Y, 0.0f), D3DXVECTOR3(UI_MENU_CIRCLE_SMALL_WIDTH, UI_MENU_CIRCLE_SMALL_HEIGHT, 0.0f),
					D3DXVECTOR3(0.0f, UI_MENU_CIRCLE_INIT_MOVE, 0.0f), CUiMove::UI_MOVE_TYPE_MENU_CIRCLE_SMALL);

	CUiMove::Create(D3DXVECTOR3(UI_MENU_CIRCLE_POS_X, UI_MENU_CIRCLE_INIT_POS_Y, 0.0f), D3DXVECTOR3(UI_MENU_CIRCLE_BIG_WIDTH, UI_MENU_CIRCLE_BIG_HEIGHT, 0.0f),
					D3DXVECTOR3(0.0f, UI_MENU_CIRCLE_INIT_MOVE, 0.0f), CUiMove::UI_MOVE_TYPE_MENU_CIRCLE_BIG);

	CUiMove::Create(D3DXVECTOR3(UI_MENU_EXPLANATION_FALSE_POS_X, UI_MENU_EXPLANATION_FALSE_POS_Y, 0.0f), D3DXVECTOR3(UI_MENU_EXPLANATION_TUTORIAL_WIDTH, UI_MENU_EXPLANATION_TUTORIAL_HEIGHT, 0.0f),
					D3DXVECTOR3(0.0f, UI_MENU_FLOAT_MOVE, 0.0f), CUiMove::UI_MOVE_TYPE_MENU_EXPLANATION_TUTORIAL);

	CUiMove::Create(D3DXVECTOR3(UI_MENU_EXPLANATION_FALSE_POS_X, UI_MENU_EXPLANATION_FALSE_POS_Y, 0.0f), D3DXVECTOR3(UI_MENU_EXPLANATION_GAME_WIDTH, UI_MENU_EXPLANATION_GAME_HEIGHT, 0.0f),
					D3DXVECTOR3(UI_MENU_EXPLANATION_MOVE, UI_MENU_FLOAT_MOVE, 0.0f), CUiMove::UI_MOVE_TYPE_MENU_EXPLANATION_GAME);

	CUiMove::Create(D3DXVECTOR3(UI_MENU_EXPLANATION_FALSE_POS_X, UI_MENU_EXPLANATION_FALSE_POS_Y, 0.0f), D3DXVECTOR3(UI_MENU_EXPLANATION_EXIT_WIDTH, UI_MENU_EXPLANATION_EXIT_HEIGHT, 0.0f),
					D3DXVECTOR3(0.0f, UI_MENU_FLOAT_MOVE, 0.0f), CUiMove::UI_MOVE_TYPE_MENU_EXPLANATION_EXIT);

	CUiMove::Create(D3DXVECTOR3(UI_MENU_SELECT_FALSE_POS_X, UI_MENU_GAME_POS_Y, 0.0f), D3DXVECTOR3(UI_MENU_SELECT_TRUE_WIDTH, UI_MENU_SELECT_TRUE_HEIGHT, 0.0f),
					D3DXVECTOR3(UI_MENU_SELECT_INIT_MOVE, UI_MENU_FLOAT_MOVE, 0.0f), CUiMove::UI_MOVE_TYPE_MENU_GAME_START);

	CUiMove::Create(D3DXVECTOR3(UI_MENU_SELECT_FALSE_POS_X, UI_MENU_TUTORIAL_POS_Y, 0.0f), D3DXVECTOR3(UI_MENU_SELECT_FALSE_WIDTH, UI_MENU_SELECT_FALSE_HEIGHT, 0.0f),
					D3DXVECTOR3(UI_MENU_SELECT_INIT_MOVE, UI_MENU_FLOAT_MOVE, 0.0f), CUiMove::UI_MOVE_TYPE_MENU_TUTORIAL);

	CUiMove::Create(D3DXVECTOR3(UI_MENU_SELECT_FALSE_POS_X, UI_MENU_EXIT_POS_Y, 0.0f), D3DXVECTOR3(UI_MENU_SELECT_FALSE_WIDTH, UI_MENU_SELECT_FALSE_HEIGHT, 0.0f),
					D3DXVECTOR3(UI_MENU_SELECT_INIT_MOVE, UI_MENU_FLOAT_MOVE, 0.0f), CUiMove::UI_MOVE_TYPE_MENU_EXIT);

	CUiRest::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(UI_REST_MENU_BAND_WIDTH, UI_REST_MENU_BAND_HEIGHT, 0.0f),
					CUiRest::UI_REST_TYPE_MENU_BAND);

	return S_OK;
}

//================================================
//�I������
//================================================
void CMenu::Uninit(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();
	//BGM�̒�~
	pSound->Stop(CSound::SOUND_LABEL_MENU_BGM);

	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CMenu::Update(void)
{
	m_nCntFrame++;

	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�t�F�[�h�擾����
	CFade *pFade;
	pFade = CManager::GetFade();

	//�p�b�h�擾����
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		//�I������
		if (pInputKeyboard->GetTrigger(DIK_UP) == true ||
			pInputPadX->GetLeftStickTrigger(CInputPadX::STICKTYPE_UP) == true ||
			pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP) == true)
		{
			m_nSelect--;
			if (m_nSelect < SELECT_MENU_TYPE_TUTORIAL)
			{
				m_nSelect = SELECT_MENU_TYPE_TUTORIAL;
			}
			else
			{
				//BGM�̍Đ�
				pSound->Play(CSound::SOUND_LABEL_CURSOR_SE);
				//�T�E���h�̉��ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_CURSOR_SE, 0.8f);
			}
		}
		else if (pInputKeyboard->GetTrigger(DIK_DOWN) == true ||
					pInputPadX->GetLeftStickTrigger(CInputPadX::STICKTYPE_DOWN) == true ||
					pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN) == true)
		{
			m_nSelect++;
			if (m_nSelect > SELECT_MENU_TYPE_EXIT)
			{
				m_nSelect = SELECT_MENU_TYPE_EXIT;
			}
			else
			{
				//SE�̍Đ�
				pSound->Play(CSound::SOUND_LABEL_CURSOR_SE);
				//�T�E���h�̉��ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_CURSOR_SE, 0.8f);
			}
		}

		//���菈��
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_START) == true ||
			pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true)
		{
			switch (m_nSelect)
			{
			case SELECT_MENU_TYPE_TUTORIAL:
				pFade->SetFade(CManager::MODE_TUTORIAL);
				//SE�̍Đ�
				pSound->Play(CSound::SOUND_LABEL_DECIDE_SE_00);
				//�T�E���h�̉��ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_DECIDE_SE_00, 0.8f);
				break;
			case SELECT_MENU_TYPE_GAME_START:
				pFade->SetFade(CManager::MODE_GAME01);
				//SE�̍Đ�
				pSound->Play(CSound::SOUND_LABEL_DECIDE_SE_00);
				//�T�E���h�̉��ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_DECIDE_SE_00, 0.8f);
				break;
			case SELECT_MENU_TYPE_EXIT:
				pFade->SetFade(CManager::MODE_TITLE);
				//SE�̍Đ�
				pSound->Play(CSound::SOUND_LABEL_EXIT_SE);
				//�T�E���h�̉��ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_EXIT_SE, 1.2f);
				break;
			default:
				break;
			}
		}
	}
}

//================================================
//�`�揈��
//================================================
void CMenu::Draw(void)
{
	
}

//=============================================================================
// texture�擾����
//=============================================================================
CTexture* CMenu::GetTexture(void)
{
	return m_pTexture;
}

//=============================================================================
// �I�����擾����
//=============================================================================
int CMenu::GetSelect(void)
{
	return m_nSelect;
}

//=============================================================================
// Frame�J�E���g�擾����
//=============================================================================
int CMenu::GetFrame(void)
{
	return m_nCntFrame;
}

//=============================================================================
// Frame�J�E���g�ݒ菈��
//=============================================================================
void CMenu::SetFrame(int nCntFrame)
{
	m_nCntFrame = nCntFrame;
}