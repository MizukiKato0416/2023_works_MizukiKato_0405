//=============================================================================
// �R���g���[���v���C���[���� [control_player.cpp]
// Author : ��������
//=============================================================================
#include "control_player.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "player.h"
#include "camera.h"
#include "game01.h"
#include "2Danimation_jump.h"
#include "motion_player.h"
#include "sound.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CControlPlayer::CControlPlayer()
{
	m_speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_nDiveTime = 0;
	m_bStop = false;
	m_bDive = false;
	m_bJump = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CControlPlayer::~CControlPlayer()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CControlPlayer::Init(void)
{
	m_speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_nDiveTime = 0;
	m_bStop = false;
	m_bDive = false;
	m_bJump = false;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CControlPlayer::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CControlPlayer::Update(CScene *pScene)
{
	//�����̃|�C���^��Ui�N���X�̃|�C���^�ɃL���X�g
	CPlayer *pPlayer = NULL;
	pPlayer = (CPlayer*)pScene;

	//�Q�[�����̎�
	if (CManager::GetGame01() != NULL)
	{
		//�Q�[���X�^�[�g��ԂłȂ�������
		if (CManager::GetGame01()->GetGame() == false)
		{
			//�����Ȃ���Ԃɂ���
			m_bStop = true;
		}
		else
		{
			//������悤�ɂ���
			m_bStop = false;
		}
	}
	else if (CManager::GetResult() != NULL)
	{
		//�����Ȃ���Ԃɂ���
		m_bStop = true;
	}

	//���[�V�����擾����
	CMotionPlayer *pMotionPlayer = NULL;
	pMotionPlayer = pPlayer->GetMotionPlayer();

	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�p�b�h�擾����
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	D3DXVECTOR3 rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//camera�̃|�C���^�z��1�Ԗڂ̃A�h���X�擾
	CCamera **pCameraAddress = CManager::GetCamera();

	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++, pCameraAddress++)
	{
		//camera�̎擾
		CCamera *pCamera = &**pCameraAddress;
		if (pCamera != NULL)
		{
			if (pPlayer->GetNum() == pCamera->GetNum())
			{
				//camera�̌����擾
				rotCamera = pCamera->GetRotV();
			}
		}
	}
	m_move = pPlayer->GetMove();
	m_moveOld = m_move;

	//�d��
	m_move.y -= PLAYER_GRAVITY;

	//�J�E���g�_�E�����͓����Ȃ�����
	if (m_bStop == false)
	{
		//�ړ�����
		Move(pPlayer);
	}

	//�ړ��̊����ɂ��Ă̏���
	MoveInteria(pPlayer);

	//���̃t���[���~�܂��Ă���Ƃ����ړ����[�V���������[�V�������Ȃ��Ă��Ȃ�������
	if (m_move.x == 0.0f && m_move.z == 0.0f &&
		pPlayer->GetMotionPlayer()->GetMotion() == CMotionPlayer::MOTION_PLAYER_TYPE_MOVE &&
		pPlayer->GetMotionPlayer()->GetConnect() == false)
	{
		//�j���[�g�������[�V�����ɂ���
		pPlayer->GetMotionPlayer()->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_NEUTRAL);
	}

	//�O�̃t���[���~�܂��Ă��č������Ă���Ƃ����W�����v���[�V��������Ȃ����_�C�u���[�V�����łȂ��Ƃ�
	if (((m_moveOld.x == 0.0f && m_move.x != 0.0f) || (m_moveOld.z == 0.0f && m_move.z != 0.0f)) &&
		pPlayer->GetMotionPlayer()->GetMotion() != CMotionPlayer::MOTION_PLAYER_TYPE_JUMP &&
		pPlayer->GetMotionPlayer()->GetMotion() != CMotionPlayer::MOTION_PLAYER_TYPE_DIVE)
	{
		//�ړ����[�V�����ɂ���
		pPlayer->GetMotionPlayer()->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_MOVE);
	}

	//�_�C�u�̏���
	Dive(pPlayer);

	//��]�̊���
	Rotate(pPlayer);

	//�W�����v����
	Jump(pPlayer);
}

