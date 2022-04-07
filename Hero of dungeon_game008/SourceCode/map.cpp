//================================================
//マップ処理
//Author:KatoMizuki
//================================================
#include "Object2D.h"
#include "manager.h"
#include "map.h"
#include "texture.h"
#include "dungeon_room_builder.h"

//================================================
//マクロ定義
//================================================

//================================================
//静的メンバ変数宣言
//================================================
D3DXVECTOR3 CMap::m_posStartRoom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//================================================
//デフォルトコンストラクタ
//================================================
CMap::CMap(int nPriority) :CObject2D(nPriority)
{
	m_bDraw = false;
	m_pObject = nullptr;
	m_type = TYPE::NONE;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CMap::~CMap()
{

}

//================================================
//初期化処理
//================================================
HRESULT CMap::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//変数初期化
	m_bDraw = true;

	CObject2D::Init(pos, size);

	//オブジェクトタイプの設定
	SetObjType(CObject::OBJTYPE::MAP);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CMap::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================
//更新処理
//================================================
void CMap::Update(void)
{
	//プレイヤーが動いた時の処理
	PlayerMove();

	//敵が動いた時の処理
	EnemyMove();
}

//================================================
//描画処理
//================================================
void CMap::Draw(void)
{
	//描画するなら
	if (m_bDraw == true)
	{
		CObject2D::Draw();
	}
}

//================================================
//生成処理
//================================================
CMap* CMap::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriolity, TYPE type)
{
	//インスタンスの生成
	CMap *pMap = nullptr;
	if (pMap == nullptr)
	{
		pMap = new CMap(nPriolity);
		if (pMap != nullptr)
		{
			pMap->m_type = type;
			pMap->Init(pos, size);
			//指定した種類でテクスチャを変える
			switch (type)
			{
			case TYPE::START:
				pMap->m_posStartRoom = pos;
				pMap->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MAP_ROAD");
				break;
			case TYPE::ROAD:
				pMap->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MAP_ROAD");
				break;
			case TYPE::WALL:
				pMap->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MAP_WALL");
				break;
			case TYPE::PLAYER:
				pMap->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MAP_PLAYER");
				break;
			case TYPE::ENEMY:
				pMap->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MAP_ENEMY");
				break;
			case TYPE::CHECK:
				pMap->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MAP_CHECK");
				break;
			case TYPE::WARP:
				pMap->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MAP_WARP");
				break;
			default:
				break;
			}
			pMap->BindTexture(pMap->m_pTexture);
		}
	}
	return pMap;
}

//================================================
//マップの位置設定処理
//================================================
void CMap::SetStartRoomPos(void)
{
	//スタート地点の位置とマップ中央の位置との差を求める
	D3DXVECTOR3 posStartRoom = D3DXVECTOR3(m_posStartRoom.x - MAP_POS_X, m_posStartRoom.y - MAP_POS_Y, 0.0f);

	//オブジェクト情報を入れるポインタ
	CObject *pObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CObject::PRIORITY_MAP);

	while (pObject != nullptr)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		//オブジェクトの種類がマップだったら
		if (pObject->GetObjType() == CObject::OBJTYPE::MAP)
		{
			//マップにキャスト
			CMap *pMapObj = nullptr;
			pMapObj = (CMap*)pObject;

			//タイプがプレイヤーではないとき
			if (pMapObj->m_type != TYPE::PLAYER)
			{
				//位置とサイズを取得
				D3DXVECTOR3 pos = pMapObj->GetPos();
				D3DXVECTOR3 size = pMapObj->GetSize();

				//スタート地点の位置とマップ中央の位置との差分移動させる
				pos -= posStartRoom;

				//位置とサイズ設定
				pMapObj->SetPos(pos, size);
			}
		}
		//次のオブジェクトに進める
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//================================================
//敵のポインタ設定処理
//================================================
void CMap::SetEnemyPointa(void)
{
	//オブジェクト情報を入れるポインタ
	CObject *pEnemyObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveEnemyObject = nullptr;

	//オブジェクト情報を入れるポインタ
	CObject *pObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;

	//マップにキャストするよう
	CMap *pMapObj = nullptr;

	//先頭のポインタを代入
	pEnemyObject = pEnemyObject->GetTopObj(CObject::PRIORITY_ENEMY);

	while (pEnemyObject != nullptr)
	{
		//現在のオブジェクトのポインタを保存
		pSaveEnemyObject = pEnemyObject;

		//オブジェクトの種類が敵だったら
		if (pEnemyObject->GetObjType() == CObject::OBJTYPE::ENEMY_BEE ||
			pEnemyObject->GetObjType() == CObject::OBJTYPE::ENEMY_FAT ||
			pEnemyObject->GetObjType() == CObject::OBJTYPE::ENEMY_BOSS)
		{
			//オブジェクト情報を入れるポインタ
			pObject = nullptr;
			//オブジェクト情報を保存するポインタ変数
			pSaveObject = nullptr;

			//先頭のポインタを代入
			pObject = pObject->GetTopObj(CObject::PRIORITY_MAP);

			while (pObject != nullptr)
			{
				//現在のオブジェクトのポインタを保存
				pSaveObject = pObject;

				//オブジェクトの種類がマップだったら
				if (pObject->GetObjType() == CObject::OBJTYPE::MAP)
				{
					//マップにキャスト
					pMapObj = nullptr;
					pMapObj = (CMap*)pObject;

					//タイプが敵のとき
					if (pMapObj->m_type == TYPE::ENEMY)
					{
						//対象のオブジェクトのポインタがnullptrの時
						if (pMapObj->m_pObject == nullptr)
						{
							//対象のオブジェクトのポインタを設定する
							pMapObj->m_pObject = pEnemyObject;

							//敵の位置を取得
							D3DXVECTOR3 posEnemy = pEnemyObject->GetPos();
							//ＺをＹに代入
							posEnemy.y = posEnemy.z;

							//マップの縮尺分縮めた場所を求める
							posEnemy *= MAP_ROOM_SIZE / DUNGEON_ROOM_BUILDER_SIZE;

							//Zは0にする
							posEnemy.z = 0.0f;

							//位置とサイズを取得
							D3DXVECTOR3 posMap = pMapObj->GetPos();
							D3DXVECTOR3 sizeMap = pMapObj->GetSize();

							//差分移動させる
							posMap.x += posEnemy.x;
							posMap.y -= posEnemy.y;

							//位置設定
							pMapObj->SetPos(posMap, sizeMap);
							break;
						}
					}
				}
				//次のオブジェクトに進める
				pObject = pSaveObject->GetObjNext(pSaveObject);
			}
		}
		//次のオブジェクトに進める
		pEnemyObject = pSaveEnemyObject->GetObjNext(pSaveEnemyObject);
	}
}

