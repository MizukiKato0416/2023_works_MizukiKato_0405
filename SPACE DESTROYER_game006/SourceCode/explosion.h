//===========================================
//��������
//Authore:��������
//===========================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "scene2D.h"

//================================================
//�}�N����`
//================================================
#define EXPLOSION_WIDTH					(50.0f)		//�|���S���̕�
#define EXPLOSION_HEIGHT				(50.0f)		//�|���S���̍���
#define EXPLOSION_BOSS_UNINIT_WIDTH		(100.0f)	//�{�X��|�����Ƃ��̃|���S���̕�
#define EXPLOSION_BOSS_UNINIT_HEIGHT	(100.0f)	//�{�X��|�����Ƃ��̃|���S���̍���
#define PATTERN_FRAME					(4)			//�p�^�[�����؂�ւ��܂ł̃t���[��
#define MAX_PATTERN						(8)			//�p�^�[���̍ő�l

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CExplosion : public CScene2D
{
public:
	CExplosion(int nPriority = PRIORITY_EXPLOSION);				//�R���X�g���N�^
	~CExplosion();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3	size);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//���L�e�N�X�`���̃|�C���^
	int m_nCounterAnim;						//�J�E���^�[
	int m_nPatternAnim;						//�p�^�[��No
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_EXPLOSION_H_