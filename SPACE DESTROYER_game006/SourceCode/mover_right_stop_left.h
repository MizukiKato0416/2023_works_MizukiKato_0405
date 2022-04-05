//===========================================
//左に行き停止し右に行く動きの処理
//Authore:加藤瑞葵
//===========================================
#ifndef _MOVER_RIGHT_STOP_LEFT_H_
#define _MOVER_RIGHT_STOP_LEFT_H_
#include "mover.h"

//================================================
//マクロ定義
//================================================
#define MOVER_RIGHT_SPEED			(1.0f)		//右に進むスピード
#define MOVER_LEFT_SPEED			(-1.0f)		//左に進むスピード
#define MOVER_RIGHT_FINISH_COUNT	(300)		//右に進むのをやめるまでのカウント
#define MOVER_STOP_FINISH_COUNT		(300)		//停止をやめるまでのカウント

//================================================
//クラスの定義
//================================================
//クラスの定義
class CMoverRightStopLeft : public CMover
{
public:
	CMoverRightStopLeft();				//コンストラクタ
	~CMoverRightStopLeft();				//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CMoverRightStopLeft *Create(void);

private:
	//動きの種類
	typedef enum
	{
		MOVE_TYPE_NONE = 0,
		MOVE_TYPE_RIGHT,
		MOVE_TYPE_STOP,
		MOVE_TYPE_LEFT,
		MOVE_TYPE_MAX
	} MOVE_TYPE;

	int m_nFrameCounter;				//Frameカウント用変数
	MOVE_TYPE m_moveType;				//動きの種類
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_MOVER_RIGHT_STOP_LEFT_H_