//=======================================================================
//敵に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "enemy.h"
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
#include "boss.h"
#include "modeltxt.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================
ENEMY g_aEnemy[MAX_ENEMY];				//プレイヤーの構造体
int g_nCntEnemy;						//敵の数ぶん回すために必要
int g_nCntAllEnemy;						//敵の現在の総数
int g_nAttackEnemy;						//剣の当たり判定に必要

//=======================================================================
//初期化処理
//=======================================================================
void InitEnemy(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//初期化
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
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
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
		g_aEnemy[nCntEnemy].fWidth = 90.0f;
		g_aEnemy[nCntEnemy].fHeight = 4000.0f;
		g_aEnemy[nCntEnemy].fDepth = 90.0f;
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
		g_aEnemy[nCntEnemy].nIdxLife = 0;
		g_aEnemy[nCntEnemy].sword.pos = D3DXVECTOR3(-40.0f, 0.0f, -90.0f);
		g_aEnemy[nCntEnemy].sword.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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


	//Xファイル読み込み
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		D3DXLoadMeshFromX("data/MODEL/enemy_nomal/N_ENEMY_BODY_00.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[0].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[0].nNumMat, &g_aEnemy[nCntEnemy].aModel[0].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy_nomal/N_ENEMY_BODY_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[1].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[1].nNumMat, &g_aEnemy[nCntEnemy].aModel[1].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy_nomal/N_ENEMY_AMR_R_02.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[2].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[2].nNumMat, &g_aEnemy[nCntEnemy].aModel[2].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy_nomal/N_ENEMY_AMR_R_03.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[3].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[3].nNumMat, &g_aEnemy[nCntEnemy].aModel[3].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy_nomal/N_ENEMY_AMR_L_04.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[4].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[4].nNumMat, &g_aEnemy[nCntEnemy].aModel[4].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy_nomal/N_ENEMY_AMR_L_05.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[5].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[5].nNumMat, &g_aEnemy[nCntEnemy].aModel[5].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy_nomal/N_ENEMY_LEG_R_06.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[6].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[6].nNumMat, &g_aEnemy[nCntEnemy].aModel[6].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy_nomal/N_ENEMY_LEG_R_07.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[7].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[7].nNumMat, &g_aEnemy[nCntEnemy].aModel[7].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy_nomal/N_ENEMY_LEG_L_08.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[8].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[8].nNumMat, &g_aEnemy[nCntEnemy].aModel[8].pMesh);
		D3DXLoadMeshFromX("data/MODEL/enemy_nomal/N_ENEMY_LEG_L_09.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aEnemy[nCntEnemy].aModel[9].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[9].nNumMat, &g_aEnemy[nCntEnemy].aModel[9].pMesh);
	}


	//テクスチャデータの取得
	D3DXMATERIAL *pMat;		//マテリアルへのポインタ

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		for (int nCntModel = 0; nCntModel < g_aEnemy[nCntEnemy].nNumModel; nCntModel++)
		{
			//マテリアル情報に対するポインタを取得
			pMat = (D3DXMATERIAL *)g_aEnemy[nCntEnemy].aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aEnemy[nCntEnemy].aModel[nCntModel].nNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_aEnemy[nCntEnemy].aModel[nCntModel].pTexture[nCntMat]);
				}
			}
		}
	}

	//textファイル読み込み
	//各パーツの階層構造を設定
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		FILE *pfile = fopen("data/MOTION/enemyN_motion.txt", "r");

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

		//モーションの読み込み
		for (int nCntMotion = 0; nCntMotion < ENEMY_MOTION_MAX; nCntMotion++)
		{
			//ループ情報の取得
			//キー数の取得
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
				//フレーム数の取得
				while (fgets(string[0], 255, pfile) != NULL)
				{
					if (strstr(string[0], search))
					{
						fscanf(pfile, "%s%s%d", string[0], string[0], &g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
						//g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame = g_aEnemy[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame * (144 / 60);
						break;
					}
				}

				//位置、回転情報の取得
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
	


	//親子関係による位置ずれの修正
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
	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化
}

//=======================================================================
//終了処理
//=======================================================================
void UninitEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		for (int nCntModel = 0; nCntModel < g_aEnemy[nCntEnemy].nNumModel; nCntModel++)
		{
			//メッシュの破棄
			if (g_aEnemy[nCntEnemy].aModel[nCntModel].pMesh != NULL)
			{
				g_aEnemy[nCntEnemy].aModel[nCntModel].pMesh->Release();
				g_aEnemy[nCntEnemy].aModel[nCntModel].pMesh = NULL;
			}

			//マテリアルの破棄
			if (g_aEnemy[nCntEnemy].aModel[nCntModel].pBuffMat != NULL)
			{
				g_aEnemy[nCntEnemy].aModel[nCntModel].pBuffMat->Release();
				g_aEnemy[nCntEnemy].aModel[nCntModel].pBuffMat = NULL;
			}

			//テクスチャの破棄
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
//更新処理
//=======================================================================
void UpdateEnemy(void)
{
	Camera *pCamera = GetCamera();
	PLAYER *pPlayer = GetPlayer();
	EnemyLife *pEnemyLife = GetEnemyLife();
	SHADOW *pShadow = GetShadow();
	Life *pLife = GetLife();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++,pEnemyLife++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true && pPlayer->bUse == true)
		{
			SetEffect(D3DXVECTOR3(g_aEnemy[nCntEnemy].sword.mtxWorld._41, g_aEnemy[nCntEnemy].sword.mtxWorld._42, g_aEnemy[nCntEnemy].sword.mtxWorld._43),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, D3DXCOLOR(0, 255, 255, 255), 2, EFFEFCT_MOVETYPE_PLAYER_HOVER);

			g_aEnemy[nCntEnemy].MotionTypeOld = g_aEnemy[nCntEnemy].MotionType;
			g_aEnemy[nCntEnemy].posOld = g_aEnemy[nCntEnemy].pos;
			g_aEnemy[nCntEnemy].move.y -= GRAVITY;		//重力
			g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].move;

			g_aEnemy[nCntEnemy].frotVecX = pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x;
			g_aEnemy[nCntEnemy].frotVecZ = pPlayer->pos.z - g_aEnemy[nCntEnemy].pos.z;
			g_aEnemy[nCntEnemy].fToPlayerR = sqrt(g_aEnemy[nCntEnemy].frotVecX * g_aEnemy[nCntEnemy].frotVecX + g_aEnemy[nCntEnemy].frotVecZ * g_aEnemy[nCntEnemy].frotVecZ);


			//動く方向に向く設定
			//g_aEnemy[nCntEnemy].move.z = -cosf(g_aEnemy[nCntEnemy].rot.y) * ENEMY_SPEED;
			//g_aEnemy[nCntEnemy].move.x = -sinf(g_aEnemy[nCntEnemy].rot.y) * ENEMY_SPEED;

			//モーション
			if (g_aEnemy[nCntEnemy].move.x == 0.0f && g_aEnemy[nCntEnemy].move.z == 0.0f && g_aEnemy[nCntEnemy].MotionType != ENEMY_MOTIONTYPE_PUNCH)
			{
				g_aEnemy[nCntEnemy].MotionType = ENEMY_MOTIONTYPE_NEUTRAL;
			}
			else if (g_aEnemy[nCntEnemy].move.x != 0.0f | g_aEnemy[nCntEnemy].move.z != 0.0f)
			{
				g_aEnemy[nCntEnemy].MotionType = ENEMY_MOTIONTYPE_MOVE;
			}

			if (g_aEnemy[nCntEnemy].pos.y <= 50.0f)
			{
				g_aEnemy[nCntEnemy].pos.y = 50.0f;
				g_aEnemy[nCntEnemy].move.y = 0.0f;
				g_aEnemy[nCntEnemy].bJump = false;
			}

			
			//敵との当たり判定
			CollisionEnemy(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posOld, &g_aEnemy[nCntEnemy].move, g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].fHeight, g_aEnemy[nCntEnemy].fDepth);
			//敵との当たり判定
			CollisionBoss(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posOld, &g_aEnemy[nCntEnemy].move, g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].fHeight, g_aEnemy[nCntEnemy].fDepth);
			//プレイヤーとの当たり判定
			if (CollisionPlayer(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posOld, &g_aEnemy[nCntEnemy].move, g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].fHeight, g_aEnemy[nCntEnemy].fDepth) == true)
			{
				if (g_aEnemy[nCntEnemy].MoveType == ENEMY_MOVETYPE_TO_PLAYER)
				{
					g_aEnemy[nCntEnemy].MoveType = ENEMY_MOVETYPE_ATTACK;
				}
			}

			//プレイヤーの弾が当たった時の処理
			int nBulletType = CollisionBullet(&g_aEnemy[nCntEnemy].pos, g_aEnemy[nCntEnemy].fWidth);
			if (nBulletType == 1)
			{
				g_aEnemy[nCntEnemy].nLife--;
				SetAddEvolutionGauge(1.0f);
			}
			else if (nBulletType == 2)
			{
				g_aEnemy[nCntEnemy].nLife--;
				SetAddEvolutionGauge(1.0f);
			}
			else if (nBulletType == 3)
			{
				g_aEnemy[nCntEnemy].nLife -= 5;
				SetAddEvolutionGauge(5.0f);
			}

			//プレイヤーの剣との当たり判定
			if (g_aEnemy[nCntEnemy].bDamage == false && pPlayer->bSlash == true)
			{
				if (CollisionSword(&g_aEnemy[nCntEnemy].pos, g_aEnemy[nCntEnemy].fWidth) == true)
				{
					if (pPlayer->nType == PLAYERTYPE_SPEED)
					{
						PlaySound(SOUND_LABEL_HIT);
						g_aEnemy[nCntEnemy].nLife -= 3;	

						SetScore(300);
					}
					else if (pPlayer->nType == PLAYERTYPE_NOMAL)
					{
						PlaySound(SOUND_LABEL_HIT);
						g_aEnemy[nCntEnemy].nLife -= 3;
						SetAddEvolutionGauge(3.0f);
						SetScore(300);
					}
					else if (pPlayer->nType == PLAYERTYPE_POWER)
					{
						PlaySound(SOUND_LABEL_HIT);
						g_aEnemy[nCntEnemy].nLife -= 6;
						SetScore(600);
					}

					g_aEnemy[nCntEnemy].bSlash = false;
					g_aEnemy[nCntEnemy].MoveType = ENEMY_MOVETYPE_DAMAGE;
					g_aEnemy[nCntEnemy].nKey = 0;
					g_aEnemy[nCntEnemy].fCounterMotion = 0.0f;
					g_aEnemy[nCntEnemy].bDamage = true;
				}
			}

			if (g_aEnemy[nCntEnemy].nLife <= 0)
			{
				g_aEnemy[nCntEnemy].nLife = 0;
				g_aEnemy[nCntEnemy].bUse = false;
				SetScore(3000);
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
				if (pCamera->nEnemyNumber == nCntEnemy && pCamera->nWhoRockOn == 1)
				{
					pCamera->bRockOn = false;
				}
			}

			if (pPlayer->bSlash == false)
			{
				g_aEnemy[nCntEnemy].bDamage = false;
			}

			g_aEnemy[nCntEnemy].fSwordCollZ = g_aEnemy[nCntEnemy].pos.z + (cosf(g_aEnemy[nCntEnemy].rot.y - D3DX_PI) * ENEMY_SWORD_COLLISION_DEPTH);
			g_aEnemy[nCntEnemy].fSwordCollX = g_aEnemy[nCntEnemy].pos.x + (sinf(g_aEnemy[nCntEnemy].rot.y - D3DX_PI) * ENEMY_SWORD_COLLISION_DEPTH);
			
			
			if (g_aEnemy[nCntEnemy].bSlash == false)
			{
				g_aEnemy[nCntEnemy].bPlayerDamage = false;
			}

			
			//影の設定
			SetPositionShadow(g_aEnemy[nCntEnemy].nIdx, g_aEnemy[nCntEnemy].pos, g_aEnemy[nCntEnemy].bUse);
			//ライフゲージの設定
			SetPositionEnemyLife(g_aEnemy[nCntEnemy].nIdxLife, D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + 150.0f, g_aEnemy[nCntEnemy].pos.z),
								g_aEnemy[nCntEnemy].bUse, MAX_ENEMY_LIFE, g_aEnemy[nCntEnemy].nLife, 50.0f);
			

			//動きの処理
			MoveTypeEnemy(nCntEnemy);
			//=======================================================================
			//モーション
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
			

			//回転の慣性
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

			//ロックオン処理
			if (pCamera->bRockOn == true && pCamera->nEnemyNumber == nCntEnemy && pCamera->nWhoRockOn == 1)
			{
				SetBillboard(g_aEnemy[nCntEnemy].pos, 100.0f, 100.0f);
				SetPositionBillboard(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + 60.0f, g_aEnemy[nCntEnemy].pos.z), g_aEnemy[nCntEnemy].bUse);
			}

			//モデルとの当たり判定
			CollisionModelTxt(&g_aEnemy[nCntEnemy].move, &g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posOld, g_aEnemy[nCntEnemy].fWidth);
		}	
	}
}

