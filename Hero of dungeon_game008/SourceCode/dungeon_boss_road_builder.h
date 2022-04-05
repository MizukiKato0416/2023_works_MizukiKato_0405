//===========================================
//ダンジョンのボスがいる道ビルダー処理
//Author:KatoMizuki
//===========================================
#ifndef _DUNGEON_BOSS_ROAD_BUILDER_H_
#define _DUNGEON_BOSS_ROAD_BUILDER_H_
#include "dungeon_room_builder.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CDungeonBossRoadBuilder :public CDungeonRoomBuilder
{
public:
	//メンバ関数
	CDungeonBossRoadBuilder();		//コンストラクタ
	~CDungeonBossRoadBuilder();		//デストラクタ

	void SetFloor(D3DXVECTOR3 pos);			//床の生成
	void SetEnemy(D3DXVECTOR3 pos);			//敵の生成
	void SetPiller(D3DXVECTOR3 pos);		//柱の生成

	//ダンジョンの道を出力
	CDungeonRoom *GetDungeonRoom() { return m_pDungeonRoom; }
	static CDungeonBossRoadBuilder *Create(void);					//生成処理

private:

};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_DUNGEON_BOSS_ROAD_BUILDER_H_