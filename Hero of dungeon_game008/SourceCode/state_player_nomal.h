//===========================================
//�v���C���[�̒ʏ��ԏ���
//Author:KatoMizuki
//===========================================
#ifndef _STATE_PLAYER_NOMAL_H_
#define _STATE_PLAYER_NOMAL_H_
#include "main.h"
#include "state_player.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CStatePlayerNomal:public CStatePlayer
{
public:
	//�����o�֐�
	CStatePlayerNomal();		//�R���X�g���N�^
	~CStatePlayerNomal();		//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:

};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_STATE_PLAYER_NOMAL_H_