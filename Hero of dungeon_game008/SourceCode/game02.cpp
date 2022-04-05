//================================================
//ゲーム02処理
//Author: KatoMizuki
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include "game02.h"
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
#define GAME02_RECOVERYCOUNT	(20)		//回復する頻度
#define GAME02_NEXT_SCENE_COUNT	(180)		//次のシーンまでのカウント
#define GAME02_GAME_OVER_SIZE_X	(914.0f)	//ゲームオーバーのサイズX
#define GAME02_GAME_OVER_SIZE_Y	(128.0f)	//ゲームオーバーのサイズY

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CGame02::CGame02(int nPriority):CObject(nPriority)
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
CGame02::~CGame02()
{

}

//================================================
//初期化処理
//================================================
HRESULT CGame02::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
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

	
	//ステージデータの読み込み
	//ロード処理
	FILE *pFile;
	pFile = fopen("data/STAGE/stage02.csv", "r");
	int nCntX = 0, nCntZ = 0;
	char aLine[64];
	int nDepth = 7;		//縦の数
	int nWidth = 5;		//横の数
	int aMapData[7][5];
	while (fgets(aLine, 64, pFile) != nullptr)
	{
		nCntX = 0;
		char *pToken = strtok(aLine, ",");
		while (pToken != nullptr)
		{
			int nNum = atoi(pToken);
			aMapData[nCntZ][nCntX] = nNum;
			pToken = strtok(nullptr, ",");
			nCntX++;
		}
		nCntZ++;
	}
	fclose(pFile);

	//部屋の生成
	for (nCntZ = 0; nCntZ < nDepth ; nCntZ++)
	{
		for (nCntX = 0; nCntX < nWidth ; nCntX++)
		{
			if (aMapData[nCntZ][nCntX] == 1)
			{
				//壁の部屋
				CDungeonRoomDirector::Create(pDungeonWallBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
																				0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));
				//壁のマップを作る
				CMap::Create(D3DXVECTOR3(MAP_ROOM_SIZE * (nCntX - (nWidth - 1) / 2.0f),
					                     -MAP_ROOM_SIZE * (nCntZ - (nDepth - 1) / 2.0f),
					                     0.0f),
					         D3DXVECTOR3(MAP_ROOM_SIZE, MAP_ROOM_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::WALL);
			}
			else if (aMapData[nCntZ][nCntX] == 2)
			{
				//スタートの部屋
				CDungeonRoomDirector::Create(pDungeonStartRoadBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
																				0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));
				//スタート地点のマップを作る
				CMap::Create(D3DXVECTOR3(MAP_ROOM_SIZE * (nCntX - (nWidth - 1) / 2.0f),
					                     -MAP_ROOM_SIZE * (nCntZ - (nDepth - 1) / 2.0f),
					                     0.0f),
					         D3DXVECTOR3(MAP_ROOM_SIZE, MAP_ROOM_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::START);
			}
			else if (aMapData[nCntZ][nCntX] == 3)
			{
				//敵がいる道
				CDungeonRoomDirector::Create(pDungeonEnemyRoadBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
							                                                       0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));
				//道のマップを作る
				CMap::Create(D3DXVECTOR3(MAP_ROOM_SIZE * (nCntX - (nWidth - 1) / 2.0f),
					                     -MAP_ROOM_SIZE * (nCntZ - (nDepth - 1) / 2.0f),
					                     0.0f),
					         D3DXVECTOR3(MAP_ROOM_SIZE, MAP_ROOM_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::ROAD);
			}
			else if (aMapData[nCntZ][nCntX] == 4)
			{
				//ゴールの部屋
				CDungeonRoomDirector::Create(pDungeonEndRoadBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
																				 0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));
				//ワープのマップを作る
				CMap::Create(D3DXVECTOR3(MAP_ROOM_SIZE * (nCntX - (nWidth - 1) / 2.0f),
					                     -MAP_ROOM_SIZE * (nCntZ - (nDepth - 1) / 2.0f),
					                     0.0f),
					         D3DXVECTOR3(MAP_ROOM_SIZE, MAP_ROOM_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::WARP);
			}
			else if (aMapData[nCntZ][nCntX] == 5)
			{
				//チェックポイントがある道
				CDungeonRoomDirector::Create(pDungeonCheckRoadBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
							                                                       0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));
				//道のマップを作る
				CMap::Create(D3DXVECTOR3(MAP_ROOM_SIZE * (nCntX - (nWidth - 1) / 2.0f),
					                     -MAP_ROOM_SIZE * (nCntZ - (nDepth - 1) / 2.0f),
					                     0.0f),
					         D3DXVECTOR3(MAP_ROOM_SIZE, MAP_ROOM_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::ROAD);
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
	pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_UI);
	pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_HP_MP_SP_FRAME"));

	//HP情報を取得
	int nHp = CManager::GetInstance()->GetPlayData()->GetHitPoint();
	//HPゲージの生成
	m_pHpGauge = CGauge::Create(D3DXVECTOR3(GAUGE_HP_POS_X, GAUGE_HP_POS_Y, 0.0f),
		                        D3DXVECTOR3(GAUGE_HP_SIZE_X, GAUGE_HP_SIZE_Y, 0.0f), PLAYER_MAX_HP, nHp);
	m_pHpGauge->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_HP_GAUGE"));
	//HP情報を設定
	CManager::GetInstance()->GetPlayData()->SetHpGauge(m_pHpGauge);

	//MP情報を取得
	int nMp = CManager::GetInstance()->GetPlayData()->GetMagicPoint();
	//MPゲージの生成
	m_pMpGauge = CGauge::Create(D3DXVECTOR3(GAUGE_MP_POS_X, GAUGE_MP_POS_Y, 0.0f),
		                        D3DXVECTOR3(GAUGE_MP_SIZE_X, GAUGE_MP_SIZE_Y, 0.0f), PLAYER_MAX_MP, nMp);
	m_pMpGauge->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_MP_GAUGE"));
	//MP情報を設定
	CManager::GetInstance()->GetPlayData()->SetMpGauge(m_pMpGauge);

	//SP情報を取得
	int nSp = CManager::GetInstance()->GetPlayData()->GetSpecialPoint();
	//SPゲージの生成
	m_pSpGauge = CGauge::Create(D3DXVECTOR3(GAUGE_SP_POS_X, GAUGE_SP_POS_Y, 0.0f),
		                        D3DXVECTOR3(GAUGE_SP_SIZE_X, GAUGE_SP_SIZE_Y, 0.0f), PLAYER_MAX_SP, nSp);
	m_pSpGauge->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_SP_GAUGE"));
	//SP情報を設定
	CManager::GetInstance()->GetPlayData()->SetSpGauge(m_pSpGauge);

	//UIの生成
	pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_UI);
	pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_HP_MP_SP"));

	//タイムの生成
	CTime::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, TIME_POLIGON_POSY, 0.0f), D3DXVECTOR3(TIME_POLYGON_WIDTH, TIME_POLYGON_HEIGHT, 0.0f),
		          CManager::GetInstance()->GetPlayData()->GetTime());

	//スコアの生成
	CScore *pSocre = nullptr;
	pSocre = CScore::Create(D3DXVECTOR3(0.0f + (SCORE_POLYGON_WIDTH * MAX_SCORE_POLYGON / 2.0f), SCORE_POLYGON_HEIGHT / 2.0f, 0.0f),
							D3DXVECTOR3(SCORE_POLYGON_WIDTH, SCORE_POLYGON_HEIGHT, 0.0f));
	CManager::GetInstance()->GetPlayData()->SetScorePoint(pSocre);

	//スコアの設定
	pSocre->SetScore(CManager::GetInstance()->GetPlayData()->GetScore());

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
void CGame02::Uninit(void)
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
void CGame02::Update(void)
{
	//カウンターを加算
	m_nRecoveryCounter++;
	//既定の値以上になったら
	if (m_nRecoveryCounter >= GAME02_RECOVERYCOUNT)
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
			pFade->SetFade(CManager::MODE::GAME03);
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
void CGame02::Draw(void)
{

}

//================================================
//ゲームオーバー処理
//================================================
void CGame02::GameOver(void)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//カウンターを加算
	m_nGameCounter++;

	if (m_pObjet2DGame == nullptr)
	{
		m_pObjet2DGame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
			                               D3DXVECTOR3(GAME02_GAME_OVER_SIZE_X, GAME02_GAME_OVER_SIZE_Y, 0.0f), CObject::PRIORITY_GAME_OVER);
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
	if (m_nGameCounter > GAME02_NEXT_SCENE_COUNT)
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
