//================================================
//���^�G�̏���
//Author:KatoMizuki
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "manager.h"
#include "enemy_fat.h"
#include "motion_enemy_fat.h"
#include "renderer.h"
#include "floor.h"
#include "model.h"
#include "model_single.h"
#include "x_load.h"
#include "player.h"
#include "mesh_trajectory.h"
#include "effect3D.h"
#include "play_data.h"
#include "gauge.h"
#include "meshfield.h"
#include "spark.h"
#include "magic_thunder.h"
#include "guard_effect.h"
#include "texture.h"
#include "exclamation_mark.h"
#include "shadow.h"
#include "score.h"
#include "sound.h"

//================================================
//�}�N����`
//================================================
#define ENEMY_FAT_SIZE_ADJUSTMENT				(30.0f)				//�T�C�Y�����l
#define ENEMY_FAT_GRAVITY						(0.2f)				//�d�͂̑傫��
#define ENEMY_FAT_MOVE_SPEED					(4.0f)				//�ʏ�ړ��̈ړ���
#define ENEMY_FAT_DAMAGE_MOVE_SPEED				(1.0f)				//�_���[�W���󂯂��Ƃ��̈ړ���
#define ENEMY_FAT_ATTACK_COLLISION_RADIUS		(40.0f)				//�U�����̓����蔻��̔��a
#define ENEMY_FAT_ATTACK_COLLISION_OFFSET		(50.0f)				//�U�����̓����蔻��̈ʒu(�e�Ƃ̃I�t�Z�b�g)
#define ENEMY_FAT_LIFE							(40)				//���C�t
#define ENEMY_FAT_HIT_EFFECT_SIZE				(40.0f)				//�q�b�g�G�t�F�N�g�̑傫��
#define ENEMY_FAT_HIT_EFFECT_POS_Y				(40.0f)				//�q�b�g�G�t�F�N�g�̈ʒu����Y
#define ENEMY_FAT_HIT_EFFECT_POS_XZ				(20.0f)				//�q�b�g�G�t�F�N�g�̈ʒu����XZ
#define ENEMY_FAT_HIT_ADD_SP					(6)					//�q�b�g��������SP������
#define ENEMY_FAT_GUARD_ADD_SP					(2)					//�K�[�h��������SP������
#define ENEMY_FAT_HIT_ADD_MP					(14)				//�q�b�g��������MP������
#define ENEMY_FAT_HIT_DAMAGE					(8)					//�q�b�g�������̃_���[�W��
#define ENEMY_FAT_EXCLAMATION_MARK_POS			(120.0f)			//�r�b�N���}�[�N�̈ʒu�����l

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CEnemyFat::CEnemyFat(int nPriority) :CEnemy(nPriority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_bAttackColl = false;
	m_pParent = nullptr;
	memset(&m_apModel, NULL, sizeof(m_apModel));
	m_pMotionEnemyFat = nullptr;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CEnemyFat::~CEnemyFat()
{

}

//================================================
//����������
//================================================
HRESULT CEnemyFat::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_posOld = pos;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_bAttackColl = true;
	m_bNotice = false;
	m_movePattern = ENEMY_MOVE_PATTERN::STOP;
	m_nStopCounter = 0;
	m_nAttackCounter = 0;
	m_nDamageCounter = 0;
	m_nLife = ENEMY_FAT_LIFE;

	//���f���̐���
	//text�t�@�C���ǂݍ���
	FILE *pFile = fopen("data/MOTION/motion_enemy_fat.txt", "r");
	if (pFile != nullptr)
	{
		char cString[128];
		//��s���ۑ�
		while (fgets(cString, 128, pFile) != nullptr)
		{
			//�������ۑ�
			fscanf(pFile, "%s", cString);
			//������̒���PARTSSET����������
			if (strncmp("PARTSSET", cString, 9) == 0)
			{
				fscanf(pFile, "%*s%*s");

				//�C���f�b�N�X�ǂݍ���
				int nIndex = 0;
				fscanf(pFile, "%*s%*s%d", &nIndex);

				//�e�ǂݍ���
				int nParent = 0;
				fscanf(pFile, "%*s%*s%d", &nParent);
				fscanf(pFile, "%*s%*s");

				//�ʒu�ǂݍ���
				D3DXVECTOR3 modelPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				fscanf(pFile, "%*s%*s%f%f%f", &modelPos.x, &modelPos.y, &modelPos.z);

				//�����ǂݍ���
				D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				fscanf(pFile, "%*s%*s%f%f%f", &rot.x, &rot.y, &rot.z);

				//���f������
				int nModelType = 0;
				nModelType = CXload::X_TYPE_ENEMY_FAT_BODY;
				m_apModel[nIndex] = CModel::Create(modelPos, rot, CManager::GetInstance()->GetXload()->GetType(nModelType + nIndex));

				//�e�̐ݒ�
				if (nParent == -1)
				{
					m_apModel[nIndex]->SetParent(nullptr);
				}
				else
				{
					m_apModel[nIndex]->SetParent(m_apModel[nParent]);
				}

				if (nIndex == MAX_ENEMY_FAT_MODEL - 1)
				{
					break;
				}
			}
		}
	}
	else
	{
		printf("�t�@�C�����J���܂���ł���\n");
	}
	fclose(pFile);

	//�ʒu�̐ݒ�
	SetPos(m_pos);
	SetPosOld(m_posOld);

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CObject::OBJTYPE::ENEMY_FAT);

	//���[�V�����̐���
	m_pMotionEnemyFat = CMotionEnemyFat::Create(this);
	m_pMotionEnemyFat->SetMotion(CMotionRoad::MOTION_ENEMY_FAT_TYPE_NEUTRAL, this);
	
	//�T�C�Y���擾
	D3DXVECTOR3 modelSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	modelSize = m_apModel[0]->GetSize();

	//�T�C�Y��X��Z���ׂđ傫���ق���X��Z���ꂼ��Ɋ��蓖�Ă�
	if (modelSize.x >= modelSize.z)
	{
		m_size = D3DXVECTOR3(modelSize.x + ENEMY_FAT_SIZE_ADJUSTMENT, modelSize.y, modelSize.x + ENEMY_FAT_SIZE_ADJUSTMENT);
	}
	else
	{
		m_size = D3DXVECTOR3(modelSize.z + ENEMY_FAT_SIZE_ADJUSTMENT, modelSize.y, modelSize.z + ENEMY_FAT_SIZE_ADJUSTMENT);
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
void CEnemyFat::Uninit(void)
{
	CEnemy::Uninit();
	Release();
}

//================================================
//�X�V����
//================================================
void CEnemyFat::Update(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	m_pos = pos;
	m_posOld = pos;

	//1�t���[���O�̈ʒu�ݒ�
	SetPosOld(m_posOld);

	//�d��
	m_move.y -= ENEMY_GRAVITY;

	//�ړ�����
	MoveType();

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

	//�ړ��ʔ��f
	m_pos += m_move;		

	//���[�V����
	m_pMotionEnemyFat->Update(this);

	//��]�̊���
	Rotate();

	//�ʒu���f
	SetPos(m_pos);

	//�v���C���[�Ƃ̓����蔻��
	CPlayer::Collision(this, m_size.x / 2.0f);

	//�G�Ƃ̓����蔻��
	Collision(this, m_size.x / 2.0f);

	//�v���C���[�ւ̍U���̓����蔻��			
	ToPlayerAttackCollision();

	//3D�|���S���Ƃ̓����蔻��
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
void CEnemyFat::Draw(void)
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
				for (int nCntModel = 0; nCntModel < MAX_ENEMY_FAT_MODEL; nCntModel++)
				{
					m_apModel[nCntModel]->Draw();
				}
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

	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;			//�v�Z�p�}�g���b�N�X

	//�U������ۂ̓����蔻��̈ʒu�ݒ�
	for (int nCntMtx = 0; nCntMtx < ENEMY_FAT_MAX_ATTACK_COLLISION; nCntMtx++)
	{
		D3DXMATRIX mtx;									//�v�Z�p�}�g���b�N�X
		D3DXMatrixIdentity(&m_aAttackCollMtx[nCntMtx]);	//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtx);						//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxTrans);					//���[���h�}�g���b�N�X�̏�����

		//�I�t�Z�b�g
		float fOffset = 0.0f;
		
		switch (nCntMtx)
		{
		case 0:
			fOffset = -ENEMY_FAT_ATTACK_COLLISION_OFFSET;
			break;
		case 1:
			fOffset = ENEMY_FAT_ATTACK_COLLISION_OFFSET;
			break;
		default:
			break;
		}
		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, fOffset, 0.0f, 0.0f);
		D3DXMatrixMultiply(&m_aAttackCollMtx[nCntMtx], &m_aAttackCollMtx[nCntMtx], &mtxTrans);

		//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&m_aAttackCollMtx[nCntMtx], &m_aAttackCollMtx[nCntMtx], m_apModel[2 + nCntMtx]->GetMtxPoint());

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_aAttackCollMtx[nCntMtx]);
	}
}

