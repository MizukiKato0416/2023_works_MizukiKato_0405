//================================================
//���~���Ē�~���㏸���铮���̏���
//Authore:��������
//================================================
#include "mover_fall_stop_rise.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CMoverFallStopRise::CMoverFallStopRise()
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
CMoverFallStopRise::~CMoverFallStopRise()
{

}

//================================================
//����������
//================================================
HRESULT CMoverFallStopRise::Init(void)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrameCounter = 0;
	m_moveType = MOVE_TYPE_FALL;

	return S_OK;
}

//================================================
//�I������
//================================================
void CMoverFallStopRise::Uninit(void)
{
	
}

//================================================
//�X�V����
//================================================
void CMoverFallStopRise::Update(void)
{
	//��ʂɂ�铮���̏���
	switch (m_moveType)
	{
	case MOVE_TYPE_FALL:
		m_move = D3DXVECTOR3(0.0f, MOVER_FALL_SPEED, 0.0f);
		//���~���Ă���ԃJ�E���g�����Z
		m_nFrameCounter++;
		if (m_nFrameCounter >= MOVER_FALL_FINISH_COUNT)
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
			m_moveType = MOVE_TYPE_RISE;
		}
		break;
	case MOVE_TYPE_RISE:
		m_move = D3DXVECTOR3(0.0f, MOVER_RISE_SPEED, 0.0f);
		break;
	default:
		break;
	}
}

//================================================
//��������
//================================================
CMoverFallStopRise* CMoverFallStopRise::Create(void)
{
	//�C���X�^���X�̐���
	CMoverFallStopRise *pMoverFallStopRise = NULL;
	if (pMoverFallStopRise == NULL)
	{
		pMoverFallStopRise = new CMoverFallStopRise;
		if (pMoverFallStopRise != NULL)
		{
			pMoverFallStopRise->Init();
		}
	}
	return pMoverFallStopRise;
}