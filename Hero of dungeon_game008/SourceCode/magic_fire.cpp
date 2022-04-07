//================================================
//�����@�̏���
//Author:KatoMizuki
//================================================
#include "magic_fire.h"
#include "fire_ball.h"
#include "texture.h"
#include "magic_circle.h"
#include "manager.h"
#include "object3D.h"
#include "player.h"
#include "sound.h"

//================================================
//�}�N����`
//================================================
#define MAGIC_FIRE_CIRCLE_SIZE				(60.0f)		//���@�w�̃T�C�Y
#define MAGIC_FIRE_CIRCLE_ADD_SIZE			(3.5f)		//���@�w��傫������l
#define MAGIC_FIRE_CIRCLE_SUBTRACTION_SIZE	(8.0f)		//���@�w������������l
#define MAGIC_FIRE_COUNTER					(50)		//���@�w���o������
#define MAGIC_FIRE_SUBTRACTION_COUNTER		(60)		//���@�w�����������n�߂鎞��
#define MAGIC_FIRE_BALL_CREATE_COUNTER_01	(20)		//�΋����o������1
#define MAGIC_FIRE_BALL_CREATE_COUNTER_02	(35)		//�΋����o������2
#define MAGIC_FIRE_BALL_CREATE_COUNTER_03	(50)		//�΋����o������3
#define MAGIC_FIRE_BALL_ROT_PARTITION_NUM	(4)			//�p�x������
#define MAGIC_FIRE_BALL_LAYER				(3)			//�w�̐�
#define MAGIC_FIRE_BALL_LIFE				(100)		//����
#define MAGIC_FIRE_BALL_POWRER				(3.8f)		//y=a(x*x)��a�̕���
#define MAGIC_FIRE_BALL_SIZE				(60.0f)		//�T�C�Y

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CMagicFire::CMagicFire(int nPriority) :CObject(nPriority)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pMagicCircle = nullptr;
	m_pFireBall = nullptr;
	m_nCounter = 0;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CMagicFire::~CMagicFire()
{

}

//================================================
//����������
//================================================
HRESULT CMagicFire::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�ϐ�������
	m_nCounter = 0;

	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::MAGIC_FIRE);
	
	//���@�w���o��
	m_pMagicCircle = CMagicCircle::Create(pos, D3DXVECTOR3(1.0f, 1.0f, 0.0f), m_rot);
	//�e�N�X�`����ݒ�
	m_pMagicCircle->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_CHECK_POINT"));
	//�J�����O���I�t
	m_pMagicCircle->SetCulling(false);
	//���e�X�g���I��
	m_pMagicCircle->SetAlphaTest(true);
	//�J���[��ݒ�
	m_pMagicCircle->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	//��]����ݒ�
	m_pMagicCircle->SetRotateType(CMagicCircle::ROTATE_TYPE::Z);
	//�v���C�I���e�B��ݒ�
	m_pMagicCircle->SetPriority(CObject::PRIORITY_MAGIC);

	return S_OK;
}

