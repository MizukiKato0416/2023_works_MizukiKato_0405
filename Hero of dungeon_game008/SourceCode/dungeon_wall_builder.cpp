//================================================
//�X�e�[�W�̃r���_�[����
//Author:KatoMizuki
//================================================
#include "dungeon_wall_builder.h"
#include "model_single.h"
#include "manager.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CDungeonWallBuilder::CDungeonWallBuilder()
{
	
}

//================================================
//�f�X�g���N�^
//================================================
CDungeonWallBuilder::~CDungeonWallBuilder()
{

}

//================================================
//�ǂ̐���
//================================================
void CDungeonWallBuilder::SetWall(D3DXVECTOR3 pos)
{
	CModelSingle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CManager::GetInstance()->GetXload()->X_TYPE_WALL_01, nullptr, true);
}

//================================================
//��������
//================================================
CDungeonWallBuilder *CDungeonWallBuilder::Create(void)
{
	//�C���X�^���X�̐���
	CDungeonWallBuilder *pDungeonWallBuilder = nullptr;
	if (pDungeonWallBuilder == nullptr)
	{
		pDungeonWallBuilder = new CDungeonWallBuilder;
	}
	return pDungeonWallBuilder;
}