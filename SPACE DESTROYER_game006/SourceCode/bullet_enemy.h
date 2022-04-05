//===========================================
//�G�̒e����
//Authore:��������
//===========================================
#ifndef _BULLET_ENEMY_H_
#define _BULLET_ENEMY_H_
#include "bullet.h"
#include "texture.h"

//================================================
//�}�N����`
//================================================
#define BULLET_ENEMY_WIDTH							(15.0f)		//�|���S���̕�
#define BULLET_ENEMY_HEIGHT							(15.0f)		//�|���S���̍���
#define BULLET_ENEMY_BOSS_CANNON_HOMING_WIDTH		(30.0f)		//�{�X�̑�C���o���z�[�~���O�e�̃|���S���̕�
#define BULLET_ENEMY_BOSS_CANNON_HOMING_HEIGHT		(30.0f)		//�{�X�̑�C���o���z�[�~���O�e�̃|���S���̍���
#define BULLET_ENEMY_BOSS_BODY_HOMING_WIDTH			(80.0f)		//�{�X�̑̂��o���z�[�~���O�e�̃|���S���̕�
#define BULLET_ENEMY_BOSS_BODY_HOMING_HEIGHT		(80.0f)		//�{�X�̑̂��o���z�[�~���O�e�̃|���S���̍���
#define BULLET_ENEMY_BOSS_STRAIGHT_WIDTH			(60.0f)		//�{�X���o�����i�e�̃|���S���̕�
#define BULLET_ENEMY_BOSS_STRAIGHT_HEIGHT			(200.0f)	//�{�X���o�����i�e�̃|���S���̍���
#define BULLET_ENEMY_BOSS_DIFFUSION_WIDTH			(80.0f)		//�{�X���o���g�U�e�̃|���S���̕�
#define BULLET_ENEMY_BOSS_DIFFUSION_HEIGHT			(80.0f)		//�{�X���o���g�U�e�̃|���S���̍���
#define BULLET_ENEMY_BOSS_LASER_WIDTH				(300.0f)	//�{�X���o�����[�U�[�e�̃|���S���̕�
#define BULLET_ENEMY_BOSS_LASER_HEIGHT				(700.0f)	//�{�X���o�����[�U�[�e�̃|���S���̍���
#define BULLET_ENEMY_SPEED							(7.0f)		//�e�̃X�s�[�h
#define BULLET_ENEMY_HOMING_SPEED					(5.0f)		//�z�[�~���O�e�̃X�s�[�h
#define BULLET_ENEMY_FINISH_HOMING					(250.0f)	//�z�[�~���O���I��鋗��

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CBulletEnemy : public CBullet
{
public:
	//�e�̎��
	typedef enum
	{
		BULLET_TYPE_NONE = 0,
		BULLET_TYPE_STRAIGHT,				//�^������
		BULLET_TYPE_HOMING,					//�ǔ�
		BULLET_TYPE_LASER,					//���[�U�[
		BULLET_TYPE_MAX
	} BULLET_TYPE;

	CBulletEnemy(int nPriority = PRIORITY_BULLET_ENEMY);	//�R���X�g���N�^
	~CBulletEnemy();										//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBulletEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CBulletEnemy::BULLET_TYPE, CTexture::TYPE textureType);

private:
	//�����o�֐�
	bool Collision(D3DXVECTOR3 pos, CSound *pSound);	//�����蔻��
	void MoveType(void);								//�e�̓�����

	D3DXVECTOR3 m_pos;									//�|���S���̈ʒu
	D3DXVECTOR3 m_move;									//�|���S���̈ړ���
	D3DXVECTOR3	m_size;									//�T�C�Y
	static LPDIRECT3DTEXTURE9 m_pTexture;				//���L�e�N�X�`���̃|�C���^
	BULLET_TYPE m_nType;								//�e�̎��
	float m_fRot;										//�e���~�`�ɓ��������߂̊p�x
	float m_fDistance;									//�e���~�`�ɓ��������߂̋���
	bool m_bHoming;										//�z�[�~���O��Ԃ��ǂ���
	int m_nLaserCounter;								//���[�U�[���o�������鎞��
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_BULLET_ENEMY_H_