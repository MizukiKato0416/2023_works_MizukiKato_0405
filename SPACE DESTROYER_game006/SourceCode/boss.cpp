//================================================
//�{�X�̏���
//Authore:��������
//================================================
#include "renderer.h"
#include "scene2D.h"
#include "manager.h"
#include "boss.h"
#include "texture.h"
#include "sound.h"
#include "score.h"
#include "explosion.h"
#include "game01.h"
#include "item.h"
#include "bullet_player.h"
#include "player.h"
#include "life.h"
#include "bullet_enemy.h"
#include "effect.h"
#include "Input_pad_x.h"


//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CBoss::m_pTexture[MAX_BOSS_POLYGON] = {};

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CBoss::CBoss(int nPriority) :CScene(nPriority)
{
	for (int nCntPolygon = 0; nCntPolygon < MAX_BOSS_POLYGON; nCntPolygon++)
	{
		m_apScene2D[nCntPolygon] = NULL;
		m_size[nCntPolygon] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pos[nCntPolygon] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_nBulletCounter[nCntPolygon] = 0;
		m_state[nCntPolygon] = BOSS_STATE_NONE;
		m_nDamageCounter[nCntPolygon] = 0;
		m_nLife[nCntPolygon] = 0;
	}

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_shootPhase = BOSS_BODY_SHOOT_PHASE_NONE;
	m_nNextPhase = 0;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CBoss::~CBoss()
{

}

//================================================
//����������
//================================================
HRESULT CBoss::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�ϐ�������
	m_size[0] = D3DXVECTOR3(BOSS_WING_WIDTH, BOSS_WING_HEIGHT, 0.0f);
	m_size[1] = D3DXVECTOR3(BOSS_BODY_WIDTH, BOSS_BODY_HEIGHT, 0.0f);
	m_size[2] = D3DXVECTOR3(BOSS_CANNON_WIDTH, BOSS_CANNON_HEIGHT, 0.0f);
	m_size[3] = D3DXVECTOR3(BOSS_CANNON_WIDTH, BOSS_CANNON_HEIGHT, 0.0f);

	for (int nCntPolygon = 0; nCntPolygon < MAX_BOSS_POLYGON; nCntPolygon++)
	{
		m_size[nCntPolygon].x *= scale.x;
		m_size[nCntPolygon].y *= scale.y;
		m_size[nCntPolygon].z *= scale.z;

		m_nBulletCounter[nCntPolygon] = 0;
		m_state[nCntPolygon] = BOSS_STATE_NORMAL;
		m_nDamageCounter[nCntPolygon] = 0;
	}
	m_pos[0] = pos;
	m_pos[1] = pos;
	m_pos[2] = D3DXVECTOR3(pos.x + BOSS_CANNON_POS, pos.y, pos.z);
	m_pos[3] = D3DXVECTOR3(pos.x - BOSS_CANNON_POS, pos.y, pos.z);

	m_move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_nLife[0] = BOSS_WING_LIFE;
	m_nLife[1] = BOSS_BODY_LIFE;
	m_nLife[2] = BOSS_CANNON_LIFE;
	m_nLife[3] = BOSS_CANNON_LIFE;

	m_shootPhase = BOSS_BODY_SHOOT_PHASE_STRAIGHT;
	m_nNextPhase = 0;

	for (int nCntPolygon = 0; nCntPolygon < MAX_BOSS_POLYGON; nCntPolygon++)
	{
		//�|���S���̐���
		m_apScene2D[nCntPolygon] = new CScene2D(PRIORITY_BOSS);
		m_apScene2D[nCntPolygon]->Init(pos, scale);

		//�e�N�X�`���̊��蓖��
		m_apScene2D[nCntPolygon]->BindTexture(m_pTexture[nCntPolygon]);

		//�ʒu��ݒ�
		m_apScene2D[nCntPolygon]->SetPos(m_pos[nCntPolygon], m_size[nCntPolygon]);
	}

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_BOSS);

	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����

	return S_OK;
}

