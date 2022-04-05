//=======================================================================
//�v���C���[�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "fade.h"
#include "enemy.h"
#include "EnemyBullet.h"
#include "pad.h"
#include "life.h"
#include "ui.h"
#include "sound.h"
#include "effect.h"
#include "mask.h"
#include "drone.h"
#include "evolutionGauge.h"
#include "boss.h"
#include "stage1.h"
#include "modeltxt.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
PLAYER g_Player;				//�v���C���[�̍\����
GUN g_Gun;						//�e�̍\����
SWORD g_Sword;					//���̍\����

//=======================================================================
//����������
//=======================================================================
void InitPlayer(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//������
	g_Player.aMotionInfo->bLoop = false;
	g_Player.aMotionInfo->nNumKey = 0;
	g_Player.aMotionInfo->aKeyInfo->nFrame = 0;
	g_Player.aMotionInfo->aKeyInfo->aKey->fPosX = 0;
	g_Player.aMotionInfo->aKeyInfo->aKey->fPosY = 0;
	g_Player.aMotionInfo->aKeyInfo->aKey->fPosZ = 0;
	g_Player.aMotionInfo->aKeyInfo->aKey->fRotX = 0;
	g_Player.aMotionInfo->aKeyInfo->aKey->fRotY = 0;
	g_Player.aMotionInfo->aKeyInfo->aKey->fRotZ = 0;

	if(GetMode() == MODE_TITLE)
	{
		g_Player.pos = D3DXVECTOR3(1017.0f, 0.0f, -97.0f);
		g_Player.rot = D3DXVECTOR3(0.0f, 2.43f, 0.0f);
	}
	else
	{
		g_Player.pos = D3DXVECTOR3(1700.0f, 0.0f, -140.0f);
		g_Player.rot = D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f);
	}
	
	g_Player.rotBullet = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.moveA = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.nNumModel = MAX_PLAYER_MODEL;
	g_Player.nNumMotion = MOTION_MAX;
	g_Player.bLoopMotion = false;
	g_Player.bBlendMotion = false;
	g_Player.bFinishMotion = false;
	g_Player.nNumKey = 0;
	g_Player.nNumKeyBlend = 0;
	g_Player.nKeyOld = 0;
	g_Player.nKey = 0;
	g_Player.nKeyBlend = 0;
	g_Player.nEffect = 0;
	g_Player.nTitle = 0;
	g_Player.nLife = MAX_PLAYER_LIFE;
	g_Player.fCounterMotion = 0.0f;
	g_Player.fCounterMotionBlend = 0.0f;
	g_Player.nCounterBlend = 0;
	g_Player.bJump = false;
	g_Player.bSlash = false;
	g_Player.bMotion = false;
	g_Player.bUse = true;
	g_Player.bDamage = false;
	g_Player.bDifence = false;
	g_Player.bWeapon = false;
	g_Player.bWeaponX = false;
	g_Player.fWidth = 70.0f;
	g_Player.fHeight = 900.0f;
	g_Player.fDepth = 70.0f;
	g_Player.fMoveSpeed = PLAYER_SPEED;
	g_Player.fMaxSpeed = MAX_PLAYER_SPEED;
	g_Player.fNumTurnPlayer = 0.0f;
	g_Player.bTurnPlayer = false;
	g_Player.bEvolutionButton = false;
	g_Player.bEvolution = false;
	g_Player.bDegenerate = false;
	g_Player.nType = PLAYERTYPE_NOMAL;
	g_Player.nTypeNext = PLAYERTYPE_SPEED;

	g_Gun.pos = D3DXVECTOR3(-60.0f, 0.0f, -10.0f);
	g_Gun.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_Sword.pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);
	g_Sword.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
	{
		g_Player.VtxRot[nCntVtx] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player.VtxPosOld[nCntVtx] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player.VtxPosSave[nCntVtx] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	g_Player.VtxPos[0] = D3DXVECTOR3(35.0f, 0.0f, 35.0f);
	g_Player.VtxPos[1] = D3DXVECTOR3(-35.0f, 0.0f, 35.0f);
	g_Player.VtxPos[2] = D3DXVECTOR3(35.0f, 0.0f, -35.0f);
	g_Player.VtxPos[3] = D3DXVECTOR3(-35.0f, 0.0f, -35.0f);


	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		g_Player.aModel[nCntModel].vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
		g_Player.aModel[nCntModel].vtxMin =D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_Player.aModel[nCntModel].fDepth = 0.0f;
		g_Player.aModel[nCntModel].fHeight = 0.0f;
		g_Player.aModel[nCntModel].fWidth = 0.0f;
		g_Player.aModel[nCntModel].rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	}

	g_Player.aModel[15].nIdxModelParent = 6;
	g_Player.aModel[15].pos.x = -22.0f;

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_body_00.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&g_Player.aModel[0].pBuffMat, NULL, &g_Player.aModel[0].nNumMat, &g_Player.aModel[0].pMesh);
	D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_body_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&g_Player.aModel[1].pBuffMat, NULL, &g_Player.aModel[1].nNumMat, &g_Player.aModel[1].pMesh);
	D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_body_02.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&g_Player.aModel[2].pBuffMat, NULL, &g_Player.aModel[2].nNumMat, &g_Player.aModel[2].pMesh);
	D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_arm_R_03.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&g_Player.aModel[3].pBuffMat, NULL, &g_Player.aModel[3].nNumMat, &g_Player.aModel[3].pMesh);
	D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_arm_R_04.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&g_Player.aModel[4].pBuffMat, NULL, &g_Player.aModel[4].nNumMat, &g_Player.aModel[4].pMesh);
	D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_arm_R_05.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&g_Player.aModel[5].pBuffMat, NULL, &g_Player.aModel[5].nNumMat, &g_Player.aModel[5].pMesh);
	D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_arm_R_06.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&g_Player.aModel[6].pBuffMat, NULL, &g_Player.aModel[6].nNumMat, &g_Player.aModel[6].pMesh);
	D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_arm_L_07.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&g_Player.aModel[7].pBuffMat, NULL, &g_Player.aModel[7].nNumMat, &g_Player.aModel[7].pMesh);
	D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_arm_L_08.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&g_Player.aModel[8].pBuffMat, NULL, &g_Player.aModel[8].nNumMat, &g_Player.aModel[8].pMesh);
	D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_arm_L_09.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&g_Player.aModel[9].pBuffMat, NULL, &g_Player.aModel[9].nNumMat, &g_Player.aModel[9].pMesh);
	D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_arm_L_10.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&g_Player.aModel[10].pBuffMat, NULL, &g_Player.aModel[10].nNumMat, &g_Player.aModel[10].pMesh);
	D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_leg_R_11.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&g_Player.aModel[11].pBuffMat, NULL, &g_Player.aModel[11].nNumMat, &g_Player.aModel[11].pMesh);
	D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_leg_R_12.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&g_Player.aModel[12].pBuffMat, NULL, &g_Player.aModel[12].nNumMat, &g_Player.aModel[12].pMesh);
	D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_leg_L_13.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&g_Player.aModel[13].pBuffMat, NULL, &g_Player.aModel[13].nNumMat, &g_Player.aModel[13].pMesh);
	D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_leg_L_14.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&g_Player.aModel[14].pBuffMat, NULL, &g_Player.aModel[14].nNumMat, &g_Player.aModel[14].pMesh);
	D3DXLoadMeshFromX("data/MODEL/exo_nomal/weapon/exo_N_Gun_weapon.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&g_Player.aModel[15].pBuffMat, NULL, &g_Player.aModel[15].nNumMat, &g_Player.aModel[15].pMesh);


	//�e�N�X�`���f�[�^�̎擾
	D3DXMATERIAL *pMat;		//�}�e���A���ւ̃|�C���^

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel - 1; nCntModel++)
	{
		//�}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL *)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_Player.aModel[nCntModel].pTexture[nCntMat]);
			}
		}

		//text�t�@�C���ǂݍ���
		FILE *pfile = fopen("data/MOTION/exoN_motion.txt", "r");

		char index[] = "INDEX";
		char string[255][255];
		char search[] = "KEYSET";
		char EndKeySet[] = "END_KEYSET";
		char LoopSearch[] = "LOOP";
		char KeySearch[] = "KEY";
		char MotionSearch[] = "MOTIONSET";
		char EndMotionSet[] = "END_MOTIONSET";

		//�e�p�[�c�̊K�w�\����ݒ�
		for (int nCntRead = 0; nCntRead < g_Player.nNumModel - 1; nCntRead++)
		{
			while (fgets(string[0], 255, pfile) != NULL)
			{
				if (strstr(string[0], index))
				{
					fscanf(pfile, "%s%s%d%*s%*s", string[1], string[2], &g_Player.aModel[nCntRead].nIdxModelParent);
					fscanf(pfile, "%s%s%f%f%f", string[3], string[4], &g_Player.aModel[nCntRead].pos.x, &g_Player.aModel[nCntRead].pos.y, &g_Player.aModel[nCntRead].pos.z);
					fscanf(pfile, "%s%s%f%f%f", string[5], string[6], &g_Player.aModel[nCntRead].rot.x, &g_Player.aModel[nCntRead].rot.y, &g_Player.aModel[nCntRead].rot.z);
					break;
				}
			}
		}

		//���[�V�����̓ǂݍ���
		for (int nCntMotion = 0; nCntMotion < MOTION_MAX; nCntMotion++)
		{
			//���[�v���̎擾
			//�L�[���̎擾
			while (fgets(string[0], 255, pfile) != NULL)
			{
				if (strstr(string[0], MotionSearch))
				{
					fscanf(pfile, "%s%s%d%*s%*s%*s%*s", string[1], string[2], &g_Player.aMotionInfo[nCntMotion].bLoop);
					fscanf(pfile, "%s%s%d", string[3], string[4], &g_Player.aMotionInfo[nCntMotion].nNumKey);
					break;
				}
			}

			for (int nCntKey = 0; nCntKey < g_Player.aMotionInfo[nCntMotion].nNumKey; nCntKey++)
			{
				//�t���[�����̎擾
				while (fgets(string[0], 255, pfile) != NULL)
				{
					if (strstr(string[0], search))
					{
						fscanf(pfile, "%s%s%d", string[0], string[0], &g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
						//g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame = g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame * (144 / 60);
						break;
					}
				}

				//�ʒu�A��]���̎擾
				for (int nCntRead = 0; nCntRead < g_Player.nNumModel - 1; nCntRead++)
				{
					while (fgets(string[0], 255, pfile) != NULL)
					{
						if (strstr(string[0], KeySearch))
						{
							fscanf(pfile, "%s%s%f%f%f", string[1], string[2], &g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosX, &g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosY, &g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosZ);
							fscanf(pfile, "%s%s%f%f%f%*s", string[0], string[0], &g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotX, &g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotY, &g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotZ);
							break;
						}
					}
				}

				while (fgets(string[0], 255, pfile) != NULL)
				{
					if (strstr(string[0], EndKeySet))
					{
						break;
					}
				}
			}

			while (fgets(string[0], 255, pfile) != NULL)
			{
				if (strstr(string[0], EndMotionSet))
				{
					break;
				}
			}
		}
		fclose(pfile);


		//�e�q�֌W�ɂ��ʒu����̏C��
		for (int nCntMotion = 0; nCntMotion < MOTION_MAX; nCntMotion++)
		{
			for (int nCntKey = 0; nCntKey < g_Player.aMotionInfo[nCntMotion].nNumKey; nCntKey++)
			{
				for (int nCntRead = 0; nCntRead < g_Player.nNumModel; nCntRead++)
				{
					g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosX = g_Player.aModel[nCntRead].pos.x + g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosX;
					g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosY = g_Player.aModel[nCntRead].pos.y + g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosY;
					g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosZ = g_Player.aModel[nCntRead].pos.z + g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosZ;
					g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotX = g_Player.aModel[nCntRead].rot.x + g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotX;
					g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotY = g_Player.aModel[nCntRead].rot.y + g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotY;
					g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotZ = g_Player.aModel[nCntRead].rot.z + g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotZ;
				}
			}
		}
	}

	
	g_Player.MotionType = MOTIONTYPE_NEUTRAL;
	g_Player.MotionTypeNext = MOTIONTYPE_NEUTRAL;
	g_Player.nTypeNext = PLAYERTYPE_POWER;
	g_Player.MotionTypeOld = MOTIONTYPE_NEUTRAL;
	g_Player.nIdx = SetShadow(g_Player.pos, g_Player.fWidth, g_Player.fDepth);
	SetUi(D3DXVECTOR3(1100.0f, 640.0f, 0.0f), UITYPE_GUN, 140.0f, 90.0f);
	SetUi(D3DXVECTOR3(1020.0f, 680.0f, 0.0f), UITYPE_SOWRD, 70.0f, 45.0f);
	SetUi(D3DXVECTOR3(10.0f, 500.0f, 0.0f), UITYPE_PLAYER_POWER, 140.0f, 120.0f);
	SetUi(D3DXVECTOR3(160.0f, 500.0f, 0.0f), UITYPE_PLAYER_SPEED, 140.0f, 120.0f);
	MotionPlayer();
}

