//============================================================================
// �r���{�[�h���� [billboard.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "scene.h"
#include "scene3D.h"

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CBillboard : public CScene
{
public:
	CBillboard(int nPriority = PRIORITY_PLAYER);	//�R���X�g���N�^
	~CBillboard();								//�f�X�g���N�^

												//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBillboard *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nPriolty);
	D3DXVECTOR3 GetPos(void);
	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void SetTex(int nPattern, int nMaxPattern);
	void SetTex(float fMoveTexU, float fMoveTexV);
	void SetCol(D3DCOLORVALUE col);
	void SetCol(D3DXCOLOR col);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

protected:
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						//�|���S���̈ʒu
	D3DXVECTOR3	m_size;						//�T�C�Y
	D3DXVECTOR3 m_rot;						//����
	D3DXVECTOR3 m_move;						//�ړ���
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X
};

#endif // !_BILLBOARD_H_