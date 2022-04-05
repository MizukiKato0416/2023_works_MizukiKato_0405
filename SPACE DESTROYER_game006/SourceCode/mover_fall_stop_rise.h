//===========================================
//降下して停止し上昇する動きの処理
//Authore:加藤瑞葵
//===========================================
#ifndef _MOVER_FALL_STOP_RISE_H_
#define _MOVER_FALL_STOP_RISE_H_
#include "mover.h"

//================================================
//マクロ定義
//================================================
#define MOVER_FALL_SPEED			(1.0f)		//下降するスピード
#define MOVER_RISE_SPEED			(-1.0f)		//上昇するスピード
#define MOVER_FALL_FINISH_COUNT		(120)		//下降をやめるまでのカウント
#define MOVER_STOP_FINISH_COUNT		(300)		//停止をやめるまでのカウント

//================================================
//クラスの定義
//================================================
//クラスの定義
class CMoverFallStopRise : public CMover
{
public:
	CMoverFallStopRise();				//コンストラクタ
	~CMoverFallStopRise();				//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CMoverFallStopRise *Create(void);

private:
	//動きの種類
	typedef enum
	{
		MOVE_TYPE_NONE = 0,
		MOVE_TYPE_FALL,
		MOVE_TYPE_STOP,
		MOVE_TYPE_RISE,
		MOVE_TYPE_MAX
	} MOVE_TYPE;

	int m_nFrameCounter;				//Frameカウント用変数
	MOVE_TYPE m_moveType;				//動きの種類
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_MOVER_FALL_STOP_RISE_H_