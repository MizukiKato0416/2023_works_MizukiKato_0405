//================================================
//ステージのボスがいる道のビルダー処理
//Author:KatoMizuki
//================================================
#include "dungeon_boss_road_builder.h"
#include "model_single.h"
#include "manager.h"
#include "floor.h"
#include "texture.h"
#include "enemy_boss.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CDungeonBossRoadBuilder::CDungeonBossRoadBuilder()
{
	
}

//================================================
//デストラクタ
//================================================
CDungeonBossRoadBuilder::~CDungeonBossRoadBuilder()
{

}

//================================================
//床の生成
//================================================
void CDungeonBossRoadBuilder::SetFloor(D3DXVECTOR3 pos)
{
	CFloor *pFloor = nullptr;
	pFloor = CFloor::Create(pos, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE, 0.0f, DUNGEON_ROOM_BUILDER_SIZE), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pFloor->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_DUNGEON_FLOOR"));
}

//================================================
//敵の生成
//================================================
void CDungeonBossRoadBuilder::SetEnemy(D3DXVECTOR3 pos)
{
	CEnemyBoss::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//================================================
//柱の生成
//================================================
void CDungeonBossRoadBuilder::SetPiller(D3DXVECTOR3 pos)
{
	CModelSingle::Create(D3DXVECTOR3(pos.x -500.0f + 50.0f, pos.y, pos.z + 500.0f - 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						 CManager::GetInstance()->GetXload()->X_TYPE_PILLER_01, nullptr, true);
	CModelSingle::Create(D3DXVECTOR3(pos.x -500.0f + 50.0f, pos.y, pos.z - 500.0f + 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						 CManager::GetInstance()->GetXload()->X_TYPE_PILLER_01, nullptr, true);
	CModelSingle::Create(D3DXVECTOR3(pos.x + 500.0f - 50.0f, pos.y, pos.z + 500.0f - 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						 CManager::GetInstance()->GetXload()->X_TYPE_PILLER_01, nullptr, true);
	CModelSingle::Create(D3DXVECTOR3(pos.x + 500.0f - 50.0f, pos.y, pos.z - 500.0f + 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						 CManager::GetInstance()->GetXload()->X_TYPE_PILLER_01, nullptr, true);
}

//================================================
//生成処理
//================================================
CDungeonBossRoadBuilder *CDungeonBossRoadBuilder::Create(void)
{
	//インスタンスの生成
	CDungeonBossRoadBuilder *pDungeonBossRoadBuilder = nullptr;
	if (pDungeonBossRoadBuilder == nullptr)
	{
		pDungeonBossRoadBuilder = new CDungeonBossRoadBuilder;
	}
	return pDungeonBossRoadBuilder;
}