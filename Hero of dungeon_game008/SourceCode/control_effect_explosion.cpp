//=============================================================================
// �����G�t�F�N�g�̓����̏���
// Author : KatoMizuki
//=============================================================================
#include "control_effect_explosion.h"
#include "effect3D.h"

//================================================
//�}�N����`
//================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CControlEffectExplosion::CControlEffectExplosion()
{
	
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CControlEffectExplosion::~CControlEffectExplosion()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CControlEffectExplosion::Init(CObject *pObject)
{
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CControlEffectExplosion::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CControlEffectExplosion::Update(CObject *pObject)
{
	//�I�u�W�F�N�g�̃|�C���^���G�t�F�N�g�̃|�C���^�ɃL���X�g
	CEffect3D *pEffect3D = nullptr;
	pEffect3D = (CEffect3D*)pObject;
	
}

//=============================================================================
// ��������
//=============================================================================
CControlEffectExplosion *CControlEffectExplosion::Create(CObject *pObject)
{
	//�C���X�^���X�̐���
	CControlEffectExplosion *pControlEffectExplosion = nullptr;
	if (pControlEffectExplosion == nullptr)
	{
		pControlEffectExplosion = new CControlEffectExplosion;
		if (pControlEffectExplosion != nullptr)
		{
			pControlEffectExplosion->Init(pObject);
		}
	}
	return pControlEffectExplosion;
}