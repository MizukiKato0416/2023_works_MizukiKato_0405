//===========================================
//�X�e�[�W�̃r���_�[����
//Author:KatoMizuki
//===========================================
#ifndef _DUNGEON_ROOM_BUILDER_H_
#define _DUNGEON_ROOM_BUILDER_H_
#include "main.h"
#include "dungeon_room.h"

//================================================
//�}�N����`
//================================================
#define DUNGEON_ROOM_BUILDER_SIZE		(1000.0f)			//�����̃T�C�Y

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CDungeonRoomBuilder
{
public:
	//�����o�֐�
	CDungeonRoomBuilder();		//�R���X�g���N�^
	~CDungeonRoomBuilder();		//�f�X�g���N�^

	virtual void SetFloor(D3DXVECTOR3 pos) {}					//���̐���
	virtual void SetCheckPoint(D3DXVECTOR3 pos) {}				//�`�F�b�N�|�C���g����
	virtual void SetEnemy(D3DXVECTOR3 pos) {}					//�G�̐���
	virtual void SetWall(D3DXVECTOR3 pos) {}					//�ǂ̐���
	virtual void SetPiller(D3DXVECTOR3 pos) {}					//���̐���
	virtual CDungeonRoom *GetDungeonRoom() { return NULL; }		//�_���W�����̕������o��
	static CDungeonRoomBuilder *Create(void);					//��������

protected:
	CDungeonRoom *m_pDungeonRoom;	//�_���W�����̕����̃|�C���^
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_DUNGEON_ROOM_BUILDER_H_