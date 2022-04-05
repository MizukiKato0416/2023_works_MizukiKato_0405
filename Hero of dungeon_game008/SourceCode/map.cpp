//================================================
//�}�b�v����
//Author:KatoMizuki
//================================================
#include "Object2D.h"
#include "manager.h"
#include "map.h"
#include "texture.h"
#include "dungeon_room_builder.h"

//================================================
//�}�N����`
//================================================

//================================================
//�ÓI�����o�ϐ��錾
//================================================
D3DXVECTOR3 CMap::m_posStartRoom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CMap::CMap(int nPriority) :CObject2D(nPriority)
{
	m_bDraw = false;
	m_pObject = nullptr;
	m_type = TYPE::NONE;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CMap::~CMap()
{

}

//================================================
//����������
//================================================
HRESULT CMap::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�ϐ�������
	m_bDraw = true;

	CObject2D::Init(pos, size);

	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjType(CObject::OBJTYPE::MAP);

	return S_OK;
}

//================================================
//�I������
//================================================
void CMap::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================
//�X�V����
//================================================
void CMap::Update(void)
{
	//�v���C���[�����������̏���
	PlayerMove();

	//�G�����������̏���
	EnemyMove();
}

//================================================
//�`�揈��
//================================================
void CMap::Draw(void)
{
	//�`�悷��Ȃ�
	if (m_bDraw == true)
	{
		CObject2D::Draw();
	}
}

//================================================
//��������
//================================================
CMap* CMap::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriolity, TYPE type)
{
	//�C���X�^���X�̐���
	CMap *pMap = nullptr;
	if (pMap == nullptr)
	{
		pMap = new CMap(nPriolity);
		if (pMap != nullptr)
		{
			pMap->m_type = type;
			pMap->Init(pos, size);
			//�w�肵����ނŃe�N�X�`����ς���
			switch (type)
			{
			case TYPE::START:
				pMap->m_posStartRoom = pos;
				pMap->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MAP_ROAD");
				break;
			case TYPE::ROAD:
				pMap->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MAP_ROAD");
				break;
			case TYPE::WALL:
				pMap->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MAP_WALL");
				break;
			case TYPE::PLAYER:
				pMap->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MAP_PLAYER");
				break;
			case TYPE::ENEMY:
				pMap->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MAP_ENEMY");
				break;
			case TYPE::CHECK:
				pMap->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MAP_CHECK");
				break;
			case TYPE::WARP:
				pMap->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MAP_WARP");
				break;
			default:
				break;
			}
			pMap->BindTexture(pMap->m_pTexture);
		}
	}
	return pMap;
}

//================================================
//�}�b�v�̈ʒu�ݒ菈��
//================================================
void CMap::SetStartRoomPos(void)
{
	//�X�^�[�g�n�_�̈ʒu�ƃ}�b�v�����̈ʒu�Ƃ̍������߂�
	D3DXVECTOR3 posStartRoom = D3DXVECTOR3(m_posStartRoom.x - MAP_POS_X, m_posStartRoom.y - MAP_POS_Y, 0.0f);

	//�I�u�W�F�N�g��������|�C���^
	CObject *pObject = nullptr;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CObject *pSaveObject = nullptr;

	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CObject::PRIORITY_MAP);

	while (pObject != nullptr)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;

		//�I�u�W�F�N�g�̎�ނ��}�b�v��������
		if (pObject->GetObjType() == CObject::OBJTYPE::MAP)
		{
			//�}�b�v�ɃL���X�g
			CMap *pMapObj = nullptr;
			pMapObj = (CMap*)pObject;

			//�^�C�v���v���C���[�ł͂Ȃ��Ƃ�
			if (pMapObj->m_type != TYPE::PLAYER)
			{
				//�ʒu�ƃT�C�Y���擾
				D3DXVECTOR3 pos = pMapObj->GetPos();
				D3DXVECTOR3 size = pMapObj->GetSize();

				//�X�^�[�g�n�_�̈ʒu�ƃ}�b�v�����̈ʒu�Ƃ̍����ړ�������
				pos -= posStartRoom;

				//�ʒu�ƃT�C�Y�ݒ�
				pMapObj->SetPos(pos, size);
			}
		}
		//���̃I�u�W�F�N�g�ɐi�߂�
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//================================================
//�G�̃|�C���^�ݒ菈��
//================================================
void CMap::SetEnemyPointa(void)
{
	//�I�u�W�F�N�g��������|�C���^
	CObject *pEnemyObject = nullptr;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CObject *pSaveEnemyObject = nullptr;

	//�I�u�W�F�N�g��������|�C���^
	CObject *pObject = nullptr;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CObject *pSaveObject = nullptr;

	//�}�b�v�ɃL���X�g����悤
	CMap *pMapObj = nullptr;

	//�擪�̃|�C���^����
	pEnemyObject = pEnemyObject->GetTopObj(CObject::PRIORITY_ENEMY);

	while (pEnemyObject != nullptr)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveEnemyObject = pEnemyObject;

		//�I�u�W�F�N�g�̎�ނ��G��������
		if (pEnemyObject->GetObjType() == CObject::OBJTYPE::ENEMY_BEE ||
			pEnemyObject->GetObjType() == CObject::OBJTYPE::ENEMY_FAT ||
			pEnemyObject->GetObjType() == CObject::OBJTYPE::ENEMY_BOSS)
		{
			//�I�u�W�F�N�g��������|�C���^
			pObject = nullptr;
			//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
			pSaveObject = nullptr;

			//�擪�̃|�C���^����
			pObject = pObject->GetTopObj(CObject::PRIORITY_MAP);

			while (pObject != nullptr)
			{
				//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
				pSaveObject = pObject;

				//�I�u�W�F�N�g�̎�ނ��}�b�v��������
				if (pObject->GetObjType() == CObject::OBJTYPE::MAP)
				{
					//�}�b�v�ɃL���X�g
					pMapObj = nullptr;
					pMapObj = (CMap*)pObject;

					//�^�C�v���G�̂Ƃ�
					if (pMapObj->m_type == TYPE::ENEMY)
					{
						//�Ώۂ̃I�u�W�F�N�g�̃|�C���^��nullptr�̎�
						if (pMapObj->m_pObject == nullptr)
						{
							//�Ώۂ̃I�u�W�F�N�g�̃|�C���^��ݒ肷��
							pMapObj->m_pObject = pEnemyObject;

							//�G�̈ʒu���擾
							D3DXVECTOR3 posEnemy = pEnemyObject->GetPos();
							//�y���x�ɑ��
							posEnemy.y = posEnemy.z;

							//�}�b�v�̏k�ڕ��k�߂��ꏊ�����߂�
							posEnemy *= MAP_ROOM_SIZE / DUNGEON_ROOM_BUILDER_SIZE;

							//Z��0�ɂ���
							posEnemy.z = 0.0f;

							//�ʒu�ƃT�C�Y���擾
							D3DXVECTOR3 posMap = pMapObj->GetPos();
							D3DXVECTOR3 sizeMap = pMapObj->GetSize();

							//�����ړ�������
							posMap.x += posEnemy.x;
							posMap.y -= posEnemy.y;

							//�ʒu�ݒ�
							pMapObj->SetPos(posMap, sizeMap);
							break;
						}
					}
				}
				//���̃I�u�W�F�N�g�ɐi�߂�
				pObject = pSaveObject->GetObjNext(pSaveObject);
			}
		}
		//���̃I�u�W�F�N�g�ɐi�߂�
		pEnemyObject = pSaveEnemyObject->GetObjNext(pSaveEnemyObject);
	}
}

