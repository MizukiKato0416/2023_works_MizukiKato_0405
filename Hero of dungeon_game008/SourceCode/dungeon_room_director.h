//===========================================
//ダンジョンの生成処理
//Author:KatoMizuki
//===========================================
#ifndef _DUNGEON_DIRECTOR_H_
#define _DUNGEON_DIRECTOR_H_
#include "main.h"

//前方宣言
class CDungeonRoomBuilder;
class CDungeonRoom;

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CDungeonRoomDirector
{
public:
	//メンバ関数
	CDungeonRoomDirector();				//コンストラクタ
	~CDungeonRoomDirector();			//デストラクタ

	//生成処理
	static CDungeonRoom *Create(CDungeonRoomBuilder *pDungeonRoomBuilder, D3DXVECTOR3 pos);
};

#endif // !_DUNGEON_DIRECTOR_H_