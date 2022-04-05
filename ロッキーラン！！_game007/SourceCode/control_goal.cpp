//=============================================================================
// �S�[���̃|���S�����o������ [control_goal.cpp]
// Author : ��ˌ�
//=============================================================================
#include "control_goal.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "title.h"
#include "ui.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CControlGoal::CControlGoal()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fMaxMove = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CControlGoal::~CControlGoal()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CControlGoal::Init(void)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fMaxMove = 40.5f;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CControlGoal::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CControlGoal::Update(CScene *pScene)
{
	//�����̃|�C���^��Ui�N���X�̃|�C���^�ɃL���X�g
	CUi *pUi = NULL;
	pUi = (CUi*)pScene;

	//UI�̎擾���I�u�W�F�N�g�̈ʒu���擾
	D3DXVECTOR3 pos;
	pos = pUi->GetPos();

	//UI�̎擾���I�u�W�F�N�g�̃T�C�Y���擾
	D3DXVECTOR3 size;
	size = pUi->GetSize();

	// ��ʉ��ɂ��鎞��
	if (pos.x < SCREEN_WIDTH / 2.0f)
	{
		m_move.x += 40.5f;
		pos += m_move;

		// �ړ��ʂ��ő�ړ��ʂ𒴂��Ȃ��悤�ɂ���
		if (m_move.x >= m_fMaxMove)
		{
			m_move.x = m_fMaxMove;
		}
		else if (m_move.x <= -m_fMaxMove)
		{
			m_move.x = -m_fMaxMove;
		}
	}

	// �r���Ŏ~�߂�(�ړ��ʂ�0�ɂ���)
	if (pos.x >= SCREEN_WIDTH / 2.0f)
	{
		m_move.x = 0.0f;
		pos.x = SCREEN_WIDTH / 2.0f;
		// �ʒu��T�C�Y�̐ݒ�
		pUi->SetPos(pos, size);
	}
}

//=============================================================================
// ��������
//=============================================================================
CControlGoal *CControlGoal::Create()
{
	//�C���X�^���X�̐���
	CControlGoal *pControlGoal = NULL;

	if (pControlGoal == NULL)
	{
		pControlGoal = new CControlGoal;

		if (pControlGoal != NULL)
		{
			pControlGoal->Init();
		}
	}

	return pControlGoal;
}