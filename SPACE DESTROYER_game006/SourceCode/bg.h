//===========================================
//�w�i����
//Authore:��������
//===========================================
#ifndef _BG_H_
#define _BG_H_
#include "scene.h"

//�O���錾
class CScene2D;
//================================================
//�}�N����`
//================================================
#define MAX_BG_POLYGON (3)		//�|���S���̍ő吔

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CBg : public CScene
{
public:
	CBg(int nPriority = PRIORITY_BG_0);					//�R���X�g���N�^
	~CBg();												//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_BG_POLYGON];			//�e�N�X�`���ւ̃|�C���^
	CScene2D *m_apScene2D[MAX_BG_POLYGON];							//Scene2D�̃C���X�^���X
	D3DXVECTOR3	m_size;												//�T�C�Y
	float m_fPosTexV[MAX_BG_POLYGON];								//�e�N�X�`��V���W
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_BG_H_