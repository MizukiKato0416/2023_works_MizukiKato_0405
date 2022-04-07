//================================================
//�v���C���[����
//Author:KatoMizuki
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_d.h"
#include "input_mouse.h"
#include "player.h"
#include "motion_player.h"
#include "renderer.h"
#include "model.h"
#include "x_load.h"
#include "floor.h"
#include "model_single.h"
#include "mesh_trajectory.h"
#include "texture.h"
#include "enemy_fat.h"
#include "camera.h"
#include "magic_thunder.h"
#include "magic_fire.h"
#include "play_data.h"
#include "gauge.h"
#include "meshfield.h"
#include "billboard.h"
#include "enemy.h"
#include "ui.h"
#include "shadow.h"
#include "sound.h"

//================================================
//�}�N����`
//================================================
#define PLAYER_JUMP							(7.0f)		//�W�����v��
#define PLAYER_GRAVITY						(0.2f)		//�d�͂̑傫��
#define PLAYER_MOVE_SPEED					(9.0f)		//�ʏ�ړ��̈ړ���
#define PLAYER_SLASH_MOVE_SPEED				(4.0f)		//�a�����̈ړ��̈ړ���
#define PLAYER_INVINCIBLE_COUNT				(30)		//���G����
#define PLAYER_SP_COST_MP					(400)		//SP���g�p����̂ɕK�v��MP
#define PLAYER_MAGIC_FIRE_COST_MP			(100)		//�����@���g�p����̂ɕK�v��MP
#define PLAYER_LOCK_ON_UI_SIZE				(100.0f)	//���b�N�I��UI�̃T�C�Y
#define PLAYER_LOCK_ON_UI_POS				(50.0f)		//���b�N�I��UI�̈ʒu�����l
#define PLAYER_SIZE							(10.0f)		//�v���C���[�̃T�C�Y�����l

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CPlayer::CPlayer(int nPriority):CObject(nPriority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pParent = nullptr;
	memset(&m_apModel, NULL, sizeof(m_apModel));
	m_pMotionPlayer = nullptr;
	m_pLockOn = nullptr;
	m_pEnemyNear = nullptr;
	m_fObjectiveRot = 0.0f;
	m_fLockOnObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_bJump = false;
	m_bBurst = false;
	m_bSpecial = false;
	m_bLockOn = false;
	m_nCntBurst = 0;
	m_bGuard = false;
	m_state = PLAYER_STATE::NONE;
	m_nInvincibleCounter = 0;
	for (int nCntMeshTrajectory = 0; nCntMeshTrajectory < 2; nCntMeshTrajectory++)
	{
		m_pMeshTrajectory[nCntMeshTrajectory] = nullptr;
	}
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
	m_pos = pos;
	m_posOld = pos;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fLockOnObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_bJump = false;
	m_bBurst = false;
	m_bSpecial = false;
	m_bLockOn = false;
	m_bGuard = false;
	m_nCntBurst = 0;
	m_state = PLAYER_STATE::NORMAL;
	m_nInvincibleCounter = 0;
	m_pLockOn = nullptr;
	m_pEnemyNear = nullptr;

	for (int nCntMeshTrajectory = 0; nCntMeshTrajectory < 2; nCntMeshTrajectory++)
	{
		m_pMeshTrajectory[nCntMeshTrajectory] = nullptr;
	}

	//���f���̐���
	//text�t�@�C���ǂݍ���
	FILE *pFile = fopen("data/MOTION/motion_player.txt", "r");
	if (pFile != nullptr)
	{
		char cString[128];
		//��s���ۑ�
		while (fgets(cString, 128, pFile) != NULL)
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
				nModelType = CXload::X_TYPE_PLAYER_BODY;
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

				if (nIndex == MAX_PLAYER_MODEL - 1)
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
	SetObjType(CObject::OBJTYPE::PLAYER);

	//���[�V�����̐���
	m_pMotionPlayer = CMotionPlayer::Create(this);
	m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL, this);

	//�T�C�Y���擾
	D3DXVECTOR3 modelSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	modelSize = m_apModel[0]->GetSize();

	//�T�C�Y��X��Z���ׂđ傫���ق���X��Z���ꂼ��Ɋ��蓖�Ă�
	if (modelSize.x >= modelSize.z)
	{
		m_size = D3DXVECTOR3(modelSize.x + PLAYER_SIZE, modelSize.y, modelSize.x + PLAYER_SIZE);
	}
	else
	{
		m_size = D3DXVECTOR3(modelSize.z + PLAYER_SIZE, modelSize.y, modelSize.z + PLAYER_SIZE);
	}

	//�T�C�Y�̐ݒ�
	SetSize(m_size);

	//�e�̐ݒ�
	CShadow::Create(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z), D3DXVECTOR3(m_size.x, 0.0f, m_size.z), this);

	return S_OK;
}

//================================================
//�I������
//================================================
void CPlayer::Uninit(void)
{
	Release();
}

