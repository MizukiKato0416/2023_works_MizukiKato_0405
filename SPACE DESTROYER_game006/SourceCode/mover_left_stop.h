//===========================================
//左に行き停止する動きの処理
//Authore:加藤瑞葵
//===========================================
#ifndef _MOVER_LEFT_STOP_H_
#define _MOVER_LEFT_STOP_H_
#include "mover.h"

//================================================
//マクロ定義
//================================================
#define MOVER_LEFT_STOP_LEFT_SPEED			(-1.0f)		//左に進むスピード
#define MOVER_LEFT_STOP_LEFT_FINISH_COUNT	(300)		//左に進むのをやめるまでのカウント

//================================================
//クラスの定義
//================================================
//クラスの定義
class CMoverLeftStop : public CMover
{
public:
	CMoverLeftStop();				//コンストラクタ
	~CMoverLeftStop();				//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CMoverLeftStop *Create(void);

private:
	//動きの種類
	typedef enum
	{
		MOVE_TYPE_NONE = 0,
		MOVE_TYPE_LEFT,
		MOVE_TYPE_STOP,
		MOVE_TYPE_MAX
	} MOVE_TYPE;

	int m_nFrameCounter;				//Frameカウント用変数
	MOVE_TYPE m_moveType;				//動きの種類
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_MOVER_LEFT_STOP_H_