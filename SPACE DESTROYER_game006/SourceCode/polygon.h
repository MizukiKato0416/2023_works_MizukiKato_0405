//===========================================
//�i���o�[����
//Authore:��������
//===========================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

//================================================
//�}�N����`
//================================================
#define FVF_VERTEX_2D_POLYGON (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//���_�t�H�[�}�b�g
#define VERTEX_NUM_POLYGON (4)												//���_��

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//���_���W
	float rhw;				//1.0f�ŌŒ�
	D3DCOLOR col;			//���_�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`�����W
} VERTEX_2D_POLYGON;

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CPolygon
{
public:
	CPolygon();			//�R���X�g���N�^
	~CPolygon();							//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						//�|���S���̈ʒu
	D3DXVECTOR3	m_size;						//�T�C�Y
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_POLYGON_H_