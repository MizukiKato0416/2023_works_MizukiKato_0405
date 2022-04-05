//===========================================
//���j���[����
//Authore:��������
//===========================================
#ifndef _MENU_H_
#define _MENU_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"

//�O���錾
class CTexture;
class CScene2D;

//================================================
//�}�N����`
//================================================

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMenu : public CScene
{
public:
	//�I����
	typedef enum
	{
		SELECT_MENU_TYPE_NONE = 0,
		SELECT_MENU_TYPE_TUTORIAL,		//Tutorial
		SELECT_MENU_TYPE_GAME_START,	//GameStart
		SELECT_MENU_TYPE_EXIT,			//Exit
		SELECT_MENU_TYPE_MAX			//�I�����ő�l
	} SELECT_MENU_TYPE;

	CMenu();				//�R���X�g���N�^
	~CMenu();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTexture *GetTexture(void);
	static int GetSelect(void);
	static int GetFrame(void);
	static void SetFrame(int nCntFrame);
	
private:
	static CTexture *m_pTexture;
	static CScene2D *m_pScene2D;
	static int m_nSelect;			//�ǂ̑I�������I������Ă��邩
	static int m_nCntFrame;			//ui�𓮂������߂̃t���[���J�E���g
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_MENU_H_