//=======================================================================
//�I������
//=======================================================================
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		//���b�V���̔j��
		if (g_Player.aModel[nCntModel].pMesh != NULL)
		{
			g_Player.aModel[nCntModel].pMesh->Release();
			g_Player.aModel[nCntModel].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_Player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_Player.aModel[nCntModel].pBuffMat->Release();
			g_Player.aModel[nCntModel].pBuffMat = NULL;
		}

		//�e�N�X�`���̔j��
		for (int nCntTex = 0; nCntTex < PLAYER_MAX_TEXTURE; nCntTex++)
		{
			if (g_Player.aModel[nCntModel].pTexture[nCntTex] != NULL)
			{
				g_Player.aModel[nCntModel].pTexture[nCntTex]->Release();
				g_Player.aModel[nCntModel].pTexture[nCntTex] = NULL;
			}
		}
	}
	
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdatePlayer(void)
{
	EvolutionGauge *pEvolutionGauge = GetEvolutionGauge();
	ENEMY *pEnemy = GetEnemy();
	Life *pLife = GetLife();
	UI *pUi = GetUi();
	BULLET *pBullet = GetBullet();
	Stage1 *pStage1 = GetStage1();

	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
	{
		g_Player.VtxPosOld[nCntVtx] = g_Player.VtxPosSave[nCntVtx];
	}
	g_Player.MotionTypeOld = g_Player.MotionType;
	g_Player.posOld = g_Player.pos;
	g_Player.move.y -= GRAVITY;		//�d��
	
	if (g_Player.bUse == true)
	{
		if (g_Player.move.x == 0.0f && g_Player.move.z == 0.0f && g_Player.MotionType != MOTIONTYPE_SHOOT_N && g_Player.MotionType != MOTIONTYPE_SHOOT_P &&
			g_Player.MotionType != MOTIONTYPE_SHOOT_S && g_Player.MotionType != MOTIONTYPE_SLASH_N && g_Player.MotionType != MOTIONTYPE_SLASH_S &&
			g_Player.MotionType != MOTIONTYPE_SLASH_P && g_Player.MotionType != MOTIONTYPE_DAMAGE && g_Player.MotionType != MOTIONTYPE_SLASH_N1 &&
			g_Player.MotionType != MOTIONTYPE_SLASH_S1 && g_Player.MotionType != MOTIONTYPE_SLASH_P1 && g_Player.MotionType != MOTIONTYPE_SLASH_N2 &&
			g_Player.MotionType != MOTIONTYPE_SLASH_S2 && g_Player.MotionType != MOTIONTYPE_SLASH_P2)
		{
			g_Player.MotionType = MOTIONTYPE_NEUTRAL;
		}
		else if ((g_Player.move.x != 0.0f || g_Player.move.z != 0.0f))
		{
			if (g_Player.MotionType != MOTIONTYPE_SHOOT_N && g_Player.MotionType != MOTIONTYPE_SHOOT_S && g_Player.MotionType != MOTIONTYPE_SHOOT_P &&
				g_Player.MotionType != MOTIONTYPE_SLASH_N && g_Player.MotionType != MOTIONTYPE_SLASH_S && g_Player.MotionType != MOTIONTYPE_SLASH_P &&
				g_Player.MotionType != MOTIONTYPE_DAMAGE && g_Player.MotionType != MOTIONTYPE_SLASH_N1 && g_Player.MotionType != MOTIONTYPE_SLASH_S1 &&
				g_Player.MotionType != MOTIONTYPE_SLASH_P1 && g_Player.MotionType != MOTIONTYPE_SLASH_N2 && g_Player.MotionType != MOTIONTYPE_SLASH_S2 &&
				g_Player.MotionType != MOTIONTYPE_SLASH_P2)
			{
				g_Player.MotionType = MOTIONTYPE_MOVE;
			}
			SetEffect(D3DXVECTOR3(g_Player.aModel[12].mtxWorld._41, g_Player.pos.y, g_Player.aModel[12].mtxWorld._43),
						D3DXVECTOR3(0.0f,0.0f,0.0f), 20.0f, 20.0f, D3DXCOLOR(255, 0, 255, 255), 6, EFFEFCT_MOVETYPE_PLAYER_HOVER);

			SetEffect(D3DXVECTOR3(g_Player.aModel[14].mtxWorld._41, g_Player.pos.y, g_Player.aModel[14].mtxWorld._43),
						D3DXVECTOR3(0.0f,0.0f,0.0f), 20.0f, 20.0f, D3DXCOLOR(255, 0, 255, 255), 6, EFFEFCT_MOVETYPE_PLAYER_HOVER);
		}

		//�J���������擾
		Camera *pCamera = GetCamera();

		//���f���̈ړ�
		//g_Player.move += g_Player.moveA;
		g_Player.pos += g_Player.move;

		if (g_Player.nType == PLAYERTYPE_NOMAL)
		{
			g_Player.fMoveSpeed = PLAYER_SPEED;
			g_Player.fMaxSpeed = MAX_PLAYER_SPEED;
		}
		else if (g_Player.nType == PLAYERTYPE_POWER)
		{
			g_Player.fMoveSpeed = PLAYER_POWER_SPEED;
			g_Player.fMaxSpeed = MAX_PLAYER_POWER_SPEED;
		}
		else if (g_Player.nType == PLAYERTYPE_SPEED)
		{
			g_Player.fMoveSpeed = PLAYER_SPEED_SPEED;
			g_Player.fMaxSpeed = MAX_PLAYER_SPEED_SPEED;
		}

		if (pStage1->bStart == true)
		{
			//=======================================================================
			//�L�[�̓��͏���
			//=======================================================================

			if (g_Player.MotionType != MOTIONTYPE_SHOOT_N && g_Player.MotionType != MOTIONTYPE_SHOOT_P && g_Player.MotionType != MOTIONTYPE_SHOOT_S &&
				g_Player.MotionType != MOTIONTYPE_SLASH_N && g_Player.MotionType != MOTIONTYPE_SLASH_S && g_Player.MotionType != MOTIONTYPE_SLASH_P &&
				g_Player.MotionType != MOTIONTYPE_DAMAGE && g_Player.MotionType != MOTIONTYPE_SLASH_N1 && g_Player.MotionType != MOTIONTYPE_SLASH_S1 &&
				g_Player.MotionType != MOTIONTYPE_SLASH_P1 && g_Player.MotionType != MOTIONTYPE_SLASH_N2 && g_Player.MotionType != MOTIONTYPE_SLASH_S2 &&
				g_Player.MotionType != MOTIONTYPE_SLASH_P2)
			{
				if (GetLeftStick(STICKTYPE_UP) == true)
				{
					if (GetLeftStick(STICKTYPE_RIGHT) == true)
					{
						g_Player.move.x += +cosf(pCamera->rot.y - D3DX_PI / 4.0f) * g_Player.fMoveSpeed;
						g_Player.move.z += -sinf(pCamera->rot.y - D3DX_PI / 4.0f) * g_Player.fMoveSpeed;

						g_Player.fNumTurnPlayer = pCamera->rot.y + D3DX_PI / 4.0f;
						g_Player.bTurnPlayer = true;
					}
					else if (GetLeftStick(STICKTYPE_LEFT) == true)
					{
						g_Player.move.x += -cosf(pCamera->rot.y + D3DX_PI / 4.0f) * g_Player.fMoveSpeed;
						g_Player.move.z += +sinf(pCamera->rot.y + D3DX_PI / 4.0f) * g_Player.fMoveSpeed;

						g_Player.fNumTurnPlayer = pCamera->rot.y - D3DX_PI / 4.0f;
						g_Player.bTurnPlayer = true;
					}
					else
					{
						g_Player.move.z += +cosf(pCamera->rot.y) * g_Player.fMoveSpeed;
						g_Player.move.x += +sinf(pCamera->rot.y) * g_Player.fMoveSpeed;

						g_Player.fNumTurnPlayer = pCamera->rot.y;
						g_Player.bTurnPlayer = true;

					}

				}
				else if (GetLeftStick(STICKTYPE_DOWN) == true)
				{
					if (GetLeftStick(STICKTYPE_RIGHT) == true)
					{
						g_Player.move.x += +cosf(pCamera->rot.y + D3DX_PI / 4.0f) * g_Player.fMoveSpeed;
						g_Player.move.z += -sinf(pCamera->rot.y + D3DX_PI / 4.0f) * g_Player.fMoveSpeed;

						g_Player.fNumTurnPlayer = pCamera->rot.y + D3DX_PI / 1.5f;
						g_Player.bTurnPlayer = true;
					}
					else if (GetLeftStick(STICKTYPE_LEFT) == true)
					{
						g_Player.move.x += -cosf(pCamera->rot.y - D3DX_PI / 4.0f) * g_Player.fMoveSpeed;
						g_Player.move.z += +sinf(pCamera->rot.y - D3DX_PI / 4.0f) * g_Player.fMoveSpeed;

						g_Player.fNumTurnPlayer = pCamera->rot.y - (D3DX_PI / 4.0f) * 3.0f;
						g_Player.bTurnPlayer = true;
					}
					else
					{
						g_Player.fNumTurnPlayer = pCamera->rot.y + D3DX_PI;

						g_Player.move.z += -cosf(pCamera->rot.y) * g_Player.fMoveSpeed;
						g_Player.move.x += -sinf(pCamera->rot.y) * g_Player.fMoveSpeed;

						g_Player.bTurnPlayer = true;
					}
				}
				else if (GetLeftStick(STICKTYPE_RIGHT) == true)
				{
					g_Player.move.x += +cosf(pCamera->rot.y) * g_Player.fMoveSpeed;
					g_Player.move.z += -sinf(pCamera->rot.y) * g_Player.fMoveSpeed;

					g_Player.fNumTurnPlayer = pCamera->rot.y + D3DX_PI / 2.0f;
					g_Player.bTurnPlayer = true;
				}
				else if (GetLeftStick(STICKTYPE_LEFT) == true)
				{
					g_Player.move.x += -cosf(pCamera->rot.y) * g_Player.fMoveSpeed;
					g_Player.move.z += +sinf(pCamera->rot.y) * g_Player.fMoveSpeed;

					g_Player.fNumTurnPlayer = pCamera->rot.y - D3DX_PI / 2.0f;
					g_Player.bTurnPlayer = true;
				}
			}
		}
		if ((GetLeftStick(STICKTYPE_RIGHT) == false && GetLeftStick(STICKTYPE_LEFT) == false &&
			GetLeftStick(STICKTYPE_DOWN) == false && GetLeftStick(STICKTYPE_UP) == false) ||
			g_Player.MotionType == MOTIONTYPE_SHOOT_N || g_Player.MotionType == MOTIONTYPE_SHOOT_P || g_Player.MotionType == MOTIONTYPE_SHOOT_S ||
			g_Player.MotionType == MOTIONTYPE_SLASH_N || g_Player.MotionType == MOTIONTYPE_SLASH_S || g_Player.MotionType == MOTIONTYPE_SLASH_P ||
			g_Player.MotionType == MOTIONTYPE_DAMAGE || g_Player.MotionType == MOTIONTYPE_SLASH_N1 || g_Player.MotionType == MOTIONTYPE_SLASH_S1 ||
			g_Player.MotionType == MOTIONTYPE_SLASH_P1 || g_Player.MotionType == MOTIONTYPE_SLASH_N2 || g_Player.MotionType == MOTIONTYPE_SLASH_S2 ||
			g_Player.MotionType == MOTIONTYPE_SLASH_P2)
		{
			g_Player.move.z *= 0.93f;
			g_Player.move.x *= 0.93f;

			if (pCamera->bRockOn == true)
			{
				g_Player.bTurnPlayer = true;
				g_Player.fNumTurnPlayer = pCamera->rot.y;
			}
		}

		if (g_Player.nType == PLAYERTYPE_NOMAL)
		{
			if (g_Player.rot.y >= 0.0f)
			{
				if (g_Player.move.x >= sinf(g_Player.rot.y) *  MAX_PLAYER_SPEED)
				{
					g_Player.move.x = sinf(g_Player.rot.y) *  MAX_PLAYER_SPEED;
				}
			}
			else if (g_Player.rot.y < 0.0f)
			{
				if (g_Player.move.x <= sinf(g_Player.rot.y) *  MAX_PLAYER_SPEED)
				{
					g_Player.move.x = sinf(g_Player.rot.y) *  MAX_PLAYER_SPEED;
				}
			}
			if (g_Player.rot.y >= -D3DX_PI / 2.0f && g_Player.rot.y <= D3DX_PI / 2.0f)
			{
				if (g_Player.move.z >= cosf(g_Player.rot.y) * MAX_PLAYER_SPEED)
				{
					g_Player.move.z = cosf(g_Player.rot.y) * MAX_PLAYER_SPEED;
				}
			}
			else if (g_Player.rot.y < -D3DX_PI / 2.0f || g_Player.rot.y > D3DX_PI / 2.0f)
			{
				if (g_Player.move.z <= cosf(g_Player.rot.y) * MAX_PLAYER_SPEED)
				{
					g_Player.move.z = cosf(g_Player.rot.y) * MAX_PLAYER_SPEED;
				}
			}
		}
		else if (g_Player.nType == PLAYERTYPE_POWER)
		{
			if (g_Player.rot.y >= 0.0f)
			{
				if (g_Player.move.x >= sinf(g_Player.rot.y) *  MAX_PLAYER_POWER_SPEED)
				{
					g_Player.move.x = sinf(g_Player.rot.y) *  MAX_PLAYER_POWER_SPEED;
				}
			}
			else if (g_Player.rot.y < 0.0f)
			{
				if (g_Player.move.x <= sinf(g_Player.rot.y) *  MAX_PLAYER_POWER_SPEED)
				{
					g_Player.move.x = sinf(g_Player.rot.y) *  MAX_PLAYER_POWER_SPEED;
				}
			}
			if (g_Player.rot.y >= -D3DX_PI / 2.0f && g_Player.rot.y <= D3DX_PI / 2.0f)
			{
				if (g_Player.move.z >= cosf(g_Player.rot.y) * MAX_PLAYER_POWER_SPEED)
				{
					g_Player.move.z = cosf(g_Player.rot.y) * MAX_PLAYER_POWER_SPEED;
				}
			}
			else if (g_Player.rot.y < -D3DX_PI / 2.0f || g_Player.rot.y > D3DX_PI / 2.0f)
			{
				if (g_Player.move.z <= cosf(g_Player.rot.y) * MAX_PLAYER_POWER_SPEED)
				{
					g_Player.move.z = cosf(g_Player.rot.y) * MAX_PLAYER_POWER_SPEED;
				}
			}
		}
		else if (g_Player.nType == PLAYERTYPE_SPEED)
		{
			if (g_Player.rot.y >= 0.0f)
			{
				if (g_Player.move.x >= sinf(g_Player.rot.y) *  MAX_PLAYER_SPEED_SPEED)
				{
					g_Player.move.x = sinf(g_Player.rot.y) *  MAX_PLAYER_SPEED_SPEED;
				}
			}
			else if (g_Player.rot.y < 0.0f)
			{
				if (g_Player.move.x <= sinf(g_Player.rot.y) *  MAX_PLAYER_SPEED_SPEED)
				{
					g_Player.move.x = sinf(g_Player.rot.y) *  MAX_PLAYER_SPEED_SPEED;
				}
			}
			if (g_Player.rot.y >= -D3DX_PI / 2.0f && g_Player.rot.y <= D3DX_PI / 2.0f)
			{
				if (g_Player.move.z >= cosf(g_Player.rot.y) * MAX_PLAYER_SPEED_SPEED)
				{
					g_Player.move.z = cosf(g_Player.rot.y) * MAX_PLAYER_SPEED_SPEED;
				}
			}
			else if (g_Player.rot.y < -D3DX_PI / 2.0f || g_Player.rot.y > D3DX_PI / 2.0f)
			{
				if (g_Player.move.z <= cosf(g_Player.rot.y) * MAX_PLAYER_SPEED_SPEED)
				{
					g_Player.move.z = cosf(g_Player.rot.y) * MAX_PLAYER_SPEED_SPEED;
				}
			}
		}
		


		if (g_Player.move.x <= 0.1f && g_Player.move.x >= -0.1f)
		{
			g_Player.move.x = 0.0f;
		}
		if (g_Player.move.z <= 0.1f && g_Player.move.z >= -0.1f)
		{
			g_Player.move.z = 0.0f;
		}

		
		//��]�̊���
		if (g_Player.bTurnPlayer == true)
		{
			if (g_Player.fNumTurnPlayer > D3DX_PI)
			{
				g_Player.fNumTurnPlayer = -D3DX_PI - (D3DX_PI - g_Player.fNumTurnPlayer);
			}
			else if (g_Player.fNumTurnPlayer < -D3DX_PI)
			{
				g_Player.fNumTurnPlayer = D3DX_PI - (-D3DX_PI - g_Player.fNumTurnPlayer);
			}

			if (g_Player.rot.y < 0.0f && -g_Player.rot.y + g_Player.fNumTurnPlayer > D3DX_PI)
			{
				g_Player.fNumPlayer = (-D3DX_PI - g_Player.rot.y) + -(D3DX_PI - g_Player.fNumTurnPlayer);
			}
			else if (g_Player.rot.y >= D3DX_PI / 2.0f && g_Player.rot.y - g_Player.fNumTurnPlayer > D3DX_PI)
			{
				g_Player.fNumPlayer = (D3DX_PI - g_Player.rot.y) - (-D3DX_PI - g_Player.fNumTurnPlayer);
			}
			else
			{
				g_Player.fNumPlayer = (g_Player.fNumTurnPlayer - g_Player.rot.y);
			}


			g_Player.rot.y += g_Player.fNumPlayer * 0.2f;
			if (g_Player.rot.y - g_Player.fNumTurnPlayer < 0.001 && g_Player.rot.y - g_Player.fNumTurnPlayer > -0.001)
			{
				if (pCamera->bRockOn == true)
				{

				}
				else
				{
					g_Player.bTurnPlayer = false;
				}
			}
		}
		if (g_Player.rot.y > D3DX_PI)
		{
			g_Player.rot.y = -D3DX_PI;
		}
		else if (g_Player.rot.y < -D3DX_PI)
		{
			g_Player.rot.y = D3DX_PI;
		}

		
		
		//�G�Ƃ̓����蔻��
		CollisionEnemy(&g_Player.pos, &g_Player.posOld, &g_Player.move, g_Player.fWidth, g_Player.fHeight, g_Player.fDepth);
		//�{�X�Ƃ̓����蔻��
		CollisionBoss(&g_Player.pos, &g_Player.posOld, &g_Player.move, g_Player.fWidth, g_Player.fHeight, g_Player.fDepth);
		//�h���[���Ƃ̓����蔻��
		CollisionDrone(&g_Player.pos, &g_Player.posOld, &g_Player.move, g_Player.fWidth, g_Player.fHeight, g_Player.fDepth);
		//�G�̒e�Ƃ̓����蔻��
		int nCntEnemyBullet = CollisionEnemyBullet(&g_Player.pos, g_Player.fWidth);

		if (nCntEnemyBullet == 1) //�h���[��1�̍U�����󂯂���
		{
			g_Player.nLife--;
			PlaySound(SOUND_LABEL_DAMAGE);
			SetMask(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2.0f, 0.0f), MASKTYPE_DAMAGE, SCREEN_WIDTH, SCREEN_HEIGHT);
			SetVibration(60000, 60000, 30);
			pLife->fWidth = PLAYER_LIFE_WIDTH / MAX_PLAYER_LIFE * g_Player.nLife;
		}
		else if (nCntEnemyBullet == 2) //�h���[��2�̍U�����󂯂���
		{
			g_Player.nLife--;
			PlaySound(SOUND_LABEL_DAMAGE);
			SetMask(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2.0f, 0.0f), MASKTYPE_DAMAGE, SCREEN_WIDTH, SCREEN_HEIGHT);
			SetVibration(60000, 60000, 30);
			pLife->fWidth = PLAYER_LIFE_WIDTH / MAX_PLAYER_LIFE * g_Player.nLife;
		}
		else if (nCntEnemyBullet == 3) //�h���[��3�̍U�����󂯂���
		{
			g_Player.nLife -= 2;
			PlaySound(SOUND_LABEL_DAMAGE);
			SetMask(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2.0f, 0.0f), MASKTYPE_DAMAGE, SCREEN_WIDTH, SCREEN_HEIGHT);
			SetVibration(60000, 60000, 30);
			pLife->fWidth = PLAYER_LIFE_WIDTH / MAX_PLAYER_LIFE * g_Player.nLife;
		}
		else if (nCntEnemyBullet == 4) //�{�X���̍U�����󂯂���
		{
			g_Player.nLife -= 3;
			PlaySound(SOUND_LABEL_DAMAGE);
			SetMask(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2.0f, 0.0f), MASKTYPE_DAMAGE, SCREEN_WIDTH, SCREEN_HEIGHT);
			SetVibration(60000, 60000, 30);
			pLife->fWidth = PLAYER_LIFE_WIDTH / MAX_PLAYER_LIFE * g_Player.nLife;
		}
		else if (nCntEnemyBullet == 5) //�{�X��̍U�����󂯂���
		{
			g_Player.nLife -= 3;
			PlaySound(SOUND_LABEL_DAMAGE);
			SetMask(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2.0f, 0.0f), MASKTYPE_DAMAGE, SCREEN_WIDTH, SCREEN_HEIGHT);
			SetVibration(60000, 60000, 30);
			pLife->fWidth = PLAYER_LIFE_WIDTH / MAX_PLAYER_LIFE * g_Player.nLife;
		}

		//�G�̌��ƃv���C���[�̓����蔻��
		if (CollisionEnemySword(&g_Player.pos, g_Player.fWidth) == true)
		{
			ENEMY *pAttackEnemy = GetAttackEnemy();
			if (pAttackEnemy->bPlayerDamage == false && pAttackEnemy->bSlash == true)
			{
				g_Player.nLife--;
				PlaySound(SOUND_LABEL_DAMAGE);
				SetMask(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2.0f, 0.0f), MASKTYPE_DAMAGE, SCREEN_WIDTH, SCREEN_HEIGHT);
				SetVibration(60000, 60000, 30);
				pLife->fWidth = pLife->fWidth / (g_Player.nLife + 1) * g_Player.nLife;
				pAttackEnemy->bPlayerDamage = true;
				g_Player.MotionType = MOTIONTYPE_DAMAGE;

				if (g_Player.nLife <= 0 && g_Player.bUse != false)
				{
					g_Player.bUse = false;
				}
			}
		}

		//���C�t��50�p�[�Z���g��؂�����
		if (g_Player.nLife <= MAX_PLAYER_LIFE * 0.5f)
		{
			SetEffect(D3DXVECTOR3(g_Player.aModel[0].mtxWorld._41 - 2.0f, g_Player.aModel[0].mtxWorld._42, g_Player.aModel[0].mtxWorld._43),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15.0f, 15.0f, D3DXCOLOR(10, 10, 10, 255), 20, EFFEFCT_MOVETYPE_PLAYER_LIFE_LOW);
			SetEffect(D3DXVECTOR3(g_Player.aModel[0].mtxWorld._41 + 2.0f, g_Player.aModel[0].mtxWorld._42 + 5.0f, g_Player.aModel[0].mtxWorld._43),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15.0f, 15.0f, D3DXCOLOR(255, 255, 255, 255), 20, EFFEFCT_MOVETYPE_PLAYER_LIFE_LOW);
		}

		//���C�t��0�ɂȂ�����
		if (g_Player.nLife <= 0 && g_Player.bUse != false)
		{
			PlaySound(SOUND_LABEL_GAMEOVER);
			g_Player.nLife = 0;
			g_Player.bUse = false;
		}


		if (GetMode() == MODE_STAGE1)
		{
			//�W�����v
			if (GetKeyboardTrigger(DIK_SPACE) == true)
			{
				if (g_Player.bJump == false)
				{
					g_Player.bJump = true;
					g_Player.move.y = PLAYER_JUMP;
				}
			}
			if (g_Player.move.y < 0.0f)
			{
				g_Player.bJump = true;
			}
		}
		if (pStage1->bStart == true)
		{
			//�U��
			if (GetButtonTrigger(XINPUT_GAMEPAD_B) == true)
			{
				if (g_Player.bWeapon == false)
				{
					g_Player.rotBullet = g_Player.rot;
					if (g_Player.nType == PLAYERTYPE_NOMAL)
					{
						g_Player.MotionType = MOTIONTYPE_SHOOT_N;
					}
					else if (g_Player.nType == PLAYERTYPE_POWER)
					{
						g_Player.MotionType = MOTIONTYPE_SHOOT_P;
					}
					else if (g_Player.nType == PLAYERTYPE_SPEED)
					{
						g_Player.MotionType = MOTIONTYPE_SHOOT_S;
					}
				}
				else if (g_Player.bWeapon == true)
				{
					if (g_Player.bSlash == false && g_Player.MotionType != MOTIONTYPE_SLASH_N && g_Player.MotionType != MOTIONTYPE_SLASH_S &&
						g_Player.MotionType != MOTIONTYPE_SLASH_P && g_Player.MotionType != MOTIONTYPE_SLASH_N1 && g_Player.MotionType != MOTIONTYPE_SLASH_S1 &&
						g_Player.MotionType != MOTIONTYPE_SLASH_P1 && g_Player.MotionType != MOTIONTYPE_SLASH_N2 && g_Player.MotionType != MOTIONTYPE_SLASH_S2 &&
						g_Player.MotionType != MOTIONTYPE_SLASH_P2)
					{
						if (g_Player.nType == PLAYERTYPE_NOMAL)
						{
							g_Player.MotionType = MOTIONTYPE_SLASH_N;
						}
						else if (g_Player.nType == PLAYERTYPE_SPEED)
						{
							g_Player.MotionType = MOTIONTYPE_SLASH_S;
						}
						else if (g_Player.nType == PLAYERTYPE_POWER)
						{
							g_Player.MotionType = MOTIONTYPE_SLASH_P;
						}

						g_Player.bSlash = true;
						PlaySound(SOUND_LABEL_SLASH_001);
					}

					else if (g_Player.MotionType == MOTIONTYPE_SLASH_N)
					{
						g_Player.MotionTypeNext = MOTIONTYPE_SLASH_N1;
					}
					else if (g_Player.MotionType == MOTIONTYPE_SLASH_N1)
					{
						g_Player.MotionTypeNext = MOTIONTYPE_SLASH_N2;
					}
					else if (g_Player.MotionType == MOTIONTYPE_SLASH_S)
					{
						g_Player.MotionTypeNext = MOTIONTYPE_SLASH_S1;
					}
					else if (g_Player.MotionType == MOTIONTYPE_SLASH_S1)
					{
						g_Player.MotionTypeNext = MOTIONTYPE_SLASH_S2;
					}
					else if (g_Player.MotionType == MOTIONTYPE_SLASH_P)
					{
						g_Player.MotionTypeNext = MOTIONTYPE_SLASH_P1;
					}
					else if (g_Player.MotionType == MOTIONTYPE_SLASH_P1)
					{
						g_Player.MotionTypeNext = MOTIONTYPE_SLASH_P2;
					}
				}
			}

			//����؂�ւ�
			if (g_Player.MotionType != MOTIONTYPE_SHOOT_N && g_Player.MotionType != MOTIONTYPE_SHOOT_P && g_Player.MotionType != MOTIONTYPE_SHOOT_S &&
				g_Player.MotionType != MOTIONTYPE_SLASH_N && g_Player.MotionType != MOTIONTYPE_SLASH_S && g_Player.MotionType != MOTIONTYPE_SLASH_P &&
				g_Player.MotionType != MOTIONTYPE_SLASH_N1 && g_Player.MotionType != MOTIONTYPE_SLASH_S1 && g_Player.MotionType != MOTIONTYPE_SLASH_P1 &&
				g_Player.MotionType != MOTIONTYPE_SLASH_N2 && g_Player.MotionType != MOTIONTYPE_SLASH_S2 && g_Player.MotionType != MOTIONTYPE_SLASH_P2)
			{
				if (GetButtonTrigger(XINPUT_GAMEPAD_Y) == true)
				{
					if (g_Player.bWeapon == true)
					{
						g_Player.bWeapon = false;
					}
					else if (g_Player.bWeapon == false)
					{
						g_Player.bWeapon = true;
					}
					g_Player.bWeaponX = true;
				}
			}

			if (g_Player.bWeaponX == true)
			{
				//�f�o�C�X�̎擾
				LPDIRECT3DDEVICE9 pDevice;
				pDevice = GetDevice();

				for (int nCntUi = 0; nCntUi < MAX_UI; nCntUi++, pUi++)
				{
					if (pUi->nType == UITYPE_GUN || pUi->nType == UITYPE_SOWRD)
					{
						pUi->bUse = false;
					}
				}

				if (g_Player.bWeapon == false)
				{
					SetUi(D3DXVECTOR3(1100.0f, 640.0f, 0.0f), UITYPE_GUN, 140.0f, 90.0f);
					SetUi(D3DXVECTOR3(1020.0f, 680.0f, 0.0f), UITYPE_SOWRD, 70.0f, 45.0f);
					if (g_Player.nType == PLAYERTYPE_NOMAL)
					{
						D3DXLoadMeshFromX("data/MODEL/exo_nomal/weapon/exo_N_Gun_weapon.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
							&g_Player.aModel[15].pBuffMat, NULL, &g_Player.aModel[15].nNumMat, &g_Player.aModel[15].pMesh);
					}
					else if (g_Player.nType == PLAYERTYPE_SPEED)
					{
						D3DXLoadMeshFromX("data/MODEL/exo_speed/weapon/exo_S_Gun_weapon.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
							&g_Player.aModel[15].pBuffMat, NULL, &g_Player.aModel[15].nNumMat, &g_Player.aModel[15].pMesh);
					}
					else if (g_Player.nType == PLAYERTYPE_POWER)
					{
						D3DXLoadMeshFromX("data/MODEL/exo_power/weapon/exo_P_Gun_weapon.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
							&g_Player.aModel[15].pBuffMat, NULL, &g_Player.aModel[15].nNumMat, &g_Player.aModel[15].pMesh);
					}
				}
				else if (g_Player.bWeapon == true)
				{
					SetUi(D3DXVECTOR3(1100.0f, 640.0f, 0.0f), UITYPE_SOWRD, 140.0f, 90.0f);
					SetUi(D3DXVECTOR3(1020.0f, 680.0f, 0.0f), UITYPE_GUN, 70.0f, 45.0f);
					if (g_Player.nType == PLAYERTYPE_NOMAL)
					{
						D3DXLoadMeshFromX("data/MODEL/exo_nomal/weapon/exo_N_Sword_weapon.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
							&g_Player.aModel[15].pBuffMat, NULL, &g_Player.aModel[15].nNumMat, &g_Player.aModel[15].pMesh);
					}
					else if (g_Player.nType == PLAYERTYPE_SPEED)
					{
						D3DXLoadMeshFromX("data/MODEL/exo_speed/weapon/exo_S_Sword_weapon.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
							&g_Player.aModel[15].pBuffMat, NULL, &g_Player.aModel[15].nNumMat, &g_Player.aModel[15].pMesh);
					}
					else if (g_Player.nType == PLAYERTYPE_POWER)
					{
						D3DXLoadMeshFromX("data/MODEL/exo_power/weapon/exo_P_Sword_weapon.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
							&g_Player.aModel[15].pBuffMat, NULL, &g_Player.aModel[15].nNumMat, &g_Player.aModel[15].pMesh);
					}
				}
				g_Player.bWeaponX = false;
			}

			//�i����I��
			if (GetButtonTrigger(XINPUT_GAMEPAD_DPAD_RIGHT) == true)
			{
				PlaySound(SOUND_LABEL_CURSOR);
				g_Player.nTypeNext = PLAYERTYPE_SPEED;
			}
			if (GetButtonTrigger(XINPUT_GAMEPAD_DPAD_LEFT) == true)
			{
				PlaySound(SOUND_LABEL_CURSOR);
				g_Player.nTypeNext = PLAYERTYPE_POWER;
			}

			//�i������
			if (pEvolutionGauge->bGaugeMax == true)
			{
				if (GetButtonPress(XINPUT_GAMEPAD_RIGHT_SHOULDER) == true && GetButtonPress(XINPUT_GAMEPAD_LEFT_SHOULDER) == true)
				{
					PlaySound(SOUND_LABEL_GRADEUP);
					g_Player.bEvolutionButton = true;
					pEvolutionGauge->bGaugeMax = false;

					for (int nCnt = 0; nCnt < 32; nCnt++)
					{
						SetEffect(D3DXVECTOR3(g_Player.pos.x + cos(D3DX_PI * 2.0f / 32.0f * nCnt) * g_Player.fWidth,
							g_Player.pos.y, g_Player.pos.z + sin(D3DX_PI * 2.0f / 32.0f * nCnt) * g_Player.fWidth),
							D3DXVECTOR3(0.0f, 1.0f, 0.0f), 10.0f, 30.0f, D3DXCOLOR(255, 255, 0, 100), 60, EFFEFCT_MOVETYPE_ENEMY_APPEAR);
						SetEffect(D3DXVECTOR3(g_Player.pos.x + cos(D3DX_PI * 2.0f / 32.0f * nCnt) * g_Player.fWidth,
							g_Player.pos.y, g_Player.pos.z + sin(D3DX_PI * 2.0f / 32.0f * nCnt) * g_Player.fWidth),
							D3DXVECTOR3(0.0f, 1.0f, 0.0f), 10.0f, 30.0f, D3DXCOLOR(255, 255, 0, 100), 60, EFFEFCT_MOVETYPE_ENEMY_APPEAR);
					}
				}
			}


			if (g_Player.bEvolutionButton == true)
			{
				g_Player.bEvolution = true;
				//�f�o�C�X�̎擾
				LPDIRECT3DDEVICE9 pDevice;
				pDevice = GetDevice();

				for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
				{
					if (pBullet->bUse == true)
					{
						pBullet->bUse = false;
					}
				}

				if (g_Player.nTypeNext == PLAYERTYPE_SPEED)
				{
					//X�t�@�C���ǂݍ���
					D3DXLoadMeshFromX("data/MODEL/exo_speed/S_exo_body_00.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[0].pBuffMat, NULL, &g_Player.aModel[0].nNumMat, &g_Player.aModel[0].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_speed/S_exo_body_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[1].pBuffMat, NULL, &g_Player.aModel[1].nNumMat, &g_Player.aModel[1].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_speed/S_exo_body_02.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[2].pBuffMat, NULL, &g_Player.aModel[2].nNumMat, &g_Player.aModel[2].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_speed/S_exo_arm_R_03.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[3].pBuffMat, NULL, &g_Player.aModel[3].nNumMat, &g_Player.aModel[3].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_speed/S_exo_arm_R_04.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[4].pBuffMat, NULL, &g_Player.aModel[4].nNumMat, &g_Player.aModel[4].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_speed/S_exo_arm_R_05.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[5].pBuffMat, NULL, &g_Player.aModel[5].nNumMat, &g_Player.aModel[5].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_speed/S_exo_arm_R_06.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[6].pBuffMat, NULL, &g_Player.aModel[6].nNumMat, &g_Player.aModel[6].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_speed/S_exo_arm_L_07.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[7].pBuffMat, NULL, &g_Player.aModel[7].nNumMat, &g_Player.aModel[7].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_speed/S_exo_arm_L_08.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[8].pBuffMat, NULL, &g_Player.aModel[8].nNumMat, &g_Player.aModel[8].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_speed/S_exo_arm_L_09.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[9].pBuffMat, NULL, &g_Player.aModel[9].nNumMat, &g_Player.aModel[9].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_speed/S_exo_arm_L_10.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[10].pBuffMat, NULL, &g_Player.aModel[10].nNumMat, &g_Player.aModel[10].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_speed/S_exo_leg_R_11.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[11].pBuffMat, NULL, &g_Player.aModel[11].nNumMat, &g_Player.aModel[11].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_speed/S_exo_leg_R_12.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[12].pBuffMat, NULL, &g_Player.aModel[12].nNumMat, &g_Player.aModel[12].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_speed/S_exo_leg_L_13.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[13].pBuffMat, NULL, &g_Player.aModel[13].nNumMat, &g_Player.aModel[13].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_speed/S_exo_leg_L_14.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[14].pBuffMat, NULL, &g_Player.aModel[14].nNumMat, &g_Player.aModel[14].pMesh);
					//g_Gun.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					g_Player.nType = PLAYERTYPE_SPEED;
				}
				else if (g_Player.nTypeNext == PLAYERTYPE_POWER)
				{
					//X�t�@�C���ǂݍ���
					D3DXLoadMeshFromX("data/MODEL/exo_power/P_exo_body_00.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[0].pBuffMat, NULL, &g_Player.aModel[0].nNumMat, &g_Player.aModel[0].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_power/P_exo_body_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[1].pBuffMat, NULL, &g_Player.aModel[1].nNumMat, &g_Player.aModel[1].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_power/P_exo_body_02.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[2].pBuffMat, NULL, &g_Player.aModel[2].nNumMat, &g_Player.aModel[2].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_power/P_exo_arm_R_03.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[3].pBuffMat, NULL, &g_Player.aModel[3].nNumMat, &g_Player.aModel[3].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_power/P_exo_arm_R_04.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[4].pBuffMat, NULL, &g_Player.aModel[4].nNumMat, &g_Player.aModel[4].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_power/P_exo_arm_R_05.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[5].pBuffMat, NULL, &g_Player.aModel[5].nNumMat, &g_Player.aModel[5].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_power/P_exo_arm_R_06.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[6].pBuffMat, NULL, &g_Player.aModel[6].nNumMat, &g_Player.aModel[6].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_power/P_exo_arm_L_07.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[7].pBuffMat, NULL, &g_Player.aModel[7].nNumMat, &g_Player.aModel[7].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_power/P_exo_arm_L_08.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[8].pBuffMat, NULL, &g_Player.aModel[8].nNumMat, &g_Player.aModel[8].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_power/P_exo_arm_L_09.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[9].pBuffMat, NULL, &g_Player.aModel[9].nNumMat, &g_Player.aModel[9].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_power/P_exo_arm_L_10.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[10].pBuffMat, NULL, &g_Player.aModel[10].nNumMat, &g_Player.aModel[10].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_power/P_exo_leg_R_11.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[11].pBuffMat, NULL, &g_Player.aModel[11].nNumMat, &g_Player.aModel[11].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_power/P_exo_leg_R_12.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[12].pBuffMat, NULL, &g_Player.aModel[12].nNumMat, &g_Player.aModel[12].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_power/P_exo_leg_L_13.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[13].pBuffMat, NULL, &g_Player.aModel[13].nNumMat, &g_Player.aModel[13].pMesh);
					D3DXLoadMeshFromX("data/MODEL/exo_power/P_exo_leg_L_14.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[14].pBuffMat, NULL, &g_Player.aModel[14].nNumMat, &g_Player.aModel[14].pMesh);
					//g_Gun.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					g_Player.nType = PLAYERTYPE_POWER;
				}

				if (g_Player.bWeapon == false)
				{
					if (g_Player.nType == PLAYERTYPE_SPEED)
					{
						D3DXLoadMeshFromX("data/MODEL/exo_speed/weapon/exo_S_Gun_weapon.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
							&g_Player.aModel[15].pBuffMat, NULL, &g_Player.aModel[15].nNumMat, &g_Player.aModel[15].pMesh);
						//g_Gun.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					}
					else if (g_Player.nType == PLAYERTYPE_POWER)
					{
						D3DXLoadMeshFromX("data/MODEL/exo_power/weapon/exo_P_Gun_weapon.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
							&g_Player.aModel[15].pBuffMat, NULL, &g_Player.aModel[15].nNumMat, &g_Player.aModel[15].pMesh);
						//g_Gun.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					}

				}
				else if (g_Player.bWeapon == true)
				{
					if (g_Player.nType == PLAYERTYPE_SPEED)
					{
						D3DXLoadMeshFromX("data/MODEL/exo_speed/weapon/exo_S_Sword_weapon.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
							&g_Player.aModel[15].pBuffMat, NULL, &g_Player.aModel[15].nNumMat, &g_Player.aModel[15].pMesh);
					}
					else if (g_Player.nType == PLAYERTYPE_POWER)
					{
						D3DXLoadMeshFromX("data/MODEL/exo_power/weapon/exo_P_Sword_weapon.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
							&g_Player.aModel[15].pBuffMat, NULL, &g_Player.aModel[15].nNumMat, &g_Player.aModel[15].pMesh);
					}
				}
				g_Player.bEvolutionButton = false;
			}

			if (g_Player.bDegenerate == true)
			{
				PlaySound(SOUND_LABEL_GRADEEND);
				for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
				{
					if (pBullet->bUse == true)
					{
						pBullet->bUse = false;
					}
				}
				//�f�o�C�X�̎擾
				LPDIRECT3DDEVICE9 pDevice;
				pDevice = GetDevice();
				//X�t�@�C���ǂݍ���
				D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_body_00.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
					&g_Player.aModel[0].pBuffMat, NULL, &g_Player.aModel[0].nNumMat, &g_Player.aModel[0].pMesh);
				D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_body_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
					&g_Player.aModel[1].pBuffMat, NULL, &g_Player.aModel[1].nNumMat, &g_Player.aModel[1].pMesh);
				D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_body_02.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
					&g_Player.aModel[2].pBuffMat, NULL, &g_Player.aModel[2].nNumMat, &g_Player.aModel[2].pMesh);
				D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_arm_R_03.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
					&g_Player.aModel[3].pBuffMat, NULL, &g_Player.aModel[3].nNumMat, &g_Player.aModel[3].pMesh);
				D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_arm_R_04.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
					&g_Player.aModel[4].pBuffMat, NULL, &g_Player.aModel[4].nNumMat, &g_Player.aModel[4].pMesh);
				D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_arm_R_05.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
					&g_Player.aModel[5].pBuffMat, NULL, &g_Player.aModel[5].nNumMat, &g_Player.aModel[5].pMesh);
				D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_arm_R_06.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
					&g_Player.aModel[6].pBuffMat, NULL, &g_Player.aModel[6].nNumMat, &g_Player.aModel[6].pMesh);
				D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_arm_L_07.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
					&g_Player.aModel[7].pBuffMat, NULL, &g_Player.aModel[7].nNumMat, &g_Player.aModel[7].pMesh);
				D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_arm_L_08.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
					&g_Player.aModel[8].pBuffMat, NULL, &g_Player.aModel[8].nNumMat, &g_Player.aModel[8].pMesh);
				D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_arm_L_09.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
					&g_Player.aModel[9].pBuffMat, NULL, &g_Player.aModel[9].nNumMat, &g_Player.aModel[9].pMesh);
				D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_arm_L_10.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
					&g_Player.aModel[10].pBuffMat, NULL, &g_Player.aModel[10].nNumMat, &g_Player.aModel[10].pMesh);
				D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_leg_R_11.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
					&g_Player.aModel[11].pBuffMat, NULL, &g_Player.aModel[11].nNumMat, &g_Player.aModel[11].pMesh);
				D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_leg_R_12.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
					&g_Player.aModel[12].pBuffMat, NULL, &g_Player.aModel[12].nNumMat, &g_Player.aModel[12].pMesh);
				D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_leg_L_13.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
					&g_Player.aModel[13].pBuffMat, NULL, &g_Player.aModel[13].nNumMat, &g_Player.aModel[13].pMesh);
				D3DXLoadMeshFromX("data/MODEL/exo_nomal/N_exo_leg_L_14.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
					&g_Player.aModel[14].pBuffMat, NULL, &g_Player.aModel[14].nNumMat, &g_Player.aModel[14].pMesh);

				g_Player.nType = PLAYERTYPE_NOMAL;

				if (g_Player.bWeapon == false)
				{
					D3DXLoadMeshFromX("data/MODEL/exo_nomal/weapon/exo_N_Gun_weapon.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[15].pBuffMat, NULL, &g_Player.aModel[15].nNumMat, &g_Player.aModel[15].pMesh);
				}
				else if (g_Player.bWeapon == true)
				{
					D3DXLoadMeshFromX("data/MODEL/exo_nomal/weapon/exo_N_Sword_weapon.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
						&g_Player.aModel[15].pBuffMat, NULL, &g_Player.aModel[15].nNumMat, &g_Player.aModel[15].pMesh);
				}
				g_Player.bDegenerate = false;
			}
		}
	}

	//-------------------------------------------------
	//�v���C���[�̈ړ�����
	//-------------------------------------------------
	if (g_Player.pos.x >= PLAYER_LIMIT)
	{
		g_Player.pos.x = PLAYER_LIMIT;
	}
	else if (g_Player.pos.x <= -PLAYER_LIMIT)
	{
		g_Player.pos.x = -PLAYER_LIMIT;
	}
	if (g_Player.pos.z >= PLAYER_LIMIT)
	{
		g_Player.pos.z = PLAYER_LIMIT;
	}
	else if (g_Player.pos.z <= -PLAYER_LIMIT)
	{
		g_Player.pos.z = -PLAYER_LIMIT;
	}
	if (g_Player.pos.y <= 30.0f)
	{
		g_Player.pos.y = 30.0f;
		g_Player.move.y = 0.0f;
		g_Player.bJump = false;
	}

	


	


	//�e�̐ݒ�
	SetPositionShadow(g_Player.nIdx, g_Player.pos, g_Player.bUse);
	

	if (g_Player.bUse == false)
	{
		g_Player.MotionType = MOTIONTYPE_DOWN;
		g_Player.nTitle++;
		g_Player.nEffect++;
		SetMask(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2.0f, 0.0f), MASKTYPE_GAMEOVER, SCREEN_WIDTH, SCREEN_HEIGHT);
		if (g_Player.nEffect >= 10)
		{
			g_Player.nEffect = 0;
			for (int nCnt = 0; nCnt < 16; nCnt++)
			{
				SetEffect(D3DXVECTOR3(g_Player.aModel[0].mtxWorld._41 - 2.0f, g_Player.aModel[0].mtxWorld._42, g_Player.aModel[0].mtxWorld._43),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15.0f, 15.0f, D3DXCOLOR(10, 10, 10, 255), 20, EFFEFCT_MOVETYPE_PLAYER_LIFE_LOW);
				SetEffect(D3DXVECTOR3(g_Player.aModel[0].mtxWorld._41 + 2.0f, g_Player.aModel[0].mtxWorld._42 + 5.0f, g_Player.aModel[0].mtxWorld._43),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15.0f, 15.0f, D3DXCOLOR(255, 255, 255, 255), 20, EFFEFCT_MOVETYPE_PLAYER_LIFE_LOW);
			}
		}
		if (g_Player.nTitle >= 300 && GetFade() == FADE_NONE)
		{
			g_Player.nTitle = 0;
			SetFade(MODE_TITLE);
		}
	}
	
	//=======================================================================
	//���[�V����
	//=======================================================================
	if (g_Player.MotionType != g_Player.MotionTypeOld)
	{
		g_Player.nKey = 0;
		g_Player.fCounterMotion = 0.0f;
	}
	MotionPlayer();

	g_Player.VtxPosSave[0].x = g_Player.pos.x + (sinf(g_Player.rot.y + D3DX_PI / 4.0f) * 35.0f);
	g_Player.VtxPosSave[0].z = g_Player.pos.z + (cosf(g_Player.rot.y + D3DX_PI / 4.0f) * 35.0f);
	g_Player.VtxPosSave[1].x = g_Player.pos.x + (sinf(g_Player.rot.y + D3DX_PI / 4.0f * 3.0f) * 35.0f);
	g_Player.VtxPosSave[1].z = g_Player.pos.z + (cosf(g_Player.rot.y + D3DX_PI / 4.0f * 3.0f) * 35.0f);
	g_Player.VtxPosSave[2].x = g_Player.pos.x + (sinf(g_Player.rot.y - D3DX_PI / 4.0f) * 35.0f);
	g_Player.VtxPosSave[2].z = g_Player.pos.z + (cosf(g_Player.rot.y - D3DX_PI / 4.0f) * 35.0f);
	g_Player.VtxPosSave[3].x = g_Player.pos.x + (sinf(g_Player.rot.y - D3DX_PI / 4.0f * 3.0f) * 35.0f);
	g_Player.VtxPosSave[3].z = g_Player.pos.z + (cosf(g_Player.rot.y - D3DX_PI / 4.0f * 3.0f) * 35.0f);

	//���f���Ƃ̓����蔻��
	CollisionModelTxt(&g_Player.move, &g_Player.pos, &g_Player.posOld, g_Player.fWidth);
	//CollisionModel(&g_Player.pos, &g_Player.posOld, &g_Player.move, g_Player.fWidth, g_Player.fHeight, g_Player.fWidth);
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����

	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	D3DXMatrixIdentity(&g_Player.mtxWorld);		//�v���C���[�̃��[���h�}�g���b�N�X�̏�����

	//�v���C���[�̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	//�v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	//���݂̃}�e���A����ۑ�
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;		//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;						//�e�̃}�g���b�N�X

		D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);		//�e�p�[�c�̃��[���h�}�g���b�N�X�̏�����

		//�e�p�[�c�̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		//�e�p�[�c�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransModel, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		//�e�p�[�c�̐e�̃}�g���b�N�X�̐ݒ�
		if (g_Player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_Player.mtxWorld;
		}

		//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxParent);

		//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorld);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nNumMat; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
			//pDevice->SetTexture(0, g_apTexturePlayer[nCntMat]);

			//���f��(�p�[�c)�̕`��
			g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	//�e�̐ݒ�

	D3DXMatrixIdentity(&g_Gun.mtxWorld);		//�v���C���[�̃��[���h�}�g���b�N�X�̏�����

												//�v���C���[�̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Gun.rot.y, g_Gun.rot.x, g_Gun.rot.z);
	D3DXMatrixMultiply(&g_Gun.mtxWorld, &g_Gun.mtxWorld, &mtxRot);

	//�v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Gun.pos.x, g_Gun.pos.y, g_Gun.pos.z);
	D3DXMatrixMultiply(&g_Gun.mtxWorld, &g_Gun.mtxWorld, &mtxTrans);

	D3DXMATRIX mtxParent;						//�e�̃}�g���b�N�X
	mtxParent = g_Player.aModel[15].mtxWorld;

	//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&g_Gun.mtxWorld, &g_Gun.mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Gun.mtxWorld);

	//���̐ݒ�
	D3DXMatrixIdentity(&g_Sword.mtxWorld);		//�v���C���[�̃��[���h�}�g���b�N�X�̏�����

												//�v���C���[�̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Sword.rot.y, g_Sword.rot.x, g_Sword.rot.z);
	D3DXMatrixMultiply(&g_Sword.mtxWorld, &g_Sword.mtxWorld, &mtxRot);

	//�v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Sword.pos.x, g_Sword.pos.y, g_Sword.pos.z);
	D3DXMatrixMultiply(&g_Sword.mtxWorld, &g_Sword.mtxWorld, &mtxTrans);

	mtxParent = g_Player.aModel[15].mtxWorld;

	//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&g_Sword.mtxWorld, &g_Sword.mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Sword.mtxWorld);

	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
	{
		//4���_�̐ݒ�
		D3DXMatrixIdentity(&g_Player.VtxMtxWorld[nCntVtx]);		//�v���C���[�̃��[���h�}�g���b�N�X�̏�����

		//�v���C���[�̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.VtxRot[nCntVtx].y, g_Player.VtxRot[nCntVtx].x, g_Player.VtxRot[nCntVtx].z);
		D3DXMatrixMultiply(&g_Player.VtxMtxWorld[nCntVtx], &g_Player.VtxMtxWorld[nCntVtx], &mtxRot);

		//�v���C���[�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player.VtxPos[nCntVtx].x, g_Player.VtxPos[nCntVtx].y, g_Player.VtxPos[nCntVtx].z);
		D3DXMatrixMultiply(&g_Player.VtxMtxWorld[nCntVtx], &g_Player.VtxMtxWorld[nCntVtx], &mtxTrans);

		mtxParent = g_Player.mtxWorld;

		//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_Player.VtxMtxWorld[nCntVtx], &g_Player.VtxMtxWorld[nCntVtx], &mtxParent);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.VtxMtxWorld[nCntVtx]);
	}
}

