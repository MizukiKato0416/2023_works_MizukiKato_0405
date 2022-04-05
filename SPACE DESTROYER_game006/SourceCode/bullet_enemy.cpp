//================================================
//�G�̒e����
//Authore:��������
//================================================
#include "scene2D.h"
#include "scene.h"
#include "manager.h"
#include "bullet_enemy.h"
#include "renderer.h"
#include "explosion.h"
#include "sound.h"
#include "effect.h"
#include "game01.h"
#include "texture.h"
#include "player.h"
#include "life.h"
#include "boss.h"


#ifndef _DEBUG
//#define NDEBUG
#endif // !_DEBUG
#include <assert.h>

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CBulletEnemy::m_pTexture = NULL;

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CBulletEnemy::CBulletEnemy(int nPriority) :CBullet(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nType = BULLET_TYPE_NONE;
	m_fRot = 0.0f;
	m_fDistance = 0.0f;
	m_bHoming = false;
	m_nLaserCounter = 0;
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
HRESULT CBulletEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	m_pos = pos;
	m_fDistance = 0.0f;
	m_size = size;
	m_move = move;
	m_bHoming = true;
	m_nLaserCounter = 0;

	CBullet::Init(pos, size, move);

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_BULLET_ENEMY);

	return S_OK;
}

//================================================
//�I������
//================================================
void CBulletEnemy::Uninit(void)
{
	CBullet::Uninit();
}

//================================================
//�X�V����
//================================================
void CBulletEnemy::Update(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//�ʒu�擾
	//m_pos = GetPos();

	m_pos += m_move;		//�ړ��ʔ��f

	//�ʒu���f
	CScene2D::SetPos(m_pos, m_size);

	//��ʊO�ɏo����
	if (m_pos.x + m_size.x / 2.0f < 0.0f || m_pos.x - m_size.x / 2.0f > SCREEN_WIDTH ||
		m_pos.y + m_size.y / 2.0f < 0.0f || m_pos.y - m_size.y / 2.0f > SCREEN_HEIGHT)
	{
		Uninit();
		return;
	}

	//�v���C���[���擾
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			//�V�[����nCnt�Ԗڂ̃|�C���^�擾
			CScene *pScene;
			pScene = CScene::GetScene(nCntScene, nCntPriority);

			if (pScene != NULL)
			{
				//�I�u�W�F�N�g�^�C�v�擾
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				if (objType == CScene::OBJTYPE_PLAYER)
				{
					//�V�[���̃|�C���^���v���C���[�̌^�ɃL���X�g
					CPlayer *pPlayer = (CPlayer*)pScene;

					//�v���C���[�̏�Ԃ��_���[�W���󂯂Ă����ԂłȂ��Ƃ������蔻����s��
					if (pPlayer->GetPlayerState() != CPlayer::PLAYER_STATE_DAMAGE)
					{
						//�e�̓����蔻��
						if (Collision(m_pos, pSound) == true)
						{
							return;
						}
					}
				}
			}
		}
	}

	//�Q�[���̏�Ԃ��擾
	if (CManager::GetMode() == CManager::MODE_GAME01)
	{
		if (CManager::GetGame01()->GetState() == CGame01::GAME_STATE_CLEAR)
		{
			Uninit();
			return;
		}
	}

	//�ړ��̐ݒ�
	MoveType();
}

//================================================
//�`�揈��
//================================================
void CBulletEnemy::Draw(void)
{
	CBullet::Draw();
}

//================================================
//��������
//================================================
CBulletEnemy *CBulletEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CBulletEnemy::BULLET_TYPE type, CTexture::TYPE textureType)
{
	//�C���X�^���X�̐���
	CBulletEnemy *pBulletEnemy = NULL;
	if (pBulletEnemy == NULL)
	{
		pBulletEnemy = new CBulletEnemy;
		if (pBulletEnemy != NULL)
		{
			pBulletEnemy->Init(pos, size, move);
			m_pTexture = CManager::GetTexture()->GetTexture(textureType);
			pBulletEnemy->BindTexture(m_pTexture);
			pBulletEnemy->m_nType = type;
		}
	}
	return pBulletEnemy;
}

