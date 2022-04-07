//===========================================
//���f���P�̂��o������
//Author:KatoMizuki
//===========================================
#ifndef _MODEL_SINGLE_H_
#define _MODEL_SINGLE_H_
#include "object.h"
#include "x_load.h"

//�O���錾
class CModel;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CModelSingle : public CObject
{
public:
	//�����o�֐�
	CModelSingle(int nPriority = PRIORITY_MODEL);				//�R���X�g���N�^
	~CModelSingle();											//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CModelSingle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CXload::X_TYPE type, CModel *pParent, bool Collision);
	static bool SimpleCollision(CObject *pObject);	//��]��������_���ȓ����蔻��
	static bool Collision(CObject *pObject);		//y������]�����Ă��������蔻��
	static bool CollisionAny(CObject *pObject);		//�����̏Փ˔���

private:
	//�����o�ϐ�
	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3	m_size;					//�T�C�Y
	D3DXVECTOR3 m_rot;					//����
	D3DXVECTOR3 m_move;					//�ړ���
	CModel *m_pModel;					//���f���̃|�C���^
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X
	CModel *m_pParent;					//�e���f���ւ̃|�C���^
	CXload::X_TYPE m_type;				//�o�����f���̎��
	bool m_bCollision;					//�����蔻������邩�ǂ���
};

#endif // !_MODEL_SINGLE_H_