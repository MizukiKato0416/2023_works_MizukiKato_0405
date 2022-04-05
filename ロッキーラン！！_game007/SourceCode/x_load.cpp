//=============================================================================
//Xファイル読み込み処理
//Authore:加藤瑞葵
//=============================================================================
#include "x_load.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CXload::CXload()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CXload::~CXload()
{

}

//=============================================================================
//テクスチャの生成
//=============================================================================
void CXload::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();	//デバイスを取得する

	//Xファイル読み込み

	//プレイヤーの体
	D3DXLoadMeshFromX("data/MODEL/body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_BODY], NULL, &m_aNumMat[X_TYPE_PLAYER_BODY], &m_apMesh[X_TYPE_PLAYER_BODY]);

	//プレイヤーの右腕
	D3DXLoadMeshFromX("data/MODEL/armR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_ARM_R], NULL, &m_aNumMat[X_TYPE_PLAYER_ARM_R], &m_apMesh[X_TYPE_PLAYER_ARM_R]);

	//プレイヤーの左腕
	D3DXLoadMeshFromX("data/MODEL/armL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_ARM_L], NULL, &m_aNumMat[X_TYPE_PLAYER_ARM_L], &m_apMesh[X_TYPE_PLAYER_ARM_L]);

	//プレイヤーの右足
	D3DXLoadMeshFromX("data/MODEL/legsR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_LEG_R], NULL, &m_aNumMat[X_TYPE_PLAYER_LEG_R], &m_apMesh[X_TYPE_PLAYER_LEG_R]);

	//プレイヤーの左足
	D3DXLoadMeshFromX("data/MODEL/legsL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_LEG_L], NULL, &m_aNumMat[X_TYPE_PLAYER_LEG_L], &m_apMesh[X_TYPE_PLAYER_LEG_L]);

	//プレイヤー女の子の体
	D3DXLoadMeshFromX("data/MODEL/girlBody.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_GIRL_BODY], NULL, &m_aNumMat[X_TYPE_PLAYER_GIRL_BODY], &m_apMesh[X_TYPE_PLAYER_GIRL_BODY]);

	//プレイヤー女の子の右腕
	D3DXLoadMeshFromX("data/MODEL/girlArmR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_GIRL_ARM_R], NULL, &m_aNumMat[X_TYPE_PLAYER_GIRL_ARM_R], &m_apMesh[X_TYPE_PLAYER_GIRL_ARM_R]);

	//プレイヤー女の子の左腕
	D3DXLoadMeshFromX("data/MODEL/girlArmL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_GIRL_ARM_L], NULL, &m_aNumMat[X_TYPE_PLAYER_GIRL_ARM_L], &m_apMesh[X_TYPE_PLAYER_GIRL_ARM_L]);

	//プレイヤー女の子の右足
	D3DXLoadMeshFromX("data/MODEL/girlLegsR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_GIRL_LEG_R], NULL, &m_aNumMat[X_TYPE_PLAYER_GIRL_LEG_R], &m_apMesh[X_TYPE_PLAYER_GIRL_LEG_R]);

	//プレイヤー女の子の左足
	D3DXLoadMeshFromX("data/MODEL/girlLegsL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_GIRL_LEG_L], NULL, &m_aNumMat[X_TYPE_PLAYER_GIRL_LEG_L], &m_apMesh[X_TYPE_PLAYER_GIRL_LEG_L]);

	//チュートリアルのスタートの床
	D3DXLoadMeshFromX("data/MODEL/TUTORIAL/start_floor.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_TUTORIAL_START_FLOOR], NULL, &m_aNumMat[X_TYPE_TUTORIAL_START_FLOOR], &m_apMesh[X_TYPE_TUTORIAL_START_FLOOR]);

	//チュートリアルのミドルの床
	D3DXLoadMeshFromX("data/MODEL/TUTORIAL/middle_floor.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_TUTORIAL_MIDDLE_FLOOR], NULL, &m_aNumMat[X_TYPE_TUTORIAL_MIDDLE_FLOOR], &m_apMesh[X_TYPE_TUTORIAL_MIDDLE_FLOOR]);

	//チュートリアルのゴールの床
	D3DXLoadMeshFromX("data/MODEL/TUTORIAL/goal_floor.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_TUTORIAL_GOAL_FLOOR], NULL, &m_aNumMat[X_TYPE_TUTORIAL_GOAL_FLOOR], &m_apMesh[X_TYPE_TUTORIAL_GOAL_FLOOR]);

	//チュートリアルのミドルの柵
	D3DXLoadMeshFromX("data/MODEL/TUTORIAL/middle_fence.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_TUTORIAL_MIDDLE_FENCE], NULL, &m_aNumMat[X_TYPE_TUTORIAL_MIDDLE_FENCE], &m_apMesh[X_TYPE_TUTORIAL_MIDDLE_FENCE]);

	//チュートリアルのスタートとゴールのサイド柵
	D3DXLoadMeshFromX("data/MODEL/TUTORIAL/startgoal_sidefence.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_TUTORIAL_SIDEFENCE], NULL, &m_aNumMat[X_TYPE_TUTORIAL_SIDEFENCE], &m_apMesh[X_TYPE_TUTORIAL_SIDEFENCE]);

	//チュートリアルのスタートとゴールの後ろ柵
	D3DXLoadMeshFromX("data/MODEL/TUTORIAL/startgoal_backfence.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_TUTORIAL_BACKFENCE], NULL, &m_aNumMat[X_TYPE_TUTORIAL_BACKFENCE], &m_apMesh[X_TYPE_TUTORIAL_BACKFENCE]);

	//チュートリアルのゴールの柱
	D3DXLoadMeshFromX("data/MODEL/TUTORIAL/goal_pole.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_TUTORIAL_GOAL_POLE], NULL, &m_aNumMat[X_TYPE_TUTORIAL_GOAL_POLE], &m_apMesh[X_TYPE_TUTORIAL_GOAL_POLE]);

	//チュートリアルのゴールの旗
	D3DXLoadMeshFromX("data/MODEL/TUTORIAL/goal_flag.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_TUTORIAL_GOAL_FLAG], NULL, &m_aNumMat[X_TYPE_TUTORIAL_GOAL_FLAG], &m_apMesh[X_TYPE_TUTORIAL_GOAL_FLAG]);

	//ステージの足場
	D3DXLoadMeshFromX("data/MODEL/GAME/scaffold.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_GAME_SCAFFOLD], NULL, &m_aNumMat[X_TYPE_GAME_SCAFFOLD], &m_apMesh[X_TYPE_GAME_SCAFFOLD]);

	//ステージのの上下壁
	D3DXLoadMeshFromX("data/MODEL/GAME/wall_updown.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_GAME_WALL_UPDOWN], NULL, &m_aNumMat[X_TYPE_GAME_WALL_UPDOWN], &m_apMesh[X_TYPE_GAME_WALL_UPDOWN]);

	//ステージの上下壁の柱
	D3DXLoadMeshFromX("data/MODEL/GAME/wall_pillar.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_GAME_WALL_PILLAR], NULL, &m_aNumMat[X_TYPE_GAME_WALL_PILLAR], &m_apMesh[X_TYPE_GAME_WALL_PILLAR]);

	//ステージの消える床
	D3DXLoadMeshFromX("data/MODEL/GAME/floor_disappear.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_GAME_FLOOR_DISAPPEAR], NULL, &m_aNumMat[X_TYPE_GAME_FLOOR_DISAPPEAR], &m_apMesh[X_TYPE_GAME_FLOOR_DISAPPEAR]);

	//ステージの滑る床（氷）
	D3DXLoadMeshFromX("data/MODEL/GAME/floor_ice.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_GAME_FLOOR_ICE], NULL, &m_aNumMat[X_TYPE_GAME_FLOOR_ICE], &m_apMesh[X_TYPE_GAME_FLOOR_ICE]);

	//ステージのバネ
	D3DXLoadMeshFromX("data/MODEL/GAME/spring.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_GAME_SPRING], NULL, &m_aNumMat[X_TYPE_GAME_SPRING], &m_apMesh[X_TYPE_GAME_SPRING]);

	//リザルトの王冠
	D3DXLoadMeshFromX("data/MODEL/GAME/crown.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_RESULT_CROWN], NULL, &m_aNumMat[X_TYPE_RESULT_CROWN], &m_apMesh[X_TYPE_RESULT_CROWN]);

	//雲
	D3DXLoadMeshFromX("data/MODEL/GAME/cloud.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_CLOUD], NULL, &m_aNumMat[X_TYPE_CLOUD], &m_apMesh[X_TYPE_CLOUD]);

	//気球
	D3DXLoadMeshFromX("data/MODEL/GAME/balloon.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_BALLOON], NULL, &m_aNumMat[X_TYPE_BALLOON], &m_apMesh[X_TYPE_BALLOON]);

	//飛行船
	D3DXLoadMeshFromX("data/MODEL/GAME/airship.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_AIRSHIP], NULL, &m_aNumMat[X_TYPE_AIRSHIP], &m_apMesh[X_TYPE_AIRSHIP]);

	//矢印
	D3DXLoadMeshFromX("data/MODEL/GAME/arrow.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_ARROW], NULL, &m_aNumMat[X_TYPE_ARROW], &m_apMesh[X_TYPE_ARROW]);

	//チェックポイント
	D3DXLoadMeshFromX("data/MODEL/GAME/checkpoint.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_CHECKPOINT], NULL, &m_aNumMat[X_TYPE_CHECKPOINT], &m_apMesh[X_TYPE_CHECKPOINT]);
}	

//=============================================================================
//終了
//=============================================================================
void CXload::Uninit(void)
{
	for (int nCntXload = 0; nCntXload < X_TYPE_MAX; nCntXload++)
	{
		//メッシュの破棄
		if (m_apMesh[nCntXload] != NULL)
		{
			m_apMesh[nCntXload]->Release();
			m_apMesh[nCntXload] = NULL;
		}

		//マテリアルの破棄
		if (m_apBuffMat[nCntXload] != NULL)
		{
			m_apBuffMat[nCntXload]->Release();
			m_apBuffMat[nCntXload] = NULL;
		}
	}
}

//=============================================================================
//メッシュの割り当て
//=============================================================================
LPD3DXMESH CXload::GetMesh(X_TYPE type)
{
	return m_apMesh[type];
}

//=============================================================================
//マテリアル割り当て
//=============================================================================
LPD3DXBUFFER CXload::GetBuffMat(X_TYPE type)
{
	return m_apBuffMat[type];
}

//=============================================================================
//マテリアル数割り当て
//=============================================================================
DWORD CXload::GetNumMat(X_TYPE type)
{
	return m_aNumMat[type];
}
