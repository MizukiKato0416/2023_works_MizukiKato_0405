//=============================================================================
// �q�b�g�G�t�F�N�g�̓����̏���
// Author : KatoMizuki
//=============================================================================
#include "control_effect_hit.h"
#include "effect3D.h"

//================================================
//�}�N����`
//================================================
#define CONTROL_EFFECT_HIT_SUBTRACTION	(0.05f)						//���l���Z�l

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CControlEffectHit::CControlEffectHit()
{
	
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CControlEffectHit::~CControlEffectHit()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CControlEffectHit::Init(CObject *pObject)
{
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CControlEffectHit::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CControlEffectHit::Update(CObject *pObject)
{
	//�I�u�W�F�N�g�̃|�C���^���G�t�F�N�g�̃|�C���^�ɃL���X�g
	CEffect3D *pEffect3D = nullptr;
	pEffect3D = (CEffect3D*)pObject;

	//�J���[�̎擾
	D3DXCOLOR col = pEffect3D->GetCol();
	//��������
	col.a -= CONTROL_EFFECT_HIT_SUBTRACTION;
	//�����Ȃ��Ȃ�����
	if (col.a <= 0.0f)
	{
		//����
		pEffect3D->Uninit();
		return;
	}
	pEffect3D->SetCol(col);
}

//=============================================================================
// ��������
//=============================================================================
CControlEffectHit *CControlEffectHit::Create(CObject *pObject)
{
	//�C���X�^���X�̐���
	CControlEffectHit *pControlEffectHit = nullptr;
	if (pControlEffectHit == nullptr)
	{
		pControlEffectHit = new CControlEffectHit;
		if (pControlEffectHit != nullptr)
		{
			pControlEffectHit->Init(pObject);
		}
	}
	return pControlEffectHit;
}