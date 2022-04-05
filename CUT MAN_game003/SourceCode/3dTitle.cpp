//=======================================================================
//ステージ1に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#include "main.h"
#include "3dTitle.h"
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
#include "input.h"
#include "sound.h"
#include "score.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================
int g_nCntResult;

//=======================================================================
//初期化処理
//=======================================================================
void Init3DTitle(void)
{
	g_nCntResult = 0;


	//各種オブジェの初期化処理
	InitShadow();
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
	SetUi(D3DXVECTOR3(SCREEN_WIDTH / 3.0f - 400.0f, 0.0f, 0.0f), UITYPE_TITLE, 800.0f, 300.0f);
	SetUi(D3DXVECTOR3(SCREEN_WIDTH / 3.0f - 250.0f, 600.0f, 0.0f), UITYPE_START, 500.0f, 100.0f);
	PlaySound(SOUND_LABEL_TITLE_BGM);

}

//=======================================================================
//終了処理
//=======================================================================
void Uninit3DTitle(void)
{
	StopSound(SOUND_LABEL_TITLE_BGM);

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
	UninitEnemyLife();
	UninitScore();

}

//=======================================================================
//更新処理
//=======================================================================
void Update3DTitle(void)
{
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
	UpdateLife();
	UpdateUi();
	UpdateEnemyLife();
	UpdateScore();

	if (GetButtonTrigger(XINPUT_GAMEPAD_START) == true || GetKeyboardTrigger(DIK_SPACE) == true)
	{
		if (GetFade() == FADE_NONE)
		{
			SetFade(MODE_DESCRIPTION);
			PlaySound(SOUND_LABEL_TITLE_DECIDE);
		}
	}
	g_nCntResult++;
	if (g_nCntResult >= 1200)
	{
		g_nCntResult = 0;
		if (GetFade() == FADE_NONE)
		{
			SetFade(MODE_RESULT);
		}
	}
}

//=======================================================================
//描画処理
//=======================================================================
void Draw3DTitle(void)
{
	DrawMeshSphere();
	//DrawScore();
	DrawGround();
	DrawShadow();
	DrawModel();
	DrawBillboard();
	DrawPlayer();
	DrawEnemy();
	DrawEnemyLife();
	DrawWall();
	DrawBullet();
	DrawUi();
	DrawLife();
}