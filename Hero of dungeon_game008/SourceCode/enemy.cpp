//================================================
//�G�̏���
//Author:KatoMizuki
//================================================
#include "manager.h"
#include "enemy.h"
#include "renderer.h"
#include "object3D.h"
#include "model_single.h"
#include "player.h"
#include "map.h"
#include "shadow.h"

//================================================
//�}�N����`
//================================================

//================================================
//�ÓI�����o�ϐ��錾
//================================================
int CEnemy::m_nNum = 0;

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CEnemy::CEnemy(int nPriority):CObject(nPriority)
{
	//��������x���₷
	m_nNum++;

	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_bDraw = false;
	m_bNotice = false;
	m_movePattern = ENEMY_MOVE_PATTERN::NONE;
	m_nStopCounter = 0;
	m_nMoveCounter = 0;
	m_nAttackCounter = 0;
	m_nDamageCounter = 0;
	m_nLife = 0;
	m_pShadow = nullptr;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CEnemy::~CEnemy()
{
	//�����x���炷
	m_nNum--;
}

//================================================
//�I������
//================================================
void CEnemy::Uninit(void)
{
	//�e������
	m_pShadow->Uninit();
	m_pShadow = nullptr;

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
			if (pPlayerObj->GetEnemyNear() == this)
			{
				//null�ɂ���
				pPlayerObj->SetEnemyNear(nullptr);
			}
		}
		//���̃I�u�W�F�N�g�ɐi�߂�
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}

	//�}�b�v��̓G�̈ʒu�j��
	CMap::Delete(this);

	Release();
}

//================================================
//�`�揈��
//================================================
void CEnemy::Draw(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;			//�v�Z�p�}�g���b�N�X

	D3DXMatrixIdentity(&m_mtxWorld);		//�v���C���[�̃��[���h�}�g���b�N�X�̏�����

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
}

//================================================
//��]����
//================================================
void CEnemy::Rotate(void)
{
	//��]�������ԂȂ�
	if (m_bRotate == true)
	{
		//�ړI�̌������v�Z
		if (m_fObjectiveRot > D3DX_PI)
		{
			m_fObjectiveRot = -D3DX_PI - (D3DX_PI - m_fObjectiveRot);
		}
		else if (m_fObjectiveRot < -D3DX_PI)
		{
			m_fObjectiveRot = D3DX_PI - (-D3DX_PI - m_fObjectiveRot);
		}

		//���݂̌������Ƃɂ��ꂼ�������ς���ʂ��v�Z
		if (m_rot.y < 0.0f && -m_rot.y + m_fObjectiveRot > D3DX_PI)
		{
			m_fNumRot = (-D3DX_PI - m_rot.y) + -(D3DX_PI - m_fObjectiveRot);
		}
		else if (m_rot.y >= D3DX_PI / 2.0f && m_rot.y - m_fObjectiveRot > D3DX_PI)
		{
			m_fNumRot = (D3DX_PI - m_rot.y) - (-D3DX_PI - m_fObjectiveRot);
		}
		else
		{
			m_fNumRot = (m_fObjectiveRot - m_rot.y);
		}

		//�����ɉ��Z
		m_rot.y += m_fNumRot * 0.2f;

		//����̒l�ɒB�������]����߂�
		if (m_rot.y - m_fObjectiveRot < 0.001f && m_rot.y - m_fObjectiveRot > -0.001f)
		{
			m_bRotate = false;
		}
	}

	//�΂��傫���Ȃ�����-2�΂���
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{	//-�΂�菬�����Ȃ�����+2�΂���
		m_rot.y += D3DX_PI * 2.0f;
	}
}

//================================================
//�����蔻��
//================================================
void CEnemy::Collision(CObject *pSubjectObject, float fObjRadius)
{
	//�I�u�W�F�N�g��������|�C���^
	CObject *pObject = nullptr;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CObject *pSaveObject = nullptr;

	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CObject::PRIORITY_ENEMY);

	while (pObject != nullptr)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;

		//�I�u�W�F�N�g�̎�ނ��G��������
		if ((pObject->GetObjType() == CObject::OBJTYPE::ENEMY ||
			pObject->GetObjType() == CObject::OBJTYPE::ENEMY_FAT ||
			pObject->GetObjType() == CObject::OBJTYPE::ENEMY_BEE ||
			pObject->GetObjType() == CObject::OBJTYPE::ENEMY_BOSS) &&
			pObject != pSubjectObject)
		{
			//�G�ɃL���X�g
			CEnemy *pEnemyObj = nullptr;
			pEnemyObj = (CEnemy*)pObject;

			//�I�u�W�F�N�g�̈ʒu���擾
			D3DXVECTOR3 posObj = pSubjectObject->GetPos();

			//���g����Ώۂ̃I�u�W�F�N�g�܂ł̋��������߂�
			float fRadius = sqrtf((posObj.x - pEnemyObj->m_pos.x) * (posObj.x - pEnemyObj->m_pos.x) +
				(posObj.z - pEnemyObj->m_pos.z) * (posObj.z - pEnemyObj->m_pos.z));
			//���g�ƑΏۂ̃I�u�W�F�N�g�̊p�x�����߂�
			float fRot = atan2((posObj.x - pEnemyObj->m_pos.x), (posObj.z - pEnemyObj->m_pos.z)) - D3DX_PI;

			//���߂��������v���C���[�̔��a�ƑΏۂ̃I�u�W�F�N�g�̔��a�𑫂������l�ȉ���������
			if (fRadius <= pEnemyObj->m_size.x / 2.0f + fObjRadius)
			{
				//���g�̈ʒu�������o��
				pEnemyObj->m_pos.x = posObj.x + (sinf(fRot) * (pEnemyObj->m_size.x / 2.0f + fObjRadius));
				pEnemyObj->m_pos.z = posObj.z + (cosf(fRot) * (pEnemyObj->m_size.x / 2.0f + fObjRadius));

				//�ʒu�ݒ�
				pEnemyObj->SetPos(pEnemyObj->m_pos);

				//���f���Ƃ̓����蔻��
				CModelSingle::Collision(pEnemyObj);
			}
		}
		//���̃I�u�W�F�N�g�ɐi�߂�
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//================================================
//�Փ˔���݂̂̏���
//================================================
bool CEnemy::CollisionOnly(CObject * pSubjectObject, float fObjRadius)
{
	//�I�u�W�F�N�g�̈ʒu���擾
	D3DXVECTOR3 posObj = pSubjectObject->GetPos();

	//�v���C���[����Ώۂ̃I�u�W�F�N�g�܂ł̋��������߂�
	float fRadius = sqrtf((posObj.x - m_pos.x) * (posObj.x - m_pos.x) +
		(posObj.z - m_pos.z) * (posObj.z - m_pos.z));

	//���߂��������v���C���[�̔��a�ƑΏۂ̃I�u�W�F�N�g�̔��a�𑫂������l�ȉ���������
	if (fRadius <= m_size.x / 2.0f + fObjRadius)
	{
		//�������Ă���
		return true;
	}

	return false;
}