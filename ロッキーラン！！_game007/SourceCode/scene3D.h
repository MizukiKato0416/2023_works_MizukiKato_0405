//===========================================
//3D�|���S������
//Author:��������
//===========================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_
#include "scene.h"
#include "main.h"

//================================================
//�}�N����`
//================================================
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)		//���_�t�H�[�}�b�g3D
#define VERTEX_3D_NUM (4)														//���_��

//========================================================
//�\���̂̒�`3D
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//���_���W
	D3DXVECTOR3 nor;		//�@���x�N�g��
	D3DCOLOR col;			//���_�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`�����W
} VERTEX_3D;

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CScene3D : public CScene
{
public:
	CScene3D(int nPriority = PRIORITY_MODEL);	//�R���X�g���N�^
	~CScene3D();								//�f�X�g���N�^

												//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScene3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nPriolty);
	D3DXVECTOR3 GetPos(void);
	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void SetTex(int nPattern, int nMaxPattern);
	void SetTex(float fMoveTexU, float fMoveTexV);
	void SetCol(D3DCOLORVALUE col);
	void SetCol(D3DXCOLOR col);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

private:

protected:
	D3DXVECTOR3 m_pos;						//�|���S���̈ʒu
	D3DXVECTOR3	m_size;						//�T�C�Y
	D3DXVECTOR3 m_rot;						//����
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X
};

#endif // !_SCENE3D_H_