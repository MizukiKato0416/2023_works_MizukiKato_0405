//===========================================
//�v���C���[�̏�ԏ���
//Author:KatoMizuki
//===========================================
#ifndef _STATE_PLAYER_H_
#define _STATE_PLAYER_H_
#include "main.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CStatePlayer
{
public:
	enum class STATE_PLAYER
	{
		NONE = 0,
		NOMAL,
		DAMAGE,
		MAX
	};

	//�����o�֐�
	CStatePlayer();					//�R���X�g���N�^
	virtual ~CStatePlayer();		//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;

private:

};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_STATE_PLAYER_H_