//================================================
//���j���[����
//Authore:��������
//================================================
#include "renderer.h"
#include "menu.h"
#include "manager.h"
#include "texture.h"
#include "scene2D.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "fade.h"
#include "ui.h"
#include "sound.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

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
	//BGM�Đ�
	pSound->Play(CSound::SOUND_LABEL_MENU_BGM);
	//���ʒ���
	pSound->ControllVoice(CSound::SOUND_LABEL_MENU_BGM, 0.6f);

	m_pScene2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), PRIORITY_NONE);
	m_pScene2D->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_MENU_BG));

	m_pScene2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), PRIORITY_UI);
	m_pScene2D->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_MEMU_EXPLANATION_FRAME)); //�����g

	m_pMenu = CUi::Create(D3DXVECTOR3(MENU_LOGO_POSX, MENU_LOGO_POSY, 0.0f), D3DXVECTOR3(MENU_LOGO_SIXEX, MENU_LOGO_SIXEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_MENU_LOGO); //���j���[���S

	m_apSelect[SELECT_TUTORIAL] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, MENU_TUTORIAL_BUTTON_POSY + MENU_CHOICES_SPACE, 0.0f), D3DXVECTOR3(MENU_UI_SIZEX, MENU_UI_SIZEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_MENU_SELECT_TUTORIAL); //�`���[�g���A���{�^��
	m_apSelect[SELECT_GAME] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, MENU_GAME_BUTTON_POSY + MENU_CHOICES_SPACE, 0.0f), D3DXVECTOR3(MENU_UI_SIZEX, MENU_UI_SIZEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_MENU_SELECT_GAME);		     //�Q�[���{�^��
	m_apSelect[SELECT_BACKTITLE] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, MENU_EXIT_BUTTON_POSY + MENU_CHOICES_SPACE, 0.0f), D3DXVECTOR3(MENU_UI_SIZEX, MENU_UI_SIZEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_MENU_SELECT_BACKTITLE);		     //�I���{�^��

	m_apExplanation[EXPLANATION_TUTORIAL] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, MENU_EXPLANATION_POSY, 0.0f), D3DXVECTOR3(MENU_UI_SIZEX, MENU_UI_SIZEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_MENU_EXPLANATION_TUTORIAL);			 //�`���[�g���A������
	m_apExplanation[EXPLANATION_GAME] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, MENU_EXPLANATION_POSY, 0.0f), D3DXVECTOR3(MENU_UI_SIZEX, MENU_UI_SIZEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_MENU_EXPLANATION_GAME);					 //�Q�[������
	m_apExplanation[EXPLANATION_EXIT] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, MENU_EXPLANATION_POSY, 0.0f), D3DXVECTOR3(MENU_UI_SIZEX, MENU_UI_SIZEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_MENU_EXPLANATION_BACKTITLE);					 //�I������

	m_nSelect = SELECT_TUTORIAL;			//�ŏ��̓`���[�g���A����I�𒆂ɂ���
	m_nExplanation = EXPLANATION_TUTORIAL;	//�ŏ��̓`���[�g���A���̐�����\������

	//�`���[�g���A���𖾂邭����
	m_apSelect[SELECT_TUTORIAL]->SetCol(MENU_SELECT_COL);
	//����ȊO���Â�����
	m_apSelect[SELECT_GAME]->SetCol(MENU_DEFAULT_COL);
	m_apSelect[SELECT_BACKTITLE]->SetCol(MENU_DEFAULT_COL);

	//�`���[�g���A���̐����𖾂邭����
	m_apExplanation[EXPLANATION_TUTORIAL]->SetCol(MENU_SELECT_COL);
	//����ȊO�̐������\���ɂ���
	m_apExplanation[EXPLANATION_GAME]->SetCol(MENU_HIDE);
	m_apExplanation[EXPLANATION_EXIT]->SetCol(MENU_HIDE);


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

	//�T�E���h�S���~�߂�
	pSound->Stop();
	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CMenu::Update(void)
{
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

	//�e�I������I�𒆂�ENTER�L�[�A�X�^�[�g�{�^���AB�{�^������������
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
		pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_START, 0) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B, 0) == true)
	{
		switch (m_nSelect)
		{
		case SELECT_TUTORIAL:
			//�`���[�g���A���ɑJ��
			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				//����SE�Đ�
				pSound->Play(CSound::SOUND_LABEL_DECISION_SE);
				//���ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_DECISION_SE, 2.0f);
				pFade->SetFade(CManager::MODE_TUTORIAL);
			}
			break;
		case SELECT_GAME:
			//�Q�[����ʂɑJ��
			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				//����SE�Đ�
				pSound->Play(CSound::SOUND_LABEL_DECISION_SE);
				//���ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_DECISION_SE, 2.0f);
				pFade->SetFade(CManager::MODE_GAME01);
			}
			break;
		case SELECT_BACKTITLE:
			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				//����SE�Đ�
				pSound->Play(CSound::SOUND_LABEL_DECISION_SE);
				//���ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_DECISION_SE, 2.0f);
				//�^�C�g���ɖ߂�
				pFade->SetFade(CManager::MODE_TITLE);
			}
			break;
		default:
			break;
		}
	}

	m_nSpan++;
	switch (m_nPattern)
	{
	case STARPATTERN_01:
		//4�b
		if (m_nSpan == 240)
		{
			m_apStar[0] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH, 60.0f, 0.0f), D3DXVECTOR3(250.0f, 250.0f, 0.0f), PRIORITY_NONE, CUi::UI_TYPE_MENU_STAR);
		}
		//6�b
		if (m_nSpan == 360)
		{
			m_apStar[1] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH, 40.0f, 0.0f), D3DXVECTOR3(175.0f, 175.0f, 0.0f), PRIORITY_NONE, CUi::UI_TYPE_MENU_STAR);
		}
		//6.5�b
		if (m_nSpan == 390)
		{
			m_apStar[2] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH, 100.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), PRIORITY_NONE, CUi::UI_TYPE_MENU_STAR);
			m_nSpan = 0;
			m_nPattern = STARPATTERN_02;
		}
		break;
	case STARPATTERN_02:
		//4�b
		if (m_nSpan == 240)
		{
			m_apStar[0] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH, 80.0f, 0.0f), D3DXVECTOR3(175.0f, 175.0f, 0.0f), PRIORITY_NONE, CUi::UI_TYPE_MENU_STAR);
		}
		//4.5�b
		if (m_nSpan == 270)
		{
			m_apStar[1] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH, 100.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), PRIORITY_NONE, CUi::UI_TYPE_MENU_STAR);
		}
		//5�b
		if (m_nSpan == 300)
		{
			m_apStar[2] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH, 60.0f, 0.0f), D3DXVECTOR3(250.0f, 250.0f, 0.0f), PRIORITY_NONE, CUi::UI_TYPE_MENU_STAR);
			m_nSpan = 0;
			m_nPattern = STARPATTERN_03;
		}
		break;
	case STARPATTERN_03:
		//4�b
		if (m_nSpan == 240)
		{
			m_apStar[0] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH, 60.0f, 0.0f), D3DXVECTOR3(250.0f, 250.0f, 0.0f), PRIORITY_NONE, CUi::UI_TYPE_MENU_STAR);
		}
		//5�b
		if (m_nSpan == 300)
		{
			m_apStar[1] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH, 60.0f, 0.0f), D3DXVECTOR3(250.0f, 250.0f, 0.0f), PRIORITY_NONE, CUi::UI_TYPE_MENU_STAR);
		}
		//6�b
		if (m_nSpan == 360)
		{
			m_apStar[2] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH, 60.0f, 0.0f), D3DXVECTOR3(250.0f, 250.0f, 0.0f), PRIORITY_NONE, CUi::UI_TYPE_MENU_STAR);
			m_nSpan = 0;
			m_nPattern = STARPATTERN_01;
		}
		break;
	}

	//W�L�[�A���L�[�������A���X�e�B�b�N����ɓ|�����Ƃ��A�\���L�[����������Ƃ�
	if (pInputKeyboard->GetTrigger(DIK_W) == true || pInputKeyboard->GetTrigger(DIK_UP) == true ||
		pInputPadX->GetLeftStickTrigger(CInputPadX::STICKTYPE_UP, 0) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP, 0) == true)

	{

		//���݂̑I�����؂�ւ�
		if (m_nSelect <= 0)
		{
			//�I��SE�Đ�
			pSound->Play(CSound::SOUND_LABEL_CHOICE_SE);
			//�I������ĂȂ��I�������Â�����
			m_apSelect[m_nSelect]->SetCol(MENU_DEFAULT_COL);
			//�I������ĂȂ��I�����̐������\���ɂ���
			m_apExplanation[m_nExplanation]->SetCol(MENU_HIDE);
			//�I�����̐؂�ւ�
			m_nSelect = SELECT_MAX - 1;
			//�����̐؂�ւ�
			m_nExplanation = EXPLANATION_MAX - 1;
		}
		else
		{
			//�I��SE�Đ�
			pSound->Play(CSound::SOUND_LABEL_CHOICE_SE);
			//�I������ĂȂ��I�������Â�����
			m_apSelect[m_nSelect]->SetCol(MENU_DEFAULT_COL);
			//�I������ĂȂ��I�����̐������\���ɂ���
			m_apExplanation[m_nExplanation]->SetCol(MENU_HIDE);
			//�I�����̐؂�ւ�
			m_nSelect--;
			//�����̐؂�ւ�
			m_nExplanation--;
		}
		//�I������Ă���I�����𖾂邭����
		m_apSelect[m_nSelect]->SetCol(MENU_SELECT_COL);
		//�I������Ă���I�����̐����𖾂邭����
		m_apExplanation[m_nExplanation]->SetCol(MENU_SELECT_COL);
	}
	//S�L�[�A���L�[�������܂��͍��X�e�B�b�N�����ɓ|�����Ƃ�
	if (pInputKeyboard->GetTrigger(DIK_S) == true || pInputKeyboard->GetTrigger(DIK_DOWN) == true ||
		pInputPadX->GetLeftStickTrigger(CInputPadX::STICKTYPE_DOWN, 0) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN, 0) == true)
	{
		//���݂̑I�����؂�ւ�
		if (m_nSelect >= SELECT_MAX - 1)
		{
			//�I��SE�Đ�
			pSound->Play(CSound::SOUND_LABEL_CHOICE_SE);
			//�I������ĂȂ��I�������Â�����
			m_apSelect[m_nSelect]->SetCol(MENU_DEFAULT_COL);
			//�I������ĂȂ��I�����̐������\���ɂ���
			m_apExplanation[m_nExplanation]->SetCol(MENU_HIDE);
			//�I�����̐؂�ւ�
			m_nSelect = 0;
			//�����̐؂�ւ�
			m_nExplanation = 0;
		}
		else
		{
			//�I��SE�Đ�
			pSound->Play(CSound::SOUND_LABEL_CHOICE_SE);
			//�I������ĂȂ��I�������Â�����
			m_apSelect[m_nSelect]->SetCol(MENU_DEFAULT_COL);
			//�I������ĂȂ��I�����̐������\���ɂ���
			m_apExplanation[m_nExplanation]->SetCol(MENU_HIDE);
			//�I�����̐؂�ւ�
			m_nSelect++;
			//�����̐؂�ւ�
			m_nExplanation++;
		}
		//�I������Ă���I�����𖾂邭����
		m_apSelect[m_nSelect]->SetCol(MENU_SELECT_COL);
		//�I������Ă���I�����̐�����\��
		m_apExplanation[m_nExplanation]->SetCol(MENU_SELECT_COL);
	}
}

//================================================
//�`�揈��
//================================================
void CMenu::Draw(void)
{

}
