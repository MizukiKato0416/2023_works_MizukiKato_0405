//================================================
//���U���g����
//Authore:��������
//================================================
#include "renderer.h"
#include "result.h"
#include "manager.h"
#include "texture.h"
#include "bg.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "fade.h"
#include "ranking.h"
#include "number.h"
#include "sound.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
CBg *CResult::m_pBg = NULL;
CTexture *CResult::m_pTexture = NULL;
CRanking *CResult::m_pRanking = NULL;

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CResult::CResult()
{
	m_nTitleCounter = 0;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CResult::~CResult()
{

}

//================================================
//����������
//================================================
HRESULT CResult::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�ϐ�������
	m_nTitleCounter = 0;

	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//BGM�̍Đ�
	pSound->Play(CSound::SOUND_LABEL_RESULT_BGM);
	//�T�E���h�̉��ʒ���
	pSound->ControllVoice(CSound::SOUND_LABEL_RESULT_BGM, 0.5f);

	//�w�i�̐���
	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	//�w�i�̐���
	m_pScene2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
		CScene::PRIORITY_BG_0);
	//�w�i�̃e�N�X�`�����蓖��
	m_pScene2D->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TYPE_BG_RESULT));

	//�����L���O�̐���
	m_pRanking = CRanking::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 0.0f, 0.0f), D3DXVECTOR3(RANKING_POLYGON_WIDTH, RANKING_POLYGON_HEIGHT, 0.0f));

	return S_OK;
}

//================================================
//�I������
//================================================
void CResult::Uninit(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();
	//BGM�̒�~
	pSound->Stop(CSound::SOUND_LABEL_RESULT_BGM);

	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CResult::Update(void)
{
	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�p�b�h�擾����
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//�J�E���^�[�����Z
	m_nTitleCounter++;
	if (m_nTitleCounter >= RESULT_TO_TITLE_COUNT)
	{
		m_nTitleCounter = 0;

		//�t�F�[�h�擾����
		CFade *pFade;
		pFade = CManager::GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			//�^�C�g���ɍs��
			pFade->SetFade(CManager::MODE_TITLE);
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_START) == true || 
		pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true)
	{
		//�t�F�[�h�擾����
		CFade *pFade;
		pFade = CManager::GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			//SE�̍Đ�
			pSound->Play(CSound::SOUND_LABEL_DECIDE_SE_00);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_DECIDE_SE_00, 0.8f);
			//�^�C�g���ɍs��
			pFade->SetFade(CManager::MODE_TITLE);
		}
	}

	if (m_pRanking != NULL)
	{
		//�X�V����
		m_pRanking->Update();
	}

}

//================================================
//�`�揈��
//================================================
void CResult::Draw(void)
{
	
}

//=============================================================================
// texture�擾����
//=============================================================================
CTexture* CResult::GetTexture(void)
{
	return m_pTexture;
}

//=============================================================================
// bg�擾����
//=============================================================================
CBg* CResult::GetBg(void)
{
	return m_pBg;
}

//=============================================================================
// ranking�擾����
//=============================================================================
CRanking* CResult::GetRanking(void)
{
	return m_pRanking;
}