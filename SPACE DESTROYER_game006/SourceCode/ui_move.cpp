//================================================
//�����̂���UI�̏���
//Authore:��������
//================================================
#include "scene2D.h"
#include "scene.h"
#include "manager.h"
#include "ui_move.h"
#include "renderer.h"
#include "texture.h"
#include "menu.h"
#include "game01.h"
#include "tutorial.h"


#ifndef _DEBUG
//#define NDEBUG
#endif // !_DEBUG
#include <assert.h>

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CUiMove::m_pTexture = NULL;

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CUiMove::CUiMove()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nType = UI_MOVE_TYPE_NONE;
	m_bFloatMove = false;
	m_fRot = 0.0f;
	m_fCircleR = 0.0f;
	m_fRotateSpeed = 0.0f;
	m_bRotateReverse = false;
	m_fTanR = 0.0f;
	m_nBlinkCounter = 0;
	m_bBlink = false;
	for (int nCntVertex = 0; nCntVertex < VERTEX_NUM; nCntVertex++)
	{
		m_vertex[nCntVertex] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CUiMove::~CUiMove()
{

}

//================================================
//����������
//================================================
HRESULT CUiMove::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	m_pos = pos;
	m_size = size;
	m_move = move;
	m_fRot = 0.0f;
	m_fRotateSpeed = 0.01f;
	m_fCircleR = sqrtf((float)pow(m_size.x / 2.0f, 2.0f) + (float)pow(m_size.y / 2.0f, 2.0f));
	m_bRotateReverse = true;
	m_nBlinkCounter = 0;
	m_bBlink = false;

	m_vertex[0] = D3DXVECTOR3(pos.x - size.x / 2.0f, pos.y - size.y / 2.0f, 0.0f);
	m_vertex[1] = D3DXVECTOR3(pos.x + size.x / 2.0f, pos.y - size.y / 2.0f, 0.0f);
	m_vertex[2] = D3DXVECTOR3(pos.x - size.x / 2.0f, pos.y + size.y / 2.0f, 0.0f);
	m_vertex[3] = D3DXVECTOR3(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f, 0.0f);

	m_fTanR = atan2f(m_size.y / 2.0f, m_size.x / 2.0f);

	if (m_nType == UI_MOVE_TYPE_MENU_CIRCLE_SMALL || m_nType == UI_MOVE_TYPE_MENU_CIRCLE_BIG)
	{
		m_bFloatMove = false;
	}
	else
	{
		m_bFloatMove = true;
	}

	CUi::Init(pos, size);

	return S_OK;
}

//================================================
//�I������
//================================================
void CUiMove::Uninit(void)
{
	CUi::Uninit();
}

//================================================
//�X�V����
//================================================
void CUiMove::Update(void)
{
	//�ʒu���擾
	m_pos = GetPos();

	//�ړ��ʔ��f
	m_pos += m_move;

	//4���_�̐ݒ�
	m_vertex[0] = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
	m_vertex[1] = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
	m_vertex[2] = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);
	m_vertex[3] = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);

	//�V�[���ɂ�鏈������
	switch (CManager::GetMode())
	{
	case CManager::MODE_TITLE:
		TitleUi();
		break;
	case CManager::MODE_MENU:
		MenuUi();
		break;
	case CManager::MODE_TUTORIAL:
		TutorialUi();
		break;
	case CManager::MODE_GAME01:
		if (GameUi() == true)
		{
			return;
		}
		break;
	case CManager::MODE_RESULT:
		ResultUi();
		break;
	default:
		break;
	}

	//�ʒu�A�T�C�Y�ݒ�
	if (m_nType == UI_MOVE_TYPE_MENU_CIRCLE_SMALL || m_nType == UI_MOVE_TYPE_MENU_CIRCLE_BIG)
	{
		
	}
	else
	{
		SetPos(m_pos, m_size);
	}
}

//================================================
//�`�揈��
//================================================
void CUiMove::Draw(void)
{
	CScene2D::Draw();
}

