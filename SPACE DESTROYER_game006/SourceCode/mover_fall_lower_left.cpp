//================================================
//���~���č����ɍs�������̏���
//Authore:��������
//================================================
#include "mover_fall_lower_left.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CMoverFallLowerLeft::CMoverFallLowerLeft()
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
CMoverFallLowerLeft::~CMoverFallLowerLeft()
{

}

//================================================
//����������
//================================================
HRESULT CMoverFallLowerLeft::Init(void)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrameCounter = 0;
	m_moveType = MOVE_TYPE_FALL;

	return S_OK;
}

//================================================
//�I������
//================================================
void CMoverFallLowerLeft::Uninit(void)
{
	
}

//================================================
//�X�V����
//================================================
void CMoverFallLowerLeft::Update(void)
{
	//��ʂɂ�铮���̏���
	switch (m_moveType)
	{
	case MOVE_TYPE_FALL:
		m_move = D3DXVECTOR3(0.0f, MOVER_LOWER_LEFT_FALL_SPEED, 0.0f);
		//���~���Ă���ԃJ�E���g�����Z
		m_nFrameCounter++;
		if (m_nFrameCounter >= MOVER_FALL_FINISH_COUNT)
		{
			//�J�E���g�����Z�b�g
			m_nFrameCounter = 0;
			//���̓����ɕς���
			m_moveType = MOVE_TYPE_LOWER_LEFT;
		}
		break;
	case MOVE_TYPE_LOWER_LEFT:
		m_move = D3DXVECTOR3(cosf(3.0f / 4.0f * D3DX_PI) * MOVER_LOWER_LEFT_SPEED, sinf(3.0f / 4.0f * D3DX_PI) * MOVER_LOWER_LEFT_SPEED, 0.0f);
		break;
	default:
		break;
	}
}

//================================================
//��������
//================================================
CMoverFallLowerLeft* CMoverFallLowerLeft::Create(void)
{
	//�C���X�^���X�̐���
	CMoverFallLowerLeft *pMoverFallLowerLeft = NULL;
	if (pMoverFallLowerLeft == NULL)
	{
		pMoverFallLowerLeft = new CMoverFallLowerLeft;
		if (pMoverFallLowerLeft != NULL)
		{
			pMoverFallLowerLeft->Init();
		}
	}
	return pMoverFallLowerLeft;
}