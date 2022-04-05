//=============================================================================
// �M���G�t�F�N�g�̓����̏���
// Author : KatoMizuki
//=============================================================================
#include "control_effect_flash.h"
#include "effect3D.h"

//================================================
//�}�N����`
//================================================
#define CONTROL_EFFECT_FLASH_ADD_SIZE_SMALL				(1.0f)		//�T�C�Y���Z�l(�ω��l��)
#define CONTROL_EFFECT_FLASH_ADD_SIZE_BIG				(30.0f)		//�T�C�Y���Z�l(�ω��l��)
#define CONTROL_EFFECT_FLASH_SUBTRACTION_SIZE			(2.0f)		//�T�C�Y���Z�l
#define CONTROL_EFFECT_FLASH_SIZE_SMALL					(40.0f)		//�������T�C�Y
#define CONTROL_EFFECT_FLASH_SIZE_BIG					(4000.0f)	//�傫�������T�C�Y

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CControlEffectFlash::CControlEffectFlash()
{
	m_nCounter = 0;
	m_state = CONTROL_EFFECT_FLASH_STATE::NONE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CControlEffectFlash::~CControlEffectFlash()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CControlEffectFlash::Init(CObject *pObject)
{
	m_nCounter = 0;
	m_state = CONTROL_EFFECT_FLASH_STATE::ADD_SIZE_SMALL;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CControlEffectFlash::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CControlEffectFlash::Update(CObject *pObject)
{
	//�J�E���^�[�����Z
	m_nCounter++;

	//�I�u�W�F�N�g�̃|�C���^���G�t�F�N�g�̃|�C���^�ɃL���X�g
	CEffect3D *pEffect3D = nullptr;
	pEffect3D = (CEffect3D*)pObject;

	//�ʒu�ƃT�C�Y�擾
	D3DXVECTOR3 pos = pEffect3D->GetPos();
	D3DXVECTOR3 size = pEffect3D->GetSize();

	switch (m_state)
	{
	case CONTROL_EFFECT_FLASH_STATE::ADD_SIZE_SMALL:
		//�傫������
		size.x += CONTROL_EFFECT_FLASH_ADD_SIZE_SMALL;
		size.y += CONTROL_EFFECT_FLASH_ADD_SIZE_SMALL;
		//����̑傫���ȏ�ɂȂ�����
		if (size.x >= CONTROL_EFFECT_FLASH_SIZE_SMALL)
		{
			//����̑傫���ɂ���
			size.x = CONTROL_EFFECT_FLASH_SIZE_SMALL;
		}
		if (size.y >= CONTROL_EFFECT_FLASH_SIZE_SMALL)
		{
			//����̑傫���ɂ���
			size.y = CONTROL_EFFECT_FLASH_SIZE_SMALL;
		}

		//����̒l�ȏ�ɂȂ�����
		if (m_nCounter >= 240)
		{
			//��Ԃ�ς���
			m_state = CONTROL_EFFECT_FLASH_STATE::SUBTRACTION_SIZE;
			//0�ɂ���
			m_nCounter = 0;
		}

		break;
	case CONTROL_EFFECT_FLASH_STATE::SUBTRACTION_SIZE:
		//����������
		size.x -= CONTROL_EFFECT_FLASH_SUBTRACTION_SIZE;
		size.y -= CONTROL_EFFECT_FLASH_SUBTRACTION_SIZE;

		//����̒l�ȏ�ɂȂ�����
		if (m_nCounter >= 30)
		{
			//��Ԃ�ς���
			m_state = CONTROL_EFFECT_FLASH_STATE::ADD_SIZE_BIG;
			//0�ɂ���
			m_nCounter = 0;
		}
		break;
	case CControlEffectFlash::CONTROL_EFFECT_FLASH_STATE::ADD_SIZE_BIG:
		//�傫������
		size.x += CONTROL_EFFECT_FLASH_ADD_SIZE_BIG;
		size.y += CONTROL_EFFECT_FLASH_ADD_SIZE_BIG;
		//����̑傫���ȏ�ɂȂ�����
		if (size.x >= CONTROL_EFFECT_FLASH_SIZE_BIG)
		{
			//����̑傫���ɂ���
			size.x = CONTROL_EFFECT_FLASH_SIZE_BIG;
		}
		if (size.y >= CONTROL_EFFECT_FLASH_SIZE_BIG)
		{
			//����̑傫���ɂ���
			size.y = CONTROL_EFFECT_FLASH_SIZE_BIG;
		}

		//����̒l�ȏ�ɂȂ�����
		if (m_nCounter >= 120)
		{
			//�J���[���擾
			D3DXCOLOR col = pEffect3D->GetCol();
			//��������
			col.a -= 0.01f;
			//�����Ȃ��Ȃ�����
			if (col.a <= 0.0f)
			{
				//����
				pEffect3D->Uninit();
				return;
			}
			//�F��ݒ�
			pEffect3D->SetCol(col);
		}
		break;
	default:
		break;
	}

	//�ʒu�ƃT�C�Y�𔽉f
	pEffect3D->SetPos(pos, size);
}

//=============================================================================
// ��������
//=============================================================================
CControlEffectFlash *CControlEffectFlash::Create(CObject *pObject)
{
	//�C���X�^���X�̐���
	CControlEffectFlash *pControlEffectFlash = nullptr;
	if (pControlEffectFlash == nullptr)
	{
		pControlEffectFlash = new CControlEffectFlash;
		if (pControlEffectFlash != nullptr)
		{
			pControlEffectFlash->Init(pObject);
		}
	}
	return pControlEffectFlash;
}