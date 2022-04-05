//=======================================================================
//ボスに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "boss.h"
#include "shadow.h"
#include "bullet.h"
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
#include "camera.h"
#include "billboard.h"
#include "evolutionGauge.h"
#include "EnemyBullet.h"
#include "modeltxt.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================
BOSS g_aBoss[MAX_BOSS];				//プレイヤーの構造体
int g_nCntBoss;						//敵の数ぶん回すために必要
int g_nCntAllBoss;						//敵の現在の総数
int g_nAttackBoss;						//剣の当たり判定に必要

//=======================================================================
//初期化処理
//=======================================================================
void InitBoss(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//初期化
	for (int nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		g_aBoss[nCntBoss].aMotionInfo->bLoop = false;
		g_aBoss[nCntBoss].aMotionInfo->nNumKey = 0;
		g_aBoss[nCntBoss].aMotionInfo->aKeyInfo->nFrame = 0;
		g_aBoss[nCntBoss].aMotionInfo->aKeyInfo->aKey->fPosX = 0;
		g_aBoss[nCntBoss].aMotionInfo->aKeyInfo->aKey->fPosY = 0;
		g_aBoss[nCntBoss].aMotionInfo->aKeyInfo->aKey->fPosZ = 0;
		g_aBoss[nCntBoss].aMotionInfo->aKeyInfo->aKey->fRotX = 0;
		g_aBoss[nCntBoss].aMotionInfo->aKeyInfo->aKey->fRotY = 0;
		g_aBoss[nCntBoss].aMotionInfo->aKeyInfo->aKey->fRotZ = 0;
		g_aBoss[nCntBoss].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].posPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].nNumModel = MAX_BOSS_MODEL;
		g_aBoss[nCntBoss].nNumMotion = 9;
		g_aBoss[nCntBoss].bLoopMotion = false;
		g_aBoss[nCntBoss].nNumKey = 0;
		g_aBoss[nCntBoss].nKey = 0;
		g_aBoss[nCntBoss].fCounterMotion = 0.0f;
		g_aBoss[nCntBoss].bJump = false;
		g_aBoss[nCntBoss].bDamage = false;
		g_aBoss[nCntBoss].fWidth = BOSS_R;
		g_aBoss[nCntBoss].fHeight = 4000.0f;
		g_aBoss[nCntBoss].fDepth = BOSS_R;
		g_aBoss[nCntBoss].fNumTurnBoss = 0.0f;
		g_aBoss[nCntBoss].fNumBoss = 0.0f;
		g_aBoss[nCntBoss].fDifferRot = 0.0f;
		g_aBoss[nCntBoss].frotVecX = 0.0f;
		g_aBoss[nCntBoss].frotVecZ = 0.0f;
		g_aBoss[nCntBoss].fToPlayerR = 0.0f;
		g_aBoss[nCntBoss].fSwordCollX = 0.0f;
		g_aBoss[nCntBoss].fSwordCollZ = 0.0f;
		g_aBoss[nCntBoss].bTurnBoss = false;
		g_aBoss[nCntBoss].bTurnBoss2 = false;
		g_aBoss[nCntBoss].bUse = false;
		g_aBoss[nCntBoss].nCntMoveTime = 0;
		g_aBoss[nCntBoss].nCntStop = 0;
		g_aBoss[nCntBoss].nCntAttack = 0;
		g_aBoss[nCntBoss].nCntAttack2 = 0;
		g_aBoss[nCntBoss].nIdx = 0;
		g_aBoss[nCntBoss].nIdxLife = 0;
		g_aBoss[nCntBoss].bullet[0].pos = D3DXVECTOR3(-90.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].bullet[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].bullet[1].pos = D3DXVECTOR3(90.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].bullet[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		for (int nCnt =0; nCnt < MAX_EFFECT; nCnt++)
		{
			g_aBoss[nCntBoss].nIdxEffect[nCnt] = 0;
		}
		g_aBoss[nCntBoss].nLife = MAX_BOSS_LIFE;
		g_aBoss[nCntBoss].MoveType = BOSS_MOVETYPE_STOP;

	}
	g_nCntBoss = 0;
	g_nAttackBoss = 0;
	g_nCntAllBoss = 0;

	//g_Boss.MotionType = BOSS_MOTIONTYPE_NEUTRAL;


	//Xファイル読み込み
	for (int nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		D3DXLoadMeshFromX("data/MODEL/enemy_boss/B_ENEMY_BODY_00.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aBoss[nCntBoss].aModel[0].pBuffMat, NULL, &g_aBoss[nCntBoss].aModel[0].nNumMat, &g_aBoss[nCntBoss].aModel[0].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy_boss/B_ENEMY_BODY_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aBoss[nCntBoss].aModel[1].pBuffMat, NULL, &g_aBoss[nCntBoss].aModel[1].nNumMat, &g_aBoss[nCntBoss].aModel[1].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy_boss/B_ENEMY_AMR_R_02.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aBoss[nCntBoss].aModel[2].pBuffMat, NULL, &g_aBoss[nCntBoss].aModel[2].nNumMat, &g_aBoss[nCntBoss].aModel[2].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy_boss/B_ENEMY_AMRA_R_03.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aBoss[nCntBoss].aModel[3].pBuffMat, NULL, &g_aBoss[nCntBoss].aModel[3].nNumMat, &g_aBoss[nCntBoss].aModel[3].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy_boss/B_ENEMY_AMR_L_04.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aBoss[nCntBoss].aModel[4].pBuffMat, NULL, &g_aBoss[nCntBoss].aModel[4].nNumMat, &g_aBoss[nCntBoss].aModel[4].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy_boss/B_ENEMY_AMRA_L_05.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aBoss[nCntBoss].aModel[5].pBuffMat, NULL, &g_aBoss[nCntBoss].aModel[5].nNumMat, &g_aBoss[nCntBoss].aModel[5].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy_boss/B_ENEMY_LEG_R_06.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aBoss[nCntBoss].aModel[6].pBuffMat, NULL, &g_aBoss[nCntBoss].aModel[6].nNumMat, &g_aBoss[nCntBoss].aModel[6].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy_boss/B_ENEMY_LEG_R_07.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aBoss[nCntBoss].aModel[7].pBuffMat, NULL, &g_aBoss[nCntBoss].aModel[7].nNumMat, &g_aBoss[nCntBoss].aModel[7].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy_boss/B_ENEMY_LEG_L_08.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aBoss[nCntBoss].aModel[8].pBuffMat, NULL, &g_aBoss[nCntBoss].aModel[8].nNumMat, &g_aBoss[nCntBoss].aModel[8].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy_boss/B_ENEMY_LEG_L_09.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aBoss[nCntBoss].aModel[9].pBuffMat, NULL, &g_aBoss[nCntBoss].aModel[9].nNumMat, &g_aBoss[nCntBoss].aModel[9].pMesh);
	}


	//テクスチャデータの取得
	D3DXMATERIAL *pMat;		//マテリアルへのポインタ

	for (int nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		for (int nCntModel = 0; nCntModel < g_aBoss[nCntBoss].nNumModel; nCntModel++)
		{
			//マテリアル情報に対するポインタを取得
			pMat = (D3DXMATERIAL *)g_aBoss[nCntBoss].aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aBoss[nCntBoss].aModel[nCntModel].nNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_aBoss[nCntBoss].aModel[nCntModel].pTexture[nCntMat]);
				}
			}
		}
	}

	//textファイル読み込み
	//各パーツの階層構造を設定
	for (int nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		FILE *pfile = fopen("data/MOTION/enemyB_motion.txt", "r");

		char index[] = "INDEX";
		char string[255][255];
		char search[] = "KEYSET";
		char EndKeySet[] = "END_KEYSET";
		char LoopSearch[] = "LOOP";
		char KeySearch[] = "KEY";
		char MotionSearch[] = "MOTIONSET";
		char EndMotionSet[] = "END_MOTIONSET";

		for (int nCntRead = 0; nCntRead < g_aBoss[nCntBoss].nNumModel; nCntRead++)
		{
			while (fgets(string[0], 255, pfile) != NULL)
			{
				if (strstr(string[0], index))
				{
					fscanf(pfile, "%s%s%d%*s%*s", string[1], string[2], &g_aBoss[nCntBoss].aModel[nCntRead].nIdxModelParent);
					fscanf(pfile, "%s%s%f%f%f", string[3], string[4], &g_aBoss[nCntBoss].aModel[nCntRead].pos.x, &g_aBoss[nCntBoss].aModel[nCntRead].pos.y, &g_aBoss[nCntBoss].aModel[nCntRead].pos.z);
					fscanf(pfile, "%s%s%f%f%f", string[5], string[6], &g_aBoss[nCntBoss].aModel[nCntRead].rot.x, &g_aBoss[nCntBoss].aModel[nCntRead].rot.y, &g_aBoss[nCntBoss].aModel[nCntRead].rot.z);
					break;
				}
			}
		}

		//モーションの読み込み
		for (int nCntMotion = 0; nCntMotion < BOSS_MOTION_MAX; nCntMotion++)
		{
			//ループ情報の取得
			//キー数の取得
			while (fgets(string[0], 255, pfile) != NULL)
			{
				if (strstr(string[0], MotionSearch))
				{
					fscanf(pfile, "%s%s%d%*s%*s%*s%*s", string[1], string[2], &g_aBoss[nCntBoss].aMotionInfo[nCntMotion].bLoop);
					fscanf(pfile, "%s%s%d", string[3], string[4], &g_aBoss[nCntBoss].aMotionInfo[nCntMotion].nNumKey);
					break;
				}
			}

			for (int nCntKey = 0; nCntKey < g_aBoss[nCntBoss].aMotionInfo[nCntMotion].nNumKey; nCntKey++)
			{
				//フレーム数の取得
				while (fgets(string[0], 255, pfile) != NULL)
				{
					if (strstr(string[0], search))
					{
						fscanf(pfile, "%s%s%d", string[0], string[0], &g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
						//g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame = g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame * (144 / 60);
						break;
					}
				}

				//位置、回転情報の取得
				for (int nCntRead = 0; nCntRead < g_aBoss[nCntBoss].nNumModel; nCntRead++)
				{
					while (fgets(string[0], 255, pfile) != NULL)
					{
						if (strstr(string[0], KeySearch))
						{
							fscanf(pfile, "%s%s%f%f%f", string[1], string[2], &g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosX, &g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosY, &g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosZ);
							fscanf(pfile, "%s%s%f%f%f%*s", string[0], string[0], &g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotX, &g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotY, &g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotZ);
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
	


	//親子関係による位置ずれの修正
	for (int nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		for (int nCntMotion = 0; nCntMotion < BOSS_MOTION_MAX; nCntMotion++)
		{
			for (int nCntKey = 0; nCntKey < g_aBoss[nCntBoss].aMotionInfo[nCntMotion].nNumKey; nCntKey++)
			{
				for (int nCntRead = 0; nCntRead < g_aBoss[nCntBoss].nNumModel; nCntRead++)
				{
					g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosX = g_aBoss[nCntBoss].aModel[nCntRead].pos.x + g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosX;
					g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosY = g_aBoss[nCntBoss].aModel[nCntRead].pos.y + g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosY;
					g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosZ = g_aBoss[nCntBoss].aModel[nCntRead].pos.z + g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fPosZ;
					g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotX = g_aBoss[nCntBoss].aModel[nCntRead].rot.x + g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotX;
					g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotY = g_aBoss[nCntBoss].aModel[nCntRead].rot.y + g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotY;
					g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotZ = g_aBoss[nCntBoss].aModel[nCntRead].rot.z + g_aBoss[nCntBoss].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRead].fRotZ;
				}
			}
		}
		g_aBoss[nCntBoss].move.x = -2.0f;
		g_aBoss[nCntBoss].move.z = 1.0f;
	}
	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化
}

//=======================================================================
//終了処理
//=======================================================================
void UninitBoss(void)
{
	for (int nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		for (int nCntModel = 0; nCntModel < g_aBoss[nCntBoss].nNumModel; nCntModel++)
		{
			//メッシュの破棄
			if (g_aBoss[nCntBoss].aModel[nCntModel].pMesh != NULL)
			{
				g_aBoss[nCntBoss].aModel[nCntModel].pMesh->Release();
				g_aBoss[nCntBoss].aModel[nCntModel].pMesh = NULL;
			}

			//マテリアルの破棄
			if (g_aBoss[nCntBoss].aModel[nCntModel].pBuffMat != NULL)
			{
				g_aBoss[nCntBoss].aModel[nCntModel].pBuffMat->Release();
				g_aBoss[nCntBoss].aModel[nCntModel].pBuffMat = NULL;
			}

			//テクスチャの破棄
			for (int nCntTex = 0; nCntTex < BOSS_MAX_TEXTURE; nCntTex++)
			{
				if (g_aBoss[nCntBoss].aModel[nCntModel].pTexture[nCntTex] != NULL)
				{
					g_aBoss[nCntBoss].aModel[nCntModel].pTexture[nCntTex]->Release();
					g_aBoss[nCntBoss].aModel[nCntModel].pTexture[nCntTex] = NULL;
				}
			}
		}
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateBoss(void)
{
	Camera *pCamera = GetCamera();
	PLAYER *pPlayer = GetPlayer();
	EnemyLife *pEnemyLife = GetEnemyLife();
	SHADOW *pShadow = GetShadow();
	Life *pLife = GetLife();
	for (int nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++,pEnemyLife++)
	{
		if (g_aBoss[nCntBoss].bUse == true && pPlayer->bUse == true)
		{
			SetEffect(D3DXVECTOR3(g_aBoss[nCntBoss].bullet[0].mtxWorld._41, g_aBoss[nCntBoss].bullet[0].mtxWorld._42, g_aBoss[nCntBoss].bullet[0].mtxWorld._43),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, D3DXCOLOR(0, 255, 255, 255), 2, EFFEFCT_MOVETYPE_PLAYER_HOVER);
			SetEffect(D3DXVECTOR3(g_aBoss[nCntBoss].bullet[1].mtxWorld._41, g_aBoss[nCntBoss].bullet[1].mtxWorld._42, g_aBoss[nCntBoss].bullet[1].mtxWorld._43),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, D3DXCOLOR(255, 255, 0, 255), 2, EFFEFCT_MOVETYPE_PLAYER_HOVER);

			g_aBoss[nCntBoss].MotionTypeOld = g_aBoss[nCntBoss].MotionType;
			g_aBoss[nCntBoss].posOld = g_aBoss[nCntBoss].pos;
			g_aBoss[nCntBoss].move.y -= GRAVITY;		//重力
			g_aBoss[nCntBoss].pos += g_aBoss[nCntBoss].move;
			g_aBoss[nCntBoss].frotVecX = pPlayer->pos.x - g_aBoss[nCntBoss].pos.x;
			g_aBoss[nCntBoss].frotVecZ = pPlayer->pos.z - g_aBoss[nCntBoss].pos.z;
			g_aBoss[nCntBoss].fToPlayerR = sqrt(g_aBoss[nCntBoss].frotVecX * g_aBoss[nCntBoss].frotVecX + g_aBoss[nCntBoss].frotVecZ * g_aBoss[nCntBoss].frotVecZ);


			//動く方向に向く設定
			//g_aBoss[nCntBoss].move.z = -cosf(g_aBoss[nCntBoss].rot.y) * BOSS_SPEED;
			//g_aBoss[nCntBoss].move.x = -sinf(g_aBoss[nCntBoss].rot.y) * BOSS_SPEED;

			//モーション
			if (g_aBoss[nCntBoss].move.x == 0.0f && g_aBoss[nCntBoss].move.z == 0.0f && g_aBoss[nCntBoss].MotionType != BOSS_MOTIONTYPE_BULLET && g_aBoss[nCntBoss].MotionType != BOSS_MOTIONTYPE_BULLET_BIG)
			{
				g_aBoss[nCntBoss].MotionType = BOSS_MOTIONTYPE_NEUTRAL;
			}
			else if (g_aBoss[nCntBoss].move.x != 0.0f || g_aBoss[nCntBoss].move.z != 0.0f)
			{
				g_aBoss[nCntBoss].MotionType = BOSS_MOTIONTYPE_MOVE;
			}

			if (g_aBoss[nCntBoss].pos.y <= 10.0f)
			{
				g_aBoss[nCntBoss].pos.y = 10.0f;
				g_aBoss[nCntBoss].move.y = 0.0f;
				g_aBoss[nCntBoss].bJump = false;
			}

			
			//ボスとの当たり判定
			CollisionBoss(&g_aBoss[nCntBoss].pos, &g_aBoss[nCntBoss].posOld, &g_aBoss[nCntBoss].move, g_aBoss[nCntBoss].fWidth, g_aBoss[nCntBoss].fHeight, g_aBoss[nCntBoss].fDepth);
			//敵との当たり判定
			CollisionBoss(&g_aBoss[nCntBoss].pos, &g_aBoss[nCntBoss].posOld, &g_aBoss[nCntBoss].move, g_aBoss[nCntBoss].fWidth, g_aBoss[nCntBoss].fHeight, g_aBoss[nCntBoss].fDepth);
			//プレイヤーとの当たり判定
			if (CollisionPlayer(&g_aBoss[nCntBoss].pos, &g_aBoss[nCntBoss].posOld, &g_aBoss[nCntBoss].move, g_aBoss[nCntBoss].fWidth, g_aBoss[nCntBoss].fHeight, g_aBoss[nCntBoss].fDepth) == true)
			{
				
			}

			//プレイヤーの弾が当たった時の処理
			int nBulletType = CollisionBullet(&g_aBoss[nCntBoss].pos, g_aBoss[nCntBoss].fWidth);
			if (nBulletType == 1)
			{
				g_aBoss[nCntBoss].nLife--;
				SetAddEvolutionGauge(1.0f);
			}
			else if (nBulletType == 2)
			{
				g_aBoss[nCntBoss].nLife--;
				SetAddEvolutionGauge(1.0f);
			}
			else if (nBulletType == 3)
			{
				g_aBoss[nCntBoss].nLife -= 5;
				SetAddEvolutionGauge(5.0f);
			}

			//プレイヤーの剣との当たり判定
			if (g_aBoss[nCntBoss].bDamage == false && pPlayer->bSlash == true)
			{
				if (CollisionSword(&g_aBoss[nCntBoss].pos, g_aBoss[nCntBoss].fWidth) == true)
				{
					if (pPlayer->nType == PLAYERTYPE_SPEED)
					{
						PlaySound(SOUND_LABEL_HIT);
						g_aBoss[nCntBoss].nLife -= 3;
						SetScore(300);
					}
					else if (pPlayer->nType == PLAYERTYPE_NOMAL)
					{
						PlaySound(SOUND_LABEL_HIT);
						g_aBoss[nCntBoss].nLife -= 3;
						SetAddEvolutionGauge(3.0f);
						SetScore(300);
					}
					else if (pPlayer->nType == PLAYERTYPE_POWER)
					{
						PlaySound(SOUND_LABEL_HIT);
						g_aBoss[nCntBoss].nLife -= 6;
						SetScore(600);
					}
					g_aBoss[nCntBoss].MoveType = BOSS_MOVETYPE_DAMAGE;
					g_aBoss[nCntBoss].nKey = 0;
					g_aBoss[nCntBoss].fCounterMotion = 0.0f;
					g_aBoss[nCntBoss].bDamage = true;
				}
			}

			if (g_aBoss[nCntBoss].nLife <= 0)
			{
				g_aBoss[nCntBoss].nLife = 0;
				g_aBoss[nCntBoss].bUse = false;
				SetScore(10000);
				pEnemyLife->bUse = false;
				g_aBoss[nCntBoss].nLife = MAX_BOSS_LIFE;
				g_aBoss[nCntBoss].MoveType = BOSS_MOVETYPE_STOP;
				g_nCntAllBoss--;
				for (int nCnt = 0; nCnt < 8; nCnt++)
				{
					SetEffect(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x, g_aBoss[nCntBoss].pos.y + 80.0f, g_aBoss[nCntBoss].pos.z),
						D3DXVECTOR3(cosf(D3DX_PI * 2.0f / 8.0f * nCnt) * 0.8f, 1.0f, sinf(D3DX_PI * 2.0f / 8.0f * nCnt) * 0.8f),
						20.0f, 20.0f, D3DXCOLOR(255, 0, 0, 255), 60, EFFEFCT_MOVETYPE_ENEMY_DEATH);
				}
				if (pCamera->nEnemyNumber == nCntBoss && pCamera->nWhoRockOn == 2)
				{
					pCamera->bRockOn = false;
				}
			}

			if (pPlayer->bSlash == false)
			{
				g_aBoss[nCntBoss].bDamage = false;
			}
			
			//影の設定
			SetPositionShadow(g_aBoss[nCntBoss].nIdx, g_aBoss[nCntBoss].pos, g_aBoss[nCntBoss].bUse);
			//ライフゲージの設定
			SetPositionEnemyLife(g_aBoss[nCntBoss].nIdxLife, D3DXVECTOR3(g_aBoss[nCntBoss].pos.x, g_aBoss[nCntBoss].pos.y + 230.0f, g_aBoss[nCntBoss].pos.z),
								g_aBoss[nCntBoss].bUse, MAX_BOSS_LIFE, g_aBoss[nCntBoss].nLife, 100.0f);
			

			//動きの処理
			MoveTypeBoss(nCntBoss);
			//=======================================================================
			//モーション
			//=======================================================================
			if (g_aBoss[nCntBoss].MotionType != g_aBoss[nCntBoss].MotionTypeOld )
			{
				g_aBoss[nCntBoss].nKey = 0;
				g_aBoss[nCntBoss].fCounterMotion = 0.0f;
			}
			MotionBoss(nCntBoss);
			

			//回転の慣性
			if (g_aBoss[nCntBoss].fNumTurnBoss > D3DX_PI)
			{
				g_aBoss[nCntBoss].fNumTurnBoss = -D3DX_PI - (D3DX_PI - g_aBoss[nCntBoss].fNumTurnBoss);
			}
			else if (g_aBoss[nCntBoss].fNumTurnBoss < -D3DX_PI)
			{
				g_aBoss[nCntBoss].fNumTurnBoss = D3DX_PI - (-D3DX_PI - g_aBoss[nCntBoss].fNumTurnBoss);
			}

			if (g_aBoss[nCntBoss].rot.y < 0.0f && -g_aBoss[nCntBoss].rot.y + g_aBoss[nCntBoss].fNumTurnBoss > D3DX_PI)
			{
				g_aBoss[nCntBoss].fDifferRot = (-D3DX_PI - g_aBoss[nCntBoss].rot.y) + -(D3DX_PI - g_aBoss[nCntBoss].fNumTurnBoss);
			}
			else if (g_aBoss[nCntBoss].rot.y >= D3DX_PI / 2.0f && g_aBoss[nCntBoss].rot.y - g_aBoss[nCntBoss].fNumTurnBoss > D3DX_PI)
			{
				g_aBoss[nCntBoss].fDifferRot = (D3DX_PI - g_aBoss[nCntBoss].rot.y) - (-D3DX_PI - g_aBoss[nCntBoss].fNumTurnBoss);
			}
			else
			{
				g_aBoss[nCntBoss].fDifferRot = (g_aBoss[nCntBoss].fNumTurnBoss - g_aBoss[nCntBoss].rot.y);
			}


			g_aBoss[nCntBoss].rot.y += g_aBoss[nCntBoss].fDifferRot * 0.1f;
			if (g_aBoss[nCntBoss].rot.y - g_aBoss[nCntBoss].fNumTurnBoss < 0.001 && g_aBoss[nCntBoss].rot.y - g_aBoss[nCntBoss].fNumTurnBoss > -0.001)
			{
				g_aBoss[nCntBoss].bTurnBoss = false;

			}

			if (g_aBoss[nCntBoss].rot.y > D3DX_PI)
			{
				g_aBoss[nCntBoss].rot.y = -D3DX_PI;
			}
			else if (g_aBoss[nCntBoss].rot.y < -D3DX_PI)
			{
				g_aBoss[nCntBoss].rot.y = D3DX_PI;
			}

			//ロックオン処理
			if (pCamera->bRockOn == true && pCamera->nEnemyNumber == nCntBoss && pCamera->nWhoRockOn == 2)
			{
				SetBillboard(g_aBoss[nCntBoss].pos, 100.0f, 100.0f);
				SetPositionBillboard(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x, g_aBoss[nCntBoss].pos.y + 90.0f, g_aBoss[nCntBoss].pos.z), g_aBoss[nCntBoss].bUse);
			}
			//モデルとの当たり判定
			CollisionModelTxt(&g_aBoss[nCntBoss].move, &g_aBoss[nCntBoss].pos, &g_aBoss[nCntBoss].posOld, g_aBoss[nCntBoss].fWidth);
		}	
	}
}

//=======================================================================
//描画処理
//=======================================================================
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する

	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	for (int nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == true)
		{
			D3DXMatrixIdentity(&g_aBoss[nCntBoss].mtxWorld);		//プレイヤーのワールドマトリックスの初期化

														//プレイヤーの向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aBoss[nCntBoss].rot.y, g_aBoss[nCntBoss].rot.x, g_aBoss[nCntBoss].rot.z);
			D3DXMatrixMultiply(&g_aBoss[nCntBoss].mtxWorld, &g_aBoss[nCntBoss].mtxWorld, &mtxRot);

			//プレイヤーの位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBoss[nCntBoss].pos.x, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z);
			D3DXMatrixMultiply(&g_aBoss[nCntBoss].mtxWorld, &g_aBoss[nCntBoss].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBoss[nCntBoss].mtxWorld);

			//現在のマテリアルを保存
			pDevice->GetMaterial(&matDef);

			for (int nCntModel = 0; nCntModel < g_aBoss[nCntBoss].nNumModel; nCntModel++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;		//計算用マトリックス
				D3DXMATRIX mtxParent;						//親のマトリックス

				D3DXMatrixIdentity(&g_aBoss[nCntBoss].aModel[nCntModel].mtxWorld);		//各パーツのワールドマトリックスの初期化

																				//各パーツの向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aBoss[nCntBoss].aModel[nCntModel].rot.y, g_aBoss[nCntBoss].aModel[nCntModel].rot.x, g_aBoss[nCntBoss].aModel[nCntModel].rot.z);
				D3DXMatrixMultiply(&g_aBoss[nCntBoss].aModel[nCntModel].mtxWorld, &g_aBoss[nCntBoss].aModel[nCntModel].mtxWorld, &mtxRotModel);

				//各パーツの位置を反映
				D3DXMatrixTranslation(&mtxTransModel, g_aBoss[nCntBoss].aModel[nCntModel].pos.x, g_aBoss[nCntBoss].aModel[nCntModel].pos.y, g_aBoss[nCntBoss].aModel[nCntModel].pos.z);
				D3DXMatrixMultiply(&g_aBoss[nCntBoss].aModel[nCntModel].mtxWorld, &g_aBoss[nCntBoss].aModel[nCntModel].mtxWorld, &mtxTransModel);

				//各パーツの親のマトリックスの設定
				if (g_aBoss[nCntBoss].aModel[nCntModel].nIdxModelParent != -1)
				{
					mtxParent = g_aBoss[nCntBoss].aModel[g_aBoss[nCntBoss].aModel[nCntModel].nIdxModelParent].mtxWorld;
				}
				else
				{
					mtxParent = g_aBoss[nCntBoss].mtxWorld;
				}

				//算出した各パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
				D3DXMatrixMultiply(&g_aBoss[nCntBoss].aModel[nCntModel].mtxWorld, &g_aBoss[nCntBoss].aModel[nCntModel].mtxWorld, &mtxParent);

				//各パーツのワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aBoss[nCntBoss].aModel[nCntModel].mtxWorld);

				//マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_aBoss[nCntBoss].aModel[nCntModel].pBuffMat->GetBufferPointer();
				for (int nCntMat = 0; nCntMat < (int)g_aBoss[nCntBoss].aModel[nCntModel].nNumMat; nCntMat++)
				{
					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//テクスチャの設定
					pDevice->SetTexture(0, NULL);
					//pDevice->SetTexture(0, g_apTextureBoss[nCntMat]);

					//モデル(パーツ)の描画
					g_aBoss[nCntBoss].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
				}

				//保存していたマテリアルを戻す
				pDevice->SetMaterial(&matDef);
			}

			//銃の設定
			for (int nCntBullet = 0; nCntBullet < 2; nCntBullet++)
			{
				D3DXMATRIX mtxParent;						//親のマトリックス
				D3DXMatrixIdentity(&g_aBoss[nCntBoss].bullet[nCntBullet].mtxWorld);		//プレイヤーのワールドマトリックスの初期化

																			//プレイヤーの向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aBoss[nCntBoss].bullet[nCntBullet].rot.y, g_aBoss[nCntBoss].bullet[nCntBullet].rot.x, g_aBoss[nCntBoss].bullet[nCntBullet].rot.z);
				D3DXMatrixMultiply(&g_aBoss[nCntBoss].bullet[nCntBullet].mtxWorld, &g_aBoss[nCntBoss].bullet[nCntBullet].mtxWorld, &mtxRot);

				//プレイヤーの位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_aBoss[nCntBoss].bullet[nCntBullet].pos.x, g_aBoss[nCntBoss].bullet[nCntBullet].pos.y, g_aBoss[nCntBoss].bullet[nCntBullet].pos.z);
				D3DXMatrixMultiply(&g_aBoss[nCntBoss].bullet[nCntBullet].mtxWorld, &g_aBoss[nCntBoss].bullet[nCntBullet].mtxWorld, &mtxTrans);

				if (nCntBullet == 0)
				{
					mtxParent = g_aBoss[nCntBoss].aModel[3].mtxWorld;
				}
				else
				{
					mtxParent = g_aBoss[nCntBoss].aModel[5].mtxWorld;
				}

				//算出した各パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
				D3DXMatrixMultiply(&g_aBoss[nCntBoss].bullet[nCntBullet].mtxWorld, &g_aBoss[nCntBoss].bullet[nCntBullet].mtxWorld, &mtxParent);

				//ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aBoss[nCntBoss].bullet[nCntBullet].mtxWorld);
			}
		}
	}
}

//=======================================================================
//モーション処理
//=======================================================================
void MotionBoss(int nCntBoss)
{
	//プレイヤーの取得
	PLAYER *pPlayer = GetPlayer();

	D3DXVECTOR3 posAsk[MAX_BOSS_MODEL];		//求めたい値
	D3DXVECTOR3 rotAsk[MAX_BOSS_MODEL];		//求めたい値
	D3DXVECTOR3 posDiffer[MAX_BOSS_MODEL];	//差分
	D3DXVECTOR3 rotDiffer[MAX_BOSS_MODEL];	//差分

	for (int nCntModel = 0; nCntModel < g_aBoss[nCntBoss].nNumModel - 1; nCntModel++)
	{
		if (g_aBoss[nCntBoss].nKey < g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].nNumKey - 1)//キーの最大数-1
		{
			posDiffer[nCntModel].x = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey + 1].aKey[nCntModel].fPosX
				- g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fPosX;
			posDiffer[nCntModel].y = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey + 1].aKey[nCntModel].fPosY
				- g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fPosY;
			posDiffer[nCntModel].z = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey + 1].aKey[nCntModel].fPosZ
				- g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fPosZ;
			rotDiffer[nCntModel].x = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey + 1].aKey[nCntModel].fRotX
				- g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fRotX;
			rotDiffer[nCntModel].y = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey + 1].aKey[nCntModel].fRotY
				- g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fRotY;
			rotDiffer[nCntModel].z = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey + 1].aKey[nCntModel].fRotZ
				- g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fRotZ;

			posAsk[nCntModel].x = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fPosX
				+ posDiffer[nCntModel].x * (g_aBoss[nCntBoss].fCounterMotion / g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].nFrame);
			posAsk[nCntModel].y = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fPosY
				+ posDiffer[nCntModel].y * (g_aBoss[nCntBoss].fCounterMotion / g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].nFrame);
			posAsk[nCntModel].z = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fPosZ
				+ posDiffer[nCntModel].z * (g_aBoss[nCntBoss].fCounterMotion / g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].nFrame);
			rotAsk[nCntModel].x = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fRotX
				+ rotDiffer[nCntModel].x * (g_aBoss[nCntBoss].fCounterMotion / g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].nFrame);
			rotAsk[nCntModel].y = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fRotY
				+ rotDiffer[nCntModel].y * (g_aBoss[nCntBoss].fCounterMotion / g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].nFrame);
			rotAsk[nCntModel].z = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fRotZ
				+ rotDiffer[nCntModel].z * (g_aBoss[nCntBoss].fCounterMotion / g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].nFrame);

			g_aBoss[nCntBoss].aModel[nCntModel].pos.x = posAsk[nCntModel].x;
			g_aBoss[nCntBoss].aModel[nCntModel].pos.y = posAsk[nCntModel].y;
			g_aBoss[nCntBoss].aModel[nCntModel].pos.z = posAsk[nCntModel].z;
			g_aBoss[nCntBoss].aModel[nCntModel].rot.x = rotAsk[nCntModel].x;
			g_aBoss[nCntBoss].aModel[nCntModel].rot.y = rotAsk[nCntModel].y;
			g_aBoss[nCntBoss].aModel[nCntModel].rot.z = rotAsk[nCntModel].z;
		}
		else if (g_aBoss[nCntBoss].nKey >= g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].nNumKey - 1)//キーの最大数-1
		{
			if (g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].bLoop == 1)
			{
				posDiffer[nCntModel].x = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[0].aKey[nCntModel].fPosX
					- g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fPosX;
				posDiffer[nCntModel].y = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[0].aKey[nCntModel].fPosY
					- g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fPosY;
				posDiffer[nCntModel].z = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[0].aKey[nCntModel].fPosZ
					- g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fPosZ;
				rotDiffer[nCntModel].x = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[0].aKey[nCntModel].fRotX
					- g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fRotX;
				rotDiffer[nCntModel].y = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[0].aKey[nCntModel].fRotY
					- g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fRotY;
				rotDiffer[nCntModel].z = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[0].aKey[nCntModel].fRotZ
					- g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fRotZ;

				posAsk[nCntModel].x = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fPosX
					+ posDiffer[nCntModel].x * (g_aBoss[nCntBoss].fCounterMotion / g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].nFrame);
				posAsk[nCntModel].y = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fPosY
					+ posDiffer[nCntModel].y * (g_aBoss[nCntBoss].fCounterMotion / g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].nFrame);
				posAsk[nCntModel].z = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fPosZ
					+ posDiffer[nCntModel].z * (g_aBoss[nCntBoss].fCounterMotion / g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].nFrame);
				rotAsk[nCntModel].x = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fRotX
					+ rotDiffer[nCntModel].x * (g_aBoss[nCntBoss].fCounterMotion / g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].nFrame);
				rotAsk[nCntModel].y = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fRotY
					+ rotDiffer[nCntModel].y * (g_aBoss[nCntBoss].fCounterMotion / g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].nFrame);
				rotAsk[nCntModel].z = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fRotZ
					+ rotDiffer[nCntModel].z * (g_aBoss[nCntBoss].fCounterMotion / g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].nFrame);

				g_aBoss[nCntBoss].aModel[nCntModel].pos.x = posAsk[nCntModel].x;
				g_aBoss[nCntBoss].aModel[nCntModel].pos.y = posAsk[nCntModel].y;
				g_aBoss[nCntBoss].aModel[nCntModel].pos.z = posAsk[nCntModel].z;
				g_aBoss[nCntBoss].aModel[nCntModel].rot.x = rotAsk[nCntModel].x;
				g_aBoss[nCntBoss].aModel[nCntModel].rot.y = rotAsk[nCntModel].y;
				g_aBoss[nCntBoss].aModel[nCntModel].rot.z = rotAsk[nCntModel].z;
			}
			else if (g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].bLoop == 0)
			{
				posDiffer[nCntModel].x = g_aBoss[nCntBoss].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[nCntModel].fPosX
					- g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fPosX;
				posDiffer[nCntModel].y = g_aBoss[nCntBoss].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[nCntModel].fPosY
					- g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fPosY;
				posDiffer[nCntModel].z = g_aBoss[nCntBoss].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[nCntModel].fPosZ
					- g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fPosZ;
				rotDiffer[nCntModel].x = g_aBoss[nCntBoss].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[nCntModel].fRotX
					- g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fRotX;
				rotDiffer[nCntModel].y = g_aBoss[nCntBoss].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[nCntModel].fRotY
					- g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fRotY;
				rotDiffer[nCntModel].z = g_aBoss[nCntBoss].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[nCntModel].fRotZ
					- g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fRotZ;

				posAsk[nCntModel].x = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fPosX
					+ posDiffer[nCntModel].x * (g_aBoss[nCntBoss].fCounterMotion / g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].nFrame);
				posAsk[nCntModel].y = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fPosY
					+ posDiffer[nCntModel].y * (g_aBoss[nCntBoss].fCounterMotion / g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].nFrame);
				posAsk[nCntModel].z = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fPosZ
					+ posDiffer[nCntModel].z * (g_aBoss[nCntBoss].fCounterMotion / g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].nFrame);
				rotAsk[nCntModel].x = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fRotX
					+ rotDiffer[nCntModel].x * (g_aBoss[nCntBoss].fCounterMotion / g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].nFrame);
				rotAsk[nCntModel].y = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fRotY
					+ rotDiffer[nCntModel].y * (g_aBoss[nCntBoss].fCounterMotion / g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].nFrame);
				rotAsk[nCntModel].z = g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].aKey[nCntModel].fRotZ
					+ rotDiffer[nCntModel].z * (g_aBoss[nCntBoss].fCounterMotion / g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].nFrame);

				g_aBoss[nCntBoss].aModel[nCntModel].pos.x = posAsk[nCntModel].x;
				g_aBoss[nCntBoss].aModel[nCntModel].pos.y = posAsk[nCntModel].y;
				g_aBoss[nCntBoss].aModel[nCntModel].pos.z = posAsk[nCntModel].z;
				g_aBoss[nCntBoss].aModel[nCntModel].rot.x = rotAsk[nCntModel].x;
				g_aBoss[nCntBoss].aModel[nCntModel].rot.y = rotAsk[nCntModel].y;
				g_aBoss[nCntBoss].aModel[nCntModel].rot.z = rotAsk[nCntModel].z;
			}
		}
	}

	if (g_aBoss[nCntBoss].MotionType == BOSS_MOTIONTYPE_BULLET && g_aBoss[nCntBoss].nKey == 1 &&
		(g_aBoss[nCntBoss].fCounterMotion == 0.0f || g_aBoss[nCntBoss].fCounterMotion == 10.0f))
	{
		
		SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].bullet[0].mtxWorld._41, g_aBoss[nCntBoss].bullet[0].mtxWorld._42, g_aBoss[nCntBoss].bullet[0].mtxWorld._43),
					D3DXVECTOR3(sinf(g_aBoss[nCntBoss].rot.y + D3DX_PI) * ENEMYBULLET_SPEED, 0.0f, cosf(g_aBoss[nCntBoss].rot.y + D3DX_PI) * ENEMYBULLET_SPEED),
					50.0f, 50.0f, D3DXCOLOR(255, 255, 255, 255), ENEMYBULLET_MOVETYPE_BOSS_SMALL);
	}
	if (g_aBoss[nCntBoss].MotionType == BOSS_MOTIONTYPE_BULLET_BIG && g_aBoss[nCntBoss].nKey == 1 &&
			(g_aBoss[nCntBoss].fCounterMotion == 0.0f || g_aBoss[nCntBoss].fCounterMotion == 10.0f || g_aBoss[nCntBoss].fCounterMotion == 20.0f ||
			g_aBoss[nCntBoss].fCounterMotion == 30.0f))
	{
		
		SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].bullet[0].mtxWorld._41, g_aBoss[nCntBoss].bullet[0].mtxWorld._42, g_aBoss[nCntBoss].bullet[0].mtxWorld._43),
			D3DXVECTOR3(sinf(g_aBoss[nCntBoss].rot.y + D3DX_PI) * ENEMYBULLET_SPEED, 0.0f, cosf(g_aBoss[nCntBoss].rot.y + D3DX_PI) * ENEMYBULLET_SPEED),
			100.0f, 100.0f, D3DXCOLOR(255, 255, 255, 255), ENEMYBULLET_MOVETYPE_BOSS_BIG);
	}

	

	g_aBoss[nCntBoss].fCounterMotion += 1.0f;
	if (g_aBoss[nCntBoss].fCounterMotion >= g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].aKeyInfo[g_aBoss[nCntBoss].nKey].nFrame)
	{
		if (g_aBoss[nCntBoss].nKey < g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].nNumKey - 1)//キーの最大数-1
		{
			g_aBoss[nCntBoss].nKey++;
			g_aBoss[nCntBoss].fCounterMotion = 0.0f;
		}
		else if (g_aBoss[nCntBoss].nKey >= g_aBoss[nCntBoss].aMotionInfo[g_aBoss[nCntBoss].MotionType].nNumKey - 1)
		{
			g_aBoss[nCntBoss].nKey = 0;
			g_aBoss[nCntBoss].fCounterMotion = 0.0f;
			g_aBoss[nCntBoss].MotionType = BOSS_MOTIONTYPE_NEUTRAL;
		}
	}
}

