//================================================
//�X�e�[�W�̃r���_�[����
//Author:KatoMizuki
//================================================
#include "dungeon_room_builder.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CDungeonRoomBuilder::CDungeonRoomBuilder()
{
	
}

//================================================
//�f�X�g���N�^
//================================================
CDungeonRoomBuilder::~CDungeonRoomBuilder()
{

}

//================================================
//��������
//================================================
CDungeonRoomBuilder *CDungeonRoomBuilder::Create(void)
{
	//�C���X�^���X�̐���
	CDungeonRoomBuilder *pDungeonRoomBuilder = nullptr;
	if (pDungeonRoomBuilder == nullptr)
	{
		pDungeonRoomBuilder = new CDungeonRoomBuilder;
	}
	return pDungeonRoomBuilder;
}