//================================================
//�X�V����
//================================================
void CPlayer::Update(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	m_pos = pos;
	m_posOld = pos;

	//1�t���[���O�̈ʒu�ݒ�
	SetPosOld(m_posOld);

	//�d��
	m_move.y -= PLAYER_GRAVITY;

	//���b�N�I������
	LockOn();

	//��Ԃɂ�鏈������
	State();

	m_pos += m_move;		//�ړ��ʔ��f

	//��]�̊���
	Rotate();

	//���[�V����
	m_pMotionPlayer->Update(this);

	//�ʒu���f
	SetPos(m_pos);

	//���Ƃ̓����蔻��
	if (CFloor::Collision(this) == true)
	{
		m_bJump = false;
		m_move.y = 0.0f;
		//�W�����v����
		Jump();

		if (m_bJump == false)
		{
			m_move.y -= 40.0f;
		}
	}

	//���f���Ƃ̓����蔻��
	if (CModelSingle::Collision(this) == true)
	{
		m_bJump = false;
		m_move.y = 0.0f;
		//�W�����v����
		Jump();

		if (m_bJump == false)
		{
			m_move.y -= 40.0f;
		}
	}

	//���b�V���t�B�[���h�Ƃ̓����蔻��
	//if (CMeshField::Collision(this, 100.0f) == true)
	//{
	//	m_bJump = false;
	//	m_move.y = 0.0f;
	//	//�W�����v����
	//	Jump();

	//	if (m_bJump == false)
	//	{
	//		m_move.y -= 40.0f;
	//	}
	//}

	//�ʒu�擾
	pos = GetPos();
	m_pos = pos;
}

