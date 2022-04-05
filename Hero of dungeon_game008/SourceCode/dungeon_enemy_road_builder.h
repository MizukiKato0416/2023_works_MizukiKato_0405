//===========================================
//�_���W�����̓G�����铹�r���_�[����
//Author:KatoMizuki
//===========================================
#ifndef _DUNGEON_ENEMY_ROAD_BUILDER_H_
#define _DUNGEON_ENEMY_ROAD_BUILDER_H_
#include "dungeon_room_builder.h"

//================================================
//�}�N����`
//================================================
#define DUNGEON_ENEMY_ROAD_BUILDER_ENEMY_NUM		(3)			//�o���G�̐�
#define DUNGEON_ENEMY_ROAD_BUILDER_ENEMY_POS		(100.0f)	//�o���G�̈ʒu�����l

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CDungeonEnemyRoadBuilder :public CDungeonRoomBuilder
{
public:
	//�����o�֐�
	CDungeonEnemyRoadBuilder();			//�R���X�g���N�^
	~CDungeonEnemyRoadBuilder();		//�f�X�g���N�^

	void SetFloor(D3DXVECTOR3 pos);			//���̐���
	void SetEnemy(D3DXVECTOR3 pos);			//�G�̐���
	void SetPiller(D3DXVECTOR3 pos);		//���̐���

	//�_���W�����̓����o��
	CDungeonRoom *GetDungeonRoom() { return m_pDungeonRoom; }
	static CDungeonEnemyRoadBuilder *Create(void);					//��������


private:

};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_DUNGEON_ENEMY_ROAD_BUILDER_H_