//================================================
//UI����
//Author:KatoMizuki
//================================================
#include "Object2D.h"
#include "manager.h"
#include "ui.h"
#include "texture.h"
#include "control.h"
#include "control_ui_subtract_alpha.h"

//================================================
//�}�N����`
//================================================
#define UI_CROSS_SUBTRACT_ALPHA			(0.07f)			//�o�cUI�̃��l���Z�l
#define UI_MESSAGE_01_SUBTRACT_ALPHA	(0.01f)			//���b�Z�[�W01UI�̃��l���Z�l
#define UI_MESSAGE_01_DELAY				(90)			//���b�Z�[�W01UI�̕\������
#define UI_MESSAGE_02_SUBTRACT_ALPHA	(0.08f)			//���b�Z�[�W02UI�̃��l���Z�l
#define UI_MESSAGE_02_DELAY				(40)			//���b�Z�[�W02UI�̕\������
#define UI_PRESS_START_SUBTRACT_ALPHA	(0.015f)		//PRESS START UI�̃��l���Z�l
#define UI_PRESS_START_DELAY			(10)			//PRESS START UI�̕\������

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CUi::CUi(int nPriority) :CObject2D(nPriority)
{
	m_pControl = nullptr;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CUi::~CUi()
{

}

//================================================
//����������
//================================================
HRESULT CUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CObject2D::Init(pos, size);

	SetObjType(CObject::OBJTYPE::UI);

	return S_OK;
}

//================================================
//�I������
//================================================
void CUi::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================
//�X�V����
//================================================
void CUi::Update(void)
{
	if (m_pControl != nullptr)
	{
		//�eUI�̍X�V�������Ăяo��
		m_pControl->Update(this);
	}
}

//================================================
//�`�揈��
//================================================
void CUi::Draw(void)
{
	CObject2D::Draw();
}

//================================================
//��������
//================================================
CUi* CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriolity, TYPE type)
{
	//�C���X�^���X�̐���
	CUi *pUi = nullptr;
	if (pUi == nullptr)
	{
		pUi = new CUi(nPriolity);
		if (pUi != nullptr)
		{
			pUi->m_type = type;
			pUi->Init(pos, size);
			// �w�肵��UI�̎�ނŃe�N�X�`����ς���
			switch (type)
			{
			case TYPE::CROSS:
				pUi->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_CROSS");
				pUi->m_pControl = CControlUiSubtractAlpha::Create(pUi, UI_CROSS_SUBTRACT_ALPHA, 0);
				break;
			case TYPE::MESSAGE_01:
				pUi->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MESSAGE_01");
				pUi->m_pControl = CControlUiSubtractAlpha::Create(pUi, UI_MESSAGE_01_SUBTRACT_ALPHA, UI_MESSAGE_01_DELAY);
				break;
			case TYPE::MESSAGE_02:
				pUi->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MESSAGE_02");
				pUi->m_pControl = CControlUiSubtractAlpha::Create(pUi, UI_MESSAGE_02_SUBTRACT_ALPHA, UI_MESSAGE_02_DELAY);
				break;
			case TYPE::PRESS_START:
				pUi->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_PRESS_START");
				pUi->m_pControl = CControlUiSubtractAlpha::Create(pUi, UI_PRESS_START_SUBTRACT_ALPHA, UI_PRESS_START_DELAY);
			default:
				break;
			}
			pUi->BindTexture(pUi->m_pTexture);
		}
	}
	return pUi;
}
