//=============================================================================
// �^�C�g�����S�R���g���[������ [control_title_logo.cpp]
// Author : KUSAKARI KAKERU
//=============================================================================
#include "control_title_logo.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "title.h"
#include "ui.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CControlTitleLogo::CControlTitleLogo()
{
	
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CControlTitleLogo::~CControlTitleLogo()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CControlTitleLogo::Init(void)
{
	m_fMaxMove = 1.5f;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CControlTitleLogo::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CControlTitleLogo::Update(CScene *pScene)
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

	// ��ʏ�ɂ��鎞��
	if (pos.y <= SCREEN_HEIGHT / 3.0f)
	{
		m_move.y += 1.5f;
	}
	// �r���Ŏ~�߂�(�ړ��ʂ�0�ɂ���)
	else if (pos.y >= SCREEN_HEIGHT / 2.6f)
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

	// �ʒu��T�C�Y�̐ݒ�
	pUi->SetPos(pos, size);
}

//=============================================================================
// ��������
//=============================================================================
CControlTitleLogo *CControlTitleLogo::Create()
{
	//�C���X�^���X�̐���
	CControlTitleLogo *pControlTitleLogo = NULL;

	if (pControlTitleLogo == NULL)
	{
		pControlTitleLogo = new CControlTitleLogo;

		if (pControlTitleLogo != NULL)
		{
			pControlTitleLogo->Init();
		}
	}

	return pControlTitleLogo;
}