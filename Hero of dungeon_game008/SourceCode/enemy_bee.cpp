//================================================
//�G(�I)�̏���
//Author:KatoMizuki
//================================================
#include "manager.h"
#include "enemy_bee.h"
#include "motion_enemy_bee.h"
#include "renderer.h"
#include "floor.h"
#include "model.h"
#include "model_single.h"
#include "x_load.h"
#include "player.h"
#include "bullet_enemy.h"
#include "mesh_trajectory.h"
#include "play_data.h"
#include "gauge.h"
#include "effect3D.h"
#include "spark.h"
#include "magic_thunder.h"
#include "exclamation_mark.h"
#include "shadow.h"
#include "score.h"

//================================================
//�}�N����`
//================================================
#define ENEMY_BEE_GRAVITY							(0.2f)		//�d�͂̑傫��
#define ENEMY_BEE_SIZE_ADJUSTMENT					(90.0f)		//�T�C�Y�����l
#define ENEMY_BEE_FLY_COUNTER						(90)		//��s���̏㉺�ړ��J�E���^�[
#define ENEMY_BEE_FLY_ADD_SPEED						(0.02f)		//��s���̏㉺�ړ��ʉ����l
#define ENEMY_BEE_FLY_MAX_SPEED						(0.4f)		//��s���̏㉺�ړ��ʏ���l
#define ENEMY_BEE_MOVE_SPEED						(4.0f)		//�ʏ�ړ��̈ړ���
#define ENEMY_BEE_DAMAGE_MOVE_SPEED					(1.0f)		//�_���[�W��Ԃ̈ړ���
#define ENEMY_BEE_ATTACK_DIFFER						(400.0f)	//�U�������Ă���͈�
#define ENEMY_BEE_MOVE_TO_PLAYER_MAX_DIFFER			(600.0f)	//�ǂ������Ă���͈�
#define ENEMY_BEE_LIFE								(30)		//���C�t
#define ENEMY_BEE_HIT_EFFECT_SIZE					(40.0f)		//�q�b�g�G�t�F�N�g�̑傫��
#define ENEMY_BEE_HIT_EFFECT_POS_Y					(10.0f)		//�q�b�g�G�t�F�N�g�̈ʒu����Y
#define ENEMY_BEE_HIT_EFFECT_POS_XZ					(20.0f)		//�q�b�g�G�t�F�N�g�̈ʒu����XZ
#define ENEMY_BEE_HIT_ADD_SP						(3)			//�q�b�g��������SP������
#define ENEMY_BEE_HIT_ADD_MP						(14)		//�q�b�g��������MP������
#define ENEMY_BEE_HIT_DAMAGE						(3)			//�q�b�g�������_���[�W
#define ENEMY_BEE_EXCLAMATION_MARK_POS				(180.0f)	//�r�b�N���}�[�N�̈ʒu�����l

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CEnemyBee::CEnemyBee(int nPriority):CEnemy(nPriority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_pModel = nullptr;
	m_nFlyMoveCounter = 0;
	m_pMotionEnemyBee = nullptr;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CEnemyBee::~CEnemyBee()
{

}

//================================================
//����������
//================================================
HRESULT CEnemyBee::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_posOld = pos;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_bNotice = false;
	m_nFlyMoveCounter = 0;
	m_movePattern = ENEMY_MOVE_PATTERN::STOP;
	m_nLife = ENEMY_BEE_LIFE;

	//�ʒu�̐ݒ�
	SetPos(m_pos);
	SetPosOld(m_posOld);

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CEnemy::OBJTYPE::ENEMY_BEE);

	//���f���̐���
	m_pModel = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_rot, CManager::GetInstance()->GetXload()->GetType(CXload::X_TYPE_BEE));

	//���[�V�����̐���
	m_pMotionEnemyBee = CMotionEnemyBee::Create(this);
	m_pMotionEnemyBee->SetMotion(CMotionRoad::MOTION_ENEMY_BEE_TYPE_NEUTRAL, this);

	//�T�C�Y���擾
	D3DXVECTOR3 modelSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	modelSize = m_pModel->GetSize();

	//�T�C�Y��X��Z���ׂđ傫���ق���X��Z���ꂼ��Ɋ��蓖�Ă�
	if (modelSize.x >= modelSize.z)
	{
		m_size = D3DXVECTOR3(modelSize.x - ENEMY_BEE_SIZE_ADJUSTMENT, modelSize.y, modelSize.x - ENEMY_BEE_SIZE_ADJUSTMENT);
	}
	else
	{
		m_size = D3DXVECTOR3(modelSize.z - ENEMY_BEE_SIZE_ADJUSTMENT, modelSize.y, modelSize.z - ENEMY_BEE_SIZE_ADJUSTMENT);
	}

	//�T�C�Y�̐ݒ�
	SetSize(m_size);

	//�e�̐ݒ�
	m_pShadow = CShadow::Create(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z), D3DXVECTOR3(m_size.x, 0.0f, m_size.z), this);

	return S_OK;
}

