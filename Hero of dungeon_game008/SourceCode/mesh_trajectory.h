//===========================================
//メッシュ軌跡処理
//Author:KatoMizuki
//===========================================
#ifndef _MESH_TRAJECTORY_H_
#define _MESH_TRAJECTORY_H_
#include "object.h"
#include "main.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CMeshTrajectory : public CObject
{
public:
	CMeshTrajectory(int nPriority = PRIORITY_TRAJECTORY);	//コンストラクタ
	~CMeshTrajectory();										//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeshTrajectory *Create(int nLine, D3DXMATRIX *pMtx, D3DXVECTOR3 offset1, D3DXVECTOR3 offset2, D3DXCOLOR col1, D3DXCOLOR col2);
	
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);								//テクスチャ設定処理
	static bool CollisionSphere(CObject *pSubjectObject, float fObjectRadius);	//球と各頂点との衝突判定

private:
	LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファへのポインタ
	D3DXVECTOR3 m_aOffset[2];					//両端のオフセット
	D3DXMATRIX m_aMtxPoint[2];					//両端のワールドマトリックス
	D3DXMATRIX *m_pMtxParent;					//親のワールドマトリックスへの
	D3DXCOLOR m_aCol[2];						//両端の基準の色
	int m_nLine;								//横のポリゴンの数
	std::vector<D3DXVECTOR3> m_aPosPoint;		//各頂点座標
	std::vector<D3DXCOLOR> m_aColPoint;			//各頂点カラー
};

#endif // !_MESH_TRAJECTORY_H_