//=======================================================================
//描画処理
//=======================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する

	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].mtxWorld);		//プレイヤーのワールドマトリックスの初期化

														//プレイヤーの向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCntEnemy].rot.y, g_aEnemy[nCntEnemy].rot.x, g_aEnemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxRot);

			//プレイヤーの位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y, g_aEnemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].mtxWorld);

			//現在のマテリアルを保存
			pDevice->GetMaterial(&matDef);

			for (int nCntModel = 0; nCntModel < g_aEnemy[nCntEnemy].nNumModel; nCntModel++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;		//計算用マトリックス
				D3DXMATRIX mtxParent;						//親のマトリックス

				D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld);		//各パーツのワールドマトリックスの初期化

																				//各パーツの向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aEnemy[nCntEnemy].aModel[nCntModel].rot.y, g_aEnemy[nCntEnemy].aModel[nCntModel].rot.x, g_aEnemy[nCntEnemy].aModel[nCntModel].rot.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxRotModel);

				//各パーツの位置を反映
				D3DXMatrixTranslation(&mtxTransModel, g_aEnemy[nCntEnemy].aModel[nCntModel].pos.x, g_aEnemy[nCntEnemy].aModel[nCntModel].pos.y, g_aEnemy[nCntEnemy].aModel[nCntModel].pos.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxTransModel);

				//各パーツの親のマトリックスの設定
				if (g_aEnemy[nCntEnemy].aModel[nCntModel].nIdxModelParent != -1)
				{
					mtxParent = g_aEnemy[nCntEnemy].aModel[g_aEnemy[nCntEnemy].aModel[nCntModel].nIdxModelParent].mtxWorld;
				}
				else
				{
					mtxParent = g_aEnemy[nCntEnemy].mtxWorld;
				}

				//算出した各パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxParent);

				//各パーツのワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld);

				//マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_aEnemy[nCntEnemy].aModel[nCntModel].pBuffMat->GetBufferPointer();
				for (int nCntMat = 0; nCntMat < (int)g_aEnemy[nCntEnemy].aModel[nCntModel].nNumMat; nCntMat++)
				{
					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//テクスチャの設定
					pDevice->SetTexture(0, NULL);
					//pDevice->SetTexture(0, g_apTextureEnemy[nCntMat]);

					//モデル(パーツ)の描画
					g_aEnemy[nCntEnemy].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
				}

				//保存していたマテリアルを戻す
				pDevice->SetMaterial(&matDef);
			}

			//剣の設定
			D3DXMATRIX mtxParent;						//親のマトリックス
			D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].sword.mtxWorld);		//プレイヤーのワールドマトリックスの初期化

														//プレイヤーの向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCntEnemy].sword.rot.y, g_aEnemy[nCntEnemy].sword.rot.x, g_aEnemy[nCntEnemy].sword.rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].sword.mtxWorld, &g_aEnemy[nCntEnemy].sword.mtxWorld, &mtxRot);

			//プレイヤーの位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCntEnemy].sword.pos.x, g_aEnemy[nCntEnemy].sword.pos.y, g_aEnemy[nCntEnemy].sword.pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].sword.mtxWorld, &g_aEnemy[nCntEnemy].sword.mtxWorld, &mtxTrans);

			mtxParent = g_aEnemy[nCntEnemy].aModel[3].mtxWorld;

			//算出した各パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].sword.mtxWorld, &g_aEnemy[nCntEnemy].sword.mtxWorld, &mtxParent);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].sword.mtxWorld);
		}
	}
}