//================================================
//チェックポイントのポインタ設定処理
//================================================
void CMap::SetCheckPointa(void)
{
	//オブジェクト情報を入れるポインタ
	CObject *pCheckObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveCheckObject = nullptr;

	//オブジェクト情報を入れるポインタ
	CObject *pObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;

	//マップにキャストするよう
	CMap *pMapObj = nullptr;

	//先頭のポインタを代入
	pCheckObject = pCheckObject->GetTopObj(CObject::PRIORITY_CHECK_CIRCLE);

	while (pCheckObject != nullptr)
	{
		//現在のオブジェクトのポインタを保存
		pSaveCheckObject = pCheckObject;

		//オブジェクトの種類がチェックポイントだったら
		if (pCheckObject->GetObjType() == CObject::OBJTYPE::CHECK_CIRCLE)
		{
			//オブジェクト情報を入れるポインタ
			pObject = nullptr;
			//オブジェクト情報を保存するポインタ変数
			pSaveObject = nullptr;

			//先頭のポインタを代入
			pObject = pObject->GetTopObj(CObject::PRIORITY_MAP);

			while (pObject != nullptr)
			{
				//現在のオブジェクトのポインタを保存
				pSaveObject = pObject;

				//オブジェクトの種類がマップだったら
				if (pObject->GetObjType() == CObject::OBJTYPE::MAP)
				{
					//マップにキャスト
					pMapObj = nullptr;
					pMapObj = (CMap*)pObject;

					//タイプがチェックポインのとき
					if (pMapObj->m_type == TYPE::CHECK)
					{
						//対象のオブジェクトのポインタがnullptrの時
						if (pMapObj->m_pObject == nullptr)
						{
							//対象のオブジェクトのポインタを設定する
							pMapObj->m_pObject = pCheckObject;

							//敵の位置を取得
							D3DXVECTOR3 posCheck = pCheckObject->GetPos();
							//ＺをＹに代入
							posCheck.y = posCheck.z;

							//マップの縮尺分縮めた場所を求める
							posCheck *= MAP_ROOM_SIZE / DUNGEON_ROOM_BUILDER_SIZE;

							//Zは0にする
							posCheck.z = 0.0f;

							//位置とサイズを取得
							D3DXVECTOR3 posMap = pMapObj->GetPos();
							D3DXVECTOR3 sizeMap = pMapObj->GetSize();

							//差分移動させる
							posMap.x += posCheck.x;
							posMap.y -= posCheck.y;

							//位置設定
							pMapObj->SetPos(posMap, sizeMap);
							break;
						}
					}
				}
				//次のオブジェクトに進める
				pObject = pSaveObject->GetObjNext(pSaveObject);
			}
		}
		//次のオブジェクトに進める
		pCheckObject = pSaveCheckObject->GetObjNext(pSaveCheckObject);
	}
}

