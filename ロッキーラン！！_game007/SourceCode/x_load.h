//=============================================================================
//xファイルロード処理
//Authore:加藤瑞葵
//=============================================================================
#ifndef _X_LOAD_H_
#define _X_LOAD_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "main.h"

//=============================================================================
// クラス定義
//=============================================================================
class CXload
{
public:
	//タイプ
	typedef enum
	{
		X_TYPE_PLAYER_BODY = 0,					//プレイヤーの体
		X_TYPE_PLAYER_ARM_R,					//プレイヤーの右腕
		X_TYPE_PLAYER_ARM_L,					//プレイヤーの左腕
		X_TYPE_PLAYER_LEG_R,					//プレイヤーの右足
		X_TYPE_PLAYER_LEG_L,					//プレイヤーの右足
		X_TYPE_PLAYER_GIRL_BODY,				//プレイヤー女の子の体
		X_TYPE_PLAYER_GIRL_ARM_R,				//プレイヤー女の子の右腕
		X_TYPE_PLAYER_GIRL_ARM_L,				//プレイヤー女の子の左腕
		X_TYPE_PLAYER_GIRL_LEG_R,				//プレイヤー女の子の右足
		X_TYPE_PLAYER_GIRL_LEG_L,				//プレイヤー女の子の右足
		X_TYPE_TUTORIAL_START_FLOOR,            //チュートリアルのスタートの床
		X_TYPE_TUTORIAL_MIDDLE_FLOOR,           //チュートリアルのミドルの床
		X_TYPE_TUTORIAL_GOAL_FLOOR,             //チュートリアルのゴールの床
		X_TYPE_TUTORIAL_MIDDLE_FENCE,           //チュートリアルのミドルの柵
		X_TYPE_TUTORIAL_SIDEFENCE,              //チュートリアルのスタートとゴールのサイド柵
		X_TYPE_TUTORIAL_BACKFENCE,              //チュートリアルのスタートとゴールの後ろ柵
		X_TYPE_TUTORIAL_GOAL_POLE,              //チュートリアルのゴールの柱
		X_TYPE_TUTORIAL_GOAL_FLAG,              //チュートリアルのゴールの旗
		X_TYPE_GAME_SCAFFOLD,                   //ステージの足場
		X_TYPE_GAME_WALL_UPDOWN,                //ステージの上下壁
		X_TYPE_GAME_WALL_PILLAR,                //ステージの上下壁の柱
		X_TYPE_GAME_FLOOR_DISAPPEAR,            //ステージの消える床
		X_TYPE_GAME_FLOOR_ICE,				    //ステージの滑る床（氷）
		X_TYPE_GAME_SPRING,				        //ステージのバネ
		X_TYPE_RESULT_CROWN,				    //リザルトの王冠
		X_TYPE_CLOUD,							//雲
		X_TYPE_BALLOON,							//気球
		X_TYPE_AIRSHIP,							//飛行船
		X_TYPE_ARROW,							//矢印
		X_TYPE_CHECKPOINT,						//チェックポイント
		X_TYPE_MAX								//テクスチャの最大数
	} X_TYPE;

	CXload();									//コンストラクタ
	~CXload();									//デストラクタ

	void Init(void);							// テクスチャの生成
	LPD3DXMESH GetMesh(X_TYPE type);			// メッシュの割り当て
	LPD3DXBUFFER GetBuffMat(X_TYPE type);		// マテリアルの割り当て
	DWORD GetNumMat(X_TYPE type);				// マテリアル数の割り当て
	void Uninit(void);							// 終了
private:
	LPD3DXMESH m_apMesh[X_TYPE_MAX];			//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER m_apBuffMat[X_TYPE_MAX];		//マテリアル(材質情報)へのポインタ
	DWORD m_aNumMat[X_TYPE_MAX];				//マテリアル数
};

#endif