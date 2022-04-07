//===========================================
//�G�̒e����
//Author:KatoMizuki
//===========================================
#ifndef _BULLET_ENEMY_H_
#define _BULLET_ENEMY_H_
#include "billboard.h"

//�O���錾

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CBulletEnemy : public CBillboard
{
public:
	CBulletEnemy(int nPriority = PRIORITY_ENEMY_BULLET);		//�R���X�g���N�^
	~CBulletEnemy();										//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBulletEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);


private:
	//�����o�֐�
	void CollisionPlayer(void);		//�v���C���[�Ƃ̓����蔻��

	D3DXVECTOR3 m_move;				//�ړ���
	int m_nLife;					//����
};

#endif // !_BULLET_ENEMY_H_