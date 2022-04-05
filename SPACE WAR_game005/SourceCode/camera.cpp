//=======================================================================
//�J�����Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "pad.h"
#include "enemy.h"
#include "drone.h"
#include "billboard.h"
#include "boss.h"
#include "sound.h"

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
		g_camera[nCntCamera].frotVecX = 0.0f;
		g_camera[nCntCamera].frotVecZ = 0.0f;
		g_camera[nCntCamera].frotVecXSub = 0.0f;
		g_camera[nCntCamera].frotVecZSub = 0.0f;
		g_camera[nCntCamera].bRockOn = false;
		g_camera[nCntCamera].nCntEnemyDrone = 0;
		g_camera[nCntCamera].fToPlayerR = 100000.0f;
		g_camera[nCntCamera].nWhoRockOn = 0;
		g_camera[0].nEnemyNumber = 0;
	}
	g_bTurn = false;
	g_camera[0].viewport.Width = SCREEN_WIDTH;										//�`�悷���ʂ̕�
	g_camera[0].viewport.Height = SCREEN_HEIGHT;									//�`�悷���ʂ̍���

	g_camera[1].viewport.Width = SCREEN_WIDTH * 0.1;										//�`�悷���ʂ̕�
	g_camera[1].viewport.Height = SCREEN_HEIGHT * 0.1;									//�`�悷���ʂ̍���

	g_camera[0].posR = D3DXVECTOR3(pPlayer->pos.x + sinf(g_camera[0].rot.y) * 80.0f, pPlayer->pos.y + 80.0f, pPlayer->pos.z + cosf(g_camera[0].rot.y) * 80.0f);	//���݂̒����_
	g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.y) * CAMERA_DISTANCE;
	g_camera[0].posV.z = g_camera[0].posR.z - cosf(g_camera[0].rot.y) * CAMERA_DISTANCE;
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
	Camera *pCamera = GetCamera();
	PLAYER *pPlayer;
	pPlayer = GetPlayer();
	ENEMY *pEnemy = GetEnemy();
	BOSS *pBoss = GetBoss();
	DRONE *pDrone = GetDrone();

	if (GetMode() == MODE_STAGE1)
	{
		int nDrone = 0;
		if (g_camera[0].bRockOn == false)
		{
			for (int nCntDrone = 0; nCntDrone < MAX_DRONE; nCntDrone++, pDrone++)
			{
				if (pDrone->bUse == true)
				{
					if (pDrone->fToPlayerR <= g_camera[0].fToPlayerR)
					{
						g_camera[0].fToPlayerR = pDrone->fToPlayerR;
						g_camera[0].frotVecXSub = g_camera[0].posV.x - pDrone->pos.x;
						g_camera[0].frotVecZSub = g_camera[0].posV.z - pDrone->pos.z;
						g_camera[0].nEnemyNumber = nCntDrone;
						g_camera[0].nWhoRockOn = 0;
					}
					nDrone++;
				}
			}
			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{
				if (pEnemy->bUse == true)
				{
					if (pEnemy->fToPlayerR <= g_camera[0].fToPlayerR)
					{
						g_camera[0].fToPlayerR = pEnemy->fToPlayerR;
						g_camera[0].frotVecXSub = g_camera[0].posV.x - pEnemy->pos.x;
						g_camera[0].frotVecZSub = g_camera[0].posV.z - pEnemy->pos.z;
						g_camera[0].nEnemyNumber = nCntEnemy;
						g_camera[0].nWhoRockOn = 1;

					}
					nDrone++;
				}
			}
			for (int nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++, pBoss++)
			{
				if (pBoss->bUse == true)
				{
					if (pBoss->fToPlayerR <= g_camera[0].fToPlayerR)
					{
						g_camera[0].fToPlayerR = pBoss->fToPlayerR;
						g_camera[0].frotVecXSub = g_camera[0].posV.x - pBoss->pos.x;
						g_camera[0].frotVecZSub = g_camera[0].posV.z - pBoss->pos.z;
						g_camera[0].nEnemyNumber = nCntBoss;
						g_camera[0].nWhoRockOn = 2;
					}
					nDrone++;
				}
			}
		}
		
		


		//ZL�������ꂽ�Ƃ��̏���
		if(GetTriggerTrigger(TRIGGERTYPE_RIGHT) == true)
		{
			g_bTurn = true;
			g_camera[0].rotAsk.y = pPlayer->rot.y;
		}

		//L�X�e�B�b�N�������ꂽ�Ƃ��̏���
		if (GetButtonTrigger(XINPUT_GAMEPAD_LEFT_THUMB) == true)
		{
			if (g_camera[0].bRockOn == true)
			{
				g_camera[0].bRockOn = false;
			}
			else if(g_camera[0].bRockOn == false && nDrone != 0)
			{
				PlaySound(SOUND_LABEL_LOCKON);
				g_bTurn = true;
				g_camera[0].bRockOn = true;
			}
		}

		//���b�N�I�������Ƃ��̏���
		if (g_camera[0].bRockOn == true)
		{
			if (g_camera[0].nWhoRockOn == 0)
			{
				pDrone = GetDrone();
				for (int nCntDrone = 0; nCntDrone < MAX_DRONE; nCntDrone++, pDrone++)
				{
					if (nCntDrone == g_camera[0].nEnemyNumber)
					{
						g_camera[0].frotVecXSub = g_camera[0].posV.x - pDrone->pos.x;
						g_camera[0].frotVecZSub = g_camera[0].posV.z - pDrone->pos.z;
					}
				}
				//SetBillboard(pDrone->pos, 100.0f, 100.0f);
			}
			else if (g_camera[0].nWhoRockOn == 1)
			{
				pEnemy = GetEnemy();
				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (nCntEnemy == g_camera[0].nEnemyNumber)
					{
						g_camera[0].frotVecXSub = g_camera[0].posV.x - pEnemy->pos.x;
						g_camera[0].frotVecZSub = g_camera[0].posV.z - pEnemy->pos.z;
					}
				}
				//SetBillboard(pEnemy->pos, 100.0f, 100.0f);
			}
			else if (g_camera[0].nWhoRockOn == 2)
			{
				pBoss = GetBoss();
				for (int nCntBoss = 0; nCntBoss < MAX_ENEMY; nCntBoss++, pBoss++)
				{
					if (nCntBoss == g_camera[0].nEnemyNumber)
					{
						g_camera[0].frotVecXSub = g_camera[0].posV.x - pBoss->pos.x;
						g_camera[0].frotVecZSub = g_camera[0].posV.z - pBoss->pos.z;
					}
				}
				//SetBillboard(pEnemy->pos, 100.0f, 100.0f);
			}
			g_camera[0].frotVecX = g_camera[0].frotVecXSub;
			g_camera[0].frotVecZ = g_camera[0].frotVecZSub;
			g_camera[0].rotAsk.y = atan2(g_camera[0].frotVecX, g_camera[0].frotVecZ) - D3DX_PI;
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
				if (g_camera[0].bRockOn == true)
				{

				}
				else
				{
					g_bTurn = false;
				}
			}
		}

		if (g_camera[0].bRockOn == false)
		{
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
		}
		
		g_camera[0].posR = D3DXVECTOR3(pPlayer->pos.x + sinf(g_camera[0].rot.y) * 80.0f, pPlayer->pos.y + 80.0f, pPlayer->pos.z + cosf(g_camera[0].rot.y) * 80.0f);	//���݂̒����_
		g_camera[0].posV = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 140.0f + g_camera[0].ftest, pPlayer->pos.z - 400.0f);	//���݂̎��_

		g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.y) * CAMERA_DISTANCE;
		g_camera[0].posV.z = g_camera[0].posR.z - cosf(g_camera[0].rot.y) * CAMERA_DISTANCE;

	}

	if (g_camera[0].rot.y > D3DX_PI)
	{
		g_camera[0].rot.y = -D3DX_PI;
	}
	else if (g_camera[0].rot.y < -D3DX_PI)
	{
		g_camera[0].rot.y = D3DX_PI;
	}

	if (g_camera[0].bRockOn == false)
	{
		g_camera[0].fToPlayerR = 100000.0f;
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
								50000.0f);

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
