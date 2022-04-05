//===========================================
//�v���C���[�̒e����
//Authore:��������
//===========================================
#ifndef _BULLET_PLAYER_H_
#define _BULLET_PLAYER_H_
#include "bullet.h"

//================================================
//�}�N����`
//================================================
#define BULLET_PLAYER_WIDTH				(15.0f)			//�|���S���̕�
#define BULLET_PLAYER_HEIGHT			(100.0f)		//�|���S���̍���
#define BULLET_PLAYER_SPEED				(-15.0f)		//�e�̃X�s�[�h
#define BULLET_PLAYER_EFFECT_INTERVAL	(1)				//�e�̃G�t�F�N�g�̊Ԋu
#define BULLET_PLAYER_FINISH_HOMING		(0.0f)			//�z�[�~���O���I��鋗��


//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CBulletPlayer : public CBullet
{
public:
	//�e�̎��
	typedef enum
	{
		BULLET_TYPE_NONE = 0,
		BULLET_TYPE_STRAIGHT,			//�^������
		BULLET_TYPE_DIFFUSION,		//�g�U
		BULLET_TYPE_HOMING,			//�ǔ�
		BULLET_TYPE_MAX
	} BULLET_TYPE;

	CBulletPlayer(int nPriority = PRIORITY_BULLET_PLAYER);	//�R���X�g���N�^
	~CBulletPlayer();												//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, float fRot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBulletPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3	size, D3DXVECTOR3 move, CBulletPlayer::BULLET_TYPE, float fRot);
	float GetRot(void);			//�e�̌����擾����

private:
	//�����o�֐�
	void MoveType(void);								//�e�̓�����

	D3DXVECTOR3 m_pos;									//�|���S���̈ʒu
	D3DXVECTOR3 m_move;									//�|���S���̈ړ���
	D3DXVECTOR3	m_size;									//�T�C�Y
	static LPDIRECT3DTEXTURE9 m_pTexture;				//���L�e�N�X�`���̃|�C���^
	BULLET_TYPE m_nType;								//�e�̎��
	int m_nEfectCounter;								//�G�t�F�N�g�𐶐�����J�E���^
	bool m_bHoming;										//�z�[�~���O��Ԃ��ǂ���
	float m_fRot;										//�e�̌���
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_BULLET_PLAYER_H_