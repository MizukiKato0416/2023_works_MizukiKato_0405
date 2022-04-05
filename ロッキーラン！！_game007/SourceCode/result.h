//===========================================
//リザルト処理
//Author:一戸健
//===========================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"
#include "player.h"

//================================================
//前方宣言
//================================================
class CRanking;
class CScene2D;
class CMeshField;
class CMeshSphere;
class CModelSingle;
class CUi;

//================================================
//マクロ定義
//================================================
#define RESULT_TO_TITLE_COUNT			(900)				//タイトルに行くまでの間隔
#define RESULT_RANKING_POSY				(60.0f)				//ランキングのposY
#define RESULT_MAX_MODEL				(60)				//リザルトのモデル最大数
#define RESULT_MAX_UI					(2)					//リザルトのUI最大数
#define RESULT_PLAYERNUMBER_SIZE_X		(360.0f * 1.6f)		//プレイヤーナンバーのサイズX
#define RESULT_PLAYERNUMBER_SIZE_Y		(300.0f * 1.6f)		//プレイヤーナンバーのサイズY
#define RESULT_PLAYERNUMBER_POS_X		(450.0f)			//プレイヤーナンバーの位置X
#define RESULT_PLAYERNUMBER_POS_Y		(200.0f)			//プレイヤーナンバーの位置Y
#define RESULT_WIN_SIZE_X				(1637.0f * 0.6f)	//WINUIのサイズX
#define RESULT_WIN_SIZE_Y				(415.0f * 0.6f)		//WINUIのサイズY
#define RESULT_WIN_POS_X				(800.0f)			//WINUIの位置X
#define RESULT_WIN_POS_Y				(200.0f)			//WINUIの位置Y
#define RESULT_WORLD_SIZE				(20000.0f)			//世界の大きさ

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CResult : public CScene
{
public:
	CResult();				//コンストラクタ
	~CResult();				//デストラクタ

							//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nTitleCounter;								//タイトルに行くまでのカウンター
	CRanking *m_pRanking;								//ランキングのポインタ
	CMeshField *m_pMeshField;							//メッシュフィールドのポインタ
	CMeshSphere *m_pMeshSphere;							//メッシュスフィアのポインタ
	CPlayer *m_apPlayer[MAX_PLAYER];					//プレイヤーのポインタ
	CModelSingle *m_apModelSingle[RESULT_MAX_MODEL];	//モデルのポインタ
	CScene2D *m_pScene2D;								//Scene2Dのポインタ
	CUi *m_apUi[RESULT_MAX_UI];							//UIのポインタ
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_RESULT_H_