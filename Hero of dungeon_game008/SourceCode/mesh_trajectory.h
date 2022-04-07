//===========================================
//���b�V���O�Տ���
//Author:KatoMizuki
//===========================================
#ifndef _MESH_TRAJECTORY_H_
#define _MESH_TRAJECTORY_H_
#include "object.h"
#include "main.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMeshTrajectory : public CObject
{
public:
	CMeshTrajectory(int nPriority = PRIORITY_TRAJECTORY);	//�R���X�g���N�^
	~CMeshTrajectory();										//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeshTrajectory *Create(int nLine, D3DXMATRIX *pMtx, D3DXVECTOR3 offset1, D3DXVECTOR3 offset2, D3DXCOLOR col1, D3DXCOLOR col2);
	
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);								//�e�N�X�`���ݒ菈��
	static bool CollisionSphere(CObject *pSubjectObject, float fObjectRadius);	//���Ɗe���_�Ƃ̏Փ˔���

private:
	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_aOffset[2];					//���[�̃I�t�Z�b�g
	D3DXMATRIX m_aMtxPoint[2];					//���[�̃��[���h�}�g���b�N�X
	D3DXMATRIX *m_pMtxParent;					//�e�̃��[���h�}�g���b�N�X�ւ�
	D3DXCOLOR m_aCol[2];						//���[�̊�̐F
	int m_nLine;								//���̃|���S���̐�
	std::vector<D3DXVECTOR3> m_aPosPoint;		//�e���_���W
	std::vector<D3DXCOLOR> m_aColPoint;			//�e���_�J���[
};

#endif // !_MESH_TRAJECTORY_H_