//=======================================================================
//敵の動き方の処理
//=======================================================================
void MoveTypeBoss(int nCntBoss)
{
	//プレイヤーの取得
	PLAYER *pPlayer = GetPlayer();

	if (g_aBoss[nCntBoss].fToPlayerR <= BOSS_SEARCH && g_aBoss[nCntBoss].MoveType != BOSS_MOVETYPE_ATTACK && g_aBoss[nCntBoss].MoveType != BOSS_MOVETYPE_DAMAGE)
	{
		g_aBoss[nCntBoss].MoveType = BOSS_MOVETYPE_ATTACK;
	}

	if (g_aBoss[nCntBoss].MoveType == BOSS_MOVETYPE_MOVE)
	{
		g_aBoss[nCntBoss].nCntMoveTime++;
		if (g_aBoss[nCntBoss].nCntMoveTime <= rand() % 650 + 450)
		{
			g_aBoss[nCntBoss].move.z = -cosf(g_aBoss[nCntBoss].rot.y) * BOSS_SPEED;
			g_aBoss[nCntBoss].move.x = -sinf(g_aBoss[nCntBoss].rot.y) * BOSS_SPEED;
		}
		else
		{
			g_aBoss[nCntBoss].MoveType = BOSS_MOVETYPE_STOP;
			g_aBoss[nCntBoss].nCntMoveTime = 0;
		}
	}
	else if (g_aBoss[nCntBoss].MoveType == BOSS_MOVETYPE_STOP)
	{
		g_aBoss[nCntBoss].move.z = 0.0f;
		g_aBoss[nCntBoss].move.x = 0.0f;

		g_aBoss[nCntBoss].nCntStop++;
		if (g_aBoss[nCntBoss].nCntStop >= BOSS_STOP_TIME)
		{
			g_aBoss[nCntBoss].MoveType = BOSS_MOVETYPE_TURN;
			g_aBoss[nCntBoss].bTurnBoss2 = true;
			g_aBoss[nCntBoss].nCntStop = 0;
		}
	}
	else if (g_aBoss[nCntBoss].MoveType == BOSS_MOVETYPE_TURN)
	{
		if (g_aBoss[nCntBoss].bTurnBoss2 == true)
		{
			//srand(1);
			g_aBoss[nCntBoss].fNumTurnBoss = BOSS_RAND;
			g_aBoss[nCntBoss].bTurnBoss2 = false;
		}
		if (g_aBoss[nCntBoss].rot.y - g_aBoss[nCntBoss].fNumTurnBoss < 0.05 && g_aBoss[nCntBoss].rot.y - g_aBoss[nCntBoss].fNumTurnBoss > -0.05)
		{
			g_aBoss[nCntBoss].MoveType = BOSS_MOVETYPE_MOVE;
		}
	}
	else if (g_aBoss[nCntBoss].MoveType == BOSS_MOVETYPE_DAMAGE)
	{
		g_aBoss[nCntBoss].MotionType = BOSS_MOTIONTYPE_DAMAGE;
		if (g_aBoss[nCntBoss].nKey == 0 && g_aBoss[nCntBoss].fCounterMotion == 0.0f)
		{
			g_aBoss[nCntBoss].fNumTurnBoss = atan2(g_aBoss[nCntBoss].frotVecX, g_aBoss[nCntBoss].frotVecZ) - D3DX_PI;
			g_aBoss[nCntBoss].posPlayer = pPlayer->pos;
		}

		g_aBoss[nCntBoss].frotVecX = g_aBoss[nCntBoss].posPlayer.x - g_aBoss[nCntBoss].pos.x;
		g_aBoss[nCntBoss].frotVecZ = g_aBoss[nCntBoss].posPlayer.z - g_aBoss[nCntBoss].pos.z;
		g_aBoss[nCntBoss].fToPlayerR = sqrt(g_aBoss[nCntBoss].frotVecX * g_aBoss[nCntBoss].frotVecX + g_aBoss[nCntBoss].frotVecZ * g_aBoss[nCntBoss].frotVecZ);

		if (g_aBoss[nCntBoss].fToPlayerR > BOSS_DAMAGE)
		{
			g_aBoss[nCntBoss].move.z = 0.0f;
			g_aBoss[nCntBoss].move.x = 0.0f;
			g_aBoss[nCntBoss].MoveType = BOSS_MOVETYPE_STOP;
			g_aBoss[nCntBoss].MotionType = BOSS_MOTIONTYPE_NEUTRAL;
		}
		else
		{
			g_aBoss[nCntBoss].move.z = -cosf(g_aBoss[nCntBoss].rot.y) * -BOSS_SPEED;
			g_aBoss[nCntBoss].move.x = -sinf(g_aBoss[nCntBoss].rot.y) * -BOSS_SPEED;
			if (g_aBoss[nCntBoss].nKey == 1)
			{
				g_aBoss[nCntBoss].move.z = 0.0f;
				g_aBoss[nCntBoss].move.x = 0.0f;
				g_aBoss[nCntBoss].MoveType = BOSS_MOVETYPE_STOP;
				g_aBoss[nCntBoss].MotionType = BOSS_MOTIONTYPE_NEUTRAL;
			}
		}
	}
	else if (g_aBoss[nCntBoss].MoveType == BOSS_MOVETYPE_ATTACK)
	{
		g_aBoss[nCntBoss].fNumTurnBoss = atan2(g_aBoss[nCntBoss].frotVecX, g_aBoss[nCntBoss].frotVecZ) - D3DX_PI;

		g_aBoss[nCntBoss].move.z = 0.0f;
		g_aBoss[nCntBoss].move.x = 0.0f;

		g_aBoss[nCntBoss].nCntStop++;
		if (g_aBoss[nCntBoss].nCntAttack >= 4)
		{
			g_aBoss[nCntBoss].MotionType = BOSS_MOTIONTYPE_BULLET_BIG;
			g_aBoss[nCntBoss].nCntAttack = 0;
		}
		if (g_aBoss[nCntBoss].nCntStop >= 150 && g_aBoss[nCntBoss].MotionType != BOSS_MOTIONTYPE_BULLET_BIG)
		{
			g_aBoss[nCntBoss].MotionType = BOSS_MOTIONTYPE_BULLET;
			g_aBoss[nCntBoss].nCntStop = 0;
			g_aBoss[nCntBoss].nCntAttack++;
		}

		

		if (g_aBoss[nCntBoss].fToPlayerR > BOSS_SEARCH)
		{
			g_aBoss[nCntBoss].MoveType = BOSS_MOVETYPE_STOP;
		}
	}
	

	//-------------------------------------------------
	//敵の移動制限
	//-------------------------------------------------
	if (g_aBoss[nCntBoss].pos.x >= PLAYER_LIMIT)
	{
		g_aBoss[nCntBoss].pos.x = PLAYER_LIMIT;
	}
	else if (g_aBoss[nCntBoss].pos.x <= -PLAYER_LIMIT)
	{
		g_aBoss[nCntBoss].pos.x = -PLAYER_LIMIT;
	}
	if (g_aBoss[nCntBoss].pos.z >= PLAYER_LIMIT)
	{
		g_aBoss[nCntBoss].pos.z = PLAYER_LIMIT;
	}
	else if (g_aBoss[nCntBoss].pos.z <= -PLAYER_LIMIT)
	{
		g_aBoss[nCntBoss].pos.z = -PLAYER_LIMIT;
	}
}


