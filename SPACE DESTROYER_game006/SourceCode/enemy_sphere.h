//===========================================
//���̌^�G�̏���
//Authore:��������
//===========================================
#ifndef _ENEMY_SPHERE_H_
#define _ENEMY_SPHERE_H_
#include "enemy.h"

//================================================
//�}�N����`
//================================================
#define ENEMY_SPHERE_WIDTH		(70.0f)	//�|���S���̕�
#define ENEMY_SPHERE_HEIGHT		(70.0f)	//�|���S���̍���
#define ENEMY_SPHERE_LIFE		(3)		//���C�t

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CEnemySphere : public CEnemy
{
public:

	CEnemySphere();				//�R���X�g���N�^
	~CEnemySphere();			//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemySphere *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CMover::MOVER_TYPE moverType);

private:
	//�����o�֐�
	void MoveType(void);								//�G�̓�����
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_ENEMY_SPHERE_H_