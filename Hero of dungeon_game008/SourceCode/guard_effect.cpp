//================================================
//���@�w�̏���
//Author:KatoMizuki
//================================================
#include "guard_effect.h"
#include "manager.h"
#include "texture.h"
#include "object3D.h"

//================================================
//�}�N����`
//================================================
#define GUARD_EFFECT_SUBTRACT_ALPHA		(0.05f)					//���l���Z�l
#define GUARD_EFFECT_ADD_SIZE			(4.5f)					//�T�C�Y���Z��

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CGuardEffect::CGuardEffect(int nPriority) :CObject(nPriority)
{
	m_pObject3D = nullptr;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CGuardEffect::~CGuardEffect()
{

}

//================================================
//����������
//================================================
HRESULT CGuardEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�K�[�h�G�t�F�N�g�̐���
	m_pObject3D = CObject3D::Create(pos, size, m_rot);
	m_pObject3D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_RING"));
	m_pObject3D->SetCulling(false);
	m_pObject3D->SetAlphaTest(true);
	m_pObject3D->SetAlphaBlend(true);
	m_pObject3D->SetLighting(false);

	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::GUARD);

	return S_OK;
}

//================================================
//�I������
//================================================
void CGuardEffect::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CGuardEffect::Update(void)
{
	//�ʒu�ƃT�C�Y�ƃJ���[�̎擾
	D3DXVECTOR3 pos = m_pObject3D->GetPos();
	D3DXVECTOR3 size = m_pObject3D->GetSize();
	D3DXCOLOR col = m_pObject3D->GetCol();

	//�傫������
	size.x += GUARD_EFFECT_ADD_SIZE;
	size.y += GUARD_EFFECT_ADD_SIZE;
	//��������
	col.a -= GUARD_EFFECT_SUBTRACT_ALPHA;
	//�����Ȃ��Ȃ�����
	if (col.a <= 0.0f)
	{
		//����
		m_pObject3D->Uninit();
		m_pObject3D = nullptr;
		Uninit();
		return;
	}
	//�J���[�̐ݒ�
	m_pObject3D->SetCol(col);
	//�T�C�Y�̐ݒ�
	m_pObject3D->SetPos(pos, size);
}

//================================================
//�`�揈��
//================================================
void CGuardEffect::Draw(void)
{
	
}

//================================================
//��������
//================================================
CGuardEffect* CGuardEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//�C���X�^���X�̐���
	CGuardEffect *pGuardEffect = nullptr;
	if (pGuardEffect == nullptr)
	{
		pGuardEffect = new CGuardEffect();
		if (pGuardEffect != nullptr)
		{
			pGuardEffect->m_rot = rot;
			pGuardEffect->Init(pos, size);
		}
	}
	return pGuardEffect;
}
