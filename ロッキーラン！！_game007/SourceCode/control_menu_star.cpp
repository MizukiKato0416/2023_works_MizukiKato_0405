//=============================================================================
// ���j���[���R���g���[������ [control_menu_star.cpp]
// Author : ��������
//=============================================================================
#include "control_menu_star.h"
#include "manager.h"
#include "menu.h"
#include "ui.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CControlMenuStar::CControlMenuStar()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CControlMenuStar::~CControlMenuStar()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CControlMenuStar::Init(void)
{
	m_fMaxMoveX = 10.0f;
	m_fMaxMoveY = 1.5f;
	m_nFrame = 0;
	m_col = STAR_COL;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CControlMenuStar::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CControlMenuStar::Update(CScene *pScene)
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


	if (pUi->GetUIType() == CUi::UI_TYPE_MENU_STAR)
	{
		m_nFrame++;


		m_move.x = -12.0f;
		m_move.y = 5.0f;

		// �ʒu��T�C�Y�̐ݒ�
		pUi->SetPos(pos, size);
	}
}

//=============================================================================
// ��������
//=============================================================================
CControlMenuStar *CControlMenuStar::Create()
{
	//�C���X�^���X�̐���
	CControlMenuStar *pControlMenuStar = NULL;

	if (pControlMenuStar == NULL)
	{
		pControlMenuStar = new CControlMenuStar;

		if (pControlMenuStar != NULL)
		{
			pControlMenuStar->Init();
		}
	}

	return pControlMenuStar;
}