//================================================
//��������
//================================================
CUiMove *CUiMove::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CUiMove::UI_MOVE_TYPE type)
{
	//�C���X�^���X�̐���
	CUiMove *pUiMove = NULL;
	if (pUiMove == NULL)
	{
		pUiMove = new CUiMove;
		if (pUiMove != NULL)
		{
			switch (type)
			{
			case UI_MOVE_TYPE_TITLE:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_TITLE);
				break;
			case UI_MOVE_TYPE_PRESS_START:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_PRESS_START);
				break;
			case UI_MOVE_TYPE_MENU_CIRCLE_SMALL:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_MENU_CIRCLE_SMALL);
				break;
			case UI_MOVE_TYPE_MENU_CIRCLE_BIG:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_MENU_CIRCLE_BIG);
				break;
			case UI_MOVE_TYPE_MENU_EXPLANATION_GAME:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_MENU_EXPLANATION_GAME);
				break;
			case UI_MOVE_TYPE_MENU_EXPLANATION_TUTORIAL:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_MENU_EXPLANATION_TUTORIAL);
				break;
			case UI_MOVE_TYPE_MENU_EXPLANATION_EXIT:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_MENU_EXPLANATION_EXIT);
				break;
			case UI_MOVE_TYPE_MENU_GAME_START:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_MENU_GAME_START);
				break;
			case UI_MOVE_TYPE_MENU_TUTORIAL:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_MENU_TUTORIAL);
				break;
			case UI_MOVE_TYPE_MENU_EXIT:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_MENU_EXIT);
				break;
			case UI_MOVE_TYPE_PAUSE_EXIT:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_PAUSE_EXIT);
				break;
			case UI_MOVE_TYPE_PAUSE_CONTINUE:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_PAUSE_CONTINUE);
				break;
			case UI_MOVE_TYPE_ENEMY_KILL_SCORE_100:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_ENEMY_KILL_SCORE_100);
				break;
			case UI_MOVE_TYPE_ENEMY_KILL_SCORE_200:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_ENEMY_KILL_SCORE_200);
				break;
			case UI_MOVE_TYPE_ENEMY_KILL_SCORE_400:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_ENEMY_KILL_SCORE_400);
				break;
			default:
				break;
			}
			pUiMove->BindTexture(m_pTexture);
			pUiMove->m_nType = type;
			pUiMove->Init(pos, size, move);
		}
	}
	return pUiMove;
}

