//===========================================
//�v���C���[����
//Author:KatoMizuki
//===========================================
#ifndef _DUNGEON_ROOM_H_
#define _DUNGEON_ROOM_H_
#include "main.h"
//�O���錾

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CDungeonRoom
{
public:
	CDungeonRoom();				//�R���X�g���N�^
	~CDungeonRoom();			//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	static CDungeonRoom *Create(D3DXVECTOR3 pos);

};

#endif // !_DUNGEON_ROOM_H_