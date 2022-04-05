//================================================
//���̒e�̏���
//Author:KatoMizuki
//================================================
#include "fire_ball.h"
#include "effect3D.h"
#include "floor.h"
#include "model_single.h"
#include "enemy.h"
#include "explosion.h"
#include "spark.h"
#include "play_data.h"
#include "manager.h"
#include "gauge.h"
#include "player.h"
#include "magic_fire.h"
#include "enemy_boss.h"
#include "score.h"

//================================================
//�}�N����`
//================================================
#define FIRE_BALL_EXPLOSION_SIZE_X				(50.0f)									//�����G�t�F�N�g�̃T�C�YX
#define FIRE_BALL_EXPLOSION_SIZE_Y				(70.0f)									//�����G�t�F�N�g�̃T�C�YY
#define FIRE_BALL_EXPLOSION_EFFECT_NUM			(70)									//�����G�t�F�N�g�̐�
#define FIRE_BALL_EXPLOSION_EFFECT_COLOR		(D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f))		//�����G�t�F�N�g�̐F
#define FIRE_BALL_EXPLOSION_MOVE_MIN			(1.0f)									//�����G�t�F�N�g�̏��������_���ŏ��l
#define FIRE_BALL_EXPLOSION_MOVE_MAX			(4.0f)									//�����G�t�F�N�g�̏��������_���ő�l
#define FIRE_BALL_EXPLOSION_GRAVITY				(-0.7f)									//�����G�t�F�N�g�̏d��
#define FIRE_BALL_EXPLOSION_COL_A_MIN			(0.01f)									//�����G�t�F�N�g�̃��l���Z�����_���ŏ��l
#define FIRE_BALL_EXPLOSION_COL_A_MAX			(0.016f)								//�����G�t�F�N�g�̃��l���Z�����_���ő�l
#define FIRE_BALL_EXPLOSION_SUBTRACTION_MOVE	(0.9f)									//�����G�t�F�N�g�̈ړ��ʌ��Z����
#define FIRE_BALL_SPARK_SIZE					(1.0f)									//�΂̕��G�t�F�N�g�̃T�C�Y
#define FIRE_BALL_SPARK_EFFECT_NUM				(100)									//�΂̕��G�t�F�N�g�̐�
#define FIRE_BALL_SPARK_EFFECT_COLOR			(D3DXCOLOR(1.0f, 0.8f, 0.0f, 1.0f))		//�΂̕��G�t�F�N�g�̐F
#define FIRE_BALL_SPARK_MOVE_MIN				(2.0f)									//�΂̕��G�t�F�N�g�̏��������_���ŏ��l
#define FIRE_BALL_SPARK_MOVE_MAX				(5.0f)									//�΂̕��G�t�F�N�g�̏��������_���ő�l
#define FIRE_BALL_SPARK_GRAVITY					(-0.5f)									//�΂̕��G�t�F�N�g�̏d��
#define FIRE_BALL_SPARK_COL_A_MIN				(0.007f)								//�΂̕��G�t�F�N�g�̃��l���Z�����_���ŏ��l
#define FIRE_BALL_SPARK_COL_A_MAX				(0.009f)								//�΂̕��G�t�F�N�g�̃��l���Z�����_���ő�l
#define FIRE_BALL_SPARK_SUBTRACTION_MOVE		(0.9f)									//�΂̕��G�t�F�N�g�̈ړ��ʌ��Z����
#define FIRE_BALL_ENEMY_FAT_DAMAGE				(6)										//���^�G�ɗ^����_���[�W
#define FIRE_BALL_ENEMY_FAT_ADD_SP				(3)										//���^�G�ɓ��Ă��Ƃ���SP������
#define FIRE_BALL_ENEMY_BEE_DAMAGE				(8)										//�I�^�G�ɗ^����_���[�W
#define FIRE_BALL_ENEMY_BEE_ADD_SP				(6)										//�I�^�G�ɓ��Ă��Ƃ���SP������
#define FIRE_BALL_ENEMY_BOSS_DAMAGE				(7)										//�{�X�ɗ^����_���[�W
#define FIRE_BALL_ENEMY_BOSS_ADD_SP				(5)										//�{�X�ɓ��Ă��Ƃ���SP������

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CFireBall::CFireBall(int nPriority) :CObject(nPriority)
{
	m_nRotPartitionNum = 0;
	m_nLayer = 0;
	m_nLife = 0;
	m_fPower = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pEffect3D.clear();
	m_bHoming = false;
	m_pTargetEnemy = nullptr;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CFireBall::~CFireBall()
{

}

//================================================
//����������
//================================================
HRESULT CFireBall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::FIRE_BALL);
	
	for (int nCnt = 0; nCnt < m_nLayer; nCnt++)
	{
		for (int nCnt1 = 0; nCnt1 < m_nRotPartitionNum; nCnt1++)
		{
			m_pEffect3D.push_back(CEffect3D::Create(D3DXVECTOR3(pos.x + cosf(D3DX_PI * 2.0f / m_nRotPartitionNum * nCnt1) * pow(m_fPower, nCnt),
																pos.y + sinf(D3DX_PI * 2.0f / m_nRotPartitionNum * nCnt1) * pow(m_fPower, nCnt),
																pos.z),
													D3DXVECTOR3(60.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CEffect3D::EFFECT3D_TYPE::FIRE));

			m_pEffect3D.push_back(CEffect3D::Create(D3DXVECTOR3(pos.x,
																pos.y + sinf(D3DX_PI * 2.0f / m_nRotPartitionNum * nCnt1) * pow(m_fPower, nCnt),
																pos.z + cosf(D3DX_PI * 2.0f / m_nRotPartitionNum * nCnt1) * pow(m_fPower, nCnt)),
													D3DXVECTOR3(60.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CEffect3D::EFFECT3D_TYPE::FIRE));
		}
	}

	//�ϐ�������
	m_pos = pos;
	m_size = size;

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
			//�v���C���[�ɃL���X�g
			CPlayer *pPlayerObj = nullptr;
			pPlayerObj = (CPlayer*)pObject;

			//���b�N�I�����Ă���G���擾
			m_pTargetEnemy = pPlayerObj->GetEnemyNear();
			//���b�N�I�����Ă���Ȃ�
			if (m_pTargetEnemy != nullptr)
			{
				//�ǔ�������
				m_bHoming = true;
			}
		}
		//���̃I�u�W�F�N�g�ɐi�߂�
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}

	//�ʒu�ƃT�C�Y��ݒ�
	SetPos(m_pos);
	SetSize(m_size);

	return S_OK;
}

