//================================================
//���U���g����
//Author: ��������
//================================================
#include "renderer.h"
#include "result.h"
#include "manager.h"
#include "texture.h"
#include "ranking.h"
#include "manager.h"
#include "input_keyboard.h"
#include "meshfield.h"
#include "meshsphere.h"
#include "model_single.h"
#include "input_pad_x.h"
#include "fade.h"
#include "sound.h"
#include "play_data.h"
#include "ui.h"
#include "motion_player.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CResult::CResult()
{
	memset(&m_apPlayer, NULL, sizeof(m_apPlayer));
	m_pMeshField = NULL;
	m_pMeshSphere = NULL;
	m_pRanking = NULL;
	memset(&m_apModelSingle, NULL, sizeof(m_apModelSingle));
	memset(&m_apUi, NULL, sizeof(m_apUi));
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
	pSound = CManager::GetSound();
	//BGM�Đ�
	pSound->Play(CSound::SOUND_LABEL_RESULT_BGM);
	//���ʒ���
	pSound->ControllVoice(CSound::SOUND_LABEL_RESULT_BGM, 0.5f);

	if(CManager::GetPlayData()->GetWinNum() == -1)
	{
		m_pScene2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), PRIORITY_NONE);
		m_pScene2D->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_RESULT_BG));

		if (m_pRanking == NULL)
		{
			//�����L���O�̐���
			m_pRanking = CRanking::Create(D3DXVECTOR3(SCREEN_WIDTH + RANKING_POLYGON_WIDTH * MAX_SCORE_POLYGON / 2.0f, RESULT_RANKING_POSY, 0.0f),
											D3DXVECTOR3(RANKING_POLYGON_WIDTH, RANKING_POLYGON_HEIGHT, 0.0f));
		}
	}
	else
	{
		//���b�V���X�t�B�A�̐���
		m_pMeshSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, -200.0f, 0.0f), D3DXVECTOR3(RESULT_WORLD_SIZE, RESULT_WORLD_SIZE, RESULT_WORLD_SIZE),
											D3DXVECTOR3(0.0f, 0.0f, 0.0f), 128, 32);
		m_pMeshSphere->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_SKY));

		//���b�V���t�B�[���h�̐���
		m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, -200.0f, 0.0f), D3DXVECTOR3(RESULT_WORLD_SIZE, 0.0f, RESULT_WORLD_SIZE),
											D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2, 2);
		m_pMeshField->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TILE));

		//�X�^�[�g���̐���
		m_apModelSingle[0] = CModelSingle::Create(D3DXVECTOR3(0.0f, 0.0f, -330.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_GOAL_FLOOR, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

		m_apModelSingle[1] = CModelSingle::Create(D3DXVECTOR3(0.0f, 10.0f, -330.0f + 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_BACKFENCE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

		m_apModelSingle[2] = CModelSingle::Create(D3DXVECTOR3(-310.0f, 10.0f, -330.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_SIDEFENCE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
		m_apModelSingle[3] = CModelSingle::Create(D3DXVECTOR3(310.0f, 10.0f, -330.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_SIDEFENCE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

		//�S�[���̒��̐���
		m_apModelSingle[4] = CModelSingle::Create(D3DXVECTOR3(-280.0f, 0.0f, -330.0f - 99.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_GOAL_POLE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
		m_apModelSingle[5] = CModelSingle::Create(D3DXVECTOR3(280.0f, 0.0f, -330.0f - 99.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_GOAL_POLE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

		//�S�[���̊��̐���
		m_apModelSingle[6] = CModelSingle::Create(D3DXVECTOR3(0.0f, 200.0f, -330.0f - 99.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_GOAL_FLAG, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

		//�����̐���
		m_apModelSingle[7] = CModelSingle::Create(D3DXVECTOR3(0.0f, 10.0f, -330.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_RESULT_CROWN, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

		//�C���̐���
		m_apModelSingle[7] = CModelSingle::Create(D3DXVECTOR3(-350.0f, 10.0f, -130.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_BALLOON, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
		m_apModelSingle[8] = CModelSingle::Create(D3DXVECTOR3(100.0f, -60.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_BALLOON, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
		m_apModelSingle[9] = CModelSingle::Create(D3DXVECTOR3(-100.0f, 10.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_BALLOON, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
		m_apModelSingle[10] = CModelSingle::Create(D3DXVECTOR3(400.0f, 10.0f, 450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_BALLOON, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	}
	
	int nNum = 0;
	switch (CManager::GetPlayData()->GetWinNum())
	{
	case 0:
		//�v���C���[�̐���
		m_apPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, 60.0f, -330.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
		m_apPlayer[1] = CPlayer::Create(D3DXVECTOR3(50.0f, 60.0f, -330.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);

		//�v���C���[�i���o�[����
		m_apUi[0] = CUi::Create(D3DXVECTOR3(RESULT_PLAYERNUMBER_POS_X + SCREEN_WIDTH, RESULT_PLAYERNUMBER_POS_Y, 0.0f),
								D3DXVECTOR3(RESULT_PLAYERNUMBER_SIZE_X, RESULT_PLAYERNUMBER_SIZE_Y, 0.0f), PRIORITY_UI, CUi::UI_TYPE_PLAYER_1P);
		//WinUI����
		m_apUi[1] = CUi::Create(D3DXVECTOR3(RESULT_WIN_POS_X + SCREEN_WIDTH, RESULT_WIN_POS_Y, 0.0f),
								D3DXVECTOR3(RESULT_WIN_SIZE_X, RESULT_WIN_SIZE_Y, 0.0f), PRIORITY_UI, CUi::UI_TYPE_RESULT_WIN);

		break;
	case 1:
		//�v���C���[�̐���
		m_apPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, 60.0f, -330.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
		m_apPlayer[1] = CPlayer::Create(D3DXVECTOR3(50.0f, 60.0f, -330.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

		//�v���C���[�i���o�[����
		m_apUi[0] = CUi::Create(D3DXVECTOR3(RESULT_PLAYERNUMBER_POS_X + SCREEN_WIDTH, RESULT_PLAYERNUMBER_POS_Y, 0.0f),
								D3DXVECTOR3(RESULT_PLAYERNUMBER_SIZE_X, RESULT_PLAYERNUMBER_SIZE_Y, 0.0f), PRIORITY_UI, CUi::UI_TYPE_PLAYER_2P);
		//WinUI����
		m_apUi[1] = CUi::Create(D3DXVECTOR3(RESULT_WIN_POS_X + SCREEN_WIDTH, RESULT_WIN_POS_Y, 0.0f),
								D3DXVECTOR3(RESULT_WIN_SIZE_X, RESULT_WIN_SIZE_Y, 0.0f), PRIORITY_UI, CUi::UI_TYPE_RESULT_WIN);
		break;
	default:
		break;
	}

	if (CManager::GetPlayData()->GetWinNum() != -1)
	{
		int nRandMotion = rand() % 4;
		//���[�V�����̊��蓖��
		switch (nRandMotion)
		{
		case 0:
			m_apPlayer[0]->GetMotionPlayer()->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_GLAD_01);
			break;
		case 1:
			m_apPlayer[0]->GetMotionPlayer()->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_GLAD_02);
			break;
		case 2:
			m_apPlayer[0]->GetMotionPlayer()->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_GLAD_03);
			break;
		case 3:
			m_apPlayer[0]->GetMotionPlayer()->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_GLAD_04);
			break;
		default:
			break;
		}
		m_apPlayer[1]->GetMotionPlayer()->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_APPLAUSE);
	}

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

	//���Đ�����Ă�T�E���h���~�߂�
	pSound->Stop();

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

	//�J�E���^�[�����Z
	m_nTitleCounter++;

	//UI�̈ړ�
	for (int nCntUi = 0; nCntUi < RESULT_MAX_UI; nCntUi++)
	{
		if (m_apUi[nCntUi] != NULL)
		{
			//�ʒu�ƃT�C�Y�擾����
			D3DXVECTOR3 pos = m_apUi[nCntUi]->GetPos();
			D3DXVECTOR3 size = m_apUi[nCntUi]->GetSize();

			switch (nCntUi)
			{
			case 0:
				if (pos.x > RESULT_PLAYERNUMBER_POS_X)
				{
					pos.x -= 30.0f;
					if (pos.x <= RESULT_PLAYERNUMBER_POS_X)
					{
						pos.x = RESULT_PLAYERNUMBER_POS_X;
					}
				}
				break;
			case 1:
				if (pos.x > RESULT_WIN_POS_X)
				{
					pos.x -= 30.0f;
					if (pos.x <= RESULT_WIN_POS_X)
					{
						pos.x = RESULT_WIN_POS_X;
					}
				}
				break;
			default:
				break;
			}
			m_apUi[nCntUi]->SetPos(pos, size);
		}
	}

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
	else if (m_nTitleCounter >= RESULT_TO_TITLE_COUNT / 3)
	{
		if (CManager::GetPlayData()->GetWinNum() != -1)
		{
			if (m_pRanking == NULL)
			{
				//�����L���O�̐���
				m_pRanking = CRanking::Create(D3DXVECTOR3(SCREEN_WIDTH + RANKING_POLYGON_WIDTH * MAX_SCORE_POLYGON / 2.0f, RESULT_RANKING_POSY, 0.0f),
												D3DXVECTOR3(RANKING_POLYGON_WIDTH, RANKING_POLYGON_HEIGHT, 0.0f));
			}
			for (int nCntUi = 0; nCntUi < RESULT_MAX_UI; nCntUi++)
			{
				if (m_apUi[nCntUi] != NULL)
				{
					m_apUi[nCntUi]->Uninit();
					m_apUi[nCntUi] = NULL;
				}
			}
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_START, 0) == true ||
		pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B, 0) == true)
	{
		//�t�F�[�h�擾����
		CFade *pFade;
		pFade = CManager::GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			//�^�C�g���ɍs��
			pFade->SetFade(CManager::MODE_TITLE);
		}
	}
}

//================================================
//�`�揈��
//================================================
void CResult::Draw(void)
{
	
}
