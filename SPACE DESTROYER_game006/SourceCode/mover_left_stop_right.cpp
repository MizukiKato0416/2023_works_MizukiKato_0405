//================================================
//���ɍs����~���E�ɍs�������̏���
//Authore:��������
//================================================
#include "mover_left_stop_right.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CMoverLeftStopRight::CMoverLeftStopRight()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrameCounter = 0;
	m_moveType = MOVE_TYPE_NONE;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CMoverLeftStopRight::~CMoverLeftStopRight()
{

}

//================================================
//����������
//================================================
HRESULT CMoverLeftStopRight::Init(void)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrameCounter = 0;
	m_moveType = MOVE_TYPE_LEFT;

	return S_OK;
}

//================================================
//�I������
//================================================
void CMoverLeftStopRight::Uninit(void)
{
	
}

//================================================
//�X�V����
//================================================
void CMoverLeftStopRight::Update(void)
{
	//��ʂɂ�铮���̏���
	switch (m_moveType)
	{
	case MOVE_TYPE_LEFT:
		m_move = D3DXVECTOR3(MOVER_LEFT_SPEED, 0.0f, 0.0f);
		//���~���Ă���ԃJ�E���g�����Z
		m_nFrameCounter++;
		if (m_nFrameCounter >= MOVER_LEFT_FINISH_COUNT)
		{
			//�J�E���g�����Z�b�g
			m_nFrameCounter = 0;
			//���̓����ɕς���
			m_moveType = MOVE_TYPE_STOP;
		}
		break;
	case MOVE_TYPE_STOP:
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//��~���Ă���ԃJ�E���g�����Z
		m_nFrameCounter++;
		if (m_nFrameCounter >= MOVER_STOP_FINISH_COUNT)
		{
			//�J�E���g�����Z�b�g
			m_nFrameCounter = 0;
			//���̓����ɕς���
			m_moveType = MOVE_TYPE_RIGHT;
		}
		break;
	case MOVE_TYPE_RIGHT:
		m_move = D3DXVECTOR3(MOVER_RIGHT_SPEED, 0.0f, 0.0f);
		break;
	default:
		break;
	}
}

//================================================
//��������
//================================================
CMoverLeftStopRight* CMoverLeftStopRight::Create(void)
{
	//�C���X�^���X�̐���
	CMoverLeftStopRight *pMoverLeftStopRight = NULL;
	if (pMoverLeftStopRight == NULL)
	{
		pMoverLeftStopRight = new CMoverLeftStopRight;
		if (pMoverLeftStopRight != NULL)
		{
			pMoverLeftStopRight->Init();
		}
	}
	return pMoverLeftStopRight;
}