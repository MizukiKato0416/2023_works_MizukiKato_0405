//================================================
//ゲーム01処理
//Author: KatoMizuki
//================================================
#include "game01.h"
#include "manager.h"
#include "input_keyboard.h"
#include "player.h"
#include "meshsphere.h"
#include "meshfield.h"
#include "texture.h"
#include "object3D.h"
#include "fade.h"
#include "model_single.h"
#include "dungeon_room_director.h"
#include "dungeon_road_builder.h"
#include "dungeon_wall_builder.h"
#include "dungeon_check_road_builder.h"
#include "dungeon_enemy_road_builder.h"
#include "dungeon_start_road_builder.h"
#include "dungeon_end_road_builder.h"
#include "magic_circle.h"
#include "gauge.h"
#include "play_data.h"
#include "map.h"
#include "ui.h"
#include "pause.h"
#include "score.h"
#include "time.h"
#include "sound.h"

//================================================
//マクロ定義
//================================================
#define GAME01_RECOVERYCOUNT	(20)		//回復する頻度
#define GAME01_STAGE_SIZE		(7)			//ステージのサイズ
#define GAME01_NEXT_SCENE_COUNT	(180)		//次のシーンまでのカウント
#define GAME01_GAME_OVER_SIZE_X	(914.0f)	//ゲームオーバーのサイズX
#define GAME01_GAME_OVER_SIZE_Y	(128.0f)	//ゲームオーバーのサイズY

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CGame01::CGame01(int nPriority):CObject(nPriority)
{
	m_pHpGauge = nullptr;
	m_pMpGauge = nullptr;
	m_pSpGauge = nullptr;
	m_nRecoveryCounter = 0;
	m_nGameCounter = 0;
	m_pObjet2DGame = nullptr;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CGame01::~CGame01()
{
	
}

//================================================
//初期化処理
//================================================
HRESULT CGame01::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//BGM再生
	pSound->Play(CSound::SOUND_LABEL_GAME_BGM);

	//サウンドの音量調整
	pSound->ControllVoice(CSound::SOUND_LABEL_GAME_BGM, 0.3f);

	//変数初期化
	m_nRecoveryCounter = 0;
	m_nGameCounter = 0;
	m_pObjet2DGame = nullptr;

	//ダンジョンを構築する部屋をそれぞれ生成
	//道だけの部屋
	CDungeonRoadBuilder *pDungeonRoadBuilder = nullptr;
	pDungeonRoadBuilder = CDungeonRoadBuilder::Create();
	//壁になる部屋
	CDungeonWallBuilder *pDungeonWallBuilder = nullptr;
	pDungeonWallBuilder = CDungeonWallBuilder::Create();
	//チェックポイントがある部屋
	CDungeonCheckRoadBuilder *pDungeonCheckRoadBuilder = nullptr;
	pDungeonCheckRoadBuilder = CDungeonCheckRoadBuilder::Create();
	//敵がいる部屋
	CDungeonEnemyRoadBuilder *pDungeonEnemyRoadBuilder = nullptr;
	pDungeonEnemyRoadBuilder = CDungeonEnemyRoadBuilder::Create();
	//スタート時の部屋
	CDungeonStartRoadBuilder *pDungeonStartRoadBuilder = nullptr;
	pDungeonStartRoadBuilder = CDungeonStartRoadBuilder::Create();
	//終点の部屋
	CDungeonEndRoadBuilder *pDungeonEndRoadBuilder = nullptr;
	pDungeonEndRoadBuilder = CDungeonEndRoadBuilder::Create();
	
	// 棒倒し法によるダンジョンの生成
	// 5未満のサイズでは生成できない
	int nDepth = GAME01_STAGE_SIZE;		//縦の数
	int nWidth = GAME01_STAGE_SIZE;		//横の数
	int nWall = 1;		//壁(今回は穴)
	int nPath = 0;		//通れる道

	// 指定サイズで生成し外周を壁にする
	int maze[GAME01_STAGE_SIZE][GAME01_STAGE_SIZE];
	for (int nCntZ = 0; nCntZ < nDepth; nCntZ++)
	{
		for (int nCntX = 0; nCntX < nWidth; nCntX++)
		{
			if (nCntX == 0 || nCntZ == 0 || nCntX == nWidth - 1 || nCntZ == nDepth - 1)
			{
				if ((nCntX == 1 && nCntZ == 0) || nCntX == nWidth - 2 && nCntZ == nDepth - 1)
				{//ここはスタート地点とゴールにするので道を作る
					maze[nCntZ][nCntX] = nPath;
				}
				else
				{//それ以外
					maze[nCntZ][nCntX] = nWall; // 外周はすべて壁
				}
			}
			else
			{
				maze[nCntZ][nCntX] = nPath;  // 外周以外は通路
			}
		}
	}

	// 棒を立て、倒す
	for (int nCntZ = 2; nCntZ < nDepth - 1; nCntZ += 2)
	{
		for (int nCntX = 2; nCntX < nWidth - 1; nCntX += 2)
		{
			maze[nCntZ][nCntX] = nWall; // 棒を立てる

			// 倒せるまで繰り返す
			while (true)
			{
				// 1行目のみ上に倒せる
				int nDirection = 0;
				if (nCntZ == 2)
				{
					nDirection = rand() % 4;
				}
				else
				{
					nDirection = rand() % 3;
				}

				// 棒を倒す方向を決める
				int nWallX = nCntX;
				int nWallZ = nCntZ;
				switch (nDirection)
				{
				case 0: // 右
					nWallX++;
					break;
				case 1: // 下
					nWallZ++;
					break;
				case 2: // 左
					nWallX--;
					break;
				case 3: // 上
					nWallZ--;
					break;
				}
				// 壁じゃない場合のみ倒して終了
				if (maze[nWallZ][nWallX] != nWall ||
					(maze[nCntZ][nCntX - 1] == nWall && maze[nCntZ][nCntX + 1] == nWall && maze[nCntZ + 1][nCntX] == nWall))
				{
					maze[nWallZ][nWallX] = nWall;
					break;
				}
			}
		}
	}

	//生成する道の種類を決めるための変数
	int nNumRoad = 0;
	//部屋の生成
	for (int nCntZ = 0; nCntZ < nDepth ; nCntZ++)
	{
		for (int nCntX = 0; nCntX < nWidth ; nCntX++)
		{
			//壁だったら
			if (maze[nCntZ][nCntX] == nWall)
			{
				//壁の部屋を作る
				CDungeonRoomDirector::Create(pDungeonWallBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
																				0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));
				//壁のマップを作る
				CMap::Create(D3DXVECTOR3(MAP_ROOM_SIZE * (nCntX - (nWidth - 1) / 2.0f),
					                     -MAP_ROOM_SIZE * (nCntZ - (nDepth - 1) / 2.0f),
					                     0.0f),
					         D3DXVECTOR3(MAP_ROOM_SIZE, MAP_ROOM_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::WALL);
			}
			else if (maze[nCntZ][nCntX] == nPath)
			{//道だったら
				
				if (nCntZ == 0 && nCntX == 1)
				{//ここだけはスタートの部屋にする
					CDungeonRoomDirector::Create(pDungeonStartRoadBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
																				0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));

					//スタート地点のマップを作る
					CMap::Create(D3DXVECTOR3(MAP_ROOM_SIZE * (nCntX - (nWidth - 1) / 2.0f),
						                     -MAP_ROOM_SIZE * (nCntZ - (nDepth - 1) / 2.0f),
						                     0.0f),
						         D3DXVECTOR3(MAP_ROOM_SIZE, MAP_ROOM_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::START);

				}
				else if (nCntX == nWidth - 2 && nCntZ == nDepth - 1)
				{//ここだけはゴールの部屋にする
					CDungeonRoomDirector::Create(pDungeonEndRoadBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
																				0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));

					//ワープのマップを作る
					CMap::Create(D3DXVECTOR3(MAP_ROOM_SIZE * (nCntX - (nWidth - 1) / 2.0f),
						                     -MAP_ROOM_SIZE * (nCntZ - (nDepth - 1) / 2.0f),
						                     0.0f),
						         D3DXVECTOR3(MAP_ROOM_SIZE, MAP_ROOM_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::WARP);
				}
				else
				{
					//道のマップを作る
					CMap::Create(D3DXVECTOR3(MAP_ROOM_SIZE * (nCntX - (nWidth - 1) / 2.0f),
						                     -MAP_ROOM_SIZE * (nCntZ - (nDepth - 1) / 2.0f),
						                     0.0f),
						         D3DXVECTOR3(MAP_ROOM_SIZE, MAP_ROOM_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::ROAD);

					//3種類の道の中から順番に生成する
					switch (nNumRoad)
					{
					case 0:
						//道だけ
						CDungeonRoomDirector::Create(pDungeonRoadBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
							0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));
						break;
					case 1:
						//チェックポイントがある道
						CDungeonRoomDirector::Create(pDungeonCheckRoadBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
							0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));
						break;
					case 2:
						//敵がいる道
						CDungeonRoomDirector::Create(pDungeonEnemyRoadBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
							0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));
						break;
					default:
						break;
					}
					//次の部屋になるよう加算
					nNumRoad++;
					if (nNumRoad >= 3)
					{
						nNumRoad = 0;
					}
				}
			}
		}
	}

	//オブジェクト情報を入れるポインタ
	CObject *pObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CObject::PRIORITY_CHECK_CIRCLE);

	while (pObject != nullptr)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		//オブジェクトの種類がチェックポイントだったら
		if (pObject->GetObjType() == CObject::OBJTYPE::CHECK_CIRCLE)
		{
			//チェックポイントのマップを作る
			CMap::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				         D3DXVECTOR3(MAP_CHECK_SIZE, MAP_CHECK_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::CHECK);
		}
		//次のオブジェクトに進める
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}

	//オブジェクト情報を入れるポインタ
	pObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	pSaveObject = nullptr;

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CObject::PRIORITY_ENEMY);

	while (pObject != nullptr)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		//オブジェクトの種類が敵だったら
		if (pObject->GetObjType() == CObject::OBJTYPE::ENEMY_BEE || pObject->GetObjType() == CObject::OBJTYPE::ENEMY_FAT)
		{
			//敵のマップを作る
			CMap::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				         D3DXVECTOR3(MAP_ENEMY_SIZE, MAP_ENEMY_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::ENEMY);
		}
		//次のオブジェクトに進める
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}

	//チェックポイントのマップのポインタと位置設定
	CMap::SetCheckPointa();

	//敵のマップのポインタと位置設定
	CMap::SetEnemyPointa();

	//マップの位置設定
	CMap::SetStartRoomPos();

	//プレイヤーのマップを作る
	CMap::Create(D3DXVECTOR3(MAP_POS_X, MAP_POS_Y, 0.0f),
		         D3DXVECTOR3(MAP_PLAYER_SIZE, MAP_PLAYER_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::PLAYER);

	//UIの生成
	CObject2D *pObject2D = nullptr;
	pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
		                          D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_UI);
	pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_HP_MP_SP_FRAME"));

	//HPゲージの生成
	m_pHpGauge = CGauge::Create(D3DXVECTOR3(GAUGE_HP_POS_X, GAUGE_HP_POS_Y, 0.0f),
		                        D3DXVECTOR3(GAUGE_HP_SIZE_X, GAUGE_HP_SIZE_Y, 0.0f), PLAYER_MAX_HP, PLAYER_MAX_HP);
	m_pHpGauge->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_HP_GAUGE"));
	CManager::GetInstance()->GetPlayData()->SetHpGauge(m_pHpGauge);

	//MPゲージの生成
	m_pMpGauge = CGauge::Create(D3DXVECTOR3(GAUGE_MP_POS_X, GAUGE_MP_POS_Y, 0.0f),
		                        D3DXVECTOR3(GAUGE_MP_SIZE_X, GAUGE_MP_SIZE_Y, 0.0f), PLAYER_MAX_MP, PLAYER_MAX_MP);
	m_pMpGauge->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_MP_GAUGE"));
	CManager::GetInstance()->GetPlayData()->SetMpGauge(m_pMpGauge);

	//SPゲージの生成
	m_pSpGauge = CGauge::Create(D3DXVECTOR3(GAUGE_SP_POS_X, GAUGE_SP_POS_Y, 0.0f),
		                        D3DXVECTOR3(GAUGE_SP_SIZE_X, GAUGE_SP_SIZE_Y, 0.0f), PLAYER_MAX_SP, 0);
	m_pSpGauge->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_SP_GAUGE"));
	CManager::GetInstance()->GetPlayData()->SetSpGauge(m_pSpGauge);

	//UIの生成
	pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
		                          D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_UI);
	pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_HP_MP_SP"));

	//タイムの生成
	CTime::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, TIME_POLIGON_POSY, 0.0f), D3DXVECTOR3(TIME_POLYGON_WIDTH, TIME_POLYGON_HEIGHT, 0.0f), 0);

	//スコアの生成
	CScore *pSocre = nullptr;
	pSocre = CScore::Create(D3DXVECTOR3(0.0f + (SCORE_POLYGON_WIDTH * MAX_SCORE_POLYGON / 2.0f), SCORE_POLYGON_HEIGHT / 2.0f, 0.0f),
							D3DXVECTOR3(SCORE_POLYGON_WIDTH, SCORE_POLYGON_HEIGHT, 0.0f));
	CManager::GetInstance()->GetPlayData()->SetScorePoint(pSocre);

	//メッセージUIの作成
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
		        CObject::PRIORITY_UI, CUi::TYPE::MESSAGE_01);

	//ポーズの生成
	CPause::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//================================================
