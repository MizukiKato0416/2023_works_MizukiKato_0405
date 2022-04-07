//===========================================
//炎の弾処理
//Author:KatoMizuki
//===========================================
#ifndef _FIRE_BALL_H_
#define _FIRE_BALL_H_

#include "object.h"

//前方宣言
class CEffect3D;
class CEnemy;

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CFireBall : public CObject
{
public:
	CFireBall(int nPriority = PRIORITY_FIRE_BALL);		//コンストラクタ
	~CFireBall();										//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CFireBall *Create(D3DXVECTOR3 pos, int nRotPartitionNum, int nLayer,int nLife, float fPower, D3DXVECTOR3 move, D3DXVECTOR3 size);

private:
	int m_nRotPartitionNum;					//角度分割数
	int m_nLayer;							//層の数
	int m_nLife;							//寿命
	float m_fPower;							//y=a(x*x)のaの部分
	D3DXVECTOR3 m_move;						//移動量
	D3DXVECTOR3 m_size;						//サイズ
	D3DXVECTOR3 m_pos;						//位置
	std::vector<CEffect3D*> m_pEffect3D;	//エフェクトのポインタ
	bool m_bHoming;							//追尾するかどうか
	CEnemy *m_pTargetEnemy;					//追尾する敵のポインタ
};

#endif // !_FIRE_BALL_H_