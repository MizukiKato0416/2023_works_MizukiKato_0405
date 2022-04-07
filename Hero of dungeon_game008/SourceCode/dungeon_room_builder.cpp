//================================================
//ステージのビルダー処理
//Author:KatoMizuki
//================================================
#include "dungeon_room_builder.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CDungeonRoomBuilder::CDungeonRoomBuilder()
{
	
}

//================================================
//デストラクタ
//================================================
CDungeonRoomBuilder::~CDungeonRoomBuilder()
{

}

//================================================
//生成処理
//================================================
CDungeonRoomBuilder *CDungeonRoomBuilder::Create(void)
{
	//インスタンスの生成
	CDungeonRoomBuilder *pDungeonRoomBuilder = nullptr;
	if (pDungeonRoomBuilder == nullptr)
	{
		pDungeonRoomBuilder = new CDungeonRoomBuilder;
	}
	return pDungeonRoomBuilder;
}
