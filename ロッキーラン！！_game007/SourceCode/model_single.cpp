//================================================
//���f���P�̂��o������
//Author:��������
//================================================
#include "scene2D.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "model_single.h"
#include "renderer.h"
#include "model.h"
#include "x_load.h"
#include "game01.h"
#include "tutorial.h"
#include "player.h"
#include "control.h"
#include "control_up_down_wall.h"
#include "shadow.h"
#include "scene3D.h"
#include "play_data.h"
//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CModelSingle::CModelSingle(int nPriority):CScene(nPriority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pParent = NULL;
	m_pModel = NULL;
	m_modelType = MODEL_SINGLE_TYPE_NONE;
	m_bDelete = false;
	m_nCntDelete = 0;
	m_pControl = NULL;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CModelSingle::~CModelSingle()
{

}

//================================================
//����������
//================================================
HRESULT CModelSingle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_posOld = m_pos;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bDelete = false;
	m_nCntDelete = 0;

	//���f���̐���
	m_pModel = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_rot, m_type);

	//�e�̐ݒ�
	m_pModel->SetParent(m_pParent);


	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_MODEL);

	//�T�C�Y���擾
	m_size = m_pModel->GetSize();
	SetSize(m_size);
	SetPos(m_pos);

	return S_OK;
}

//================================================
//�I������
//================================================
void CModelSingle::Uninit(void)
{
	Release();
}

//================================================
//�X�V����
//================================================
void CModelSingle::Update(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	//�ʒu�̔��f
	m_pos = pos;
	m_posOld = pos;

	//���f���̈ړ�����
	if (m_pControl != NULL)
	{
		m_pControl->Update(this);
		m_move = m_pControl->GetMove();
	}

	m_pos += m_move;		//�ړ��ʔ��f

	//�ʒu���f
	SetPos(m_pos);
	SetPosOld(m_posOld);

	//�I�u�W�F�N�g��������|�C���^
	CScene *pObject = NULL;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CScene *pSaveObject = NULL;

	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CScene::PRIORITY_MODEL);

	if (m_modelType == MODEL_SINGLE_TYPE_DOWN_WALL || m_modelType == MODEL_SINGLE_TYPE_UP_WALL)
	{
		while (pObject != NULL)
		{
			//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
			pSaveObject = pObject;

			if (pObject->GetObjType() == CScene::OBJTYPE_PLAYER)
			{
				//�v���C���[�ɃL���X�g
				CPlayer *pPlayer = NULL;
				pPlayer = (CPlayer*)pObject;
				//�I�u�W�F�N�g�Ƃ̓����蔻��
				pPlayer->Collision(this);
			}
			pObject = pSaveObject->GetObjNext(pSaveObject);
		}
	}

	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�p�b�h�擾����
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	m_pModel->Update();

	if (m_bDelete == true)
	{
		//�J�E���g�����Z
		m_nCntDelete++;
		if (m_nCntDelete >= MODEL_SINGLE_DELETE_TIME)
		{
			m_bDelete = false;
			m_nCntDelete = 0;
		}
	}

	//�ʒu���f
	SetPos(m_pos);
}

//================================================
//�`�揈��
//================================================
void CModelSingle::Draw(void)
{
	//�����Ă��Ȃ�������
	if (m_bDelete == false)
	{
		//�f�o�C�X�̃|�C���^
		LPDIRECT3DDEVICE9 pDevice;
		//�f�o�C�X�̎擾
		pDevice = CManager::GetRenderer()->GetDevice();

		D3DXMATRIX mtxRot, mtxTrans;			//�v�Z�p�}�g���b�N�X

		D3DXMatrixIdentity(&m_mtxWorld);		//���f���̃��[���h�}�g���b�N�X�̏�����

												//���f���̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//���f���̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//���f���̕`��
		m_pModel->Draw();
	}
}

//================================================
//��������
//================================================
CModelSingle *CModelSingle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CXload::X_TYPE type, CModel *pParent, MODEL_SINGLE_TYPE modelType)
{
	//�C���X�^���X�̐���
	CModelSingle *pModelSingle = NULL;
	if (pModelSingle == NULL)
	{
		pModelSingle = new CModelSingle;
		if (pModelSingle != NULL)
		{
			switch (modelType)
			{
			case MODEL_SINGLE_TYPE_UP_WALL:
				pModelSingle->m_pControl = CControlUpDownWall::Create(CControlUpDownWall::UP_WALL, 110.0f);
				break;

			case MODEL_SINGLE_TYPE_DOWN_WALL:
				pModelSingle->m_pControl = CControlUpDownWall::Create(CControlUpDownWall::DOWN_WALL, 110.0f);
				break;
			default:
				pModelSingle->m_pControl = NULL;
				break;
			}
			pModelSingle->m_rot = rot;
			pModelSingle->m_type = type;
			pModelSingle->m_modelType = modelType;
			pModelSingle->m_pParent = pParent;
			pModelSingle->Init(pos, pModelSingle->m_size);
		}
	}
	return pModelSingle;
}