//=======================================================================
//モーション処理
//=======================================================================
void MotionEnemy(int nCntEnemy)
{
	//プレイヤーの取得
	PLAYER *pPlayer = GetPlayer();

	D3DXVECTOR3 posAsk[MAX_ENEMY_MODEL];		//求めたい値
	D3DXVECTOR3 rotAsk[MAX_ENEMY_MODEL];		//求めたい値
	D3DXVECTOR3 posDiffer[MAX_ENEMY_MODEL];	//差分
	D3DXVECTOR3 rotDiffer[MAX_ENEMY_MODEL];	//差分

	for (int nCntModel = 0; nCntModel < g_aEnemy[nCntEnemy].nNumModel - 1; nCntModel++)
	{
		if (g_aEnemy[nCntEnemy].nKey < g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].nNumKey - 1)//キーの最大数-1
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
		else if (g_aEnemy[nCntEnemy].nKey >= g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].nNumKey - 1)//キーの最大数-1
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
		PlaySound(SOUND_LABEL_SLASH_000);
	}
	if (g_aEnemy[nCntEnemy].MotionType == ENEMY_MOTIONTYPE_PUNCH && g_aEnemy[nCntEnemy].bSlash == true && g_aEnemy[nCntEnemy].nKey == 2 && g_aEnemy[nCntEnemy].fCounterMotion >= 5)
	{
		PlaySound(SOUND_LABEL_SLASH_000);
		g_aEnemy[nCntEnemy].bSlash = false;
	}

	g_aEnemy[nCntEnemy].fCounterMotion += 1.0f;
	if (g_aEnemy[nCntEnemy].fCounterMotion >= g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].aKeyInfo[g_aEnemy[nCntEnemy].nKey].nFrame)
	{
		if (g_aEnemy[nCntEnemy].nKey < g_aEnemy[nCntEnemy].aMotionInfo[g_aEnemy[nCntEnemy].MotionType].nNumKey - 1)//キーの最大数-1
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
//敵の動き方の処理
//=======================================================================
void MoveTypeEnemy(int nCntEnemy)
{
	//プレイヤーの取得
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
	//敵の移動制限
	//-------------------------------------------------
	if (g_aEnemy[nCntEnemy].pos.x >= PLAYER_LIMIT)
	{
		g_aEnemy[nCntEnemy].pos.x = PLAYER_LIMIT;
	}
	else if (g_aEnemy[nCntEnemy].pos.x <= -PLAYER_LIMIT)
	{
		g_aEnemy[nCntEnemy].pos.x = -PLAYER_LIMIT;
	}
	if (g_aEnemy[nCntEnemy].pos.z >= PLAYER_LIMIT)
	{
		g_aEnemy[nCntEnemy].pos.z = PLAYER_LIMIT;
	}
	else if (g_aEnemy[nCntEnemy].pos.z <= -PLAYER_LIMIT)
	{
		g_aEnemy[nCntEnemy].pos.z = -PLAYER_LIMIT;
	}
}


//=======================================================================
//設定処理
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
			g_aEnemy[nCntEnemy].nIdxLife = SetEnemyLife(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + 150.0f, g_aEnemy[nCntEnemy].pos.z), 50.0f, 5.0f);
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
//敵との当たり判定
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
//剣との当たり判定
//=======================================================================
bool CollisionEnemySword(D3DXVECTOR3 *pPos, float fWidth)
{
	ENEMY *pEnemy = GetEnemy();
	bool bDamage = false;			//当たっているかどうか

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (g_aEnemy[nCntEnemy].sword.mtxWorld._41 >= pPos->x - fWidth / 2.0f && g_aEnemy[nCntEnemy].sword.mtxWorld._41 <= pPos->x + fWidth / 2.0f &&
			g_aEnemy[nCntEnemy].sword.mtxWorld._43 >= pPos->z - fWidth / 2.0f && g_aEnemy[nCntEnemy].sword.mtxWorld._43 <= pPos->z + fWidth / 2.0f)
		{
			bDamage = true;
			g_nAttackEnemy = nCntEnemy;
		}
	}
	return bDamage;
}



//=======================================================================
//取得処理
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