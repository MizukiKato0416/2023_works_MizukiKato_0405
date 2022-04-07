//===========================================
//�_���W�����̏I�_�n�_�r���_�[����
//Author:KatoMizuki
//===========================================
#ifndef _DUNGEON_END_ROAD_BUILDER_H_
#define _DUNGEON_END_ROAD_BUILDER_H_
#include "dungeon_room_builder.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CDungeonEndRoadBuilder :public CDungeonRoomBuilder
{
public:
	//�����o�֐�
	CDungeonEndRoadBuilder();			//�R���X�g���N�^
	~CDungeonEndRoadBuilder();		//�f�X�g���N�^

	void SetFloor(D3DXVECTOR3 pos);			//���̐���
	void SetPiller(D3DXVECTOR3 pos);		//���̐���
	void SetWall(D3DXVECTOR3 pos);			//�ǂ̐���
	void SetCheckPoint(D3DXVECTOR3 pos);	//���[�v�]�[���̐���

	//�_���W�����̓����o��
	CDungeonRoom *GetDungeonRoom() { return m_pDungeonRoom; }
	static CDungeonEndRoadBuilder *Create(void);					//��������


private:

};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_DUNGEON_END_ROAD_BUILDER_H_