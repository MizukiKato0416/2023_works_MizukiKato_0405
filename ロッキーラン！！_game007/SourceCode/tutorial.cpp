//================================================
//�`���[�g���A������
//Authore: UENOYAMA TAIGA
//================================================
#include "renderer.h"
#include "tutorial.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "scene3D.h"
#include "texture.h"
#include "meshfield.h"
#include "meshsphere.h"
#include "fade.h"
#include "player.h"
#include "model_single.h"
#include "ui.h"
#include "sound.h"
#include "pause.h"

#include "camera.h"
//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CTutorial::CTutorial()
{
	memset(&m_apPlayer, NULL, sizeof(m_apPlayer));
	memset(&m_apUi, NULL, sizeof(m_apUi));
	m_nNumScene2D = 0;
	m_nSelect = 0;
	m_pMeshField = NULL;
	m_pMeshSphere = NULL;
	m_bGoal = false;
	m_pScene3D = NULL;
	memset(&m_apModelSingle, NULL, sizeof(m_apModelSingle));
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
	m_nNumScene2D = 0;
	m_nSelect = 0;

	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();
	//BGM�Đ�
	pSound->Play(CSound::SOUND_LABEL_TUTORIAL_BGM);
	//���ʒ���
	pSound->ControllVoice(CSound::SOUND_LABEL_TUTORIAL_BGM, 0.5f);
	//UI�̐���
	m_apUi[0] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, TUTORIAL_EXPLANATION_POS_Y, 0.0f), 
							D3DXVECTOR3(TUTORIAL_EXPLANATION_SIZE_X, TUTORIAL_EXPLANATION_SIZE_Y, 0.0f), PRIORITY_UI, CUi::UI_TYPE_TUTORIAL_EXPLANATION);	//�������

	m_apUi[1] = CUi::Create(D3DXVECTOR3(TUTORIAL_1P_TEX_POS_X, TUTORIAL_PLAYERNUMBER_TEX_POS_Y, 0.0f), 
							D3DXVECTOR3(TUTORIAL_PLAYERNUMBER_TEX_SIZE_X, TUTORIAL_PLAYERNUMBER_TEX_SIZE_Y, 0.0f), PRIORITY_UI, CUi::UI_TYPE_PLAYER_1P);	//1P�\��

	m_apUi[2] = CUi::Create(D3DXVECTOR3(TUTORIAL_2P_TEX_POS_X, TUTORIAL_PLAYERNUMBER_TEX_POS_Y, 0.0f), 
							D3DXVECTOR3(TUTORIAL_PLAYERNUMBER_TEX_SIZE_X, TUTORIAL_PLAYERNUMBER_TEX_SIZE_Y, 0.0f), PRIORITY_UI, CUi::UI_TYPE_PLAYER_2P);	//2P�\��

	//���b�V���X�t�B�A�̐���
	m_pMeshSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, -200.0f, 0.0f), D3DXVECTOR3(TUTORIAL_WORLD_SIZE, TUTORIAL_WORLD_SIZE, TUTORIAL_WORLD_SIZE), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 128, 32);
	m_pMeshSphere->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_SKY));

	//���b�V���t�B�[���h�̐���
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, -200.0f, 0.0f), D3DXVECTOR3(TUTORIAL_WORLD_SIZE, 0.0f, TUTORIAL_WORLD_SIZE), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2, 2);
	m_pMeshField->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TILE));

	//�|�[�Y�̐���
	m_pPause = CPause::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�X�^�[�g���̐���
	m_apModelSingle[0] = CModelSingle::Create(D3DXVECTOR3(0.0f, 0.0f, TUTORIAL_START_FLOOR_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_START_FLOOR, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

	//�~�h����O���̐���
	m_apModelSingle[1] = CModelSingle::Create(D3DXVECTOR3(0.0f, 0.0f, TUTORIAL_MIDDLE_FLOOR_FRONT_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_MIDDLE_FLOOR, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

	//�~�h�������̐���
	m_apModelSingle[2] = CModelSingle::Create(D3DXVECTOR3(0.0f, 0.0f, TUTORIAL_MIDDLE_FLOOR_BACK_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_MIDDLE_FLOOR, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

	//�S�[�����̐���
	m_apModelSingle[3] = CModelSingle::Create(D3DXVECTOR3(0.0f, 0.0f, TUTORIAL_GOAL_FLOOR_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_GOAL_FLOOR, NULL, CModelSingle::MODEL_SINGLE_TYPE_GOAL);

	//�X�^�[�g�ƃS�[���̌���̐���
	m_apModelSingle[4] = CModelSingle::Create(D3DXVECTOR3(0.0f, TUTORIAL_FENCE_POS_Y, TUTORIAL_START_FLOOR_POS_Z - 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_BACKFENCE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[5] = CModelSingle::Create(D3DXVECTOR3(0.0f, TUTORIAL_FENCE_POS_Y, TUTORIAL_GOAL_FLOOR_POS_Z + 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_BACKFENCE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

	//�X�^�[�g�ƃS�[���̃T�C�h��̐���
	m_apModelSingle[6] = CModelSingle::Create(D3DXVECTOR3(-TUTORIAL_FENCE_POS_X, TUTORIAL_FENCE_POS_Y, TUTORIAL_START_FLOOR_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_SIDEFENCE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[7] = CModelSingle::Create(D3DXVECTOR3(TUTORIAL_FENCE_POS_X, TUTORIAL_FENCE_POS_Y, TUTORIAL_START_FLOOR_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_SIDEFENCE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[8] = CModelSingle::Create(D3DXVECTOR3(-TUTORIAL_FENCE_POS_X, TUTORIAL_FENCE_POS_Y, TUTORIAL_GOAL_FLOOR_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_SIDEFENCE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[9] = CModelSingle::Create(D3DXVECTOR3(TUTORIAL_FENCE_POS_X, TUTORIAL_FENCE_POS_Y, TUTORIAL_GOAL_FLOOR_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_SIDEFENCE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

	//�~�h����̐���
	m_apModelSingle[10] = CModelSingle::Create(D3DXVECTOR3(-TUTORIAL_FENCE_POS_X, TUTORIAL_FENCE_POS_Y, TUTORIAL_MIDDLE_FLOOR_FRONT_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_MIDDLE_FENCE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[11] = CModelSingle::Create(D3DXVECTOR3(TUTORIAL_FENCE_POS_X, TUTORIAL_FENCE_POS_Y, TUTORIAL_MIDDLE_FLOOR_FRONT_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_MIDDLE_FENCE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[12] = CModelSingle::Create(D3DXVECTOR3(-TUTORIAL_FENCE_POS_X, TUTORIAL_FENCE_POS_Y, TUTORIAL_MIDDLE_FLOOR_BACK_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_MIDDLE_FENCE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[13] = CModelSingle::Create(D3DXVECTOR3(TUTORIAL_FENCE_POS_X, TUTORIAL_FENCE_POS_Y, TUTORIAL_MIDDLE_FLOOR_BACK_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_MIDDLE_FENCE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

	//�S�[���̒��̐���
	m_apModelSingle[14] = CModelSingle::Create(D3DXVECTOR3(-TUTORIAL_GOAL_POLE_POS_X, TUTORIAL_GOAL_POLE_POS_Y, TUTORIAL_GOAL_POLE_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_GOAL_POLE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[15] = CModelSingle::Create(D3DXVECTOR3(TUTORIAL_GOAL_POLE_POS_X, TUTORIAL_GOAL_POLE_POS_Y, TUTORIAL_GOAL_POLE_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_GOAL_POLE, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

	//�S�[���̊��̐���
	m_apModelSingle[16] = CModelSingle::Create(D3DXVECTOR3(0.0f, TUTORIAL_GOAL_FLAG_POS_Y, TUTORIAL_GOAL_FLAG_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TUTORIAL_GOAL_FLAG, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	
	//��s�D�̐���
	m_apModelSingle[17] = CModelSingle::Create(D3DXVECTOR3(-600.0f, 0.0f, 3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_AIRSHIP, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[18] = CModelSingle::Create(D3DXVECTOR3(2000.0f, 0.0f, 8000.0f), D3DXVECTOR3(0.0f,D3DX_PI / 2, 0.0f), CXload::X_TYPE_AIRSHIP, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[19] = CModelSingle::Create(D3DXVECTOR3(1500.0f, 0.0f, -5000.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), CXload::X_TYPE_AIRSHIP, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

	//�C���̐���
	m_apModelSingle[20] = CModelSingle::Create(D3DXVECTOR3(600.0f, 50.0f, -360.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_BALLOON, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[21] = CModelSingle::Create(D3DXVECTOR3(800.0f, 150.0f, 1060.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_BALLOON, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[22] = CModelSingle::Create(D3DXVECTOR3(-500.0f, 0.0f, 900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_BALLOON, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[23] = CModelSingle::Create(D3DXVECTOR3(0.0f, 30.0f, -800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_BALLOON, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

	//���̐���
	m_apModelSingle[24] = CModelSingle::Create(D3DXVECTOR3(320.0f, 50.0f, 325.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), CXload::X_TYPE_ARROW, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[25] = CModelSingle::Create(D3DXVECTOR3(-320.0f, 50.0f, 325.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), CXload::X_TYPE_ARROW, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

	//�`�F�b�N�|�C���g�̐���
	m_apModelSingle[26] = CModelSingle::Create(D3DXVECTOR3(310.0f, 60.0f, 262.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_CHECKPOINT, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[27] = CModelSingle::Create(D3DXVECTOR3(-310.0f, 60.0f, 262.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_CHECKPOINT, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);

	//�`�F�b�N�|�C���g�̐���
	m_apModelSingle[28] = CModelSingle::Create(D3DXVECTOR3(-3100.0f,-60.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_CLOUD, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[29] = CModelSingle::Create(D3DXVECTOR3(4300.0f, -70.0f, 20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_CLOUD, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[30] = CModelSingle::Create(D3DXVECTOR3(-6350.0f,  -90.0f, -2600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_CLOUD, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[31] = CModelSingle::Create(D3DXVECTOR3(5705.0f,  -130.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_CLOUD, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[32] = CModelSingle::Create(D3DXVECTOR3(6800.0f, -750.0f, -800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_CLOUD, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[33] = CModelSingle::Create(D3DXVECTOR3(-3010.0f,-90.0f, 2550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_CLOUD, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[34] = CModelSingle::Create(D3DXVECTOR3(7605.0f,  -100.0f, 3040.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_CLOUD, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[35] = CModelSingle::Create(D3DXVECTOR3(-4020.0f, -65.0f, 5000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_CLOUD, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);
	m_apModelSingle[36] = CModelSingle::Create(D3DXVECTOR3(-2400.0f, -88.0f, -3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_CLOUD, NULL, CModelSingle::MODEL_SINGLE_TYPE_NONE);


	//�S�[���e�[�v�̐���
	m_pScene3D = CScene3D::Create(D3DXVECTOR3(0.0f, 10.0f, TUTORIAL_GOAL_FLOOR_POS_Z - 87.0f), D3DXVECTOR3(600.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CScene3D::PRIORITY_MODEL);
	m_pScene3D->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_GOAL_TAPE));

	//�v���C���[�̐���
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		m_apPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(-TUTORIAL_PLAYER_SPAWN_POS_X + (TUTORIAL_PLAYER_SPAWN_WIDTH * nCntPlayer),
																TUTORIAL_PLAYER_SPAWN_POS_Y,
																TUTORIAL_PLAYER_SPAWN_POS_Z),
													D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), nCntPlayer);
	}

	return S_OK;
}

//================================================
//�I������
//================================================
void CTutorial::Uninit(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//���Đ�����Ă�T�E���h���~�߂�
	pSound->Stop();

	//�I�u�W�F�N�g�̔j��
	Release();

	//�v���C���[�̔j��
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (m_apPlayer[nCntPlayer] != NULL)
		{
			m_apPlayer[nCntPlayer]->Uninit();
			delete m_apPlayer[nCntPlayer];
			m_apPlayer[nCntPlayer] = NULL;
		}
	}
}

//================================================
//�X�V����
//================================================
void CTutorial::Update(void)
{
	//�v���C���[�̈ʒu�擾����
	D3DXVECTOR3 aPosPlayer[MAX_PLAYER];
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		//������
		aPosPlayer[nCntPlayer] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//NULL�`�F�b�N
		if (m_apPlayer[nCntPlayer] != NULL)
		{
			aPosPlayer[nCntPlayer] = m_apPlayer[nCntPlayer]->GetPos();
		}
	}

	//�t�F�[�h�擾����
	CFade *pFade;
	pFade = CManager::GetFade();

	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//�p�b�h�擾����
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//�v���C���[��y���W��0��菬�����Ȃ�����
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (aPosPlayer[nCntPlayer].y <= PLAYER_UNINIT_POS_Y)
		{
			if (m_apPlayer[nCntPlayer] != NULL)
			{
				//�v���C���[������
				m_apPlayer[nCntPlayer]->Uninit();
				delete m_apPlayer[nCntPlayer];
				m_apPlayer[nCntPlayer] = NULL;
			}
			if (m_apPlayer[nCntPlayer] == NULL)
			{
				m_apPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(-TUTORIAL_PLAYER_SPAWN_POS_X + (TUTORIAL_PLAYER_SPAWN_WIDTH * nCntPlayer),
																		TUTORIAL_PLAYER_SPAWN_POS_Y,
																		TUTORIAL_PLAYER_SPAWN_POS_Z),
															D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), nCntPlayer);
			}
		}
	}

	//�S�[��������
	if (m_bGoal == true)
	{
		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{
			if (m_apPlayer[nCntPlayer] != NULL)
			{
				//�v���C���[������
				m_apPlayer[nCntPlayer]->Uninit();
				delete m_apPlayer[nCntPlayer];
				m_apPlayer[nCntPlayer] = NULL;
			}
		}
		if (m_apUi[3] == NULL)
		{
			//BGM���~�߂�
			pSound->Stop(CSound::SOUND_LABEL_TUTORIAL_BGM);
			//�N���ASE�Đ�
			pSound->Play(CSound::SOUND_LABEL_GAMECLEAR_SE);

			m_apUi[3] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
									D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT / 2.0f, 0.0f), PRIORITY_UI, CUi::UI_TYPE_GAME_GOAL);
		}

		//�J�E���g�����Z
		m_nFrame++;
		if (m_nFrame >= TUTORIAL_NEXT_SCENE_COUNT)
		{
			m_nFrame = 0;
			//���U���g�ɑJ��
			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				pFade->SetFade(CManager::MODE_MENU);
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

//================================================
//�S�[������擾
//================================================
void CTutorial::SetGoal(bool bGoal)
{
	m_bGoal = bGoal;
}
//================================================
//�S�[������n��
//================================================
bool CTutorial::GetGoal()
{
	return m_bGoal;
}