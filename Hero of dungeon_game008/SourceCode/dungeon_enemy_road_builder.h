//===========================================
//ダンジョンの敵がいる道ビルダー処理
//Author:KatoMizuki
//===========================================
#ifndef _DUNGEON_ENEMY_ROAD_BUILDER_H_
#define _DUNGEON_ENEMY_ROAD_BUILDER_H_
#include "dungeon_room_builder.h"

//================================================
//マクロ定義
//================================================
#define DUNGEON_ENEMY_ROAD_BUILDER_ENEMY_NUM		(3)			//出す敵の数
#define DUNGEON_ENEMY_ROAD_BUILDER_ENEMY_POS		(100.0f)	//出す敵の位置調整値

//================================================
//クラスの定義
//================================================
//クラスの定義
class CDungeonEnemyRoadBuilder :public CDungeonRoomBuilder
{
public:
	//メンバ関数
	CDungeonEnemyRoadBuilder();			//コンストラクタ
	~CDungeonEnemyRoadBuilder();		//デストラクタ

	void SetFloor(D3DXVECTOR3 pos);			//床の生成
	void SetEnemy(D3DXVECTOR3 pos);			//敵の生成
	void SetPiller(D3DXVECTOR3 pos);		//柱の生成

	//ダンジョンの道を出力
	CDungeonRoom *GetDungeonRoom() { return m_pDungeonRoom; }
	static CDungeonEnemyRoadBuilder *Create(void);					//生成処理


private:

};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_DUNGEON_ENEMY_ROAD_BUILDER_H_