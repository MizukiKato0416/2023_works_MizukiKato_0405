//=======================================================================
//カメラに関する処理
//Aouthor: 加藤　瑞葵
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
//グローバル変数宣言
//=======================================================================
Camera g_camera[MAX_CAMERA];				//カメラの情報
D3DXMATRIX g_mtxWorldCamera;		//ワールドマトリックス
bool g_bTurn;

//=======================================================================
//初期化処理
//=======================================================================
void InitCamera(void)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		//変数初期化
		g_camera[nCntCamera].rot.y = pPlayer->rot.y;											//カメラの向き
		g_camera[nCntCamera].rotAsk = D3DXVECTOR3(0.0f,0.0f,0.0f);									//カメラの向き
		g_camera[0].posV = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 140.0f + g_camera[0].ftest, pPlayer->pos.z - 400.0f);	//現在の視点
		g_camera[nCntCamera].posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//目的の視点
		g_camera[0].posR = D3DXVECTOR3(pPlayer->pos.x + sinf(g_camera[0].rot.y) * 80.0f, pPlayer->pos.y + 80.0f, pPlayer->pos.z + cosf(g_camera[0].rot.y) * 80.0f);	//現在の注視点
		g_camera[nCntCamera].posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//目的の注視点
		g_camera[nCntCamera].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);								//法線
		g_camera[nCntCamera].ftest = 0.0f;														//テスト用
		g_camera[nCntCamera].rotDiffer = 0.0f;														//テスト用
		g_camera[nCntCamera].viewport.X = 0.0f;													//描画する画面の左上X座標
		g_camera[nCntCamera].viewport.Y = 0.0f;													//描画する画面の左上Y座標
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
	g_camera[0].viewport.Width = SCREEN_WIDTH;										//描画する画面の幅
	g_camera[0].viewport.Height = SCREEN_HEIGHT;									//描画する画面の高さ

	g_camera[1].viewport.Width = SCREEN_WIDTH * 0.1;										//描画する画面の幅
	g_camera[1].viewport.Height = SCREEN_HEIGHT * 0.1;									//描画する画面の高さ

	g_camera[0].posR = D3DXVECTOR3(pPlayer->pos.x + sinf(g_camera[0].rot.y) * 80.0f, pPlayer->pos.y + 80.0f, pPlayer->pos.z + cosf(g_camera[0].rot.y) * 80.0f);	//現在の注視点
	g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.y) * CAMERA_DISTANCE;
	g_camera[0].posV.z = g_camera[0].posR.z - cosf(g_camera[0].rot.y) * CAMERA_DISTANCE;
}

//=======================================================================
//終了処理
//=======================================================================
void UninitCamera(void)
{

}

//=======================================================================
//更新処理
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
		
		


		//ZLが押されたときの処理
		if(GetTriggerTrigger(TRIGGERTYPE_RIGHT) == true)
		{
			g_bTurn = true;
			g_camera[0].rotAsk.y = pPlayer->rot.y;
		}

		//Lスティックが押されたときの処理
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

		//ロックオンしたときの処理
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
			//右スティック入力
			//============================================
			// スティックの左が押された
			if (GetRightStick(STICKTYPE_LEFT) == true && g_bTurn == false)
			{
				g_camera[0].rot.y -= CAMERA_R_SPEED;
				g_camera[0].posR.x = g_camera[0].posV.x + sinf(g_camera[0].rot.y) * CAMERA_DISTANCE;
				g_camera[0].posR.z = g_camera[0].posV.z + cosf(g_camera[0].rot.y) * CAMERA_DISTANCE;
				//g_bTurn = false;

			}
			// スティックの右が押された
			else if (GetRightStick(STICKTYPE_RIGHT) == true && g_bTurn == false)
			{
				g_camera[0].rot.y += CAMERA_R_SPEED;
				g_camera[0].posR.x = g_camera[0].posV.x + sinf(g_camera[0].rot.y) * CAMERA_DISTANCE;
				g_camera[0].posR.z = g_camera[0].posV.z + cosf(g_camera[0].rot.y) * CAMERA_DISTANCE;
				//g_bTurn = false;

			}
		}
		
		g_camera[0].posR = D3DXVECTOR3(pPlayer->pos.x + sinf(g_camera[0].rot.y) * 80.0f, pPlayer->pos.y + 80.0f, pPlayer->pos.z + cosf(g_camera[0].rot.y) * 80.0f);	//現在の注視点
		g_camera[0].posV = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 140.0f + g_camera[0].ftest, pPlayer->pos.z - 400.0f);	//現在の視点

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
//設定処理
//=======================================================================
void SetCamera(int nIdx)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する

	//ビューポートの設定
	pDevice->SetViewport(&g_camera[nIdx].viewport);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera[nIdx].mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_camera[nIdx].mtxProjection,
								D3DXToRadian(50.0f),							//画角
								(float)g_camera[nIdx].viewport.Width / (float)g_camera[nIdx].viewport.Height,		//比率
								10.0f,											//Z方向の描画範囲
								50000.0f);

	//プロジェクションマトリックスの設定

	pDevice->SetTransform(D3DTS_PROJECTION,&g_camera[nIdx].mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera[nIdx].mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera[nIdx].mtxView, &g_camera[nIdx].posV, &g_camera[nIdx].posR, &g_camera[nIdx].vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera[nIdx].mtxView);
}

Camera *GetCamera(void)
{
	return &g_camera[0];
}
