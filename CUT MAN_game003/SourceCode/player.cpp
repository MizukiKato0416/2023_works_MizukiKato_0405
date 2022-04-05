//=======================================================================
//プレイヤーに関する処理
//Aouthor: 加藤　瑞葵
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
#include "model.h"
#include "fade.h"
#include "enemy.h"
#include "pad.h"
#include "life.h"
#include "ui.h"
#include "sound.h"
#include "effect.h"
#include "mask.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================
PLAYER g_Player;				//プレイヤーの構造体
int g_nNumPlayer;				//影
float g_fNumTurnPlayer;			//目的のrot
float g_fNumPlayer;				//目的と現在のrotの差
bool g_bTurnPlayer;				//回転の慣性
D3DXVECTOR3 g_SwordPos;			//剣の位置
float g_fSwordVecAx[4];			//剣の当たり判定に必要なベクトル
float g_fSwordVecAz[4];			//剣の当たり判定に必要なベクトル
float g_fAdVec[4];			//剣の当たり判定に必要なベクトル
float g_fSwordVecBx;			//剣の当たり判定に必要なベクトル
float g_fSwordVecBz;			//剣の当たり判定に必要なベクトル

//=======================================================================
//初期化処理
//=======================================================================
void InitPlayer(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//初期化
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
		g_Player.pos = D3DXVECTOR3(600.0f, 0.0f, 1000.0f);
		g_Player.rot = D3DXVECTOR3(0.0f, D3DX_PI / 2.0f, 0.0f);
	}
	
	
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.nNumModel = MAX_PLAYER_MODEL;
	g_Player.nNumMotion = 9;
	g_Player.bLoopMotion = false;
	g_Player.nNumKey = 0;
	g_Player.nKeyOld = 0;
	g_Player.nKey = 0;
	g_Player.nEffect = 0;
	g_Player.nTitle = 0;
	g_Player.nLife = MAX_PLAYER_LIFE;
	g_Player.fCounterMotion = 0.0f;
	g_Player.bJump = false;
	g_Player.bSlash = false;
	g_Player.bUse = true;
	g_Player.bDamage = false;
	g_Player.bDifence = false;
	g_Player.fWidth = 50.0f;
	g_Player.fHeight = 40.0f;
	g_Player.fDepth = 50.0f;
	g_Player.fNumTurnPlayer = 0.0f;
	g_Player.bTurnPlayer = false;
	g_nNumPlayer = 0;
	g_fNumTurnPlayer = 0.0f;
	g_fNumPlayer = 0.0f;
	g_bTurnPlayer = false;
	g_SwordPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_fSwordVecAx[0] = 0.0f;
	g_fSwordVecAz[0] = 0.0f;
	g_fSwordVecAx[1] = 0.0f;
	g_fSwordVecAz[1] = 0.0f;
	g_fSwordVecAx[2] = 0.0f;
	g_fSwordVecAz[2] = 0.0f;
	g_fSwordVecAx[3] = 0.0f;
	g_fSwordVecAz[3] = 0.0f;
	g_fAdVec[0] = 0.0f;
	g_fAdVec[1] = 0.0f;
	g_fAdVec[2] = 0.0f;
	g_fAdVec[3] = 0.0f;
	g_fSwordVecBx = 0.0f;
	g_fSwordVecBz = 0.0f;

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		g_Player.aModel[nCntModel].vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
		g_Player.aModel[nCntModel].vtxMin =D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_Player.aModel[nCntModel].fDepth = 0.0f;
		g_Player.aModel[nCntModel].fHeight = 0.0f;
		g_Player.aModel[nCntModel].fWidth = 0.0f;
	}


	//g_Player.MotionType = MOTIONTYPE_NEUTRAL;


	//Xファイル読み込み
	D3DXLoadMeshFromX("data/MODEL/player003/00_original_body_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, 
						&g_Player.aModel[0].pBuffMat,NULL, &g_Player.aModel[0].nNumMat, &g_Player.aModel[0].pMesh);
	D3DXLoadMeshFromX("data/MODEL/player003/01_original_head_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, 
						&g_Player.aModel[1].pBuffMat,NULL, &g_Player.aModel[1].nNumMat, &g_Player.aModel[1].pMesh);
	D3DXLoadMeshFromX("data/MODEL/player003/02_original_armR_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, 
						&g_Player.aModel[2].pBuffMat,NULL, &g_Player.aModel[2].nNumMat, &g_Player.aModel[2].pMesh);
	D3DXLoadMeshFromX("data/MODEL/player003/03_original_frontarmR_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, 
						&g_Player.aModel[3].pBuffMat,NULL, &g_Player.aModel[3].nNumMat, &g_Player.aModel[3].pMesh);
	D3DXLoadMeshFromX("data/MODEL/player003/04_original_handR_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, 
						&g_Player.aModel[4].pBuffMat,NULL, &g_Player.aModel[4].nNumMat, &g_Player.aModel[4].pMesh);
	D3DXLoadMeshFromX("data/MODEL/player003/05_original_armL_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, 
						&g_Player.aModel[5].pBuffMat,NULL, &g_Player.aModel[5].nNumMat, &g_Player.aModel[5].pMesh);
	D3DXLoadMeshFromX("data/MODEL/player003/06_original_frontarmL_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, 
						&g_Player.aModel[6].pBuffMat,NULL, &g_Player.aModel[6].nNumMat, &g_Player.aModel[6].pMesh);
	D3DXLoadMeshFromX("data/MODEL/player003/07_original_handL_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, 
						&g_Player.aModel[7].pBuffMat,NULL, &g_Player.aModel[7].nNumMat, &g_Player.aModel[7].pMesh);
	D3DXLoadMeshFromX("data/MODEL/player003/08_original_legR_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, 
						&g_Player.aModel[8].pBuffMat,NULL, &g_Player.aModel[8].nNumMat, &g_Player.aModel[8].pMesh);
	D3DXLoadMeshFromX("data/MODEL/player003/09_original_frontlegR_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, 
						&g_Player.aModel[9].pBuffMat,NULL, &g_Player.aModel[9].nNumMat, &g_Player.aModel[9].pMesh);
	D3DXLoadMeshFromX("data/MODEL/player003/10_original_footR_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, 
						&g_Player.aModel[10].pBuffMat,NULL, &g_Player.aModel[10].nNumMat, &g_Player.aModel[10].pMesh);
	D3DXLoadMeshFromX("data/MODEL/player003/11_original_legL_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, 
						&g_Player.aModel[11].pBuffMat,NULL, &g_Player.aModel[11].nNumMat, &g_Player.aModel[11].pMesh);
	D3DXLoadMeshFromX("data/MODEL/player003/12_original_frontlegL_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, 
						&g_Player.aModel[12].pBuffMat,NULL, &g_Player.aModel[12].nNumMat, &g_Player.aModel[12].pMesh);
	D3DXLoadMeshFromX("data/MODEL/player003/13_original_footL_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, 
						&g_Player.aModel[13].pBuffMat,NULL, &g_Player.aModel[13].nNumMat, &g_Player.aModel[13].pMesh);


	//テクスチャデータの取得
	D3DXMATERIAL *pMat;		//マテリアルへのポインタ

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		//マテリアル情報に対するポインタを取得
		pMat = (D3DXMATERIAL *)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_Player.aModel[nCntModel].pTexture[nCntMat]);
			}
		}

		//textファイル読み込み
		FILE *pfile = fopen("data/MOTION/player001motion.txt", "r");

		char index[] = "INDEX";
		char string[255][255];
		char search[] = "KEYSET";
		char EndKeySet[] = "END_KEYSET";
		char LoopSearch[] = "LOOP";
		char KeySearch[] = "KEY";
		char MotionSearch[] = "MOTIONSET";
		char EndMotionSet[] = "END_MOTIONSET";

		//各パーツの階層構造を設定
		for (int nCntRead = 0; nCntRead < g_Player.nNumModel; nCntRead++)
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

		//モーションの読み込み
		for (int nCntMotion = 0; nCntMotion < MOTION_MAX; nCntMotion++)
		{
			//ループ情報の取得
			//キー数の取得
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
				//フレーム数の取得
				while (fgets(string[0], 255, pfile) != NULL)
				{
					if (strstr(string[0], search))
					{
						fscanf(pfile, "%s%s%d", string[0], string[0], &g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
						//g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame = g_Player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame * (144 / 60);
						break;
					}
				}

				//位置、回転情報の取得
				for (int nCntRead = 0; nCntRead < g_Player.nNumModel; nCntRead++)
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


		//親子関係による位置ずれの修正
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

	//頂点情報の取得
	int nNumVtx;		//頂点数
	DWORD sizeFVF;		//頂点フォーマットのサイズ
	BYTE *pVtxBuff;		//頂点バッファへのポインタ

						//頂点数を取得
	nNumVtx = g_Player.aModel[4].pMesh->GetNumVertices();
	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[4].pMesh->GetFVF());

	//頂点バッファをロック
	g_Player.aModel[4].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//頂点座標の代入

														//全ての頂点を比較して最大値と最小手を抜き出す
														//最大値
		if (vtx.x >= g_Player.aModel[4].vtxMax.x)
		{
			g_Player.aModel[4].vtxMax.x = vtx.x;
		}
		if (vtx.y >= g_Player.aModel[4].vtxMax.y)
		{
			g_Player.aModel[4].vtxMax.y = vtx.y;
		}
		if (vtx.z >= g_Player.aModel[4].vtxMax.z)
		{
			g_Player.aModel[4].vtxMax.z = vtx.z;
		}
		//最小値
		if (vtx.x <= g_Player.aModel[4].vtxMin.x)
		{
			g_Player.aModel[4].vtxMin.x = vtx.x;
		}
		if (vtx.y <= g_Player.aModel[4].vtxMin.y)
		{
			g_Player.aModel[4].vtxMin.y = vtx.y;
		}
		if (vtx.z <= g_Player.aModel[4].vtxMin.z)
		{
			g_Player.aModel[4].vtxMin.z = vtx.z;
		}

		pVtxBuff += sizeFVF;		//頂点フォーマットのサイズ分ポインタを進める
	}
	//頂点バッファをアンロック
	g_Player.aModel[4].pMesh->UnlockVertexBuffer();

	g_Player.MotionType = MOTIONTYPE_NEUTRAL;
	g_Player.MotionTypeNext = MOTIONTYPE_NEUTRAL;
	g_Player.MotionTypeOld = MOTIONTYPE_NEUTRAL;
	g_Player.nIdx = SetShadow(g_Player.pos, g_Player.fWidth, g_Player.fDepth);
}