//================================================
//�I������
//================================================
void CEnemyBee::Uninit(void)
{
	CEnemy::Uninit();
}

//================================================
//�X�V����
//================================================
void CEnemyBee::Update(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	m_pos = pos;
	m_posOld = pos;

	//1�t���[���O�̈ʒu�ݒ�
	SetPosOld(m_posOld);

	//�ړ�����
	Move();

	//�ړ��p�^�[������
	MoveType();

	m_pos += m_move;		//�ړ��ʔ��f

	//���[�V����
	m_pMotionEnemyBee->Update(this);

	//��]�̊���
	Rotate();

	//�ʒu���f
	SetPos(m_pos);

	//�v���C���[�Ƃ̓����蔻��
	CPlayer::Collision(this, m_size.x / 2.0f);

	//�G�Ƃ̓����蔻��
	Collision(this, m_size.x / 2.0f);

	//�a���̓����蔻��
	if (CollisionSlash() == true)
	{
		return;
	}

	//�����@�̓����蔻��
	if (CollisionMagicThunder() == true)
	{
		return;
	}

	//3D�|���S���̏��Ƃ̓����蔻��
	if (CFloor::Collision(this) == true)
	{
		m_move.y = 0.0f;
		m_move.y -= 40.0f;
	}

	//���f���Ƃ̓����蔻��
	if (CModelSingle::Collision(this) == true)
	{
		m_move.y = 0.0f;
		m_move.y -= 40.0f;
	}

	//�ʒu�擾
	pos = GetPos();
	m_pos = pos;
}

//================================================
//�`�揈��
//================================================
void CEnemyBee::Draw(void)
{
	CEnemy::Draw();

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

			//���߂�����������̐��l�ȉ���������
			if (fRadius <= ENEMY_DRAW_DIFFER)
			{
				//�`�悳��Ă����Ԃɂ���
				m_bDraw = true;
				//���f���̕`��
				m_pModel->Draw();
			}
			else
			{
				//�`�悳��Ă��Ȃ���Ԃɂ���
				m_bDraw = false;
				
				//�e��`�悵�Ȃ��悤�ɂ���
				m_pShadow->SetDraw(false);

				//�v���C���[�ɃL���X�g
				CPlayer *pPlayerObj = nullptr;
				pPlayerObj = (CPlayer*)pObject;

				//���b�N�I�����Ă���Ȃ�
				if (pPlayerObj->GetEnemyNear() == this)
				{
					//null�ɂ���
					pPlayerObj->SetEnemyNear(nullptr);
				}
			}
		}
		//���̃I�u�W�F�N�g�ɐi�߂�
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//================================================
//��������
//================================================
CEnemyBee *CEnemyBee::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�C���X�^���X�̐���
	CEnemyBee *pEnemyBee = nullptr;
	if (pEnemyBee == nullptr)
	{
		pEnemyBee = new CEnemyBee;
		if (pEnemyBee != nullptr)
		{
			pEnemyBee->m_rot = rot;
			pEnemyBee->Init(pos, pEnemyBee->m_size);
		}
	}
	return pEnemyBee;
}