//================================================
//�`�揈��
//================================================
void CPlayer::Draw(void)
{
	//�ʒu�擾����
	D3DXVECTOR3 pos = GetPos();

	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

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
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�C���X�^���X�̐���
	CPlayer *pPlayer = nullptr;
	if (pPlayer == nullptr)
	{
		pPlayer = new CPlayer;
		if (pPlayer != nullptr)
		{
			pPlayer->m_rot = rot;
			pPlayer->Init(pos, pPlayer->m_size);
		}
	}
	return pPlayer;
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
//���f���̓�������
//================================================
void CPlayer::Move(void)
{
	//�p�b�hD�擾����
	CInputPadD *pInputPadD = CManager::GetInstance()->GetInputPadD();
	DIJOYSTATE2 JoyStick = pInputPadD->GetGamepad();

	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�p�b�hX�擾����
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInstance()->GetInputPadX();

	D3DXVECTOR3 rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//camera�̃|�C���^�z��1�Ԗڂ̃A�h���X�擾
	CCamera **pCameraAddress = CManager::GetInstance()->GetCamera();

	for (int nCntCamera = 0; nCntCamera < MAX_MAIN_CAMERA; nCntCamera++, pCameraAddress++)
	{
		//camera�̎擾
		CCamera *pCamera = &**pCameraAddress;
		if (pCamera != nullptr)
		{
			//camera�̌����擾
			rotCamera = pCamera->GetRotV();
		}
	}

	//�ړ��ʐݒ�p�ϐ�
	float fSpeed = 0.0f;

	//�A��������Ȃ�������
	if (m_bBurst == false)
	{
		//�ʏ�̈ړ��ʂɂ���
		fSpeed = PLAYER_MOVE_SPEED;
	}
	else
	{//�A�����Ȃ�
		//�a�����̈ړ��ʂɂ���
		fSpeed = PLAYER_SLASH_MOVE_SPEED;
	}

	//�X�e�B�b�N�̌X������������܂���WASD����������
	if ((float)JoyStick.lX != 0.0f || (float)JoyStick.lY != 0.0f || 
		pInputKeyboard->GetPress(DIK_W) == true || pInputKeyboard->GetPress(DIK_A) == true ||
		pInputKeyboard->GetPress(DIK_S) == true || pInputKeyboard->GetPress(DIK_D) == true)
	{
		//�ړI�̌�����ݒ�
		if ((float)JoyStick.lX != 0.0f || (float)JoyStick.lY != 0.0f)
		{
			m_fObjectiveRot = rotCamera.y + atan2f((float)JoyStick.lY, (float)JoyStick.lX) + D3DX_PI / 2.0f;
		}
		else if (pInputKeyboard->GetPress(DIK_W) == true)
		{
			if (pInputKeyboard->GetPress(DIK_A) == true)
			{
				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y - D3DX_PI / 4.0f;
			}
			else if (pInputKeyboard->GetPress(DIK_D) == true)
			{
				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y + D3DX_PI / 4.0f;
			}
			else
			{
				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{
			if (pInputKeyboard->GetPress(DIK_A) == true)
			{
				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y - D3DX_PI / 4.0f * 3.0f;
			}
			else if (pInputKeyboard->GetPress(DIK_D) == true)
			{
				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y + D3DX_PI / 4.0f * 3.0f;
			}
			else
			{
				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y + D3DX_PI;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			//�ړI�̌�����ݒ�
			m_fObjectiveRot = rotCamera.y - D3DX_PI / 2.0f;
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			//�ړI�̌�����ݒ�
			m_fObjectiveRot = rotCamera.y + D3DX_PI / 2.0f;
		}

		//�ړ��ʉ��Z
		m_move.x = sinf(m_fObjectiveRot + D3DX_PI) * fSpeed;
		m_move.z = cosf(m_fObjectiveRot + D3DX_PI) * fSpeed;
		//��]��������
		m_bRotate = true;

		if (m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_SLASH_01 &&	//�a��1���[�V�����łȂ�
			m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_SLASH_02 &&	//�a��2���[�V�����łȂ�
			m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_SLASH_03 &&	//�a��3���[�V�����łȂ�
			m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_SLASH_04 &&	//�a��4���[�V�����łȂ�
			m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_SPECIAL &&	//�K�E�Z���[�V�����łȂ�
			m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_MOVE)		//�ړ����[�V�����łȂ�
		{
			//�ړ����[�V�����ɂ���
			m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_MOVE, this);
		}
	}
	else
	{//�X�e�B�b�N�ɌX�����Ȃ�������

		//�ړ��ʂ��[���ɂ���
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		//�ړ����[�V������������
		if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_MOVE)
		{
			//�j���[�g�������[�V�����ɂ���
			m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL, this);
		}
	}
}

//================================================
//��]����
//================================================
void CPlayer::Rotate(void)
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

		//�v���C���[�̌��݂̌������Ƃɂ��ꂼ�������ς���ʂ��v�Z
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

		//�v���C���[�̌����ɉ��Z
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
//�W�����v����
//================================================
void CPlayer::Jump(void)
{
	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�p�b�hD�擾����
	CInputPadD *pInputPadD;
	pInputPadD = CManager::GetInstance()->GetInputPadD();

	if (pInputPadD->GetTrigger(CInputPadD::A) == true)	//A�{�^�����������Ƃ��̏���
	{
		//�ړ��ʂ��W�����v�����Z
		m_move.y = PLAYER_JUMP;
		m_bJump = true;
	}
}

//================================================
//���U������
//================================================
void CPlayer::Slash(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�p�b�hD�擾����
	CInputPadD *pInputPadD;
	pInputPadD = CManager::GetInstance()->GetInputPadD();

	//�}�E�X�擾����
	CInputMouse *pInputMouse;
	pInputMouse = CManager::GetInstance()->GetInputMouse();

	//�U���{�^�����������Ƃ��̏���
	if (pInputPadD->GetTrigger(CInputPadD::B) == true || pInputMouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
	{
		if (m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_GUARD &&	//�K�[�h���[�V�����ł͂Ȃ��Ƃ�
			m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_MAGIC_01 &&	//���@���[�V�����ł͂Ȃ��Ƃ�
			m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_SPECIAL)	//�K�E�Z���[�V�����ł͂Ȃ��Ƃ�
		{
			//�U�����[�V�����ő�l�����������Ƃ�
			if (m_nCntBurst <= CMotionRoad::MOTION_PLAYER_TYPE_SLASH_04 - CMotionRoad::MOTION_PLAYER_TYPE_SLASH_01)
			{
				//�A�����ł͂Ȃ��Ƃ�
				if (m_bBurst == false)
				{
					//�A������0�̎�
					if (m_nCntBurst == 0)
					{
						//�A���������Z
						m_nCntBurst++;
						//�A����Ԃɂ���
						m_bBurst = true;
						//�a�����[�V�����ɂ���
						m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_SLASH_01 + m_nCntBurst - 1, this);

						if (m_nCntBurst == 1 || m_nCntBurst == 3)
						{
							//SE�Đ�
							pSound->Play(CSound::SOUND_LABEL_SLASH_01_SE);
							//�T�E���h�̉��ʒ���
							pSound->ControllVoice(CSound::SOUND_LABEL_SLASH_01_SE, 1.5f);
						}
						else if (m_nCntBurst == 2 || m_nCntBurst == 4)
						{
							//SE�Đ�
							pSound->Play(CSound::SOUND_LABEL_SLASH_02_SE);
							//�T�E���h�̉��ʒ���
							pSound->ControllVoice(CSound::SOUND_LABEL_SLASH_02_SE, 1.5f);
						}
						
					}
				}
				else
				{//�A�����̎�
					//���݂̃��[�V���������̍U�����[�V�����̂ЂƂO��������
					if (m_pMotionPlayer->GetMotion() == m_nCntBurst + CMotionRoad::MOTION_PLAYER_TYPE_SLASH_01 - 1)
					{
						//�A���������Z
						m_nCntBurst++;
					}
				}
			}
		}
	}

	//���[�V�������q�����Ă����ԂłȂ��Ƃ�
	if (m_pMotionPlayer->GetConnect() == false)
	{
		//�a�����[�V�������I������Ƃ�
		if ((m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_01 ||
			 m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_02 ||
			 m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_03 ||
			 m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_04) &&
			 m_pMotionPlayer->GetKey() == m_pMotionPlayer->GetKeyMax() - 2 &&
			 m_pMotionPlayer->GetFrame() == m_pMotionPlayer->GetFrameMax())
		{
			for (int nCntMeshTrajectory = 0; nCntMeshTrajectory < 2; nCntMeshTrajectory++)
			{
				if (m_pMeshTrajectory[nCntMeshTrajectory] != nullptr)
				{
					//���̋O�Ղ�j��
					m_pMeshTrajectory[nCntMeshTrajectory]->Uninit();
					m_pMeshTrajectory[nCntMeshTrajectory] = nullptr;
				}
			}

			//�A���������݂̎a�����[�V�����̎��̃��[�V������������
			if (m_nCntBurst + CMotionRoad::MOTION_PLAYER_TYPE_SLASH_01 - 1 == m_pMotionPlayer->GetMotion() + 1)
			{
				if (m_nCntBurst == 1 || m_nCntBurst == 3)
				{
					//SE�Đ�
					pSound->Play(CSound::SOUND_LABEL_SLASH_01_SE);
					//�T�E���h�̉��ʒ���
					pSound->ControllVoice(CSound::SOUND_LABEL_SLASH_01_SE, 1.5f);
				}
				else if (m_nCntBurst == 2 || m_nCntBurst == 4)
				{
					//SE�Đ�
					pSound->Play(CSound::SOUND_LABEL_SLASH_02_SE);
					//�T�E���h�̉��ʒ���
					pSound->ControllVoice(CSound::SOUND_LABEL_SLASH_02_SE, 1.5f);
				}

				//���̎a�����[�V�����ɐݒ�
				m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_SLASH_01 + m_nCntBurst - 1, this);
				//���[�V�������Ȃ��Ƃ��̃t���[������ݒ�
				m_pMotionPlayer->SetFrameMax(1);
			}
			else
			{//�A���������݂̎a�����[�V�����̎��̃��[�V��������Ȃ�������
				if(m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_SLASH_04)
				{
					//�A����ԂłȂ�����
					m_bBurst = false;
					//�A������0�ɂ���
					m_nCntBurst = 0;
					m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL, this);
					//���[�V�������Ȃ��Ƃ��̃t���[������ݒ�
					m_pMotionPlayer->SetFrameMax(20);
				}
			}
		}
	}

	//���[�V�������q�����Ă����Ԃ���Ȃ��ă��[�V�������ړ����j���[�g�����̎�
	if (m_pMotionPlayer->GetConnect() == false &&
		(m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL ||
		 m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_MOVE))
	{
		//�A����ԂłȂ�����
		m_bBurst = false;
		//�A������0�ɂ���
		m_nCntBurst = 0;
	}
	

	if (((m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_01 && m_pMotionPlayer->GetKey() == 1) ||
		 (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_02 && m_pMotionPlayer->GetKey() == 1) ||
		 (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_03 && m_pMotionPlayer->GetKey() == 1) ||
		 (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_04 && m_pMotionPlayer->GetKey() == 1)) &&
		  m_pMotionPlayer->GetFrame() == 0)
	{
		//���̋O�Ղ���������Ă��Ȃ�������
		if (m_pMeshTrajectory[0] == nullptr)
		{
			//���̋O�Ղ𐶐�
			m_pMeshTrajectory[0] = CMeshTrajectory::Create(14, m_apModel[15]->GetMtxPoint(), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, -44.0f),
														D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			m_pMeshTrajectory[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MESH_TRAJECTORY_01"));
		}
		if (m_pMeshTrajectory[1] == nullptr)
		{
			//���̋O�Ղ𐶐�
			m_pMeshTrajectory[1] = CMeshTrajectory::Create(18, m_apModel[15]->GetMtxPoint(), D3DXVECTOR3(-2.0f, 0.0f, -20.0f), D3DXVECTOR3(-2.0f, 0.0f, -94.0f),
														D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			m_pMeshTrajectory[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MESH_TRAJECTORY_02"));
		}
	}

	//�U��1�A2�A3�͍U�����[�V�������n�܂����u�ԁA�U��4�̓L�[��4�ɂȂ����Ƃ�
	if (((m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_01 ||
		  m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_02 ||
		  m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_03) &&
		  m_pMotionPlayer->GetKey() == 0 && m_pMotionPlayer->GetFrame() == 0) || 
		 (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_04 &&
		  m_pMotionPlayer->GetKey() == 4 && m_pMotionPlayer->GetFrame() == 0))
	{
		//�ړ��ł���悤�ɂ���
		Move();
	}


	//�U��1�̎��̓L�[��3�ȍ~�͈ړ��ł��Ȃ��悤�ɂ���
	//�U��2�̎��̓L�[��2�ȍ~�͈ړ��ł��Ȃ��悤�ɂ���
	//�U��3�̎��͈ړ��ł��Ȃ��悤�ɂ���
	//�U��4�̎��̓L�[��7�ȍ~�͈ړ��ł��Ȃ��悤�ɂ���
	if ((m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_01 &&
		m_pMotionPlayer->GetKey() == 3 && m_pMotionPlayer->GetFrame() == 0) ||
		(m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_02 &&
		m_pMotionPlayer->GetKey() == 2 && m_pMotionPlayer->GetFrame() == 0) ||
		(m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_03 &&
		m_pMotionPlayer->GetKey() == 0 && m_pMotionPlayer->GetFrame() == 0 ||
		(m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_04 &&
		m_pMotionPlayer->GetKey() == 7 && m_pMotionPlayer->GetFrame() == 0)))
	{
		//�ړ��ʂ�0�ɂ���
		m_move.x = 0.0f;
		m_move.z = 0.0f;
	}
}

//================================================
//�K�E�Z����
//================================================
void CPlayer::Special(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//�p�b�hD�擾����
	CInputPadD *pInputPadD;
	pInputPadD = CManager::GetInstance()->GetInputPadD();

	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�J�����̃|�C���^�z��1�Ԗڂ̃A�h���X�擾
	CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
	//camera�̎擾
	CCamera* pCamera = &**pCameraAddress;

	//R2L2�����Ƀ{�^�����������Ƃ��܂���SPACE�L�[���������Ƃ��̏���
	if (((pInputPadD->GetPress(CInputPadD::R2) == true && pInputPadD->GetTrigger(CInputPadD::L2) == true) ||
		(pInputPadD->GetTrigger(CInputPadD::R2) == true && pInputPadD->GetPress(CInputPadD::L2) == true)) ||
		 pInputKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		//SP�Q�[�W��MAX�̎�����MP�Q�[�W������̒l�ȏ゠��Ƃ�
		if (CManager::GetInstance()->GetPlayData()->GetSpGauge()->GetGauge() == CManager::GetInstance()->GetPlayData()->GetSpGauge()->GetMaxNum() &&
			CManager::GetInstance()->GetPlayData()->GetMpGauge()->GetGauge() >= PLAYER_SP_COST_MP)
		{
			if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL ||	//�j���[�g�������[�V�����̎�
				m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_MOVE)		//�ړ����[�V�����̎�
			{
				//�K�E�Z���[�V�����ɂ���
				m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_SPECIAL, this);
				//�J�����̏�Ԃ��������h��ɂ���
				pCamera->SetState(CCamera::CAMERA_STATE::SWAY_SMALL);
				//���G��Ԃɂ���
				m_state = PLAYER_STATE::INVINCIBLE;
				//�ړ��ʂ�0�ɂ���
				m_move.x = 0.0f;
				m_move.z = 0.0f;
				//SP�Q�[�W��0�ɂ���
				CManager::GetInstance()->GetPlayData()->GetSpGauge()->SetGauge(0);
				//MP�Q�[�W�����炷
				CManager::GetInstance()->GetPlayData()->GetMpGauge()->AddGauge(-PLAYER_SP_COST_MP);
				//�K�E�Z�����Ă����Ԃɂ���
				m_bSpecial = true;

				//SE�Đ�
				pSound->Play(CSound::SOUND_LABEL_MAGIC_CIRCLE_SE);
				//�T�E���h�̉��ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_MAGIC_CIRCLE_SE, 1.8f);

				//SE�Đ�
				pSound->Play(CSound::SOUND_LABEL_EARTH_QUAKE_01_SE);
				//�T�E���h�̉��ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_EARTH_QUAKE_01_SE, 2.8f);
			}
		}

		//SP������Ȃ��Ƃ�
		if (CManager::GetInstance()->GetPlayData()->GetSpGauge()->GetGauge() != CManager::GetInstance()->GetPlayData()->GetSpGauge()->GetMaxNum())
		{
			//UI���o��
			CUi::Create(D3DXVECTOR3(GAUGE_SP_POS_X, GAUGE_SP_POS_Y, 0.0f), D3DXVECTOR3(UI_CROSS_SIZE, UI_CROSS_SIZE, 0.0f),
				        PRIORITY_UI, CUi::TYPE::CROSS);
			//SE�Đ�
			pSound->Play(CSound::SOUND_LABEL_POOR_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_POOR_SE, 1.4f);
		}
		//MP������Ȃ��Ƃ�
		if (CManager::GetInstance()->GetPlayData()->GetMpGauge()->GetGauge() < PLAYER_SP_COST_MP)
		{
			//UI���o��
			CUi::Create(D3DXVECTOR3(GAUGE_MP_POS_X, GAUGE_MP_POS_Y, 0.0f), D3DXVECTOR3(UI_CROSS_SIZE, UI_CROSS_SIZE, 0.0f),
				        PRIORITY_UI, CUi::TYPE::CROSS);
			//SE�Đ�
			pSound->Play(CSound::SOUND_LABEL_POOR_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_POOR_SE, 1.4f);
		}
	}

	//�K�E�Z���[�V�����̎�
	if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SPECIAL && m_pMotionPlayer->GetConnect() == false)
	{
		//�L�[��0�̎�
		if (m_pMotionPlayer->GetKey() == 0)
		{
			//����΂���
			m_move.y = 3.0f;
			//����̒l�ȏ�ɂȂ�����
			if (pCamera->GetDiffer() > CAMERA_DISTANCE_SPECIAL)
			{
				pCamera->SetDiffer(CAMERA_DISTANCE_SPECIAL);
			}
			else
			{//����̒l�����������Ƃ�
				//�J�����������Ă���
				pCamera->AddDiffer(4.0f);
			}
		}
		else if (m_pMotionPlayer->GetKey() < 5)
		{//�L�[��5��菬�����Ƃ�
			//�~�߂�
			m_move.y = 0.0f;
		}
		else if (m_pMotionPlayer->GetKey() >= 5)
		{//�L�[��5�ȏ�̎�
			//����̒l�ȉ��ɂȂ�����
			if (pCamera->GetDiffer() <= CAMERA_DISTANCE)
			{
				pCamera->SetDiffer(CAMERA_DISTANCE);
			}
			else
			{//����̒l�����傫���Ƃ�
			 //�J�������񂹂�
				pCamera->AddDiffer(-6.0f);
			}
		}

		//�L�[��1�ɂȂ����u��
		if (m_pMotionPlayer->GetKey() == 1 && m_pMotionPlayer->GetFrame() == 0 && m_pMotionPlayer->GetConnect() == false)
		{
			//�����@���o��
			CMagicThunder::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 150.0f, m_pos.z));

			//SE�Đ�
			pSound->Play(CSound::SOUND_LABEL_THUNDER_01_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_THUNDER_01_SE, 1.5f);
		}
		else if (m_pMotionPlayer->GetKey() == 2 && m_pMotionPlayer->GetFrame() == 0)
		{//�L�[��2�ɂȂ����u��
			//�J�����̏�Ԃ�傫���h��ɂ���
			pCamera->SetState(CCamera::CAMERA_STATE::SWAY_LARGE);

			//SE�Đ�
			pSound->Play(CSound::SOUND_LABEL_EARTH_QUAKE_02_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_EARTH_QUAKE_02_SE, 1.5f);
		}
		else if (m_pMotionPlayer->GetKey() == 3 && m_pMotionPlayer->GetFrame() == 0)
		{//�L�[��2�ɂȂ����u��
		 //�J�����̏�Ԃ�傫���h��ɂ���
			pCamera->SetState(CCamera::CAMERA_STATE::SWAY_LARGE);

			//SE�Đ�
			pSound->Play(CSound::SOUND_LABEL_THUNDER_02_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_THUNDER_02_SE, 1.5f);
		}
		else if(m_pMotionPlayer->GetKey() == 5 && m_pMotionPlayer->GetFrame() == 0)
		{//�L�[��5�ɂȂ����u��
			//�J�����̏�Ԃ�ʏ�ɂ���
			pCamera->SetState(CCamera::CAMERA_STATE::NORMAL);
			//�ʏ��Ԃɂ���
			m_state = PLAYER_STATE::NORMAL;
			//�K�E�Z�����Ă��Ȃ���Ԃɂ���
			m_bSpecial = false;
		}
	}
}