//=======================================================================
//終了処理
//=======================================================================
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		//メッシュの破棄
		if (g_Player.aModel[nCntModel].pMesh != NULL)
		{
			g_Player.aModel[nCntModel].pMesh->Release();
			g_Player.aModel[nCntModel].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_Player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_Player.aModel[nCntModel].pBuffMat->Release();
			g_Player.aModel[nCntModel].pBuffMat = NULL;
		}

		//テクスチャの破棄
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
//更新処理
//=======================================================================
void UpdatePlayer(void)
{
	ENEMY *pEnemy = GetEnemy();
	Life *pLife = GetLife();

	g_Player.MotionTypeOld = g_Player.MotionType;
	g_Player.posOld = g_Player.pos;
	g_Player.move.y -= GRAVITY;		//重力
	
	if (g_Player.bUse == true)
	{
		if (g_Player.move.x == 0.0f && g_Player.move.z == 0.0f && g_Player.MotionType != MOTIONTYPE_PUNCH &&
			g_Player.MotionType != MOTIONTYPE_SLASH04 && g_Player.MotionType != MOTIONTYPE_SLASH && g_Player.MotionType != MOTIONTYPE_SLASH03)
		{
			g_Player.MotionType = MOTIONTYPE_NEUTRAL;
		}
		else if ((g_Player.move.x != 0.0f || g_Player.move.z != 0.0f) && g_Player.MotionType != MOTIONTYPE_SLASH04 && g_Player.MotionType != MOTIONTYPE_PUNCH &&
			g_Player.MotionType != MOTIONTYPE_SLASH && g_Player.MotionType != MOTIONTYPE_SLASH03)
		{
			g_Player.MotionType = MOTIONTYPE_MOVE;
		}

		//カメラ情報を取得
		Camera *pCamera = GetCamera();

		//モデルの移動
		g_Player.pos += g_Player.move;

		if (GetMode() == MODE_STAGE1)
		{
			//=======================================================================
			//キーの入力処理
			//=======================================================================

			if (g_Player.MotionType != MOTIONTYPE_PUNCH && g_Player.MotionType != MOTIONTYPE_SLASH && g_Player.MotionType != MOTIONTYPE_SLASH03 && g_Player.MotionType != MOTIONTYPE_SLASH04)
			{
				if (GetLeftStick(STICKTYPE_UP) == true)
				{
					if (GetLeftStick(STICKTYPE_RIGHT) == true)
					{
						g_Player.move.x = +cosf(pCamera->rot.y - D3DX_PI / 4.0f) * PLAYER_SPEED;
						g_Player.move.z = -sinf(pCamera->rot.y - D3DX_PI / 4.0f) * PLAYER_SPEED;

						pCamera->posV.x = pCamera->posV.x + cosf(pCamera->rot.y - D3DX_PI / 4.0f) * CAMERA_VR_SPEED;
						pCamera->posV.z = pCamera->posV.z - sinf(pCamera->rot.y - D3DX_PI / 4.0f) * CAMERA_VR_SPEED;

						g_Player.fNumTurnPlayer = pCamera->rot.y + D3DX_PI / 4.0f;
						g_Player.bTurnPlayer = true;
					}
					else if (GetLeftStick(STICKTYPE_LEFT) == true)
					{
						g_Player.move.x = -cosf(pCamera->rot.y + D3DX_PI / 4.0f) * PLAYER_SPEED;
						g_Player.move.z = +sinf(pCamera->rot.y + D3DX_PI / 4.0f) * PLAYER_SPEED;

						pCamera->posV.x = pCamera->posV.x - cosf(pCamera->rot.y + D3DX_PI / 4.0f) * CAMERA_VR_SPEED;
						pCamera->posV.z = pCamera->posV.z + sinf(pCamera->rot.y + D3DX_PI / 4.0f) * CAMERA_VR_SPEED;

						g_Player.fNumTurnPlayer = pCamera->rot.y - D3DX_PI / 4.0f;
						g_Player.bTurnPlayer = true;
					}
					else
					{
						g_Player.move.z = +cosf(pCamera->rot.y) * PLAYER_SPEED;
						g_Player.move.x = +sinf(pCamera->rot.y) * PLAYER_SPEED;

						pCamera->posV.z = pCamera->posV.z + cosf(pCamera->rot.y) * CAMERA_VR_SPEED;
						pCamera->posV.x = pCamera->posV.x + sinf(pCamera->rot.y) * CAMERA_VR_SPEED;

						g_Player.fNumTurnPlayer = pCamera->rot.y;

						g_Player.bTurnPlayer = true;

					}

				}
				else if (GetLeftStick(STICKTYPE_DOWN) == true)
				{
					if (GetLeftStick(STICKTYPE_RIGHT) == true)
					{
						g_Player.move.x = +cosf(pCamera->rot.y + D3DX_PI / 4.0f) * PLAYER_SPEED;
						g_Player.move.z = -sinf(pCamera->rot.y + D3DX_PI / 4.0f) * PLAYER_SPEED;

						pCamera->posV.x = pCamera->posV.x + cosf(pCamera->rot.y + D3DX_PI / 4.0f) * CAMERA_VR_SPEED;
						pCamera->posV.z = pCamera->posV.z - sinf(pCamera->rot.y + D3DX_PI / 4.0f) * CAMERA_VR_SPEED;

						g_Player.fNumTurnPlayer = pCamera->rot.y + D3DX_PI / 1.5f;
						g_Player.bTurnPlayer = true;
					}
					else if (GetLeftStick(STICKTYPE_LEFT) == true)
					{
						g_Player.move.x = -cosf(pCamera->rot.y - D3DX_PI / 4.0f) * PLAYER_SPEED;
						g_Player.move.z = +sinf(pCamera->rot.y - D3DX_PI / 4.0f) * PLAYER_SPEED;

						pCamera->posV.x = pCamera->posV.x - cosf(pCamera->rot.y - D3DX_PI / 4.0f) * CAMERA_VR_SPEED;
						pCamera->posV.z = pCamera->posV.z + sinf(pCamera->rot.y - D3DX_PI / 4.0f) * CAMERA_VR_SPEED;

						g_Player.fNumTurnPlayer = pCamera->rot.y - (D3DX_PI / 4.0f) * 3.0f;
						g_Player.bTurnPlayer = true;
					}
					else
					{
						g_Player.fNumTurnPlayer = pCamera->rot.y + D3DX_PI;

						g_Player.move.z = -cosf(pCamera->rot.y) * PLAYER_SPEED;
						g_Player.move.x = -sinf(pCamera->rot.y) * PLAYER_SPEED;

						pCamera->posV.z = pCamera->posV.z - cosf(pCamera->rot.y) * CAMERA_VR_SPEED;
						pCamera->posV.x = pCamera->posV.x - sinf(pCamera->rot.y) * CAMERA_VR_SPEED;

						g_Player.bTurnPlayer = true;
					}
				}
				else if (GetLeftStick(STICKTYPE_RIGHT) == true)
				{
					g_Player.move.x = +cosf(pCamera->rot.y) * PLAYER_SPEED;
					g_Player.move.z = -sinf(pCamera->rot.y) * PLAYER_SPEED;

					pCamera->posV.x = pCamera->posV.x + cosf(pCamera->rot.y) * CAMERA_VR_SPEED;
					pCamera->posV.z = pCamera->posV.z - sinf(pCamera->rot.y) * CAMERA_VR_SPEED;

					g_Player.fNumTurnPlayer = pCamera->rot.y + D3DX_PI / 2.0f;
					g_Player.bTurnPlayer = true;
				}
				else if (GetLeftStick(STICKTYPE_LEFT) == true)
				{
					g_Player.move.x = -cosf(pCamera->rot.y) * PLAYER_SPEED;
					g_Player.move.z = +sinf(pCamera->rot.y) * PLAYER_SPEED;

					pCamera->posV.x = pCamera->posV.x - cosf(pCamera->rot.y) * CAMERA_VR_SPEED;
					pCamera->posV.z = pCamera->posV.z + sinf(pCamera->rot.y) * CAMERA_VR_SPEED;

					g_Player.fNumTurnPlayer = pCamera->rot.y - D3DX_PI / 2.0f;
					g_Player.bTurnPlayer = true;
				}
			}
		}




		if (GetLeftStick(STICKTYPE_RIGHT) == false && GetLeftStick(STICKTYPE_LEFT) == false &&
			GetLeftStick(STICKTYPE_UP) == false && GetLeftStick(STICKTYPE_DOWN) == false)
		{
			g_Player.move.x = 0.0f;
			g_Player.move.z = 0.0f;
		}


		//回転の慣性
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
				g_fNumPlayer = (-D3DX_PI - g_Player.rot.y) + -(D3DX_PI - g_Player.fNumTurnPlayer);
			}
			else if (g_Player.rot.y >= D3DX_PI / 2.0f && g_Player.rot.y - g_Player.fNumTurnPlayer > D3DX_PI)
			{
				g_fNumPlayer = (D3DX_PI - g_Player.rot.y) - (-D3DX_PI - g_Player.fNumTurnPlayer);
			}
			else
			{
				g_fNumPlayer = (g_Player.fNumTurnPlayer - g_Player.rot.y);
			}


			g_Player.rot.y += g_fNumPlayer * 0.1f;
			if (g_Player.rot.y - g_Player.fNumTurnPlayer < 0.001 && g_Player.rot.y - g_Player.fNumTurnPlayer > -0.001)
			{
				g_Player.bTurnPlayer = false;

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





		//弾の発射処理
		/*if (GetKeyboardPress(DIK_P) == true)
		{
		SetBullet(g_Player.pos, D3DXVECTOR3(sinf(g_Player.rot.y) * 40.0f, 0.0f, cosf(g_Player.rot.y) * 40.0f), 50.0f, 50.0f);
		}*/



		//-------------------------------------------------
		//プレイヤーの移動制限
		//-------------------------------------------------
		if (g_Player.pos.x >= 1200.0f)
		{
			g_Player.pos.x = 1200.0f;
		}
		else if (g_Player.pos.x <= -1200.0f)
		{
			g_Player.pos.x = -1200.0f;
		}
		if (g_Player.pos.z >= 1200.0f)
		{
			g_Player.pos.z = 1200.0f;
		}
		else if (g_Player.pos.z <= -1200.0f)
		{
			g_Player.pos.z = -1200.0f;
		}
		if (g_Player.pos.y <= 0.0f)
		{
			g_Player.pos.y = 0.0f;
			g_Player.bJump = false;
		}

		//モデルとの当たり判定
		if (CollisionModel(&g_Player.pos, &g_Player.posOld, &g_Player.move, g_Player.fWidth, g_Player.fHeight, g_Player.fDepth) == true)
		{
			g_Player.bJump = false;
		}
		//敵との当たり判定
		CollisionEnemy(&g_Player.pos, &g_Player.posOld, &g_Player.move, g_Player.fWidth, g_Player.fHeight, g_Player.fDepth);




		if (GetMode() == MODE_STAGE1)
		{
			//ジャンプ
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

		//ガード
		if (GetTriggerPress(TRIGGERTYPE_LEFT) == true && g_Player.bSlash == false && g_Player.MotionType != MOTIONTYPE_SLASH03)
		{
			g_Player.MotionType = MOTIONTYPE_DIFENCE;
		}

		//斬撃
		if (GetButtonTrigger(XINPUT_GAMEPAD_B) == true && g_Player.MotionType != MOTIONTYPE_DIFENCE)
		{
			if (g_Player.bSlash == false && g_Player.MotionType != MOTIONTYPE_SLASH && g_Player.MotionType != MOTIONTYPE_SLASH03)
			{
				g_Player.MotionType = MOTIONTYPE_PUNCH;
				g_Player.bSlash = true;
				PlaySound(SOUND_LABEL_SLASH_001);
			}
			else
			{
				if (g_Player.MotionType == MOTIONTYPE_PUNCH)
				{
					g_Player.MotionTypeNext = MOTIONTYPE_SLASH;

				}
				else if (g_Player.MotionType == MOTIONTYPE_SLASH)
				{
					g_Player.MotionTypeNext = MOTIONTYPE_PUNCH;
				}
			}
		}
		if (GetButtonTrigger(XINPUT_GAMEPAD_Y) == true && g_Player.MotionType != MOTIONTYPE_DIFENCE && g_Player.MotionType != MOTIONTYPE_PUNCH &&
			g_Player.MotionType != MOTIONTYPE_SLASH04 && g_Player.MotionType != MOTIONTYPE_SLASH)
		{
			g_Player.MotionType = MOTIONTYPE_SLASH03;
			PlaySound(SOUND_LABEL_SLASH_003);
			g_Player.MotionTypeNext = MOTIONTYPE_NEUTRAL;
		}
		if (GetButtonTrigger(XINPUT_GAMEPAD_X) == true && g_Player.MotionType != MOTIONTYPE_DIFENCE&& g_Player.MotionType != MOTIONTYPE_PUNCH &&
			g_Player.MotionType != MOTIONTYPE_SLASH03 && g_Player.MotionType != MOTIONTYPE_SLASH)
		{
			g_Player.MotionType = MOTIONTYPE_SLASH04;
			g_Player.MotionTypeNext = MOTIONTYPE_NEUTRAL;
			g_Player.bSlash = true;
			PlaySound(SOUND_LABEL_SLASH_005);
		}


		if (g_Player.MotionTypeOld == MOTIONTYPE_DIFENCE && g_Player.MotionType != MOTIONTYPE_DIFENCE)
		{
			g_Player.nKey = 0;
			g_Player.fCounterMotion = 0.0f;
			g_Player.bSlash = false;
		}
	}

	//=======================================================================
	//モーション
	//=======================================================================
	if (g_Player.MotionType != g_Player.MotionTypeOld)
	{
		g_Player.nKey = 0;
		g_Player.fCounterMotion = 0.0f;
	}
	MotionPlayer();


	if (g_Player.MotionType == MOTIONTYPE_PUNCH || g_Player.MotionType == MOTIONTYPE_SLASH || g_Player.MotionType == MOTIONTYPE_SLASH03 ||
		g_Player.MotionType == MOTIONTYPE_DIFENCE || g_Player.MotionType == MOTIONTYPE_SLASH04)
	{
		g_Player.move.x = 0.0f;
		g_Player.move.z = 0.0f;
	}


	//影の設定
	SetPositionShadow(g_Player.nIdx, g_Player.pos, g_Player.bUse);
	

	if (g_Player.bUse == false)
	{
		g_Player.nTitle++;
		g_Player.nEffect++;
		SetMask(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2.0f, 0.0f), MASKTYPE_GAMEOVER, SCREEN_WIDTH, SCREEN_HEIGHT);
		if (g_Player.nEffect >= 10)
		{
			g_Player.nEffect = 0;
			for (int nCnt = 0; nCnt < 16; nCnt++)
			{
				SetEffect(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 40.0f, g_Player.pos.z),
					D3DXVECTOR3(cosf(D3DX_PI * 2.0f / 16.0f * nCnt) * 0.8f, 2.5f, sinf(D3DX_PI * 2.0f / 16.0f * nCnt) * 0.8f),
					10.0f, 10.0f, D3DXCOLOR(255, 0, 0, 255), 60, EFFEFCT_MOVETYPE_ENEMY_DEATH);
			}
		}
		if (g_Player.nTitle >= 300 && GetFade() == FADE_NONE)
		{
			g_Player.nTitle = 0;
			SetFade(MODE_TITLE);
		}
	}
}

