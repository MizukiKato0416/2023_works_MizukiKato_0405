//===========================================
//�GUFO�̏���
//Authore:��������
//===========================================
#ifndef _ENEMY_UFO_H_
#define _ENEMY_UFO_H_
#include "enemy.h"

//================================================
//�}�N����`
//================================================
#define ENEMY_UFO_WIDTH				(70.0f)		//�|���S���̕�
#define ENEMY_UFO_HEIGHT			(70.0f)		//�|���S���̍���
#define ENEMY_UFO_SHOOT_COUNTER		(180)		//�e�����Ԋu
#define ENEMY_UFO_LIFE				(2)			//���C�t

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CEnemyUfo : public CEnemy
{
public:
	CEnemyUfo();				//�R���X�g���N�^
	~CEnemyUfo();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemyUfo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CMover::MOVER_TYPE moverType);

private:
	//�����o�֐�
	void MoveType(void);								//�G�̓�����
	void ShootBullet(void);			//�e��ł���
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_ENEMY_UFO_H_