//================================================
//�I������
//================================================
void CFireBall::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CFireBall::Update(void)
{
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
			//�v���C���[�ɃL���X�g
			CPlayer *pPlayerObj = nullptr;
			pPlayerObj = (CPlayer*)pObject;

			//���b�N�I�����Ă���Ȃ�
			if (m_pTargetEnemy != pPlayerObj->GetEnemyNear())
			{
				//�ǔ�����߂�
				m_bHoming = false;
			}
		}
		//���̃I�u�W�F�N�g�ɐi�߂�
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}

	//���������炷
	m_nLife--;
	//0�ȉ��ɂȂ�����
	if (m_nLife <= 0)
	{
		for (int nCntEffect = 0; nCntEffect < (int)m_pEffect3D.size(); nCntEffect++)
		{
			if (m_pEffect3D[nCntEffect] != nullptr)
			{
				//�G�t�F�N�g������
				m_pEffect3D[nCntEffect]->Uninit();
				m_pEffect3D[nCntEffect] = nullptr;
			}
		}
		Uninit();
		return;
	}

	//�ړ���
	for (int nCntEffect = 0; nCntEffect < (int)m_pEffect3D.size(); nCntEffect++)
	{
		//�ʒu�ƃT�C�Y���擾
		D3DXVECTOR3 posEffect = m_pEffect3D[nCntEffect]->GetPos();
		D3DXVECTOR3 sizeEffect = m_pEffect3D[nCntEffect]->GetSize();


		//�ǔ�����Ȃ�
		if (m_bHoming == true)
		{
			//�G�̈ʒu���擾
			D3DXVECTOR3 enemyPos = m_pTargetEnemy->GetPos();

			//�ړ��ʂ����߂邽�߂̃x�N�g��
			D3DXVECTOR3 moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//�G�̈ʒu���玩�g�̈ʒu�̃x�N�g�������߂�
			moveVec = D3DXVECTOR3(enemyPos.x - posEffect.x, 0.0f, enemyPos.z - posEffect.z);

			//�Z�o�����x�N�g���𐳋K��
			D3DXVec3Normalize(&moveVec, &moveVec);

			//�ړ��ʐݒ�
			m_move = moveVec * MAGIC_FIRE_BALL_MOVE;
		}

		//�ړ��ʂ����Z
		posEffect += m_move;

		//�ʒu��ݒ�
		m_pEffect3D[nCntEffect]->SetPos(posEffect, sizeEffect);
	}
	
	//�ʒu���擾
	m_pos = GetPos();

	//�ړ��ʂ����Z
	m_pos += m_move;

	//�ʒu��ݒ�
	SetPos(m_pos);

	//3D�|���S���Ƃ̓����蔻��
	if (CFloor::Collision(this) == true)
	{
		for (int nCntEffect = 0; nCntEffect < (int)m_pEffect3D.size(); nCntEffect++)
		{
			if (m_pEffect3D[nCntEffect] != nullptr)
			{
				//�G�t�F�N�g������
				m_pEffect3D[nCntEffect]->Uninit();
				m_pEffect3D[nCntEffect] = nullptr;
			}
		}
		Uninit();
		return;
	}

	//���f���Ƃ̓����蔻��
	if (CModelSingle::CollisionAny(this) == true)
	{
		for (int nCntEffect = 0; nCntEffect < (int)m_pEffect3D.size(); nCntEffect++)
		{
			if (m_pEffect3D[nCntEffect] != nullptr)
			{
				//�G�t�F�N�g������
				m_pEffect3D[nCntEffect]->Uninit();
				m_pEffect3D[nCntEffect] = nullptr;
			}
		}
		Uninit();
		return;
	}

	//�I�u�W�F�N�g��������|�C���^
	pObject = nullptr;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	pSaveObject = nullptr;

	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CObject::PRIORITY_ENEMY);

	while (pObject != nullptr)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;

		//�I�u�W�F�N�g�̎�ނ��G��������
		if (pObject->GetObjType() == CObject::OBJTYPE::ENEMY_FAT ||
			pObject->GetObjType() == CObject::OBJTYPE::ENEMY_BEE)
		{
			//�G�ɃL���X�g
			CEnemy *pEnemyObj = nullptr;
			pEnemyObj = (CEnemy*)pObject;

			//�G�Ƃ̓����蔻��
			if (pEnemyObj->CollisionOnly(this, m_size.x / 2.0f) == true)
			{
				//�_���[�W��ԂłȂ��Ȃ�
				if (pEnemyObj->GetMovePattern() != CEnemy::ENEMY_MOVE_PATTERN::DAMAGE)
				{
					//�����G�t�F�N�g�̐���
					CExplosion::Create(m_pos, D3DXVECTOR3(FIRE_BALL_EXPLOSION_SIZE_X, FIRE_BALL_EXPLOSION_SIZE_Y, 0.0f), FIRE_BALL_EXPLOSION_EFFECT_NUM,
						               FIRE_BALL_EXPLOSION_EFFECT_COLOR, FIRE_BALL_EXPLOSION_MOVE_MIN, FIRE_BALL_EXPLOSION_MOVE_MAX,
						               FIRE_BALL_EXPLOSION_GRAVITY, FIRE_BALL_EXPLOSION_COL_A_MIN, FIRE_BALL_EXPLOSION_COL_A_MAX,
						               FIRE_BALL_EXPLOSION_SUBTRACTION_MOVE);

					//�΂̕��G�t�F�N�g�̐���
					CSpark::Create(m_pos, D3DXVECTOR3(FIRE_BALL_SPARK_SIZE, FIRE_BALL_SPARK_SIZE, 0.0f), FIRE_BALL_SPARK_EFFECT_NUM,
						           FIRE_BALL_SPARK_EFFECT_COLOR, FIRE_BALL_SPARK_MOVE_MIN, FIRE_BALL_SPARK_MOVE_MAX, FIRE_BALL_SPARK_GRAVITY,
						           FIRE_BALL_SPARK_COL_A_MIN, FIRE_BALL_SPARK_COL_A_MAX, FIRE_BALL_SPARK_SUBTRACTION_MOVE);

					//�_���[�W��Ԃɂ���
					pEnemyObj->SetMovePattern(CEnemy::ENEMY_MOVE_PATTERN::DAMAGE);
					//�G�̎�ނɂ���ă_���[�W��ς���
					int nDamage = 0;
					switch (pObject->GetObjType())
					{
					case CObject::OBJTYPE::ENEMY_BEE:
						nDamage = FIRE_BALL_ENEMY_BEE_DAMAGE;
						CManager::GetPlayData()->GetSpGauge()->AddGauge(FIRE_BALL_ENEMY_BEE_ADD_SP);
						break;
					case CObject::OBJTYPE::ENEMY_FAT:
						nDamage = FIRE_BALL_ENEMY_FAT_DAMAGE;
						CManager::GetPlayData()->GetSpGauge()->AddGauge(FIRE_BALL_ENEMY_FAT_ADD_SP);
						break;
					default:
						break;
					}
					//HP�����炷
					pEnemyObj->AddLife(-nDamage);
					//HP��0�ȉ��ɂȂ�����
					if (pEnemyObj->GetLife() <= 0)
					{
						switch (pObject->GetObjType())
						{
						case CObject::OBJTYPE::ENEMY_BEE:
							//�X�R�A�𑝂₷
							CManager::GetInstance()->GetPlayData()->GetScorePoint()->AddScore(ENEMY_BEE_UNINIT_SCORE);
							break;
						case CObject::OBJTYPE::ENEMY_FAT:
							//�X�R�A�𑝂₷
							CManager::GetInstance()->GetPlayData()->GetScorePoint()->AddScore(ENEMY_FAT_UNINIT_SCORE);
							break;
						default:
							break;
						}
						//����
						pEnemyObj->Uninit();
					}

					//����
					for (int nCntEffect = 0; nCntEffect < (int)m_pEffect3D.size(); nCntEffect++)
					{
						if (m_pEffect3D[nCntEffect] != nullptr)
						{
							//�G�t�F�N�g������
							m_pEffect3D[nCntEffect]->Uninit();
							m_pEffect3D[nCntEffect] = nullptr;
						}
					}
					Uninit();
					return;
				}
			}
		}
		else if (pObject->GetObjType() == CObject::OBJTYPE::ENEMY_BOSS)
		{
			//�{�X�ɃL���X�g
			CEnemyBoss *pEnemyBossObj = nullptr;
			pEnemyBossObj = (CEnemyBoss*)pObject;

			//�G�Ƃ̓����蔻��
			if (pEnemyBossObj->CollisionOnly(this, m_size.x / 2.0f) == true)
			{
				//�_���[�W��ԂłȂ��Ȃ�
				if (pEnemyBossObj->GetDamage() == false)
				{
					//�����G�t�F�N�g�̐���
					CExplosion::Create(m_pos, D3DXVECTOR3(FIRE_BALL_EXPLOSION_SIZE_X, FIRE_BALL_EXPLOSION_SIZE_Y, 0.0f), FIRE_BALL_EXPLOSION_EFFECT_NUM,
									   FIRE_BALL_EXPLOSION_EFFECT_COLOR, FIRE_BALL_EXPLOSION_MOVE_MIN, FIRE_BALL_EXPLOSION_MOVE_MAX,
									   FIRE_BALL_EXPLOSION_GRAVITY, FIRE_BALL_EXPLOSION_COL_A_MIN, FIRE_BALL_EXPLOSION_COL_A_MAX,
									   FIRE_BALL_EXPLOSION_SUBTRACTION_MOVE);

					//�΂̕��G�t�F�N�g�̐���
					CSpark::Create(m_pos, D3DXVECTOR3(FIRE_BALL_SPARK_SIZE, FIRE_BALL_SPARK_SIZE, 0.0f), FIRE_BALL_SPARK_EFFECT_NUM,
								   FIRE_BALL_SPARK_EFFECT_COLOR, FIRE_BALL_SPARK_MOVE_MIN, FIRE_BALL_SPARK_MOVE_MAX, FIRE_BALL_SPARK_GRAVITY,
								   FIRE_BALL_SPARK_COL_A_MIN, FIRE_BALL_SPARK_COL_A_MAX, FIRE_BALL_SPARK_SUBTRACTION_MOVE);

					//�_���[�W��Ԃɂ���
					pEnemyBossObj->SetDamage(true);
					CManager::GetPlayData()->GetSpGauge()->AddGauge(FIRE_BALL_ENEMY_BOSS_ADD_SP);
					//HP�����炷
					pEnemyBossObj->AddLife(-FIRE_BALL_ENEMY_BOSS_DAMAGE);
					//HP��0�ȉ��ɂȂ�����
					if (pEnemyBossObj->GetLife() <= 0)
					{
						//�X�R�A�𑝂₷
						CManager::GetInstance()->GetPlayData()->GetScorePoint()->AddScore(ENEMY_BOSS_UNINIT_SCORE);

						//�Q�[���N���A�ɂ���
						CManager::GetInstance()->GetPlayData()->SetGameClear(true);

						//����
						pEnemyBossObj->Uninit();
					}

					//����
					for (int nCntEffect = 0; nCntEffect < (int)m_pEffect3D.size(); nCntEffect++)
					{
						if (m_pEffect3D[nCntEffect] != nullptr)
						{
							//�G�t�F�N�g������
							m_pEffect3D[nCntEffect]->Uninit();
							m_pEffect3D[nCntEffect] = nullptr;
						}
					}
					Uninit();
					return;
				}
			}
		}
		//���̃I�u�W�F�N�g�ɐi�߂�
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//================================================
//�`�揈��
//================================================
void CFireBall::Draw(void)
{
	
}

//================================================
//��������
//================================================
CFireBall* CFireBall::Create(D3DXVECTOR3 pos, int nRotPartitionNum, int nLayer, int nLife, float fPower, D3DXVECTOR3 move, D3DXVECTOR3 size)
{
	//�C���X�^���X�̐���
	CFireBall *pFireBall = nullptr;
	if (pFireBall == nullptr)
	{
		pFireBall = new CFireBall();
		if (pFireBall != nullptr)
		{
			pFireBall->m_nRotPartitionNum = nRotPartitionNum;
			pFireBall->m_nLayer = nLayer;
			pFireBall->m_nLife = nLife;
			pFireBall->m_fPower = fPower;
			pFireBall->m_move = move;
			pFireBall->Init(pos, size);
		}
	}
	return pFireBall;
}
