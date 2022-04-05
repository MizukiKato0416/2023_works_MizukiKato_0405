//===========================================
//プレイヤーの状態処理
//Author:KatoMizuki
//===========================================
#ifndef _STATE_PLAYER_H_
#define _STATE_PLAYER_H_
#include "main.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CStatePlayer
{
public:
	enum class STATE_PLAYER
	{
		NONE = 0,
		NOMAL,
		DAMAGE,
		MAX
	};

	//メンバ関数
	CStatePlayer();					//コンストラクタ
	virtual ~CStatePlayer();		//デストラクタ

	//メンバ関数
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;

private:

};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_STATE_PLAYER_H_