//=============================================================================
// ���G�t�F�N�g�̓����̏���
// Author : KatoMizuki
//=============================================================================
#include "control_effect_thunder.h"
#include "effect3D.h"

//================================================
//�}�N����`
//================================================
#define CONTROL_EFFECT_THUNDER_ADD_SIZE				(5.0f)		//�T�C�Y���Z�l
#define CONTROL_EFFECT_THUNDER_SUBTRACTION_SIZE		(8.0f)		//�T�C�Y���Z�l
#define CONTROL_EFFECT_THUNDER_SIZE					(400.0f)	//�T�C�Y
#define CONTROL_EFFECT_THUNDER_DESTROY_COUNT		(280)		//������܂ł̎���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CControlEffectThunder::CControlEffectThunder()
{
	m_nDestroyCounter = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CControlEffectThunder::~CControlEffectThunder()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CControlEffectThunder::Init(CObject *pObject)
{
	m_nDestroyCounter = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CControlEffectThunder::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CControlEffectThunder::Update(CObject *pObject)
{
	//�J�E���^�[�����Z
	m_nDestroyCounter++;

	//�I�u�W�F�N�g�̃|�C���^���G�t�F�N�g�̃|�C���^�ɃL���X�g
	CEffect3D *pEffect3D = nullptr;
	pEffect3D = (CEffect3D*)pObject;

	//�ʒu�ƃT�C�Y�擾
	D3DXVECTOR3 pos = pEffect3D->GetPos();
	D3DXVECTOR3 size = pEffect3D->GetSize();

	//����̒l��菬�����Ƃ�
	if (m_nDestroyCounter < CONTROL_EFFECT_THUNDER_DESTROY_COUNT)
	{
		//��������
		size.x += CONTROL_EFFECT_THUNDER_ADD_SIZE;
		//����̒l��葾���Ȃ�����
		if (size.x >= CONTROL_EFFECT_THUNDER_SIZE)
		{
			//����̒l�ɂ���
			size.x = CONTROL_EFFECT_THUNDER_SIZE;
		}
	}
	else
	{//����̒l�ȏ�̎�
		//�ׂ�����
		size.x -= CONTROL_EFFECT_THUNDER_SUBTRACTION_SIZE;
		//�����Ȃ��Ȃ�����
		if (size.x <= 0.0f)
		{
			//����
			pEffect3D->Uninit();
			return;
		}
	}

	//�ʒu�ƃT�C�Y�𔽉f
	pEffect3D->SetPos(pos, size);
}

//=============================================================================
// ��������
//=============================================================================
CControlEffectThunder *CControlEffectThunder::Create(CObject *pObject)
{
	//�C���X�^���X�̐���
	CControlEffectThunder *pControlEffectThunder = nullptr;
	if (pControlEffectThunder == nullptr)
	{
		pControlEffectThunder = new CControlEffectThunder;
		if (pControlEffectThunder != nullptr)
		{
			pControlEffectThunder->Init(pObject);
		}
	}
	return pControlEffectThunder;
}