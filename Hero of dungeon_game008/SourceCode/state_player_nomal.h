//===========================================
//プレイヤーの通常状態処理
//Author:KatoMizuki
//===========================================
#ifndef _STATE_PLAYER_NOMAL_H_
#define _STATE_PLAYER_NOMAL_H_
#include "main.h"
#include "state_player.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CStatePlayerNomal:public CStatePlayer
{
public:
	//メンバ関数
	CStatePlayerNomal();		//コンストラクタ
	~CStatePlayerNomal();		//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:

};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_STATE_PLAYER_NOMAL_H_