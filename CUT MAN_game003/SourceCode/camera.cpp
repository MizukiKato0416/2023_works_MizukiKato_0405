//=======================================================================
//�J�����Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "pad.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
Camera g_camera[MAX_CAMERA];				//�J�����̏��
D3DXMATRIX g_mtxWorldCamera;		//���[���h�}�g���b�N�X
bool g_bTurn;

//=======================================================================
//����������
//=======================================================================
void InitCamera(void)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		//�ϐ�������
		g_camera[nCntCamera].rot.y = pPlayer->rot.y;											//�J�����̌���
		g_camera[nCntCamera].rotAsk = D3DXVECTOR3(0.0f,0.0f,0.0f);									//�J�����̌���
		g_camera[0].posV = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 140.0f + g_camera[0].ftest, pPlayer->pos.z - 400.0f);	//���݂̎��_
		g_camera[nCntCamera].posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//�ړI�̎��_
		g_camera[0].posR = D3DXVECTOR3(pPlayer->pos.x + sinf(g_camera[0].rot.y) * 80.0f, pPlayer->pos.y + 80.0f, pPlayer->pos.z + cosf(g_camera[0].rot.y) * 80.0f);	//���݂̒����_
		g_camera[nCntCamera].posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//�ړI�̒����_
		g_camera[nCntCamera].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);								//�@��
		g_camera[nCntCamera].ftest = 0.0f;														//�e�X�g�p
		g_camera[nCntCamera].rotDiffer = 0.0f;														//�e�X�g�p
		g_camera[nCntCamera].viewport.X = 0.0f;													//�`�悷���ʂ̍���X���W
		g_camera[nCntCamera].viewport.Y = 0.0f;													//�`�悷���ʂ̍���Y���W
		g_camera[nCntCamera].viewport.MinZ = 0.0f;
		g_camera[nCntCamera].viewport.MaxZ = 1.0f;
	}
	g_bTurn = false;
	g_camera[0].viewport.Width = SCREEN_WIDTH;										//�`�悷���ʂ̕�
	g_camera[0].viewport.Height = SCREEN_HEIGHT;									//�`�悷���ʂ̍���

	g_camera[1].viewport.Width = SCREEN_WIDTH * 0.1;										//�`�悷���ʂ̕�
	g_camera[1].viewport.Height = SCREEN_HEIGHT * 0.1;									//�`�悷���ʂ̍���
}

