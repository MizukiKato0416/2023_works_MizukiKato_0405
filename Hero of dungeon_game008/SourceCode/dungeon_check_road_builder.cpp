//================================================
//ステージのチェックポイントがある道ビルダー処理
//Author:KatoMizuki
//================================================
#include "dungeon_check_road_builder.h"
#include "model_single.h"
#include "manager.h"
#include "check_circle.h"
#include "floor.h"
#include "texture.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CDungeonCheckRoadBuilder::CDungeonCheckRoadBuilder()
{
	
}

//================================================
//デストラクタ
//================================================
CDungeonCheckRoadBuilder::~CDungeonCheckRoadBuilder()
{

}

//================================================
//床の生成
//================================================
void CDungeonCheckRoadBuilder::SetFloor(D3DXVECTOR3 pos)
{
	CFloor *pFloor = nullptr;
	pFloor = CFloor::Create(pos, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE, 0.0f, DUNGEON_ROOM_BUILDER_SIZE), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pFloor->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_DUNGEON_FLOOR"));
}

//================================================
//チェックポイント生成
//================================================
void CDungeonCheckRoadBuilder::SetCheckPoint(D3DXVECTOR3 pos)
{
	CCheckCircle *pCheckCircle = nullptr;
	pCheckCircle = CCheckCircle::Create(D3DXVECTOR3(pos.x, pos.y + 0.1f, pos.z), D3DXVECTOR3(200.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pCheckCircle->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_CHECK_POINT"));
	pCheckCircle->SetCol(D3DXCOLOR(0.3f, 1.0f, 0.0f, 1.0f));
}

//================================================
//柱の生成
//================================================
void CDungeonCheckRoadBuilder::SetPiller(D3DXVECTOR3 pos)
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
CDungeonCheckRoadBuilder *CDungeonCheckRoadBuilder::Create(void)
{
	//インスタンスの生成
	CDungeonCheckRoadBuilder *pDungeonCheckRoadBuilder = nullptr;
	if (pDungeonCheckRoadBuilder == nullptr)
	{
		pDungeonCheckRoadBuilder = new CDungeonCheckRoadBuilder;
	}
	return pDungeonCheckRoadBuilder;
}