//================================================
//���f���̓�������
//================================================
void CEnemyBee::Move(void)
{
	//��s���̏㉺�ړ��̉����ʕۑ��p�ϐ�
	float fFlySpeed = 0.0f;

	//�J�E���^�[���K��l��菭�Ȃ��Ƃ�
	if (m_nFlyMoveCounter < ENEMY_BEE_FLY_COUNTER)
	{
		fFlySpeed = ENEMY_BEE_FLY_ADD_SPEED;
	}
	else
	{
		fFlySpeed = -ENEMY_BEE_FLY_ADD_SPEED;
	}

	//�ړ��ʂ����Z
	m_move.y += fFlySpeed;

	//�ړ��ʂ��K��l���傫���Ȃ�����
	if (m_move.y >= ENEMY_BEE_FLY_MAX_SPEED)
	{
		//�K��l�ɂ���
		m_move.y = ENEMY_BEE_FLY_MAX_SPEED;
	}
	else if (m_move.y <= -ENEMY_BEE_FLY_MAX_SPEED)
	{
		//�K��l�ɂ���
		m_move.y = -ENEMY_BEE_FLY_MAX_SPEED;
	}

	//�J�E���^�[�����Z
	m_nFlyMoveCounter++;

	//�J�E���^�[���K��l��肨�������Ȃ�����
	if (m_nFlyMoveCounter >= ENEMY_BEE_FLY_COUNTER * 2)
	{
		//0�ɂ���
		m_nFlyMoveCounter = 0;
	}
}

//================================================
//���f���̈ʒu�ݒ菈��
//================================================
void CEnemyBee::SetModelPos(D3DXVECTOR3 pos)
{
	m_pModel->SetPos(pos);
}

//================================================
//���f���̈ʒu�擾����
//================================================
D3DXVECTOR3 CEnemyBee::GetModelPos(void)
{
	return m_pModel->GetPos();
}

//================================================
//���f���̌����ݒ菈��
//================================================
void CEnemyBee::SetModelRot(D3DXVECTOR3 rot)
{
	m_pModel->SetRot(rot);
}

//================================================
//���f���̌����擾����
//================================================
D3DXVECTOR3 CEnemyBee::GetModelRot(void)
{
	return m_pModel->GetRot();
}

