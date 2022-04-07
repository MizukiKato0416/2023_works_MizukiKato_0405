//===========================================
//�_���W�����̕ǃr���_�[����
//Author:KatoMizuki
//===========================================
#ifndef _DUNGEON_WALL_BUILDER_H_
#define _DUNGEON_WALL_BUILDER_H_
#include "main.h"
#include "dungeon_room_builder.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CDungeonWallBuilder :public CDungeonRoomBuilder
{
public:
	//�����o�֐�
	CDungeonWallBuilder();		//�R���X�g���N�^
	~CDungeonWallBuilder();		//�f�X�g���N�^

	void SetWall(D3DXVECTOR3 pos);			//�ǂ̐���

	//�_���W�����̕ǂ��o��
	CDungeonRoom *GetDungeonRoom(void) { return m_pDungeonRoom; }
	static CDungeonWallBuilder *Create(void);					//��������

private:

};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_DUNGEON_WALL_BUILDER_H_