//================================================
//�I������
//================================================
void CBoss::Uninit(void)
{
	for (int nCntPolygon = 0; nCntPolygon < MAX_BOSS_POLYGON; nCntPolygon++)
	{
		if (m_apScene2D[nCntPolygon] != NULL)
		{
			m_apScene2D[nCntPolygon]->Uninit();
			m_apScene2D[nCntPolygon] = NULL;
		}
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CBoss::Update(void)
{
	//�Q�[���N���A���̏���
	if (CManager::GetGame01()->GetState() == CGame01::GAME_STATE_CLEAR)
	{
		if (GameClear() == true)
		{
			return;
		}
	}
	else if(CManager::GetGame01()->GetState() == CGame01::GAME_STATE_GAME)
	{
		for (int nCntPolygon = 0; nCntPolygon < MAX_BOSS_POLYGON; nCntPolygon++)
		{
			if (m_apScene2D[nCntPolygon] != NULL)
			{
				//�ʒu���擾
				m_pos[nCntPolygon] = m_apScene2D[nCntPolygon]->GetPos();
				//�ړ��ʂ��ʒu�ɔ��f
				m_pos[nCntPolygon] += m_move;

				if (m_pos[nCntPolygon].y >= 100.0f)
				{
					m_pos[nCntPolygon].y = 100.0f;
				}

				//�ʒu��ݒ�
				m_apScene2D[nCntPolygon]->SetPos(m_pos[nCntPolygon], m_size[nCntPolygon]);
				SetPos(m_pos[nCntPolygon]);
				//�T�C�Y��ݒ�
				SetSize(m_size[nCntPolygon]);
				//��Ԃɂ���ĐF��ς���
				StateColor(nCntPolygon);
				//�ˌ�����
				if (nCntPolygon != 0)	//�H�ɂ͎ˌ��������s�킹�Ȃ�
				{
					Shoot(nCntPolygon);
				}
			}
		}

		//�����蔻��
		if (CollisionPlayerBullet() == true)
		{
			return;
		}
	}
}

//================================================
//�`�揈��
//================================================
void CBoss::Draw(void)
{
	
}

//================================================
//��������
//================================================
CBoss* CBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move)
{
	//�C���X�^���X�̐���
	CBoss *pBoss = NULL;
	if (pBoss == NULL)
	{
		pBoss = new CBoss;
		if (pBoss != NULL)
		{
			//�e�N�X�`�����蓖��
			m_pTexture[0] = CManager::GetTexture()->GetTexture(CTexture::TYPE_BOSS_WING);
			m_pTexture[1] = CManager::GetTexture()->GetTexture(CTexture::TYPE_BOSS_BODY);
			m_pTexture[2] = CManager::GetTexture()->GetTexture(CTexture::TYPE_BOSS_CANNON);
			m_pTexture[3] = CManager::GetTexture()->GetTexture(CTexture::TYPE_BOSS_CANNON);
			pBoss->Init(pos, scale);
		}
	}
	return pBoss;
}

//================================================
//��Ԃɉ������F�ɕω������鏈��
//================================================
void CBoss::StateColor(int nCntPolygon)
{
	switch (m_state[nCntPolygon])
	{
	case BOSS_STATE_NORMAL:
		break;
	case BOSS_STATE_DAMAGE:
		//�J�E���^�[�����Z
		m_nDamageCounter[nCntPolygon]++;
		if (m_nDamageCounter[nCntPolygon] >= BOSS_DAMAGE_COUNT)
		{
			//�J�E���^�[��0�ɂ���
			m_nDamageCounter[nCntPolygon] = 0;
			//��Ԃ�NORMAL�ɖ߂�
			m_state[nCntPolygon] = BOSS_STATE_NORMAL;
			//�F�����ɖ߂�
			m_apScene2D[nCntPolygon]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			//�Ԃ�����
			m_apScene2D[nCntPolygon]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
		break;
	default:
		break;
	}
}

//================================================
//�v���C���[�̒e�Ƃ̓����蔻�菈��
//================================================
bool CBoss::CollisionPlayerBullet(void)
{
	bool bCol = false;	//�����������ǂ����̃t���O

	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//�X�R�A�̃|�C���^�擾
	CScore *pScore;
	pScore = CGame01::GetScore();

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

				if (objType == CScene::OBJTYPE_BULLET_PLAYER)
				{
					//�e�̃T�C�Y�ƈʒu�擾
					D3DXVECTOR3 BulletPlayerPos = pScene->GetPos();
					D3DXVECTOR3 BulletPlayerSize = pScene->GetSize();
					//�e�̌����擾
					CBulletPlayer *pBulletPlayer = (CBulletPlayer*)pScene;
					float fBulletPlayerRot = pBulletPlayer->GetRot();
					//�T�C�Y��e�̌����ɂ���Ē���
					D3DXVECTOR3 BulletSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					if (fBulletPlayerRot == 0.0f)
					{
						BulletSize = D3DXVECTOR3(BulletPlayerSize.x, BulletPlayerSize.y, 0.0f);
					}
					else
					{
						BulletSize = D3DXVECTOR3(BulletPlayerSize.y, BulletPlayerSize.x, 0.0f);
					}


					for (int nCntPolygon = 0; nCntPolygon < MAX_BOSS_POLYGON; nCntPolygon++)
					{
						if (m_apScene2D[nCntPolygon] != NULL)
						{
							float fAdjust = 0;		//�����蔻�蒲���p

							//�����蔻��𒲐�
							if (nCntPolygon == 0)
							{
								fAdjust = BOSS_WING_COLLISION_ADJUST;
							}
							else if (nCntPolygon == 1)
							{
								fAdjust = BOSS_BODY_COLLISION_ADJUST;
							}
							else
							{
								fAdjust = BOSS_CANNON_COLLISION_ADJUST;
							}

							if (m_pos[nCntPolygon].x + m_size[nCntPolygon].x / 2.0f >= BulletPlayerPos.x - BulletSize.x / 2.0f &&
								m_pos[nCntPolygon].x - m_size[nCntPolygon].x / 2.0f <= BulletPlayerPos.x + BulletSize.x / 2.0f &&
								m_pos[nCntPolygon].y + m_size[nCntPolygon].y / 2.0f + fAdjust >= BulletPlayerPos.y - BulletSize.y / 2.0f &&
								m_pos[nCntPolygon].y - m_size[nCntPolygon].y / 2.0f <= BulletPlayerPos.y + BulletSize.y / 2.0f)
							{
								//������������
								bCol = true;
								//�����̐���
								CExplosion::Create(BulletPlayerPos, D3DXVECTOR3(EXPLOSION_WIDTH, EXPLOSION_HEIGHT, 0.0f));
								//�T�E���h�̍Đ�
								pSound->Play(CSound::SOUND_LABEL_EXPLOSION_SE);

								//�H�̓_���[�W���󂯂Ȃ�
								if (nCntPolygon != 0)
								{
									//�A�C�e���̐���
									CItem::Create(BulletPlayerPos, D3DXVECTOR3(ITEM_SCORE_WIDTH, ITEM_SCORE_HEIGHT, 0.0f), CItem::ITEM_TYPE_SCORE);
									//�X�R�A���Z
									pScore->AddScore(100);
									//�����������ʂ��_���[�W��Ԃɂ���
									m_state[nCntPolygon] = BOSS_STATE_DAMAGE;
									//���C�t�����炷
									m_nLife[nCntPolygon]--;
								}
								
								//���C�t��0�ɂȂ�����
								if (m_nLife[nCntPolygon] <= 0)
								{
									m_nLife[nCntPolygon] = 0;
									//�̂̃��C�t��0�ɂȂ�����
									if (nCntPolygon == 1)
									{
										//�Q�[���N���A�ɂ���
										CManager::GetGame01()->SetState(CGame01::GAME_STATE_CLEAR);
										//��Ԃ����ɖ߂�
										m_state[nCntPolygon] = BOSS_STATE_NORMAL;
										//�F�����ɖ߂�
										m_apScene2D[nCntPolygon]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
										//�J�E���^�[��0�ɂ���
										m_nDamageCounter[nCntPolygon] = 0;
									}
									else
									{
										//���C�t��0�ɂȂ������ʂ�j��
										m_apScene2D[nCntPolygon]->Uninit();
										m_apScene2D[nCntPolygon] = NULL;
									}
								}
								//�e�̔j��
								pScene->Uninit();
								return bCol;
							}
						}
					}
				}
				else if (objType == CScene::OBJTYPE_PLAYER)
				{
					//�v���C���[�̃T�C�Y�ƈʒu�擾
					D3DXVECTOR3 PlayerPos = pScene->GetPos();
					D3DXVECTOR3 PlayerSize = pScene->GetSize();

					for (int nCntPolygon = 0; nCntPolygon < MAX_BOSS_POLYGON; nCntPolygon++)
					{
						if (m_apScene2D[nCntPolygon] != NULL)
						{
							float fAdjust = 0;		//�����蔻�蒲���p

													//�����蔻��𒲐�
							if (nCntPolygon == 0)
							{
								fAdjust = BOSS_BODY_COLLISION_PLAYER_ADJUST;
							}
							else if (nCntPolygon == 1)
							{
								fAdjust = BOSS_BODY_COLLISION_PLAYER_ADJUST;
							}
							else
							{
								fAdjust = BOSS_CANNON_COLLISION_PLAYER_ADJUST;
							}

							if (m_pos[nCntPolygon].x + m_size[nCntPolygon].x / 2.0f >= PlayerPos.x - PlayerSize.x / 2.0f &&
								m_pos[nCntPolygon].x - m_size[nCntPolygon].x / 2.0f <= PlayerPos.x + PlayerSize.x / 2.0f &&
								m_pos[nCntPolygon].y + m_size[nCntPolygon].y / 2.0f + fAdjust >= PlayerPos.y - PlayerSize.y / 2.0f &&
								m_pos[nCntPolygon].y - m_size[nCntPolygon].y / 2.0f <= PlayerPos.y + PlayerSize.y / 2.0f)
							{
								//�V�[���̃|�C���^���v���C���[�̌^�ɃL���X�g
								CPlayer *pPlayer = (CPlayer*)pScene;

								if (pPlayer->GetPlayerState() != CPlayer::PLAYER_STATE_DAMAGE)
								{
									//������������
									bCol = true;
									//�����̐���
									CExplosion::Create(PlayerPos, D3DXVECTOR3(EXPLOSION_WIDTH, EXPLOSION_HEIGHT, 0.0f));
									//�T�E���h�̍Đ�
									pSound->Play(CSound::SOUND_LABEL_EXPLOSION_SE);
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
			}
		}
	}
	return bCol;
}

//================================================
//�ˌ�����
//================================================
void CBoss::Shoot(int nCntPolygon)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//�J�E���^�[�����Z
	m_nBulletCounter[nCntPolygon]++;
	if (nCntPolygon == 1)
	{
		BodyShoot(nCntPolygon);
	}
	else
	{
		if (m_nBulletCounter[nCntPolygon] >= BOSS_CANNON_SHOOT_COUNTER)
		{
			m_nBulletCounter[nCntPolygon] = 0;

			//�e�̐���
			CBulletEnemy::Create(D3DXVECTOR3(m_pos[nCntPolygon].x - BOSS_CANNON_SHOOT_ADJUST_X, m_pos[nCntPolygon].y + BOSS_CANNON_SHOOT_ADJUST_Y, 0.0f),
									D3DXVECTOR3(BULLET_ENEMY_BOSS_CANNON_HOMING_WIDTH, BULLET_ENEMY_BOSS_CANNON_HOMING_HEIGHT, 0.0f),
									D3DXVECTOR3(0.0f, BULLET_ENEMY_HOMING_SPEED, 0.0f), CBulletEnemy::BULLET_TYPE_HOMING,
									CTexture::TYPE_BULLET_SPHERE);
			//�e�̐���
			CBulletEnemy::Create(D3DXVECTOR3(m_pos[nCntPolygon].x + BOSS_CANNON_SHOOT_ADJUST_X, m_pos[nCntPolygon].y + BOSS_CANNON_SHOOT_ADJUST_Y, 0.0f),
									D3DXVECTOR3(BULLET_ENEMY_BOSS_CANNON_HOMING_WIDTH, BULLET_ENEMY_BOSS_CANNON_HOMING_HEIGHT, 0.0f),
									D3DXVECTOR3(0.0f, BULLET_ENEMY_HOMING_SPEED, 0.0f), CBulletEnemy::BULLET_TYPE_HOMING,
									CTexture::TYPE_BULLET_SPHERE);
		}
	}
}

//================================================
////�̕����̎ˌ���������
//================================================
void CBoss::BodyShoot(int nCntPolygon)
{
	//�p�b�h�擾����
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//���̃t�F�[�Y�ɍs���܂ł̃J�E���^�[�����Z
	m_nNextPhase++;


	//�t�F�[�Y�ʂɏ����𕪂���
	switch (m_shootPhase)
	{
	case BOSS_BODY_SHOOT_PHASE_STRAIGHT:
		if (m_nBulletCounter[nCntPolygon] == BOSS_BODY_SHOOT_STRAIGHT_COUNT_0)
		{
			//�T�E���h�̍Đ�
			pSound->Play(CSound::SOUND_LABEL_BOSS_BULLET_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_BOSS_BULLET_SE, 1.6f);

			//�e�̐���
			CBulletEnemy::Create(D3DXVECTOR3(m_pos[nCntPolygon].x - BOSS_BODY_SHOOT_STRAIGHT_ADJUST, m_pos[nCntPolygon].y + BOSS_BODY_SHOOT_ADJUST_Y, 0.0f),
									D3DXVECTOR3(BULLET_ENEMY_BOSS_STRAIGHT_WIDTH, BULLET_ENEMY_BOSS_STRAIGHT_HEIGHT, 0.0f),
									D3DXVECTOR3(0.0f, BULLET_ENEMY_SPEED, 0.0f), CBulletEnemy::BULLET_TYPE_STRAIGHT,
									CTexture::TYPE_BULLET_BOSS_STRAIGHT);

			//�e�̐���
			CBulletEnemy::Create(D3DXVECTOR3(m_pos[nCntPolygon].x + BOSS_BODY_SHOOT_STRAIGHT_ADJUST, m_pos[nCntPolygon].y + BOSS_BODY_SHOOT_ADJUST_Y, 0.0f),
									D3DXVECTOR3(BULLET_ENEMY_BOSS_STRAIGHT_WIDTH, BULLET_ENEMY_BOSS_STRAIGHT_HEIGHT, 0.0f),
									D3DXVECTOR3(0.0f, BULLET_ENEMY_SPEED, 0.0f), CBulletEnemy::BULLET_TYPE_STRAIGHT, 
									CTexture::TYPE_BULLET_BOSS_STRAIGHT);
		}
		else if (m_nBulletCounter[nCntPolygon] >= BOSS_BODY_SHOOT_STRAIGHT_COUNT_1)
		{
			//�T�E���h�̍Đ�
			pSound->Play(CSound::SOUND_LABEL_BOSS_BULLET_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_BOSS_BULLET_SE, 1.6f);

			//�e�̐���
			CBulletEnemy::Create(D3DXVECTOR3(m_pos[nCntPolygon].x, m_pos[nCntPolygon].y + BOSS_BODY_SHOOT_ADJUST_Y, 0.0f),
									D3DXVECTOR3(BULLET_ENEMY_BOSS_STRAIGHT_WIDTH, BULLET_ENEMY_BOSS_STRAIGHT_HEIGHT, 0.0f),
									D3DXVECTOR3(0.0f, BULLET_ENEMY_SPEED, 0.0f), CBulletEnemy::BULLET_TYPE_STRAIGHT, 
									CTexture::TYPE_BULLET_BOSS_STRAIGHT);

			m_nBulletCounter[nCntPolygon] = 0;
		}

		//��莞�Ԃ𒴂����玟�̃t�F�[�Y�Ɉڍs
		if (m_nNextPhase >= BOSS_BODY_SHOOT_STRAIGHT_PHASE_COUNT)
		{
			m_nBulletCounter[nCntPolygon] = 0;
			m_nNextPhase = 0;
			m_shootPhase = BOSS_BODY_SHOOT_PHASE_DIFFUSION_00;
		}
		break;
	case BOSS_BODY_SHOOT_PHASE_DIFFUSION_00:
		if (m_nBulletCounter[nCntPolygon] == BOSS_BODY_SHOOT_DIFFUSION_00_COUNT)
		{
			//�T�E���h�̍Đ�
			pSound->Play(CSound::SOUND_LABEL_BOSS_BULLET_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_BOSS_BULLET_SE, 1.6f);

			for (int nCntBullet = 0; nCntBullet < BOSS_BODY_SHOOT_DIFFUSION_00_NUM; nCntBullet++)
			{
				//�e�̐���
				CBulletEnemy::Create(D3DXVECTOR3(m_pos[nCntPolygon].x, m_pos[nCntPolygon].y + BOSS_BODY_SHOOT_ADJUST_Y, 0.0f),
										D3DXVECTOR3(BULLET_ENEMY_BOSS_DIFFUSION_WIDTH, BULLET_ENEMY_BOSS_DIFFUSION_HEIGHT, 0.0f),
										D3DXVECTOR3(BULLET_ENEMY_SPEED * cosf((D3DX_PI / (float)(BOSS_BODY_SHOOT_DIFFUSION_00_NUM + 1) * (nCntBullet + 1))),
													BULLET_ENEMY_SPEED * sinf((D3DX_PI / (float)(BOSS_BODY_SHOOT_DIFFUSION_00_NUM + 1) * (nCntBullet + 1))), 0.0f),
										CBulletEnemy::BULLET_TYPE_STRAIGHT, CTexture::TYPE_BULLET_SPHERE);
			}
		}
		else if(m_nBulletCounter[nCntPolygon] >= BOSS_BODY_SHOOT_DIFFUSION_01_COUNT)
		{
			//�T�E���h�̍Đ�
			pSound->Play(CSound::SOUND_LABEL_BOSS_BULLET_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_BOSS_BULLET_SE, 1.6f);

			for (int nCntBullet = 0; nCntBullet < BOSS_BODY_SHOOT_DIFFUSION_01_NUM; nCntBullet++)
			{
				//�e�̐���
				CBulletEnemy::Create(D3DXVECTOR3(m_pos[nCntPolygon].x, m_pos[nCntPolygon].y + BOSS_BODY_SHOOT_ADJUST_Y, 0.0f),
										D3DXVECTOR3(BULLET_ENEMY_BOSS_DIFFUSION_WIDTH, BULLET_ENEMY_BOSS_DIFFUSION_HEIGHT, 0.0f),
										D3DXVECTOR3(BULLET_ENEMY_SPEED * cosf((D3DX_PI / (float)(BOSS_BODY_SHOOT_DIFFUSION_01_NUM + 1) * (nCntBullet + 1))),
													BULLET_ENEMY_SPEED * sinf((D3DX_PI / (float)(BOSS_BODY_SHOOT_DIFFUSION_01_NUM + 1) * (nCntBullet + 1))), 0.0f),
										CBulletEnemy::BULLET_TYPE_STRAIGHT, CTexture::TYPE_BULLET_SPHERE);
			}
			m_nBulletCounter[nCntPolygon] = 0;
		}

		//��莞�Ԃ𒴂����玟�̃t�F�[�Y�Ɉڍs
		if (m_nNextPhase >= BOSS_BODY_SHOOT_DIFFUSION_PHASE_COUNT)
		{
			m_nBulletCounter[nCntPolygon] = 0;
			m_nNextPhase = 0;
			m_shootPhase = BOSS_BODY_SHOOT_PHASE_LASER;
		}
		break;
	case BOSS_BODY_SHOOT_PHASE_LASER:
		if (m_nBulletCounter[nCntPolygon] <= BOSS_BODY_SHOOT_LASER_EFFECT_TIME)
		{
			if (m_nBulletCounter[nCntPolygon] % BOSS_BODY_SHOOT_LASER_EFFECT_COUNT == 0)
			{
				for (int nCntEffect = 0; nCntEffect < BOSS_BODY_SHOOT_LASER_EFFECT_NUM; nCntEffect++)
				{
					//�G�t�F�N�g����
					CEffect::Create(D3DXVECTOR3(m_pos[nCntPolygon].x + BOSS_BODY_SHOOT_LASER_EFFECT_ADJUST * cosf((D3DX_PI / (float)(BOSS_BODY_SHOOT_LASER_EFFECT_NUM + 1) * (nCntEffect + 1))),
												m_pos[nCntPolygon].y + BOSS_BODY_SHOOT_LASER_EFFECT_ADJUST  * sinf((D3DX_PI / (float)(BOSS_BODY_SHOOT_LASER_EFFECT_NUM + 1) * (nCntEffect + 1))), 0.0f),
									D3DXVECTOR3(0.1f, 0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									D3DXCOLOR(255.0f, 0.0f, 255.0f, 255.0f), CEffect::EFFECT_TYPE_BOSS_LASER);
				}
			}
		}
		else if (m_nBulletCounter[nCntPolygon] == BOSS_BODY_SHOOT_LASER_COUNT)
		{
			//�T�E���h�̍Đ�
			pSound->Play(CSound::SOUND_LABEL_BOSS_LASER_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_BOSS_LASER_SE, 2.8f);

			//�e�̐���
			CBulletEnemy::Create(D3DXVECTOR3(m_pos[nCntPolygon].x, m_pos[nCntPolygon].y + BOSS_BODY_SHOOT_ADJUST_Y, 0.0f),
									D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									D3DXVECTOR3(0.0f, 0.0f, 0.0f), CBulletEnemy::BULLET_TYPE_LASER,
									CTexture::TYPE_BULLET_BOSS_LASER);

			//�o�C�u���[�V�����ݒ�
			pInputPadX->SetVibration(60000, 60000, BOSS_BODY_SHOOT_LASER_TIME);

		}
		//��莞�Ԃ𒴂����玟�̃t�F�[�Y�Ɉڍs
		if (m_nNextPhase >= BOSS_BODY_SHOOT_LASER_PHASE_COUNT)
		{
			m_nBulletCounter[nCntPolygon] = 0;
			m_nNextPhase = 0;
			m_shootPhase = BOSS_BODY_SHOOT_PHASE_HOMING;
		}
		break;
	case BOSS_BODY_SHOOT_PHASE_HOMING:
		if (m_nBulletCounter[nCntPolygon] % BOSS_BODY_SHOOT_HOMING_COUNT == 0)
		{
			//�T�E���h�̍Đ�
			pSound->Play(CSound::SOUND_LABEL_BOSS_BULLET_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_BOSS_BULLET_SE, 1.6f);

			//�e�̐���
			CBulletEnemy::Create(D3DXVECTOR3(m_pos[nCntPolygon].x + BOSS_CANNON_SHOOT_ADJUST_X, m_pos[nCntPolygon].y + BOSS_CANNON_SHOOT_ADJUST_Y, 0.0f),
									D3DXVECTOR3(BULLET_ENEMY_BOSS_BODY_HOMING_WIDTH, BULLET_ENEMY_BOSS_BODY_HOMING_HEIGHT, 0.0f),
									D3DXVECTOR3(0.0f, BULLET_ENEMY_HOMING_SPEED, 0.0f), CBulletEnemy::BULLET_TYPE_HOMING,
									CTexture::TYPE_BULLET_BOSS_BODY_HOMING);
		}
		//��莞�Ԃ𒴂����玟�̃t�F�[�Y�Ɉڍs
		if (m_nNextPhase >= BOSS_BODY_SHOOT_HOMING_PHASE_COUNT)
		{
			m_nBulletCounter[nCntPolygon] = 0;
			m_nNextPhase = 0;
			m_shootPhase = BOSS_BODY_SHOOT_PHASE_STRAIGHT;
		}
		break;
	default:
		break;
	}
}

//================================================
//�̂̈ʒu�擾����
//================================================
D3DXVECTOR3 CBoss::GetBodyPos(void)
{
	return m_pos[1];
}

//================================================
//�Q�[���N���A���̏���
//================================================
bool CBoss::GameClear(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//�t���[�����擾
	int nClearCounter = CGame01::GetFinishCounter();

	if (nClearCounter == BOSS_CLEAR_UNINIT_COUNT)
	{
		//�{�X��j��
		Uninit();
		return true;
	}
	else
	{
		if (nClearCounter % BOSS_CLEAR_EXPLOSION_COUNT == 0)
		{
			//�T�E���h�̍Đ�
			pSound->Play(CSound::SOUND_LABEL_DIE_EXPLOSION_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_BOSS_BULLET_SE, 1.6f);

			//�����̐���
			CExplosion::Create(D3DXVECTOR3(BOSS_CLEAR_EXPLOSION_POS_X, BOSS_CLEAR_EXPLOSION_POS_Y, 0.0f),
								D3DXVECTOR3(EXPLOSION_BOSS_UNINIT_WIDTH, EXPLOSION_BOSS_UNINIT_HEIGHT, 0.0f));
		}
	}
	return false;
}
