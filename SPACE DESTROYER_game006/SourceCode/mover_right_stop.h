//===========================================
//左に行き停止する動きの処理
//Authore:加藤瑞葵
//===========================================
#ifndef _MOVER_RIGHT_STOP_H_
#define _MOVER_RIGHT_STOP_H_
#include "mover.h"

//================================================
//マクロ定義
//================================================
#define MOVER_RIGHT_STOP_RIGHT_SPEED			(1.0f)		//右に進むスピード
#define MOVER_RIGHT_STOP_RIGHT_FINISH_COUNT		(300)		//右に進むのをやめるまでのカウント

//================================================
//クラスの定義
//================================================
//クラスの定義
class CMoverRightStop : public CMover
{
public:
	CMoverRightStop();				//コンストラクタ
	~CMoverRightStop();				//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CMoverRightStop *Create(void);

private:
	//動きの種類
	typedef enum
	{
		MOVE_TYPE_NONE = 0,
		MOVE_TYPE_RIGHT,
		MOVE_TYPE_STOP,
		MOVE_TYPE_MAX
	} MOVE_TYPE;

	int m_nFrameCounter;				//Frameカウント用変数
	MOVE_TYPE m_moveType;				//動きの種類
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_MOVER_RIGHT_STOP_H_