//終了処理
//================================================
void CGame01::Uninit(void)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//BGM再生
	pSound->Stop(CSound::SOUND_LABEL_GAME_BGM);

	//ゲームオーバー状態を初期化
	CManager::GetInstance()->GetPlayData()->SetGameOver(false);
	CManager::GetInstance()->GetPlayData()->SetGameClear(false);

	//現在のHP、MP、SPを保存
	CManager::GetInstance()->GetPlayData()->SetHitPoint(m_pHpGauge->GetGauge());
	CManager::GetInstance()->GetPlayData()->SetMagicPoint(m_pMpGauge->GetGauge());
	CManager::GetInstance()->GetPlayData()->SetSpecialPoint(m_pSpGauge->GetGauge());

	//スコアを保存
	CManager::GetInstance()->GetPlayData()->SetScore(CManager::GetInstance()->GetPlayData()->GetScorePoint()->GetScore());
	
	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CGame01::Update(void)
{
	//カウンターを加算
	m_nRecoveryCounter++;
	//既定の値以上になったら
	if (m_nRecoveryCounter >= GAME01_RECOVERYCOUNT)
	{
		//0にする
		m_nRecoveryCounter = 0;
		//HPとMPを回復させる
		m_pHpGauge->AddGauge(1);
		m_pMpGauge->AddGauge(1);
	}
	
	//ゲームオーバーの時
	if (CManager::GetInstance()->GetPlayData()->GetGameOver() == true ||
		CManager::GetInstance()->GetPlayData()->GetGameClear() == true)
	{
		GameOver();
	}

#ifdef DEBUG

	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//Enterキー、スタートボタンを押したら
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		//フェード取得処理
		CFade *pFade;
		pFade = CManager::GetInstance()->GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE::GAME02);
		}
	}

	if (pInputKeyboard->GetPress(DIK_UP) == true)
	{
		m_pMpGauge->AddGauge(10);
	}
	else if (pInputKeyboard->GetPress(DIK_DOWN) == true)
	{
		m_pMpGauge->AddGauge(-10);
	}
	if (pInputKeyboard->GetPress(DIK_LEFT) == true)
	{
		m_pSpGauge->AddGauge(-10);
	}
	else if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{
		m_pSpGauge->AddGauge(10);
	}

