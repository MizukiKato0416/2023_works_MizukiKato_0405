//===========================================
//降下ながらランダムで左右に行く動きの処理
//Authore:加藤瑞葵
//===========================================
#ifndef _MOVER_FALL_RANDOM_RIGHT_LEFT_H_
#define _MOVER_FALL_RANDOM_RIGHT_LEFT_H_
#include "mover.h"

//================================================
//マクロ定義
//================================================
#define MOVER_FALL_RANDOM_RIGHT_LEFT_SPEED			(2.0f)					//下降するスピード
#define MOVER_RANDOM_RIGHT_LEFT_SPEED				(2.0f)					//左右下に行くスピード
#define MOVER_RIGHT_LEFT_FINISH_COUNT				(rand() % 1020 + 60)	//移動量を変えるタイミングのカウント

//================================================
//クラスの定義
//================================================
//クラスの定義
class CMoverFallRandomRightLeft : public CMover
{
public:
	CMoverFallRandomRightLeft();				//コンストラクタ
	~CMoverFallRandomRightLeft();				//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CMoverFallRandomRightLeft *Create(void);

private:
	//動きの種類
	typedef enum
	{
		MOVE_TYPE_NONE = 0,
		MOVE_TYPE_LOWER_LEFT,	//左下
		MOVE_TYPE_LOWER_RIGHT,	//右下
		MOVE_TYPE_MAX
	} MOVE_TYPE;

	int m_nFrameCounter;				//Frameカウント用変数
	MOVE_TYPE m_moveType;				//動きの種類
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_MOVER_FALL_RANDOM_RIGHT_LEFT_H_