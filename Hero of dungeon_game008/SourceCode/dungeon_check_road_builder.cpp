//================================================
//�X�e�[�W�̃`�F�b�N�|�C���g�����铹�r���_�[����
//Author:KatoMizuki
//================================================
#include "dungeon_check_road_builder.h"
#include "model_single.h"
#include "manager.h"
#include "check_circle.h"
#include "floor.h"
#include "texture.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CDungeonCheckRoadBuilder::CDungeonCheckRoadBuilder()
{
	
}

//================================================
//�f�X�g���N�^
//================================================
CDungeonCheckRoadBuilder::~CDungeonCheckRoadBuilder()
{

}

//================================================
//���̐���
//================================================
void CDungeonCheckRoadBuilder::SetFloor(D3DXVECTOR3 pos)
{
	CFloor *pFloor = nullptr;
	pFloor = CFloor::Create(pos, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE, 0.0f, DUNGEON_ROOM_BUILDER_SIZE), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pFloor->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_DUNGEON_FLOOR"));
}

//================================================
//�`�F�b�N�|�C���g����
//================================================
void CDungeonCheckRoadBuilder::SetCheckPoint(D3DXVECTOR3 pos)
{
	CCheckCircle *pCheckCircle = nullptr;
	pCheckCircle = CCheckCircle::Create(D3DXVECTOR3(pos.x, pos.y + 0.1f, pos.z), D3DXVECTOR3(200.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pCheckCircle->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_CHECK_POINT"));
	pCheckCircle->SetCol(D3DXCOLOR(0.3f, 1.0f, 0.0f, 1.0f));
}

//================================================
//���̐���
//================================================
void CDungeonCheckRoadBuilder::SetPiller(D3DXVECTOR3 pos)
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
CDungeonCheckRoadBuilder *CDungeonCheckRoadBuilder::Create(void)
{
	//�C���X�^���X�̐���
	CDungeonCheckRoadBuilder *pDungeonCheckRoadBuilder = nullptr;
	if (pDungeonCheckRoadBuilder == nullptr)
	{
		pDungeonCheckRoadBuilder = new CDungeonCheckRoadBuilder;
	}
	return pDungeonCheckRoadBuilder;
}