//=======================================================================
//�I������
//=======================================================================
void UninitCamera(void)
{

}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateCamera(void)
{


	//=======================================================================
	//�v���C���[�̃J�����ݒ�
	//=======================================================================
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	if (GetMode() == MODE_TITLE)
	{
		g_camera[0].posV = D3DXVECTOR3(1228.0f, 23.0f,-291.3f);	//���݂̎��_
		g_camera[0].posR = D3DXVECTOR3(941.0f, 80.0f, -205.0f);	//���݂̒����_
	}
	else if (GetMode() == MODE_STAGE1)
	{
	


		if(GetTriggerTrigger(TRIGGERTYPE_RIGHT) == true)
		{
			g_bTurn = true;
			g_camera[0].rotAsk.y = pPlayer->rot.y;
		}
		if (g_bTurn == true)
		{
			if (g_camera[0].rotAsk.y > D3DX_PI)
			{
				g_camera[0].rotAsk.y = -D3DX_PI - (D3DX_PI - g_camera[0].rotAsk.y);
			}
			else if (g_camera[0].rotAsk.y < -D3DX_PI)
			{
				g_camera[0].rotAsk.y = D3DX_PI - (-D3DX_PI - g_camera[0].rotAsk.y);
			}

			if (g_camera[0].rot.y < 0.0f && -g_camera[0].rot.y + g_camera[0].rotAsk.y > D3DX_PI)
			{
				g_camera[0].rotDiffer = (-D3DX_PI - g_camera[0].rot.y) + -(D3DX_PI - g_camera[0].rotAsk.y);
			}
			else if (g_camera[0].rot.y >= D3DX_PI / 2.0f && g_camera[0].rot.y - g_camera[0].rotAsk.y > D3DX_PI)
			{
				g_camera[0].rotDiffer = (D3DX_PI - g_camera[0].rot.y) - (-D3DX_PI - g_camera[0].rotAsk.y);
			}
			else
			{
				g_camera[0].rotDiffer = (g_camera[0].rotAsk.y - g_camera[0].rot.y);
			}

			g_camera[0].rot.y += g_camera[0].rotDiffer * 0.1f;
			if (g_camera[0].rot.y - g_camera[0].rotAsk.y < 0.01 && g_camera[0].rot.y - g_camera[0].rotAsk.y > -0.01)
			{
				g_bTurn = false;

			}
		}

		//============================================
		//�E�X�e�B�b�N����
		//============================================
		// �X�e�B�b�N�̍��������ꂽ
		if (GetRightStick(STICKTYPE_LEFT) == true && g_bTurn == false)
		{
			g_camera[0].rot.y -= CAMERA_R_SPEED;
			g_camera[0].posR.x = g_camera[0].posV.x + sinf(g_camera[0].rot.y) * CAMERA_DISTANCE;
			g_camera[0].posR.z = g_camera[0].posV.z + cosf(g_camera[0].rot.y) * CAMERA_DISTANCE;
			//g_bTurn = false;

		}
		// �X�e�B�b�N�̉E�������ꂽ
		else if (GetRightStick(STICKTYPE_RIGHT) == true && g_bTurn == false)
		{
			g_camera[0].rot.y += CAMERA_R_SPEED;
			g_camera[0].posR.x = g_camera[0].posV.x + sinf(g_camera[0].rot.y) * CAMERA_DISTANCE;
			g_camera[0].posR.z = g_camera[0].posV.z + cosf(g_camera[0].rot.y) * CAMERA_DISTANCE;
			//g_bTurn = false;

		}

		g_camera[0].posR = D3DXVECTOR3(pPlayer->pos.x + sinf(g_camera[0].rot.y) * 80.0f, pPlayer->pos.y + 80.0f, pPlayer->pos.z + cosf(g_camera[0].rot.y) * 80.0f);	//���݂̒����_
		g_camera[0].posV = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 140.0f + g_camera[0].ftest, pPlayer->pos.z - 400.0f);	//���݂̎��_

		g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.y) * CAMERA_DISTANCE;
		g_camera[0].posV.z = g_camera[0].posR.z - cosf(g_camera[0].rot.y) * CAMERA_DISTANCE;

	}

	
	//=======================================================================
	//�L�[�̓��͏���
	//=======================================================================
	

	//�����_�̂�
	if (GetKeyboardPress(DIK_E) == true)
	{
		g_camera[0].rot.y += CAMERA_R_SPEED;
		g_camera[0].posR.x = g_camera[0].posV.x + sinf(g_camera[0].rot.y) * CAMERA_DISTANCE;
		g_camera[0].posR.z = g_camera[0].posV.z + cosf(g_camera[0].rot.y) * CAMERA_DISTANCE;
	}
	else if (GetKeyboardPress(DIK_Q) == true)
	{
		g_camera[0].rot.y -= CAMERA_R_SPEED;
		g_camera[0].posR.x = g_camera[0].posV.x + sinf(g_camera[0].rot.y) * CAMERA_DISTANCE;
		g_camera[0].posR.z = g_camera[0].posV.z + cosf(g_camera[0].rot.y) * CAMERA_DISTANCE;
	}

	if (GetKeyboardPress(DIK_R) == true)
	{
		g_camera[0].ftest += CAMERA_VR_SPEED;
	}
	else if (GetKeyboardPress(DIK_V) == true)
	{
		g_camera[0].ftest -= CAMERA_VR_SPEED;

	}

	//���_�̂�
	if (GetKeyboardPress(DIK_C) == true)
	{
		g_camera[0].rot.y -= CAMERA_R_SPEED;
		g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.y) * CAMERA_DISTANCE;
		g_camera[0].posV.z = g_camera[0].posR.z - cosf(g_camera[0].rot.y) * CAMERA_DISTANCE;
	}
	else if (GetKeyboardPress(DIK_Z) == true)
	{
		g_camera[0].rot.y += CAMERA_R_SPEED;
		g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.y) * CAMERA_DISTANCE;
		g_camera[0].posV.z = g_camera[0].posR.z - cosf(g_camera[0].rot.y) * CAMERA_DISTANCE;
	}

	if (GetKeyboardPress(DIK_T) == true)
	{
		g_camera[0].ftest += CAMERA_VR_SPEED;
	}
	else if (GetKeyboardPress(DIK_B) == true)
	{
		g_camera[0].ftest -= CAMERA_VR_SPEED;
	}

	if (g_camera[0].rot.y > D3DX_PI)
	{
		g_camera[0].rot.y = -D3DX_PI;
	}
	else if (g_camera[0].rot.y < -D3DX_PI)
	{
		g_camera[0].rot.y = D3DX_PI;
	}
}

//=======================================================================
//�ݒ菈��
//=======================================================================
void SetCamera(int nIdx)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����

	//�r���[�|�[�g�̐ݒ�
	pDevice->SetViewport(&g_camera[nIdx].viewport);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera[nIdx].mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera[nIdx].mtxProjection,
								D3DXToRadian(50.0f),							//��p
								(float)g_camera[nIdx].viewport.Width / (float)g_camera[nIdx].viewport.Height,		//�䗦
								10.0f,											//Z�����̕`��͈�
								5000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�

	pDevice->SetTransform(D3DTS_PROJECTION,&g_camera[nIdx].mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera[nIdx].mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera[nIdx].mtxView, &g_camera[nIdx].posV, &g_camera[nIdx].posR, &g_camera[nIdx].vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera[nIdx].mtxView);
}

Camera *GetCamera(void)
{
	return &g_camera[0];
}
