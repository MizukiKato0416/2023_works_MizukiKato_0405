//===========================================
//���b�V���X�t�B�A����
//Author:KatoMizuki
//===========================================
#ifndef _MESH_SPHERE_H_
#define _MESH_SPHERE_H_
#include "object.h"
#include "main.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMeshSphere : public CObject
{
public:
	CMeshSphere(int nPriority = PRIORITY_NONE);	//�R���X�g���N�^
	~CMeshSphere();								//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeshSphere *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nLine, int nVertical);
	//�e�N�X�`���ݒ菈��
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;			//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;							//�|���S���̈ʒu
	D3DXVECTOR3	m_size;							//�T�C�Y
	D3DXVECTOR3 m_rot;							//����
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	int m_nVertical;							//�c�̃|���S���̐� 
	int m_nLine;								//���̃|���S���̐�
};

#endif // !_MESH_SPHERE_H_