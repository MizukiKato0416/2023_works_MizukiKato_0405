//=======================================================================
//ステージ1に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#include "main.h"
#include "stage1.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "shadow.h"
#include "wall.h"
#include "billboard.h"
#include "bullet.h"
#include "ground.h"
#include "player.h"
#include "enemy.h"
#include "meshsphere.h"
#include "fade.h"
#include "life.h"
#include "ui.h"
#include "enemylife.h"
#include "pad.h"
#include "sound.h"
#include "mask.h"
#include "time.h"
#include "score.h"
#include "effect.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================
Stage1 g_Stage1;
int g_TimeUp;
bool g_bMask;

//=======================================================================
//初期化処理
//=======================================================================
void InitStage1(void)
{
	SetShadow(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f);
	g_Stage1.bStop = true;
	g_Stage1.nSetEnemy = 0;
	g_TimeUp = 0;
	g_bMask = false;

	//各種オブジェの初期化処理
	InitShadow();
	InitEffect();
	InitPlayer();
	InitCamera();
	InitLight();
	InitWall();
	InitBillboard();
	InitBullet();
	InitGround();
	InitModel();
	InitEnemy();
	InitMeshSphere();
	InitLife();
	InitUi();
	InitEnemyLife();
	InitMask();
	InitTime();
	InitScore();

	//=======================================================================
	////各設置物の配置
	//=======================================================================
	SetWall(D3DXVECTOR3(0.0f, 390.0f, 1600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3200.0f, 800.0f, 0.0f));
	SetWall(D3DXVECTOR3(0.0f, 390.0f, -1600.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(3200.0f, 800.0f, 0.0f));
	SetWall(D3DXVECTOR3(1600.0f, 390.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f, 0.0f), D3DXVECTOR3(3200.0f, 800.0f, 0.0f));
	SetWall(D3DXVECTOR3(-1600.0f, 390.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f), D3DXVECTOR3(3200.0f, 800.0f, 0.0f));
	for (int nCntTree = 0; nCntTree < 16; nCntTree++)
	{
		SetBillboard(D3DXVECTOR3(-1500.0f + (200 * nCntTree), 170.0f, -1500.0f), 200.0f, 400.0f);
		SetBillboard(D3DXVECTOR3(-1500.0f + (200 * nCntTree), 170.0f, 1500.0f), 200.0f, 400.0f);
		SetBillboard(D3DXVECTOR3(-1500.0f, 170.0f, -1500.0f + (200 * nCntTree)), 200.0f, 400.0f);
		SetBillboard(D3DXVECTOR3(1500.0f, 170.0f, -1500.0f + (200 * nCntTree)), 200.0f, 400.0f);
	}
	for (int nCntTree = 0; nCntTree < 15; nCntTree++)
	{
		SetBillboard(D3DXVECTOR3(-1400.0f + (200 * nCntTree), 170.0f, -1300.0f), 200.0f, 400.0f);
		SetBillboard(D3DXVECTOR3(-1400.0f + (200 * nCntTree), 170.0f, 1300.0f), 200.0f, 400.0f);
		SetBillboard(D3DXVECTOR3(-1300.0f, 170.0f, -1400.0f + (200 * nCntTree)), 200.0f, 400.0f);
		SetBillboard(D3DXVECTOR3(1300.0f, 170.0f, -1400.0f + (200 * nCntTree)), 200.0f, 400.0f);
	}

	SetGround(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3200.0f, 0.0f, 3200.0f, 20, 20);
	SetModel(D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BUILDING_LOW);
	SetModel(D3DXVECTOR3(-200.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BUILDING_LOW);
	SetModel(D3DXVECTOR3(-600.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BUILDING_LOW_02);
	SetModel(D3DXVECTOR3(600.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BUILDING_LOW_02);
	SetModel(D3DXVECTOR3(1000.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BUILDING_HIGH);
	SetModel(D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BUILDING_HIGH);
	SetModel(D3DXVECTOR3(-900.0f, 0.0f, 900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BUILDING_HIGH_02);
	SetModel(D3DXVECTOR3(0.0f, 0.0f, 900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BUILDING_HIGH_02);
	SetModel(D3DXVECTOR3(0.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CAR);
	SetEnemy(D3DXVECTOR3(0.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(0.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(0.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(0.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(1000.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(1000.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(1000.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(1000.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(1000.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetLife(D3DXVECTOR3(20.0f, 685.0f, 0.0f), GAUGETYPE_PLAYER, 450.0f, 40.0f);
	SetUi(D3DXVECTOR3(0.0f, 680.0f, 0.0f), UITYPE_PLAYER, 500.0f, 80.0f);
	PlaySound(SOUND_LABEL_STAGE1_BGM);
}

//=======================================================================
//終了処理
//=======================================================================
void UninitStage1(void)
{
	StopSound(SOUND_LABEL_STAGE1_BGM);
	UninitCamera();
	UninitLight();
	UninitModel();
	UninitShadow();
	UninitWall();
	UninitBillboard();
	UninitBullet();
	UninitGround();
	UninitPlayer();
	UninitEnemy();
	UninitMeshSphere();
	UninitLife();
	UninitUi();
	UninitMask();
	UninitEnemyLife();
	UninitTime();
	UninitScore();
	UninitEffect();
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateStage1(void)
{
	PLAYER *pPlayer = GetPlayer();
	int nTime = GetTime();
	int nAllEnemy = GetAllEnemy();
	int nPause = GetPauseUi();

	//Pキーを押したときの処理
	if (GetButtonTrigger(XINPUT_GAMEPAD_START) == true && nTime > 0 && pPlayer->bUse == true)
	{
		if (g_Stage1.bStop == true)
		{
			PlaySound(SOUND_LABEL_PAUSEOPEN);
			g_Stage1.bStop = false;
			SetUi(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 400.0f, SCREEN_HEIGHT / 2.0f, 0.0f), UITYPE_PAUSE, 800.0f, 500.0f);
			SetUi(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 2.0f - 50.0f, 0.0f), UITYPE_CONTINUE, 600.0f, 75.0f);
			SetUi(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 150.0f, SCREEN_HEIGHT / 2.0f + 100.0f, 0.0f), UITYPE_EXIT, 300.0f, 75.0f);
		}
		else
		{
			g_Stage1.bStop = true;
			PlaySound(SOUND_LABEL_TITLE_DECIDE);
		}
	}

	//更新処理
	if (g_Stage1.bStop == true && nTime > 0)
	{
		if (pPlayer->bUse == true)
		{
			g_Stage1.nSetEnemy++;

			if (g_Stage1.nSetEnemy >= 900 && nAllEnemy < MAX_ENEMY - 5)
			{
				g_Stage1.nSetEnemy = 0;

				if (pPlayer->pos.x >= 200)
				{
					SetEnemy(D3DXVECTOR3(-100.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					SetEnemy(D3DXVECTOR3(-100.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					SetEnemy(D3DXVECTOR3(-100.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					SetEnemy(D3DXVECTOR3(-100.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					SetEnemy(D3DXVECTOR3(-100.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				else
				{
					SetEnemy(D3DXVECTOR3(1000.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					SetEnemy(D3DXVECTOR3(1000.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					SetEnemy(D3DXVECTOR3(1000.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					SetEnemy(D3DXVECTOR3(1000.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					SetEnemy(D3DXVECTOR3(1000.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}

			}


			UpdateEnemy();
			UpdatePlayer();
			UpdateCamera();
			UpdateLight();
			UpdateModel();
			UpdateWall();
			UpdateBillboard();
			UpdateBullet();
			UpdateGround();
			UpdateMeshSphere();
			UpdateShadow();
			UpdateEffect();
			UpdateLife();
			UpdateMask();
			UpdateEnemyLife();
			UpdateTime();
			UpdateScore();
		}
		else
		{
			UpdatePlayer();
			UpdateEffect();
			UpdateMask();
		}
	}
	else if(g_Stage1.bStop == false)
	{
		if (GetButtonTrigger(XINPUT_GAMEPAD_B) == true)
		{
			if (nPause == 0)
			{
				g_Stage1.bStop = true;
				PlaySound(SOUND_LABEL_TITLE_DECIDE);
			}
			else
			{
				if (GetFade() == FADE_NONE)
				{
					SetFade(MODE_TITLE);
					PlaySound(SOUND_LABEL_TITLE_DECIDE);
				}
			}
		}
	}
	UpdateUi();

	//リザルトへ移行
	if (GetKeyboardTrigger(DIK_LSHIFT) == true)
	{
		SetFade(MODE_RESULT);
	}
	if (nTime <= 0)
	{
		UpdateTime();
		UpdateMask();
		if (g_bMask == false)
		{
			PlaySound(SOUND_LABEL_TIMEUP);
			g_bMask = true;
			SetMask(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 400.0f, SCREEN_HEIGHT / 2.0f , 0.0f), MASKTYPE_TIMEUP, 800.0f, 300.0f);
		}
		g_TimeUp++;
		if (g_TimeUp >= 300 && GetFade() == FADE_NONE)
		{
			g_TimeUp = 0;
			SetFade(MODE_RESULT);
		}
	}
}

//=======================================================================
//描画処理
//=======================================================================
void DrawStage1(void)
{
	//各種オブジェクトの描画処理

	if (g_Stage1.bStop == true)
	{
		DrawMeshSphere();
		DrawGround();
		DrawShadow();
		DrawBillboard();
		DrawPlayer();
		DrawEnemy();
		DrawEnemyLife();
		DrawWall();
		DrawModel();
		DrawEffect();
		DrawBullet();
		DrawUi();
		DrawLife();
		DrawScore();
		DrawTime();
		DrawMask();
		//SetCamera();
	}
	else if (g_Stage1.bStop == false)
	{
		DrawMeshSphere();
		DrawGround();
		DrawModel();
		DrawBillboard();
		DrawShadow();
		DrawPlayer();
		DrawEnemy();
		DrawEnemyLife();
		DrawWall();
		DrawEffect();
		DrawBullet();
		DrawUi();
		DrawLife();
		DrawScore();
		DrawTime();
		DrawMask();

	}
}

//=======================================================================
//取得処理
//=======================================================================
Stage1 *GetStage1(void)
{
	return &g_Stage1;
}