//================================================
//���@�U������
//================================================
void CPlayer::Magic(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//�p�b�hD�擾����
	CInputPadD *pInputPadD;
	pInputPadD = CManager::GetInstance()->GetInputPadD();

	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//Y�{�^�����������Ƃ��܂���Q�L�[���������Ƃ��̏���
	if (pInputPadD->GetTrigger(CInputPadD::Y) == true || pInputKeyboard->GetTrigger(DIK_Q) == true)
	{
		//MP�Q�[�W������̒l�ȏ゠��Ƃ�
		if (CManager::GetInstance()->GetPlayData()->GetMpGauge()->GetGauge() >= PLAYER_MAGIC_FIRE_COST_MP)
		{

			if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL ||	//�j���[�g�������[�V�����̎�
				m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_MOVE)		//�ړ����[�V�����̎�
			{
				//���@�U��1���[�V�����ɂ���
				m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_MAGIC_01, this);
				//�ړ��ʂ�0�ɂ���
				m_move.x = 0.0f;
				m_move.z = 0.0f;
				//MP�Q�[�W�����炷
				CManager::GetInstance()->GetPlayData()->GetMpGauge()->AddGauge(-PLAYER_MAGIC_FIRE_COST_MP);
			}
		}
		else
		{//MP������Ȃ��Ƃ�
			//SE�Đ�
			pSound->Play(CSound::SOUND_LABEL_POOR_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_POOR_SE, 1.4f);

			//UI���o��
			CUi::Create(D3DXVECTOR3(GAUGE_MP_POS_X, GAUGE_MP_POS_Y, 0.0f), D3DXVECTOR3(UI_CROSS_SIZE, UI_CROSS_SIZE, 0.0f),
				        PRIORITY_UI, CUi::TYPE::CROSS);
		}
	}

	//���@�U��1���[�V�����̎�
	if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_MAGIC_01 && m_pMotionPlayer->GetConnect() == false)
	{
		//�L�[��1�ɂȂ����u��
		if (m_pMotionPlayer->GetKey() == 1 && m_pMotionPlayer->GetFrame() == 0 && m_pMotionPlayer->GetConnect() == false)
		{
			//�����@���o��
			CMagicFire::Create(D3DXVECTOR3(m_pos.x + sinf(m_rot.y - D3DX_PI) * PLAYER_MAGIC_01_POS,
				                           m_pos.y + PLAYER_MAGIC_01_POS_Y,
				                           m_pos.z + cosf(m_rot.y - D3DX_PI) * PLAYER_MAGIC_01_POS), m_rot);
		}
	}
}

