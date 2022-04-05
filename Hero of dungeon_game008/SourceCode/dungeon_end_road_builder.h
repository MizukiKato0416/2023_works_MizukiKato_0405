//===========================================
//ダンジョンの終点地点ビルダー処理
//Author:KatoMizuki
//===========================================
#ifndef _DUNGEON_END_ROAD_BUILDER_H_
#define _DUNGEON_END_ROAD_BUILDER_H_
#include "dungeon_room_builder.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CDungeonEndRoadBuilder :public CDungeonRoomBuilder
{
public:
	//メンバ関数
	CDungeonEndRoadBuilder();			//コンストラクタ
	~CDungeonEndRoadBuilder();		//デストラクタ

	void SetFloor(D3DXVECTOR3 pos);			//床の生成
	void SetPiller(D3DXVECTOR3 pos);		//柱の生成
	void SetWall(D3DXVECTOR3 pos);			//壁の生成
	void SetCheckPoint(D3DXVECTOR3 pos);	//ワープゾーンの生成

	//ダンジョンの道を出力
	CDungeonRoom *GetDungeonRoom() { return m_pDungeonRoom; }
	static CDungeonEndRoadBuilder *Create(void);					//生成処理


private:

};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_DUNGEON_END_ROAD_BUILDER_H_