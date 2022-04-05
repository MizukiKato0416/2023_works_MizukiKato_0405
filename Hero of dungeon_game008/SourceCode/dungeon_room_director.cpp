//================================================
//�_���W�����̐�������
//Author:KatoMizuki
//================================================
#include "dungeon_room_director.h"
#include "dungeon_room_builder.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CDungeonRoomDirector::CDungeonRoomDirector()
{
	
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CDungeonRoomDirector::~CDungeonRoomDirector()
{

}

//================================================
//��������
//================================================
CDungeonRoom *CDungeonRoomDirector::Create(CDungeonRoomBuilder *pDungeonRoomBuilder, D3DXVECTOR3 pos)
{
	pDungeonRoomBuilder->SetFloor(pos);					//���̐���
	pDungeonRoomBuilder->SetCheckPoint(pos);			//�`�F�b�N�|�C���g����
	pDungeonRoomBuilder->SetEnemy(pos);					//�G�̐���
	pDungeonRoomBuilder->SetWall(pos);					//�ǂ̐���
	pDungeonRoomBuilder->SetPiller(pos);				//���̐���
	return pDungeonRoomBuilder->GetDungeonRoom();
}
