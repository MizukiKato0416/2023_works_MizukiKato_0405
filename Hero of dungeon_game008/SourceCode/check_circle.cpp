//================================================
//���@�w�̏���
//Author:KatoMizuki
//================================================
#include "check_circle.h"
#include "effect3D.h"
#include "texture.h"
#include "object2D.h"
#include "manager.h"
#include "play_data.h"
#include "gauge.h"
#include "map.h"
#include "sound.h"

//================================================
//�}�N����`
//================================================
#define CHECK_CIRCLE_EFFECT_NUM		(rand() % 16 + 8)						//�G�t�F�N�g�̐�
#define CHECK_CIRCLE_EFFECT_ROT		(float (rand() % 629 + -314) / 100)		//�G�t�F�N�g���o���ꏊ�����߂邽�߂̊p�x
#define CHECK_CIRCLE_EFFECT_COUNTER	(rand() % 120 + 30)						//�G�t�F�N�g���o���p�x
#define CHECK_CIRCLE_MAX_GAUGE		(300)									//�Q�[�W�ő�l

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CCheckCircle::CCheckCircle(int nPriority) :CMagicCircle(nPriority)
{
	m_nEffectCounter = 0;
	m_pMask = nullptr;
	m_pGauge = nullptr;
	m_pGaugeFrame = nullptr;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CCheckCircle::~CCheckCircle()
{

}

//================================================
//����������
//================================================
HRESULT CCheckCircle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CMagicCircle::Init(pos,size);

	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::CHECK_CIRCLE);

	//�ϐ�������
	m_nEffectCounter = 0;
	m_pMask = nullptr;
	m_pGauge = nullptr;
	m_pGaugeFrame = nullptr;

	
	

	return S_OK;
}

//================================================
//�I������
//================================================
void CCheckCircle::Uninit(void)
{
	//�}�b�v��̓G�̈ʒu�j��
	CMap::Delete(this);

	if (m_pMask != nullptr)
	{
		//�}�X�N���폜
		m_pMask->Uninit();
		m_pMask = nullptr;
	}
	if (m_pGaugeFrame != nullptr)
	{
		//�Q�[�W�̃t���[�����폜
		m_pGaugeFrame->Uninit();
		m_pGaugeFrame = nullptr;
	}
	if (m_pGauge != nullptr)
	{
		//�Q�[�W���폜
		m_pGauge->Uninit();
		m_pGauge = nullptr;
	}

	CMagicCircle::Uninit();
}

//================================================
//�X�V����
//================================================
void CCheckCircle::Update(void)
{
	CMagicCircle::Update();

	//�v���C���[�Ƃ̓����蔻��
	if (CollisionPlayer() == true)
	{
		if (m_pGauge != nullptr)
		{
			//�Q�[�W�̗ʂ�����̈ȏ�ɂȂ�����
			if (m_pGauge->GetGauge() >= m_pGauge->GetMaxNum())
			{
				//�T�E���h�擾����
				CSound *pSound;
				pSound = CManager::GetInstance()->GetSound();

				//SE�Đ�
				pSound->Play(CSound::SOUND_LABEL_CURE_SE);
				//�T�E���h�̉��ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_CURE_SE, 1.3f);

				//HP��MP���񕜂�����
				CManager::GetInstance()->GetPlayData()->GetHpGauge()->AddGauge(200);
				CManager::GetInstance()->GetPlayData()->GetMpGauge()->AddGauge(200);

				//�`�F�b�N�|�C���g������
				Uninit();
				return;
			}
		}

		if (m_pMask == nullptr)
		{
			//�}�X�N���쐬
			m_pMask = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
										D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_MASK);
			m_pMask->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_CHECK_MASK"));
		}
		if (m_pGaugeFrame == nullptr)
		{
			//�Q�[�W�̃t���[�����쐬
			m_pGaugeFrame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
												D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_UI);
			m_pGaugeFrame->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_CHECK_GAUGE_FRAME"));
		}
		if (m_pGauge == nullptr)
		{
			//�Q�[�W���쐬
			m_pGauge = CGauge::Create(D3DXVECTOR3(480.84f, 352.0f + 15.01f / 2.0f, 0.0f), D3DXVECTOR3(317.36f, 15.01f, 0.0f), CHECK_CIRCLE_MAX_GAUGE, 0);
			m_pGauge->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_CHECK_GAUGE"));
		}
		//�`�F�b�N�|�C���g�̃Q�[�W�𑝂₷
		m_pGauge->AddGauge(1);
	}
	else
	{
		if (m_pMask != nullptr)
		{
			//�}�X�N���폜
			m_pMask->Uninit();
			m_pMask = nullptr;
		}
		if (m_pGaugeFrame != nullptr)
		{
			//�Q�[�W�̃t���[�����폜
			m_pGaugeFrame->Uninit();
			m_pGaugeFrame = nullptr;
		}
		if (m_pGauge != nullptr)
		{
			//�Q�[�W���폜
			m_pGauge->Uninit();
			m_pGauge = nullptr;
		}
	}

	//�J�E���^�[�����Z
	m_nEffectCounter++;
	//�K��l�����傫���Ȃ�����
	if (m_nEffectCounter >= CHECK_CIRCLE_EFFECT_COUNTER)
	{
		//�G�t�F�N�g�̐���
		for (int nCnteffect = 0; nCnteffect < CHECK_CIRCLE_EFFECT_NUM; nCnteffect++)
		{
			float fRot = CHECK_CIRCLE_EFFECT_ROT;
			CEffect3D::Create(D3DXVECTOR3(m_pos.x + cosf(fRot) * m_size.x / 2.0f,
													m_pos.y,
													m_pos.z + sinf(fRot) * m_size.z / 2.0f),
							  D3DXVECTOR3(5.0f, 5.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.3f, 1.0f), CEffect3D::EFFECT3D_TYPE::CHECK);
		}
		//0�ɂ���
		m_nEffectCounter = 0;
	}
}

//================================================
//�`�揈��
//================================================
void CCheckCircle::Draw(void)
{
	CMagicCircle::Draw();
}

//================================================
//��������
//================================================
CCheckCircle* CCheckCircle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//�C���X�^���X�̐���
	CCheckCircle *pCheckCircle = nullptr;
	if (pCheckCircle == nullptr)
	{
		pCheckCircle = new CCheckCircle();
		if (pCheckCircle != nullptr)
		{
			pCheckCircle->m_rot = rot;
			pCheckCircle->Init(pos, size);
		}
	}
	return pCheckCircle;
}


//================================================
//�v���C���[�Ƃ̓����蔻��
//================================================
bool CCheckCircle::CollisionPlayer(void)
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
