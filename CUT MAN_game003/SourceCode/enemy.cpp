//=======================================================================
//�G�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "enemy.h"
#include "shadow.h"
#include "bullet.h"
#include "model.h"
#include "player.h"
#include "enemylife.h"
#include "pad.h"
#include "fade.h"
#include "ui.h"
#include "life.h"
#include "mask.h"
#include "sound.h"
#include "score.h"
#include "effect.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
ENEMY g_aEnemy[MAX_ENEMY];				//�v���C���[�̍\����
int g_nCntEnemy;						//�G�̐��Ԃ�񂷂��߂ɕK�v
int g_nCntAllEnemy;						//�G�̌��݂̑���
int g_nAttackEnemy;						//���̓����蔻��ɕK�v

//=======================================================================
//����������
//=======================================================================
void InitEnemy(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//������
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].aMotionInfo->bLoop = false;
		g_aEnemy[nCntEnemy].aMotionInfo->nNumKey = 0;
		g_aEnemy[nCntEnemy].aMotionInfo->aKeyInfo->nFrame = 0;
		g_aEnemy[nCntEnemy].aMotionInfo->aKeyInfo->aKey->fPosX = 0;
		g_aEnemy[nCntEnemy].aMotionInfo->aKeyInfo->aKey->fPosY = 0;
		g_aEnemy[nCntEnemy].aMotionInfo->aKeyInfo->aKey->fPosZ = 0;
		g_aEnemy[nCntEnemy].aMotionInfo->aKeyInfo->aKey->fRotX = 0;
		g_aEnemy[nCntEnemy].aMotionInfo->aKeyInfo->aKey->fRotY = 0;
		g_aEnemy[nCntEnemy].aMotionInfo->aKeyInfo->aKey->fRotZ = 0;
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].posPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nNumModel = MAX_ENEMY_MODEL;
		g_aEnemy[nCntEnemy].nNumMotion = 9;
		g_aEnemy[nCntEnemy].bLoopMotion = false;
		g_aEnemy[nCntEnemy].nNumKey = 0;
		g_aEnemy[nCntEnemy].nKey = 0;
		g_aEnemy[nCntEnemy].fCounterMotion = 0.0f;
		g_aEnemy[nCntEnemy].bJump = false;
		g_aEnemy[nCntEnemy].bSlash = false;
		g_aEnemy[nCntEnemy].bDamage = false;
		g_aEnemy[nCntEnemy].fWidth = 50.0f;
		g_aEnemy[nCntEnemy].fHeight = 4000.0f;
		g_aEnemy[nCntEnemy].fDepth = 50.0f;
		g_aEnemy[nCntEnemy].fNumTurnEnemy = 0.0f;
		g_aEnemy[nCntEnemy].fNumEnemy = 0.0f;
		g_aEnemy[nCntEnemy].fDifferRot = 0.0f;
		g_aEnemy[nCntEnemy].frotVecX = 0.0f;
		g_aEnemy[nCntEnemy].frotVecZ = 0.0f;
		g_aEnemy[nCntEnemy].fToPlayerR = 0.0f;
		g_aEnemy[nCntEnemy].fSwordCollX = 0.0f;
		g_aEnemy[nCntEnemy].fSwordCollZ = 0.0f;
		g_aEnemy[nCntEnemy].bTurnEnemy = false;
		g_aEnemy[nCntEnemy].bTurnEnemy2 = false;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].bPlayerDamage = false;
		g_aEnemy[nCntEnemy].nCntMoveTime = 0;
		g_aEnemy[nCntEnemy].nCntStop = 0;
		g_aEnemy[nCntEnemy].nIdx = 0;
		for (int nCnt =0; nCnt < MAX_EFFECT; nCnt++)
		{
			g_aEnemy[nCntEnemy].nIdxEffect[nCnt] = 0;
		}
		g_aEnemy[nCntEnemy].nLife = MAX_ENEMY_LIFE;
		g_aEnemy[nCntEnemy].MoveType = ENEMY_MOVETYPE_STOP;

	}
	g_nCntEnemy = 0;
	g_nAttackEnemy = 0;
	g_nCntAllEnemy = 0;

	//g_Enemy.MotionType = ENEMY_MOTIONTYPE_NEUTRAL;


	//X�t�@�C���ǂݍ���
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		D3DXLoadMeshFromX("data/MODEL/enemy001/00_original_body_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[0].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[0].nNumMat, &g_aEnemy[nCntEnemy].aModel[0].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy001/01_original_head_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[1].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[1].nNumMat, &g_aEnemy[nCntEnemy].aModel[1].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy001/02_original_armR_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[2].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[2].nNumMat, &g_aEnemy[nCntEnemy].aModel[2].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy001/03_original_frontarmR_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[3].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[3].nNumMat, &g_aEnemy[nCntEnemy].aModel[3].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy001/04_original_handR_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[4].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[4].nNumMat, &g_aEnemy[nCntEnemy].aModel[4].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy001/05_original_armL_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[5].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[5].nNumMat, &g_aEnemy[nCntEnemy].aModel[5].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy001/06_original_frontarmL_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[6].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[6].nNumMat, &g_aEnemy[nCntEnemy].aModel[6].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy001/07_original_handL_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[7].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[7].nNumMat, &g_aEnemy[nCntEnemy].aModel[7].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy001/08_original_legR_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[8].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[8].nNumMat, &g_aEnemy[nCntEnemy].aModel[8].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy001/09_original_frontlegR_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[9].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[9].nNumMat, &g_aEnemy[nCntEnemy].aModel[9].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy001/10_original_footR_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[10].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[10].nNumMat, &g_aEnemy[nCntEnemy].aModel[10].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy001/11_original_legL_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[11].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[11].nNumMat, &g_aEnemy[nCntEnemy].aModel[11].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy001/12_original_frontlegL_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[12].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[12].nNumMat, &g_aEnemy[nCntEnemy].aModel[12].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy001/13_original_footL_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[13].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[13].nNumMat, &g_aEnemy[nCntEnemy].aModel[13].pMesh);
	}
	


	//�e�N�X�`���f�[�^�̎擾
	D3DXMATERIAL *pMat;		//�}�e���A���ւ̃|�C���^

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		for (int nCntModel = 0; nCntModel < g_aEnemy[nCntEnemy].nNumModel; nCntModel++)
		{
			//�}�e���A�����ɑ΂���|�C���^���擾
			pMat = (D3DXMATERIAL *)g_aEnemy[nCntEnemy].aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aEnemy[nCntEnemy].aModel[nCntModel].nNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//�e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_aEnemy[nCntEnemy].aModel[nCntModel].pTexture[nCntMat]);
				}
			}


			//���_���̎擾
			int nNumVtx;		//���_��
			DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
			BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

								//���_�����擾
			nNumVtx = g_aEnemy[nCntEnemy].aModel[nCntModel].pMesh->GetNumVertices();
			//���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(g_aEnemy[nCntEnemy].aModel[nCntModel].pMesh->GetFVF());

			//���_�o�b�t�@�����b�N
			g_aEnemy[nCntEnemy].aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			//for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			//{
			//	D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//���_���W�̑��

			//													//�S�Ă̒��_���r���čő�l�ƍŏ���𔲂��o��
			//													//�ő�l
			//	if (vtx.x >= g_Model.vtxMax.x)
			//	{
			//		g_Model.vtxMax.x = vtx.x;
			//	}
			//	if (vtx.y >= g_Model.vtxMax.y)
			//	{
			//		g_Model.vtxMax.y = vtx.y;
			//	}
			//	if (vtx.z >= g_Model.vtxMax.z)
			//	{
			//		g_Model.vtxMax.z = vtx.z;
			//	}
			//	//�ŏ��l
			//	if (vtx.x <= g_Model.vtxMin.x)
			//	{
			//		g_Model.vtxMin.x = vtx.x;
			//	}
			//	if (vtx.y <= g_Model.vtxMin.y)
			//	{
			//		g_Model.vtxMin.y = vtx.y;
			//	}
			//	if (vtx.z <= g_Model.vtxMin.z)
			//	{
			//		g_Model.vtxMin.z = vtx.z;
			//	}

			//	pVtxBuff += sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			//}
			//���_�o�b�t�@���A�����b�N
			g_aEnemy[nCntEnemy].aModel[nCntModel].pMesh->UnlockVertexBuffer();
		}
	}

	//text�t�@�C���ǂݍ���
	//�e�p�[�c�̊K�w�\����ݒ�
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		FILE *pfile = fopen("data/MOTION/enemy001motion.txt", "r");

		char index[] = "INDEX";
		char string[255][255];
		char search[] = "KEYSET";
		char EndKeySet[] = "END_KEYSET";
		char LoopSearch[] = "LOOP";
		char KeySearch[] = "KEY";
		char MotionSearch[] = "MOTIONSET";
		char EndMotionSet[] = "END_MOTIONSET";

		for (int nCntRead = 0; nCntRead < g_aEnemy[nCntEnemy].nNumModel; nCntRead++)
		{
			while (fgets(string[0], 255, pfile) != NULL)
			{
				if (strstr(string[0], index))
				{
					fscanf(pfile, "%s%s%d%*s%*s", string[1], string[2], &g_aEnemy[nCntEnemy].aModel[nCntRead].nIdxModelParent);
					fscanf(pfile, "%s%s%f%f%f", string[3], string[4], &g_aEnemy[nCntEnemy].aModel[nCntRead].pos.x, &g_aEnemy[nCntEnemy].aModel[nCntRead].pos.y, &g_aEnemy[nCntEnemy].aModel[nCntRead].pos.z);
					fscanf(pfile, "%s%s%f%f%f", string[5], string[6], &g_aEnemy[nCntEnemy].aModel[nCntRead].rot.x, &g_aEnemy[nCntEnemy].aModel[nCntRead].rot.y, &g_aEnemy[nCntEnemy].aModel[nCntRead].rot.z);
					break;
				}
			}
		}

		//���[�V�����̓ǂݍ���
		for (int nCntMotion = 0; nCntMotion < ENEMY_MOTION_MAX; nCntMotion++)
		{
			//���[�v���̎擾
			//�L�[���̎擾
			while (fgets(string[0], 255, pfile) != NULL)
			{
				if (strstr(string[0], MotionSearch))
				{
					fscanf(pfile, "%s%s%d%*s%*s%*s%*s", string[1], string[2], &g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].bLoop);
					fscanf(pfile, "%s%s%d", string[3], string[4], &g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].nNumKey);
					break;
				}
			}

			for (int nCntKey = 0; nCntKey < g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].nNumKey; nCntKey++)
			{
				//�t���[�����̎擾
				while (fgets(string[0], 255, pfile) != NULL)
				{
					if (strstr(string[0], search))
					{
						fscanf(pfile, "%s%s%d", string[0], string[0], &g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
						//g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame = g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame * (144 / 60);
						break;
					}
				}

				//�ʒu�A��]���̎擾
				for (int nCntRead = 0; nCntRead < g_aEnemy[nCntEnemy].nNumModel; nCntRead++)
				{
					while (fgets(string[0], 255, pfile) != NULL)
					{
						if (strstr(string[0], KeySearch))
						{
							fscanf(pfile, "%s%s%f%f%f", string[1], string[2], &g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosX, &g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosY, &g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosZ);
							fscanf(pfile, "%s%s%f%f%f%*s", string[0], string[0], &g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotX, &g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotY, &g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotZ);
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
	}
	


	//�e�q�֌W�ɂ��ʒu����̏C��
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		for (int nCntMotion = 0; nCntMotion < ENEMY_MOTION_MAX; nCntMotion++)
		{
			for (int nCntKey = 0; nCntKey < g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].nNumKey; nCntKey++)
			{
				for (int nCntRead = 0; nCntRead < g_aEnemy[nCntEnemy].nNumModel; nCntRead++)
				{
					g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosX = g_aEnemy[nCntEnemy].aModel[nCntRead].pos.x + g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosX;
					g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosY = g_aEnemy[nCntEnemy].aModel[nCntRead].pos.y + g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosY;
					g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosZ = g_aEnemy[nCntEnemy].aModel[nCntRead].pos.z + g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosZ;
					g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotX = g_aEnemy[nCntEnemy].aModel[nCntRead].rot.x + g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotX;
					g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotY = g_aEnemy[nCntEnemy].aModel[nCntRead].rot.y + g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotY;
					g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotZ = g_aEnemy[nCntEnemy].aModel[nCntRead].rot.z + g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotZ;
				}
			}
		}
		g_aEnemy[nCntEnemy].move.x = -2.0f;
		g_aEnemy[nCntEnemy].move.z = 1.0f;
	}
	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����
}

//=======================================================================
//�I������
//=======================================================================
void UninitEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		for (int nCntModel = 0; nCntModel < g_aEnemy[nCntEnemy].nNumModel; nCntModel++)
		{
			//���b�V���̔j��
			if (g_aEnemy[nCntEnemy].aModel[nCntModel].pMesh != NULL)
			{
				g_aEnemy[nCntEnemy].aModel[nCntModel].pMesh->Release();
				g_aEnemy[nCntEnemy].aModel[nCntModel].pMesh = NULL;
			}

			//�}�e���A���̔j��
			if (g_aEnemy[nCntEnemy].aModel[nCntModel].pBuffMat != NULL)
			{
				g_aEnemy[nCntEnemy].aModel[nCntModel].pBuffMat->Release();
				g_aEnemy[nCntEnemy].aModel[nCntModel].pBuffMat = NULL;
			}

			//�e�N�X�`���̔j��
			for (int nCntTex = 0; nCntTex < ENEMY_MAX_TEXTURE; nCntTex++)
			{
				if (g_aEnemy[nCntEnemy].aModel[nCntModel].pTexture[nCntTex] != NULL)
				{
					g_aEnemy[nCntEnemy].aModel[nCntModel].pTexture[nCntTex]->Release();
					g_aEnemy[nCntEnemy].aModel[nCntModel].pTexture[nCntTex] = NULL;
				}
			}
		}
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateEnemy(void)
{
	PLAYER *pPlayer = GetPlayer();
	EnemyLife *pEnemyLife = GetEnemyLife();
	SHADOW *pShadow = GetShadow();
	Life *pLife = GetLife();
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++,pEnemyLife++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true && pPlayer->bUse == true)
		{
			g_aEnemy[nCntEnemy].MotionTypeOld = g_aEnemy[nCntEnemy].MotionType;
			g_aEnemy[nCntEnemy].posOld = g_aEnemy[nCntEnemy].pos;
			g_aEnemy[nCntEnemy].move.y -= GRAVITY;		//�d��
			g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].move;
			g_aEnemy[nCntEnemy].frotVecX = pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x;
			g_aEnemy[nCntEnemy].frotVecZ = pPlayer->pos.z - g_aEnemy[nCntEnemy].pos.z;
			g_aEnemy[nCntEnemy].fToPlayerR = sqrt(g_aEnemy[nCntEnemy].frotVecX * g_aEnemy[nCntEnemy].frotVecX + g_aEnemy[nCntEnemy].frotVecZ * g_aEnemy[nCntEnemy].frotVecZ);


			//���������Ɍ����ݒ�
			//g_aEnemy[nCntEnemy].move.z = -cosf(g_aEnemy[nCntEnemy].rot.y) * ENEMY_SPEED;
			//g_aEnemy[nCntEnemy].move.x = -sinf(g_aEnemy[nCntEnemy].rot.y) * ENEMY_SPEED;

			//���[�V����
			if (g_aEnemy[nCntEnemy].move.x == 0.0f && g_aEnemy[nCntEnemy].move.z == 0.0f && g_aEnemy[nCntEnemy].MotionType != ENEMY_MOTIONTYPE_PUNCH)
			{
				g_aEnemy[nCntEnemy].MotionType = ENEMY_MOTIONTYPE_NEUTRAL;
			}
			else if (g_aEnemy[nCntEnemy].move.x != 0.0f || g_aEnemy[nCntEnemy].move.z != 0.0f)
			{
				g_aEnemy[nCntEnemy].MotionType = ENEMY_MOTIONTYPE_MOVE;
			}

			if (g_aEnemy[nCntEnemy].pos.y <= 0.0f)
			{
				g_aEnemy[nCntEnemy].pos.y = 0.0f;
				g_aEnemy[nCntEnemy].bJump = false;
			}

			//���f���Ƃ̓����蔻��
			if (CollisionModel(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posOld, &g_aEnemy[nCntEnemy].move, g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].fHeight, g_aEnemy[nCntEnemy].fDepth) == true)
			{
				g_aEnemy[nCntEnemy].bJump = false;
			}
			//�G�Ƃ̓����蔻��
			CollisionEnemy(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posOld, &g_aEnemy[nCntEnemy].move, g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].fHeight, g_aEnemy[nCntEnemy].fDepth);
			//�v���C���[�Ƃ̓����蔻��
			if (CollisionPlayer(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posOld, &g_aEnemy[nCntEnemy].move, g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].fHeight, g_aEnemy[nCntEnemy].fDepth) == true)
			{
				if (g_aEnemy[nCntEnemy].MoveType == ENEMY_MOVETYPE_TO_PLAYER)
				{
					g_aEnemy[nCntEnemy].MoveType = ENEMY_MOVETYPE_ATTACK;
				}
			}

			
			//�v���C���[�̌��Ƃ̓����蔻��
			if (g_aEnemy[nCntEnemy].bDamage == false && pPlayer->bSlash == true)
			{
				if (CollisionSword(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posOld, &g_aEnemy[nCntEnemy].move, g_aEnemy[nCntEnemy].fWidth + 20.0f, g_aEnemy[nCntEnemy].fHeight, g_aEnemy[nCntEnemy].fDepth + 20.0f) == true)
				{
					if (pPlayer->MotionType == MOTIONTYPE_SLASH03)
					{
						g_aEnemy[nCntEnemy].nLife -= 5;
						SetScore(500);
						g_aEnemy[nCntEnemy].bSlash = false;
						g_aEnemy[nCntEnemy].MoveType = ENEMY_MOVETYPE_DAMAGE;
						g_aEnemy[nCntEnemy].nKey = 0;
						g_aEnemy[nCntEnemy].fCounterMotion = 0.0f;
					}
					else if (pPlayer->MotionType == MOTIONTYPE_SLASH04)
					{
						g_aEnemy[nCntEnemy].nLife -= 1;
						SetScore(100);
						g_aEnemy[nCntEnemy].bSlash = false;
						g_aEnemy[nCntEnemy].MoveType = ENEMY_MOVETYPE_DAMAGE;
						g_aEnemy[nCntEnemy].nKey = 0;
						g_aEnemy[nCntEnemy].fCounterMotion = 0.0f;
					}
					else
					{
						g_aEnemy[nCntEnemy].nLife--;
						SetScore(100);
						//g_aEnemy[nCntEnemy].bSlash = false;
					}
					g_aEnemy[nCntEnemy].bDamage = true;

					pEnemyLife->scale.x = 50.0f / MAX_ENEMY_LIFE * g_aEnemy[nCntEnemy].nLife;
					if (g_aEnemy[nCntEnemy].nLife <= 0)
					{
						g_aEnemy[nCntEnemy].nLife = 0;
						g_aEnemy[nCntEnemy].bUse = false;
						SetScore(1000);
						pEnemyLife->bUse = false;
						g_aEnemy[nCntEnemy].nLife = MAX_ENEMY_LIFE;
						g_aEnemy[nCntEnemy].MoveType = ENEMY_MOVETYPE_STOP;
						g_nCntAllEnemy--;
						for (int nCnt = 0; nCnt < 8; nCnt++)
						{
							SetEffect(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + 80.0f, g_aEnemy[nCntEnemy].pos.z),
								D3DXVECTOR3(cosf(D3DX_PI * 2.0f / 8.0f * nCnt) * 0.8f, 1.0f, sinf(D3DX_PI * 2.0f / 8.0f * nCnt) * 0.8f),
								20.0f, 20.0f, D3DXCOLOR(255, 0, 0, 255), 60, EFFEFCT_MOVETYPE_ENEMY_DEATH);
						}
					}
				}
			}

			if (pPlayer->bSlash == false)
			{
				g_aEnemy[nCntEnemy].bDamage = false;
			}

			g_aEnemy[nCntEnemy].fSwordCollZ = g_aEnemy[nCntEnemy].pos.z + (cosf(g_aEnemy[nCntEnemy].rot.y - D3DX_PI) * ENEMY_SWORD_COLLISION_DEPTH);
			g_aEnemy[nCntEnemy].fSwordCollX = g_aEnemy[nCntEnemy].pos.x + (sinf(g_aEnemy[nCntEnemy].rot.y - D3DX_PI) * ENEMY_SWORD_COLLISION_DEPTH);

			//�G�̌��ƃv���C���[�̓����蔻��
			if (pPlayer->pos.x > g_aEnemy[nCntEnemy].fSwordCollX - pPlayer->fWidth / 2.0f &&
				pPlayer->pos.x < g_aEnemy[nCntEnemy].fSwordCollX + pPlayer->fWidth / 2.0f &&
				pPlayer->pos.z < g_aEnemy[nCntEnemy].fSwordCollZ + pPlayer->fDepth / 2.0f &&
				pPlayer->pos.z > g_aEnemy[nCntEnemy].fSwordCollZ - pPlayer->fDepth / 2.0f)
			{
				if (g_aEnemy[nCntEnemy].bPlayerDamage == false && g_aEnemy[nCntEnemy].bSlash == true)
				{
					if (pPlayer->MotionType == MOTIONTYPE_DIFENCE)
					{

					}
					else
					{
						pPlayer->nLife--;
						PlaySound(SOUND_LABEL_DAMAGE);
						SetMask(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2.0f, 0.0f), MASKTYPE_DAMAGE, SCREEN_WIDTH, SCREEN_HEIGHT);
						SetVibration(60000, 60000, 30);
						pLife->fWidth = pLife->fWidth / (pPlayer->nLife + 1) * pPlayer->nLife;
						g_aEnemy[nCntEnemy].bPlayerDamage = true;
					}
					
					if (pPlayer->nLife <= 0 && pPlayer->bUse != false)
					{
						pPlayer->bUse = false;
					}
				}
			}

			
			
			if (g_aEnemy[nCntEnemy].bSlash == false)
			{
				g_aEnemy[nCntEnemy].bPlayerDamage = false;
			}

			

			SetPositionShadow(g_aEnemy[nCntEnemy].nIdx, g_aEnemy[nCntEnemy].pos, g_aEnemy[nCntEnemy].bUse);
			

			//�����̏���
			MoveTypeEnemy(nCntEnemy);
			//=======================================================================
			//���[�V����
			//=======================================================================
			if (g_aEnemy[nCntEnemy].MotionType != g_aEnemy[nCntEnemy].MotionTypeOld )
			{
				g_aEnemy[nCntEnemy].nKey = 0;
				g_aEnemy[nCntEnemy].fCounterMotion = 0.0f;
				if (g_aEnemy[nCntEnemy].MotionTypeOld == ENEMY_MOTIONTYPE_PUNCH)
				{
					//g_aEnemy[nCntEnemy].bSlash = false;
				}
				
			}
			MotionEnemy(nCntEnemy);
			

			//��]�̊���
			if (g_aEnemy[nCntEnemy].fNumTurnEnemy > D3DX_PI)
			{
				g_aEnemy[nCntEnemy].fNumTurnEnemy = -D3DX_PI - (D3DX_PI - g_aEnemy[nCntEnemy].fNumTurnEnemy);
			}
			else if (g_aEnemy[nCntEnemy].fNumTurnEnemy < -D3DX_PI)
			{
				g_aEnemy[nCntEnemy].fNumTurnEnemy = D3DX_PI - (-D3DX_PI - g_aEnemy[nCntEnemy].fNumTurnEnemy);
			}

			if (g_aEnemy[nCntEnemy].rot.y < 0.0f && -g_aEnemy[nCntEnemy].rot.y + g_aEnemy[nCntEnemy].fNumTurnEnemy > D3DX_PI)
			{
				g_aEnemy[nCntEnemy].fDifferRot = (-D3DX_PI - g_aEnemy[nCntEnemy].rot.y) + -(D3DX_PI - g_aEnemy[nCntEnemy].fNumTurnEnemy);
			}
			else if (g_aEnemy[nCntEnemy].rot.y >= D3DX_PI / 2.0f && g_aEnemy[nCntEnemy].rot.y - g_aEnemy[nCntEnemy].fNumTurnEnemy > D3DX_PI)
			{
				g_aEnemy[nCntEnemy].fDifferRot = (D3DX_PI - g_aEnemy[nCntEnemy].rot.y) - (-D3DX_PI - g_aEnemy[nCntEnemy].fNumTurnEnemy);
			}
			else
			{
				g_aEnemy[nCntEnemy].fDifferRot = (g_aEnemy[nCntEnemy].fNumTurnEnemy - g_aEnemy[nCntEnemy].rot.y);
			}


			g_aEnemy[nCntEnemy].rot.y += g_aEnemy[nCntEnemy].fDifferRot * 0.1f;
			if (g_aEnemy[nCntEnemy].rot.y - g_aEnemy[nCntEnemy].fNumTurnEnemy < 0.001 && g_aEnemy[nCntEnemy].rot.y - g_aEnemy[nCntEnemy].fNumTurnEnemy > -0.001)
			{
				g_aEnemy[nCntEnemy].bTurnEnemy = false;

			}

			if (g_aEnemy[nCntEnemy].rot.y > D3DX_PI)
			{
				g_aEnemy[nCntEnemy].rot.y = -D3DX_PI;
			}
			else if (g_aEnemy[nCntEnemy].rot.y < -D3DX_PI)
			{
				g_aEnemy[nCntEnemy].rot.y = D3DX_PI;
			}
		}	
	}
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����

	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].mtxWorld);		//�v���C���[�̃��[���h�}�g���b�N�X�̏�����

														//�v���C���[�̌����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCntEnemy].rot.y, g_aEnemy[nCntEnemy].rot.x, g_aEnemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxRot);

			//�v���C���[�̈ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y, g_aEnemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].mtxWorld);

			//���݂̃}�e���A����ۑ�
			pDevice->GetMaterial(&matDef);

			for (int nCntModel = 0; nCntModel < g_aEnemy[nCntEnemy].nNumModel; nCntModel++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;		//�v�Z�p�}�g���b�N�X
				D3DXMATRIX mtxParent;						//�e�̃}�g���b�N�X

				D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld);		//�e�p�[�c�̃��[���h�}�g���b�N�X�̏�����

																				//�e�p�[�c�̌����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aEnemy[nCntEnemy].aModel[nCntModel].rot.y, g_aEnemy[nCntEnemy].aModel[nCntModel].rot.x, g_aEnemy[nCntEnemy].aModel[nCntModel].rot.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxRotModel);

				//�e�p�[�c�̈ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTransModel, g_aEnemy[nCntEnemy].aModel[nCntModel].pos.x, g_aEnemy[nCntEnemy].aModel[nCntModel].pos.y, g_aEnemy[nCntEnemy].aModel[nCntModel].pos.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxTransModel);

				//�e�p�[�c�̐e�̃}�g���b�N�X�̐ݒ�
				if (g_aEnemy[nCntEnemy].aModel[nCntModel].nIdxModelParent != -1)
				{
					mtxParent = g_aEnemy[nCntEnemy].aModel[g_aEnemy[nCntEnemy].aModel[nCntModel].nIdxModelParent].mtxWorld;
				}
				else
				{
					mtxParent = g_aEnemy[nCntEnemy].mtxWorld;
				}

				//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxParent);

				//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld);

				//�}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_aEnemy[nCntEnemy].aModel[nCntModel].pBuffMat->GetBufferPointer();
				for (int nCntMat = 0; nCntMat < (int)g_aEnemy[nCntEnemy].aModel[nCntModel].nNumMat; nCntMat++)
				{
					//�}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, NULL);
					//pDevice->SetTexture(0, g_apTextureEnemy[nCntMat]);

					//���f��(�p�[�c)�̕`��
					g_aEnemy[nCntEnemy].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
				}

				//�ۑ����Ă����}�e���A����߂�
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//=======================================================================
//���[�V��������
//=======================================================================
void MotionEnemy(int nCntEnemy)
{
	//�v���C���[�̎擾
	PLAYER *pPlayer = GetPlayer();

	D3DXVECTOR3 posAsk[MAX_ENEMY_MODEL];		//���߂����l
	D3DXVECTOR3 rotAsk[MAX_ENEMY_MODEL];		//���߂����l
	D3DXVECTOR3 posDiffer[MAX_ENEMY_MODEL];	//����
	D3DXVECTOR3 rotDiffer[MAX_ENEMY_MODEL];	//����

	for (int nCntModel = 0; nCntModel < g_aEnemy[nCntEnemy].nNumModel; nCntModel++)
	{
		if (g_aEnemy[nCntEnemy].nKey < g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].nNumKey - 1)//�L�[�̍ő吔-1
		{
			posDiffer[nCntModel].x = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey + 1].aKey[nCntModel].fPosX
				- g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosX;
			posDiffer[nCntModel].y = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey + 1].aKey[nCntModel].fPosY
				- g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosY;
			posDiffer[nCntModel].z = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey + 1].aKey[nCntModel].fPosZ
				- g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosZ;
			rotDiffer[nCntModel].x = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey + 1].aKey[nCntModel].fRotX
				- g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotX;
			rotDiffer[nCntModel].y = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey + 1].aKey[nCntModel].fRotY
				- g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotY;
			rotDiffer[nCntModel].z = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey + 1].aKey[nCntModel].fRotZ
				- g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotZ;

			posAsk[nCntModel].x = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosX
				+ posDiffer[nCntModel].x * (g_aEnemy[nCntEnemy].fCounterMotion / g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].nFrame);
			posAsk[nCntModel].y = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosY
				+ posDiffer[nCntModel].y * (g_aEnemy[nCntEnemy].fCounterMotion / g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].nFrame);
			posAsk[nCntModel].z = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosZ
				+ posDiffer[nCntModel].z * (g_aEnemy[nCntEnemy].fCounterMotion / g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].nFrame);
			rotAsk[nCntModel].x = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotX
				+ rotDiffer[nCntModel].x * (g_aEnemy[nCntEnemy].fCounterMotion / g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].nFrame);
			rotAsk[nCntModel].y = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotY
				+ rotDiffer[nCntModel].y * (g_aEnemy[nCntEnemy].fCounterMotion / g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].nFrame);
			rotAsk[nCntModel].z = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotZ
				+ rotDiffer[nCntModel].z * (g_aEnemy[nCntEnemy].fCounterMotion / g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].nFrame);

			g_aEnemy[nCntEnemy].aModel[nCntModel].pos.x = posAsk[nCntModel].x;
			g_aEnemy[nCntEnemy].aModel[nCntModel].pos.y = posAsk[nCntModel].y;
			g_aEnemy[nCntEnemy].aModel[nCntModel].pos.z = posAsk[nCntModel].z;
			g_aEnemy[nCntEnemy].aModel[nCntModel].rot.x = rotAsk[nCntModel].x;
			g_aEnemy[nCntEnemy].aModel[nCntModel].rot.y = rotAsk[nCntModel].y;
			g_aEnemy[nCntEnemy].aModel[nCntModel].rot.z = rotAsk[nCntModel].z;
		}
		else if (g_aEnemy[nCntEnemy].nKey >= g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].nNumKey - 1)//�L�[�̍ő吔-1
		{
			if (g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].bLoop == 1)
			{
				posDiffer[nCntModel].x = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[0].aKey[nCntModel].fPosX
					- g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosX;
				posDiffer[nCntModel].y = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[0].aKey[nCntModel].fPosY
					- g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosY;
				posDiffer[nCntModel].z = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[0].aKey[nCntModel].fPosZ
					- g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosZ;
				rotDiffer[nCntModel].x = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[0].aKey[nCntModel].fRotX
					- g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotX;
				rotDiffer[nCntModel].y = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[0].aKey[nCntModel].fRotY
					- g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotY;
				rotDiffer[nCntModel].z = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[0].aKey[nCntModel].fRotZ
					- g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotZ;

				posAsk[nCntModel].x = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosX
					+ posDiffer[nCntModel].x * (g_aEnemy[nCntEnemy].fCounterMotion / g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].nFrame);
				posAsk[nCntModel].y = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosY
					+ posDiffer[nCntModel].y * (g_aEnemy[nCntEnemy].fCounterMotion / g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].nFrame);
				posAsk[nCntModel].z = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosZ
					+ posDiffer[nCntModel].z * (g_aEnemy[nCntEnemy].fCounterMotion / g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].nFrame);
				rotAsk[nCntModel].x = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotX
					+ rotDiffer[nCntModel].x * (g_aEnemy[nCntEnemy].fCounterMotion / g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].nFrame);
				rotAsk[nCntModel].y = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotY
					+ rotDiffer[nCntModel].y * (g_aEnemy[nCntEnemy].fCounterMotion / g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].nFrame);
				rotAsk[nCntModel].z = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotZ
					+ rotDiffer[nCntModel].z * (g_aEnemy[nCntEnemy].fCounterMotion / g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].nFrame);

				g_aEnemy[nCntEnemy].aModel[nCntModel].pos.x = posAsk[nCntModel].x;
				g_aEnemy[nCntEnemy].aModel[nCntModel].pos.y = posAsk[nCntModel].y;
				g_aEnemy[nCntEnemy].aModel[nCntModel].pos.z = posAsk[nCntModel].z;
				g_aEnemy[nCntEnemy].aModel[nCntModel].rot.x = rotAsk[nCntModel].x;
				g_aEnemy[nCntEnemy].aModel[nCntModel].rot.y = rotAsk[nCntModel].y;
				g_aEnemy[nCntEnemy].aModel[nCntModel].rot.z = rotAsk[nCntModel].z;
			}
			else if (g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].bLoop == 0)
			{
				posDiffer[nCntModel].x = g_aEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[nCntModel].fPosX
					- g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosX;
				posDiffer[nCntModel].y = g_aEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[nCntModel].fPosY
					- g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosY;
				posDiffer[nCntModel].z = g_aEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[nCntModel].fPosZ
					- g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosZ;
				rotDiffer[nCntModel].x = g_aEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[nCntModel].fRotX
					- g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotX;
				rotDiffer[nCntModel].y = g_aEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[nCntModel].fRotY
					- g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotY;
				rotDiffer[nCntModel].z = g_aEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[nCntModel].fRotZ
					- g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotZ;

				posAsk[nCntModel].x = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosX
					+ posDiffer[nCntModel].x * (g_aEnemy[nCntEnemy].fCounterMotion / g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].nFrame);
				posAsk[nCntModel].y = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosY
					+ posDiffer[nCntModel].y * (g_aEnemy[nCntEnemy].fCounterMotion / g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].nFrame);
				posAsk[nCntModel].z = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosZ
					+ posDiffer[nCntModel].z * (g_aEnemy[nCntEnemy].fCounterMotion / g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].nFrame);
				rotAsk[nCntModel].x = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotX
					+ rotDiffer[nCntModel].x * (g_aEnemy[nCntEnemy].fCounterMotion / g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].nFrame);
				rotAsk[nCntModel].y = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotY
					+ rotDiffer[nCntModel].y * (g_aEnemy[nCntEnemy].fCounterMotion / g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].nFrame);
				rotAsk[nCntModel].z = g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotZ
					+ rotDiffer[nCntModel].z * (g_aEnemy[nCntEnemy].fCounterMotion / g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].nFrame);

				g_aEnemy[nCntEnemy].aModel[nCntModel].pos.x = posAsk[nCntModel].x;
				g_aEnemy[nCntEnemy].aModel[nCntModel].pos.y = posAsk[nCntModel].y;
				g_aEnemy[nCntEnemy].aModel[nCntModel].pos.z = posAsk[nCntModel].z;
				g_aEnemy[nCntEnemy].aModel[nCntModel].rot.x = rotAsk[nCntModel].x;
				g_aEnemy[nCntEnemy].aModel[nCntModel].rot.y = rotAsk[nCntModel].y;
				g_aEnemy[nCntEnemy].aModel[nCntModel].rot.z = rotAsk[nCntModel].z;
			}

		}
	}


	if ((g_aEnemy[nCntEnemy].MotionType == ENEMY_MOTIONTYPE_PUNCH && g_aEnemy[nCntEnemy].bSlash == false && g_aEnemy[nCntEnemy].nKey == 1 && g_aEnemy[nCntEnemy].fCounterMotion == 0))
	{
		g_aEnemy[nCntEnemy].bSlash = true;
		PlaySound(SOUND_LABEL_SLASH_004);
	}
	if (g_aEnemy[nCntEnemy].MotionType == ENEMY_MOTIONTYPE_PUNCH && g_aEnemy[nCntEnemy].bSlash == true && g_aEnemy[nCntEnemy].nKey == 2 && g_aEnemy[nCntEnemy].fCounterMotion >= 5)
	{
		g_aEnemy[nCntEnemy].bSlash = false;
	}

	g_aEnemy[nCntEnemy].fCounterMotion += 1.0f;
	if (g_aEnemy[nCntEnemy].fCounterMotion >= g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].nFrame)
	{
		if (g_aEnemy[nCntEnemy].nKey < g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].nNumKey - 1)//�L�[�̍ő吔-1
		{
			g_aEnemy[nCntEnemy].nKey++;
			g_aEnemy[nCntEnemy].fCounterMotion = 0.0f;
		}
		else if (g_aEnemy[nCntEnemy].nKey >= g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].nNumKey - 1)
		{
			g_aEnemy[nCntEnemy].nKey = 0;
			g_aEnemy[nCntEnemy].fCounterMotion = 0.0f;
			g_aEnemy[nCntEnemy].bSlash = false;
			g_aEnemy[nCntEnemy].MotionType = ENEMY_MOTIONTYPE_NEUTRAL;
		}
	}
}

