//================================================
//�_���W�����̃X�^�[�g�n�_�r���_�[����
//Author:KatoMizuki
//================================================
#include "dungeon_start_road_builder.h"
#include "model_single.h"
#include "manager.h"
#include "floor.h"
#include "texture.h"
#include "player.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CDungeonStartRoadBuilder::CDungeonStartRoadBuilder()
{
	
}

//================================================
//�f�X�g���N�^
//================================================
CDungeonStartRoadBuilder::~CDungeonStartRoadBuilder()
{

}

//================================================
//���̐���
//================================================
void CDungeonStartRoadBuilder::SetFloor(D3DXVECTOR3 pos)
{
	CFloor *pFloor = nullptr;
	pFloor = CFloor::Create(pos, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE, 0.0f, DUNGEON_ROOM_BUILDER_SIZE), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pFloor->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_DUNGEON_FLOOR"));

	//�v���C���[�̐���
	CPlayer::Create(pos, D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	/*for (int nCnt2 = 0; nCnt2 < 1; nCnt2++)
	{
		for (int nCnt = 0; nCnt < 50; nCnt++)
		{
			for (int nCnt1 = 0; nCnt1 < 10; nCnt1++)
			{
				CEffect3D::Create(D3DXVECTOR3(pos.x + 40 * nCnt2, 25.0f + pos.y + pow(1.190f, nCnt1) * nCnt1, pos.z + 25.0f * nCnt), D3DXVECTOR3(50.0f - (2.0f * nCnt1), 50.0f - (2.0f * nCnt1), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
									CEffect3D::EFFECT3D_TYPE::FIRE);
			}
		}
	}*/

	/*int nNum = 8;

	for (int nCnt2 = 0; nCnt2 < 1; nCnt2++)
	{
		for (int nCnt1 = 0; nCnt1 < 3; nCnt1++)
		{
			for (int nCnt = 0; nCnt < nNum; nCnt++)
			{
				CEffect3D::Create(D3DXVECTOR3(pos.x + cosf(D3DX_PI * 2.0f / nNum * nCnt) * pow(3.9f, nCnt1),
											 (pos.y + 100.0f) + sinf(D3DX_PI * 2.0f / nNum * nCnt) * pow(3.9f, nCnt1),
											  pos.z),
								  D3DXVECTOR3(60.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CEffect3D::EFFECT3D_TYPE::FIRE);

				CEffect3D::Create(D3DXVECTOR3(pos.x,
											 (pos.y + 100.0f) + sinf(D3DX_PI * 2.0f / nNum * nCnt) * pow(3.9f, nCnt1),
											  pos.z + cosf(D3DX_PI * 2.0f / nNum * nCnt) * pow(3.9f, nCnt1)),
								  D3DXVECTOR3(60.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CEffect3D::EFFECT3D_TYPE::FIRE);
			}
		}
	}*/
}

//================================================
//���̐���
//================================================
void CDungeonStartRoadBuilder::SetPiller(D3DXVECTOR3 pos)
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
void CDungeonStartRoadBuilder::SetWall(D3DXVECTOR3 pos)
{
	CModelSingle::Create(D3DXVECTOR3(pos.x, pos.y, pos.z - DUNGEON_ROOM_BUILDER_SIZE), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CManager::GetInstance()->GetXload()->X_TYPE_WALL_01, nullptr, true);
}

//================================================
//��������
//================================================
CDungeonStartRoadBuilder *CDungeonStartRoadBuilder::Create(void)
{
	//�C���X�^���X�̐���
	CDungeonStartRoadBuilder *pDungeonStartRoadBuilder = nullptr;
	if (pDungeonStartRoadBuilder == nullptr)
	{
		pDungeonStartRoadBuilder = new CDungeonStartRoadBuilder;
	}
	return pDungeonStartRoadBuilder;
}