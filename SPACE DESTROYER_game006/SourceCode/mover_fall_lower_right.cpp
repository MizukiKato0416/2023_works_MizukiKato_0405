//================================================
//���~���ĉE���ɍs�������̏���
//Authore:��������
//================================================
#include "mover_fall_lower_right.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CMoverFallLowerRight::CMoverFallLowerRight()
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
CMoverFallLowerRight::~CMoverFallLowerRight()
{

}

//================================================
//����������
//================================================
HRESULT CMoverFallLowerRight::Init(void)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrameCounter = 0;
	m_moveType = MOVE_TYPE_FALL;

	return S_OK;
}

//================================================
//�I������
//================================================
void CMoverFallLowerRight::Uninit(void)
{
	
}

//================================================
//�X�V����
//================================================
void CMoverFallLowerRight::Update(void)
{
	//��ʂɂ�铮���̏���
	switch (m_moveType)
	{
	case MOVE_TYPE_FALL:
		m_move = D3DXVECTOR3(0.0f, MOVER_FALL_LOWER_RIGHT_SPEED, 0.0f);
		//���~���Ă���ԃJ�E���g�����Z
		m_nFrameCounter++;
		if (m_nFrameCounter >= MOVER_FALL_FINISH_COUNT)
		{
			//�J�E���g�����Z�b�g
			m_nFrameCounter = 0;
			//���̓����ɕς���
			m_moveType = MOVE_TYPE_LOWER_RIGHT;
		}
		break;
	case MOVE_TYPE_LOWER_RIGHT:
		m_move = D3DXVECTOR3(cosf(1.0f / 4.0f * D3DX_PI) * MOVER_LOWER_RIGHT_SPEED, sinf(1.0f / 4.0f * D3DX_PI) * MOVER_LOWER_RIGHT_SPEED, 0.0f);
		break;
	default:
		break;
	}
}

//================================================
//��������
//================================================
CMoverFallLowerRight* CMoverFallLowerRight::Create(void)
{
	//�C���X�^���X�̐���
	CMoverFallLowerRight *pMoverFallLowerRight = NULL;
	if (pMoverFallLowerRight == NULL)
	{
		pMoverFallLowerRight = new CMoverFallLowerRight;
		if (pMoverFallLowerRight != NULL)
		{
			pMoverFallLowerRight->Init();
		}
	}
	return pMoverFallLowerRight;
}