//=======================================================================
//���[�V��������
//=======================================================================
void MotionPlayer(void)
{
	Camera *pCamera = GetCamera();
	DRONE *pDrone = GetDrone();
	ENEMY *pEnemy = GetEnemy();
	ENEMY *pEnemy2 = GetAttackEnemy();

	D3DXVECTOR3 posAsk[MAX_PLAYER_MODEL];		//���߂����l
	D3DXVECTOR3 rotAsk[MAX_PLAYER_MODEL];		//���߂����l
	D3DXVECTOR3 posDiffer[MAX_PLAYER_MODEL];	//����
	D3DXVECTOR3 rotDiffer[MAX_PLAYER_MODEL];	//����

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel - 1; nCntModel++)
	{
		if (g_Player.nKey < g_Player.aMotionInfo[g_Player.MotionType].nNumKey - 1)//�L�[�̍ő吔-1
		{
			posDiffer[nCntModel].x = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey + 1].aKey[nCntModel].fPosX
				- g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosX;
			posDiffer[nCntModel].y = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey + 1].aKey[nCntModel].fPosY
				- g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosY;
			posDiffer[nCntModel].z = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey + 1].aKey[nCntModel].fPosZ
				- g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosZ;
			rotDiffer[nCntModel].x = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey + 1].aKey[nCntModel].fRotX
				- g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotX;
			rotDiffer[nCntModel].y = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey + 1].aKey[nCntModel].fRotY
				- g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotY;
			rotDiffer[nCntModel].z = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey + 1].aKey[nCntModel].fRotZ
				- g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotZ;

			posAsk[nCntModel].x = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosX
				+ posDiffer[nCntModel].x * (g_Player.fCounterMotion / g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].nFrame);
			posAsk[nCntModel].y = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosY
				+ posDiffer[nCntModel].y * (g_Player.fCounterMotion / g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].nFrame);
			posAsk[nCntModel].z = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosZ
				+ posDiffer[nCntModel].z * (g_Player.fCounterMotion / g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].nFrame);
			rotAsk[nCntModel].x = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotX
				+ rotDiffer[nCntModel].x * (g_Player.fCounterMotion / g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].nFrame);
			rotAsk[nCntModel].y = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotY
				+ rotDiffer[nCntModel].y * (g_Player.fCounterMotion / g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].nFrame);
			rotAsk[nCntModel].z = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotZ
				+ rotDiffer[nCntModel].z * (g_Player.fCounterMotion / g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].nFrame);

			g_Player.aModel[nCntModel].pos.x = posAsk[nCntModel].x;
			g_Player.aModel[nCntModel].pos.y = posAsk[nCntModel].y;
			g_Player.aModel[nCntModel].pos.z = posAsk[nCntModel].z;
			g_Player.aModel[nCntModel].rot.x = rotAsk[nCntModel].x;
			g_Player.aModel[nCntModel].rot.y = rotAsk[nCntModel].y;
			g_Player.aModel[nCntModel].rot.z = rotAsk[nCntModel].z;
		}
		else if (g_Player.nKey >= g_Player.aMotionInfo[g_Player.MotionType].nNumKey - 1)//�L�[�̍ő吔-1
		{
			if (g_Player.aMotionInfo[g_Player.MotionType].bLoop == 1)
			{
				posDiffer[nCntModel].x = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[0].aKey[nCntModel].fPosX
					- g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosX;
				posDiffer[nCntModel].y = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[0].aKey[nCntModel].fPosY
					- g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosY;
				posDiffer[nCntModel].z = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[0].aKey[nCntModel].fPosZ
					- g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosZ;
				rotDiffer[nCntModel].x = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[0].aKey[nCntModel].fRotX
					- g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotX;
				rotDiffer[nCntModel].y = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[0].aKey[nCntModel].fRotY
					- g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotY;
				rotDiffer[nCntModel].z = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[0].aKey[nCntModel].fRotZ
					- g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotZ;

				posAsk[nCntModel].x = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosX
					+ posDiffer[nCntModel].x * (g_Player.fCounterMotion / g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].nFrame);
				posAsk[nCntModel].y = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosY
					+ posDiffer[nCntModel].y * (g_Player.fCounterMotion / g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].nFrame);
				posAsk[nCntModel].z = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosZ
					+ posDiffer[nCntModel].z * (g_Player.fCounterMotion / g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].nFrame);
				rotAsk[nCntModel].x = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotX
					+ rotDiffer[nCntModel].x * (g_Player.fCounterMotion / g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].nFrame);
				rotAsk[nCntModel].y = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotY
					+ rotDiffer[nCntModel].y * (g_Player.fCounterMotion / g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].nFrame);
				rotAsk[nCntModel].z = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotZ
					+ rotDiffer[nCntModel].z * (g_Player.fCounterMotion / g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].nFrame);

				g_Player.aModel[nCntModel].pos.x = posAsk[nCntModel].x;
				g_Player.aModel[nCntModel].pos.y = posAsk[nCntModel].y;
				g_Player.aModel[nCntModel].pos.z = posAsk[nCntModel].z;
				g_Player.aModel[nCntModel].rot.x = rotAsk[nCntModel].x;
				g_Player.aModel[nCntModel].rot.y = rotAsk[nCntModel].y;
				g_Player.aModel[nCntModel].rot.z = rotAsk[nCntModel].z;
			}
			else if (g_Player.aMotionInfo[g_Player.MotionType].bLoop == 0)
			{
				posDiffer[nCntModel].x = g_Player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[nCntModel].fPosX
					- g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosX;
				posDiffer[nCntModel].y = g_Player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[nCntModel].fPosY
					- g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosY;
				posDiffer[nCntModel].z = g_Player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[nCntModel].fPosZ
					- g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosZ;
				rotDiffer[nCntModel].x = g_Player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[nCntModel].fRotX
					- g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotX;
				rotDiffer[nCntModel].y = g_Player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[nCntModel].fRotY
					- g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotY;
				rotDiffer[nCntModel].z = g_Player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[nCntModel].fRotZ
					- g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotZ;

				posAsk[nCntModel].x = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosX
					+ posDiffer[nCntModel].x * (g_Player.fCounterMotion / g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].nFrame);
				posAsk[nCntModel].y = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosY
					+ posDiffer[nCntModel].y * (g_Player.fCounterMotion / g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].nFrame);
				posAsk[nCntModel].z = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosZ
					+ posDiffer[nCntModel].z * (g_Player.fCounterMotion / g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].nFrame);
				rotAsk[nCntModel].x = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotX
					+ rotDiffer[nCntModel].x * (g_Player.fCounterMotion / g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].nFrame);
				rotAsk[nCntModel].y = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotY
					+ rotDiffer[nCntModel].y * (g_Player.fCounterMotion / g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].nFrame);
				rotAsk[nCntModel].z = g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotZ
					+ rotDiffer[nCntModel].z * (g_Player.fCounterMotion / g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].nFrame);

				g_Player.aModel[nCntModel].pos.x = posAsk[nCntModel].x;
				g_Player.aModel[nCntModel].pos.y = posAsk[nCntModel].y;
				g_Player.aModel[nCntModel].pos.z = posAsk[nCntModel].z;
				g_Player.aModel[nCntModel].rot.x = rotAsk[nCntModel].x;
				g_Player.aModel[nCntModel].rot.y = rotAsk[nCntModel].y;
				g_Player.aModel[nCntModel].rot.z = rotAsk[nCntModel].z;
			}
		}
	}

	g_Player.aModel[15].pos.x = posAsk[6].x;
	g_Player.aModel[15].pos.y = posAsk[6].y;
	g_Player.aModel[15].pos.z = posAsk[6].z;
	
	if (g_Player.MotionType == MOTIONTYPE_SHOOT_N && g_Player.nKey == 1)
	{
		if (g_Player.fCounterMotion == 0.0f || g_Player.fCounterMotion == 9.0f || g_Player.fCounterMotion == 18.0f)
		{
			PlaySound(SOUND_LABEL_BULLET);
			SetBullet(D3DXVECTOR3(g_Gun.mtxWorld._41, g_Gun.mtxWorld._42, g_Gun.mtxWorld._43),
				D3DXVECTOR3(sinf(g_Player.rot.y) * BULLET_SPEED, 0.0f, cosf(g_Player.rot.y) * BULLET_SPEED),
				15.0f, 15.0f, D3DXCOLOR(255, 255, 255, 255));
		}
	}
	else if (g_Player.MotionType == MOTIONTYPE_SHOOT_P && g_Player.nKey == 1)
	{
		if (g_Player.fCounterMotion == 0.0f)
		{
			PlaySound(SOUND_LABEL_BULLET_P);
			SetBullet(D3DXVECTOR3(g_Gun.mtxWorld._41, g_Gun.mtxWorld._42, g_Gun.mtxWorld._43),
				D3DXVECTOR3(sinf(g_Player.rot.y) * BULLET_SPEED, 0.0f, cosf(g_Player.rot.y) * BULLET_SPEED),
				140.0f, 140.0f, D3DXCOLOR(255, 255, 255, 255));
		}
	}
	else if (g_Player.MotionType == MOTIONTYPE_SHOOT_S && g_Player.nKey == 1)
	{
		if (g_Player.fCounterMotion == 0.0f || g_Player.fCounterMotion == 4.0f || g_Player.fCounterMotion == 8.0f)
		{
			PlaySound(SOUND_LABEL_BULLET);
			SetBullet(D3DXVECTOR3(g_Gun.mtxWorld._41, g_Gun.mtxWorld._42, g_Gun.mtxWorld._43),
				D3DXVECTOR3(sinf(g_Player.rot.y) * BULLET_SPEED, 0.0f, cosf(g_Player.rot.y) * BULLET_SPEED),
				10.0f, 10.0f, D3DXCOLOR(255, 255, 255, 255));
		}
	}
	else if ((g_Player.MotionType == MOTIONTYPE_SLASH_N || g_Player.MotionType == MOTIONTYPE_SLASH_S || g_Player.MotionType == MOTIONTYPE_SLASH_P ||
				g_Player.MotionType == MOTIONTYPE_SLASH_N1 || g_Player.MotionType == MOTIONTYPE_SLASH_S1 || g_Player.MotionType == MOTIONTYPE_SLASH_P1 ||
				g_Player.MotionType == MOTIONTYPE_SLASH_N2 || g_Player.MotionType == MOTIONTYPE_SLASH_S2 || g_Player.MotionType == MOTIONTYPE_SLASH_P2) && 
				g_Player.nKey == 1)
	{
		if (g_Player.nKey == 1 && g_Player.fCounterMotion == 0.0f && 
			(g_Player.MotionType == MOTIONTYPE_SLASH_N || g_Player.MotionType == MOTIONTYPE_SLASH_P || g_Player.MotionType == MOTIONTYPE_SLASH_S))
		{
			PlaySound(SOUND_LABEL_SLASH_000);
		}
		else if (g_Player.nKey == 1 && g_Player.fCounterMotion == 0.0f &&
			(g_Player.MotionType == MOTIONTYPE_SLASH_N1 || g_Player.MotionType == MOTIONTYPE_SLASH_P1 || g_Player.MotionType == MOTIONTYPE_SLASH_S1))
		{
			PlaySound(SOUND_LABEL_SLASH_001);
		}
		else if (g_Player.nKey == 1 && g_Player.fCounterMotion == 0.0f &&
			(g_Player.MotionType == MOTIONTYPE_SLASH_N2 || g_Player.MotionType == MOTIONTYPE_SLASH_P2 || g_Player.MotionType == MOTIONTYPE_SLASH_S2))
		{
			PlaySound(SOUND_LABEL_SLASH_002);
		}
		g_Player.bSlash = true;
	}
	

	g_Player.fCounterMotion += 1.0f;
	if (g_Player.fCounterMotion >= g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].nFrame)
	{
		if (g_Player.nKey < g_Player.aMotionInfo[g_Player.MotionType].nNumKey - 1)//�L�[�̍ő吔-1
		{
			g_Player.nKey++;
			g_Player.fCounterMotion = 0.0f;
		}
		else if (g_Player.nKey >= g_Player.aMotionInfo[g_Player.MotionType].nNumKey - 1)
		{
			g_Player.nKey = 0;
			g_Player.fCounterMotion = 0.0f;
			g_Player.bSlash = false;

			if (g_Player.MotionTypeNext == MOTIONTYPE_SLASH_N1)
			{
				g_Player.MotionType = MOTIONTYPE_SLASH_N1;
				g_Player.MotionTypeNext = MOTIONTYPE_NEUTRAL;

				InputPlayer();
			}
			else if (g_Player.MotionTypeNext == MOTIONTYPE_SLASH_N2)
			{
				g_Player.MotionType = MOTIONTYPE_SLASH_N2;
				g_Player.MotionTypeNext = MOTIONTYPE_NEUTRAL;

				InputPlayer();
			}
			else if (g_Player.MotionTypeNext == MOTIONTYPE_SLASH_S1)
			{
				g_Player.MotionType = MOTIONTYPE_SLASH_S1;
				g_Player.MotionTypeNext = MOTIONTYPE_NEUTRAL;

				InputPlayer();
			}
			else if (g_Player.MotionTypeNext == MOTIONTYPE_SLASH_S2)
			{
				g_Player.MotionType = MOTIONTYPE_SLASH_S2;
				g_Player.MotionTypeNext = MOTIONTYPE_NEUTRAL;

				InputPlayer();
			}
			else if (g_Player.MotionTypeNext == MOTIONTYPE_SLASH_P1)
			{
				g_Player.MotionType = MOTIONTYPE_SLASH_P1;
				g_Player.MotionTypeNext = MOTIONTYPE_NEUTRAL;

				InputPlayer();
			}
			else if (g_Player.MotionTypeNext == MOTIONTYPE_SLASH_P2)
			{
				g_Player.MotionType = MOTIONTYPE_SLASH_P2;
				g_Player.MotionTypeNext = MOTIONTYPE_NEUTRAL;

				InputPlayer();
			}
			else if (g_Player.aMotionInfo[g_Player.MotionType].bLoop == 0)
			{
				g_Player.MotionType = MOTIONTYPE_NEUTRAL;
			}
		}
	}
}

