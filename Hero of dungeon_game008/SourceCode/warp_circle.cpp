//================================================
//���[�v���@�w�̏���
//Author:KatoMizuki
//================================================
#include "warp_circle.h"
#include "effect3D.h"
#include "texture.h"
#include "manager.h"
#include "fade.h"
#include "enemy.h"
#include "ui.h"

//================================================
//�}�N����`
//================================================
#define WARP_CIRCLE_EFFECT_NUM						(rand() % 16 + 8)						//�G�t�F�N�g�̐�
#define WARP_CIRCLE_EFFECT_ROT						(float (rand() % 629 + -314) / 100)		//�G�t�F�N�g���o���ꏊ�����߂邽�߂̊p�x
#define WARP_CIRCLE_EFFECT_COUNTER					(rand() % 120 + 30)						//�G�t�F�N�g���o���p�x
#define WARP_CIRCLE_OBJECT3D_COUNTER				(120)									//��ɏオ��I�u�W�F�N�g��\�����鎞��
#define WARP_CIRCLE_OBJECT3D_MOVE					(0.5f)									//��ɏオ��I�u�W�F�N�g�̈ړ���
#define WARP_CIRCLE_OBJECT3D_COLOR_SUBTRACTION		(0.006f)								//��ɏオ��I�u�W�F�N�g�̃J���[���Z�l

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CWarpCircle::CWarpCircle(int nPriority) :CMagicCircle(nPriority)
{
	m_nEffectCounter = 0;
	m_pObject3D = nullptr;
	m_nObject3DCounter = 0;
	m_pUiMessage = nullptr;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CWarpCircle::~CWarpCircle()
{

}

//================================================
//����������
//================================================
HRESULT CWarpCircle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CMagicCircle::Init(pos,size);

	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::WARP_CIRCLE);

	m_nEffectCounter = 0;
	m_pObject3D = nullptr;
	m_nObject3DCounter = 0;
	m_pUiMessage = nullptr;

	return S_OK;
}

//================================================
//�I������
//================================================
void CWarpCircle::Uninit(void)
{
	CMagicCircle::Uninit();
}

//================================================
//�X�V����
//================================================
void CWarpCircle::Update(void)
{
	CMagicCircle::Update();

	//�G�t�F�N�g��������
	EffectSpawn();

	//��ɏオ��3D�I�u�W�F�N�g��������
	Object3DSpawn();

	//�v���C���[�Ƃ̓����蔻��
	if (CollisionPlayer() == true)
	{
		//�G�����ׂē|���Ă�����
		if (CEnemy::GetNum() == 0)
		{
			//�t�F�[�h�擾����
			CFade *pFade;
			pFade = CManager::GetInstance()->GetFade();

			//�t�F�[�h���Ă��Ȃ��Ƃ�
			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				//���݂̃��[�h�ɂ���đJ�ڐ��ύX
				switch (CManager::GetMode())
				{
				case CManager::MODE::GAME01:
					pFade->SetFade(CManager::MODE::GAME02);
					break;
				case CManager::MODE::GAME02:
					pFade->SetFade(CManager::MODE::GAME03);
					break;
				default:
					break;
				}
			}
		}
		else
		{//�G���c���Ă�����
			if (m_pUiMessage == nullptr)
			{
				//���b�Z�[�WUI�̍쐬
				m_pUiMessage = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
					                       D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
					                       CObject::PRIORITY_UI, CUi::TYPE::MESSAGE_02);
			}
			
		}
	}
	else
	{//�v���C���[�ɓ������Ă��Ȃ��Ƃ�
		if (m_pUiMessage != nullptr)
		{
			
			m_pUiMessage = nullptr;
		}
	}
}

//================================================
//�`�揈��
//================================================
void CWarpCircle::Draw(void)
{
	CMagicCircle::Draw();
}

//================================================
//��������
//================================================
CWarpCircle* CWarpCircle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//�C���X�^���X�̐���
	CWarpCircle *pWarpCircle = nullptr;
	if (pWarpCircle == nullptr)
	{
		pWarpCircle = new CWarpCircle();
		if (pWarpCircle != nullptr)
		{
			pWarpCircle->m_rot = rot;
			pWarpCircle->Init(pos, size);
		}
	}
	return pWarpCircle;
}