//================================================
//�`�F�b�N�|�C���g�̃|�C���^�ݒ菈��
//================================================
void CMap::SetCheckPointa(void)
{
	//�I�u�W�F�N�g��������|�C���^
	CObject *pCheckObject = nullptr;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CObject *pSaveCheckObject = nullptr;

	//�I�u�W�F�N�g��������|�C���^
	CObject *pObject = nullptr;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CObject *pSaveObject = nullptr;

	//�}�b�v�ɃL���X�g����悤
	CMap *pMapObj = nullptr;

	//�擪�̃|�C���^����
	pCheckObject = pCheckObject->GetTopObj(CObject::PRIORITY_CHECK_CIRCLE);

	while (pCheckObject != nullptr)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveCheckObject = pCheckObject;

		//�I�u�W�F�N�g�̎�ނ��`�F�b�N�|�C���g��������
		if (pCheckObject->GetObjType() == CObject::OBJTYPE::CHECK_CIRCLE)
		{
			//�I�u�W�F�N�g��������|�C���^
			pObject = nullptr;
			//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
			pSaveObject = nullptr;

			//�擪�̃|�C���^����
			pObject = pObject->GetTopObj(CObject::PRIORITY_MAP);

			while (pObject != nullptr)
			{
				//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
				pSaveObject = pObject;

				//�I�u�W�F�N�g�̎�ނ��}�b�v��������
				if (pObject->GetObjType() == CObject::OBJTYPE::MAP)
				{
					//�}�b�v�ɃL���X�g
					pMapObj = nullptr;
					pMapObj = (CMap*)pObject;

					//�^�C�v���`�F�b�N�|�C���̂Ƃ�
					if (pMapObj->m_type == TYPE::CHECK)
					{
						//�Ώۂ̃I�u�W�F�N�g�̃|�C���^��nullptr�̎�
						if (pMapObj->m_pObject == nullptr)
						{
							//�Ώۂ̃I�u�W�F�N�g�̃|�C���^��ݒ肷��
							pMapObj->m_pObject = pCheckObject;

							//�G�̈ʒu���擾
							D3DXVECTOR3 posCheck = pCheckObject->GetPos();
							//�y���x�ɑ��
							posCheck.y = posCheck.z;

							//�}�b�v�̏k�ڕ��k�߂��ꏊ�����߂�
							posCheck *= MAP_ROOM_SIZE / DUNGEON_ROOM_BUILDER_SIZE;

							//Z��0�ɂ���
							posCheck.z = 0.0f;

							//�ʒu�ƃT�C�Y���擾
							D3DXVECTOR3 posMap = pMapObj->GetPos();
							D3DXVECTOR3 sizeMap = pMapObj->GetSize();

							//�����ړ�������
							posMap.x += posCheck.x;
							posMap.y -= posCheck.y;

							//�ʒu�ݒ�
							pMapObj->SetPos(posMap, sizeMap);
							break;
						}
					}
				}
				//���̃I�u�W�F�N�g�ɐi�߂�
				pObject = pSaveObject->GetObjNext(pSaveObject);
			}
		}
		//���̃I�u�W�F�N�g�ɐi�߂�
		pCheckObject = pSaveCheckObject->GetObjNext(pSaveCheckObject);
	}
}