//================================================
//��������
//================================================
CControlPlayer *CControlPlayer::Create(void)
{
	//�C���X�^���X�̐���
	CControlPlayer *pControlPlayer = NULL;
	if (pControlPlayer == NULL)
	{
		pControlPlayer = new CControlPlayer;
		if (pControlPlayer != NULL)
		{

			pControlPlayer->Init();
		}
	}
	return pControlPlayer;
}

//================================================
//�ړ�����
//================================================
void CControlPlayer::Move(CPlayer *pPlayer)
{
	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�p�b�h�擾����
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	D3DXVECTOR3 rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//camera�̃|�C���^�z��1�Ԗڂ̃A�h���X�擾
	CCamera **pCameraAddress = CManager::GetCamera();

	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++, pCameraAddress++)
	{
		//camera�̎擾
		CCamera *pCamera = &**pCameraAddress;
		if (pCamera != NULL)
		{
			if (pPlayer->GetNum() == pCamera->GetNum())
			{
				//camera�̌����擾
				rotCamera = pCamera->GetRotV();
			}
		}
	}

	//�v���C���[�̌̎��ʔԍ��擾����
	int nNumPlayer = pPlayer->GetNum();

	//�ʏ�ړ��̉����x
	float fSpeed;

	//�X�̏�ɏ������
	if (pPlayer->GetOnIce() == true)
	{
		fSpeed = PLAYER_MOVE_SPEED_ON_ICE;

		if (pPlayer->GetDive() == true)
		{
			//�_�C�u���̉����x
			fSpeed = PLAYER_DIVE_SPEED_ON_ICE;
		}

	}
	//����ȊO�͒ʏ�̃X�s�[�h�⊵���ɖ߂�
	else
	{
		fSpeed = PLAYER_MOVE_SPEED;

		if (pPlayer->GetDive() == true)
		{
			//�_�C�u���̉����x
			fSpeed = PLAYER_DIVE_SPEED;
		}
	}

	//�_�C�u���n���[�V����������Ȃ�������
	if (pPlayer->GetMotionPlayer()->GetMotion() != CMotionPlayer::MOTION_PLAYER_TYPE_DIVE_LAND)
	{
		//***********************************************************************
		// �ړ�
		//***********************************************************************
		if (pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_UP, nNumPlayer) == true ||
			(pInputKeyboard->GetPress(DIK_W) == true && nNumPlayer == 0))								
		{//���X�e�B�b�N����ɓ|�����Ƃ��܂���w���������Ƃ��̏���
			if (pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_LEFT, nNumPlayer) == true ||
				(pInputKeyboard->GetPress(DIK_A) == true && nNumPlayer == 0))
			{//���X�e�B�b�N�����ɓ|�����Ƃ��܂���a���������Ƃ��̏����̏���
				//�ړ��ʉ��Z
				m_move.x += +cosf(rotCamera.y + D3DX_PI / 4.0f) * fSpeed;
				m_move.z += -sinf(rotCamera.y + D3DX_PI / 4.0f) * fSpeed;

				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y - D3DX_PI / 4.0f;
				//��]�̊������I���ɂ���
				m_bRotate = true;
			}
			else if (pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_RIGHT, nNumPlayer) == true ||
				(pInputKeyboard->GetPress(DIK_D) == true && nNumPlayer == 0))
			{//���X�e�B�b�N���E�ɓ|�����Ƃ��܂���d���������Ƃ��̏����̏���
				//�ړ��ʉ��Z
				m_move.x += -cosf(rotCamera.y - D3DX_PI / 4.0f) * fSpeed;
				m_move.z += +sinf(rotCamera.y - D3DX_PI / 4.0f) * fSpeed;

				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y + D3DX_PI / 4.0f;
				//��]�̊������I���ɂ���
				m_bRotate = true;
			}
			else
			{
				//�ړ��ʉ��Z
				m_move.z += -cosf(rotCamera.y) * fSpeed;
				m_move.x += -sinf(rotCamera.y) * fSpeed;

				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y;
				//��]�̊������I���ɂ���
				m_bRotate = true;
			}

		}
		else if (pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_DOWN, nNumPlayer) == true ||
			(pInputKeyboard->GetPress(DIK_S) == true && nNumPlayer == 0))			
		{//���X�e�B�b�N�����ɓ|�����Ƃ��܂���s���������Ƃ��̏����̏����̏���
			if (pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_LEFT, nNumPlayer) == true ||
				(pInputKeyboard->GetPress(DIK_A) == true && nNumPlayer == 0))			
			{//���X�e�B�b�N�����ɓ|�����Ƃ��܂���a���������Ƃ��̏����̏����̏���
				//�ړ��ʉ��Z
				m_move.x += +cosf(rotCamera.y - D3DX_PI / 4.0f) * fSpeed;
				m_move.z += -sinf(rotCamera.y - D3DX_PI / 4.0f) * fSpeed;

				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y - (D3DX_PI / 4.0f) * 3.0f;
				//��]�̊������I���ɂ���
				m_bRotate = true;
			}
			else if (pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_RIGHT, nNumPlayer) == true ||
				(pInputKeyboard->GetPress(DIK_D) == true && nNumPlayer == 0))		
			{//���X�e�B�b�N���E�ɓ|�����Ƃ��܂���d���������Ƃ��̏����̏����̏���
				//�ړ��ʉ��Z
				m_move.x += -cosf(rotCamera.y + D3DX_PI / 4.0f) * fSpeed;
				m_move.z += +sinf(rotCamera.y + D3DX_PI / 4.0f) * fSpeed;

				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y + D3DX_PI / 1.5f;
				//��]�̊������I���ɂ���
				m_bRotate = true;
			}
			else
			{
				//�ړ��ʉ��Z
				m_move.z += +cosf(rotCamera.y) * fSpeed;
				m_move.x += +sinf(rotCamera.y) * fSpeed;

				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y + D3DX_PI;
				//��]�̊������I���ɂ���
				m_bRotate = true;
			}
		}
		else if (pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_LEFT, nNumPlayer) == true ||
			(pInputKeyboard->GetPress(DIK_A) == true && nNumPlayer == 0))			
		{//���X�e�B�b�N�����ɓ|�����Ƃ��܂���a���������Ƃ��̏����̏����̏���
			//�ړ��ʉ��Z
			m_move.x += +cosf(rotCamera.y) * fSpeed;
			m_move.z += -sinf(rotCamera.y) * fSpeed;

			//�ړI�̌�����ݒ�
			m_fObjectiveRot = rotCamera.y - D3DX_PI / 2.0f;
			//��]�̊������I���ɂ���
			m_bRotate = true;
		}
		else if (pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_RIGHT, nNumPlayer) == true ||
			(pInputKeyboard->GetPress(DIK_D) == true && nNumPlayer == 0))		
		{//���X�e�B�b�N���E�ɓ|�����Ƃ��܂���d���������Ƃ��̏����̏����̏���
			//�ړ��ʉ��Z
			m_move.x += -cosf(rotCamera.y) * fSpeed;
			m_move.z += +sinf(rotCamera.y) * fSpeed;

			//�ړI�̌�����ݒ�
			m_fObjectiveRot = rotCamera.y + D3DX_PI / 2.0f;
			//��]�̊������I���ɂ���
			m_bRotate = true;
		}
	}
}

