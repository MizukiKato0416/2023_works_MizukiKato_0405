//===========================================
//ステージのビルダー処理
//Author:KatoMizuki
//===========================================
#ifndef _DUNGEON_ROOM_BUILDER_H_
#define _DUNGEON_ROOM_BUILDER_H_
#include "main.h"
#include "dungeon_room.h"

//================================================
//マクロ定義
//================================================
#define DUNGEON_ROOM_BUILDER_SIZE		(1000.0f)			//部屋のサイズ

//================================================
//クラスの定義
//================================================
//クラスの定義
class CDungeonRoomBuilder
{
public:
	//メンバ関数
	CDungeonRoomBuilder();		//コンストラクタ
	~CDungeonRoomBuilder();		//デストラクタ

	virtual void SetFloor(D3DXVECTOR3 pos) {}					//床の生成
	virtual void SetCheckPoint(D3DXVECTOR3 pos) {}				//チェックポイント生成
	virtual void SetEnemy(D3DXVECTOR3 pos) {}					//敵の生成
	virtual void SetWall(D3DXVECTOR3 pos) {}					//壁の生成
	virtual void SetPiller(D3DXVECTOR3 pos) {}					//柱の生成
	virtual CDungeonRoom *GetDungeonRoom() { return NULL; }		//ダンジョンの部屋を出力
	static CDungeonRoomBuilder *Create(void);					//生成処理

protected:
	CDungeonRoom *m_pDungeonRoom;	//ダンジョンの部屋のポインタ
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_DUNGEON_ROOM_BUILDER_H_