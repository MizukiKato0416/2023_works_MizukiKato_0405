//===========================================
//プレイヤー処理
//Author:KatoMizuki
//===========================================
#ifndef _DUNGEON_ROOM_H_
#define _DUNGEON_ROOM_H_
#include "main.h"
//前方宣言

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CDungeonRoom
{
public:
	CDungeonRoom();				//コンストラクタ
	~CDungeonRoom();			//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	static CDungeonRoom *Create(D3DXVECTOR3 pos);

};

#endif // !_DUNGEON_ROOM_H_