//================================================
//�j������
//================================================
void CMap::Delete(CObject * pSubjectObject)
{
	//�I�u�W�F�N�g��������|�C���^
	CObject *pObject = nullptr;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CObject *pSaveObject = nullptr;

	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CObject::PRIORITY_MAP);

	while (pObject != nullptr)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;

		//�I�u�W�F�N�g�̎�ނ��}�b�v��������
		if (pObject->GetObjType() == CObject::OBJTYPE::MAP)
		{
			//�}�b�v�ɃL���X�g
			CMap *pMapObj = nullptr;
			pMapObj = (CMap*)pObject;

			//�����ƑΏۂ̃|�C���^����v���Ă�����
			if (pMapObj->m_pObject == pSubjectObject)
			{
				//����
				pMapObj->m_pObject = nullptr;
				pMapObj->Uninit();
				return;
			}
		}
		//���̃I�u�W�F�N�g�ɐi�߂�
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//================================================
//�v���C���[�����������̏���
//================================================
void CMap::PlayerMove(void)
{
	//�^�C�v���v���C���[�ł͂Ȃ��Ƃ�
	if (m_type != TYPE::PLAYER)
	{
		//�^�C�v���G�̎�
		if (m_type == TYPE::ENEMY || m_type == TYPE::CHECK)
		{
			if (m_pObject == nullptr)
			{
				return;
			}
		}
		//�ʒu�ƃT�C�Y���擾
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 size = GetSize();

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
				//�v���C���[�̌��ݒn����1�t���[���O�̈ʒu�܂ł̍������߂�
				D3DXVECTOR3 posDiffer = pObject->GetPosOld() - pObject->GetPos();
				//�y���x�ɑ��
				posDiffer.y = posDiffer.z;

				//�}�b�v�̏k�ڕ������k�߂�
				posDiffer *= MAP_ROOM_SIZE / DUNGEON_ROOM_BUILDER_SIZE;

				//Z��0�ɂ���
				posDiffer.z = 0.0f;

				//�����ړ�������
				pos.x += posDiffer.x;
				pos.y -= posDiffer.y;
			}
			//���̃I�u�W�F�N�g�ɐi�߂�
			pObject = pSaveObject->GetObjNext(pSaveObject);
		}

		//�ʒu�ƃT�C�Y�ݒ�
		SetPos(pos, size);

		//�`�悷��͈͂Ɋւ��鏈��
		DrawRange(pos);
	}
}

//================================================
//�G�����������̏���
//================================================
void CMap::EnemyMove(void)
{
	//�^�C�v���G�̂Ƃ�
	if (m_type == TYPE::ENEMY)
	{
		if (m_pObject == nullptr)
		{
			return;
		}
		//�ʒu�ƃT�C�Y���擾
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 size = GetSize();

		//���ݒn����1�t���[���O�̈ʒu�܂ł̍������߂�
		D3DXVECTOR3 posDiffer = m_pObject->GetPosOld() - m_pObject->GetPos();
		//�y���x�ɑ��
		posDiffer.y = posDiffer.z;

		//�}�b�v�̏k�ڕ������k�߂�
		posDiffer *= MAP_ROOM_SIZE / DUNGEON_ROOM_BUILDER_SIZE;

		//Z��0�ɂ���
		posDiffer.z = 0.0f;

		//�����ړ�������
		pos.x -= posDiffer.x;
		pos.y += posDiffer.y;

		//�ʒu�ƃT�C�Y�ݒ�
		SetPos(pos, size);

		//�`�悷��͈͂Ɋւ��鏈��
		DrawRange(pos);
	}
}

//================================================
//�`��͈̔͂Ɋւ��鏈��
//================================================
void CMap::DrawRange(D3DXVECTOR3 pos)
{
	//����͈̔͂���|���S�����o����
	if (pos.x < MAP_POS_X - MAP_SIZE / 2.0f || pos.x > MAP_POS_X + MAP_SIZE / 2.0f ||
		pos.y < MAP_POS_Y - MAP_SIZE / 2.0f || pos.y > MAP_POS_Y + MAP_SIZE / 2.0f)
	{
		//�`�悳��Ă���Ȃ�
		if (m_bDraw == true)
		{
			//�`������Ȃ��悤�ɂ���
			m_bDraw = false;
		}
	}
	else
	{//����͈̔͂ɂ���Ƃ�
	 //�`�悳��Ă��Ȃ��Ȃ�
		if (m_bDraw == false)
		{
			//�`�������
			m_bDraw = true;
		}
	}
}
