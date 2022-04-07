//================================================
//�_���W�����̏I�_�n�_�r���_�[����
//Author:KatoMizuki
//================================================
#include "dungeon_end_road_builder.h"
#include "model_single.h"
#include "warp_circle.h"
#include "manager.h"
#include "floor.h"
#include "texture.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CDungeonEndRoadBuilder::CDungeonEndRoadBuilder()
{
	
}

//================================================
//�f�X�g���N�^
//================================================
CDungeonEndRoadBuilder::~CDungeonEndRoadBuilder()
{

}

//================================================
//���̐���
//================================================
void CDungeonEndRoadBuilder::SetFloor(D3DXVECTOR3 pos)
{
	CFloor *pFloor = nullptr;
	pFloor = CFloor::Create(pos, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE, 0.0f, DUNGEON_ROOM_BUILDER_SIZE), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pFloor->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_DUNGEON_FLOOR"));
}

//================================================
//���̐���
//================================================
void CDungeonEndRoadBuilder::SetPiller(D3DXVECTOR3 pos)
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
//�ǂ̐���
//================================================
void CDungeonEndRoadBuilder::SetWall(D3DXVECTOR3 pos)
{
	CModelSingle::Create(D3DXVECTOR3(pos.x, pos.y, pos.z + DUNGEON_ROOM_BUILDER_SIZE), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CManager::GetInstance()->GetXload()->X_TYPE_WALL_01, nullptr, true);
}

//================================================
//�`�F�b�N�|�C���g����
//================================================
void CDungeonEndRoadBuilder::SetCheckPoint(D3DXVECTOR3 pos)
{
	CWarpCircle *pWarpCircle = nullptr;
	pWarpCircle = CWarpCircle::Create(D3DXVECTOR3(pos.x, pos.y + 0.1f, pos.z), D3DXVECTOR3(200.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pWarpCircle->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_CHECK_POINT"));
}

//================================================
//��������
//================================================
CDungeonEndRoadBuilder *CDungeonEndRoadBuilder::Create(void)
{
	//�C���X�^���X�̐���
	CDungeonEndRoadBuilder *pDungeonEndRoadBuilder = nullptr;
	if (pDungeonEndRoadBuilder == nullptr)
	{
		pDungeonEndRoadBuilder = new CDungeonEndRoadBuilder;
	}
	return pDungeonEndRoadBuilder;
}