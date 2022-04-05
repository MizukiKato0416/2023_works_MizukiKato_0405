//===========================================
//�p���[�A�b�v�̃A�C�e���𗎂Ƃ��G�̏���
//Authore:��������
//===========================================
#ifndef _ENEMY_ITEM_POWER_H_
#define _ENEMY_ITEM_POWER_H_
#include "enemy.h"

//================================================
//�}�N����`
//================================================
#define ENEMY_ITEM_POWER_WIDTH		(70.0f)	//�|���S���̕�
#define ENEMY_ITEM_POWER_HEIGHT		(70.0f)	//�|���S���̍���
#define ENEMY_ITEM_POWER_LIFE		(1)		//���C�t

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CEnemyItemPower : public CEnemy
{
public:

	CEnemyItemPower();				//�R���X�g���N�^
	~CEnemyItemPower();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemyItemPower *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CMover::MOVER_TYPE moverType);

private:
	//�����o�֐�
	void MoveType(void);								//�G�̓�����
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_ENEMY_ITEM_POWER_H_