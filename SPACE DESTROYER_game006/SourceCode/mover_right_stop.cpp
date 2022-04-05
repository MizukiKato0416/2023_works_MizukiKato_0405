//================================================
//�E�ɍs����~���铮���̏���
//Authore:��������
//================================================
#include "mover_right_stop.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CMoverRightStop::CMoverRightStop()
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
CMoverRightStop::~CMoverRightStop()
{

}

//================================================
//����������
//================================================
HRESULT CMoverRightStop::Init(void)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrameCounter = 0;
	m_moveType = MOVE_TYPE_RIGHT;

	return S_OK;
}

//================================================
//�I������
//================================================
void CMoverRightStop::Uninit(void)
{
	
}

//================================================
//�X�V����
//================================================
void CMoverRightStop::Update(void)
{
	//��ʂɂ�铮���̏���
	switch (m_moveType)
	{
	case MOVE_TYPE_RIGHT:
		m_move = D3DXVECTOR3(MOVER_RIGHT_STOP_RIGHT_SPEED, 0.0f, 0.0f);
		//���~���Ă���ԃJ�E���g�����Z
		m_nFrameCounter++;
		if (m_nFrameCounter >= MOVER_RIGHT_STOP_RIGHT_FINISH_COUNT)
		{
			//�J�E���g�����Z�b�g
			m_nFrameCounter = 0;
			//���̓����ɕς���
			m_moveType = MOVE_TYPE_STOP;
		}
		break;
	case MOVE_TYPE_STOP:
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		break;
	default:
		break;
	}
}

//================================================
//��������
//================================================
CMoverRightStop* CMoverRightStop::Create(void)
{
	//�C���X�^���X�̐���
	CMoverRightStop *pMoverRightStop = NULL;
	if (pMoverRightStop == NULL)
	{
		pMoverRightStop = new CMoverRightStop;
		if (pMoverRightStop != NULL)
		{
			pMoverRightStop->Init();
		}
	}
	return pMoverRightStop;
}