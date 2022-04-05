//===========================================
//�e����
//Authore:��������
//===========================================
#ifndef _BULLET_H_
#define _BULLET_H_
#include "scene2D.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CBullet : public CScene2D
{
public:
	CBullet(int nPriority = PRIORITY_BULLET_ENEMY);				//�R���X�g���N�^
	~CBullet();												//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	D3DXVECTOR3 m_move;									//�|���S���̈ړ���
	D3DXVECTOR3	m_size;									//�T�C�Y
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_BULLET_H_