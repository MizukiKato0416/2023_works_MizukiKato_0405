//===========================================
//モデル単体を出す処理
//Author:加藤瑞葵
//===========================================
#ifndef _MODEL_SINGLE_H_
#define _MODEL_SINGLE_H_
#include "scene.h"
#include "x_load.h"
#include "scene.h"

//前方宣言
class CModel;
class CControl;

//================================================
//マクロ定義
//================================================
#define MODEL_SINGLE_DELETE_TIME	(240)	//消えている時間

//================================================
//クラスの定義
//================================================
//クラスの定義
class CModelSingle : public CScene
{
public:
	//モデルの動きの種類
	typedef enum
	{
		MODEL_SINGLE_TYPE_NONE = 0,
		MODEL_SINGLE_TYPE_UP_WALL,			//上下する壁(上方向から移動)
		MODEL_SINGLE_TYPE_DOWN_WALL,		//上下する壁(下方向から移動)
		MODEL_SINGLE_TYPE_UNINIT_FLOOR,		//なくなる床
		MODEL_SINGLE_TYPE_GOAL,				//ゴールの床
		MODEL_SINGLE_TYPE_START_FLOOR,		//スタートの床
		MODEL_SINGLE_TYPE_MIDDLE1_FLOOR,	//中間地点1の床
		MODEL_SINGLE_TYPE_MIDDLE2_FLOOR,	//中間地点2の床
		MODEL_SINGLE_TYPE_ICE_FLOOR,		//氷の床
		MODEL_SINGLE_TYPE_SPRING,			//バネ
		MODEL_SINGLE_TYPE_MAX
	} MODEL_SINGLE_TYPE;

	CModelSingle(int nPriority = PRIORITY_MODEL);				//コンストラクタ
	~CModelSingle();											//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CModelSingle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CXload::X_TYPE type, CModel *pParent, MODEL_SINGLE_TYPE modelType);
	static bool SimpleCollision(CScene *pScene);	//回転させたらダメな当たり判定
	bool GetDeleteObject(void);						//消えたかどうかの取得処理

private:
	//メンバ関数

	D3DXVECTOR3 m_pos;								//位置
	D3DXVECTOR3 m_posOld;							//1フレーム前の位置
	D3DXVECTOR3 m_move;								//ポリゴンの移動量
	D3DXVECTOR3	m_size;								//サイズ
	D3DXVECTOR3 m_rot;								//向き
	CModel *m_pModel;								//モデルのポインタ
	D3DXMATRIX m_mtxWorld;							//ワールドマトリックス
	CModel *m_pParent;								//親モデルへのポインタ
	CXload::X_TYPE m_type;							//出すモデルの種類
	MODEL_SINGLE_TYPE m_modelType;					//モデルの動きの種類
	bool m_bDelete;									//消えているかどうか
	int m_nCntDelete;								//消えてからどれくらいたつか
	CControl *m_pControl;							//コントロールクラスのポインタ
};

#endif // !_MODEL_SINGLE_H_