//================================================
//�I������
//================================================
void CMagicFire::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CMagicFire::Update(void)
{
	if (m_pMagicCircle != nullptr)
	{
		//�ʒu�ƃT�C�Y���擾
		D3DXVECTOR3 pos = m_pMagicCircle->GetPos();
		D3DXVECTOR3 size = m_pMagicCircle->GetSize();

		//�I�u�W�F�N�g��������|�C���^
		CObject *pThisObject = nullptr;
		//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
		CObject *pSaveObject = nullptr;

		//�擪�̃|�C���^����
		pThisObject = pThisObject->GetTopObj(CObject::PRIORITY_PLAYER);

		while (pThisObject != nullptr)
		{
			//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
			pSaveObject = pThisObject;
			if (pThisObject->GetObjType() == CObject::OBJTYPE::PLAYER)
			{
				//�v���C���[�ɃL���X�g
				CPlayer *pPlayer = nullptr;
				pPlayer = (CPlayer*)pThisObject;

				//�v���C���[�̈ʒu�ƌ����擾
				D3DXVECTOR3 posPlayer = pPlayer->GetPos();
				D3DXVECTOR3 rotPlayer = pPlayer->GetRot();

				pos = D3DXVECTOR3(posPlayer.x + sinf(rotPlayer.y - D3DX_PI) * PLAYER_MAGIC_01_POS,
					              posPlayer.y + PLAYER_MAGIC_01_POS_Y,
					              posPlayer.z + cosf(rotPlayer.y - D3DX_PI) * PLAYER_MAGIC_01_POS);
			}
			pThisObject = pSaveObject->GetObjNext(pSaveObject);
		}



		//�J�E���^�[�����Z
		m_nCounter++;

		//����̒l�ȉ��̎�
		if (m_nCounter <= MAGIC_FIRE_COUNTER)
		{
			//����̒l��菬����������
			if (size.x < MAGIC_FIRE_CIRCLE_SIZE)
			{
				//�T�C�Y��傫������
				size.x += MAGIC_FIRE_CIRCLE_ADD_SIZE;
				size.y += MAGIC_FIRE_CIRCLE_ADD_SIZE;

				//����̃T�C�Y�𒴂�����
				if (size.x >= MAGIC_FIRE_CIRCLE_SIZE)
				{
					//����̃T�C�Y�ɂ���
					size.x = MAGIC_FIRE_CIRCLE_SIZE;
					size.y = MAGIC_FIRE_CIRCLE_SIZE;
				}

				//�T�C�Y��ݒ�
				m_pMagicCircle->SetPos(pos, size);
			}

			//����̒l�̎�
			if (m_nCounter == MAGIC_FIRE_BALL_CREATE_COUNTER_01 ||
				m_nCounter == MAGIC_FIRE_BALL_CREATE_COUNTER_02 || 
				m_nCounter == MAGIC_FIRE_BALL_CREATE_COUNTER_03)
			{
				//�T�E���h�擾����
				CSound *pSound;
				pSound = CManager::GetInstance()->GetSound();

				//SE�Đ�
				pSound->Play(CSound::SOUND_LABEL_MAGIC_SE);
				//�T�E���h�̉��ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_MAGIC_SE, 1.8f);

				//�΋��̐���
				CFireBall::Create(pos, MAGIC_FIRE_BALL_ROT_PARTITION_NUM, MAGIC_FIRE_BALL_LAYER, MAGIC_FIRE_BALL_LIFE, MAGIC_FIRE_BALL_POWRER,
					              D3DXVECTOR3(sinf(m_rot.y + D3DX_PI) * MAGIC_FIRE_BALL_MOVE, 0.0f, cosf(m_rot.y + D3DX_PI) * MAGIC_FIRE_BALL_MOVE),
								  D3DXVECTOR3(MAGIC_FIRE_BALL_SIZE, MAGIC_FIRE_BALL_SIZE, MAGIC_FIRE_BALL_SIZE));
			}
		}
		else
		{//����̒l�����傫���Ƃ�
			//����̒l�����������Ƃ�
			if (m_nCounter < MAGIC_FIRE_SUBTRACTION_COUNTER)
			{
				//�T�C�Y��傫������
				size.x += MAGIC_FIRE_CIRCLE_ADD_SIZE;
				size.y += MAGIC_FIRE_CIRCLE_ADD_SIZE;
			}
			else
			{//����̒l�ȏ�̎�
				//�T�C�Y������������
				size.x -= MAGIC_FIRE_CIRCLE_SUBTRACTION_SIZE;
				size.y -= MAGIC_FIRE_CIRCLE_SUBTRACTION_SIZE;

				//�����Ȃ��Ȃ�����
				if (size.x <= 0.0f || size.y <= 0.0f)
				{
					//����
					m_pMagicCircle->Uninit();
					m_pMagicCircle = nullptr;

					Uninit();
					return;
				}
			}
		}

		if (m_pMagicCircle != nullptr)
		{
			//�T�C�Y��ݒ�
			m_pMagicCircle->SetPos(pos, size);
		}
	}
}

//================================================
//�`�揈��
//================================================
void CMagicFire::Draw(void)
{
	
}

//================================================
//��������
//================================================
CMagicFire* CMagicFire::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�C���X�^���X�̐���
	CMagicFire *pMagicFire = nullptr;
	if (pMagicFire == nullptr)
	{
		pMagicFire = new CMagicFire();
		if (pMagicFire != nullptr)
		{
			pMagicFire->m_rot = rot;
			pMagicFire->Init(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}
	return pMagicFire;
}
