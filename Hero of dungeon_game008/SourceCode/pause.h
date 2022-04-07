//===========================================
//�|�[�Y����
//Author:KatoMizuki
//===========================================
#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "object.h"
#include "main.h"

//�O���錾
class CObject2D;
class CManager;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CPause : public CObject
{
public:
	CPause(int nPriority = PRIORITY_PAUSE);			//�R���X�g���N�^
	~CPause();										//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static bool GetPause(void);
	static bool SetPause(bool bPause);
	static CPause *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	//��ʑJ�ڂ̑I�����{�^��
	typedef enum
	{
		SELECT_START = 0,		//�ĊJ�{�^��
		SELECT_EXIT,			//���j���[�ɖ߂�{�^��
		SELECT_MAX
	}SELECT;

	CObject2D *m_apObject2D[SELECT_MAX];	//UI
	CObject2D *m_pObject2D;					//�|�[�Y�̃t���[��
	int m_nSelect;							//�I����
	static bool m_bPause;					//�|�[�Y��ʂ��ǂ���
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_PAUSE_H_