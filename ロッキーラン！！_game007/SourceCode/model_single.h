//===========================================
//���f���P�̂��o������
//Author:��������
//===========================================
#ifndef _MODEL_SINGLE_H_
#define _MODEL_SINGLE_H_
#include "scene.h"
#include "x_load.h"
#include "scene.h"

//�O���錾
class CModel;
class CControl;

//================================================
//�}�N����`
//================================================
#define MODEL_SINGLE_DELETE_TIME	(240)	//�����Ă��鎞��

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CModelSingle : public CScene
{
public:
	//���f���̓����̎��
	typedef enum
	{
		MODEL_SINGLE_TYPE_NONE = 0,
		MODEL_SINGLE_TYPE_UP_WALL,			//�㉺�����(���������ړ�)
		MODEL_SINGLE_TYPE_DOWN_WALL,		//�㉺�����(����������ړ�)
		MODEL_SINGLE_TYPE_UNINIT_FLOOR,		//�Ȃ��Ȃ鏰
		MODEL_SINGLE_TYPE_GOAL,				//�S�[���̏�
		MODEL_SINGLE_TYPE_START_FLOOR,		//�X�^�[�g�̏�
		MODEL_SINGLE_TYPE_MIDDLE1_FLOOR,	//���Ԓn�_1�̏�
		MODEL_SINGLE_TYPE_MIDDLE2_FLOOR,	//���Ԓn�_2�̏�
		MODEL_SINGLE_TYPE_ICE_FLOOR,		//�X�̏�
		MODEL_SINGLE_TYPE_SPRING,			//�o�l
		MODEL_SINGLE_TYPE_MAX
	} MODEL_SINGLE_TYPE;

	CModelSingle(int nPriority = PRIORITY_MODEL);				//�R���X�g���N�^
	~CModelSingle();											//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CModelSingle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CXload::X_TYPE type, CModel *pParent, MODEL_SINGLE_TYPE modelType);
	static bool SimpleCollision(CScene *pScene);	//��]��������_���ȓ����蔻��
	bool GetDeleteObject(void);						//���������ǂ����̎擾����

private:
	//�����o�֐�

	D3DXVECTOR3 m_pos;								//�ʒu
	D3DXVECTOR3 m_posOld;							//1�t���[���O�̈ʒu
	D3DXVECTOR3 m_move;								//�|���S���̈ړ���
	D3DXVECTOR3	m_size;								//�T�C�Y
	D3DXVECTOR3 m_rot;								//����
	CModel *m_pModel;								//���f���̃|�C���^
	D3DXMATRIX m_mtxWorld;							//���[���h�}�g���b�N�X
	CModel *m_pParent;								//�e���f���ւ̃|�C���^
	CXload::X_TYPE m_type;							//�o�����f���̎��
	MODEL_SINGLE_TYPE m_modelType;					//���f���̓����̎��
	bool m_bDelete;									//�����Ă��邩�ǂ���
	int m_nCntDelete;								//�����Ă���ǂꂭ�炢����
	CControl *m_pControl;							//�R���g���[���N���X�̃|�C���^
};

#endif // !_MODEL_SINGLE_H_