//================================================
//破棄処理
//================================================
void CMap::Delete(CObject * pSubjectObject)
{
	//オブジェクト情報を入れるポインタ
	CObject *pObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CObject::PRIORITY_MAP);

	while (pObject != nullptr)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		//オブジェクトの種類がマップだったら
		if (pObject->GetObjType() == CObject::OBJTYPE::MAP)
		{
			//マップにキャスト
			CMap *pMapObj = nullptr;
			pMapObj = (CMap*)pObject;

			//引数と対象のポインタが一致していたら
			if (pMapObj->m_pObject == pSubjectObject)
			{
				//消す
				pMapObj->m_pObject = nullptr;
				pMapObj->Uninit();
				return;
			}
		}
		//次のオブジェクトに進める
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//================================================
//プレイヤーが動いた時の処理
//================================================
void CMap::PlayerMove(void)
{
	//タイプがプレイヤーではないとき
	if (m_type != TYPE::PLAYER)
	{
		//タイプが敵の時
		if (m_type == TYPE::ENEMY || m_type == TYPE::CHECK)
		{
			if (m_pObject == nullptr)
			{
				return;
			}
		}
		//位置とサイズを取得
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 size = GetSize();

		//オブジェクト情報を入れるポインタ
		CObject *pObject = nullptr;
		//オブジェクト情報を保存するポインタ変数
		CObject *pSaveObject = nullptr;

		//先頭のポインタを代入
		pObject = pObject->GetTopObj(CObject::PRIORITY_PLAYER);

		while (pObject != nullptr)
		{
			//現在のオブジェクトのポインタを保存
			pSaveObject = pObject;

			//オブジェクトの種類がプレイヤーだったら
			if (pObject->GetObjType() == CObject::OBJTYPE::PLAYER)
			{
				//プレイヤーの現在地から1フレーム前の位置までの差を求める
				D3DXVECTOR3 posDiffer = pObject->GetPosOld() - pObject->GetPos();
				//ＺをＹに代入
				posDiffer.y = posDiffer.z;

				//マップの縮尺分差を縮める
				posDiffer *= MAP_ROOM_SIZE / DUNGEON_ROOM_BUILDER_SIZE;

				//Zは0にする
				posDiffer.z = 0.0f;

				//差分移動させる
				pos.x += posDiffer.x;
				pos.y -= posDiffer.y;
			}
			//次のオブジェクトに進める
			pObject = pSaveObject->GetObjNext(pSaveObject);
		}

		//位置とサイズ設定
		SetPos(pos, size);

		//描画する範囲に関する処理
		DrawRange(pos);
	}
}

//================================================
//敵が動いた時の処理
//================================================
void CMap::EnemyMove(void)
{
	//タイプが敵のとき
	if (m_type == TYPE::ENEMY)
	{
		if (m_pObject == nullptr)
		{
			return;
		}
		//位置とサイズを取得
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 size = GetSize();

		//現在地から1フレーム前の位置までの差を求める
		D3DXVECTOR3 posDiffer = m_pObject->GetPosOld() - m_pObject->GetPos();
		//ＺをＹに代入
		posDiffer.y = posDiffer.z;

		//マップの縮尺分差を縮める
		posDiffer *= MAP_ROOM_SIZE / DUNGEON_ROOM_BUILDER_SIZE;

		//Zは0にする
		posDiffer.z = 0.0f;

		//差分移動させる
		pos.x -= posDiffer.x;
		pos.y += posDiffer.y;

		//位置とサイズ設定
		SetPos(pos, size);

		//描画する範囲に関する処理
		DrawRange(pos);
	}
}

//================================================
//描画の範囲に関する処理
//================================================
void CMap::DrawRange(D3DXVECTOR3 pos)
{
	//既定の範囲からポリゴンが出たら
	if (pos.x < MAP_POS_X - MAP_SIZE / 2.0f || pos.x > MAP_POS_X + MAP_SIZE / 2.0f ||
		pos.y < MAP_POS_Y - MAP_SIZE / 2.0f || pos.y > MAP_POS_Y + MAP_SIZE / 2.0f)
	{
		//描画されているなら
		if (m_bDraw == true)
		{
			//描画をしないようにする
			m_bDraw = false;
		}
	}
	else
	{//既定の範囲にいるとき
	 //描画されていないなら
		if (m_bDraw == false)
		{
			//描画をする
			m_bDraw = true;
		}
	}
}
