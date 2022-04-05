#//=============================================================================
// �㉺����ǂ̃R���g���[������ [control_up_down_wall.cpp]
// Author : KUSAKARI KAKERU
//=============================================================================
#include "control_up_down_wall.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CControlUpDownWall::CControlUpDownWall()
{
	m_fMoveLength = 0;
	m_nWaitTime = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CControlUpDownWall::~CControlUpDownWall()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CControlUpDownWall::Init(void)
{
	// �������g���ė����̏�����
	srand((unsigned int)time(NULL));

	m_fMoveLength = 0;
	m_nWaitTime = 50;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CControlUpDownWall::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CControlUpDownWall::Update(CScene *pScene)
{
	// m_bUpDown��false�̎��ɏ㏸
	if (m_bUpDown == false)
	{
		// �ړ��ł���͈͊O�ɂȂ����牺�~�ɐ؂�ւ���
		if (m_fMoveLength > m_moveLimit)
		{
			m_nWaitTime--;

			//�ҋ@���Ԃ̊Ԃ͈ړ��ʂ�0��
			m_move.y = 0;

			//�ҋ@���Ԃ�0�ɂȂ�����
			if (m_nWaitTime <= 0)
			{
				m_fMoveLength = 0;
				m_bUpDown = true;
			}
		}
		else
		{
			m_move.y += MOVE_UPDOWN_WALL_SPEED;
			m_fMoveLength += MOVE_UPDOWN_WALL_SPEED;
		}
	}
	// m_bUpDown��true�̎��ɉ��~
	else if (m_bUpDown == true)
	{
		// �ړ��ł���͈͊O�ɂȂ�����㏸�ɐ؂�ւ���
		if (m_fMoveLength < -m_moveLimit)
		{
			m_move.y = 0;
			m_fMoveLength = 0;

			//�ҋ@���Ԃ������_���ɕύX(����50�`350)
			int nRumdomNumber = rand() % 300 + 50;
			m_nWaitTime = nRumdomNumber;

			m_bUpDown = false;
		}
		else
		{
			m_move.y -= MOVE_UPDOWN_WALL_SPEED;
			m_fMoveLength -= MOVE_UPDOWN_WALL_SPEED;
		}
	}

	// �ő�ړ���
	if (m_move.y > MAX_UPDOWN_WALL_SPEED)
	{
		m_move.y = MAX_UPDOWN_WALL_SPEED;
	}

	if (m_move.y < -MAX_UPDOWN_WALL_SPEED)
	{
		m_move.y = -MAX_UPDOWN_WALL_SPEED;
	}
}

//================================================
//��������
//================================================
CControlUpDownWall *CControlUpDownWall::Create(UP_DOWN_WALL type, float moveLimit)
{
	//�C���X�^���X�̐���
	CControlUpDownWall *pControlUpDownWall = NULL;
	if (pControlUpDownWall == NULL)
	{
		pControlUpDownWall = new CControlUpDownWall;
		if (pControlUpDownWall != NULL)
		{
			switch (type)
			{
			case UP_WALL:
				pControlUpDownWall->m_bUpDown = false;
				break;

			case DOWN_WALL:
				pControlUpDownWall->m_bUpDown = true;
				break;

			default:
				break;
			}

			pControlUpDownWall->m_moveLimit = moveLimit;
			pControlUpDownWall->Init();
		}
	}
	return pControlUpDownWall;
}