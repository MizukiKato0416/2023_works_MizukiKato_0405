//================================================
//ステージのビルダー処理
//Author:KatoMizuki
//================================================
#include "dungeon_wall_builder.h"
#include "model_single.h"
#include "manager.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CDungeonWallBuilder::CDungeonWallBuilder()
{
	
}

//================================================
//デストラクタ
//================================================
CDungeonWallBuilder::~CDungeonWallBuilder()
{

}

//================================================
//壁の生成
//================================================
void CDungeonWallBuilder::SetWall(D3DXVECTOR3 pos)
{
	CModelSingle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CManager::GetInstance()->GetXload()->X_TYPE_WALL_01, nullptr, true);
}

//================================================
//生成処理
//================================================
CDungeonWallBuilder *CDungeonWallBuilder::Create(void)
{
	//インスタンスの生成
	CDungeonWallBuilder *pDungeonWallBuilder = nullptr;
	if (pDungeonWallBuilder == nullptr)
	{
		pDungeonWallBuilder = new CDungeonWallBuilder;
	}
	return pDungeonWallBuilder;
}