//================================================
//��������
//================================================
CEnemyFat *CEnemyFat::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�C���X�^���X�̐���
	CEnemyFat *pEnemyFat = nullptr;
	if (pEnemyFat == nullptr)
	{
		pEnemyFat = new CEnemyFat;
		if (pEnemyFat != nullptr)
		{
			pEnemyFat->m_rot = rot;
			pEnemyFat->Init(pos, pEnemyFat->m_size);
		}
	}
	return pEnemyFat;
}

//================================================
//���f���̈ʒu�ݒ菈��
//================================================
void CEnemyFat::SetModelPos(int nCntModel, D3DXVECTOR3 pos)
{
	m_apModel[nCntModel]->SetPos(pos);
}

//================================================
//���f���̈ʒu�擾����
//================================================
D3DXVECTOR3 CEnemyFat::GetModelPos(int nCntModel)
{
	return m_apModel[nCntModel]->GetPos();
}

//================================================
//���f���̌����ݒ菈��
//================================================
void CEnemyFat::SetModelRot(int nCntModel, D3DXVECTOR3 rot)
{
	m_apModel[nCntModel]->SetRot(rot);
}

//================================================
//���f���̌����擾����
//================================================
D3DXVECTOR3 CEnemyFat::GetModelRot(int nCntModel)
{
	return m_apModel[nCntModel]->GetRot();
}

