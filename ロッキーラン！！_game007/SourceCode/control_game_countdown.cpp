//=============================================================================
// �Q�[���J�E���g�_�E������ [control_game_countdown.cpp]
// Author : ��������
//=============================================================================
#include "control_game_countdown.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "game01.h"
#include "ui.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CControlGameCountdown::CControlGameCountdown()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CControlGameCountdown::~CControlGameCountdown()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CControlGameCountdown::Init(void)
{
	m_fMaxMove = 2.0f;
	m_nCount = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CControlGameCountdown::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CControlGameCountdown::Update(CScene *pScene)
{
	//�����̃|�C���^��Ui�N���X�̃|�C���^�ɃL���X�g
	CUi *pUi = NULL;
	pUi = (CUi*)pScene;

	m_nCount++;

	//UI�̎擾���I�u�W�F�N�g�̈ʒu���擾
	D3DXVECTOR3 pos;
	pos = pUi->GetPos();

	//UI�̎擾���I�u�W�F�N�g�̃T�C�Y���擾
	D3DXVECTOR3 size;
	size = pUi->GetSize();

	// ��ʏ�ɂ��鎞��
	if (pos.y <= SCREEN_HEIGHT / 3.0f)
	{
		m_move.y += 1.5f;
	}
	// �r���Ŏ~�߂�(�ړ��ʂ�0�ɂ���)
	else if (pos.y >= SCREEN_HEIGHT / 2)
	{
		m_move.y = 0.0f;
	}

	// �ړ��ʂ��ő�ړ��ʂ𒴂��Ȃ��悤�ɂ���
	if (m_move.y >= m_fMaxMove)
	{
		m_move.y = m_fMaxMove;
	}
	else if (m_move.y <= -m_fMaxMove)
	{
		m_move.y = -m_fMaxMove;
	}

	// �A���t�@�l���グ��(�s�����ɂ���)
	if (m_nCount % 2 == 0)
	{
		m_col.a += 0.05f;
	}

	if (m_col.a > 1.0f && m_nCount >= 70)
	{
		m_nCount = 0;
		m_col = 1.0f;
	}

	// m_fAlpha�̒l�𓧖��x�ɓ����
	pUi->SetCol(m_col);

	// �ʒu��T�C�Y�̐ݒ�
	pUi->SetPos(pos, size);
}

//=============================================================================
// ��������
//=============================================================================
CControlGameCountdown *CControlGameCountdown::Create()
{
	//�C���X�^���X�̐���
	CControlGameCountdown *pControlGameCountdown = NULL;

	if (pControlGameCountdown == NULL)
	{
		pControlGameCountdown = new CControlGameCountdown;

		if (pControlGameCountdown != NULL)
		{
			pControlGameCountdown->Init();
		}
	}

	return pControlGameCountdown;
}