//================================================
//�X�e�[�W�̃{�X�����铹�̃r���_�[����
//Author:KatoMizuki
//================================================
#include "dungeon_boss_road_builder.h"
#include "model_single.h"
#include "manager.h"
#include "floor.h"
#include "texture.h"
#include "enemy_boss.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CDungeonBossRoadBuilder::CDungeonBossRoadBuilder()
{
	
}

//================================================
//�f�X�g���N�^
//================================================
CDungeonBossRoadBuilder::~CDungeonBossRoadBuilder()
{

}

//================================================
//���̐���
//================================================
void CDungeonBossRoadBuilder::SetFloor(D3DXVECTOR3 pos)
{
	CFloor *pFloor = nullptr;
	pFloor = CFloor::Create(pos, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE, 0.0f, DUNGEON_ROOM_BUILDER_SIZE), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pFloor->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_DUNGEON_FLOOR"));
}

//================================================
//�G�̐���
//================================================
void CDungeonBossRoadBuilder::SetEnemy(D3DXVECTOR3 pos)
{
	CEnemyBoss::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//================================================
//���̐���
//================================================
void CDungeonBossRoadBuilder::SetPiller(D3DXVECTOR3 pos)
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
CDungeonBossRoadBuilder *CDungeonBossRoadBuilder::Create(void)
{
	//�C���X�^���X�̐���
	CDungeonBossRoadBuilder *pDungeonBossRoadBuilder = nullptr;
	if (pDungeonBossRoadBuilder == nullptr)
	{
		pDungeonBossRoadBuilder = new CDungeonBossRoadBuilder;
	}
	return pDungeonBossRoadBuilder;
}