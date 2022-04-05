//================================================
//�X�e�[�W�̓G�����铹�̃r���_�[����
//Author:KatoMizuki
//================================================
#include "dungeon_enemy_road_builder.h"
#include "model_single.h"
#include "manager.h"
#include "floor.h"
#include "texture.h"
#include "enemy_bee.h"
#include "enemy_fat.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CDungeonEnemyRoadBuilder::CDungeonEnemyRoadBuilder()
{
	
}

//================================================
//�f�X�g���N�^
//================================================
CDungeonEnemyRoadBuilder::~CDungeonEnemyRoadBuilder()
{

}

//================================================
//���̐���
//================================================
void CDungeonEnemyRoadBuilder::SetFloor(D3DXVECTOR3 pos)
{
	CFloor *pFloor = nullptr;
	pFloor = CFloor::Create(pos, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE, 0.0f, DUNGEON_ROOM_BUILDER_SIZE), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pFloor->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_DUNGEON_FLOOR"));
}

//================================================
//�G�̐���
//================================================
void CDungeonEnemyRoadBuilder::SetEnemy(D3DXVECTOR3 pos)
{
	CEnemyBee::Create(D3DXVECTOR3(pos.x - DUNGEON_ENEMY_ROAD_BUILDER_ENEMY_POS, pos.y, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CEnemyFat::Create(D3DXVECTOR3(pos.x + DUNGEON_ENEMY_ROAD_BUILDER_ENEMY_POS, pos.y, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//================================================
//���̐���
//================================================
void CDungeonEnemyRoadBuilder::SetPiller(D3DXVECTOR3 pos)
{
	CModelSingle::Create(D3DXVECTOR3(pos.x -500.0f + 50.0f, pos.y, pos.z + 500.0f - 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						 CManager::GetInstance()->GetXload()->X_TYPE_PILLER_01, nullptr, true);
	CModelSingle::Create(D3DXVECTOR3(pos.x -500.0f + 50.0f, pos.y, pos.z - 500.0f + 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						 CManager::GetInstance()->GetXload()->X_TYPE_PILLER_01, nullptr, true);
	CModelSingle::Create(D3DXVECTOR3(pos.x + 500.0f - 50.0f, pos.y, pos.z + 500.0f - 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						 CManager::GetInstance()->GetXload()->X_TYPE_PILLER_01, nullptr, true);
	CModelSingle::Create(D3DXVECTOR3(pos.x + 500.0f - 50.0f, pos.y, pos.z - 500.0f + 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						 CManager::GetInstance()->GetXload()->X_TYPE_PILLER_01, nullptr, true);
}

//================================================
//��������
//================================================
CDungeonEnemyRoadBuilder *CDungeonEnemyRoadBuilder::Create(void)
{
	//�C���X�^���X�̐���
	CDungeonEnemyRoadBuilder *pDungeonEnemyRoadBuilder = nullptr;
	if (pDungeonEnemyRoadBuilder == nullptr)
	{
		pDungeonEnemyRoadBuilder = new CDungeonEnemyRoadBuilder;
	}
	return pDungeonEnemyRoadBuilder;
}