//=======================================================================
//�v���C���[�Ƃ̓����蔻��
//=======================================================================
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth)
{
	bool bColl = false;	//�������Ă��邩�ǂ���
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	if (pPos->x > pPlayer->pos.x - pPlayer->fWidth / 2.0f - fWidth / 2.0f &&
		pPos->x < pPlayer->pos.x + pPlayer->fWidth / 2.0f + fWidth / 2.0f &&
		pPos->z > pPlayer->pos.z - pPlayer->fDepth / 2.0f - fDepth / 2.0f &&
		pPos->z < pPlayer->pos.z + pPlayer->fDepth / 2.0f + fDepth / 2.0f &&
		pPos->y <= pPlayer->pos.y + pPlayer->fHeight &&
		pBeforePos->y >= pPlayer->pos.y + pPlayer->fHeight)
	{
		pPos->y = pPlayer->pos.y + pPlayer->fHeight;
		pMove->y = 0.0f;
	}
	else if (pPos->x > pPlayer->pos.x - pPlayer->fWidth / 2.0f - fWidth / 2.0f &&
		pPos->x < pPlayer->pos.x + pPlayer->fWidth / 2.0f + fWidth / 2.0f &&
		pPos->z > pPlayer->pos.z - pPlayer->fDepth / 2.0f - fDepth / 2.0f &&
		pPos->z < pPlayer->pos.z + pPlayer->fDepth / 2.0f + fDepth / 2.0f &&
		pPos->y >= pPlayer->pos.y - fHeight &&
		pBeforePos->y <= pPlayer->pos.y - fHeight)
	{
		pPos->y = pPlayer->pos.y - fHeight;
	}

	if (pPos->y < pPlayer->pos.y + pPlayer->fHeight &&
		pPos->y > pPlayer->pos.y - fHeight &&
		pPos->z > pPlayer->pos.z - pPlayer->fDepth / 2.0f - fDepth / 2.0f &&
		pPos->z < pPlayer->pos.z + pPlayer->fDepth / 2.0f + fDepth / 2.0f &&
		pPos->x >= pPlayer->pos.x - pPlayer->fWidth / 2.0f - fWidth / 2.0f &&
		pBeforePos->x <= pPlayer->pos.x - pPlayer->fWidth / 2.0f - fWidth / 2.0f)
	{
		pPos->x = pPlayer->pos.x - pPlayer->fWidth / 2.0f - fWidth / 2.0f;
		bColl = true;
	}
	else if (pPos->y < pPlayer->pos.y + pPlayer->fHeight &&
		pPos->y > pPlayer->pos.y - fHeight &&
		pPos->z > pPlayer->pos.z - pPlayer->fDepth / 2.0f - fDepth / 2.0f &&
		pPos->z < pPlayer->pos.z + pPlayer->fDepth / 2.0f + fDepth / 2.0f &&
		pPos->x <= pPlayer->pos.x + pPlayer->fWidth / 2.0f + fWidth / 2.0f &&
		pBeforePos->x >= pPlayer->pos.x + pPlayer->fWidth / 2.0f + fWidth / 2.0f)
	{
		pPos->x = pPlayer->pos.x + pPlayer->fWidth / 2.0f + fWidth / 2.0f;
		bColl = true;
	}

	if (pPos->y < pPlayer->pos.y + pPlayer->fHeight &&
		pPos->y > pPlayer->pos.y - fHeight &&
		pPos->x > pPlayer->pos.x - pPlayer->fWidth / 2.0f - fWidth / 2.0f &&
		pPos->x < pPlayer->pos.x + pPlayer->fWidth / 2.0f + fWidth / 2.0f &&
		pPos->z >= pPlayer->pos.z - pPlayer->fDepth / 2.0f - fDepth / 2.0f &&
		pBeforePos->z <= pPlayer->pos.z - pPlayer->fDepth / 2.0f - fDepth / 2.0f)
	{
		pPos->z = pPlayer->pos.z - pPlayer->fDepth / 2.0f - fDepth / 2.0f;
		bColl = true;
	}
	else if (pPos->y < pPlayer->pos.y + pPlayer->fHeight &&
		pPos->y > pPlayer->pos.y - fHeight &&
		pPos->x > pPlayer->pos.x - pPlayer->fWidth / 2.0f - fWidth / 2.0f &&
		pPos->x < pPlayer->pos.x + pPlayer->fWidth / 2.0f + fWidth / 2.0f &&
		pPos->z <= pPlayer->pos.z + pPlayer->fDepth / 2.0f + fDepth / 2.0f &&
		pBeforePos->z >= pPlayer->pos.z + pPlayer->fDepth / 2.0f + fDepth / 2.0f)
	{
		pPos->z = pPlayer->pos.z + pPlayer->fDepth / 2.0f + fDepth / 2.0f;
		bColl = true;
	}
	return bColl;
}

