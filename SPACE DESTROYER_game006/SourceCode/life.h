//===========================================
//���C�t����
//Authore:��������
//===========================================
#ifndef _LIFE_H_
#define _LIFE_H_
#include "scene.h"
#include "polygon.h"

//================================================
//�}�N����`
//================================================
#define MAX_LIFE_POLYGON (8)				//�|���S���̍ő吔
#define START_LIFE_POLYGON (5)				//�|���S���̍ő吔
#define LIFE_POLYGON_WIDTH (60.0f)			//�|���S���̕�
#define LIFE_POLYGON_HEIGHT (60.0f)			//�|���S���̍���

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CLife : public CScene
{
public:
	CLife(int nPriority = PRIORITY_UI);		//�R���X�g���N�^
	~CLife();								//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetLife(int nLife);			//�ݒ�
	void AddLife(int nValue);			//���Z
	void SubtractLife(int nValue);		//���Z
	int GetLife(void);

	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	CPolygon *m_apPolygon[MAX_LIFE_POLYGON];		//polygon�̃C���X�^���X
	int m_nLife;									//���C�t
	D3DXVECTOR3 m_pos;								//�ʒu
	static LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̃|�C���^

};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_LIFE_H_