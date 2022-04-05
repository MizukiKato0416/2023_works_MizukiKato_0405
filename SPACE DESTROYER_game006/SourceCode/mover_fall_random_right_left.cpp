//================================================
//�~���Ȃ��烉���_���ō��E�ɍs�������̏���
//Authore:��������
//================================================
#include "mover_fall_random_right_left.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CMoverFallRandomRightLeft::CMoverFallRandomRightLeft()
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
CMoverFallRandomRightLeft::~CMoverFallRandomRightLeft()
{

}

//================================================
//����������
//================================================
HRESULT CMoverFallRandomRightLeft::Init(void)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrameCounter = 0;
	m_moveType = MOVE_TYPE_LOWER_LEFT;

	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����

	return S_OK;
}

//================================================
//�I������
//================================================
void CMoverFallRandomRightLeft::Uninit(void)
{
	
}

//================================================
//�X�V����
//================================================
void CMoverFallRandomRightLeft::Update(void)
{
	//���~���Ă���ԃJ�E���g�����Z
	m_nFrameCounter++;

	//��ʂɂ�铮���̏���
	switch (m_moveType)
	{
	case MOVE_TYPE_LOWER_LEFT:
		m_move = D3DXVECTOR3(cosf(3.0f / 4.0f * D3DX_PI) * MOVER_FALL_RANDOM_RIGHT_LEFT_SPEED,
							sinf(3.0f / 4.0f * D3DX_PI) * MOVER_FALL_RANDOM_RIGHT_LEFT_SPEED, 0.0f);
		if (m_nFrameCounter >= MOVER_RIGHT_LEFT_FINISH_COUNT)
		{
			//�J�E���g�����Z�b�g
			m_nFrameCounter = 0;
			//���̓����ɕς���
			m_moveType = MOVE_TYPE_LOWER_RIGHT;
		}
		break;
	case MOVE_TYPE_LOWER_RIGHT:
		m_move = D3DXVECTOR3(cosf(1.0f / 4.0f * D3DX_PI) * MOVER_FALL_RANDOM_RIGHT_LEFT_SPEED,
							sinf(1.0f / 4.0f * D3DX_PI) * MOVER_FALL_RANDOM_RIGHT_LEFT_SPEED, 0.0f);
		if (m_nFrameCounter >= MOVER_RIGHT_LEFT_FINISH_COUNT)
		{
			//�J�E���g�����Z�b�g
			m_nFrameCounter = 0;
			//���̓����ɕς���
			m_moveType = MOVE_TYPE_LOWER_LEFT;
		}
		break;
	default:
		break;
	}
}

//================================================
//��������
//================================================
CMoverFallRandomRightLeft* CMoverFallRandomRightLeft::Create(void)
{
	//�C���X�^���X�̐���
	CMoverFallRandomRightLeft *pMoverFallRandomRightLeft = NULL;
	if (pMoverFallRandomRightLeft == NULL)
	{
		pMoverFallRandomRightLeft = new CMoverFallRandomRightLeft;
		if (pMoverFallRandomRightLeft != NULL)
		{
			pMoverFallRandomRightLeft->Init();
		}
	}
	return pMoverFallRandomRightLeft;
}