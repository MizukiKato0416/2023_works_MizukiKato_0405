//================================================
//�p�[�e�B�N������
//Author:KatoMizuki
//================================================
#include "effect3D.h"
#include "manager.h"
#include "renderer.h"
#include "control_effect_check.h"
#include "control_effect_hit.h"
#include "control_effect_thunder.h"
#include "control_effect_flash.h"
#include "control_effect_fire.h"
#include "control_effect_explosion.h"
#include "texture.h"

//================================================
//�}�N����`
//================================================
#define EFFECT3D_DRAW_DIFFERE		(1000)	//�G�t�F�N�g�̕`�悷��͈�


//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CEffect3D::CEffect3D(int nPriority) :CBillboard(nPriority)
{
	m_type = EFFECT3D_TYPE::NONE;
	m_pControl = nullptr;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CEffect3D::~CEffect3D()
{

}

//================================================
//����������
//================================================
HRESULT CEffect3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CBillboard::Init(pos,size);

	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::EFFECT_3D);

	return S_OK;
}

//================================================
//�I������
//================================================
void CEffect3D::Uninit(void)
{
	CBillboard::Uninit();
	if (m_pControl != nullptr)
	{
		m_pControl->Uninit();
		m_pControl = nullptr;
	}
}

//================================================
//�X�V����
//================================================
void CEffect3D::Update(void)
{
	if (m_pControl != nullptr)
	{
		//�R���g���[���N���X�X�V�������Ăяo��
		m_pControl->Update(this);

		if (m_pControl != nullptr)
		{
			//�ʒu�Ɉړ��ʂ����蓖�Ă�
			m_pos += m_pControl->GetMove();
			//�ʒu�̐ݒ�
			CObject::SetPos(m_pos);
		}
	}
}

//================================================
//�`�揈��
//================================================
void CEffect3D::Draw(void)
{
	//�I�u�W�F�N�g��������|�C���^
	CObject *pObject = nullptr;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CObject *pSaveObject = nullptr;

	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CObject::PRIORITY_PLAYER);

	while (pObject != nullptr)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;

		//�I�u�W�F�N�g�̎�ނ��v���C���[��������
		if (pObject->GetObjType() == CObject::OBJTYPE::PLAYER)
		{
			//�I�u�W�F�N�g�̈ʒu���擾
			D3DXVECTOR3 posObj = pObject->GetPos();

			//���g����Ώۂ̃I�u�W�F�N�g�܂ł̋��������߂�
			float fRadius = sqrtf((posObj.x - m_pos.x) * (posObj.x - m_pos.x) +
				                  (posObj.z - m_pos.z) * (posObj.z - m_pos.z));

			//�f�o�C�X�̃|�C���^
			LPDIRECT3DDEVICE9 pDevice;
			//�f�o�C�X�̎擾
			pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

			if (m_type == EFFECT3D_TYPE::CHECK)
			{
				//���߂�����������̐��l�ȉ���������
				if (fRadius <= EFFECT3D_DRAW_DIFFERE)
				{
					//���u�����f�B���O�����Z�����ɐݒ�
					pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
					pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
					pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

					//���C�e�B���O�𖳌��ɂ���
					pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

					//�A���t�@�e�X�g
					pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
					pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
					pDevice->SetRenderState(D3DRS_ALPHAREF, 50);

					//Z�o�b�t�@�̏�������
					pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

					CBillboard::Draw();

					//Z�e�X�g�����ɖ߂�
					pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

					//���C�e�B���O��L���ɂ���
					pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

					//�A���t�@�e�X�g���ɖ߂�
					pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
					pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
					pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

					//a�u�����f�B���O��ʏ�ɖ߂�
					pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
					pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);
					pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				}
			}
			else
			{
				//���u�����f�B���O�����Z�����ɐݒ�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

				//���C�e�B���O�𖳌��ɂ���
				pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

				//�A���t�@�e�X�g
				pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
				pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
				pDevice->SetRenderState(D3DRS_ALPHAREF, 50);

				//Z�o�b�t�@�̏�������
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

				CBillboard::Draw();

				//Z�e�X�g�����ɖ߂�
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

				//���C�e�B���O��L���ɂ���
				pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

				//�A���t�@�e�X�g���ɖ߂�
				pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
				pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
				pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

				//a�u�����f�B���O��ʏ�ɖ߂�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			}
		}
		//���̃I�u�W�F�N�g�ɐi�߂�
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//================================================
//��������
//================================================
CEffect3D* CEffect3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, EFFECT3D_TYPE type)
{
	//�C���X�^���X�̐���
	CEffect3D *pEffect3D = nullptr;
	if (pEffect3D == nullptr)
	{
		pEffect3D = new CEffect3D();
		if (pEffect3D != nullptr)
		{
			pEffect3D->m_type = type;
			pEffect3D->m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pEffect3D->Init(pos, size);

			//��ނɂ���Ăǂ̃R���g���[���N���X�̔h���N���X�����蓖�Ă邩�����߂�
			switch (pEffect3D->m_type)
			{
			case EFFECT3D_TYPE::NONE:
				pEffect3D->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_3D");
				break;
			case EFFECT3D_TYPE::CHECK:
				pEffect3D->m_pControl = CControlEffectCheck::Create(pEffect3D);
				pEffect3D->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_3D");
				break;
			case EFFECT3D_TYPE::HIT:
				pEffect3D->m_pControl = CControlEffectHit::Create(pEffect3D);
				pEffect3D->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_HIT");
				break;
			case EFFECT3D_TYPE::THUNDER:
				pEffect3D->m_pControl = CControlEffectThunder::Create(pEffect3D);
				pEffect3D->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_3D_002");
				break;
			case EFFECT3D_TYPE::FLASH:
				pEffect3D->m_pControl = CControlEffectFlash::Create(pEffect3D);
				pEffect3D->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_3D");
				break;
			case EFFECT3D_TYPE::FIRE:
				pEffect3D->m_pControl = CControlEffectFire::Create(pEffect3D);
				pEffect3D->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_FIRE");
				break;
			case EFFECT3D_TYPE::EXPLOSION:
				pEffect3D->m_pControl = CControlEffectExplosion::Create(pEffect3D);
				pEffect3D->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_3D");
				break;
			default:
				pEffect3D->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_3D");
				break;
			}
			pEffect3D->SetCol(col);
		}
	}
	return pEffect3D;
}