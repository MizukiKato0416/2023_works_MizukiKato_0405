//===========================================
//降下して左下に行く動きの処理
//Authore:加藤瑞葵
//===========================================
#ifndef _MOVER_FALL_LOWER_LEFT_H_
#define _MOVER_FALL_LOWER_LEFT_H_
#include "mover.h"

//================================================
//マクロ定義
//================================================
#define MOVER_LOWER_LEFT_FALL_SPEED		(1.5f)		//下降するスピード
#define MOVER_LOWER_LEFT_SPEED			(1.5f)		//左下に行くスピード
#define MOVER_FALL_FINISH_COUNT			(120)		//下降をやめるまでのカウント

//================================================
//クラスの定義
//================================================
//クラスの定義
class CMoverFallLowerLeft : public CMover
{
public:
	CMoverFallLowerLeft();				//コンストラクタ
	~CMoverFallLowerLeft();				//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CMoverFallLowerLeft *Create(void);

private:
	//動きの種類
	typedef enum
	{
		MOVE_TYPE_NONE = 0,
		MOVE_TYPE_FALL,
		MOVE_TYPE_LOWER_LEFT,
		MOVE_TYPE_MAX
	} MOVE_TYPE;

	int m_nFrameCounter;				//Frameカウント用変数
	MOVE_TYPE m_moveType;				//動きの種類
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_MOVER_FALL_LOWER_LEFT_H_