//=======================================================================
//描画処理
//=======================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する

	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	D3DXMatrixIdentity(&g_Player.mtxWorld);		//プレイヤーのワールドマトリックスの初期化

	//プレイヤーの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	//プレイヤーの位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	//現在のマテリアルを保存
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;		//計算用マトリックス
		D3DXMATRIX mtxParent;						//親のマトリックス

		D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);		//各パーツのワールドマトリックスの初期化

		//各パーツの向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		//各パーツの位置を反映
		D3DXMatrixTranslation(&mtxTransModel, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		//各パーツの親のマトリックスの設定
		if (g_Player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_Player.mtxWorld;
		}

		//算出した各パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxParent);

		//各パーツのワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorld);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nNumMat; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, NULL);
			//pDevice->SetTexture(0, g_apTexturePlayer[nCntMat]);

			//モデル(パーツ)の描画
			g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
	}
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=======================================================================
//モーション処理
//=======================================================================
void MotionPlayer(void)
{
	ENEMY *pEnemy = GetEnemy();
	ENEMY *pEnemy2 = GetAttackEnemy();

	D3DXVECTOR3 posAsk[MAX_PLAYER_MODEL];		//求めたい値
	D3DXVECTOR3 rotAsk[MAX_PLAYER_MODEL];		//求めたい値
	D3DXVECTOR3 posDiffer[MAX_PLAYER_MODEL];	//差分
	D3DXVECTOR3 rotDiffer[MAX_PLAYER_MODEL];	//差分

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		if (g_Player.nKey < g_Player.aMotionInfo[g_Player.MotionType].nNumKey - 1)//キーの最大数-1
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
		else if (g_Player.nKey >= g_Player.aMotionInfo[g_Player.MotionType].nNumKey - 1)//キーの最大数-1
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

	if ((g_Player.MotionType == MOTIONTYPE_SLASH && g_Player.bSlash == false))
	{
		g_Player.bSlash = true;
		PlaySound(SOUND_LABEL_SLASH_002);
	}
	if ((g_Player.MotionType == MOTIONTYPE_SLASH03 && g_Player.bSlash == false && g_Player.nKey == 2))
	{
		g_Player.bSlash = true;
	}
	if (g_Player.MotionType == MOTIONTYPE_SLASH04)
	{
		g_Player.rot.y += 1.0f;
	}

	g_Player.fCounterMotion += 1.0f;
	if (g_Player.fCounterMotion >= g_Player.aMotionInfo[g_Player.MotionType].aKeyInfo[g_Player.nKey].nFrame)
	{
		if (g_Player.nKey < g_Player.aMotionInfo[g_Player.MotionType].nNumKey - 1)//キーの最大数-1
		{
			g_Player.nKey++;
			g_Player.fCounterMotion = 0.0f;
		}
		else if (g_Player.nKey >= g_Player.aMotionInfo[g_Player.MotionType].nNumKey - 1)
		{
			if (g_Player.MotionType == MOTIONTYPE_DIFENCE)
			{
				g_Player.MotionType = MOTIONTYPE_DIFENCE;
				g_Player.nKey = 0;
				g_Player.fCounterMotion = 0.0f;
				//StopSound(SOUND_LABEL_SLASH_003);

			}
			else
			{
				g_Player.nKey = 0;
				g_Player.fCounterMotion = 0.0f;
				g_Player.bSlash = false;
				g_Player.MotionType = MOTIONTYPE_NEUTRAL;
			}

			if (g_Player.MotionTypeNext == MOTIONTYPE_SLASH)
			{
				g_Player.MotionType = MOTIONTYPE_SLASH;
				g_Player.MotionTypeNext = MOTIONTYPE_NEUTRAL;

			}
			else if (g_Player.MotionTypeNext == MOTIONTYPE_SLASH03)
			{
				g_Player.MotionType = MOTIONTYPE_SLASH03;
				PlaySound(SOUND_LABEL_SLASH_003);
				g_Player.MotionTypeNext = MOTIONTYPE_NEUTRAL;
			}
		}
	}
}

