//===========================================
//動きの処理
//Authore:加藤瑞葵
//===========================================
#ifndef _MOVER_H_
#define _MOVER_H_

#include "main.h"

//================================================
//マクロ定義
//================================================


//================================================
//クラスの定義
//================================================
//クラスの定義
class CMover
{
public:
	//動きの種類
	typedef enum
	{
		MOVER_TYPE_NONE = 0,
		MOVER_TYPE_FALL_STOP_RISE,			//下降して停止し上昇する
		MOVER_TYPE_RIGHT_STOP_LEFT,			//右に行き停止し左に行く
		MOVER_TYPE_LEFT_STOP_RIGHT,			//左に行き停止し右に行く
		MOVER_TYPE_FALL_LOWER_LEFT,			//下降して左下に降下
		MOVER_TYPE_FALL_LOWER_RIGHT,		//下降して右下に降下
		MOVER_TYPE_FALL_RANDOM_RIGHT_LEFT,	//下降しながら左右に不規則に移動
		MOVER_TYPE_RIGHT_STOP,				//右に行き停止
		MOVER_TYPE_LEFT_STOP,				//左に行き停止
		MOVER_TYPE_MAX
	} MOVER_TYPE;

	CMover();						//コンストラクタ
	virtual ~CMover();				//デストラクタ

	//メンバ関数
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	D3DXVECTOR3 GetMove(void);					//移動量取得処理
	
protected:
	D3DXVECTOR3 m_move;			//移動量
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_MOVER_H_