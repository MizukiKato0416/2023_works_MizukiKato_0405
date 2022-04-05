//================================================
//�}�l�[�W������
//Author:��������
//================================================
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "title.h"
#include "tutorial.h"
#include "game01.h"
#include "result.h"
#include "menu.h"
#include "texture.h"
#include "x_load.h"
#include "fade.h"
#include "play_data.h"
#include "camera.h"
#include "light.h"
#include "pause.h"
#include "sound.h"
#include "motion.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputPadX *CManager::m_pInputPadX = NULL;
CTitle *CManager::m_pTitle = NULL;
CTexture *CManager::m_pTexture = NULL;
CXload *CManager::m_pXload = NULL;
CFade *CManager::m_pFade = NULL;
CMenu *CManager::m_pMenu = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CGame01 *CManager::m_pGame01 = NULL;
CResult *CManager::m_pResult = NULL;
CManager::MODE CManager::m_mode = MODE_TITLE;
CPlayData *CManager::m_pPlayData = NULL;
CCamera *CManager::m_apCamera[MAX_CAMERA] = {};
CLight *CManager::m_apLight[MAX_LIGHT] = {};
CSound *CManager::m_pSound = NULL;
CMotion *CManager::m_pMotion = NULL;

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CManager::CManager()
{
	memset(&m_apCamera, NULL, sizeof(m_apCamera));
	memset(&m_apLight, NULL, sizeof(m_apLight));
}

//================================================
//�f�X�g���N�^
//================================================
CManager::~CManager()
{

}

//================================================
//����������
//================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//�����ŏ�����
	srand((unsigned int)time(NULL));

	POINT screenPos;
	GetCursorPos(&screenPos);
	SetCursorPos(0, 0);
	ShowCursor(true);

	//�T�E���h�N���X�̐���
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
		if (m_pSound != NULL)
		{
			m_pSound->Init(hWnd);
		}
	}

	//�����_�����O�N���X�̐���
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
		if (m_pRenderer != NULL)
		{
			m_pRenderer->Init(hWnd, bWindow);
		}
	}

	//�L�[�{�[�h�N���X�̐���
	if (m_pInputKeyboard == NULL)
	{
		m_pInputKeyboard = new CInputKeyboard;
		if (m_pInputKeyboard != NULL)
		{
			m_pInputKeyboard->Init(hInstance, hWnd);
		}
	}

	//�p�b�h�N���X�̐���
	if (m_pInputPadX == NULL)
	{
		m_pInputPadX = new CInputPadX;
		if (m_pInputPadX != NULL)
		{
			m_pInputPadX->Init(hInstance, hWnd);
		}
	}

	//�e�N�X�`���N���X�̐���
	if (m_pTexture == NULL)
	{
		m_pTexture = new CTexture;
		if (m_pTexture != NULL)
		{
			m_pTexture->Init();
		}
	}

	//x�t�@�C���ǂݍ��݃N���X�̐���
	if (m_pXload == NULL)
	{
		m_pXload = new CXload;
		if (m_pXload != NULL)
		{
			m_pXload->Init();
		}
	}

	//�v���C�f�[�^�N���X�̐���
	if (m_pPlayData == NULL)
	{
		m_pPlayData = new CPlayData;
		if (m_pPlayData != NULL)
		{
			m_pPlayData->Init();
		}
	}

	//���[�V�����N���X�̐���
	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;
		if (m_pMotion != NULL)
		{
			m_pMotion->Init();
		}
	}

	//���C�g�̐���
	m_apLight[0] = CLight::Create(D3DXVECTOR3(-0.4f, -0.2f, 0.4f), D3DXVECTOR3(400.0f, 800.0f, -400.0f));
	m_apLight[1] = CLight::Create(D3DXVECTOR3(0.4f, 0.8f, -0.4f), D3DXVECTOR3(-100.0f, 0.0f, 100.0f));
	m_apLight[2] = CLight::Create(D3DXVECTOR3(0.0f, -0.4f, 0.4f), D3DXVECTOR3(100.0f, 0.0f, -100.0f));

	//�J�����̐���
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		m_apCamera[nCntCamera] = CCamera::Create(D3DXVECTOR3(0.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
													SCREEN_WIDTH / MAX_CAMERA * nCntCamera, 0.0f,
													SCREEN_WIDTH / MAX_CAMERA, SCREEN_HEIGHT);
		m_apCamera[nCntCamera]->SetNum(nCntCamera);
	}

	//�t�F�[�h�N���X�̐���
	m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
							D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
							MODE_TITLE);
	return S_OK;
}