//================================================
//�K�[�h����
//================================================
void CPlayer::Guard(void)
{
	//�p�b�hD�擾����
	CInputPadD *pInputPadD;
	pInputPadD = CManager::GetInstance()->GetInputPadD();

	//�}�E�X�擾����
	CInputMouse *pInputMouse;
	pInputMouse = CManager::GetInstance()->GetInputMouse();

	//L�{�^�����������Ƃ��܂��͍��N���b�N�������Ƃ��̏���
	if (pInputPadD->GetPress(CInputPadD::L) == true || pInputMouse->GetPress(CInputMouse::MOUSE_TYPE_RIGHT) == true)
	{
		if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL ||	//�j���[�g�������[�V�����̎�
			m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_MOVE)		//�ړ����[�V�����̎�
		{
			//�K�[�h���[�V��������Ȃ�������
			if (m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_GUARD)
			{
				//�K�[�h���[�V�����ɂ���
				m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_GUARD, this);

				//�K�[�h���Ă��Ȃ���ԂȂ�
				if (m_bGuard == false)
				{
					//�K�[�h���Ă����Ԃɂ���
					m_bGuard = true;
				}
			}
			//�ړ��ʂ�0�ɂ���
			m_move.x = 0.0f;
			m_move.z = 0.0f;
		}
	}
	else
	{
		//�K�[�h���[�V������������
		if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_GUARD)
		{
			//�j���[�g�������[�V�����ɂ���
			m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL, this);
			//�ʏ��Ԃɂ���
			m_state = PLAYER_STATE::NORMAL;
			//�K�[�h���Ă��Ȃ���Ԃɂ���
			m_bGuard = false;
		}
	}
}

