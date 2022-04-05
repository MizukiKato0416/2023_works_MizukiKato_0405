//===========================================
//�A�C�e������
//Authore:��������
//===========================================
#ifndef _ITEM_H_
#define _ITEM_H_
#include "scene2D.h"

//================================================
//�}�N����`
//================================================
#define ITEM_WIDTH				(30.0f)				//�|���S���̕�
#define ITEM_HEIGHT				(30.0f)				//�|���S���̍���
#define ITEM_SCORE_WIDTH		(20.0f * 1.9f)		//�X�R�A�A�C�e���̃|���S���̕�
#define ITEM_SCORE_HEIGHT		(30.0f * 1.9f)		//�X�R�A�A�C�e���̃|���S���̍���
#define ITEM_SCROLL_SPEED		(1.0f)				//�X�N���[���̃X�s�[�h
#define ITEM_COLECT_SPEED		(10.0f)				//�A�C�e�����v���C���[�ɏW�܂�X�s�[�h
#define ITEM_EFFECT_INTERVAL	(2)					//�G�t�F�N�g�����������Ԋu

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CItem : public CScene2D
{
public:
	typedef enum
	{
		ITEM_TYPE_NONE = 0,
		ITEM_TYPE_SPEED,
		ITEM_TYPE_POWER,
		ITEM_TYPE_SCORE,
		ITEM_TYPE_MAX
	} ITEM_TYPE;

	CItem(int nPriority = PRIORITY_ITEM);				//�R���X�g���N�^
	~CItem();											//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, ITEM_TYPE type);


private:
	//�����o�֐�
	bool Collision(void);					//�����蔻��
	void Move(void);						//�����̏���

	static LPDIRECT3DTEXTURE9 m_pTexture;	//���L�e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_move;						//�ړ���
	D3DXVECTOR3	m_size;						//�T�C�Y
	D3DXVECTOR3 m_scrollSpeed;				//�X�N���[���̃X�s�[�h
	ITEM_TYPE m_type;						//�A�C�e���̃^�C�v
	int m_nEfectCounter;					//�G�t�F�N�g�����Ԋu�J�E���^�[
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_ITEM_H_