//================================================
//�G�̒e����
//Author:KatoMizuki
//================================================
#include "bullet_enemy.h"
#include "manager.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "floor.h"
#include "model_single.h"
#include "player.h"
#include "play_data.h"
#include "gauge.h"
#include "guard_effect.h"
#include "sound.h"

//================================================
//�}�N����`
//================================================
#define BULLET_ENEMY_MOVE_SPEED		(15.0f)		//�e�̈ړ����x
#define BULLET_ENEMY_LIFE			(300)		//����
#define BULLET_ENEMY_DAMAGE			(30)		//�_���[�W��
#define BULLET_ENEMY_GUARD_ADD_SP	(2)			//�K�[�h����SP������

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CBulletEnemy::CBulletEnemy(int nPriority) :CBillboard(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CBulletEnemy::~CBulletEnemy()
{

}

//================================================
//����������
//================================================
HRESULT CBulletEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_nLife = 0;

	CBillboard::Init(pos,size);

	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::BULLET_ENEMY);

	//�I�u�W�F�N�g��������|�C���^
	CObject *pObject = nullptr;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CObject *pSaveObject = nullptr;
	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CObject::PRIORITY_PLAYER);

	while (pObject != nullptr)
	{
		//���݂̎��̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;

		//�I�u�W�F�N�g�̎�ނ��v���C���[��������
		if (pObject->GetObjType() == CObject::OBJTYPE::PLAYER)
		{
			//�I�u�W�F�N�g�̈ʒu�ƃT�C�Y���擾
			D3DXVECTOR3 posObj = pObject->GetPos();
			D3DXVECTOR3 sizeObj = pObject->GetSize();

			//�ʒu���T�C�Y������
			posObj.y += sizeObj.y;

			//�ړ��ʂ����߂邽�߂̃x�N�g��
			D3DXVECTOR3 moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//�v���C���[�̈ʒu���玩�g�̈ʒu�̃x�N�g�������߂�
			moveVec = D3DXVECTOR3(m_pos.x - posObj.x, m_pos.y - posObj.y, m_pos.z - posObj.z);

			//�Z�o�����x�N�g���𐳋K��
			D3DXVec3Normalize(&moveVec, &moveVec);

			//�ړ��ʂ��x�N�g�������ƂɎZ�o
			m_move = D3DXVECTOR3(-moveVec.x * BULLET_ENEMY_MOVE_SPEED, -moveVec.y * BULLET_ENEMY_MOVE_SPEED, -moveVec.z * BULLET_ENEMY_MOVE_SPEED);
		}
		//���̃I�u�W�F�N�g�ɐi�߂�
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}

	//�r���{�[�h�̃��[�h�ݒ�
	SetMode(BILLBOARD_MODE::NORMAL);

	return S_OK;
}

//================================================
//�I������
//================================================
void CBulletEnemy::Uninit(void)
{
	CBillboard::Uninit();
}

//================================================
//�X�V����
//================================================
void CBulletEnemy::Update(void)
{
	//�J�E���^�[�����Z
	m_nLife++;

	//�K��l�ȏ�ɂȂ�����
	if (m_nLife >= BULLET_ENEMY_LIFE)
	{
		//0�ɂ���
		m_nLife = 0;
		//����
		Uninit();
		return;
	}

	//�ړ��ʂ��ʒu�ɉ��Z
	m_pos += m_move;

	//�ʒu�̐ݒ�
	SetPos(m_pos, m_size);

	//3D�|���S���Ƃ̓����蔻��
	if (CFloor::Collision(this) == true)
	{
		Uninit();
		return;
	}

	//���f���Ƃ̓����蔻��
	if (CModelSingle::CollisionAny(this) == true)
	{
		Uninit();
		return;
	}

	//�v���C���[�Ƃ̓����蔻��
	CollisionPlayer();
}

//================================================
//�`�揈��
//================================================
void CBulletEnemy::Draw(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);

	CBillboard::Draw();

	//���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�A���t�@�e�X�g���ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}

//================================================
//��������
//================================================
CBulletEnemy* CBulletEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X�̐���
	CBulletEnemy *pBulletEnemy = nullptr;
	if (pBulletEnemy == nullptr)
	{
		pBulletEnemy = new CBulletEnemy();
		if (pBulletEnemy != nullptr)
		{
			pBulletEnemy->m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pBulletEnemy->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_BULLET_ENEMY");
			pBulletEnemy->Init(pos, size);
		}
	}
	return pBulletEnemy;
}

