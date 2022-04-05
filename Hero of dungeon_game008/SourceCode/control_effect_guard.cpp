//=============================================================================
// �K�[�h�G�t�F�N�g�̓����̏���
// Author : KatoMizuki
//=============================================================================
#include "control_effect_guard.h"
#include "effect3D.h"

//================================================
//�}�N����`
//================================================
#define CONTROL_EFFECT_GUARD_SUBTRACT_ALPHA		(0.05f)					//���l���Z�l
#define CONTROL_EFFECT_GUARD_ADD_SIZE			(1.0f)					//�T�C�Y���Z��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CControlEffectGuard::CControlEffectGuard()
{
	
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CControlEffectGuard::~CControlEffectGuard()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CControlEffectGuard::Init(CObject *pObject)
{
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CControlEffectGuard::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CControlEffectGuard::Update(CObject *pObject)
{
	//�I�u�W�F�N�g�̃|�C���^���G�t�F�N�g�̃|�C���^�ɃL���X�g
	CEffect3D *pEffect3D = nullptr;
	pEffect3D = (CEffect3D*)pObject;

	//�ʒu�ƃT�C�Y�ƃJ���[�̎擾
	D3DXVECTOR3 pos = pEffect3D->GetPos();
	D3DXVECTOR3 size = pEffect3D->GetSize();
	D3DXCOLOR col = pEffect3D->GetCol();

	//�傫������
	size.x += CONTROL_EFFECT_GUARD_ADD_SIZE;
	size.y += CONTROL_EFFECT_GUARD_ADD_SIZE;
	//��������
	col.a -= CONTROL_EFFECT_GUARD_SUBTRACT_ALPHA;
	//�����Ȃ��Ȃ�����
	if (col.a <= 0.0f)
	{
		//����
		pEffect3D->Uninit();
		return;
	}
	//�J���[�̐ݒ�
	pEffect3D->SetCol(col);
	//�T�C�Y�̐ݒ�
	pEffect3D->SetPos(pos,size);
}

//=============================================================================
// ��������
//=============================================================================
CControlEffectGuard *CControlEffectGuard::Create(CObject *pObject)
{
	//�C���X�^���X�̐���
	CControlEffectGuard *pControlEffectGuard = nullptr;
	if (pControlEffectGuard == nullptr)
	{
		pControlEffectGuard = new CControlEffectGuard;
		if (pControlEffectGuard != nullptr)
		{
			pControlEffectGuard->Init(pObject);
		}
	}
	return pControlEffectGuard;
}