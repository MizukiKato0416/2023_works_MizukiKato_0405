//================================================
//�^�C�g������
//Author:KatoMizuki
//================================================
#include "title.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_d.h"
#include "fade.h"
#include "manager.h"
#include "texture.h"
#include "ui.h"
#include "sound.h"

//================================================
//�}�N����`
//================================================
#define TITLE_TO_RESULT_COUNT		(600)				//���U���g�ɍs���܂ł̎���
#define TITLE_LOGO_SIZE_X			(366.0f)			//�^�C�g�����S�̃T�C�YX
#define TITLE_LOGO_SIZE_Y			(420.0f)			//�^�C�g�����S�̃T�C�YY
#define TITLE_PRESS_START_SIZE_X	(594.0f)			//PRESS START UI�̃T�C�YX
#define TITLE_PRESS_START_SIZE_Y	(84.0f)				//PRESS START UI�̃T�C�YY
#define TITLE_PRESS_START_POS_Y		(600.0f)			//PRESS START UI�̈ʒuY

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CTitle::CTitle(int nPriority):CObject(nPriority)
{
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
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//BGM�Đ�
	pSound->Play(CSound::SOUND_LABEL_TITLE_BGM);
	//�T�E���h�̉��ʒ���
	pSound->ControllVoice(CSound::SOUND_LABEL_TITLE_BGM, 0.7f);

	//�^�C�g���w�i�̐���
	CObject2D *pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 
											 D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_UI);
	pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_TITLE"));

	//�^�C�g�����S�̐���
	CObject2D *pObject2DTitleLogo = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
													  D3DXVECTOR3(TITLE_LOGO_SIZE_X, TITLE_LOGO_SIZE_Y, 0.0f), CObject::PRIORITY_UI);
	pObject2DTitleLogo->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_TITLE_LOGO"));

	m_nTitleCounter = 0;
	return S_OK;
}

//================================================
//�I������
//================================================
void CTitle::Uninit(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//BGM�Đ�
	pSound->Stop(CSound::SOUND_LABEL_TITLE_BGM);

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
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�p�b�hD�擾����
	CInputPadD *pInputPadD;
	pInputPadD = CManager::GetInstance()->GetInputPadD();

	//Enter�L�[�A�X�^�[�g�{�^������������
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadD->GetPress(CInputPadD::START) == true)
	{
		//�t�F�[�h�擾����
		CFade *pFade;
		pFade = CManager::GetInstance()->GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			//�T�E���h�擾����
			CSound *pSound;
			pSound = CManager::GetInstance()->GetSound();

			//SE�Đ�
			pSound->Play(CSound::SOUND_LABEL_DECIDE_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_DECIDE_SE, 1.8f);

			pFade->SetFade(CManager::MODE::MENU);
		}
	}

	if (m_nTitleCounter % 90 == 0 || m_nTitleCounter == 0)
	{
		CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, TITLE_PRESS_START_POS_Y, 0.0f),
			        D3DXVECTOR3(TITLE_PRESS_START_SIZE_X, TITLE_PRESS_START_SIZE_Y, 0.0f), CObject::PRIORITY_UI, CUi::TYPE::PRESS_START);
	}

	//�J�E���^�[�𑝂₷
	m_nTitleCounter++;
	

	if (m_nTitleCounter >= TITLE_TO_RESULT_COUNT)
	{
		m_nTitleCounter = 0;
		//�t�F�[�h�擾����
		CFade *pFade;
		pFade = CManager::GetInstance()->GetFade();

		//���U���g�ɑJ��
		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE::RESULT);
		}
	}
}

//================================================
//�`�揈��
//================================================
void CTitle::Draw(void)
{
	
}
