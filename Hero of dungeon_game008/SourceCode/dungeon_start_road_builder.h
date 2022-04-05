//===========================================
//�_���W�����̃X�^�[�g�n�_�r���_�[����
//Author:KatoMizuki
//===========================================
#ifndef _DUNGEON_START_ROAD_BUILDER_H_
#define _DUNGEON_START_ROAD_BUILDER_H_
#include "dungeon_room_builder.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CDungeonStartRoadBuilder :public CDungeonRoomBuilder
{
public:
	//�����o�֐�
	CDungeonStartRoadBuilder();			//�R���X�g���N�^
	~CDungeonStartRoadBuilder();		//�f�X�g���N�^

	void SetFloor(D3DXVECTOR3 pos);			//���̐���
	void SetPiller(D3DXVECTOR3 pos);		//���̐���
	void SetWall(D3DXVECTOR3 pos);			//�ǂ̐���

	//�_���W�����̓����o��
	CDungeonRoom *GetDungeonRoom() { return m_pDungeonRoom; }
	static CDungeonStartRoadBuilder *Create(void);					//��������


private:

};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_DUNGEON_START_ROAD_BUILDER_H_