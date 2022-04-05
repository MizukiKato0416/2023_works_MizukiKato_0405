//===========================================
//ワープ魔法陣処理
//Author:KatoMizuki
//===========================================
#ifndef _WARP_CIRCLE_H_
#define _WARP_CIRCLE_H_
#include "magic_circle.h"

//前方宣言
class CUi;

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CWarpCircle : public CMagicCircle
{
public:
	CWarpCircle(int nPriority = PRIORITY_POLYGON_3D);		//コンストラクタ
	~CWarpCircle();											//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CWarpCircle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);

private:
	//メンバ関数
	bool CollisionPlayer(void);		//プレイヤーとの当たり判定
	void EffectSpawn(void);			//エフェクト生成処理
	void Object3DSpawn(void);		//上に上がる3Dオブジェクト生成処理

	int m_nEffectCounter;			//エフェクトを出す頻度のカウンター
	int m_nObject3DCounter;			//上に上がるobject3Dを出す頻度のカウンター
	CObject3D *m_pObject3D;			//object3Dのポインタ
	CUi *m_pUiMessage;				//メッセージUIのポインタ
};

#endif // !_WARP_CIRCLE_H_