//=======================================================================
//プレイヤーとの当たり判定
//=======================================================================
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth)
{
	bool bColl = false;	//当たっているかどうか
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
//剣との当たり判定
//=======================================================================
bool CollisionSword(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth)
{
	PLAYER *pPlayer = GetPlayer();
	bool bDamage = false;			//当たっているかどうか

	//内積を求めるためのベクトル計算
	/*g_fSwordVecAx[0] = (pPlayer->pos.x - (cosf(pPlayer->rot.y) * SWORD_COLLISION_WIDTH / 2.0f)) -
						((pPlayer->pos.x - (cosf(pPlayer->rot.y) * SWORD_COLLISION_WIDTH / 2.0f)) + (sinf(pPlayer->rot.y) * SWORD_COLLISION_DEPTH));
	g_fSwordVecAx[1] = ((pPlayer->pos.x - (cosf(pPlayer->rot.y) * SWORD_COLLISION_WIDTH / 2.0f)) + (sinf(pPlayer->rot.y) * SWORD_COLLISION_DEPTH)) -
						((pPlayer->pos.x + (cosf(pPlayer->rot.y) * SWORD_COLLISION_WIDTH / 2.0f)) + (sinf(pPlayer->rot.y) * SWORD_COLLISION_DEPTH));
	g_fSwordVecAx[2] = ((pPlayer->pos.x + (cosf(pPlayer->rot.y) * SWORD_COLLISION_WIDTH / 2.0f)) + (sinf(pPlayer->rot.y) * SWORD_COLLISION_DEPTH)) -
						(pPlayer->pos.x + (cosf(pPlayer->rot.y) * SWORD_COLLISION_WIDTH / 2.0f));
	g_fSwordVecAx[3] = (pPlayer->pos.x + (cosf(pPlayer->rot.y) * SWORD_COLLISION_WIDTH / 2.0f)) -
						(pPlayer->pos.x - (cosf(pPlayer->rot.y) * SWORD_COLLISION_WIDTH / 2.0f));

	g_fSwordVecAz[0] = (pPlayer->pos.z - (sinf(pPlayer->rot.y) * SWORD_COLLISION_WIDTH / 2.0f)) -
						((pPlayer->pos.z - (sinf(pPlayer->rot.y) * SWORD_COLLISION_WIDTH / 2.0f)) + (cosf(pPlayer->rot.y) * SWORD_COLLISION_DEPTH));
	g_fSwordVecAz[1] = ((pPlayer->pos.z - (sinf(pPlayer->rot.y) * SWORD_COLLISION_WIDTH / 2.0f)) + (cosf(pPlayer->rot.y) * SWORD_COLLISION_DEPTH)) -
						((pPlayer->pos.z + (sinf(pPlayer->rot.y) * SWORD_COLLISION_WIDTH / 2.0f)) + (cosf(pPlayer->rot.y) * SWORD_COLLISION_DEPTH));
	g_fSwordVecAz[2] = ((pPlayer->pos.z + (sinf(pPlayer->rot.y) * SWORD_COLLISION_WIDTH / 2.0f)) + (cosf(pPlayer->rot.y) * SWORD_COLLISION_DEPTH)) -
						(pPlayer->pos.z + (sinf(pPlayer->rot.y) * SWORD_COLLISION_WIDTH / 2.0f));
	g_fSwordVecAz[3] = (pPlayer->pos.z + (sinf(pPlayer->rot.y) * SWORD_COLLISION_WIDTH / 2.0f)) - 
						(pPlayer->pos.z - (sinf(pPlayer->rot.y) * SWORD_COLLISION_WIDTH / 2.0f));

	g_fSwordVecBx = pPos->x - pBeforePos->x;
	g_fSwordVecBz = pPos->z - pBeforePos->z;

	g_fAdVec[0] = (g_fSwordVecAz[0] * g_fSwordVecBx) - (g_fSwordVecAx[0] * g_fSwordVecBz);
	g_fAdVec[1] = (g_fSwordVecAz[1] * g_fSwordVecBx) - (g_fSwordVecAx[1] * g_fSwordVecBz);
	g_fAdVec[2] = (g_fSwordVecAz[2] * g_fSwordVecBx) - (g_fSwordVecAx[2] * g_fSwordVecBz);
	g_fAdVec[3] = (g_fSwordVecAz[3] * g_fSwordVecBx) - (g_fSwordVecAx[3] * g_fSwordVecBz);


	if (g_fAdVec[0] < 0.0f &&
		g_fAdVec[1] < 0.0f &&
		g_fAdVec[2] < 0.0f &&
		g_fAdVec[3] < 0.0f)
	{
		bDamage = true;
	}
*/

	g_fSwordVecAz[0] = pPlayer->pos.z + (cosf(pPlayer->rot.y) * SWORD_COLLISION_DEPTH);
	g_fSwordVecAz[1] = pPlayer->pos.x + (sinf(pPlayer->rot.y) * SWORD_COLLISION_WIDTH);

	if (pPos->x > g_fSwordVecAz[1] - fWidth / 2.0f &&
		pPos->x < g_fSwordVecAz[1] + fWidth / 2.0f &&
		pPos->z < g_fSwordVecAz[0] + fDepth / 2.0f &&
		pPos->z > g_fSwordVecAz[0] - fDepth / 2.0f)
	{
		bDamage = true;
	}

	return bDamage;
}


//=======================================================================
//取得処理
//=======================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}

//=======================================================================
//取得処理
//=======================================================================
Model *GetSword(void)
{
	return &g_Player.aModel[4];
}