//================================================
//�ړ��̊����ɂ��Ă̏���
//================================================
void CControlPlayer::MoveInteria(CPlayer *pPlayer)
{
	//�v���C���[���X�̏�ɏ���Ă�����
	if (pPlayer->GetOnIce() == true)
	{
		// ������0�ɂȂ�܂Ŗ߂�
		m_move.z *= PLAYER_INTERIA_SUBTRACTION_ON_ICE;
		m_move.x *= PLAYER_INTERIA_SUBTRACTION_ON_ICE;
	}
	else	//����Ă��Ȃ�������
	{
		// ������0�ɂȂ�܂Ŗ߂�
		m_move.z *= PLAYER_INTERIA_SUBTRACTION;
		m_move.x *= PLAYER_INTERIA_SUBTRACTION;
	}

	//�ړ��ʂ�����̒l�ɂȂ�����0�ɂ���
	if (m_move.x <= PLAYER_MOVE_STOP_COUNT && m_move.x >= -PLAYER_MOVE_STOP_COUNT)
	{
		m_move.x = 0.0f;
	}
	if (m_move.z <= PLAYER_MOVE_STOP_COUNT && m_move.z >= -PLAYER_MOVE_STOP_COUNT)
	{
		m_move.z = 0.0f;
	}
}

//================================================
//��]����
//================================================
void CControlPlayer::Rotate(CPlayer *pPlayer)
{
	//�v���C���[�̌����擾����
	D3DXVECTOR3 rotPlayer = pPlayer->GetRot();

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
		if (rotPlayer.y < 0.0f && -rotPlayer.y + m_fObjectiveRot > D3DX_PI)
		{
			m_fNumRot = (-D3DX_PI - rotPlayer.y) + -(D3DX_PI - m_fObjectiveRot);
		}
		else if (rotPlayer.y >= D3DX_PI / 2.0f && rotPlayer.y - m_fObjectiveRot > D3DX_PI)
		{
			m_fNumRot = (D3DX_PI - rotPlayer.y) - (-D3DX_PI - m_fObjectiveRot);
		}
		else
		{
			m_fNumRot = (m_fObjectiveRot - rotPlayer.y);
		}

		//�v���C���[�̌����ɉ��Z
		rotPlayer.y += m_fNumRot * 0.2f;

		//����̒l�ɒB�������]����߂�
		if (rotPlayer.y - m_fObjectiveRot < 0.001 && rotPlayer.y - m_fObjectiveRot > -0.001)
		{
			m_bRotate = false;
		}
	}

	//�΂��傫���Ȃ�����-2�΂���
	if (rotPlayer.y > D3DX_PI)
	{
		rotPlayer.y -= D3DX_PI * 2.0f;
	}
	else if (rotPlayer.y < -D3DX_PI)
	{	//-�΂�菬�����Ȃ�����+2�΂���
		rotPlayer.y += D3DX_PI * 2.0f;
	}

	//�����𔽉f
	pPlayer->SetRot(rotPlayer);
}