//=======================================================================
//���Ƃ̓����蔻��
//=======================================================================
bool CollisionSword(D3DXVECTOR3 *pPos, float fWidth)
{
	PLAYER *pPlayer = GetPlayer();
	bool bDamage = false;			//�������Ă��邩�ǂ���

	if (g_Sword.mtxWorld._41 >= pPos->x - fWidth / 2.0f && g_Sword.mtxWorld._41 <= pPos->x + fWidth / 2.0f &&
		g_Sword.mtxWorld._43 >= pPos->z - fWidth / 2.0f && g_Sword.mtxWorld._43 <= pPos->z + fWidth / 2.0f)
	{
		bDamage = true;
	}

	return bDamage;
}

//=======================================================================
//�a�����̓��͏���
//=======================================================================
void InputPlayer(void)
{
	Camera *pCamera = GetCamera();

	if (GetLeftStick(STICKTYPE_UP) == true)
	{
		if (GetLeftStick(STICKTYPE_RIGHT) == true)
		{
			g_Player.move.x += +cosf(pCamera->rot.y - D3DX_PI / 4.0f) * PLAYER_SLASH_MOVE;
			g_Player.move.z += -sinf(pCamera->rot.y - D3DX_PI / 4.0f) * PLAYER_SLASH_MOVE;

			g_Player.fNumTurnPlayer = pCamera->rot.y + D3DX_PI / 4.0f;
			g_Player.bTurnPlayer = true;
		}
		else if (GetLeftStick(STICKTYPE_LEFT) == true)
		{
			g_Player.move.x += -cosf(pCamera->rot.y + D3DX_PI / 4.0f) * PLAYER_SLASH_MOVE;
			g_Player.move.z += +sinf(pCamera->rot.y + D3DX_PI / 4.0f) * PLAYER_SLASH_MOVE;

			g_Player.fNumTurnPlayer = pCamera->rot.y - D3DX_PI / 4.0f;
			g_Player.bTurnPlayer = true;
		}
		else
		{
			g_Player.move.z += +cosf(pCamera->rot.y) * PLAYER_SLASH_MOVE;
			g_Player.move.x += +sinf(pCamera->rot.y) * PLAYER_SLASH_MOVE;

			g_Player.fNumTurnPlayer = pCamera->rot.y;
			g_Player.bTurnPlayer = true;

		}

	}
	else if (GetLeftStick(STICKTYPE_DOWN) == true)
	{
		if (GetLeftStick(STICKTYPE_RIGHT) == true)
		{
			g_Player.move.x += +cosf(pCamera->rot.y + D3DX_PI / 4.0f) * PLAYER_SLASH_MOVE;
			g_Player.move.z += -sinf(pCamera->rot.y + D3DX_PI / 4.0f) * PLAYER_SLASH_MOVE;

			g_Player.fNumTurnPlayer = pCamera->rot.y + D3DX_PI / 1.5f;
			g_Player.bTurnPlayer = true;
		}
		else if (GetLeftStick(STICKTYPE_LEFT) == true)
		{
			g_Player.move.x += -cosf(pCamera->rot.y - D3DX_PI / 4.0f) * PLAYER_SLASH_MOVE;
			g_Player.move.z += +sinf(pCamera->rot.y - D3DX_PI / 4.0f) * PLAYER_SLASH_MOVE;

			g_Player.fNumTurnPlayer = pCamera->rot.y - (D3DX_PI / 4.0f) * 3.0f;
			g_Player.bTurnPlayer = true;
		}
		else
		{
			g_Player.fNumTurnPlayer = pCamera->rot.y + D3DX_PI;

			g_Player.move.z += -cosf(pCamera->rot.y) * PLAYER_SLASH_MOVE;
			g_Player.move.x += -sinf(pCamera->rot.y) * PLAYER_SLASH_MOVE;

			g_Player.bTurnPlayer = true;
		}
	}
	else if (GetLeftStick(STICKTYPE_RIGHT) == true)
	{
		g_Player.move.x += +cosf(pCamera->rot.y) * PLAYER_SLASH_MOVE;
		g_Player.move.z += -sinf(pCamera->rot.y) * PLAYER_SLASH_MOVE;

		g_Player.fNumTurnPlayer = pCamera->rot.y + D3DX_PI / 2.0f;
		g_Player.bTurnPlayer = true;
	}
	else if (GetLeftStick(STICKTYPE_LEFT) == true)
	{
		g_Player.move.x += -cosf(pCamera->rot.y) * PLAYER_SLASH_MOVE;
		g_Player.move.z += +sinf(pCamera->rot.y) * PLAYER_SLASH_MOVE;

		g_Player.fNumTurnPlayer = pCamera->rot.y - D3DX_PI / 2.0f;
		g_Player.bTurnPlayer = true;
	}
}

//=======================================================================
//�擾����
//=======================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}