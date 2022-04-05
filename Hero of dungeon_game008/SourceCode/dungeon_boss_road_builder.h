//===========================================
//�_���W�����̃{�X�����铹�r���_�[����
//Author:KatoMizuki
//===========================================
#ifndef _DUNGEON_BOSS_ROAD_BUILDER_H_
#define _DUNGEON_BOSS_ROAD_BUILDER_H_
#include "dungeon_room_builder.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CDungeonBossRoadBuilder :public CDungeonRoomBuilder
{
public:
	//�����o�֐�
	CDungeonBossRoadBuilder();		//�R���X�g���N�^
	~CDungeonBossRoadBuilder();		//�f�X�g���N�^

	void SetFloor(D3DXVECTOR3 pos);			//���̐���
	void SetEnemy(D3DXVECTOR3 pos);			//�G�̐���
	void SetPiller(D3DXVECTOR3 pos);		//���̐���

	//�_���W�����̓����o��
	CDungeonRoom *GetDungeonRoom() { return m_pDungeonRoom; }
	static CDungeonBossRoadBuilder *Create(void);					//��������

private:

};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_DUNGEON_BOSS_ROAD_BUILDER_H_