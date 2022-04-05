//===========================================
//降下して右下に行く動きの処理
//Authore:加藤瑞葵
//===========================================
#ifndef _MOVER_FALL_LOWER_RIGHT_H_
#define _MOVER_FALL_LOWER_RIGHT_H_
#include "mover.h"

//================================================
//マクロ定義
//================================================
#define MOVER_FALL_LOWER_RIGHT_SPEED			(1.5f)		//下降するスピード
#define MOVER_LOWER_RIGHT_SPEED					(1.5f)		//右下に行くスピード
#define MOVER_FALL_FINISH_COUNT					(120)		//下降をやめるまでのカウント

//================================================
//クラスの定義
//================================================
//クラスの定義
class CMoverFallLowerRight : public CMover
{
public:
	CMoverFallLowerRight();				//コンストラクタ
	~CMoverFallLowerRight();				//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CMoverFallLowerRight *Create(void);

private:
	//動きの種類
	typedef enum
	{
		MOVE_TYPE_NONE = 0,
		MOVE_TYPE_FALL,
		MOVE_TYPE_LOWER_RIGHT,
		MOVE_TYPE_MAX
	} MOVE_TYPE;

	int m_nFrameCounter;				//Frameカウント用変数
	MOVE_TYPE m_moveType;				//動きの種類
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_MOVER_FALL_LOWER_RIGHT_H_