//=======================================================================
//ステージ1に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#include "main.h"
#include "stage1.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "modeltxt.h"
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
#include "drone.h"
#include "EnemyBullet.h"
#include "evolutionGauge.h"
#include "boss.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================
Stage1 g_Stage1;
int g_TimeUp;
bool g_bMask;
bool g_bStart;
int g_nStartTime;
int g_nCntStart;

//=======================================================================
//初期化処理
//=======================================================================
void InitStage1(void)
{
	SetShadow(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f);
	g_Stage1.bStop = true;
	g_Stage1.bStart = false;
	g_Stage1.nSetEnemy = 0;
	g_Stage1.nStartTime = 0;
	g_TimeUp = 0;
	g_bMask = false;
	g_bStart = false;
	g_nStartTime = 0;
	g_nCntStart = 0;

	//各種オブジェの初期化処理
	InitUi();
	InitShadow();
	InitEffect();
	InitPlayer();
	InitCamera();
	InitLight();
	InitWall();
	InitBillboard();
	InitBullet();
	InitEnemyBullet();
	InitGround();
	InitModelTxt();
	InitDrone();
	InitEnemy();
	InitMeshSphere();
	InitLife();
	InitEnemyLife();
	InitMask();
	InitTime();
	InitScore();
	InitEvolutionGauge();
	InitBoss();

	//=======================================================================
	////各設置物の配置
	//=======================================================================
	SetWall(D3DXVECTOR3(0.0f, 440.0f, 3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(6000.0f, 900.0f, 0.0f));
	SetWall(D3DXVECTOR3(0.0f, 440.0f, -3000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(6000.0f, 900.0f, 0.0f));
	SetWall(D3DXVECTOR3(3000.0f, 440.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f, 0.0f), D3DXVECTOR3(6000.0f, 900.0f, 0.0f));
	SetWall(D3DXVECTOR3(-3000.0f, 440.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f), D3DXVECTOR3(6000.0f, 900.0f, 0.0f));
	
	SetGround(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 6000.0f, 0.0f, 6000.0f, 30, 30);

	//敵
	SetEnemy(D3DXVECTOR3(-800.0f, 0.0f, -900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(-800.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(-800.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(-800.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(-800.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(-800.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(-800.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetEnemy(D3DXVECTOR3(2300.0f, 0.0f, -2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(2300.0f, 0.0f, -1800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(2300.0f, 0.0f, -1600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(2300.0f, 0.0f, -1400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(2300.0f, 0.0f, -1200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(2300.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(2300.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(2300.0f, 0.0f, 1200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(2300.0f, 0.0f, 1400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(2300.0f, 0.0f, 1600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(2300.0f, 0.0f, 1800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(2300.0f, 0.0f, 2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(2300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	//ボス
	SetBoss(D3DXVECTOR3(-1400.0f, 0.0f, 1600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetBoss(D3DXVECTOR3(-1400.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetBoss(D3DXVECTOR3(1000.0f, 0.0f, 1600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetBoss(D3DXVECTOR3(1000.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//ドローン
	SetDrone(D3DXVECTOR3(600.0f, 80.0f, -1750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), DRONETYPE_001);
	SetDrone(D3DXVECTOR3(400.0f, 80.0f, -1750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), DRONETYPE_001);

	SetDrone(D3DXVECTOR3(600.0f, 80.0f, 1600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), DRONETYPE_002);
	SetDrone(D3DXVECTOR3(400.0f, 80.0f, 1600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), DRONETYPE_002);

	SetDrone(D3DXVECTOR3(-700.0f, 80.0f, 1600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), DRONETYPE_003);
	SetDrone(D3DXVECTOR3(-700.0f, 80.0f, -1750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), DRONETYPE_003);



	SetLife(D3DXVECTOR3(40.0f, 685.0f, 0.0f), GAUGETYPE_PLAYER, PLAYER_LIFE_WIDTH, 40.0f);
	SetEvolutionGauge(D3DXVECTOR3(40.0f, 615.0f, 0.0f), EVOLUTION_GAUGETYPE_PLAYER, 0.0f, EVOLUTIONGAUGE_HEIGHT);
	SetUi(D3DXVECTOR3(0.0f, 685.0f, 0.0f), UITYPE_PLAYER, 525.0f, 70.0f);
	SetUi(D3DXVECTOR3(0.0f, 615.0f, 0.0f), UITYPE_EVOLUTION, 525.0f, 70.0f);
	SetUi(D3DXVECTOR3(1140.0f, 700.0f, 0.0f), UITYPE_BUTTON_Y, 30.0f, 30.0f);
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
	UninitModelTxt();
	UninitShadow();
	UninitWall();
	UninitBillboard();
	UninitBullet();
	UninitEnemyBullet();
	UninitGround();
	UninitPlayer();
	UninitEnemy();
	UninitDrone();
	UninitMeshSphere();
	UninitLife();
	UninitUi();
	UninitMask();
	UninitEnemyLife();
	UninitTime();
	UninitScore();
	UninitEffect();
	UninitEvolutionGauge();
	UninitBoss();
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateStage1(void)
{
	PLAYER *pPlayer = GetPlayer();
	int nTime = GetTime();
	int nAllEnemy = GetAllEnemy();
	int nAllBoss = GetAllBoss();
	int nAllDrone = GetAllDrone();
	int nPause = GetPauseUi();

	g_nCntStart++;
	if (g_nCntStart >= 60)
	{
		g_nCntStart = 0;
		g_Stage1.nStartTime++;
	}

	if (g_Stage1.nStartTime == 1 && g_nCntStart == 1)
	{
		PlaySound(SOUND_LABEL_321);
		SetUi(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 150.0f, SCREEN_HEIGHT / 3.0f, 0.0f), UITYPE_3, 300.0f, 300.0f);
	}
	else if (g_Stage1.nStartTime == 2 && g_nCntStart == 1)
	{
		PlaySound(SOUND_LABEL_321);
		SetUi(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 150.0f, SCREEN_HEIGHT / 3.0f, 0.0f), UITYPE_2, 300.0f, 300.0f);
	}
	else if (g_Stage1.nStartTime == 3 && g_nCntStart == 1)
	{
		PlaySound(SOUND_LABEL_321);
		SetUi(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 150.0f, SCREEN_HEIGHT / 3.0f, 0.0f), UITYPE_1, 300.0f, 300.0f);
	}
	else if (g_Stage1.nStartTime == 4 && g_nCntStart == 1)
	{
		PlaySound(SOUND_LABEL_START);
		SetUi(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), UITYPE_321START, 700.0f * 3.0f, 300.0f * 3.0f);
		g_Stage1.bStart = true;
	}
	else if (g_Stage1.nStartTime >= 5)
	{
		g_Stage1.nStartTime = 5;
	}

	if (g_Stage1.bStart == true)
	{
		//Pキーを押したときの処理
		if (GetButtonTrigger(XINPUT_GAMEPAD_START) == true && nTime > 0 && pPlayer->bUse == true)
		{
			if (g_Stage1.bStop == true)
			{
				PlaySound(SOUND_LABEL_PAUSEOPEN);
				g_Stage1.bStop = false;
				SetUi(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2.0f, 0.0f), UITYPE_BLACKMASK, SCREEN_WIDTH, SCREEN_HEIGHT);
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

				if (g_Stage1.nSetEnemy >= 900)
				{
					g_Stage1.nSetEnemy = 0;

					if (nAllEnemy < MAX_ENEMY - 7)
					{
						SetEnemy(D3DXVECTOR3(-800.0f, 0.0f, -900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
						SetEnemy(D3DXVECTOR3(-800.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
						SetEnemy(D3DXVECTOR3(-800.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
						SetEnemy(D3DXVECTOR3(-800.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
						SetEnemy(D3DXVECTOR3(-800.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
						SetEnemy(D3DXVECTOR3(-800.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
						SetEnemy(D3DXVECTOR3(-800.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}

					if (nAllBoss < MAX_BOSS - 1)
					{
						SetBoss(D3DXVECTOR3(-1400.0f, 0.0f, 1600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}

					if (nAllDrone < MAX_DRONE - 3)
					{
						SetDrone(D3DXVECTOR3(600.0f, 80.0f, -1750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), DRONETYPE_001);

						SetDrone(D3DXVECTOR3(400.0f, 80.0f, 1600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), DRONETYPE_002);

						SetDrone(D3DXVECTOR3(-700.0f, 80.0f, 1600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), DRONETYPE_003);
					}
				}

				UpdateEnemy();
				UpdatePlayer();
				UpdateCamera();
				UpdateLight();
				UpdateModelTxt();
				UpdateDrone();
				UpdateWall();
				UpdateBillboard();
				UpdateBullet();
				UpdateEnemyBullet();
				UpdateGround();
				UpdateMeshSphere();
				UpdateShadow();
				UpdateEffect();
				UpdateLife();
				UpdateMask();
				UpdateEnemyLife();
				UpdateTime();
				UpdateScore();
				UpdateEvolutionGauge();
				UpdateBoss();
			}
			else
			{
				UpdatePlayer();
				UpdateEffect();
				UpdateMask();
			}
		}
		else if (g_Stage1.bStop == false)
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
						SetFade(MODE_MENUE);
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
				PlaySound(SOUND_LABEL_GRADECHARGE);
				g_bMask = true;
				SetMask(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 400.0f, SCREEN_HEIGHT / 2.0f, 0.0f), MASKTYPE_TIMEUP, 800.0f, 300.0f);
			}
			g_TimeUp++;
			if (g_TimeUp >= 300 && GetFade() == FADE_NONE)
			{
				g_TimeUp = 0;
				SetFade(MODE_RESULT);
			}
		}
	}
	else
	{
		UpdateCamera();
		UpdateUi();
		UpdatePlayer();
	}
}

//=======================================================================
//描画処理
//=======================================================================
void DrawStage1(void)
{
	//各種オブジェクトの描画処理
	SetCamera(0);
	if (g_Stage1.bStop == true)
	{
		DrawMeshSphere();
		DrawGround();
		DrawShadow();
		DrawBillboard();
		DrawPlayer();
		DrawEnemy();
		DrawBoss();
		DrawEnemyLife();
		DrawWall();
		DrawModelTxt();
		DrawDrone();
		DrawEffect();
		DrawBullet();
		DrawEnemyBullet();
		DrawLife();
		DrawEvolutionGauge();
		DrawScore();
		DrawTime();
		DrawUi();
		DrawMask();
	}
	else if (g_Stage1.bStop == false)
	{
		DrawMeshSphere();
		DrawGround();
		DrawModelTxt();
		DrawDrone();
		DrawBillboard();
		DrawShadow();
		DrawPlayer();
		DrawEnemy();
		DrawBoss();
		DrawEnemyLife();
		DrawWall();
		DrawEffect();
		DrawBullet();
		DrawEnemyBullet();
		DrawLife();
		DrawEvolutionGauge();
		DrawScore();
		DrawTime();
		DrawUi();
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