//================================================
//��Ԃɂ�鏈������
//================================================
void CPlayer::State(void)
{
	//���݂̏�Ԃɂ���ď����𕪂���
	switch (m_state)
	{
	case PLAYER_STATE::NORMAL:			//�ʏ�
		//���U������
		Slash();

		//�K�E�Z����
		Special();

		//���@�U������
		Magic();

		//�K�[�h����
		Guard();

		if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL ||	//�j���[�g�������[�V�����̎�
			m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_MOVE)		//�ړ����[�V�����̎�
		{
			//�ړ�����
			Move();
		}

		break;
	case PLAYER_STATE::DAMAGE:			//�_���[�W
		//�J�E���^�[�����Z
		m_nInvincibleCounter++;
		//�K��l�ȏ�ɂȂ�����
		if (m_nInvincibleCounter >= PLAYER_INVINCIBLE_COUNT)
		{
			//0�ɂ���
			m_nInvincibleCounter = 0;
			//�ʏ��Ԃɂ���
			m_state = PLAYER_STATE::NORMAL;
		}

		//���U������
		Slash();

		//�K�E�Z����
		Special();

		//���@�U������
		Magic();

		//�K�[�h����
		Guard();

		if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL ||	//�j���[�g�������[�V�����̎�
			m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_MOVE)		//�ړ����[�V�����̎�
		{
			//�ړ�����
			Move();
		}
		break;
	case PLAYER_STATE::INVINCIBLE:		//���G
		//���U������
		Slash();

		//�K�E�Z����
		Special();

		//���@�U������
		Magic();

		//�K�[�h����
		Guard();

		if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL ||	//�j���[�g�������[�V�����̎�
			m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_MOVE)		//�ړ����[�V�����̎�
		{
			//�ړ�����
			Move();
		}
		break;
	default:
		break;
	}
}