//================================================
//�^�C�g���Ŏg��UI�̏���
//================================================
void CUiMove::TitleUi(void)
{
	//��ʂɂ�鏈������
	switch (m_nType)
	{
	case UI_MOVE_TYPE_TITLE:
		if (m_pos.y >= SCREEN_HEIGHT / 2.0f)
		{
			m_pos.y = SCREEN_HEIGHT / 2.0f;
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		break;
	case UI_MOVE_TYPE_PRESS_START:
		//�J�E���^�[�����Z
		m_nBlinkCounter++;
		if (m_bBlink == true)
		{
			if (m_nBlinkCounter >= UI_TITLE_PRESS_START_BLINK_COUNT)
			{
				//�F��߂�
				SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_bBlink = false;
				m_nBlinkCounter = 0;
			}
		}
		else
		{
			if (m_nBlinkCounter >= UI_TITLE_PRESS_START_BLINK_COUNT)
			{
				//�F������
				SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				m_bBlink = true;
				m_nBlinkCounter = 0;
			}
		}
		break;
	default:
		break;
	}
}

//================================================
//���j���[�Ŏg��UI�̏���
//================================================
void CUiMove::MenuUi(void)
{
	//�ǂ̑I�������I������Ă��邩�擾
	int nSelect = CMenu::GetSelect();

	//��ʂɂ�鏈������
	switch (m_nType)
	{
	case UI_MOVE_TYPE_MENU_CIRCLE_SMALL:
		//���V�̓����̏���
		FloatMove();

		//�p�x�����߂�
		m_fTanR = atan2f(m_size.y / 2.0f, m_size.x / 2.0f);

		//UI���o������܂ł̓���
		if (m_bFloatMove == false)
		{
			if (m_pos.y >= UI_MENU_CIRCLE_POS_Y)
			{
				m_move.y = UI_MENU_FLOAT_MOVE;
				m_bFloatMove = true;
				m_pos.y = UI_MENU_CIRCLE_POS_Y;
			}
		}

		//��]�̓���
		m_fRot += m_fRotateSpeed;

		//�t���ɂ��鏈��
		if (m_fRotateSpeed <= -UI_MENU_CIRCLE_SMALL_ROTATE_MAX_SPEED)
		{
			m_bRotateReverse = true;
		}
		else if (m_fRotateSpeed >= UI_MENU_CIRCLE_SMALL_ROTATE_MAX_SPEED)
		{
			m_bRotateReverse = false;
		}

		//�t��]�A����]�̏�������
		if (m_bRotateReverse == true)
		{
			m_fRotateSpeed += UI_MENU_CIRCLE_SMALL_ADD_ROTATE_SPEED;
		}
		else
		{
			m_fRotateSpeed -= UI_MENU_CIRCLE_SMALL_ADD_ROTATE_SPEED;
		}
		
		if (m_fRot <= -D3DX_PI * 2.0f)
		{
			m_fRot += D3DX_PI * 2.0f;
		}

		//4���_�̐ݒ�
		m_vertex[0].x = m_pos.x - m_fCircleR * cosf(m_fTanR - m_fRot);	//���_�̋O����̉~�̒��a*�p�x
		m_vertex[0].y = m_pos.y - m_fCircleR * sinf(m_fTanR - m_fRot);	//���_�̋O����̉~�̒��a*�p�x
		m_vertex[1].x = m_pos.x + m_fCircleR * cosf(m_fTanR + m_fRot);	//���_�̋O����̉~�̒��a*�p�x
		m_vertex[1].y = m_pos.y - m_fCircleR * sinf(m_fTanR + m_fRot);	//���_�̋O����̉~�̒��a*�p�x
		m_vertex[2].x = m_pos.x - m_fCircleR * cosf(m_fTanR + m_fRot);	//���_�̋O����̉~�̒��a*�p�x
		m_vertex[2].y = m_pos.y + m_fCircleR * sinf(m_fTanR + m_fRot);	//���_�̋O����̉~�̒��a*�p�x
		m_vertex[3].x = m_pos.x + m_fCircleR * cosf(m_fTanR - m_fRot);	//���_�̋O����̉~�̒��a*�p�x
		m_vertex[3].y = m_pos.y + m_fCircleR * sinf(m_fTanR - m_fRot);	//���_�̋O����̉~�̒��a*�p�x

		SetVtx(m_pos, m_vertex[0], m_vertex[1], m_vertex[2], m_vertex[3]);

		break;
	case UI_MOVE_TYPE_MENU_CIRCLE_BIG:
		//���V�̓����̏���
		FloatMove();

		//�p�x�����߂�
		m_fTanR = atan2f(m_size.y / 2.0f, m_size.x / 2.0f);

		//UI���o������܂ł̓���
		if (m_bFloatMove == false)
		{
			if (m_pos.y >= UI_MENU_CIRCLE_POS_Y)
			{
				m_move.y = UI_MENU_FLOAT_MOVE;
				m_bFloatMove = true;
				m_pos.y = UI_MENU_CIRCLE_POS_Y;
			}
		}

		//��]�̓���
		m_fRot -= m_fRotateSpeed;

		//�t���ɂ��鏈��
		if (m_fRotateSpeed <= -UI_MENU_CIRCLE_BIG_ROTATE_MAX_SPEED)
		{
			m_bRotateReverse = true;
		}
		else if (m_fRotateSpeed >= UI_MENU_CIRCLE_BIG_ROTATE_MAX_SPEED)
		{
			m_bRotateReverse = false;
		}

		//�t��]�A����]�̏�������
		if (m_bRotateReverse == true)
		{
			m_fRotateSpeed += UI_MENU_CIRCLE_BIG_ADD_ROTATE_SPEED;
		}
		else
		{
			m_fRotateSpeed -= UI_MENU_CIRCLE_BIG_ADD_ROTATE_SPEED;
		}

		if (m_fRot >= D3DX_PI * 2.0f)
		{
			m_fRot -= D3DX_PI * 2.0f;
		}

		//4���_�̐ݒ�
		m_vertex[0].x = m_pos.x - m_fCircleR * cosf(m_fTanR - m_fRot);	//���_�̋O����̉~�̒��a*�p�x
		m_vertex[0].y = m_pos.y - m_fCircleR * sinf(m_fTanR - m_fRot);	//���_�̋O����̉~�̒��a*�p�x
		m_vertex[1].x = m_pos.x + m_fCircleR * cosf(m_fTanR + m_fRot);	//���_�̋O����̉~�̒��a*�p�x
		m_vertex[1].y = m_pos.y - m_fCircleR * sinf(m_fTanR + m_fRot);	//���_�̋O����̉~�̒��a*�p�x
		m_vertex[2].x = m_pos.x - m_fCircleR * cosf(m_fTanR + m_fRot);	//���_�̋O����̉~�̒��a*�p�x
		m_vertex[2].y = m_pos.y + m_fCircleR * sinf(m_fTanR + m_fRot);	//���_�̋O����̉~�̒��a*�p�x
		m_vertex[3].x = m_pos.x + m_fCircleR * cosf(m_fTanR - m_fRot);	//���_�̋O����̉~�̒��a*�p�x
		m_vertex[3].y = m_pos.y + m_fCircleR * sinf(m_fTanR - m_fRot);	//���_�̋O����̉~�̒��a*�p�x

		SetVtx(m_pos, m_vertex[0], m_vertex[1], m_vertex[2], m_vertex[3]);

		break;
	case UI_MOVE_TYPE_MENU_EXPLANATION_GAME:
		//���V�̓����̏���
		FloatMove();

		//UI���o���A�ދ����铮��
		if (nSelect == CMenu::SELECT_MENU_TYPE_GAME_START)
		{
			if (m_pos.x >= UI_MENU_EXPLANATION_TRUE_POS_X)
			{
				m_move.x = 0.0f;
				m_pos.x = UI_MENU_EXPLANATION_TRUE_POS_X;
			}
			else
			{
				m_move.x = UI_MENU_EXPLANATION_MOVE;
			}
		}
		else
		{
			if (m_pos.x <= UI_MENU_EXPLANATION_FALSE_POS_X)
			{
				m_move.x = 0.0f;
				m_pos.x = UI_MENU_EXPLANATION_FALSE_POS_X;
			}
			else
			{
				m_move.x = -UI_MENU_EXPLANATION_MOVE;
			}
		}

		break;
	case UI_MOVE_TYPE_MENU_EXPLANATION_TUTORIAL:
		//���V�̓����̏���
		FloatMove();

		//UI���o���A�ދ����铮��
		if (nSelect == CMenu::SELECT_MENU_TYPE_TUTORIAL)
		{
			if (m_pos.x >= UI_MENU_EXPLANATION_TRUE_POS_X)
			{
				m_move.x = 0.0f;
				m_pos.x = UI_MENU_EXPLANATION_TRUE_POS_X;
			}
			else
			{
				m_move.x = UI_MENU_EXPLANATION_MOVE;
			}
		}
		else
		{
			if (m_pos.x <= UI_MENU_EXPLANATION_FALSE_POS_X)
			{
				m_move.x = 0.0f;
				m_pos.x = UI_MENU_EXPLANATION_FALSE_POS_X;
			}
			else
			{
				m_move.x = -UI_MENU_EXPLANATION_MOVE;
			}
		}
		break;
	case UI_MOVE_TYPE_MENU_EXPLANATION_EXIT:
		//���V�̓����̏���
		FloatMove();

		//UI���o���A�ދ����铮��
		if (nSelect == CMenu::SELECT_MENU_TYPE_EXIT)
		{
			if (m_pos.x >= UI_MENU_EXPLANATION_TRUE_POS_X)
			{
				m_move.x = 0.0f;
				m_pos.x = UI_MENU_EXPLANATION_TRUE_POS_X;
			}
			else
			{
				m_move.x = UI_MENU_EXPLANATION_MOVE;
			}
		}
		else
		{
			if (m_pos.x <= UI_MENU_EXPLANATION_FALSE_POS_X)
			{
				m_move.x = 0.0f;
				m_pos.x = UI_MENU_EXPLANATION_FALSE_POS_X;
			}
			else
			{
				m_move.x = -UI_MENU_EXPLANATION_MOVE;
			}
		}

		break;
	case UI_MOVE_TYPE_MENU_GAME_START:
		//���V�̓����̏���
		FloatMove();

		//UI���o�����铮��
		if (m_pos.x <= UI_MENU_SELECT_TRUE_POS_X)
		{
			m_move.x = 0.0f;
			m_pos.x = UI_MENU_SELECT_TRUE_POS_X;
		}

		if (nSelect == CMenu::SELECT_MENU_TYPE_GAME_START)
		{
			m_size = D3DXVECTOR3(UI_MENU_SELECT_TRUE_WIDTH, UI_MENU_SELECT_TRUE_HEIGHT, 0.0f);
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			m_size = D3DXVECTOR3(UI_MENU_SELECT_FALSE_WIDTH, UI_MENU_SELECT_FALSE_HEIGHT, 0.0f);
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, UI_MENU_NOT_SELECT_COLOR));
		}

		break;
	case UI_MOVE_TYPE_MENU_TUTORIAL:
		//���V�̓����̏���
		FloatMove();


		//UI���o�����铮��
		if (m_pos.x <= UI_MENU_SELECT_TRUE_POS_X)
		{
			m_move.x = 0.0f;
			m_pos.x = UI_MENU_SELECT_TRUE_POS_X;
		}

		if (nSelect == CMenu::SELECT_MENU_TYPE_TUTORIAL)
		{
			m_size = D3DXVECTOR3(UI_MENU_SELECT_TRUE_WIDTH, UI_MENU_SELECT_TRUE_HEIGHT, 0.0f);
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			m_size = D3DXVECTOR3(UI_MENU_SELECT_FALSE_WIDTH, UI_MENU_SELECT_FALSE_HEIGHT, 0.0f);
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, UI_MENU_NOT_SELECT_COLOR));
		}
		break;
	case UI_MOVE_TYPE_MENU_EXIT:
		//���V�̓����̏���
		FloatMove();

		//UI���o�����铮��
		if (m_pos.x <= UI_MENU_SELECT_TRUE_POS_X)
		{
			m_move.x = 0.0f;
			m_pos.x = UI_MENU_SELECT_TRUE_POS_X;
		}

		if (nSelect == CMenu::SELECT_MENU_TYPE_EXIT)
		{
			m_size = D3DXVECTOR3(UI_MENU_SELECT_TRUE_WIDTH, UI_MENU_SELECT_TRUE_HEIGHT, 0.0f);
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			m_size = D3DXVECTOR3(UI_MENU_SELECT_FALSE_WIDTH, UI_MENU_SELECT_FALSE_HEIGHT, 0.0f);
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, UI_MENU_NOT_SELECT_COLOR));
		}

		break;
	default:
		break;
	}
}

