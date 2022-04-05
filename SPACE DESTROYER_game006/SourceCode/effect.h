//===========================================
//�e����
//Authore:��������
//===========================================
#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "scene2D.h"

//================================================
//�}�N����`
//================================================
#define EFFECT_WIDTH (50.0f)			//�|���S���̕�
#define EFFECT_HEIGHT (50.0f)			//�|���S���̍���

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CEffect : public CScene2D
{
public:
	//�G�t�F�N�g�̎��
	typedef enum
	{
		EFFECT_TYPE_NONE = 0,
		EFFECT_TYPE_NORMAL,			//����
		EFFECT_TYPE_BOSS_LASER,		//�{�X�̃��[�U�[�e����
		EFFECT_TYPE_MAX
	} EFFECT_TYPE;

	CEffect(int nPriority = PRIORITY_EFFECT);				//�R���X�g���N�^
	~CEffect();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLORVALUE col);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3	size, D3DXVECTOR3 move, D3DCOLORVALUE col, EFFECT_TYPE type);

private:
	//�����o�֐�
	void MoveType(void);								//�^�C�v�ɂ�铮��

	D3DXVECTOR3	m_size;									//�T�C�Y
	D3DCOLORVALUE	m_col;								//�J���[
	D3DXVECTOR3 m_move;									//�ړ���
	static LPDIRECT3DTEXTURE9 m_pTexture;				//���L�e�N�X�`���̃|�C���^
	EFFECT_TYPE m_type;									//�G�t�F�N�g�̎��
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_EFFECT_H_