//================================================
//�����蔻�菈��
//================================================
bool CModelSingle::SimpleCollision(CScene *pScene)
{
	bool bLand = false;	//���n���Ă��邩�ǂ���

	//�I�u�W�F�N�g��������|�C���^
	CScene *pObject = NULL;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CScene *pSaveObject = NULL;

	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CScene::PRIORITY_MODEL);

	while (pObject != NULL)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;

		if (pObject->GetObjType() == CScene::OBJTYPE_MODEL)
		{
			//���f���V���O���ɃL���X�g
			CModelSingle *pModelSingle = NULL;
			pModelSingle = (CModelSingle*)pObject;

			//�����Ă��Ȃ�������
			if (pModelSingle->m_bDelete == false)
			{
				D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�Ώۂ̈ʒu
				D3DXVECTOR3 posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���f���̈ʒu
				D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�Ώۂ̃T�C�Y
				D3DXVECTOR3 sizeModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���f���̃T�C�Y
				D3DXVECTOR3 posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�Ώۂ�1�t���[���O�̈ʒu

				//���f���̈ʒu�E�T�C�Y�擾
				posModel = pModelSingle->GetPos();
				sizeModel = pModelSingle->GetSize();

				//�Ώۂ̈ʒu�E�T�C�Y�擾
				pos = pScene->GetPos();
				posOld = pScene->GetPosOld();
				size = pScene->GetSize();

				if (pos.x + size.x / 2.0f > posModel.x - sizeModel.x / 2.0f &&
					pos.x - size.x / 2.0f < posModel.x + sizeModel.x / 2.0f &&
					pos.z + size.x / 2.0f > posModel.z - sizeModel.z / 2.0f &&
					pos.z - size.x / 2.0f < posModel.z + sizeModel.z / 2.0f &&
					pos.y <= posModel.y + sizeModel.y &&
					posOld.y >= posModel.y + sizeModel.y)
				{
					pos.y = posModel.y + sizeModel.y;
					//�ʒu��ݒ�
					pScene->SetPos(pos);

					if (pModelSingle->m_modelType == MODEL_SINGLE_TYPE_UNINIT_FLOOR)
					{
						pModelSingle->m_bDelete = true;
						return false;
					}
					else if (pModelSingle->m_modelType == MODEL_SINGLE_TYPE_GOAL)
					{
						//�t�F�[�Y���S�[���ɂ���
						if (CManager::GetGame01() != NULL)
						{
							//�v���C���[�ɃL���X�g
							CPlayer *pPlayer = NULL;
							pPlayer = (CPlayer*)pScene;

							CManager::GetGame01()->SetPhase(CGame01::GAME01_PHASE_CLEAR);

							CPlayData::SetWinNum(pPlayer->GetNum());
						}
						if (CManager::GetTutorial() != NULL)
						{
							CManager::GetTutorial()->SetGoal(true);
						}
					}
					else if (pModelSingle->m_modelType == MODEL_SINGLE_TYPE_MIDDLE1_FLOOR)
					{//���Ԃ̏��ɏ������
						if (CManager::GetGame01() != NULL)
						{
							//�v���C���[�ɃL���X�g
							CPlayer *pPlayer = NULL;
							pPlayer = (CPlayer*)pScene;

							//�`�F�b�N�|�C���g���ЂƂO�Ȃ�`�F�b�N�|�C���g��ݒ�
							if (pPlayer->GetCheckPoint() == CPlayer::PLAYER_CHECK_POINT_NONE)
							{
								pPlayer->SetCheckPoint(CPlayer::PLAYER_CHECK_POINT_GAME01_MIDDLE1);
							}
						}
					}
					else if (pModelSingle->m_modelType == MODEL_SINGLE_TYPE_MIDDLE2_FLOOR)
					{//���Ԃ̏��ɏ������
						if (CManager::GetGame01() != NULL)
						{
							//�v���C���[�ɃL���X�g
							CPlayer *pPlayer = NULL;
							pPlayer = (CPlayer*)pScene;

							//�`�F�b�N�|�C���g���ЂƂO�Ȃ�`�F�b�N�|�C���g��ݒ�
							if (pPlayer->GetCheckPoint() == CPlayer::PLAYER_CHECK_POINT_GAME01_MIDDLE1)
							{
								pPlayer->SetCheckPoint(CPlayer::PLAYER_CHECK_POINT_GAME01_MIDDLE2);
							}
						}
					}
					else if (pModelSingle->m_modelType == MODEL_SINGLE_TYPE_ICE_FLOOR)
					{//�X�̏��ɏ������

						if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
						{
							//�v���C���[�ɃL���X�g
							CPlayer *pPlayer = NULL;
							pPlayer = (CPlayer*)pScene;

							pPlayer->SetOnIce(true);
						}
					}
					else if (pModelSingle->m_modelType == MODEL_SINGLE_TYPE_SPRING)
					{//�΂˂̏��ɏ������
						if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
						{
							//�v���C���[�ɃL���X�g
							CPlayer *pPlayer = NULL;
							pPlayer = (CPlayer*)pScene;

							pPlayer->SetOnSpring(true);
						}
					}

					if (pModelSingle->m_modelType != MODEL_SINGLE_TYPE_ICE_FLOOR)
					{
						if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
						{
							//�v���C���[�ɃL���X�g
							CPlayer *pPlayer = NULL;
							pPlayer = (CPlayer*)pScene;

							pPlayer->SetOnIce(false);
						}
					}

					if (pModelSingle->m_modelType != MODEL_SINGLE_TYPE_SPRING)
					{
						if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
						{
							//�v���C���[�ɃL���X�g
							CPlayer *pPlayer = NULL;
							pPlayer = (CPlayer*)pScene;

							pPlayer->SetOnSpring(false);
						}
					}

					bLand = true;
				}
				else if (pos.x + size.x / 2.0f > posModel.x - sizeModel.x / 2.0f &&
					pos.x - size.x / 2.0f < posModel.x + sizeModel.x / 2.0f &&
					pos.z + size.x / 2.0f > posModel.z - sizeModel.z / 2.0f &&
					pos.z - size.x / 2.0f < posModel.z + sizeModel.z / 2.0f &&
					pos.y + size.y >= posModel.y &&
					posOld.y + size.y <= posModel.y)
				{
					pos.y = posModel.y - size.y;
					//�ʒu��ݒ�
					pScene->SetPos(pos);
				}
				if (pos.y + size.y > posModel.y &&
					pos.y < posModel.y + sizeModel.y &&
					pos.z + size.x / 2.0f > posModel.z - sizeModel.z / 2.0f &&
					pos.z - size.x / 2.0f < posModel.z + sizeModel.z / 2.0f &&
					pos.x + size.x / 2.0f >= posModel.x - sizeModel.x / 2.0f &&
					posOld.x + size.x / 2.0f <= posModel.x - sizeModel.x / 2.0f)
				{
					pos.x = posModel.x - sizeModel.x / 2.0f - size.x / 2.0f;
					//�ʒu��ݒ�
					pScene->SetPos(pos);
				}
				else if (pos.y + size.y > posModel.y &&
					pos.y < posModel.y + sizeModel.y &&
					pos.z + size.x / 2.0f > posModel.z - sizeModel.z / 2.0f &&
					pos.z - size.x / 2.0f < posModel.z + sizeModel.z / 2.0f &&
					pos.x - size.x / 2.0f <= posModel.x + sizeModel.x / 2.0f &&
					posOld.x - size.x / 2.0f >= posModel.x + sizeModel.x / 2.0f)
				{
					pos.x = posModel.x + sizeModel.x / 2.0f + size.x / 2.0f;
					//�ʒu��ݒ�
					pScene->SetPos(pos);
				}
				if (pos.y + size.y > posModel.y &&
					pos.y < posModel.y + sizeModel.y &&
					pos.x + size.x / 2.0f > posModel.x - sizeModel.x / 2.0f &&
					pos.x - size.x / 2.0f < posModel.x + sizeModel.x / 2.0f &&
					pos.z + size.x / 2.0f >= posModel.z - sizeModel.z / 2.0f &&
					posOld.z + size.x / 2.0f <= posModel.z - sizeModel.z / 2.0f)
				{
					pos.z = posModel.z - sizeModel.z / 2.0f - size.x / 2.0f;
					//�ʒu��ݒ�
					pScene->SetPos(pos);
				}
				else if (pos.y + size.y > posModel.y &&
					pos.y < posModel.y + sizeModel.y &&
					pos.x + size.x / 2.0f > posModel.x - sizeModel.x / 2.0f &&
					pos.x - size.x / 2.0f < posModel.x + sizeModel.x / 2.0f &&
					pos.z - size.x / 2.0f <= posModel.z + sizeModel.z / 2.0f &&
					posOld.z - size.x / 2.0f >= posModel.z + sizeModel.z / 2.0f)
				{
					pos.z = posModel.z + sizeModel.z / 2.0f + size.x / 2.0f;
					//�ʒu��ݒ�
					pScene->SetPos(pos);
				}
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
	return bLand;
}

//================================================
//�g�p�󋵂̎擾����
//================================================
bool CModelSingle::GetDeleteObject(void)
{
	return m_bDelete;
}