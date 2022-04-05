//================================================
//�|�[�Y����
//Authore:��������
//================================================
#include "renderer.h"
#include "pause.h"
#include "manager.h"
#include "texture.h"
#include "scene2D.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "fade.h"
#include "ui.h"
#include "sound.h"
#include "scene.h"
//================================================
//�ÓI�����o�ϐ��錾
//================================================
bool CPause::m_bPause = false;			//�|�[�Y��ʂ��ǂ���

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CPause::CPause(int nPriority) :CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CPause::~CPause()
{

}

//================================================
//����������
//================================================
HRESULT CPause::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;
	m_bPause = false;

	return S_OK;
}

//================================================
//�I������
//================================================
void CPause::Uninit(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//���Đ�����Ă�T�E���h���~�߂�
	pSound->Stop();

	m_bPause = false;
	
	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CPause::Update(void)
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

	//P�L�[���X�^�[�g�{�^���Ń|�[�Y
	if (pInputKeyboard->GetTrigger(DIK_P) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_START, 0) == true)
	{
		//���[�h��TUTORIAL�Ȃ�
		if (m_pManager->GetMode() == CManager::MODE_TUTORIAL)
		{
			pSound->ControllVoice(CSound::SOUND_LABEL_TUTORIAL_BGM, 0.1f);
		}
		//���[�h��GAME01�Ȃ�
		if (m_pManager->GetMode() == CManager::MODE_GAME01)
		{
			pSound->ControllVoice(CSound::SOUND_LABEL_GAME_BGM, 0.1f);
		}

		pSound->Play(CSound::SOUND_LABEL_POSESCREEN_SE);

		if (m_bPause == false)
		{
			m_bPause = true;

			m_pScene2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + m_pos.x, SCREEN_HEIGHT / 2 + m_pos.y, 0.0f), D3DXVECTOR3(PAUSE_FRAME_SIXEX + m_size.x, PAUSE_FRAME_SIXEY + m_size.y, 0.0f), PRIORITY_UI);
			m_pScene2D->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_PAUSE_UI_FRAME));

			m_apSelect[SELECT_START] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + m_pos.x, PAUSE_START_BUTTON_POSY + PAUSE_CHOICES_SPACE + m_pos.y, 0.0f), D3DXVECTOR3(PAUSE_UI_SIZEX + m_size.x, PAUSE_UI_SIZEY + m_size.y, 0.0f), PRIORITY_UI, CUi::UI_TYPE_PAUSE_START);			//�ĊJ�{�^��
			m_apSelect[SELECT_EXIT] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + m_pos.x, PAUSE_EXIT_BUTTON_POSY + PAUSE_CHOICES_SPACE + m_pos.y, 0.0f), D3DXVECTOR3(PAUSE_UI_SIZEX + m_size.x, PAUSE_UI_SIZEY + m_size.y, 0.0f), PRIORITY_UI, CUi::UI_TYPE_PAUSE_EXIT);				//���j���[�ɖ߂�{�^��
			m_apSelect[SELECT_RESTART] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + m_pos.x, PAUSE_RESTART_BUTTON_POSY + PAUSE_CHOICES_SPACE + m_pos.y, 0.0f), D3DXVECTOR3(PAUSE_UI_SIZEX + m_size.x, PAUSE_UI_SIZEY + m_size.y, 0.0f), PRIORITY_UI, CUi::UI_TYPE_PAUSE_RESTART);	//���X�^�[�g�{�^��

			m_nSelect = SELECT_START;			//�ŏ��͍ĊJ��I�𒆂ɂ���

			//�ĊJ�𖾂邭����
			m_apSelect[SELECT_START]->SetCol(PAUSE_SELECT_COL);
			//����ȊO���Â�����
			m_apSelect[SELECT_EXIT]->SetCol(PAUSE_DEFAULT_COL);
			m_apSelect[SELECT_RESTART]->SetCol(PAUSE_DEFAULT_COL);
		}
		else
		{
			//���[�h��TUTORIAL�Ȃ�
			if (m_pManager->GetMode() == CManager::MODE_TUTORIAL)
			{
				pSound->ControllVoice(CSound::SOUND_LABEL_TUTORIAL_BGM, 0.5f);
			}
			//���[�h��GAME01�Ȃ�
			if (m_pManager->GetMode() == CManager::MODE_GAME01)
			{
				pSound->ControllVoice(CSound::SOUND_LABEL_GAME_BGM, 0.5f);
			}
			pSound->Play(CSound::SOUND_LABEL_POSESCREENCLOSE_SE);
			m_bPause = false;

			m_pScene2D->Uninit();
			delete m_pScene2D;
			m_pScene2D = NULL;
			for (int nCnt = 0; nCnt < SELECT_MAX; nCnt++)
			{
				m_apSelect[nCnt]->Uninit();
				delete m_apSelect[nCnt];
				m_apSelect[nCnt] = NULL;
			}
		}
	}


	if (m_bPause == true)
	{
		//�e�I������I�𒆂�ENTER�L�[�AB�{�^������������
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B, 0) == true)
		{
			switch (m_nSelect)
			{
			case SELECT_START:
				//����SE�Đ�
				pSound->Play(CSound::SOUND_LABEL_DECISION_SE);
				//���ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_DECISION_SE, 2.0f);
				//�|�[�Y�����Ƃ��납��ĊJ(�|�[�Y��ʂ̏I��)
				m_bPause = false;
				break;
			case SELECT_EXIT:
				//����SE�Đ�
				pSound->Play(CSound::SOUND_LABEL_DECISION_SE);
				//���ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_DECISION_SE, 2.0f);
				//���j���[��ʂɖ߂�
				m_bPause = false;
				if (pFade->GetFade() == CFade::FADE_NONE)
				{
				pFade->SetFade(CManager::MODE_MENU);
				}
				break;
			case SELECT_RESTART:
				//����SE�Đ�
				pSound->Play(CSound::SOUND_LABEL_DECISION_SE);
				//���ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_DECISION_SE, 2.0f);

				//���[�h��TUTORIAL�Ȃ�
				if (m_pManager->GetMode() == CManager::MODE_TUTORIAL)
				{
					//�`���[�g���A�����ŏ������蒼��
					m_bPause = false;
					if (pFade->GetFade() == CFade::FADE_NONE)
					{
						pFade->SetFade(CManager::MODE_TUTORIAL);
					}
				}
				//���[�h��GAME01�Ȃ�
				if (m_pManager->GetMode() == CManager::MODE_GAME01)
				{
					//�Q�[�����ŏ������蒼��
					m_bPause = false;
					if (pFade->GetFade() == CFade::FADE_NONE)
					{
						pFade->SetFade(CManager::MODE_GAME01);
					}
				}
				break;
			default:
				break;
			}
			//�T�E���h����
			pSound->ControllVoice(CSound::SOUND_LABEL_GAME_BGM, 0.5f);
			pSound->ControllVoice(CSound::SOUND_LABEL_TUTORIAL_BGM, 0.5f);

			m_pScene2D->Uninit();
			delete m_pScene2D;
			m_pScene2D = NULL;
			for (int nCnt = 0; nCnt < SELECT_MAX; nCnt++)
			{
				m_apSelect[nCnt]->Uninit();
				delete m_apSelect[nCnt];
				m_apSelect[nCnt] = NULL;
			}
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
				m_apSelect[m_nSelect]->SetCol(PAUSE_DEFAULT_COL);
				m_nSelect = SELECT_MAX - 1;
			}
			else
			{
				//�I��SE�Đ�
				pSound->Play(CSound::SOUND_LABEL_CHOICE_SE);
				m_apSelect[m_nSelect]->SetCol(PAUSE_DEFAULT_COL);
				m_nSelect--;
			}
			//�I������Ă���I�����𖾂邭����
			m_apSelect[m_nSelect]->SetCol(PAUSE_SELECT_COL);
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
				m_apSelect[m_nSelect]->SetCol(PAUSE_DEFAULT_COL);
				m_nSelect = 0;
			}
			else
			{
				//�I��SE�Đ�
				pSound->Play(CSound::SOUND_LABEL_CHOICE_SE);
				m_apSelect[m_nSelect]->SetCol(PAUSE_DEFAULT_COL);
				m_nSelect++;
			}
			m_apSelect[m_nSelect]->SetCol(PAUSE_SELECT_COL);
		}
	}
}

//================================================
//�`�揈��
//================================================
void CPause::Draw(void)
{

}

bool CPause::GetPause(void)
{
	return m_bPause;
}

bool CPause::SetPause(bool bPause)
{
	m_bPause = bPause;
	return m_bPause;
}
//================================================
//��������
//================================================
CPause* CPause::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X�̐���
	CPause *pPause = NULL;
	if (pPause == NULL)
	{
		pPause = new CPause;
		if (pPause != NULL)
		{
			pPause->Init(pos, size);
		}
	}
	return pPause;
}