//================================================
//�����Ɋւ��鏈��
//================================================
void CEnemyFat::MoveType(void)
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

			//�v���C���[�Ǝ��g�̋���������̋����͈͓̔����A���[�V�������U���ł͂Ȃ��A�_���[�W���󂯂Ă����ԂłȂ��Ƃ�
			if (fRadius <= ENEMY_MOVE_TO_PLAYER_MAX_DIFFER && fRadius > ENEMY_ATTACK_DIFFER &&
				m_pMotionEnemyFat->GetMotion() != CMotionRoad::MOTION_ENEMY_FAT_TYPE_ATTACK_01 && m_movePattern != ENEMY_MOVE_PATTERN::DAMAGE)
			{
				//�v���C���[�Ɍ������ē����悤�ɂ���
				m_movePattern = ENEMY_MOVE_PATTERN::MOVE_TO_PLAYER;

				//�v���C���[�ɋC�Â��Ă��Ȃ��Ȃ�
				if (m_bNotice == false)
				{
					//�C�Â�����
					m_bNotice = true;
					//�r�b�N���}�[�N���o��
					CExclamationMark::Create(D3DXVECTOR3(m_pos.x, m_pos.y + ENEMY_FAT_EXCLAMATION_MARK_POS, m_pos.z),
						                     D3DXVECTOR3(ENEMY_EXCLAMATION_MARK_SIZE, ENEMY_EXCLAMATION_MARK_SIZE, 0.0f),
						                     D3DXVECTOR3(ENEMY_EXCLAMATION_MARK_SIZE, 0.1f, 0.0f),
						                     D3DXVECTOR3(0.0f, ENEMY_EXCLAMATION_MARK_ADD_SIZE, 0.0f),
						                     this, ENEMY_EXCLAMATION_MARK_LIFE);

				}
			}
			else if (fRadius <= ENEMY_ATTACK_DIFFER && m_movePattern != ENEMY_MOVE_PATTERN::DAMAGE)
			{//�v���C���[�Ǝ��g�̋���������̋������Z�������犎�A�_���[�W���󂯂Ă����ԂłȂ��Ƃ�
				//�U������
				m_movePattern = ENEMY_MOVE_PATTERN::ATTACK;
			}
			else if (fRadius > ENEMY_MOVE_TO_PLAYER_MAX_DIFFER &&
					m_movePattern == ENEMY_MOVE_PATTERN::MOVE_TO_PLAYER)
			{//�v���C���[�Ǝ��g�̋���������̋�����蒷���Ȃ�s���p�^�[�����v���C���[�Ɍ������ē����Ă����Ԃ̎�
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
		m_move.z = -cosf(m_rot.y) * ENEMY_FAT_MOVE_SPEED;
		m_move.x = -sinf(m_rot.y) * ENEMY_FAT_MOVE_SPEED;

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
		m_move.z = -cosf(fRot) * ENEMY_FAT_MOVE_SPEED;
		m_move.x = -sinf(fRot) * ENEMY_FAT_MOVE_SPEED;

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
			//�U������
			m_pMotionEnemyFat->SetMotion(CMotionRoad::MOTION_ENEMY_FAT_TYPE_ATTACK_01, this);
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
			m_pMotionEnemyFat->SetMotion(CMotionRoad::MOTION_ENEMY_FAT_TYPE_NEUTRAL, this);
		}
		else
		{
			//�v���C���[�Ɣ��΂̕��Ƀm�b�N�o�b�N������
			m_move.z = cosf(fRot) * ENEMY_FAT_DAMAGE_MOVE_SPEED;
			m_move.x = sinf(fRot) * ENEMY_FAT_DAMAGE_MOVE_SPEED;

			//��_���[�W���[�V��������Ȃ�������
			if (m_pMotionEnemyFat->GetMotion() != CMotionRoad::MOTION_ENEMY_FAT_TYPE_DAMAGE)
			{
				//�_���[�W���[�V�����ɂ���
				m_pMotionEnemyFat->SetMotion(CMotionRoad::MOTION_ENEMY_FAT_TYPE_DAMAGE, this);
			}
		}
		break;
	default:
		break;
	}
}

