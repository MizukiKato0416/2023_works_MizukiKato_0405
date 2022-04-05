//===========================================
//�|�[�Y����
//Authore:��������
//===========================================
#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"

//================================================
//�}�N����`
//================================================
#define PAUSE_SELECT_COL					(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))		//�I�𒆂̐F(������)
#define PAUSE_DEFAULT_COL					(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f))		//�f�t�H�̐F(�O���[�̕�)

#define PAUSE_FRAME_SIXEX					(770.0f)								//�|�[�Y�t���[����sizeX
#define PAUSE_FRAME_SIXEY					(570.0f)								//�|�[�Y�t���[����sizeY
#define PAUSE_CHOICES_SPACE					(100.0f)								//�I�����̊Ԋu	
#define PAUSE_UI_SIZEX						(370.0f)								//�I������sizeX
#define PAUSE_UI_SIZEY						(90.0f)									//�I������sizeY
#define PAUSE_START_BUTTON_POSY				(180.0f)								//�I����:�ĊJ��posY
#define PAUSE_EXIT_BUTTON_POSY				(320.0f)								//�I����:���j���[�ɖ߂��posY
#define PAUSE_RESTART_BUTTON_POSY			(460.0f)								//�I����:���X�^�[�g��posY
//========================================================
//�\���̂̒�`
//========================================================

//========================================================
//�O���錾
//========================================================
class CUi;
class CScene2D;
class CManager;
//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CPause : public CScene
{
public:
	CPause(int nPriority = PRIORITY_PAUSE);				//�R���X�g���N�^
	~CPause();				//�f�X�g���N�^

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
		SELECT_START,			//�ĊJ�{�^��
		SELECT_EXIT,			//���j���[�ɖ߂�{�^��
		SELECT_RESTART,			//���X�^�[�g�{�^��
		SELECT_MAX
	}SELECT;

	CUi *m_apSelect[SELECT_MAX];		//�e�I����
	CScene2D *m_pScene2D;				//Scene2D�̃|�C���^
	CManager *m_pManager;				//Manager�̃|�C���^
	int m_nSelect;						//���̑I����
	static bool m_bPause;				//�|�[�Y��ʂ��ǂ���
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_PAUSE_H_