//=======================================================================
//�G�̓������̏���
//=======================================================================
void MoveTypeEnemy(int nCntEnemy)
{
	//�v���C���[�̎擾
	PLAYER *pPlayer = GetPlayer();

	if (g_aEnemy[nCntEnemy].fToPlayerR <= ENEMY_SEARCH && g_aEnemy[nCntEnemy].MoveType != ENEMY_MOVETYPE_ATTACK && g_aEnemy[nCntEnemy].MoveType != ENEMY_MOVETYPE_DAMAGE)
	{
		g_aEnemy[nCntEnemy].MoveType = ENEMY_MOVETYPE_TO_PLAYER;
	}

	if (g_aEnemy[nCntEnemy].MoveType == ENEMY_MOVETYPE_MOVE)
	{
		g_aEnemy[nCntEnemy].nCntMoveTime++;
		if (g_aEnemy[nCntEnemy].nCntMoveTime <= rand() % 650 + 450)
		{
			g_aEnemy[nCntEnemy].move.z = -cosf(g_aEnemy[nCntEnemy].rot.y) * ENEMY_SPEED;
			g_aEnemy[nCntEnemy].move.x = -sinf(g_aEnemy[nCntEnemy].rot.y) * ENEMY_SPEED;
		}
		else
		{
			g_aEnemy[nCntEnemy].MoveType = ENEMY_MOVETYPE_STOP;
			g_aEnemy[nCntEnemy].nCntMoveTime = 0;
		}
	}
	else if (g_aEnemy[nCntEnemy].MoveType == ENEMY_MOVETYPE_STOP)
	{
		g_aEnemy[nCntEnemy].move.z = 0.0f;
		g_aEnemy[nCntEnemy].move.x = 0.0f;

		g_aEnemy[nCntEnemy].nCntStop++;
		if (g_aEnemy[nCntEnemy].nCntStop >= ENEMY_STOP_TIME)
		{
			g_aEnemy[nCntEnemy].MoveType = ENEMY_MOVETYPE_TURN;
			g_aEnemy[nCntEnemy].bTurnEnemy2 = true;
			g_aEnemy[nCntEnemy].nCntStop = 0;
		}
	}
	else if (g_aEnemy[nCntEnemy].MoveType == ENEMY_MOVETYPE_TURN)
	{
		if (g_aEnemy[nCntEnemy].bTurnEnemy2 == true)
		{
			//srand(1);
			g_aEnemy[nCntEnemy].fNumTurnEnemy = ENEMY_RAND;
			g_aEnemy[nCntEnemy].bTurnEnemy2 = false;
		}
		if (g_aEnemy[nCntEnemy].rot.y - g_aEnemy[nCntEnemy].fNumTurnEnemy < 0.05 && g_aEnemy[nCntEnemy].rot.y - g_aEnemy[nCntEnemy].fNumTurnEnemy > -0.05)
		{
			g_aEnemy[nCntEnemy].MoveType = ENEMY_MOVETYPE_MOVE;
		}
	}
	else if (g_aEnemy[nCntEnemy].MoveType == ENEMY_MOVETYPE_TO_PLAYER)
	{
		g_aEnemy[nCntEnemy].fNumTurnEnemy = atan2(g_aEnemy[nCntEnemy].frotVecX, g_aEnemy[nCntEnemy].frotVecZ) - D3DX_PI;
		
		g_aEnemy[nCntEnemy].move.z = -cosf(g_aEnemy[nCntEnemy].rot.y) * ENEMY_SPEED;
		g_aEnemy[nCntEnemy].move.x = -sinf(g_aEnemy[nCntEnemy].rot.y) * ENEMY_SPEED;

		if (g_aEnemy[nCntEnemy].fToPlayerR > ENEMY_SEARCH)
		{
			g_aEnemy[nCntEnemy].MoveType = ENEMY_MOVETYPE_STOP;
		}
	}
	else if (g_aEnemy[nCntEnemy].MoveType == ENEMY_MOVETYPE_DAMAGE)
	{
		g_aEnemy[nCntEnemy].MotionType = ENEMY_MOTIONTYPE_DAMAGE;
		if (g_aEnemy[nCntEnemy].nKey == 0 && g_aEnemy[nCntEnemy].fCounterMotion == 0.0f)
		{
			g_aEnemy[nCntEnemy].fNumTurnEnemy = atan2(g_aEnemy[nCntEnemy].frotVecX, g_aEnemy[nCntEnemy].frotVecZ) - D3DX_PI;
			g_aEnemy[nCntEnemy].posPlayer = pPlayer->pos;
		}

		g_aEnemy[nCntEnemy].frotVecX = g_aEnemy[nCntEnemy].posPlayer.x - g_aEnemy[nCntEnemy].pos.x;
		g_aEnemy[nCntEnemy].frotVecZ = g_aEnemy[nCntEnemy].posPlayer.z - g_aEnemy[nCntEnemy].pos.z;
		g_aEnemy[nCntEnemy].fToPlayerR = sqrt(g_aEnemy[nCntEnemy].frotVecX * g_aEnemy[nCntEnemy].frotVecX + g_aEnemy[nCntEnemy].frotVecZ * g_aEnemy[nCntEnemy].frotVecZ);

		if (g_aEnemy[nCntEnemy].fToPlayerR > ENEMY_DAMAGE)
		{
			g_aEnemy[nCntEnemy].move.z = 0.0f;
			g_aEnemy[nCntEnemy].move.x = 0.0f;
			g_aEnemy[nCntEnemy].MoveType = ENEMY_MOVETYPE_STOP;
			g_aEnemy[nCntEnemy].MotionType = ENEMY_MOTIONTYPE_NEUTRAL;
		}
		else
		{
			g_aEnemy[nCntEnemy].move.z = -cosf(g_aEnemy[nCntEnemy].rot.y) * -ENEMY_SPEED;
			g_aEnemy[nCntEnemy].move.x = -sinf(g_aEnemy[nCntEnemy].rot.y) * -ENEMY_SPEED;
			if (g_aEnemy[nCntEnemy].nKey == 1)
			{
				g_aEnemy[nCntEnemy].move.z = 0.0f;
				g_aEnemy[nCntEnemy].move.x = 0.0f;
				g_aEnemy[nCntEnemy].MoveType = ENEMY_MOVETYPE_STOP;
				g_aEnemy[nCntEnemy].MotionType = ENEMY_MOTIONTYPE_NEUTRAL;
			}
		}
	}
	else if (g_aEnemy[nCntEnemy].MoveType == ENEMY_MOVETYPE_ATTACK)
	{
		g_aEnemy[nCntEnemy].fNumTurnEnemy = atan2(g_aEnemy[nCntEnemy].frotVecX, g_aEnemy[nCntEnemy].frotVecZ) - D3DX_PI;

		g_aEnemy[nCntEnemy].move.z = 0.0f;
		g_aEnemy[nCntEnemy].move.x = 0.0f;

		g_aEnemy[nCntEnemy].nCntStop++;
		if (g_aEnemy[nCntEnemy].nCntStop >= 100)
		{
			g_aEnemy[nCntEnemy].MotionType = ENEMY_MOTIONTYPE_PUNCH;
			
			g_aEnemy[nCntEnemy].nCntStop = 0;
		}

		if (g_aEnemy[nCntEnemy].fToPlayerR > ENEMY_ATTACK)
		{
			g_aEnemy[nCntEnemy].MoveType = ENEMY_MOVETYPE_TO_PLAYER;
		}
	}
	

	//-------------------------------------------------
	//�G�̈ړ�����
	//-------------------------------------------------
	if (g_aEnemy[nCntEnemy].pos.x >= 1200.0f)
	{
		g_aEnemy[nCntEnemy].pos.x = 1200.0f;
	}
	else if (g_aEnemy[nCntEnemy].pos.x <= -1200.0f)
	{
		g_aEnemy[nCntEnemy].pos.x = -1200.0f;
	}
	if (g_aEnemy[nCntEnemy].pos.z >= 1200.0f)
	{
		g_aEnemy[nCntEnemy].pos.z = 1200.0f;
	}
	else if (g_aEnemy[nCntEnemy].pos.z <= -1200.0f)
	{
		g_aEnemy[nCntEnemy].pos.z = -1200.0f;
	}
}


