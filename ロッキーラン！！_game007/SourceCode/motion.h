//===========================================
//モーション処理
//Author:加藤瑞葵
//===========================================
#ifndef _MOTION_H_
#define _MOTION_H_
#include "main.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CMotion
{
public:
	CMotion();			//コンストラクタ
	~CMotion();			//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);

private:

};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_MOTION_H_