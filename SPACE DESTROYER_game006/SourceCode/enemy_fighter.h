//===========================================
//�G�퓬�@�̏���
//Authore:��������
//===========================================
#ifndef _ENEMY_FIGHTER_H_
#define _ENEMY_FIGHTER_H_
#include "enemy.h"

//================================================
//�}�N����`
//================================================
#define ENEMY_FIGHTER_WIDTH				(70.0f)		//�|���S���̕�
#define ENEMY_FIGHTER_HEIGHT			(70.0f)		//�|���S���̍���
#define ENEMY_FIGHTER_SHOOT_COUNTER		(120)		//�e�����Ԋu
#define ENEMY_FIGHTER_LIFE				(2)			//���C�t

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CEnemyFighter : public CEnemy
{
public:

	CEnemyFighter();				//�R���X�g���N�^
	~CEnemyFighter();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemyFighter *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CMover::MOVER_TYPE moverType);

private:
	//�����o�֐�
	void MoveType(void);			//�G�̓�����
	void ShootBullet(void);			//�e��ł���
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_ENEMY_FIGHTER_H_