//================================================
//�����Ɋւ��鏈��
//================================================
void CEnemyBee::MoveType(void)
{
	//�I�u�W�F�N�g��������|�C���^
	CObject *pObject = nullptr;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CObject *pSaveObject = nullptr;
	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CObject::PRIORITY_PLAYER);
	//�v���C���[�Ƃ̊p�x�ۑ��p�ϐ�
	float fRot = 0.0f;

	while (pObject != nullptr)
	{
		//���݂̎��̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;

		//�I�u�W�F�N�g�̎�ނ��v���C���[��������
		if (pObject->GetObjType() == CObject::OBJTYPE::PLAYER)
		{
			//�I�u�W�F�N�g�̈ʒu���擾
			D3DXVECTOR3 posObj = pObject->GetPos();

			//�v���C���[���玩�g�܂ł̂̋��������߂�
			float fRadius = sqrtf((posObj.x - m_pos.x) * (posObj.x - m_pos.x) + (posObj.z - m_pos.z) * (posObj.z - m_pos.z));

			//�v���C���[�Ǝ��g�̋���������̋����͈͓̔����A�_���[�W���󂯂Ă����ԂłȂ��Ƃ�
			if (fRadius <= ENEMY_BEE_MOVE_TO_PLAYER_MAX_DIFFER && fRadius > ENEMY_BEE_ATTACK_DIFFER && m_movePattern != ENEMY_MOVE_PATTERN::DAMAGE)
			{
				//�v���C���[�Ɍ������ē����悤�ɂ���
				m_movePattern = ENEMY_MOVE_PATTERN::MOVE_TO_PLAYER;

				//�v���C���[�ɋC�Â��Ă��Ȃ��Ȃ�
				if (m_bNotice == false)
				{
					//�C�Â�����
					m_bNotice = true;
					//�r�b�N���}�[�N���o��
					CExclamationMark::Create(D3DXVECTOR3(m_pos.x, m_pos.y + ENEMY_BEE_EXCLAMATION_MARK_POS, m_pos.z),
						                     D3DXVECTOR3(ENEMY_EXCLAMATION_MARK_SIZE, ENEMY_EXCLAMATION_MARK_SIZE, 0.0f),
						                     D3DXVECTOR3(ENEMY_EXCLAMATION_MARK_SIZE, 0.1f, 0.0f),
						                     D3DXVECTOR3(0.0f, ENEMY_EXCLAMATION_MARK_ADD_SIZE, 0.0f),
						                     this, ENEMY_EXCLAMATION_MARK_LIFE);

				}
			}
			else if (fRadius <= ENEMY_BEE_ATTACK_DIFFER && m_movePattern != ENEMY_MOVE_PATTERN::DAMAGE)
			{//�v���C���[�Ǝ��g�̋���������̋������Z�������犎�A�_���[�W���󂯂Ă����ԂłȂ��Ƃ�
				//�U������
				m_movePattern = ENEMY_MOVE_PATTERN::ATTACK;
			}
			else if (fRadius > ENEMY_BEE_MOVE_TO_PLAYER_MAX_DIFFER &&
					m_movePattern == ENEMY_MOVE_PATTERN::MOVE_TO_PLAYER)
			{//�v���C���[�Ǝ��g�̋���������̋�����蒷���Ȃ�s���p�^�[�����v���C���[�Ɍ������ē����Ă����Ԃ̂Ƃ�
				//��~������
				m_movePattern = ENEMY_MOVE_PATTERN::STOP;

				//�v���C���[�ɋC�Â��Ă��Ȃ�
				if (m_bNotice == true)
				{
					//�C�Â��Ă��Ȃ���Ԃɂ���
					m_bNotice = false;
				}
			}

			//�v���C���[�ƑΏۂ̃I�u�W�F�N�g�̊p�x�����߂�
			fRot = atan2((posObj.x - m_pos.x), (posObj.z - m_pos.z)) - D3DX_PI;
		}
		//���̃I�u�W�F�N�g�ɐi�߂�
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}


	//�����̎�ނɂ���ď�����ς���
	switch (m_movePattern)
	{
	case ENEMY_MOVE_PATTERN::MOVE:				//�ړ�
		//�ړ��ʂ�ݒ�
		m_move.z = -cosf(m_rot.y) * ENEMY_BEE_MOVE_SPEED;
		m_move.x = -sinf(m_rot.y) * ENEMY_BEE_MOVE_SPEED;

		//�J�E���^�[�����Z
		m_nMoveCounter++;
		//�K��l���傫���Ȃ�����
		if (m_nMoveCounter >= ENEMY_MOVE_MAX_COUNT)
		{
			//0�ɖ߂�
			m_nMoveCounter = 0;
			//��~��Ԃɂ���
			m_movePattern = ENEMY_MOVE_PATTERN::STOP;
		}
		break;
	case ENEMY_MOVE_PATTERN::STOP:				//��~
		//�ړ��ʂ�0�ɂ���
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		//�J�E���^�[�����Z
		m_nStopCounter++;
		//�K��l���傫���Ȃ�����
		if (m_nStopCounter >= ENEMY_STOP_MAX_COUNT)
		{
			//0�ɖ߂�
			m_nStopCounter = 0;
			//��]��Ԃɂ���
			m_movePattern = ENEMY_MOVE_PATTERN::TURN;
			//�ړI�̕�����ݒ肷��
			m_fObjectiveRot = ENEMY_TURN_RAND;
			//��]��������
			m_bRotate = true;
		}
		break;
	case ENEMY_MOVE_PATTERN::TURN:				//��]
		//��]���I�������
		if (m_bRotate == false)
		{
			//�ړ���Ԃɂ���
			m_movePattern = ENEMY_MOVE_PATTERN::MOVE;
		}
		break;
	case ENEMY_MOVE_PATTERN::MOVE_TO_PLAYER:	//�v���C���[�̂ق��Ɍ������Ĉړ�
		//�ړ��ʂ�ݒ�
		m_move.z = -cosf(fRot) * ENEMY_BEE_MOVE_SPEED;
		m_move.x = -sinf(fRot) * ENEMY_BEE_MOVE_SPEED;

		//�ړI�̕�����ݒ肷��
		m_fObjectiveRot = fRot;
		//��]��������
		m_bRotate = true;
		break;
	case ENEMY_MOVE_PATTERN::ATTACK:			//�U��
		//�ړ��ʂ�0�ɂ���
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		//�J�E���^�[�����Z
		m_nAttackCounter++;
		//�K��l���傫���Ȃ�����
		if (m_nAttackCounter >= ENEMY_ATTACK_STOP_MAX_COUNT)
		{
			//0�ɖ߂�
			m_nAttackCounter = 0;
			//�e���o���čU������
			CBulletEnemy::Create(m_pos, D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		}
		else
		{
			//�ړI�̕�����ݒ肷��
			m_fObjectiveRot = fRot;
			//��]��������
			m_bRotate = true;
		}
		break;
	case ENEMY_MOVE_PATTERN::DAMAGE:			//��_���[�W
		//�J�E���^�[�����Z
		m_nDamageCounter++;

		//�K��l�����J�E���^�[���傫���Ȃ�����
		if (m_nDamageCounter >= ENEMY_DAMAGE_MAX_COUNT)
		{
			//�J�E���^�[��߂�
			m_nDamageCounter = 0;
			//��~������
			m_movePattern = ENEMY_MOVE_PATTERN::STOP;
			//�j���[�g�������[�V�����ɂ���
			m_pMotionEnemyBee->SetMotion(CMotionRoad::MOTION_ENEMY_BEE_TYPE_NEUTRAL, this);
		}
		else
		{
			//�v���C���[�Ɣ��΂̕��Ƀm�b�N�o�b�N������
			m_move.z = cosf(fRot) * ENEMY_BEE_DAMAGE_MOVE_SPEED;
			m_move.x = sinf(fRot) * ENEMY_BEE_DAMAGE_MOVE_SPEED;

			//��_���[�W���[�V��������Ȃ�������
			if (m_pMotionEnemyBee->GetMotion() != CMotionRoad::MOTION_ENEMY_BEE_TYPE_DAMAGE)
			{
				//�_���[�W���[�V�����ɂ���
				m_pMotionEnemyBee->SetMotion(CMotionRoad::MOTION_ENEMY_BEE_TYPE_DAMAGE, this);
			}
		}
		break;
	default:
		break;
	}
}

