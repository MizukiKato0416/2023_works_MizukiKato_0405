//=======================================================================
//カメラに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "pad.h"

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
	}
	g_bTurn = false;
	g_camera[0].viewport.Width = SCREEN_WIDTH;										//描画する画面の幅
	g_camera[0].viewport.Height = SCREEN_HEIGHT;									//描画する画面の高さ

	g_camera[1].viewport.Width = SCREEN_WIDTH * 0.1;										//描画する画面の幅
	g_camera[1].viewport.Height = SCREEN_HEIGHT * 0.1;									//描画する画面の高さ
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


	//=======================================================================
	//プレイヤーのカメラ設定
	//=======================================================================
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	if (GetMode() == MODE_TITLE)
	{
		g_camera[0].posV = D3DXVECTOR3(1228.0f, 23.0f,-291.3f);	//現在の視点
		g_camera[0].posR = D3DXVECTOR3(941.0f, 80.0f, -205.0f);	//現在の注視点
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

		g_camera[0].posR = D3DXVECTOR3(pPlayer->pos.x + sinf(g_camera[0].rot.y) * 80.0f, pPlayer->pos.y + 80.0f, pPlayer->pos.z + cosf(g_camera[0].rot.y) * 80.0f);	//現在の注視点
		g_camera[0].posV = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 140.0f + g_camera[0].ftest, pPlayer->pos.z - 400.0f);	//現在の視点

		g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.y) * CAMERA_DISTANCE;
		g_camera[0].posV.z = g_camera[0].posR.z - cosf(g_camera[0].rot.y) * CAMERA_DISTANCE;

	}

	
	//=======================================================================
	//キーの入力処理
	//=======================================================================
	

	//注視点のみ
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

	//視点のみ
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
								5000.0f);

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
