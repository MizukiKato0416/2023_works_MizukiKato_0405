//===========================================
//炎魔法処理
//Author:KatoMizuki
//===========================================
#ifndef _MAGIC_FIRE_H_
#define _MAGIC_FIRE_H_

#include "object.h"

//前方宣言
class CMagicCircle;
class CFireBall;

//================================================
//マクロ定義
//================================================
#define MAGIC_FIRE_BALL_MOVE				(15.0f)		//移動量

//================================================
//クラスの定義
//================================================
//クラスの定義
class CMagicFire : public CObject
{
public:
	CMagicFire(int nPriority = PRIORITY_MAGIC);			//コンストラクタ
	~CMagicFire();										//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMagicFire *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	CMagicCircle *m_pMagicCircle;		//魔法陣のポインタ
	CFireBall *m_pFireBall;				//火球のポインタ
	int m_nCounter;						//魔法陣のカウンター
	D3DXVECTOR3 m_rot;					//向き
};

#endif // !_MAGIC_FIRE_H_