//===========================================
//���b�V���t�B�[���h����
//Author:KatoMizuki
//===========================================
#ifndef _MESH_FIELD_H_
#define _MESH_FIELD_H_
#include "object.h"
#include "main.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMeshField : public CObject
{
public:
	CMeshField(int nPriority = PRIORITY_MESH_FIELD);	//�R���X�g���N�^
	~CMeshField();										//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeshField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nLine, int nVertical);
	//�e�N�X�`���ݒ菈��
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	//�����蔻��(�������͓����蔻������锼�a)
	static bool Collision(CObject *pSubjectObject, float fRadius);
	//���_���W�ݒ菈��
	void SetVtxPos(int nNumVtx, D3DXVECTOR3 pos);
	//���_���W�擾����
	D3DXVECTOR3 GetVtxPos(int nNumVtx) { return m_bufferPos[nNumVtx]; }
	//�C���f�b�N�X�o�b�t�@�[�̒��_�ʒu�擾����
	void GetIndexPos(void);						
private:
	//�����o�֐�

	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;			//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;							//�|���S���̈ʒu
	std::vector<D3DXVECTOR3> m_indexPos;		//�C���f�b�N�X�o�b�t�@�[�̒��_�ʒu
	std::vector<D3DXVECTOR3> m_indexSavePos;	//�C���f�b�N�X�o�b�t�@�[�̒��_�ʒu�ۑ��p
	std::vector<D3DXVECTOR3> m_indexRot;		//�C���f�b�N�X�o�b�t�@�[�̒��_����
	std::vector<D3DXVECTOR3> m_bufferPos;		//�o�b�t�@�[�̒��_�ʒu
	D3DXVECTOR3	m_size;							//�T�C�Y
	D3DXVECTOR3 m_rot;							//����
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	std::vector<D3DXMATRIX> m_indexMtxWorld;	//�C���f�b�N�X�o�b�t�@���[���h�}�g���b�N�X
	int m_nVertical;							//�c�̃|���S���̐� 
	int m_nLine;								//���̃|���S���̐�
};

#endif // !_MESH_FIELD_H_