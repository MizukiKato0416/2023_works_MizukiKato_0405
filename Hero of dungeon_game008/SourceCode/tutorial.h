//===========================================
//チュートリアル処理
//Author:KatoMizuki
//===========================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "object.h"

//前方宣言
class CObject2D;

//================================================
//マクロ定義
//================================================
#define TUTORIAL_MAX_TYPE		(2)		//チュートリアルの種類

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CTutorial : public CObject
{
public:
	CTutorial(int nPriority = PRIORITY_NONE);		//コンストラクタ
	~CTutorial();									//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CObject2D *m_pObject2D[TUTORIAL_MAX_TYPE];	//object2Dのポインタ
};

#endif // !_TUTORIAL_H_