//================================================
//�`���[�g���A���Ŏg��UI�̏���
//================================================
void CUiMove::TutorialUi(void)
{
	//�ǂ̑I�������I������Ă��邩�擾
	int nSelect = CTutorial::GetSelect();

	//��ʂɂ�鏈������
	switch (m_nType)
	{
	case UI_MOVE_TYPE_PAUSE_EXIT:
		if (nSelect == CTutorial::SELECT_TUTORIAL_PAUSE_TYPE_EXIT)
		{
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, UI_MENU_NOT_SELECT_COLOR));
		}
		break;
	case UI_MOVE_TYPE_PAUSE_CONTINUE:
		if (nSelect == CTutorial::SELECT_TUTORIAL_PAUSE_TYPE_CONTINUE)
		{
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, UI_MENU_NOT_SELECT_COLOR));
		}
		break;
	default:
		break;
	}
}

//================================================
//�Q�[�����Ŏg��UI�̏���
//================================================
bool CUiMove::GameUi(void)
{
	//�ǂ̑I�������I������Ă��邩�擾
	int nSelect = CGame01::GetSelect();

	//��ʂɂ�鏈������
	switch (m_nType)
	{
	case UI_MOVE_TYPE_PAUSE_EXIT:
		if (nSelect == CGame01::SELECT_GAME01_PAUSE_TYPE_EXIT)
		{
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, UI_MENU_NOT_SELECT_COLOR));
		}
		break;
	case UI_MOVE_TYPE_PAUSE_CONTINUE:
		if (nSelect == CGame01::SELECT_GAME01_PAUSE_TYPE_CONTINUE)
		{
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, UI_MENU_NOT_SELECT_COLOR));
		}
		break;
	case UI_MOVE_TYPE_ENEMY_KILL_SCORE_100:
		//�J�E���^�[�����Z
		m_nBlinkCounter++;
		if (m_nBlinkCounter >= UI_ENEMY_KILL_SCORE_COUNT)
		{
			m_nBlinkCounter = 0;
			//�j��
			Uninit();
			return true;
		}
		break;
	case UI_MOVE_TYPE_ENEMY_KILL_SCORE_200:
		//�J�E���^�[�����Z
		m_nBlinkCounter++;
		if (m_nBlinkCounter >= UI_ENEMY_KILL_SCORE_COUNT)
		{
			m_nBlinkCounter = 0;
			//�j��
			Uninit();
			return true;
		}
		break;
	case UI_MOVE_TYPE_ENEMY_KILL_SCORE_400:
		//�J�E���^�[�����Z
		m_nBlinkCounter++;
		if (m_nBlinkCounter >= UI_ENEMY_KILL_SCORE_COUNT)
		{
			m_nBlinkCounter = 0;
			//�j��
			Uninit();
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}