//================================================
//�v���C���[�Ƃ̓����蔻��
//================================================
bool CWarpCircle::CollisionPlayer(void)
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
			//�I�u�W�F�N�g�̈ʒu�ƃT�C�Y���擾
			D3DXVECTOR3 posObj = pObject->GetPos();
			D3DXVECTOR3 sizeObj = pObject->GetSize();

			//���S�_����v���C���[�܂ł̋��������߂�
			float fRadius = sqrtf((posObj.x - m_pos.x) * (posObj.x - m_pos.x) +
				                  (posObj.z - m_pos.z) * (posObj.z - m_pos.z));

			//���@�w�̔��a�ȉ���������
			if (fRadius <= m_size.x / 2.0f)
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
//�G�t�F�N�g��������
//================================================
void CWarpCircle::EffectSpawn(void)
{
	//�J�E���^�[�����Z
	m_nEffectCounter++;
	//�K��l�����傫���Ȃ�����
	if (m_nEffectCounter >= WARP_CIRCLE_EFFECT_COUNTER)
	{
		//�G�t�F�N�g�̐���
		for (int nCnteffect = 0; nCnteffect < WARP_CIRCLE_EFFECT_NUM; nCnteffect++)
		{
			float fRot = WARP_CIRCLE_EFFECT_ROT;
			CEffect3D *pEffect3D = nullptr;
			pEffect3D = CEffect3D::Create(D3DXVECTOR3(m_pos.x + cosf(fRot) * m_size.x / 2.0f,
				m_pos.y,
				m_pos.z + sinf(fRot) * m_size.z / 2.0f),
				D3DXVECTOR3(3.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CEffect3D::EFFECT3D_TYPE::CHECK);
			pEffect3D->SetMode(CBillboard::BILLBOARD_MODE::BESIDE_ONLY);
		}
		//0�ɂ���
		m_nEffectCounter = 0;
	}
}

//================================================
//��ɏオ��3D�I�u�W�F�N�g��������
//================================================
void CWarpCircle::Object3DSpawn(void)
{
	//�J�E���^�[�����Z
	m_nObject3DCounter++;
	//�K��l�����傫���Ȃ�����
	if (m_nObject3DCounter >= WARP_CIRCLE_OBJECT3D_COUNTER)
	{
		//0�ɂ���
		m_nObject3DCounter = 0;
		//nullptr����Ȃ�������
		if (m_pObject3D != nullptr)
		{
			//����
			m_pObject3D->Uninit();
			m_pObject3D = nullptr;
		}
		//��ɏオ��3D�|���S���𐶐�
		m_pObject3D = CObject3D::Create(m_pos, m_size, m_rot);
		//�J���[��ݒ�
		m_pObject3D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
		//�e�N�X�`����ݒ�
		m_pObject3D->BindTexture(m_pTexture);
		//�J�����O���s��Ȃ��悤�ɂ���
		m_pObject3D->SetCulling(false);
		//���e�X�g������
		m_pObject3D->SetAlphaTest(true);
	}
	else
	{
		//nullptr����Ȃ�������
		if (m_pObject3D != nullptr)
		{
			//�ʒu���擾
			D3DXVECTOR3 pos = m_pObject3D->GetPos();
			//�J���[���擾
			D3DXCOLOR col = m_pObject3D->GetCol();
			//�ړ��ʂ����Z
			pos.y += WARP_CIRCLE_OBJECT3D_MOVE;
			//�F�𔖂�����
			col.a -= WARP_CIRCLE_OBJECT3D_COLOR_SUBTRACTION;

			//�����Ȃ��Ȃ�����
			if (col.a <= 0.0f)
			{
				//����
				m_pObject3D->Uninit();
				m_pObject3D = nullptr;
			}
			else
			{//�����Ă���Ƃ�
			 //�ʒu�ݒ�
				m_pObject3D->SetPos(pos, m_size);
				//�F��ݒ�
				m_pObject3D->SetCol(col);
			}
		}
	}
}

