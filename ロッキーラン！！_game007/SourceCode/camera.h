//=======================================================================
//カメラに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"

//========================================================
//マクロ定義
//========================================================
#define MAX_CAMERA				(2)			//カメラの最大数
#define MAX_RESULT_CAMERA		(1)			//リザルトのカメラの最大数
#define CAMERA_R_SPEED			(0.03f)		//カメラの旋回スピード
#define CAMERA_VR_SPEED			(4.0f)		//カメラの移動
#define CAMERA_DISTANCE			(300.0f)	//視点と注視点の距離
#define CAMERA_RESULT_DISTANCE	(200.0f)	//リザルトの視点と注視点の距離
#define CAMERA_V_MAX_POS_Y		(400.0f)	//視点のy座標最大値
#define CAMERA_V_MIN_POS_Y		(50.0f)		//視点のy座標最小値
#define CAMERA_MAX_RENDERER		(20000.0f)	//cameraでの描画最大Z値
#define CAMERA_MIN_RENDERER		(10.0f)		//cameraでの描画最小Z値

//================================================
//クラスの定義
//================================================
//クラスの定義
class CCamera
{
public:
	CCamera();				//コンストラクタ
	~CCamera();				//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 m_pos, D3DXVECTOR3 rot, float viewportX, float viewportY, float viewportWidth, float viewporHeight);
	void Uninit(void);
	void Update(void);
	static CCamera *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float viewportX, float viewportY, float viewportWidth, float viewporHeight);
	void Set(void);
	D3DXVECTOR3 GetPosV(void);		//視点取得処理
	D3DXVECTOR3 GetPosR(void);		//注視点取得処理
	void SetPosV(D3DXVECTOR3 pos);	//視点設定処理
	void SetPosR(D3DXVECTOR3 pos);	//注視点設定処理
	D3DXVECTOR3 GetRotV(void);		//視点の向き取得処理
	void SetRotV(D3DXVECTOR3 rot);	//視点の向き設定処理
	void SetNum(int nNum);			//cameraの個体識別番号設定処理
	int GetNum(void);				//cameraの個体識別番号取得処理
	D3DVIEWPORT9 *GetViewPort(void) { return &m_viewport; }

private:
	D3DXVECTOR3 m_posV;						//現在の視点
	D3DXVECTOR3 m_posVDest;					//目的の視点
	D3DXVECTOR3 m_posR;						//現在の注視点
	D3DXVECTOR3 m_posRDest;					//目的の注視点
	D3DXVECTOR3 m_vecU;						//上方向ベクトル
	D3DXVECTOR3 m_rot;						//視点の向き
	D3DXVECTOR3 m_rotAsk;					//目的の向き
	float m_rotDiffer;						//目的の向きとの差
	D3DXMATRIX m_mtxProjection;				//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;					//ビューマトリックス
	D3DVIEWPORT9 m_viewport;				//ビューポート
	D3DXMATRIX m_mtxWorldCamera;			//ワールドマトリックス
	bool m_bTurn;							//カメラが回転中かどうか
	int m_nNum;								//cameraの個体識別番号
};

#endif //!_CAMERA_H_