//================================================
//�����蔻�菈��
//================================================
bool CBulletEnemy::Collision(D3DXVECTOR3 pos, CSound *pSound)
{
	bool bCol = false;		//�����������ǂ����̃t���O

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			//�V�[����nCnt�Ԗڂ̃|�C���^�擾
			CScene *pScene;
			pScene = CScene::GetScene(nCntScene, nCntPriority);

			if (pScene != NULL)
			{
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				if (objType == CScene::OBJTYPE_PLAYER)
				{
					D3DXVECTOR3 PlayerPos = pScene->GetPos();
					D3DXVECTOR3 PlayerSize = pScene->GetSize();
					if (pos.x + m_size.x / 2.0f >= PlayerPos.x - PlayerSize.x / 2.0f + PLAYER_COLLISION_ENEMY_BULLET_ADJUST &&
						pos.x - m_size.x / 2.0f <= PlayerPos.x + PlayerSize.x / 2.0f - PLAYER_COLLISION_ENEMY_BULLET_ADJUST &&
						pos.y + m_size.y / 2.0f >= PlayerPos.y - PlayerSize.y / 2.0f + PLAYER_COLLISION_ENEMY_BULLET_ADJUST &&
						pos.y - m_size.y / 2.0f <= PlayerPos.y + PlayerSize.y / 2.0f - PLAYER_COLLISION_ENEMY_BULLET_ADJUST)
					{
						//�V�[���̃|�C���^���v���C���[�̌^�ɃL���X�g
						CPlayer *pPlayer = (CPlayer*)pScene;

						//������������
						bCol = true;
						//�����̐���
						CExplosion::Create(PlayerPos, D3DXVECTOR3(EXPLOSION_WIDTH, EXPLOSION_HEIGHT, 0.0f));
						//�T�E���h�̍Đ�
						pSound->Play(CSound::SOUND_LABEL_EXPLOSION_SE);
						if (m_nType != BULLET_TYPE_LASER)
						{
							//�e�̔j��
							Uninit();
						}
						//�v���C���[�̏�Ԃ�ݒ�
						pPlayer->SetPlayerState(CPlayer::PLAYER_STATE_DAMAGE);
						//���C�t�̃|�C���^�擾
						CLife *pLife;
						pLife = CGame01::GetLife();
						//�v���C���[�̃��C�t�����炷
						pPlayer->SetLife(-1);
						//���C�t��ݒ�
						pLife->SubtractLife(1);
						
						break;
					}
				}
			}
		}
	}
	return bCol;
}

//================================================
//�ړ��ʊǗ�����
//================================================
void CBulletEnemy::MoveType(void)
{
	//�v���C���[�ƒe�̊p�x�v�Z�p
	float fTanR = 0.0f;
	//�v���C���[�̃|�C���^�[
	CPlayer *pPlayer = NULL;
	//�v���C���[�̈ʒu�ۑ��p
	D3DXVECTOR3 posPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�v���C���[�Ƃ̋���
	float fDiffer = 0;

	switch (m_nType)
	{
	case BULLET_TYPE_STRAIGHT:
		break;
	case BULLET_TYPE_HOMING:
		for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
		{
			for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
			{
				//�V�[����nCnt�Ԗڂ̃|�C���^�擾
				CScene *pScene;
				pScene = CScene::GetScene(nCntScene, nCntPriority);

				if (pScene != NULL)
				{
					//�I�u�W�F�N�g�^�C�v�擾
					CScene::OBJTYPE objType;
					objType = pScene->GetObjType();

					if (objType == CScene::OBJTYPE_PLAYER)
					{
						//�V�[���̃|�C���^���v���C���[�̌^�ɃL���X�g
						pPlayer = (CPlayer*)pScene;

						//�v���C���[�̈ʒu���擾
						posPlayer = pPlayer->GetPos();

						fDiffer = sqrtf(((posPlayer.x - m_pos.x) * (posPlayer.x - m_pos.x)) + ((posPlayer.y - m_pos.y) * (posPlayer.y - m_pos.y)));
						if (fDiffer >= BULLET_ENEMY_FINISH_HOMING)
						{
							if (m_bHoming == true)
							{
								//�v���C���[�ƓG�̒e�̊p�x���v�Z
								fTanR = atan2f(posPlayer.y - m_pos.y, posPlayer.x - m_pos.x);
								//�v���C���[�Ɍ������čs���悤�ړ��ʂ��v�Z
								m_move = D3DXVECTOR3(cosf(fTanR) * BULLET_ENEMY_HOMING_SPEED, sinf(fTanR) * BULLET_ENEMY_HOMING_SPEED, 0.0f);
							}
						}
						else
						{
							m_bHoming = false;
						}
					}
				}
			}
		}
		break;
	case BULLET_TYPE_LASER:
		//�J�E���^�[�����Z
		m_nLaserCounter++;
		
		if (m_nLaserCounter >= BOSS_BODY_SHOOT_LASER_TIME)
		{
			if (m_size.x <= 0.0f)
			{
				m_nLaserCounter = 0;
				m_size.x = 0.0f;
				Uninit();
			}
			else
			{
				//�T�C�Y�����X�ɏ���������
				m_size.x -= 4.0f;
			}
		}
		else
		{
			//�T�C�Y������̑傫���ɕێ�����
			if (m_size.y >= BULLET_ENEMY_BOSS_LASER_HEIGHT)
			{
				m_size.y = BULLET_ENEMY_BOSS_LASER_HEIGHT;
			}
			else
			{
				//�T�C�Y�����X�ɑ傫������
				m_size.y += 20.0f;
				//y���ɃT�C�Y��L�΂������ʒu��y���W���ړ�������
				m_pos.y += 10.0f;
			}
			if (m_size.x >= BULLET_ENEMY_BOSS_LASER_WIDTH)
			{
				m_size.x = BULLET_ENEMY_BOSS_LASER_WIDTH;
			}
			else
			{
				//�T�C�Y�����X�ɑ傫������
				m_size.x += 5.0f;
			}

		}


		break;
	default:
		//assert(false);
		break;
	}
}