//=======================================================================
//設定処理
//=======================================================================
void SetBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == false)
		{
			g_aBoss[nCntBoss].rot = rot;
			g_aBoss[nCntBoss].pos = pos;
			g_aBoss[nCntBoss].bUse = true;
			g_aBoss[nCntBoss].nIdx = SetShadow(g_aBoss[nCntBoss].pos, g_aBoss[nCntBoss].fWidth, g_aBoss[nCntBoss].fDepth);
			g_aBoss[nCntBoss].nIdxLife = SetEnemyLife(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x, g_aBoss[nCntBoss].pos.y + 230.0f, g_aBoss[nCntBoss].pos.z), 100.0f, 5.0f);
			for (int nCnt = 0; nCnt < 32; nCnt++)
			{
				SetEffect(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + cos(D3DX_PI * 2.0f / 32.0f * nCnt) * g_aBoss[nCntBoss].fWidth,
					g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z + sin(D3DX_PI * 2.0f / 32.0f * nCnt) * g_aBoss[nCntBoss].fWidth),
					D3DXVECTOR3(0.0f, 1.0f, 0.0f), 10.0f, 30.0f, D3DXCOLOR(255, 255, 0, 100), 60, EFFEFCT_MOVETYPE_ENEMY_APPEAR);
			}
			g_nCntAllBoss++;
			break;
		}
	}
	
}