//=======================================================================
//�ݒ菈��
//=======================================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			g_aEnemy[nCntEnemy].rot = rot;
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].bUse = true;
			g_aEnemy[nCntEnemy].nIdx = SetShadow(g_aEnemy[nCntEnemy].pos, g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].fDepth);
			SetEnemyLife(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + 100.0f, g_aEnemy[nCntEnemy].pos.z), 50.0f, 5.0f);
			for (int nCnt = 0; nCnt < 32; nCnt++)
			{
				SetEffect(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + cos(D3DX_PI * 2.0f / 32.0f * nCnt) * g_aEnemy[nCntEnemy].fWidth,
					g_aEnemy[nCntEnemy].pos.y, g_aEnemy[nCntEnemy].pos.z + sin(D3DX_PI * 2.0f / 32.0f * nCnt) * g_aEnemy[nCntEnemy].fWidth),
					D3DXVECTOR3(0.0f, 1.0f, 0.0f), 10.0f, 30.0f, D3DXCOLOR(255, 255, 0, 100), 60, EFFEFCT_MOVETYPE_ENEMY_APPEAR);
			}
			//g_nCntEnemy++;
			g_nCntAllEnemy++;
			break;
		}
	}
	
}

//=======================================================================
//�G�Ƃ̓����蔻��
//=======================================================================
void CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth)
{
	ENEMY *pEnemy;
	pEnemy = GetEnemy();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++,pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			if (pPos->x > pEnemy->pos.x - pEnemy->fWidth / 2.0f - fWidth / 2.0f &&
				pPos->x < pEnemy->pos.x + pEnemy->fWidth / 2.0f + fWidth / 2.0f &&
				pPos->z > pEnemy->pos.z - pEnemy->fDepth / 2.0f - fDepth / 2.0f &&
				pPos->z < pEnemy->pos.z + pEnemy->fDepth / 2.0f + fDepth / 2.0f &&
				pPos->y <= pEnemy->pos.y + pEnemy->fHeight &&
				pBeforePos->y >= pEnemy->pos.y + pEnemy->fHeight)
			{
				pPos->y = pEnemy->pos.y + pEnemy->fHeight;
				pMove->y = 0.0f;
			}
			else if (pPos->x > pEnemy->pos.x - pEnemy->fWidth / 2.0f - fWidth / 2.0f &&
					pPos->x < pEnemy->pos.x + pEnemy->fWidth / 2.0f + fWidth / 2.0f &&
					pPos->z > pEnemy->pos.z - pEnemy->fDepth / 2.0f - fDepth / 2.0f &&
					pPos->z < pEnemy->pos.z + pEnemy->fDepth / 2.0f + fDepth / 2.0f &&
					pPos->y >= pEnemy->pos.y - fHeight &&
					pBeforePos->y <= pEnemy->pos.y - fHeight)
			{
				pPos->y = pEnemy->pos.y - fHeight;
			}

			if (pPos->y < pEnemy->pos.y + pEnemy->fHeight &&
				pPos->y > pEnemy->pos.y - fHeight &&
				pPos->z > pEnemy->pos.z - pEnemy->fDepth / 2.0f - fDepth / 2.0f &&
				pPos->z < pEnemy->pos.z + pEnemy->fDepth / 2.0f + fDepth / 2.0f &&
				pPos->x >= pEnemy->pos.x - pEnemy->fWidth / 2.0f - fWidth / 2.0f &&
				pBeforePos->x <= pEnemy->pos.x - pEnemy->fWidth / 2.0f - fWidth / 2.0f)
			{
				pPos->x = pEnemy->pos.x - pEnemy->fWidth / 2.0f - fWidth / 2.0f;
			}
			else if (pPos->y < pEnemy->pos.y + pEnemy->fHeight &&
					pPos->y > pEnemy->pos.y - fHeight &&
					pPos->z > pEnemy->pos.z - pEnemy->fDepth / 2.0f - fDepth / 2.0f &&
					pPos->z < pEnemy->pos.z + pEnemy->fDepth / 2.0f + fDepth / 2.0f &&
					pPos->x <= pEnemy->pos.x + pEnemy->fWidth / 2.0f + fWidth / 2.0f &&
					pBeforePos->x >= pEnemy->pos.x + pEnemy->fWidth / 2.0f + fWidth / 2.0f)
			{
				pPos->x = pEnemy->pos.x + pEnemy->fWidth / 2.0f + fWidth / 2.0f;
			}

			if (pPos->y < pEnemy->pos.y + pEnemy->fHeight &&
				pPos->y > pEnemy->pos.y - fHeight &&
				pPos->x > pEnemy->pos.x - pEnemy->fWidth / 2.0f - fWidth / 2.0f &&
				pPos->x < pEnemy->pos.x + pEnemy->fWidth / 2.0f + fWidth / 2.0f &&
				pPos->z >= pEnemy->pos.z - pEnemy->fDepth / 2.0f - fDepth / 2.0f &&
				pBeforePos->z <= pEnemy->pos.z - pEnemy->fDepth / 2.0f - fDepth / 2.0f)
			{
				pPos->z = pEnemy->pos.z - pEnemy->fDepth / 2.0f - fDepth / 2.0f;
			}
			else if (pPos->y < pEnemy->pos.y + pEnemy->fHeight &&
					pPos->y > pEnemy->pos.y - fHeight &&
					pPos->x > pEnemy->pos.x - pEnemy->fWidth / 2.0f - fWidth / 2.0f &&
					pPos->x < pEnemy->pos.x + pEnemy->fWidth / 2.0f + fWidth / 2.0f &&
					pPos->z <= pEnemy->pos.z + pEnemy->fDepth / 2.0f + fDepth / 2.0f &&
					pBeforePos->z >= pEnemy->pos.z + pEnemy->fDepth / 2.0f + fDepth / 2.0f)
			{
				pPos->z = pEnemy->pos.z + pEnemy->fDepth / 2.0f + fDepth / 2.0f;
			}

		}
	}
}

