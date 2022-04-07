//===========================================
//火の粉の処理
//Author:KatoMizuki
//===========================================
#ifndef _SPARK_H_
#define _SPARK_H_

#include "object.h"

//前方宣言
class CEffect3D;

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CSpark : public CObject
{
public:
	CSpark(int nPriority = PRIORITY_SPARK);		//コンストラクタ
	~CSpark();									//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//位置、サイズ、エフェクトの数、色、初速ランダム最小値、初速ランダム最大値、重力、α値減算量ランダム最小値、α値減算量ランダム最大値、移動量減算値
	static CSpark *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumEffect, D3DXCOLOR col, float fMoveMin, float fMoveMax,
		                  float fGravity, float fColAMin, float fColAMax, float fSubtractionMove);

private:
	std::vector<CEffect3D*> m_pEffect3D;		//エフェクトのポインタ
	D3DXVECTOR3 m_size;							//エフェクトのサイズ
	std::vector<float> m_fInitMove;				//初速
	std::vector<float> m_fRotX;					//移動する方向
	std::vector<float> m_fRotY;					//移動する方向
	D3DXCOLOR m_col;							//エフェクトの色
	int m_nNumEffect;							//エフェクトの数
	float m_fGravity;							//重力
	int m_nColAMin;					    		//α値減算量ランダム最小値
	int m_nColAMax;					    		//α値減算量ランダム最大値
	float m_fSubtractionMove;					//移動量減算値
};

#endif // !_SPARK_H_