//================================================
//���U���g�Ŏg��UI�̏���
//================================================
void CUiMove::ResultUi(void)
{

}

//================================================
//���V�̓�������
//================================================
void CUiMove::FloatMove(void)
{
	if (m_bFloatMove == true)
	{
		//Frame�J�E���g�擾
		int nCntFrame = CMenu::GetFrame();
		int nCntReverse = 0;

		//��ʂɂ�鏈������
		switch (m_nType)
		{
		case UI_MOVE_TYPE_MENU_CIRCLE_SMALL:
			nCntReverse = UI_MENU_CIRCLE_FLOAT_MOVE_REVERSE;
			break;
		case UI_MOVE_TYPE_MENU_CIRCLE_BIG:
			nCntReverse = UI_MENU_CIRCLE_FLOAT_MOVE_REVERSE;
			break;
		case UI_MOVE_TYPE_MENU_EXPLANATION_GAME:
			nCntReverse = UI_MENU_EXPLANATION_FLOAT_MOVE_REVERSE;
			break;
		case UI_MOVE_TYPE_MENU_EXPLANATION_TUTORIAL:
			nCntReverse = UI_MENU_EXPLANATION_FLOAT_MOVE_REVERSE;
			break;
		case UI_MOVE_TYPE_MENU_EXPLANATION_EXIT:
			nCntReverse = UI_MENU_EXPLANATION_FLOAT_MOVE_REVERSE;
			break;
		case UI_MOVE_TYPE_MENU_GAME_START:
			nCntReverse = UI_MENU_SELECT_FLOAT_MOVE_REVERSE;
			break;
		case UI_MOVE_TYPE_MENU_TUTORIAL:
			nCntReverse = UI_MENU_SELECT_FLOAT_MOVE_REVERSE;
			break;
		case UI_MOVE_TYPE_MENU_EXIT:
			nCntReverse = UI_MENU_SELECT_FLOAT_MOVE_REVERSE;
			break;
		default:
			break;
		}

		//�㉺�ړ����]
		if (nCntFrame % nCntReverse == 0)
		{
			m_move.y *= -1.0f;
		}
	}
}