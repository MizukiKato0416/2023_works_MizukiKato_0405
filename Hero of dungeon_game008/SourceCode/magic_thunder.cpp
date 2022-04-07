//================================================
//�����@�̏���
//Author:KatoMizuki
//================================================
#include "magic_thunder.h"
#include "effect3D.h"
#include "texture.h"
#include "magic_circle.h"
#include "manager.h"
#include "texture.h"
#include "object3D.h"
#include "enemy.h"

//================================================
//�}�N����`
//================================================
#define MAGIC_THUNDER_CIRCLE_SIZE				(800.0f)							//���@�w�̃T�C�Y
#define MAGIC_THUNDER_CIRCLE_ADD_SIZE			(30.0f)								//���@�w��傫������l
#define MAGIC_THUNDER_CIRCLE_SUBTRACTION_SIZE	(40.0f)								//���@�w������������l
#define MAGIC_THUNDER_COUNTER					(400)								//���@�w���o������
#define MAGIC_THUNDER_SUBTRACTION_COUNTER		(420)								//���@�w�����������n�߂鎞��
#define MAGIC_THUNDER_EFFECT_NUM				(8)									//���G�t�F�N�g�̐�
#define MAGIC_THUNDER_EFFECT_SIZ_X				(0.1f)								//���G�t�F�N�g�̃T�C�YX
#define MAGIC_THUNDER_EFFECT_SIZ_Y				(1200.0f)							//���G�t�F�N�g�̃T�C�YY
#define MAGIC_THUNDER_EFFECT_COLOR				(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))	//���G�t�F�N�g�̐F
#define MAGIC_THUNDER_EFFECT_FLASH_SIZE			(0.1f)								//�M���G�t�F�N�g�̃T�C�Y
#define MAGIC_THUNDER_EFFECT_FLASH_POS_Y		(120.0f)							//�M���G�t�F�N�g��y���W

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CMagicThunder::CMagicThunder(int nPriority) :CObject(nPriority)
{
	m_pMagicCircle = nullptr;
	m_nCounter = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CMagicThunder::~CMagicThunder()
{

}

//================================================
//����������
//================================================
HRESULT CMagicThunder::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�ϐ�������
	m_nCounter = 0;
	m_pos = pos;
	m_size = size;

	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::MAGIC_THUNDER);
	
	//���@�w���o��
	m_pMagicCircle = CMagicCircle::Create(m_pos, D3DXVECTOR3(1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�e�N�X�`����ݒ�
	m_pMagicCircle->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MAGIC_CIRCLE_01"));
	//�J�����O���I�t
	m_pMagicCircle->SetCulling(false);
	//���Z�������I��
	m_pMagicCircle->SetAlphaBlend(true);
	//�v���C�I���e�B�̐ݒ�
	m_pMagicCircle->SetPriority(CObject::PRIORITY_MAGIC);

	//�G�t�F�N�g�̐���
	for (int nCnteffect = 0; nCnteffect < MAGIC_THUNDER_EFFECT_NUM; nCnteffect++)
	{
		CEffect3D *pEffect3D = nullptr;
		pEffect3D = CEffect3D::Create(D3DXVECTOR3(pos.x + cosf(D3DX_PI * 2.0f / (float)MAGIC_THUNDER_EFFECT_NUM * nCnteffect) * MAGIC_THUNDER_CIRCLE_SIZE / 2.0f,
													0.0f,
													pos.z + sinf(D3DX_PI * 2.0f / (float)MAGIC_THUNDER_EFFECT_NUM * nCnteffect) * MAGIC_THUNDER_CIRCLE_SIZE / 2.0f),
									  D3DXVECTOR3(MAGIC_THUNDER_EFFECT_SIZ_X, MAGIC_THUNDER_EFFECT_SIZ_Y, 0.0f),
			                          MAGIC_THUNDER_EFFECT_COLOR, CEffect3D::EFFECT3D_TYPE::THUNDER);
		pEffect3D->SetMode(CBillboard::BILLBOARD_MODE::BESIDE_ONLY);
	}

	//�G�t�F�N�g�̐���
	CEffect3D::Create(D3DXVECTOR3(pos.x, pos.y - MAGIC_THUNDER_EFFECT_FLASH_POS_Y, pos.z),
			          D3DXVECTOR3(MAGIC_THUNDER_EFFECT_FLASH_SIZE, MAGIC_THUNDER_EFFECT_FLASH_SIZE, 0.0f),
					  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CEffect3D::EFFECT3D_TYPE::FLASH);

	return S_OK;
}

//================================================
//�I������
//================================================
void CMagicThunder::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CMagicThunder::Update(void)
{
	//���@�w�Ɋւ��鏈��
	MagicCircle();
}

//================================================
//�`�揈��
//================================================
void CMagicThunder::Draw(void)
{
	
}

//================================================
//��������
//================================================
CMagicThunder* CMagicThunder::Create(D3DXVECTOR3 pos)
{
	//�C���X�^���X�̐���
	CMagicThunder *pMagicThunder = nullptr;
	if (pMagicThunder == nullptr)
	{
		pMagicThunder = new CMagicThunder();
		if (pMagicThunder != nullptr)
		{
			pMagicThunder->Init(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}
	return pMagicThunder;
}

//================================================
//�����蔻��
//================================================
bool CMagicThunder::Collision(CObject *pSubjectObject)
{
	//�I�u�W�F�N�g��������|�C���^
	CObject *pObject = nullptr;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CObject *pSaveObject = nullptr;

	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CObject::PRIORITY_MAGIC);

	while (pObject != nullptr)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;

		//�I�u�W�F�N�g�̎�ނ������@��������
		if (pObject->GetObjType() == CObject::OBJTYPE::MAGIC_THUNDER)
		{
			//�����@�ɃL���X�g
			CMagicThunder *pMagicThunderObj = nullptr;
			pMagicThunderObj = (CMagicThunder*)pObject;

			//�I�u�W�F�N�g�̈ʒu�ƃT�C�Y���擾
			D3DXVECTOR3 posObj = pSubjectObject->GetPos();
			D3DXVECTOR3 sizeObj = pSubjectObject->GetSize();

			//���S�_����v���C���[�܂ł̋��������߂�
			float fRadius = sqrtf((posObj.x - pMagicThunderObj->m_pos.x) * (posObj.x - pMagicThunderObj->m_pos.x) +
				                  (posObj.z - pMagicThunderObj->m_pos.z) * (posObj.z - pMagicThunderObj->m_pos.z));
			 
			//���@�w�̔��a��1.5�{�ȉ���������
			if (fRadius <= pMagicThunderObj->m_size.x / 2.0f)
			{
				return true;
			}
		}
		//���̃I�u�W�F�N�g�ɐi�߂�
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
	return false;
}

//================================================
//���@�w�Ɋւ��鏈��
//================================================
void CMagicThunder::MagicCircle(void)
{
	if (m_pMagicCircle != nullptr)
	{
		//�ʒu�ƃT�C�Y���擾
		m_pos = m_pMagicCircle->GetPos();
		m_size = m_pMagicCircle->GetSize();

		//�J�E���^�[�����Z
		m_nCounter++;

		//����̒l�ȉ��̎�
		if (m_nCounter <= MAGIC_THUNDER_COUNTER)
		{
			//����̒l��菬����������
			if (m_size.x < MAGIC_THUNDER_CIRCLE_SIZE)
			{
				//�T�C�Y��傫������
				m_size.x += MAGIC_THUNDER_CIRCLE_ADD_SIZE;
				m_size.z += MAGIC_THUNDER_CIRCLE_ADD_SIZE;

				//����̃T�C�Y�𒴂�����
				if (m_size.x >= MAGIC_THUNDER_CIRCLE_SIZE)
				{
					//����̃T�C�Y�ɂ���
					m_size.x = MAGIC_THUNDER_CIRCLE_SIZE;
					m_size.z = MAGIC_THUNDER_CIRCLE_SIZE;
				}

				//�T�C�Y��ݒ�
				m_pMagicCircle->SetPos(m_pos, m_size);
			}
		}
		else
		{//����̒l�����傫���Ƃ�
		 //����̒l�����������Ƃ�
			if (m_nCounter < MAGIC_THUNDER_SUBTRACTION_COUNTER)
			{
				//�T�C�Y��傫������
				m_size.x += MAGIC_THUNDER_CIRCLE_ADD_SIZE;
				m_size.z += MAGIC_THUNDER_CIRCLE_ADD_SIZE;
			}
			else
			{//����̒l�ȏ�̎�
			 //�T�C�Y������������
				m_size.x -= MAGIC_THUNDER_CIRCLE_SUBTRACTION_SIZE;
				m_size.z -= MAGIC_THUNDER_CIRCLE_SUBTRACTION_SIZE;

				//�����Ȃ��Ȃ�����
				if (m_size.x <= 0.0f || m_size.z <= 0.0f)
				{
					//����
					m_pMagicCircle->Uninit();
					m_pMagicCircle = nullptr;
				}
			}

			if (m_pMagicCircle != nullptr)
			{
				//�T�C�Y��ݒ�
				m_pMagicCircle->SetPos(m_pos, m_size);
			}
		}
	}
}
