//===========================================
//�_���W�����̓��r���_�[����
//Author:KatoMizuki
//===========================================
#ifndef _DUNGEON_ROAD_BUILDER_H_
#define _DUNGEON_ROAD_BUILDER_H_
#include "dungeon_room_builder.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CDungeonRoadBuilder :public CDungeonRoomBuilder
{
public:
	//�����o�֐�
	CDungeonRoadBuilder();		//�R���X�g���N�^
	~CDungeonRoadBuilder();		//�f�X�g���N�^

	void SetFloor(D3DXVECTOR3 pos);			//���̐���
	void SetPiller(D3DXVECTOR3 pos);		//���̐���

	//�_���W�����̓����o��
	CDungeonRoom *GetDungeonRoom() { return m_pDungeonRoom; }
	static CDungeonRoadBuilder *Create(void);					//��������


private:

};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_DUNGEON_ROAD_BUILDER_H_