//================================================
//�_�C�u����
//================================================
void CControlPlayer::Dive(CPlayer *pPlayer)
{
	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�p�b�h�擾����
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//���[�V�����擾����
	CMotionPlayer *pMotionPlayer = NULL;
	pMotionPlayer = pPlayer->GetMotionPlayer();

	//�v���C���[�̌̎��ʔԍ��擾����
	int nNumPlayer = pPlayer->GetNum();

	//�v���C���[���~�܂��Ă��Ԃł͂Ȃ��Ƃ�
	if (m_bStop == false)
	{
		//�W�����v���Ă�����
		if (pPlayer->GetJump() == true)
		{
			if (pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B, nNumPlayer) == true ||
				(pInputKeyboard->GetTrigger(DIK_SPACE) == true && nNumPlayer == 0))
			{	//B�{�^�����������Ƃ��܂���SPACE���������Ƃ��̏����̏����̏���
				//�W�����v��Ԃ̎�
				if (m_bJump == true)
				{
					//�_�C�u���Ă��Ȃ�������
					if (m_bDive == false)
					{
						//�T�E���h�擾����
						CSound *pSound;
						pSound = CManager::GetSound();

						//�_�C�uSE
						pSound->Play(CSound::SOUND_LABEL_DIVE_SE);

						//�_�C�u���[�V�����ɂ���
						pMotionPlayer->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_DIVE);
						//�_�C�u��Ԃɂ���
						pPlayer->SetDive(true);
						pPlayer->SetJump(false);
						m_bDive = true;
					}
				}
			}
		}
	}
	//�_�C�u��Ԃ̎�
	if (pPlayer->GetDive() == true)
	{
		//�J�E���g�𑝂₷
		m_nDiveTime++;

		//����̎��ԂɂȂ�����
		if (m_nDiveTime >= PLAYER_DIVE_COUNT)
		{
			m_nDiveTime = 0;
			//�_�C�u�����Ă��Ȃ���Ԃɂ���
			pPlayer->SetDive(false);
		}
	}
}