//=======================================================================
//���Ƃ̓����蔻��
//=======================================================================
bool CollisionEnemySword(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth)
{
	ENEMY *pEnemy;
	pEnemy = GetEnemy();
	bool bDamage = false;			//�������Ă��邩�ǂ���

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++,pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			pEnemy->fSwordCollZ = pEnemy->pos.z + (cosf(pEnemy->rot.y - D3DX_PI) * ENEMY_SWORD_COLLISION_DEPTH);
			pEnemy->fSwordCollX = pEnemy->pos.x + (sinf(pEnemy->rot.y - D3DX_PI) * ENEMY_SWORD_COLLISION_DEPTH);

			if (pPos->x > pEnemy->fSwordCollX - fWidth / 2.0f &&
				pPos->x < pEnemy->fSwordCollX + fWidth / 2.0f &&
				pPos->z < pEnemy->fSwordCollZ + fDepth / 2.0f &&
				pPos->z > pEnemy->fSwordCollZ - fDepth / 2.0f)
			{
				g_nAttackEnemy = nCntEnemy;
				bDamage = true;
				break;
			}
		}
	}
	return bDamage;
}


//=======================================================================
//�擾����
//=======================================================================
ENEMY *GetEnemy(void)
{
	return &g_aEnemy[0];
}

ENEMY *GetAttackEnemy(void)
{
	return &g_aEnemy[g_nAttackEnemy];
}

int GetUseEnemy(void)
{
	return g_nCntEnemy;
}


int GetAllEnemy(void)
{
	return g_nCntAllEnemy;
}