//===========================================
//魔法陣処理
//Author:KatoMizuki
//===========================================
#ifndef _MAGIC_CIRCLE_H_
#define _MAGIC_CIRCLE_H_
#include "object3D.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CMagicCircle : public CObject3D
{
public:
	//回転軸の種類
	enum class ROTATE_TYPE
	{
		NONE = 0,
		X ,			//X軸
		Y,			//Y軸
		Z,			//Z軸
		MAX
	};

	CMagicCircle(int nPriority = PRIORITY_POLYGON_3D);		//コンストラクタ
	~CMagicCircle();										//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMagicCircle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);
	void SetRotateType(ROTATE_TYPE rotateType) { m_rotateType = rotateType; }		//回転軸設定処理

private:
	ROTATE_TYPE m_rotateType;			//回転軸の種類
};

#endif // !_MAGIC_CIRCLE_H_