//================================================
//�W�����v����
//================================================
void CControlPlayer::Jump(CPlayer *pPlayer)
{
	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�p�b�h�擾����
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//���[�V�����擾����
	CMotionPlayer *pMotionPlayer = NULL;
	pMotionPlayer = pPlayer->GetMotionPlayer();

	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//�v���C���[�̌����擾����
	D3DXVECTOR3 rotPlayer = pPlayer->GetRot();

	//�v���C���[�̌̎��ʔԍ��擾����
	int nNumPlayer = pPlayer->GetNum();

	if (pPlayer->GetLand() == true)
	{
		m_move.y = 0.0f;

		if (CManager::GetResult() != NULL)
		{

		}
		else
		{
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			// �W�����v
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			if (pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_A, nNumPlayer) == true ||
				(pInputKeyboard->GetTrigger(DIK_SPACE) == true && nNumPlayer == 0))
			{	//A�{�^�����������Ƃ��܂���SPACE���������Ƃ��̏����̏����̏���
				if (pPlayer->GetMotionPlayer()->GetMotion() != CMotionPlayer::MOTION_PLAYER_TYPE_DIVE_LAND &&
					pPlayer->GetMotionPlayer()->GetMotion() != CMotionPlayer::MOTION_PLAYER_TYPE_DIVE)
				{
					//�W�����vSE
					pSound->Play(CSound::SOUND_LABEL_JUMP_SE);
					pSound->ControllVoice(CSound::SOUND_LABEL_JUMP_SE, 0.6f);

					//�W�����v���[�V�����ɂ���
					pMotionPlayer->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_JUMP);

					//�ړ��ʂ��W�����v�����Z
					m_move.y = PLAYER_JUMP;

					pPlayer->SetJump(true);
					pPlayer->SetLand(false);

					D3DXVECTOR3 pos = pPlayer->GetPos();

					C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y, m_rot.z), 0.8f);
					C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y + 3.14f, m_rot.z), 0.8f);
					C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y + 1.04f, m_rot.z), 0.8f);
					C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y - 1.04f, m_rot.z), 0.8f);
					C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y + 2.1f, m_rot.z), 0.8f);
					C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y - 2.1f, m_rot.z), 0.8f);

					m_bJump = true;
					m_bDive = false;
				}
			}
			//�o�l�ɏ������
			else if (pPlayer->GetOnSpring() == true)
			{
				//�W�����vSE
				pSound->Play(CSound::SOUND_LABEL_SPRING_SE);
				pSound->ControllVoice(CSound::SOUND_LABEL_SPRING_SE, 1.5f);

				//�W�����v���[�V�����ɂ���
				pMotionPlayer->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_JUMP);

				//�v���C���[�������Ă�������Ɉړ��ʂ����Z
				m_move.z += -cosf(rotPlayer.y) * PLAYER_MOVE_FORWARD_SPRING;
				m_move.x += -sinf(rotPlayer.y) * PLAYER_MOVE_FORWARD_SPRING;

				//�ړ��ʂ��W�����v�����Z
				m_move.y = PLAYER_JUMP_SPRING;

				pPlayer->SetJump(true);
				pPlayer->SetLand(false);

				D3DXVECTOR3 pos = pPlayer->GetPos();

				C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y, m_rot.z), 0.8f);
				C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y + 3.14f, m_rot.z), 0.8f);
				C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y + 1.04f, m_rot.z), 0.8f);
				C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y - 1.04f, m_rot.z), 0.8f);
				C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y + 2.1f, m_rot.z), 0.8f);
				C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y - 2.1f, m_rot.z), 0.8f);

				m_bJump = true;
				m_bDive = false;
			}
			else
			{
				m_bJump = false;
			}
		}
	}
}