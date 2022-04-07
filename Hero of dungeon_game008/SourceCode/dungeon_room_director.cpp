//================================================
//ダンジョンの生成処理
//Author:KatoMizuki
//================================================
#include "dungeon_room_director.h"
#include "dungeon_room_builder.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CDungeonRoomDirector::CDungeonRoomDirector()
{
	
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CDungeonRoomDirector::~CDungeonRoomDirector()
{

}

//================================================
//生成処理
//================================================
CDungeonRoom *CDungeonRoomDirector::Create(CDungeonRoomBuilder *pDungeonRoomBuilder, D3DXVECTOR3 pos)
{
	pDungeonRoomBuilder->SetFloor(pos);					//床の生成
	pDungeonRoomBuilder->SetCheckPoint(pos);			//チェックポイント生成
	pDungeonRoomBuilder->SetEnemy(pos);					//敵の生成
	pDungeonRoomBuilder->SetWall(pos);					//壁の生成
	pDungeonRoomBuilder->SetPiller(pos);				//柱の生成
	return pDungeonRoomBuilder->GetDungeonRoom();
}
