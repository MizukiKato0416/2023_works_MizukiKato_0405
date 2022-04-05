//===========================================
//UI処理
//Authore:加藤瑞葵
//===========================================
#ifndef _UI_H_
#define _UI_H_
#include "scene2D.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CUi : public CScene2D
{
public:
	CUi(int nPriority = PRIORITY_UI);				//コンストラクタ
	~CUi();											//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_UI_H_