#endif // DEBUG
}

//================================================
//描画処理
//================================================
void CGame01::Draw(void)
{

}

//================================================
//ゲームオーバー処理
//================================================
void CGame01::GameOver(void)
{
	//カウンターを加算
	m_nGameCounter++;

	if (m_pObjet2DGame == nullptr)
	{
		//サウンド取得処理
		CSound *pSound;
		pSound = CManager::GetInstance()->GetSound();

		m_pObjet2DGame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
			                               D3DXVECTOR3(GAME01_GAME_OVER_SIZE_X, GAME01_GAME_OVER_SIZE_Y, 0.0f), CObject::PRIORITY_GAME_OVER);
		//ゲームオーバーの時
		if (CManager::GetInstance()->GetPlayData()->GetGameOver() == true)
		{
			//SE再生
			pSound->Play(CSound::SOUND_LABEL_GAMEOVER_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_GAMEOVER_SE, 1.8f);

			m_pObjet2DGame->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_GAME_OVER"));
		}
		else if (CManager::GetInstance()->GetPlayData()->GetGameClear() == true)
		{//ゲームクリアの時
			//SE再生
			pSound->Play(CSound::SOUND_LABEL_GAMECLEAR_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_GAMECLEAR_SE, 1.8f);

			m_pObjet2DGame->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_GAME_CLEAR"));
		}
	}

	//既定の値よりも大きくなったら
	if (m_nGameCounter > GAME01_NEXT_SCENE_COUNT)
	{
		//フェード取得処理
		CFade *pFade;
		pFade = CManager::GetInstance()->GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			//ゲームオーバーの時
			if (CManager::GetInstance()->GetPlayData()->GetGameOver() == true)
			{
				pFade->SetFade(CManager::MODE::MENU);
			}
			else if (CManager::GetInstance()->GetPlayData()->GetGameClear() == true)
			{//ゲームクリアの時
				pFade->SetFade(CManager::MODE::RESULT);
			}
		}
	}
}
