//=============================================================================
// �`�F�b�N�|�C���g�̃G�t�F�N�g�̓����̏���
// Author : KatoMizuki
//=============================================================================
#include "control_effect_check.h"
#include "effect3D.h"

//================================================
//�}�N����`
//================================================
#define CONTROL_EFFECT_CHECK_MOVE			(float (rand() % 3 + 1) / 10)	//�ړ���
#define CONTROL_EFFECT_CHECK_SUBTRACTION	(0.005f)						//���l���Z�l

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CControlEffectCheck::CControlEffectCheck()
{
	
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CControlEffectCheck::~CControlEffectCheck()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CControlEffectCheck::Init(CObject *pObject)
{
	m_move = D3DXVECTOR3(0.0f, CONTROL_EFFECT_CHECK_MOVE, 0.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CControlEffectCheck::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CControlEffectCheck::Update(CObject *pObject)
{
	//�I�u�W�F�N�g�̃|�C���^���G�t�F�N�g�̃|�C���^�ɃL���X�g
	CEffect3D *pEffect3D = nullptr;
	pEffect3D = (CEffect3D*)pObject;

	//�J���[�̎擾
	D3DXCOLOR col = pEffect3D->GetCol();
	//��������
	col.a -= CONTROL_EFFECT_CHECK_SUBTRACTION;
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
CControlEffectCheck *CControlEffectCheck::Create(CObject *pObject)
{
	//�C���X�^���X�̐���
	CControlEffectCheck *pControlEffectCheck = nullptr;
	if (pControlEffectCheck == nullptr)
	{
		pControlEffectCheck = new CControlEffectCheck;
		if (pControlEffectCheck != nullptr)
		{
			pControlEffectCheck->Init(pObject);
		}
	}
	return pControlEffectCheck;
}