//================================================
//�v���C���[�Ƃ̓����蔻��
//================================================
void CBulletEnemy::CollisionPlayer(void)
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
			//�v���C���[�ɃL���X�g
			CPlayer *pPlayerObj = nullptr;
			pPlayerObj = (CPlayer*)pObject;

			//�v���C���[�Ƃ̓����蔻��
			if (pPlayerObj->CollisionOnly(this, m_size.x / 2.0f) == true)
			{
				//���������Ƃ��̏���
				if (pPlayerObj->GetState() == CPlayer::PLAYER_STATE::NORMAL)
				{//�ʏ��ԂȂ�
					//�K�[�h���Ă��Ȃ�������
					if (pPlayerObj->GetGuard() == false)
					{
						//�_���[�W��Ԃɂ���
						pPlayerObj->SetState(CPlayer::PLAYER_STATE::DAMAGE);
						//HP�����炷
						CManager::GetInstance()->GetPlayData()->GetHpGauge()->AddGauge(-BULLET_ENEMY_DAMAGE);
						//���C�t��0�ɂȂ�����
						if (CManager::GetInstance()->GetPlayData()->GetHpGauge()->GetGauge() <= 0)
						{
							//�Q�[���I�[�o�[�ɂ���
							CManager::GetInstance()->GetPlayData()->SetGameOver(true);
						}
					}
					else
					{//�K�[�h���Ă�����
						//�v���C���[�̈ʒu�ƌ����擾
						D3DXVECTOR3 posPlayer = pPlayerObj->GetPos();
						D3DXVECTOR3 rotPlayer = pPlayerObj->GetRot();
						float fRotPlayerY = rotPlayer.y;

						//�v���C���[�Ƃ̊p�x�����߂�
						float fRot = atan2((posPlayer.x - m_pos.x), (posPlayer.z - m_pos.z));

						//�v���C���[�̌����������}�C�i�X�̎�D3DXPI*2�𑫂�
						if (fRotPlayerY < 0.0f && fRot > 0.0f)
						{
							fRotPlayerY += D3DX_PI * 2.0f;
						}
						else if (rotPlayer.y > 0.0f && fRot < 0.0f)
						{//�v���C���[�Ƃ̊p�x�������}�C�i�X�̎�D3DXPI*2�𑫂�
							fRot += D3DX_PI * 2.0f;
						}

						float fDiffer = abs(fRotPlayerY - fRot);
						//�����̍���90�x�ȏ゠������
						if (fDiffer> D3DX_PI / 2.0f)
						{
							//�_���[�W��Ԃɂ���
							pPlayerObj->SetState(CPlayer::PLAYER_STATE::DAMAGE);
							//HP�����炷
							CManager::GetInstance()->GetPlayData()->GetHpGauge()->AddGauge(-BULLET_ENEMY_DAMAGE);
							//���C�t��0�ɂȂ�����
							if (CManager::GetInstance()->GetPlayData()->GetHpGauge()->GetGauge() <= 0)
							{
								//�Q�[���I�[�o�[�ɂ���
								CManager::GetInstance()->GetPlayData()->SetGameOver(true);
							}
						}
						else
						{
							//�T�E���h�擾����
							CSound *pSound;
							pSound = CManager::GetInstance()->GetSound();

							//SE�Đ�
							pSound->Play(CSound::SOUND_LABEL_GUARD_SE);
							//�T�E���h�̉��ʒ���
							pSound->ControllVoice(CSound::SOUND_LABEL_GUARD_SE, 1.3f);

							//�K�[�h�G�t�F�N�g�̐���
							CGuardEffect::Create(D3DXVECTOR3(posPlayer.x + sinf(rotPlayer.y - D3DX_PI) * GUARD_EFFECT_POS,
								                             posPlayer.y + GUARD_EFFECT_POS_Y,
								                             posPlayer.z + cosf(rotPlayer.y - D3DX_PI) * GUARD_EFFECT_POS),
								                 D3DXVECTOR3(GUARD_EFFECT_SIZE, GUARD_EFFECT_SIZE, 0.0f), rotPlayer);

							//SP�Q�[�W�𑝂₷
							CManager::GetInstance()->GetPlayData()->GetSpGauge()->AddGauge(BULLET_ENEMY_GUARD_ADD_SP);
						}
					}
				}

				//����
				Uninit();
			}
		}
		//���̃I�u�W�F�N�g�ɐi�߂�
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

