//=============================================================================
// �Q�[��GO�����R���g���[������ [control_game_start.h]
// Author : ��������
//=============================================================================
#ifndef _CONTROL_GAME_START_H_
#define _CONTROL_GAME_START_H_

#include "control.h"

//�O���錾
class CScene;

//================================================
//�}�N����`
//================================================
#define COL_SPEED		(0.025f)	//���l�̕ϓ����鑁��
#define SMALL_SPEED		(25.0f)		//�������������Ȃ鑁��
#define MIN_SIZE		(300.0f)	//�ŏ��T�C�Y

//*****************************************************************************
// �Q�[��GO�����R���g���[���N���X
//*****************************************************************************
class CControlGameStart : public CControl
{
public:
	CControlGameStart();					// �R���X�g���N�^
	~CControlGameStart();					// �f�X�g���N�^
	HRESULT Init(void);						// ����������
	void Uninit(void);						// �I������
	void Update(CScene *pScene);			// �X�V����
	static CControlGameStart *Create();	// ��������

private:
	int m_nCount;							// �J�E���g
	D3DXVECTOR3 MIN_Size;					// �ŏ��T�C�Y
	D3DXCOLOR m_col;						//�|���S���̐F
};

#endif	//_CONTROL_TITLE_LOGO_H_