//================================================
//�E�ɍs����~�����ɍs�������̏���
//Authore:��������
//================================================
#include "mover_right_stop_left.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CMoverRightStopLeft::CMoverRightStopLeft()
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
CMoverRightStopLeft::~CMoverRightStopLeft()
{

}

//================================================
//����������
//================================================
HRESULT CMoverRightStopLeft::Init(void)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrameCounter = 0;
	m_moveType = MOVE_TYPE_RIGHT;

	return S_OK;
}

//================================================
//�I������
//================================================
void CMoverRightStopLeft::Uninit(void)
{
	
}

//================================================
//�X�V����
//================================================
void CMoverRightStopLeft::Update(void)
{
	//��ʂɂ�铮���̏���
	switch (m_moveType)
	{
	case MOVE_TYPE_RIGHT:
		m_move = D3DXVECTOR3(MOVER_RIGHT_SPEED, 0.0f, 0.0f);
		//���~���Ă���ԃJ�E���g�����Z
		m_nFrameCounter++;
		if (m_nFrameCounter >= MOVER_RIGHT_FINISH_COUNT)
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
			m_moveType = MOVE_TYPE_LEFT;
		}
		break;
	case MOVE_TYPE_LEFT:
		m_move = D3DXVECTOR3(MOVER_LEFT_SPEED, 0.0f, 0.0f);
		break;
	default:
		break;
	}
}

//================================================
//��������
//================================================
CMoverRightStopLeft* CMoverRightStopLeft::Create(void)
{
	//�C���X�^���X�̐���
	CMoverRightStopLeft *pMoverRightStopLeft = NULL;
	if (pMoverRightStopLeft == NULL)
	{
		pMoverRightStopLeft = new CMoverRightStopLeft;
		if (pMoverRightStopLeft != NULL)
		{
			pMoverRightStopLeft->Init();
		}
	}
	return pMoverRightStopLeft;
}