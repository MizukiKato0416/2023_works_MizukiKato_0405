//===========================================
//�v���C�f�[�^�Ǘ�����
//Authore:��������
//===========================================
#ifndef _PLAY_DATA_H_
#define _PLAY_DATA_H_
#include "main.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CPlayData
{
public:
	CPlayData();			//�R���X�g���N�^
	~CPlayData();			//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);

	static void SetPlayerLife(int nLife);	//�v���C���[�̃��C�t�̐ݒ�
	static int GetPlayerLife(void);			//�v���C���[�̃��C�t�̎擾
	static void SetScore(int nScore);		//�X�R�A�̐ݒ�
	static int GetScore(void);				//�X�R�A�̎擾

private:
	static int m_nPlayerLife;				//�v���C���[�̃��C�t
	static int m_nScore;					//�X�R�A

};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_PLAY_DATA_H_