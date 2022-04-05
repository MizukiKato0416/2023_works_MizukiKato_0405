//================================================
//�^�C�g������
//Author:KatoMizuki
//================================================
#include "tutorial.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_d.h"
#include "fade.h"
#include "manager.h"
#include "texture.h"
#include "sound.h"

//================================================
//�}�N����`
//================================================

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CTutorial::CTutorial(int nPriority):CObject(nPriority)
{
	memset(m_pObject2D, NULL, sizeof(m_pObject2D[TUTORIAL_MAX_TYPE]));
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
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//BGM�Đ�
	pSound->Play(CSound::SOUND_LABEL_MENU_BGM);

	//�`���[�g���A���̐���
	m_pObject2D[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 
									   D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_UI);
	m_pObject2D[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_TUTORIAL_01"));

	return S_OK;
}

//================================================
//�I������
//================================================
void CTutorial::Uninit(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//BGM�Đ�
	pSound->Stop(CSound::SOUND_LABEL_MENU_BGM);

	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CTutorial::Update(void)
{
	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�p�b�hD�擾����
	CInputPadD *pInputPadD;
	pInputPadD = CManager::GetInstance()->GetInputPadD();


	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//Enter�L�[�A�X�^�[�g�{�^������������
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadD->GetTrigger(CInputPadD::START) == true)
	{
		//1���ڂ���������Ă�����
		if (m_pObject2D[0] != nullptr)
		{
			//SE�Đ�
			pSound->Play(CSound::SOUND_LABEL_DECIDE_SE);

			//����
			m_pObject2D[0]->Uninit();
			m_pObject2D[0] = nullptr;

			//2���ڂ𐶐�
			m_pObject2D[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 
									           D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_UI);
			m_pObject2D[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_TUTORIAL_02"));
		}
		else if (m_pObject2D[1] != nullptr)
		{//2���ڂ���������Ă�����
			//�t�F�[�h�擾����
			CFade *pFade;
			pFade = CManager::GetInstance()->GetFade();

			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				//SE�Đ�
				pSound->Play(CSound::SOUND_LABEL_DECIDE_SE);

				pFade->SetFade(CManager::MODE::MENU);
			}
		}
	}
}

//================================================
//�`�揈��
//================================================
void CTutorial::Draw(void)
{
	
}