//================================================
//���b�N�I������
//================================================
void CPlayer::LockOn(void)
{
	//�p�b�hD�擾����
	CInputPadD *pInputPadD;
	pInputPadD = CManager::GetInstance()->GetInputPadD();

	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//R�{�^���܂���R�L�[���������Ƃ��̏���
	if (pInputPadD->GetTrigger(CInputPadD::R) == true || pInputKeyboard->GetTrigger(DIK_R) == true)
	{
		//���b�N�I����ԂłȂ��Ƃ�
		if (m_bLockOn == false)
		{
			//�I�u�W�F�N�g��������|�C���^
			CObject *pObject = nullptr;
			//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
			CObject *pSaveObject = nullptr;

			//�擪�̃|�C���^����
			pObject = pObject->GetTopObj(CObject::PRIORITY_ENEMY);

			//�v���C���[�Ƃ̋����ۑ��p
			float fDiffer = 100000.0f;

			while (pObject != nullptr)
			{
				//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
				pSaveObject = pObject;

				//�I�u�W�F�N�g�̎�ނ��G��������
				if (pObject->GetObjType() == CObject::OBJTYPE::ENEMY_FAT ||
					pObject->GetObjType() == CObject::OBJTYPE::ENEMY_BEE ||
					pObject->GetObjType() == CObject::OBJTYPE::ENEMY_BOSS)
				{
					//�G�ɃL���X�g
					CEnemy *pEnemyObj = nullptr;
					pEnemyObj = (CEnemy*)pObject;

					//�G���`�悳��Ă����Ԃ�������
					if (pEnemyObj->GetDraw() == true)
					{
						//�I�u�W�F�N�g�̈ʒu���擾
						D3DXVECTOR3 posObj = pEnemyObj->GetPos();

						//���g����Ώۂ̃I�u�W�F�N�g�܂ł̋��������߂�
						float fRadius = sqrtf((m_pos.x - posObj.x) * (m_pos.x - posObj.x) +
							                  (m_pos.z - posObj.z) * (m_pos.z - posObj.z));

						//�������r���ĕۑ����Ă�����̂�菬����������
						if (fRadius < fDiffer)
						{
							//�㏑������
							fDiffer = fRadius;
							//�|�C���^��ۑ�
							m_pEnemyNear = pEnemyObj;
						}
					}
				}
				//���̃I�u�W�F�N�g�ɐi�߂�
				pObject = pSaveObject->GetObjNext(pSaveObject);
			}

			if (m_pEnemyNear != nullptr)
			{
				//���b�N�I����Ԃɂ���
				m_bLockOn = true;

				//��ԋ߂��̓G�̈ʒu�擾
				D3DXVECTOR3 posEnemy = m_pEnemyNear->GetPos();
				//�v���C���[�Ƃ̊p�x�����߂�
				m_fLockOnObjectiveRot = atan2((posEnemy.x - m_pos.x), (posEnemy.z - m_pos.z)) - D3DX_PI;
				if (m_pLockOn == nullptr)
				{
					//���b�N�I��UI���o��
					m_pLockOn = CBillboard::Create(D3DXVECTOR3(posEnemy.x + sinf(m_fLockOnObjectiveRot) * PLAYER_LOCK_ON_UI_POS,
						                                       posEnemy.y + PLAYER_LOCK_ON_UI_POS,
						                                       posEnemy.z + cosf(m_fLockOnObjectiveRot) * PLAYER_LOCK_ON_UI_POS),
						                           D3DXVECTOR3(PLAYER_LOCK_ON_UI_SIZE, PLAYER_LOCK_ON_UI_SIZE, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					//�e�N�X�`����ݒ�
					m_pLockOn->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_LOCK_ON"));
					//�v���C�I���e�B��ݒ�
					m_pLockOn->SetPriority(CObject::PRIORITY_LOCK_ON);
					//���e�X�g���s���ݒ�
					m_pLockOn->SetAlphaTest(true);
					//���C�e�B���O�𖳌��ɂ���
					m_pLockOn->SetLighting(false);
				}
			}
		}
		else
		{//���b�N�I����Ԃ̎�
			//�J�����̃|�C���^�z��1�Ԗڂ̃A�h���X�擾
			CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
			//camera�̎擾
			CCamera* pCamera = &**pCameraAddress;

			//���b�N�I����������
			m_bLockOn = false;

			//UI������
			if (m_pLockOn != nullptr)
			{
				m_pLockOn->Uninit();
				m_pLockOn = nullptr;
			}

			//��]���~�߂�
			m_bRotate = false;
			//�J�����̉�]���~�߂�
			pCamera->SetRotateX(false);
			pCamera->SetRotateY(false);

			//nullptr�ɂ���
			m_pEnemyNear = nullptr;
		}
	}

	//���b�N�I����Ԃ̂Ƃ�
	if (m_bLockOn == true)
	{
		if (m_pEnemyNear != nullptr)
		{
			//�J�����̃|�C���^�z��1�Ԗڂ̃A�h���X�擾
			CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
			//camera�̎擾
			CCamera* pCamera = &**pCameraAddress;

			//��ԋ߂��̓G�̈ʒu�擾
			D3DXVECTOR3 posEnemy = m_pEnemyNear->GetPos();
			//�v���C���[�Ƃ̊p�x�����߂�
			m_fLockOnObjectiveRot = atan2((posEnemy.x - m_pos.x), (posEnemy.z - m_pos.z)) - D3DX_PI;
			//�v���C���[�̖ړI�̌�����ݒ�
			m_fObjectiveRot = m_fLockOnObjectiveRot;
			//��]��������
			m_bRotate = true;
			//�J�����̖ړI�̌�����ݒ�
			pCamera->SetRotAsk(D3DXVECTOR3(CAMERA_ROCK_ON_ROT_X, m_fLockOnObjectiveRot, 0.0f));
			//��]������
			pCamera->SetRotateX(true);
			pCamera->SetRotateY(true);

			//���b�N�I��UI�̈ʒu�ƃT�C�Y�擾
			D3DXVECTOR3 posLockOn = m_pLockOn->GetPos();
			D3DXVECTOR3 sizeLockOn = m_pLockOn->GetSize();
			posLockOn = D3DXVECTOR3(posEnemy.x + sinf(m_fLockOnObjectiveRot) * PLAYER_LOCK_ON_UI_POS,
				                    posEnemy.y + PLAYER_LOCK_ON_UI_POS,
				                    posEnemy.z + cosf(m_fLockOnObjectiveRot) * PLAYER_LOCK_ON_UI_POS);
			//�ʒu�ݒ�
			m_pLockOn->SetPos(posLockOn, sizeLockOn);
		}
		else
		{
			//�J�����̃|�C���^�z��1�Ԗڂ̃A�h���X�擾
			CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
			//camera�̎擾
			CCamera* pCamera = &**pCameraAddress;

			//���b�N�I����������
			m_bLockOn = false;

			//UI������
			if (m_pLockOn != nullptr)
			{
				m_pLockOn->Uninit();
				m_pLockOn = nullptr;
			}

			//��]���~�߂�
			m_bRotate = false;
			//�J�����̉�]���~�߂�
			pCamera->SetRotateX(false);
			pCamera->SetRotateY(false);
		}
	}
}

//================================================
//�v���C���[�Ƃ̓����蔻��
//================================================
void CPlayer::Collision(CObject *pSubjectObject, float fObjRadius)
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

			//�K�E�Z�����Ă��Ȃ��Ƃ�
			if (pPlayerObj->m_bSpecial == false)
			{
				//�I�u�W�F�N�g�̈ʒu���擾
				D3DXVECTOR3 posObj = pSubjectObject->GetPos();

				//�v���C���[����Ώۂ̃I�u�W�F�N�g�܂ł̋��������߂�
				float fRadius = sqrtf((posObj.x - pPlayerObj->m_pos.x) * (posObj.x - pPlayerObj->m_pos.x) +
					                  (posObj.z - pPlayerObj->m_pos.z) * (posObj.z - pPlayerObj->m_pos.z));
				//�v���C���[�ƑΏۂ̃I�u�W�F�N�g�̊p�x�����߂�
				float fRot = atan2((posObj.x - pPlayerObj->m_pos.x), (posObj.z - pPlayerObj->m_pos.z)) - D3DX_PI;

				//���߂��������v���C���[�̔��a�ƑΏۂ̃I�u�W�F�N�g�̔��a�𑫂������l�ȉ���������
				if (fRadius <= pPlayerObj->m_size.x / 2.0f + fObjRadius)
				{
					//�v���C���[�̈ʒu�������o��
					pPlayerObj->m_pos.x = posObj.x + (sinf(fRot) * (pPlayerObj->m_size.x / 2.0f + fObjRadius));
					pPlayerObj->m_pos.z = posObj.z + (cosf(fRot) * (pPlayerObj->m_size.x / 2.0f + fObjRadius));

					//�ʒu�ݒ�
					pPlayerObj->SetPos(pPlayerObj->m_pos);

					//���f���Ƃ̓����蔻��
					CModelSingle::Collision(pPlayerObj);
				}
			}
		}
		//���̃I�u�W�F�N�g�ɐi�߂�
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//================================================
//�v���C���[�Ƃ̏Փ˔���݂̂̏���
//================================================
bool CPlayer::CollisionOnly(CObject * pSubjectObject, float fObjRadius)
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
