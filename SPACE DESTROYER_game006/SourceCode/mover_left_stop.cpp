//================================================
//���ɍs����~���铮���̏���
//Authore:��������
//================================================
#include "mover_left_stop.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CMoverLeftStop::CMoverLeftStop()
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
CMoverLeftStop::~CMoverLeftStop()
{

}

//================================================
//����������
//================================================
HRESULT CMoverLeftStop::Init(void)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrameCounter = 0;
	m_moveType = MOVE_TYPE_LEFT;

	return S_OK;
}

//================================================
//�I������
//================================================
void CMoverLeftStop::Uninit(void)
{
	
}

//================================================
//�X�V����
//================================================
void CMoverLeftStop::Update(void)
{
	//��ʂɂ�铮���̏���
	switch (m_moveType)
	{
	case MOVE_TYPE_LEFT:
		m_move = D3DXVECTOR3(MOVER_LEFT_STOP_LEFT_SPEED, 0.0f, 0.0f);
		//���~���Ă���ԃJ�E���g�����Z
		m_nFrameCounter++;
		if (m_nFrameCounter >= MOVER_LEFT_STOP_LEFT_FINISH_COUNT)
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
CMoverLeftStop* CMoverLeftStop::Create(void)
{
	//�C���X�^���X�̐���
	CMoverLeftStop *pMoverLeftStop = NULL;
	if (pMoverLeftStop == NULL)
	{
		pMoverLeftStop = new CMoverLeftStop;
		if (pMoverLeftStop != NULL)
		{
			pMoverLeftStop->Init();
		}
	}
	return pMoverLeftStop;
}