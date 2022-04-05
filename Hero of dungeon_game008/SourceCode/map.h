//===========================================
//マップ処理
//Author:KatoMizuki
//===========================================
#ifndef _MAP_H_
#define _MAP_H_
#include "object2D.h"

//前方宣言

//================================================
//マクロ定義
//================================================
#define MAP_ROOM_SIZE		(40.0f)											//部屋の大きさ
#define MAP_SIZE			(200.0f)										//マップのサイズ
#define MAP_PLAYER_SIZE		(15.0f)											//マップのプレイヤーのサイズ
#define MAP_CHECK_SIZE		(13.0f)											//マップのチェックポイントのサイズ
#define MAP_ENEMY_SIZE		(8.0f)											//マップの敵のサイズ
#define MAP_POS_X			(SCREEN_WIDTH - MAP_SIZE / 2.0f - 20.0f)		//マップの原点X
#define MAP_POS_Y			(MAP_SIZE / 2.0f + 20.0f)						//マップの原点Y

//================================================
//クラスの定義
//================================================
//クラスの定義
class CMap : public CObject2D
{
public:
	//MAPの種類
	enum class TYPE
	{
		NONE = 0,
		START,		//スタートの道
		ROAD,		//道
		WALL,		//壁
		PLAYER,		//プレイヤー
		ENEMY,		//敵
		CHECK,		//チェックポイント
		WARP,		//ワープ
		MAX
	};

	CMap(int nPriority = PRIORITY_MAP);	//コンストラクタ
	~CMap();							//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMap *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriolty, TYPE type);
	//マップの位置設定処理
	static void SetStartRoomPos(void);
	//敵のポインタ設定処理
	static void SetEnemyPointa(void);
	//チェックポイントのポインタ設定処理
	static void SetCheckPointa(void);
	//破棄処理
	static void Delete(CObject *pSubjectObject);

private:
	//メンバ関数
	void PlayerMove(void);				//プレイヤーが動いた時の処理
	void EnemyMove(void);				//敵が動いた時の 処理
	void DrawRange(D3DXVECTOR3 pos);	//描画の範囲に関する処理

	static D3DXVECTOR3 m_posStartRoom;	//スタートする部屋の現在地
	TYPE m_type;						//MAPの種類
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
	bool m_bDraw;						//描画するかどうか
	CObject *m_pObject;					//オブジェクトのポインタ
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_MAP_H_