//=============================================================================
// ���G�t�F�N�g�̓����̏���
// Author : KatoMizuki
//=============================================================================
#include "control_effect_fire.h"
#include "effect3D.h"

//================================================
//�}�N����`
//================================================
#define CONTROL_EFFECT_FIRE_MAX_TEX_ANIM	(8)			//�e�N�X�`���A�j���[�V�����̎��
#define CONTROL_EFFECT_FIRE_TEX_COUNTER		(rand() % 8 + 3)			//�A�j���[�V�����̃J�E���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CControlEffectFire::CControlEffectFire()
{
	m_nTexAnimCounter = 0;
	m_nTexAnimNum = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CControlEffectFire::~CControlEffectFire()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CControlEffectFire::Init(CObject *pObject)
{
	//�I�u�W�F�N�g�̃|�C���^���G�t�F�N�g�̃|�C���^�ɃL���X�g
	CEffect3D *pEffect3D = nullptr;
	pEffect3D = (CEffect3D*)pObject;

	m_nTexAnimCounter = 0;
	m_nTexAnimNum = rand() % (CONTROL_EFFECT_FIRE_MAX_TEX_ANIM - 1);

	//�e�N�X�`���̐ݒ�
	pEffect3D->SetTex(m_nTexAnimNum, CONTROL_EFFECT_FIRE_MAX_TEX_ANIM);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CControlEffectFire::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CControlEffectFire::Update(CObject *pObject)
{
	//�I�u�W�F�N�g�̃|�C���^���G�t�F�N�g�̃|�C���^�ɃL���X�g
	CEffect3D *pEffect3D = nullptr;
	pEffect3D = (CEffect3D*)pObject;

	//�J�E���^�[�����Z
	m_nTexAnimCounter++;
	//�K��l�ȏ�ɂȂ�����
	if (m_nTexAnimCounter >= CONTROL_EFFECT_FIRE_TEX_COUNTER)
	{
		//0�ɂ���
		m_nTexAnimCounter = 0;

		//�A�j���[�V�����̔ԍ������Z
		m_nTexAnimNum++;
		//�K��l�ȏ�ɂȂ�����
		if (m_nTexAnimNum >= CONTROL_EFFECT_FIRE_MAX_TEX_ANIM)
		{
			//0�ɂ���
			m_nTexAnimNum = 0;
		}

		//�e�N�X�`���̐ݒ�
		pEffect3D->SetTex(m_nTexAnimNum, CONTROL_EFFECT_FIRE_MAX_TEX_ANIM);
	}
}

//=============================================================================
// ��������
//=============================================================================
CControlEffectFire *CControlEffectFire::Create(CObject *pObject)
{
	//�C���X�^���X�̐���
	CControlEffectFire *pControlEffectFire = nullptr;
	if (pControlEffectFire == nullptr)
	{
		pControlEffectFire = new CControlEffectFire;
		if (pControlEffectFire != nullptr)
		{
			pControlEffectFire->Init(pObject);
		}
	}
	return pControlEffectFire;
}