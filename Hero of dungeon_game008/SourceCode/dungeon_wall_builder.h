//===========================================
//ダンジョンの壁ビルダー処理
//Author:KatoMizuki
//===========================================
#ifndef _DUNGEON_WALL_BUILDER_H_
#define _DUNGEON_WALL_BUILDER_H_
#include "main.h"
#include "dungeon_room_builder.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CDungeonWallBuilder :public CDungeonRoomBuilder
{
public:
	//メンバ関数
	CDungeonWallBuilder();		//コンストラクタ
	~CDungeonWallBuilder();		//デストラクタ

	void SetWall(D3DXVECTOR3 pos);			//壁の生成

	//ダンジョンの壁を出力
	CDungeonRoom *GetDungeonRoom(void) { return m_pDungeonRoom; }
	static CDungeonWallBuilder *Create(void);					//生成処理

private:

};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_DUNGEON_WALL_BUILDER_H_