//=======================================================================
//敵との当たり判定
//=======================================================================
void CollisionBoss(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth)
{
	BOSS *pBoss;
	pBoss = GetBoss();

	for (int nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++,pBoss++)
	{
		if (pBoss->bUse == true)
		{
			if (pPos->x > pBoss->pos.x - pBoss->fWidth / 2.0f - fWidth / 2.0f &&
				pPos->x < pBoss->pos.x + pBoss->fWidth / 2.0f + fWidth / 2.0f &&
				pPos->z > pBoss->pos.z - pBoss->fDepth / 2.0f - fDepth / 2.0f &&
				pPos->z < pBoss->pos.z + pBoss->fDepth / 2.0f + fDepth / 2.0f &&
				pPos->y <= pBoss->pos.y + pBoss->fHeight &&
				pBeforePos->y >= pBoss->pos.y + pBoss->fHeight)
			{
				pPos->y = pBoss->pos.y + pBoss->fHeight;
				pMove->y = 0.0f;
			}
			else if (pPos->x > pBoss->pos.x - pBoss->fWidth / 2.0f - fWidth / 2.0f &&
					pPos->x < pBoss->pos.x + pBoss->fWidth / 2.0f + fWidth / 2.0f &&
					pPos->z > pBoss->pos.z - pBoss->fDepth / 2.0f - fDepth / 2.0f &&
					pPos->z < pBoss->pos.z + pBoss->fDepth / 2.0f + fDepth / 2.0f &&
					pPos->y >= pBoss->pos.y - fHeight &&
					pBeforePos->y <= pBoss->pos.y - fHeight)
			{
				pPos->y = pBoss->pos.y - fHeight;
			}

			if (pPos->y < pBoss->pos.y + pBoss->fHeight &&
				pPos->y > pBoss->pos.y - fHeight &&
				pPos->z > pBoss->pos.z - pBoss->fDepth / 2.0f - fDepth / 2.0f &&
				pPos->z < pBoss->pos.z + pBoss->fDepth / 2.0f + fDepth / 2.0f &&
				pPos->x >= pBoss->pos.x - pBoss->fWidth / 2.0f - fWidth / 2.0f &&
				pBeforePos->x <= pBoss->pos.x - pBoss->fWidth / 2.0f - fWidth / 2.0f)
			{
				pPos->x = pBoss->pos.x - pBoss->fWidth / 2.0f - fWidth / 2.0f;
			}
			else if (pPos->y < pBoss->pos.y + pBoss->fHeight &&
					pPos->y > pBoss->pos.y - fHeight &&
					pPos->z > pBoss->pos.z - pBoss->fDepth / 2.0f - fDepth / 2.0f &&
					pPos->z < pBoss->pos.z + pBoss->fDepth / 2.0f + fDepth / 2.0f &&
					pPos->x <= pBoss->pos.x + pBoss->fWidth / 2.0f + fWidth / 2.0f &&
					pBeforePos->x >= pBoss->pos.x + pBoss->fWidth / 2.0f + fWidth / 2.0f)
			{
				pPos->x = pBoss->pos.x + pBoss->fWidth / 2.0f + fWidth / 2.0f;
			}

			if (pPos->y < pBoss->pos.y + pBoss->fHeight &&
				pPos->y > pBoss->pos.y - fHeight &&
				pPos->x > pBoss->pos.x - pBoss->fWidth / 2.0f - fWidth / 2.0f &&
				pPos->x < pBoss->pos.x + pBoss->fWidth / 2.0f + fWidth / 2.0f &&
				pPos->z >= pBoss->pos.z - pBoss->fDepth / 2.0f - fDepth / 2.0f &&
				pBeforePos->z <= pBoss->pos.z - pBoss->fDepth / 2.0f - fDepth / 2.0f)
			{
				pPos->z = pBoss->pos.z - pBoss->fDepth / 2.0f - fDepth / 2.0f;
			}
			else if (pPos->y < pBoss->pos.y + pBoss->fHeight &&
					pPos->y > pBoss->pos.y - fHeight &&
					pPos->x > pBoss->pos.x - pBoss->fWidth / 2.0f - fWidth / 2.0f &&
					pPos->x < pBoss->pos.x + pBoss->fWidth / 2.0f + fWidth / 2.0f &&
					pPos->z <= pBoss->pos.z + pBoss->fDepth / 2.0f + fDepth / 2.0f &&
					pBeforePos->z >= pBoss->pos.z + pBoss->fDepth / 2.0f + fDepth / 2.0f)
			{
				pPos->z = pBoss->pos.z + pBoss->fDepth / 2.0f + fDepth / 2.0f;
			}

		}
	}
}


//=======================================================================
//取得処理
//=======================================================================
BOSS *GetBoss(void)
{
	return &g_aBoss[0];
}

BOSS *GetAttackBoss(void)
{
	return &g_aBoss[g_nAttackBoss];
}

int GetUseBoss(void)
{
	return g_nCntBoss;
}


int GetAllBoss(void)
{
	return g_nCntAllBoss;
}