//================================================
//���U���g����
//Author: KatoMizuki
//================================================
#include "result.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_d.h"
#include "fade.h"
#include "texture.h"
#include "ranking.h"
#include "sound.h"

//================================================
//�}�N����`
//================================================
#define RESULT_TO_TITLE_COUNT			(900)				//�^�C�g���ɍs���܂ł̊Ԋu

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CResult::CResult()
{
	m_nResultCounter = 0;
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
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//BGM�Đ�
	pSound->Play(CSound::SOUND_LABEL_RESULT_BGM);

	//�T�E���h�̉��ʒ���
	pSound->ControllVoice(CSound::SOUND_LABEL_RESULT_BGM, 0.7f);

	CObject2D *pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 
											 D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_UI);
	pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MENU"));

	//�����L���O�̐���
	CRanking::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 0.0f, 0.0f), D3DXVECTOR3(RANKING_POLYGON_WIDTH, RANKING_POLYGON_HEIGHT, 0.0f));

	m_nResultCounter = 0;
	return S_OK;
}

//================================================
//�I������
//================================================
void CResult::Uninit(void)
{	
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//BGM�Đ�
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
			pFade->SetFade(CManager::MODE::TITLE);
		}
	}

	//�J�E���^�[�����Z
	m_nResultCounter++;

	if (m_nResultCounter >= RESULT_TO_TITLE_COUNT)
	{
		m_nResultCounter = 0;

		//�t�F�[�h�擾����
		CFade *pFade;
		pFade = CManager::GetInstance()->GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			//�^�C�g���ɍs��
			pFade->SetFade(CManager::MODE::TITLE);
		}
	}
}

//================================================
//�`�揈��
//================================================
void CResult::Draw(void)
{
	
}