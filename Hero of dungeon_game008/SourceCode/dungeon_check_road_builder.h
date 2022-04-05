//===========================================
//�_���W�����̃`�F�b�N�|�C���g�����铹�r���_�[����
//Author:KatoMizuki
//===========================================
#ifndef _DUNGEON_CHECK_ROAD_BUILDER_H_
#define _DUNGEON_CHECK_ROAD_BUILDER_H_
#include "dungeon_room_builder.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CDungeonCheckRoadBuilder :public CDungeonRoomBuilder
{
public:
	//�����o�֐�
	CDungeonCheckRoadBuilder();			//�R���X�g���N�^
	~CDungeonCheckRoadBuilder();		//�f�X�g���N�^

	void SetFloor(D3DXVECTOR3 pos);			//���̐���
	void SetCheckPoint(D3DXVECTOR3 pos);	//�`�F�b�N�|�C���g����
	void SetPiller(D3DXVECTOR3 pos);		//���̐���

	//�_���W�����̓����o��
	CDungeonRoom *GetDungeonRoom() { return m_pDungeonRoom; }
	static CDungeonCheckRoadBuilder *Create(void);					//��������


private:

};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_DUNGEON_CHECK_ROAD_BUILDER_H_