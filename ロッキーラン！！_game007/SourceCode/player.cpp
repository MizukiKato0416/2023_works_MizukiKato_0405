//================================================
//�v���C���[����
//Author:��������
//================================================
#include "scene2D.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "player.h"
#include "renderer.h"
#include "model.h"
#include "x_load.h"
#include "control.h"
#include "control_player.h"
#include "shadow.h"
#include "model_single.h"
#include "camera.h"
#include "motion_player.h"
#include "2DAnimation_jump.h"
#include "sound.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CPlayer::CPlayer(int nPriority):CScene(nPriority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pParent = NULL;
	m_pControl = NULL;
	m_bLand = false;
	m_bJump = false;
	m_bDive = false;
	m_bOnIce = false;
	m_bOnIce = false;
	m_bOnSpring = false;
	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{
		m_apModel[nCntModel] = NULL;
	}
	m_pMotionPlayer = NULL;
	m_pShadow = NULL;
	m_bLandMoment = false;
	m_bJumpOld = false;
	m_nNum = 0;
	m_checkPoint = PLAYER_CHECK_POINT_NONE;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CPlayer::~CPlayer()
{

}

//================================================
//����������
//================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//�N���ASE�Đ�
	pSound->Play(CSound::SOUND_LABEL_RESPAWN_SE);

	m_pos = pos;
	m_posOld = pos;
	m_move = m_pControl->GetMove();
	m_bLand = false;
	m_bJump = true;
	m_bDive = false;
	m_bLandMoment = false;
	m_bJumpOld = false;
	m_bOnIce = false;
	m_bOnSpring = false;
	m_checkPoint = PLAYER_CHECK_POINT_NONE;

	//���f���̐���
	switch (m_nNum)
	{
	case 0:
		m_apModel[0] = CModel::Create(D3DXVECTOR3(0.0f, 8.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_BODY);
		m_apModel[1] = CModel::Create(D3DXVECTOR3(-10.0f, 12.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_ARM_R);
		m_apModel[2] = CModel::Create(D3DXVECTOR3(10.0f, 12.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_ARM_L);
		m_apModel[3] = CModel::Create(D3DXVECTOR3(-5.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_LEG_R);
		m_apModel[4] = CModel::Create(D3DXVECTOR3(5.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_LEG_L);
		break;
	case 1:
		m_apModel[0] = CModel::Create(D3DXVECTOR3(0.0f, 8.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_GIRL_BODY);
		m_apModel[1] = CModel::Create(D3DXVECTOR3(-10.0f, 12.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_GIRL_ARM_R);
		m_apModel[2] = CModel::Create(D3DXVECTOR3(10.0f, 12.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_GIRL_ARM_L);
		m_apModel[3] = CModel::Create(D3DXVECTOR3(-5.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_GIRL_LEG_R);
		m_apModel[4] = CModel::Create(D3DXVECTOR3(5.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_GIRL_LEG_L);
	default:
		break;
	}

	//�e�̐ݒ�
	m_apModel[0]->SetParent(NULL);
	m_apModel[1]->SetParent(m_apModel[0]);
	m_apModel[2]->SetParent(m_apModel[0]);
	m_apModel[3]->SetParent(m_apModel[0]);
	m_apModel[4]->SetParent(m_apModel[0]);

	//�ʒu�̐ݒ�
	SetPos(m_pos);
	SetPosOld(m_posOld);

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_PLAYER);

	//�T�C�Y���擾
	m_size = m_apModel[0]->GetSize();

	//�T�C�Y�̐ݒ�
	SetSize(m_size);

	//���[�V�����̐���
	m_pMotionPlayer = CMotionPlayer::Create(this);

	//camera�̃|�C���^�z��1�Ԗڂ̃A�h���X�擾
	CCamera **pCameraAddress = CManager::GetCamera();

	for (int nCntCamera = 0; nCntCamera <MAX_CAMERA; nCntCamera++, pCameraAddress++)
	{
		//camera�̎擾
		CCamera *pCamera = &**pCameraAddress;
		if (pCamera != NULL)
		{
			if (m_nNum == pCamera->GetNum())
			{
				if (CManager::GetResult() != NULL)
				{
					//camera�̌����ݒ�
					pCamera->SetRotV(D3DXVECTOR3(m_rot.x, m_rot.y - D3DX_PI, m_rot.z));
					//camera�̒����_�ݒ菈��
					pCamera->SetPosR(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z));
					//camera�̎��_�ݒ菈��
					pCamera->SetPosV(D3DXVECTOR3(m_pos.x + sinf(m_rot.y - D3DX_PI) * CAMERA_RESULT_DISTANCE,
													100.0f,
													m_pos.z + cosf(m_rot.y - D3DX_PI) * CAMERA_RESULT_DISTANCE));
				}
				else
				{
					//camera�̌����ݒ�
					pCamera->SetRotV(m_rot);
					//camera�̒����_�ݒ菈��
					pCamera->SetPosR(m_pos);
					//camera�̎��_�ݒ菈��
					pCamera->SetPosV(D3DXVECTOR3(m_pos.x + sinf(m_rot.y) * CAMERA_DISTANCE, 150.0f, m_pos.z + cosf(m_rot.y) * CAMERA_DISTANCE));
				}
			}
		}
	}
	return S_OK;
}

//================================================
//�I������
//================================================
void CPlayer::Uninit(void)
{
	//�e������
	m_pShadow->Uninit();
	delete m_pShadow;
	m_pShadow = NULL;

	Release();
}

//================================================
//�X�V����
//================================================
void CPlayer::Update(void)
{
	if (this != NULL)
	{
		//�ʒu�擾
		D3DXVECTOR3 pos = GetPos();
		m_pos = pos;
		m_posOld = pos;
		//1�t���[���O�̈ʒu�ݒ�
		SetPosOld(m_posOld);

		//�O�̃t���[���̃W�����v���Ă��邩�ǂ����̏�����
		m_bJumpOld = m_bJump;

		//�L�[�{�[�h�擾����
		CInputKeyboard *pInputKeyboard;
		pInputKeyboard = CManager::GetInputKeyboard();

		//�p�b�h�擾����
		CInputPadX *pInputPadX;
		pInputPadX = CManager::GetInputPadX();

		//�ړ�����
		Move();

		m_pos += m_move;		//�ړ��ʔ��f

		//�v���C���[�Ƃ̓����蔻��
		CollisionPlayer(this);

		//�ʒu���f
		SetPos(m_pos);

		//���n���Ă���Ƃ��͈ړ��ʂ�0�ɂ���
		m_bLand = CModelSingle::SimpleCollision(this);
		if (m_bLand == true)
		{
			if (m_bJumpOld == true)
			{
				//�W�����v���[�V������
				if (m_pMotionPlayer->GetMotion() == CMotionPlayer::MOTION_PLAYER_TYPE_JUMP)
				{
					//���n���[�V�����ɂ���
					m_pMotionPlayer->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_LAND);

					//���n�A�j���[�V����
					C2DAnimationJump::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 10.0f, m_pos.z),
											D3DXVECTOR3(25.0f, 25.0f, 0.0f), 
											D3DXVECTOR3(m_rot.x, m_rot.y + 3.14f, m_rot.z), 0.1f);
					m_bJump = false;
					m_move.y = 0.0f;
				}
			}
		}
		else
		{
			m_bLandMoment = false;
		}
		
		//���[�V����
		m_pMotionPlayer->Update(this);

		//�e�̒Ǐ]
		ShadowCollision();

		//�ʒu�擾
		m_pos = GetPos();
	}
}

//================================================
//�`�揈��
//================================================
void CPlayer::Draw(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;			//�v�Z�p�}�g���b�N�X

	D3DXMatrixIdentity(&m_mtxWorld);		//�v���C���[�̃��[���h�}�g���b�N�X�̏�����

	//�v���C���[�̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���f���̕`��
	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{
		m_apModel[nCntModel]->Draw();
	}

}

//================================================
//��������
//================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNum)
{
	//�C���X�^���X�̐���
	CPlayer *pPlayer = NULL;
	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;
		if (pPlayer != NULL)
		{
			pPlayer->m_pShadow = CShadow::Create(D3DXVECTOR3(pos.x, 0.0f, pos.z), D3DXVECTOR3(40.0f, 0.0f, 40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			pPlayer->m_pControl = CControlPlayer::Create();
			pPlayer->m_rot = rot;
			pPlayer->m_nNum = nNum;
			pPlayer->Init(pos, pPlayer->m_size);
		}
	}
	return pPlayer;
}

//================================================
//1�t���[���O�̈ʒu�擾
//================================================
D3DXVECTOR3 CPlayer::GetPosOld(void)
{
	return m_posOld;
}

//================================================
//�����蔻�菈��
//================================================
bool CPlayer::Collision(void)
{
	return false;
}

//================================================
//�ړ�����
//================================================
void CPlayer::Move(void)
{
	if (m_pControl != NULL)
	{
		m_pControl->Update(this);
		m_move = m_pControl->GetMove();
	}
}

//================================================
//���n�ݒ菈��
//================================================
void CPlayer::SetLand(bool bLand)
{
	m_bLand = bLand;
}

//================================================
//���n�擾����
//================================================
bool CPlayer::GetLand(void)
{
	return m_bLand;
}

//================================================
//�����擾����
//================================================
D3DXVECTOR3 CPlayer::GetRot(void)
{
	return m_rot;
}

//================================================
//�����ݒ菈��
//================================================
void CPlayer::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//================================================
//�ړ��ʎ擾����
//================================================
void CPlayer::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//================================================
//�ړ��ʎ擾����
//================================================
D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_move;
}

//================================================
//�W�����v�擾����
//================================================
void CPlayer::SetJump(bool bJump)
{
	m_bJump = bJump;
}

//================================================
//�W�����v�擾����
//================================================
bool CPlayer::GetJump(void)
{
	return m_bJump;
}

//================================================
//�_�C�u�擾����
//================================================
void CPlayer::SetDive(bool bDive)
{
	m_bDive = bDive;
}

//================================================
//�_�C�u�擾����
//================================================
bool CPlayer::GetDive(void)
{
	return m_bDive;
}

//================================================
//���f���̈ʒu�ݒ菈��
//================================================
void CPlayer::SetModelPos(int nCntModel, D3DXVECTOR3 pos)
{
	m_apModel[nCntModel]->SetPos(pos);
}

//================================================
//���f���̈ʒu�擾����
//================================================
D3DXVECTOR3 CPlayer::GetModelPos(int nCntModel)
{
	return m_apModel[nCntModel]->GetPos();
}

//================================================
//���f���̌����ݒ菈��
//================================================
void CPlayer::SetModelRot(int nCntModel, D3DXVECTOR3 rot)
{
	m_apModel[nCntModel]->SetRot(rot);
}

//================================================
//���f���̌����擾����
//================================================
D3DXVECTOR3 CPlayer::GetModelRot(int nCntModel)
{
	return m_apModel[nCntModel]->GetRot();
}

//================================================
//���[�V�����v���C���[�擾����
//================================================
CMotionPlayer *CPlayer::GetMotionPlayer(void)
{
	return m_pMotionPlayer;
}

//================================================
//�X�̏ォ�ǂ����ݒ菈��
//================================================
void CPlayer::SetOnIce(bool bOnIce)
{
	m_bOnIce = bOnIce;
}

//================================================
//�X�̏ォ�ǂ����擾����
//================================================
bool CPlayer::GetOnIce(void)
{
	return m_bOnIce;
}

//================================================
//�o�l���ǂ����ݒ菈��
//================================================
void CPlayer::SetOnSpring(bool bOnSpring)
{
	m_bOnSpring = bOnSpring;
}

//================================================
//�o�l���ǂ����擾����
//================================================
bool CPlayer::GetOnSpring(void)
{
	return m_bOnSpring;
}

//================================================
//�I�u�W�F�N�g�Ƃ̓����蔻��
//================================================
void CPlayer::Collision(CScene *pScene)
{
	//�I�u�W�F�N�g�̈ʒu���擾
	D3DXVECTOR3 posObj = pScene->GetPos();
	//�I�u�W�F�N�g��1�t���[���O�̈ʒu���擾
	D3DXVECTOR3 posObjOld = pScene->GetPosOld();
	//�I�u�W�F�N�g�̃T�C�Y���擾
	D3DXVECTOR3 sizeObj = pScene->GetSize();

	if (posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
		posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
		posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
		posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
		posObj.y + sizeObj.y >= m_pos.y&&
		posObjOld.y + sizeObj.y <= m_pos.y)
	{
		m_pos.y = posObj.y + sizeObj.y;
		//�ʒu��ݒ�
		SetPos(m_pos);
		//1�t���[���O�̈ʒu��ݒ�
		SetPosOld(m_pos);
		if (pScene->GetObjType() == OBJTYPE_MODEL)
		{
			m_move.z -= 2.0f;
		}
	}
	else if (posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
			 posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
			 posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
			 posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
			 posObj.y <= m_pos.y + m_size.y &&
			 posObjOld.y >= m_pos.y + m_size.y)
	{
		m_pos.y = posObj.y - m_size.y;
		//�ʒu��ݒ�
		SetPos(m_pos);
		//1�t���[���O�̈ʒu��ݒ�
		SetPosOld(m_pos);
	}
	if (posObj.y + sizeObj.y < m_pos.y &&
		posObj.y > m_pos.y + m_size.y &&
		posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
		posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
		posObj.x + sizeObj.x / 2.0f <= m_pos.x - m_size.x / 2.0f &&
		posObjOld.x + sizeObj.x / 2.0f >= m_pos.x - m_size.x / 2.0f)
	{
		m_pos.x = posObj.x + sizeObj.x / 2.0f - m_size.x / 2.0f;
		//�ʒu��ݒ�
		SetPos(m_pos);
		//1�t���[���O�̈ʒu��ݒ�
		SetPosOld(m_pos);
	}
	else if (posObj.y + sizeObj.y < m_pos.y &&
			 posObj.y > m_pos.y + m_size.y &&
			 posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
			 posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
			 posObj.x - sizeObj.x / 2.0f >= m_pos.x + m_size.x / 2.0f &&
			 posObjOld.x - sizeObj.x / 2.0f <= m_pos.x + m_size.x / 2.0f)
	{
		m_pos.x = posObj.x - sizeObj.x / 2.0f + m_size.x / 2.0f;
		//�ʒu��ݒ�
		SetPos(m_pos);
		//1�t���[���O�̈ʒu��ݒ�
		SetPosOld(m_pos);
	}
	if (posObj.y + sizeObj.y < m_pos.y &&
		posObj.y > m_pos.y + m_size.y &&
		posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
		posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
		posObj.z + sizeObj.z / 2.0f <= m_pos.z - m_size.x / 2.0f &&
		posObjOld.z + sizeObj.z / 2.0f >= m_pos.z - m_size.x / 2.0f)
	{
		m_pos.z = posObj.z - sizeObj.z / 2.0f + m_size.x / 2.0f;
		//�ʒu��ݒ�
		SetPos(m_pos);
		//1�t���[���O�̈ʒu��ݒ�
		SetPosOld(m_pos);
	}
	else if (posObj.y + sizeObj.y < m_pos.y &&
			 posObj.y > m_pos.y + m_size.y &&
			 posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
			 posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
			 posObj.z - sizeObj.z / 2.0f >= m_pos.z + m_size.x / 2.0f &&
			 posObjOld.z - sizeObj.z / 2.0f <= m_pos.z + m_size.x / 2.0f)
	{
		m_pos.z = posObj.z + sizeObj.z / 2.0f - m_size.x / 2.0f;
		//�ʒu��ݒ�
		SetPos(m_pos);
		//1�t���[���O�̈ʒu��ݒ�
		SetPosOld(m_pos);
	}
}

//================================================
//�v���C���[�Ƃ̓����蔻��
//================================================
void CPlayer::CollisionPlayer(CPlayer *pPlayer)
{
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

		if (pObject->GetObjType() == CScene::OBJTYPE_PLAYER)
		{
			//�v���C���[�ɃL���X�g
			CPlayer *pPlayerObj = NULL;
			pPlayerObj = (CPlayer*)pObject;

			if (pPlayerObj->GetNum() != pPlayer->GetNum())
			{
				//�I�u�W�F�N�g�̈ʒu���擾
				D3DXVECTOR3 posObj = pPlayerObj->GetPos();
				//�I�u�W�F�N�g��1�t���[���O�̈ʒu���擾
				D3DXVECTOR3 posObjOld = pPlayerObj->GetPosOld();
				//�I�u�W�F�N�g�̃T�C�Y���擾
				D3DXVECTOR3 sizeObj = pPlayerObj->GetSize();

				float fRadius = sqrtf((posObj.x - pPlayer->m_pos.x) * (posObj.x - pPlayer->m_pos.x) + (posObj.z - pPlayer->m_pos.z) * (posObj.z - pPlayer->m_pos.z));
				float fRot = atan2((posObj.x - pPlayer->m_pos.x), (posObj.z - pPlayer->m_pos.z)) - D3DX_PI;
				pPlayer->m_rot;

				if (fRadius <= pPlayer->m_size.x * 2.0f)
				{
					pPlayer->m_pos.x = posObj.x + (sinf(fRot) * pPlayer->m_size.x * 2.0f);
					pPlayer->m_pos.z = posObj.z + (cosf(fRot) * pPlayer->m_size.x * 2.0f);
				}
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}


//================================================
//�̎��ʔԍ��ݒ菈��
//================================================
void CPlayer::SetNum(int nNum)
{
	m_nNum = nNum;
}

//================================================
//�o�l���ǂ����擾����
//================================================
int CPlayer::GetNum(void)
{
	return m_nNum;
}

//================================================
//�`�F�b�N�|�C���g�ݒ菈��
//================================================
void CPlayer::SetCheckPoint(PLAYER_CHECK_POINT checkPoint)
{
	m_checkPoint = checkPoint;
}

//================================================
//�`�F�b�N�|�C���g�擾����
//================================================
CPlayer::PLAYER_CHECK_POINT CPlayer::GetCheckPoint(void)
{
	return m_checkPoint;
}

//================================================
//�e�̕\���̂��߂̃I�u�W�F�N�g�Ƃ̓����蔻��
//================================================
void CPlayer::ShadowCollision(void)
{
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

			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//�I�u�W�F�N�g�̈ʒu���擾
			D3DXVECTOR3 posObj = pModelSingle->GetPos();
			//�I�u�W�F�N�g��1�t���[���O�̈ʒu���擾
			D3DXVECTOR3 posObjOld = pModelSingle->GetPosOld();
			//�I�u�W�F�N�g�̃T�C�Y���擾
			D3DXVECTOR3 sizeObj = pModelSingle->GetSize();

			if (posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
				posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
				posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
				posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
				posObj.y + sizeObj.y >= m_pos.y - 50.0f &&
				posObj.y + sizeObj.y <= m_pos.y)
			{
				//�I�u�W�F�N�g�������ĂȂ��ꍇ�̂�
				if (pModelSingle->GetDeleteObject() == false)
				{
					//�ʒu�����f���̏��
					pos.y = posObj.y + sizeObj.y;

					//�e�̒Ǐ]
					m_pShadow->SetShadow(D3DXVECTOR3(m_pos.x, pos.y, m_pos.z), (m_pos.y - pos.y));


					//�e���g���Ă����Ԃɂ���
					m_pShadow->SetUseShadow(true);

					return;
				}
			}
			else
			{
				//�e���g���Ă��Ȃ���Ԃɂ���
				m_pShadow->SetUseShadow(false);
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}