//================================================
//�v���C���[�ւ̍U���̓����蔻��			
//================================================
void CEnemyFat::ToPlayerAttackCollision(void)
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
			CPlayer *pPlayer = nullptr;
			pPlayer = (CPlayer*)pObject;

			//���[�V�������U�����A�L�[��2�ڈȍ~�̎�
			if (m_pMotionEnemyFat->GetMotion() == CMotionRoad::MOTION_ENEMY_FAT_TYPE::MOTION_ENEMY_FAT_TYPE_ATTACK_01 &&
				m_pMotionEnemyFat->GetKey() >= 2)
			{
				//�U���̓����蔻�肪����Ȃ�
				if (m_bAttackColl == true)
				{
					//�I�u�W�F�N�g�̈ʒu���擾
					D3DXVECTOR3 posObj = pPlayer->GetPos();
					posObj.y += pPlayer->GetSize().y;
					//�I�u�W�F�N�g�̃T�C�Y���擾
					D3DXVECTOR3 size = pPlayer->GetSize();

					for (int nCntMtx = 0; nCntMtx < ENEMY_FAT_MAX_ATTACK_COLLISION; nCntMtx++)
					{
						//���g�̎肩��Ώۂ̃I�u�W�F�N�g�܂ł̋��������߂�
						float fRadius = sqrtf((posObj.x - m_aAttackCollMtx[nCntMtx]._41) * (posObj.x - m_aAttackCollMtx[nCntMtx]._41) +
							                  (posObj.y - m_aAttackCollMtx[nCntMtx]._42) * (posObj.y - m_aAttackCollMtx[nCntMtx]._42) +
							                  (posObj.z - m_aAttackCollMtx[nCntMtx]._43) * (posObj.z - m_aAttackCollMtx[nCntMtx]._43));


						//���߂��������v���C���[�̔��a�ƑΏۂ̃I�u�W�F�N�g�̔��a�𑫂������l�ȉ���������
						if (fRadius <= ENEMY_FAT_ATTACK_COLLISION_RADIUS + size.x / 2.0f)
						{
							//���^�G�̍U���Ƃ̓����蔻��
							if (pPlayer->GetState() == CPlayer::PLAYER_STATE::NORMAL)
							{
								//�K�[�h���Ă��Ȃ�������
								if (pPlayer->GetGuard() == false)
								{
									//��Ԃ𖳓G�ɂ���
									pPlayer->SetState(CPlayer::PLAYER_STATE::DAMAGE);
									//���C�t�����炷
									CManager::GetInstance()->GetPlayData()->GetHpGauge()->AddGauge(-ENEMY_FAT_ATTACK_DAMAGE);
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
									D3DXVECTOR3 posPlayer = pPlayer->GetPos();
									D3DXVECTOR3 rotPlayer = pPlayer->GetRot();
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
									if (fDiffer > D3DX_PI / 2.0f)
									{
										//��Ԃ𖳓G�ɂ���
										pPlayer->SetState(CPlayer::PLAYER_STATE::DAMAGE);
										//���C�t�����炷
										CManager::GetInstance()->GetPlayData()->GetHpGauge()->AddGauge(-ENEMY_FAT_ATTACK_DAMAGE);
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
										CManager::GetInstance()->GetPlayData()->GetSpGauge()->AddGauge(ENEMY_FAT_GUARD_ADD_SP);
									}
								}
							}
							//�U���̓����蔻�肪�L���Ȃ�
							if (m_bAttackColl == true)
							{
								//�U���̓����蔻�������
								m_bAttackColl = false;
							}
						}
					}
				}
			}
			if (m_pMotionEnemyFat->GetMotion() == CMotionRoad::MOTION_ENEMY_FAT_TYPE::MOTION_ENEMY_FAT_TYPE_ATTACK_01 &&
			    m_pMotionEnemyFat->GetKey() >= m_pMotionEnemyFat->GetKeyMax() - 2 &&
			    m_pMotionEnemyFat->GetFrame() >= m_pMotionEnemyFat->GetFrameMax())
			{//���[�V�������U�����I�������
				//�U���̓����蔻�肪�����Ȃ�
				if (m_bAttackColl == false)
				{
					//�U���̓����蔻���L���ɂ���
					m_bAttackColl = true;
				}
			}
		}
		//���̃I�u�W�F�N�g�ɐi�߂�
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//================================================
//�a���̓����蔻��
//================================================
bool CEnemyFat::CollisionSlash(void)
{
	//���̋O�ՂƂ̓����蔻��
	if (CMeshTrajectory::CollisionSphere(this, m_size.x / 3.0f) == true && m_movePattern != ENEMY_MOVE_PATTERN::DAMAGE &&
		m_pMotionEnemyFat->GetMotion() != CMotionRoad::MOTION_ENEMY_FAT_TYPE_ATTACK_01)
	{//�_���[�W���󂯂Ă��Ȃ��čU�����[�V�����ł͂Ȃ�������

		//�J�����̃|�C���^�z��1�Ԗڂ̃A�h���X�擾
		CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
		//camera�̎擾
		CCamera* pCamera = &**pCameraAddress;
		//�J�����̌����擾
		D3DXVECTOR3 rotCamera = pCamera->GetRotV();

		//�q�b�g�G�t�F�N�g���o��
		CEffect3D::Create(D3DXVECTOR3(m_pos.x + sinf(rotCamera.y) * ENEMY_FAT_HIT_EFFECT_POS_XZ, m_pos.y + ENEMY_FAT_HIT_EFFECT_POS_Y,
			              m_pos.z + cosf(rotCamera.y) * ENEMY_FAT_HIT_EFFECT_POS_XZ),
			              D3DXVECTOR3(ENEMY_FAT_HIT_EFFECT_SIZE, ENEMY_FAT_HIT_EFFECT_SIZE, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			              CEffect3D::EFFECT3D_TYPE::HIT);

		//�΂̕��G�t�F�N�g�̐���
		CSpark::Create(D3DXVECTOR3(m_pos.x + sinf(rotCamera.y) * ENEMY_FAT_HIT_EFFECT_POS_XZ, m_pos.y + ENEMY_FAT_HIT_EFFECT_POS_Y,
			                       m_pos.z + cosf(rotCamera.y) * ENEMY_FAT_HIT_EFFECT_POS_XZ),
			           D3DXVECTOR3(ENEMY_SPARK_SIZE, ENEMY_SPARK_SIZE, 0.0f), ENEMY_SPARK_EFFECT_NUM,
			           ENEMY_SPARK_EFFECT_COLOR, ENEMY_SPARK_MOVE_MIN, ENEMY_SPARK_MOVE_MAX, ENEMY_SPARK_GRAVITY,
			           ENEMY_SPARK_COL_A_MIN, ENEMY_SPARK_COL_A_MAX, ENEMY_SPARK_SUBTRACTION_MOVE);

		//SP�Q�[�W�𑝂₷
		CManager::GetInstance()->GetPlayData()->GetSpGauge()->AddGauge(ENEMY_FAT_HIT_ADD_SP);
		//MP�Q�[�W�𑝂₷
		CManager::GetInstance()->GetPlayData()->GetMpGauge()->AddGauge(ENEMY_FAT_HIT_ADD_MP);

		//���C�t�����炷
		m_nLife -= ENEMY_FAT_HIT_DAMAGE;
		//���C�t��0�ɂȂ�����
		if (m_nLife <= 0)
		{
			//�X�R�A�𑝂₷
			CManager::GetInstance()->GetPlayData()->GetScorePoint()->AddScore(ENEMY_FAT_UNINIT_SCORE);

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
bool CEnemyFat::CollisionMagicThunder(void)
{
	if (CMagicThunder::Collision(this) == true)
	{
		//�_���[�W��ԂłȂ��Ȃ�
		if (m_movePattern != ENEMY_MOVE_PATTERN::DAMAGE)
		{
			//�_���[�W��Ԃɂ���
			m_movePattern = ENEMY_MOVE_PATTERN::DAMAGE;

			//HP�����炷
			m_nLife -= MAGIC_THUNDER_EFFECT_ENEMY_FAT_DAMAGE;

			//�J�����̃|�C���^�z��1�Ԗڂ̃A�h���X�擾
			CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
			//camera�̎擾
			CCamera* pCamera = &**pCameraAddress;
			//�J�����̌����擾
			D3DXVECTOR3 rotCamera = pCamera->GetRotV();

			//�q�b�g�G�t�F�N�g���o��
			CEffect3D::Create(D3DXVECTOR3(m_pos.x + sinf(rotCamera.y) * ENEMY_FAT_HIT_EFFECT_POS_XZ, m_pos.y + ENEMY_FAT_HIT_EFFECT_POS_Y,
				              m_pos.z + cosf(rotCamera.y) * ENEMY_FAT_HIT_EFFECT_POS_XZ),
				              D3DXVECTOR3(ENEMY_FAT_HIT_EFFECT_SIZE, ENEMY_FAT_HIT_EFFECT_SIZE, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				              CEffect3D::EFFECT3D_TYPE::HIT);

			//�΂̕��G�t�F�N�g�̐���
			CSpark::Create(D3DXVECTOR3(m_pos.x + sinf(rotCamera.y) * ENEMY_FAT_HIT_EFFECT_POS_XZ, m_pos.y + ENEMY_FAT_HIT_EFFECT_POS_Y,
				                       m_pos.z + cosf(rotCamera.y) * ENEMY_FAT_HIT_EFFECT_POS_XZ),
				           D3DXVECTOR3(ENEMY_SPARK_SIZE, ENEMY_SPARK_SIZE, 0.0f), ENEMY_SPARK_EFFECT_NUM,
				           ENEMY_SPARK_EFFECT_COLOR, ENEMY_SPARK_MOVE_MIN, ENEMY_SPARK_MOVE_MAX, ENEMY_SPARK_GRAVITY,
				           ENEMY_SPARK_COL_A_MIN, ENEMY_SPARK_COL_A_MAX, ENEMY_SPARK_SUBTRACTION_MOVE);

			//HP��0�ȉ��ɂȂ�����
			if (m_nLife <= 0)
			{
				//�X�R�A�𑝂₷
				CManager::GetInstance()->GetPlayData()->GetScorePoint()->AddScore(ENEMY_FAT_UNINIT_SCORE);

				//����
				Uninit();
				return true;
			}
		}
	}
	return false;
}
