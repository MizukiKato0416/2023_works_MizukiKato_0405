//=============================================================================
// �^�C�g���G���^�[�����R���g���[������ [control_title_enter.cpp]
// Author : ��������
//=============================================================================
#include "control_game_start.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "title.h"
#include "ui.h"
#include "scene.h"
#include "game01.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CControlGameStart::CControlGameStart()
{
	m_nCount = 0;
	MIN_Size = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CControlGameStart::~CControlGameStart()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CControlGameStart::Init(void)
{
	m_nCount = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CControlGameStart::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CControlGameStart::Update(CScene *pScene)
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

	// �A���t�@�l���グ��(�s�����ɂ���)
	m_col.a += 0.025f;
	size.x -= SMALL_SPEED;
	size.y -= SMALL_SPEED;
	if (size.y <= MIN_SIZE)
	{
		size.y = MIN_SIZE;
	}
	if (size.x <= MIN_SIZE)
	{
		size.x = MIN_SIZE;
	}

	if (m_col.a > 1.0f && m_nCount >= 70)
	{
		m_nCount = 0;
		m_col.a = 1.0f;
	}

	// m_fAlpha�̒l�𓧖��x�ɓ����
	pUi->SetCol(m_col);
	// �ʒu��T�C�Y�̐ݒ�
	pUi->SetPos(pos, size);
}

//=============================================================================
// ��������
//=============================================================================
CControlGameStart *CControlGameStart::Create()
{
	//�C���X�^���X�̐���
	CControlGameStart *pControlGameStart = NULL;

	if (pControlGameStart == NULL)
	{
		pControlGameStart = new CControlGameStart;

		if (pControlGameStart != NULL)
		{
			pControlGameStart->Init();
		}
	}

	return pControlGameStart;
}