//================================================
//�I������
//================================================
void CManager::Uninit(void)
{
	//�S�ẴI�u�W�F�N�g�̔j��
	CScene::ReleaseAll();

	//���[�V�����N���X�̔j��
	if (m_pMotion != NULL)
	{
		//�I������
		m_pMotion->Uninit();

		//�������̊J��
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//�J�����̔j��
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		if (m_apCamera[nCntCamera] != NULL)
		{
			//�I������
			m_apCamera[nCntCamera]->Uninit();

			//�������̊J��
			delete m_apCamera[nCntCamera];
			m_apCamera[nCntCamera] = NULL;
		}
	}

	//���C�g�̔j��
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		if (m_apLight[nCntLight] != NULL)
		{
			m_apLight[nCntLight]->Uninit();
			delete m_apLight[nCntLight];
			m_apLight[nCntLight] = NULL;
		}
	}

	//�v���C�f�[�^�N���X�̔j��
	if (m_pPlayData != NULL)
	{
		//�I������
		m_pPlayData->Uninit();

		//�������̊J��
		delete m_pPlayData;
		m_pPlayData = NULL;
	}

	//X�t�@�C���ǂݍ��݃N���X�̔j��
	if (m_pXload != NULL)
	{
		//�I������
		m_pXload->Uninit();

		//�������̊J��
		delete m_pXload;
		m_pXload = NULL;
	}

	//�e�N�X�`���N���X�̔j��
	if (m_pTexture != NULL)
	{
		//�I������
		m_pTexture->Uninit();

		//�������̊J��
		delete m_pTexture;
		m_pTexture = NULL;
	}

	//�p�b�h�N���X�̔j��
	if (m_pInputPadX != NULL)
	{
		//�I������
		m_pInputPadX->Uninit();

		//�������̊J��
		delete m_pInputPadX;
		m_pInputPadX = NULL;
	}

	//�L�[�{�[�h�N���X�̔j��
	if (m_pInputKeyboard != NULL)
	{
		//�I������
		m_pInputKeyboard->Uninit();

		//�������̊J��
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//�����_���[�N���X�̔j��
	if (m_pRenderer != NULL)
	{
		//�I������
		m_pRenderer->Uninit();

		//�������̊J��
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//�T�E���h�N���X�̔j��
	if (m_pSound != NULL)
	{
		//�I������
		m_pSound->Uninit();

		//�������̊J��
		delete m_pSound;
		m_pSound = NULL;
	}
}

//================================================
//�X�V����
//================================================
void CManager::Update(void)
{
	if (CPause::GetPause() == false)
	{
		for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
		{
			//�J�����̍X�V����
			if (m_apCamera[nCntCamera] != NULL)
			{
				m_apCamera[nCntCamera]->Update();
			}
		}
	}

	//�L�[�{�[�h
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	//�p�b�h
	if (m_pInputPadX != NULL)
	{
		m_pInputPadX->Update();
	}

	//�����_���[
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
}

//================================================
//�`�揈��
//================================================
void CManager::Draw(void)
{
	//�����_���[
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=======================================================================
//�ݒ菈��
//=======================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;
	case MODE_MENU:
		if (m_pMenu != NULL)
		{
			m_pMenu->Uninit();
			m_pMenu = NULL;
		}
		break;
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			m_pTutorial = NULL;
		}
		break;
	case MODE_GAME01:
		if (m_pGame01 != NULL)
		{
			m_pGame01->Uninit();
			m_pGame01 = NULL;
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;
	}

	//�S�ẴI�u�W�F�N�g�̔j��
	CScene::ReleaseAll();

	m_mode = mode;

	switch (mode)
	{
	case MODE_TITLE:
		//�^�C�g���N���X�̐���
		if (m_pTitle == NULL)
		{
			m_pTitle = new CTitle;
			if (m_pTitle != NULL)
			{
				m_pTitle->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}
		break;
	case MODE_MENU:
		//���j���[�N���X�̐���
		if (m_pMenu == NULL)
		{
			m_pMenu = new CMenu;
			if (m_pMenu != NULL)
			{
				m_pMenu->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}
		break;
	case MODE_TUTORIAL:
		//�`���[�g���A���N���X�̐���
		if (m_pTutorial == NULL)
		{
			m_pTutorial = new CTutorial;
			if (m_pTutorial != NULL)
			{
				//�J�����̔j��
				for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
				{
					if (m_apCamera[nCntCamera] != NULL)
					{
						//�I������
						m_apCamera[nCntCamera]->Uninit();

						//�������̊J��
						delete m_apCamera[nCntCamera];
						m_apCamera[nCntCamera] = NULL;
					}
				}

				//�J�����̐���
				for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
				{
					m_apCamera[nCntCamera] = CCamera::Create(D3DXVECTOR3(0.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
															SCREEN_WIDTH / MAX_CAMERA * nCntCamera, 0.0f,
															SCREEN_WIDTH / MAX_CAMERA, SCREEN_HEIGHT);
					m_apCamera[nCntCamera]->SetNum(nCntCamera);
				}

				m_pTutorial->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}
		break;
	case MODE_GAME01:
		//�Q�[��01�N���X�̐���
		if (m_pGame01 == NULL)
		{
			m_pGame01 = new CGame01;
			if (m_pGame01 != NULL)
			{
				//�J�����̔j��
				for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
				{
					if (m_apCamera[nCntCamera] != NULL)
					{
						//�I������
						m_apCamera[nCntCamera]->Uninit();

						//�������̊J��
						delete m_apCamera[nCntCamera];
						m_apCamera[nCntCamera] = NULL;
					}
				}

				//�J�����̐���
				for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
				{
					m_apCamera[nCntCamera] = CCamera::Create(D3DXVECTOR3(0.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
															SCREEN_WIDTH / MAX_CAMERA * nCntCamera, 0.0f,
															SCREEN_WIDTH / MAX_CAMERA, SCREEN_HEIGHT);
					m_apCamera[nCntCamera]->SetNum(nCntCamera);
				}

				m_pGame01->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}
		break;
	case MODE_RESULT:
		//���U���g�N���X�̐���
		if (m_pResult == NULL)
		{
			m_pResult = new CResult;
			if (m_pResult != NULL)
			{
				//�J�����̔j��
				for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
				{
					if (m_apCamera[nCntCamera] != NULL)
					{
						//�I������
						m_apCamera[nCntCamera]->Uninit();

						//�������̊J��
						delete m_apCamera[nCntCamera];
						m_apCamera[nCntCamera] = NULL;
					}
				}

				//�J�����̐���
				for (int nCntCamera = 0; nCntCamera < MAX_RESULT_CAMERA; nCntCamera++)
				{
					m_apCamera[nCntCamera] = CCamera::Create(D3DXVECTOR3(0.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
																SCREEN_WIDTH / MAX_RESULT_CAMERA * nCntCamera, 0.0f,
																SCREEN_WIDTH / MAX_RESULT_CAMERA, SCREEN_HEIGHT);
					m_apCamera[nCntCamera]->SetNum(nCntCamera);
				}

				m_pResult->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}
		break;
	}
}


//=============================================================================
// ���[�h�擾����
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
// fade�擾����
//=============================================================================
CFade* CManager::GetFade(void)
{
	return m_pFade;
}

//=============================================================================
// Renderer�擾����
//=============================================================================
CRenderer* CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// InputKeyboard�擾����
//=============================================================================
CInputKeyboard* CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
// InputKeyboard�擾����
//=============================================================================
CInputPadX* CManager::GetInputPadX(void)
{
	return m_pInputPadX;
}

//=============================================================================
// title�擾����
//=============================================================================
CTitle* CManager::GetTitle(void)
{
	return m_pTitle;
}

//=============================================================================
// menu�擾����
//=============================================================================
CMenu* CManager::GetMenu(void)
{
	return m_pMenu;
}

//=============================================================================
// tutorial�擾����
//=============================================================================
CTutorial* CManager::GetTutorial(void)
{
	return m_pTutorial;
}

//=============================================================================
// game01�擾����
//=============================================================================
CGame01* CManager::GetGame01(void)
{
	return m_pGame01;
}

//=============================================================================
// result�擾����
//=============================================================================
CResult* CManager::GetResult(void)
{
	return m_pResult;
}

//=============================================================================
// texture�擾����
//=============================================================================
CTexture* CManager::GetTexture(void)
{
	return m_pTexture;
}

//=============================================================================
// Xload�擾����
//=============================================================================
CXload* CManager::GetXload(void)
{
	return m_pXload;
}

//=============================================================================
// play_data�擾����
//=============================================================================
CPlayData* CManager::GetPlayData(void)
{
	return m_pPlayData;
}

//=============================================================================
// camera�擾����
//=============================================================================
CCamera** CManager::GetCamera(void)
{
	return &m_apCamera[0];
}

//=============================================================================
// light�擾����
//=============================================================================
CLight* CManager::GetLight(void)
{
	return m_apLight[0];
}

//=============================================================================
// sound�擾����
//=============================================================================
CSound* CManager::GetSound(void)
{
	return m_pSound;
}