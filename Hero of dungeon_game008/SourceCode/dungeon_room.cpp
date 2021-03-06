//================================================
//ダンジョンの部屋処理
//Author:KatoMizuki
//================================================
#include "dungeon_room.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CDungeonRoom::CDungeonRoom()
{
	
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CDungeonRoom::~CDungeonRoom()
{

}

//================================================
//初期化処理
//================================================
HRESULT CDungeonRoom::Init(D3DXVECTOR3 pos)
{	
	return S_OK;
}

//================================================
//終了処理
//================================================
void CDungeonRoom::Uninit(void)
{
	
}

//================================================
//更新処理
//================================================
void CDungeonRoom::Update(void)
{
	
}

//================================================
//生成処理
//================================================
CDungeonRoom *CDungeonRoom::Create(D3DXVECTOR3 pos)
{
	//インスタンスの生成
	CDungeonRoom *pDungeonRoom = nullptr;
	if (pDungeonRoom == nullptr)
	{
		pDungeonRoom = new CDungeonRoom;
		if (pDungeonRoom != nullptr)
		{
			pDungeonRoom->Init(pos);
		}
	}
	return pDungeonRoom;
}
