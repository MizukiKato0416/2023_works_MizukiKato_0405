//================================================
//�^�C�g������
//Author:��������
//================================================
#include "renderer.h"
#include "title.h"
#include "manager.h"
#include "texture.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "fade.h"
#include "ui.h"
#include "scene2D.h"
#include "sound.h"
#include "manager.h"
#include "play_data.h"
//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CTitle::CTitle(int nPriority)
{
	memset(&m_apUi, NULL, sizeof(m_apUi));
	m_nTitleCounter = 0;
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
	//�v���C�f�[�^�ɂ���X�R�A��������
	CManager::GetPlayData()->SetScore(0);
	//�v���C�f�[�^�ɂ��鏟�����̎��ʔԍ���������
	CManager::GetPlayData()->SetWinNum(-1);

	m_nTitleCounter = 0;

	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();
	//BGM�Đ�
	pSound->Play(CSound::SOUND_LABEL_TITLE_BGM);
	//���ʒ���
	pSound->ControllVoice(CSound::SOUND_LABEL_TITLE_BGM, 0.5f);

	m_pScene2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), PRIORITY_NONE);
	m_pScene2D->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TITLE_BG));

	m_apUi[0] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, TITLE_LOGO_POSY, 0.0f), D3DXVECTOR3(TITLE_LOGO_SIZEX, TITLE_LOGO_SIZEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_TITLE_LOGO);	//�^�C�g�����S
	m_apUi[1] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, TITlE_PRESS_POSY, 0.0f), D3DXVECTOR3(TITlE_PRESS_SIZEX, TITlE_PRESS_SIZEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_TITLE_PRESS);	//Press�{�^��
	m_apUi[2] = CUi::Create(D3DXVECTOR3(200.0f, TITlE_PLAYER_1P_POSY, 0.0f), D3DXVECTOR3(TITlE_PLAYER_1P_SIZEX, TITlE_PLAYER_1P_SIZEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_TITLE_PLAYER_1P);	//1P
	m_apUi[3] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, TITlE_PLAYER_2P_POSY, 0.0f), D3DXVECTOR3(TITlE_PLAYER_2P_SIZEX, TITlE_PLAYER_2P_SIZEY, 0.0f), PRIORITY_UI, CUi::UI_TYPE_TITLE_PLAYER_2P);	//2P

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

	//�T�E���h�S���~�߂�
	pSound->Stop();
	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CTitle::Update(void)
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

	//Enter�L�[�A�X�^�[�g�{�^���AB�{�^������������
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
		pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_START, 0) == true ||pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B, 0) == true)
	{
		//�t�F�[�h�擾����
		CFade *pFade;
		pFade = CManager::GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			//����SE�Đ�
			pSound->Play(CSound::SOUND_LABEL_DECISION_SE);
			pFade->SetFade(CManager::MODE_MENU);
		}
	}

	//�J�E���^�[�𑝂₷
	m_nTitleCounter++;
	if (m_nTitleCounter >= TITLE_TO_RESULT_COUNT)
	{
		m_nTitleCounter = 0;
		//�t�F�[�h�擾����
		CFade *pFade;
		pFade = CManager::GetFade();

		//���U���g�ɑJ��
		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_RESULT);
		}
	}
}

//================================================
//�`�揈��
//================================================
void CTitle::Draw(void)
{
	
}

//=============================================================================
//UI�擾����
//=============================================================================
CUi *CTitle::GetUi(void)
{
	return m_apUi[0];
} 