//================================================
//�a���̓����蔻��
//================================================
bool CEnemyBee::CollisionSlash(void)
{
	//���̋O�ՂƂ̓����蔻��
	if (CMeshTrajectory::CollisionSphere(this, m_size.x / 3.0f) == true && m_movePattern != ENEMY_MOVE_PATTERN::DAMAGE)
	{//�_���[�W���󂯂Ă��Ȃ��čU�����[�V�����ł͂Ȃ�������

		//�J�����̃|�C���^�z��1�Ԗڂ̃A�h���X�擾
		CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
		//camera�̎擾
		CCamera* pCamera = &**pCameraAddress;
		//�J�����̌����擾
		D3DXVECTOR3 rotCamera = pCamera->GetRotV();

		//�q�b�g�G�t�F�N�g���o��
		CEffect3D::Create(D3DXVECTOR3(m_pos.x + sinf(rotCamera.y) * ENEMY_BEE_HIT_EFFECT_POS_XZ, m_pos.y + ENEMY_BEE_HIT_EFFECT_POS_Y,
			              m_pos.z + cosf(rotCamera.y) * ENEMY_BEE_HIT_EFFECT_POS_XZ),
			              D3DXVECTOR3(ENEMY_BEE_HIT_EFFECT_SIZE, ENEMY_BEE_HIT_EFFECT_SIZE, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			              CEffect3D::EFFECT3D_TYPE::HIT);

		//�΂̕��G�t�F�N�g�̐���
		CSpark::Create(D3DXVECTOR3(m_pos.x + sinf(rotCamera.y) * ENEMY_BEE_HIT_EFFECT_POS_XZ, m_pos.y + ENEMY_BEE_HIT_EFFECT_POS_Y,
			                       m_pos.z + cosf(rotCamera.y) * ENEMY_BEE_HIT_EFFECT_POS_XZ),
			           D3DXVECTOR3(ENEMY_SPARK_SIZE, ENEMY_SPARK_SIZE, 0.0f), ENEMY_SPARK_EFFECT_NUM,
			           ENEMY_SPARK_EFFECT_COLOR, ENEMY_SPARK_MOVE_MIN, ENEMY_SPARK_MOVE_MAX, ENEMY_SPARK_GRAVITY,
			           ENEMY_SPARK_COL_A_MIN, ENEMY_SPARK_COL_A_MAX, ENEMY_SPARK_SUBTRACTION_MOVE);

		//SP�Q�[�W�𑝂₷
		CManager::GetInstance()->GetPlayData()->GetSpGauge()->AddGauge(ENEMY_BEE_HIT_ADD_SP);
		//MP�Q�[�W�𑝂₷
		CManager::GetInstance()->GetPlayData()->GetMpGauge()->AddGauge(ENEMY_BEE_HIT_ADD_MP);

		//���C�t�����炷
		m_nLife -= ENEMY_BEE_HIT_DAMAGE;
		//���C�t��0�ɂȂ�����
		if (m_nLife <= 0)
		{
			//�X�R�A�𑝂₷
			CManager::GetInstance()->GetPlayData()->GetScorePoint()->AddScore(ENEMY_BEE_UNINIT_SCORE);

			//����
			Uninit();
			return true;
		}
		//�_���[�W���󂯂��Ƃ��̃p�^�[���ɂ���
		m_movePattern = ENEMY_MOVE_PATTERN::DAMAGE;
	}
	return false;
}

//================================================
//�����@�̓����蔻��
//================================================
bool CEnemyBee::CollisionMagicThunder(void)
{
	if (CMagicThunder::Collision(this) == true)
	{
		//�_���[�W��ԂłȂ��Ȃ�
		if (m_movePattern != ENEMY_MOVE_PATTERN::DAMAGE)
		{
			//�_���[�W��Ԃɂ���
			m_movePattern = ENEMY_MOVE_PATTERN::DAMAGE;

			//HP�����炷
			m_nLife -= MAGIC_THUNDER_EFFECT_ENEMY_BEE_DAMAGE;

			//�J�����̃|�C���^�z��1�Ԗڂ̃A�h���X�擾
			CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
			//camera�̎擾
			CCamera* pCamera = &**pCameraAddress;
			//�J�����̌����擾
			D3DXVECTOR3 rotCamera = pCamera->GetRotV();

			//�q�b�g�G�t�F�N�g���o��
			CEffect3D::Create(D3DXVECTOR3(m_pos.x + sinf(rotCamera.y) * ENEMY_BEE_HIT_EFFECT_POS_XZ, m_pos.y + ENEMY_BEE_HIT_EFFECT_POS_Y,
				              m_pos.z + cosf(rotCamera.y) * ENEMY_BEE_HIT_EFFECT_POS_XZ),
				              D3DXVECTOR3(ENEMY_BEE_HIT_EFFECT_SIZE, ENEMY_BEE_HIT_EFFECT_SIZE, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				              CEffect3D::EFFECT3D_TYPE::HIT);

			//�΂̕��G�t�F�N�g�̐���
			CSpark::Create(D3DXVECTOR3(m_pos.x + sinf(rotCamera.y) * ENEMY_BEE_HIT_EFFECT_POS_XZ, m_pos.y + ENEMY_BEE_HIT_EFFECT_POS_Y,
				                       m_pos.z + cosf(rotCamera.y) * ENEMY_BEE_HIT_EFFECT_POS_XZ),
				           D3DXVECTOR3(ENEMY_SPARK_SIZE, ENEMY_SPARK_SIZE, 0.0f), ENEMY_SPARK_EFFECT_NUM,
				           ENEMY_SPARK_EFFECT_COLOR, ENEMY_SPARK_MOVE_MIN, ENEMY_SPARK_MOVE_MAX, ENEMY_SPARK_GRAVITY,
				           ENEMY_SPARK_COL_A_MIN, ENEMY_SPARK_COL_A_MAX, ENEMY_SPARK_SUBTRACTION_MOVE);

			//HP��0�ȉ��ɂȂ�����
			if (m_nLife <= 0)
			{
				//�X�R�A�𑝂₷
				CManager::GetInstance()->GetPlayData()->GetScorePoint()->AddScore(ENEMY_BEE_UNINIT_SCORE);

				//����
				Uninit();
				return true;
			}
		}
	}
	return false;
}
