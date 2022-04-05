//=============================================================================
// �^�C�g���G���^�[�����R���g���[������ [control_title_enter.cpp]
// Author : KUSAKARI KAKERU
//=============================================================================
#include "control_title_enter.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "title.h"
#include "ui.h"
#include "scene.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CControlTitleEnter::CControlTitleEnter()
{
	m_nCount = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_bAlphaUp = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CControlTitleEnter::~CControlTitleEnter()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CControlTitleEnter::Init(void)
{
	m_nCount = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_bAlphaUp = true;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CControlTitleEnter::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CControlTitleEnter::Update(CScene *pScene)
{
	//�����̃|�C���^��Ui�N���X�̃|�C���^�ɃL���X�g
	CUi *pUi = NULL;
	pUi = (CUi*)pScene;

	D3DXVECTOR3 pos;
	pos = pUi->GetPos();

	m_nCount++;

	// �A���t�@�l��������(�����ɂ���)
	if (m_bAlphaUp == false)
	{
		if (m_nCount % 2 == 0)
		{
			m_col.a += -0.05f;
		}

		if (m_col.a < 0)
		{
			m_nCount = 0;
			m_col.a = 0;
			m_bAlphaUp = true;
		}
	}
	// �A���t�@�l���グ��(�s�����ɂ���)
	else if (m_bAlphaUp == true)
	{
		if (m_nCount % 2 == 0)
		{
			m_col.a += 0.05f;
		}

		if (m_col.a > 1.0f && m_nCount >= 70)
		{
			m_nCount = 0;
			m_col.a = 1.0f;
			m_bAlphaUp = false;
		}
	}

	// m_fAlpha�̒l�𓧖��x�ɓ����
	pUi->SetCol(m_col);
}

//=============================================================================
// ��������
//=============================================================================
CControlTitleEnter *CControlTitleEnter::Create()
{
	//�C���X�^���X�̐���
	CControlTitleEnter *pControlTitleEnter = NULL;

	if (pControlTitleEnter == NULL)
	{
		pControlTitleEnter = new CControlTitleEnter;

		if (pControlTitleEnter != NULL)
		{
			pControlTitleEnter->Init();
		}
	}

	return pControlTitleEnter;
}