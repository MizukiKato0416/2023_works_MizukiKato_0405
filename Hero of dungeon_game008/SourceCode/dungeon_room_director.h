//===========================================
//�_���W�����̐�������
//Author:KatoMizuki
//===========================================
#ifndef _DUNGEON_DIRECTOR_H_
#define _DUNGEON_DIRECTOR_H_
#include "main.h"

//�O���錾
class CDungeonRoomBuilder;
class CDungeonRoom;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CDungeonRoomDirector
{
public:
	//�����o�֐�
	CDungeonRoomDirector();				//�R���X�g���N�^
	~CDungeonRoomDirector();			//�f�X�g���N�^

	//��������
	static CDungeonRoom *Create(CDungeonRoomBuilder *pDungeonRoomBuilder, D3DXVECTOR3 pos);
};

#endif // !_DUNGEON_DIRECTOR_H_