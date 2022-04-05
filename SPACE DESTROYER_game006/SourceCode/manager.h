//===========================================
//�}�l�[�W������
//Authore:��������
//===========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "scene.h"

//�O���錾
class CRenderer;
class CInputKeyboard;
class CInputPadX;
class CSound;
class CTexture;
class CTitle;
class CMenu;
class CGame01;
class CResult;
class CFade;
class CPlayData;
class CTutorial;

//================================================
//�}�N����`
//================================================
#define MAX_STRINGS (128)

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CManager
{
public:
	//���[�h�̎��
	typedef enum
	{
		MODE_TITLE  = 0,		//�^�C�g��
		MODE_MENU,				//���j���[
		MODE_TUTORIAL,			//�`���[�g���A��
		MODE_GAME01,			//�Q�[��01
		MODE_RESULT,			//���U���g
		MODE_MAX
	} MODE;

	CManager();				//�R���X�g���N�^
	~CManager();			//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CInputPadX *GetInputPadX(void);
	static CSound *GetSound(void);
	static CTexture *GetTexture(void);
	static CFade *GetFade(void);
	static CPlayData *GetPlayData(void);
	static CTitle *GetTitle(void);
	static CMenu *GetMenu(void);
	static CTutorial *GetTutorial(void);
	static CGame01 *GetGame01(void);
	static CResult *GetResult(void);
	static void SetMode(MODE mode);
	static MODE GetMode();


private:
	static CTitle *m_pTitle;
	static CMenu *m_pMenu;
	static CTutorial *m_pTutorial;
	static CGame01 *m_pGame01;
	static CResult *m_pResult;
	static MODE m_mode;

	static CRenderer *m_pRenderer;
	static CInputKeyboard *m_pInputKeyboard;
	static CInputPadX *m_pInputPadX;
	static CSound *m_pSound;
	static CTexture *m_pTexture;
	static CFade *m_pFade;
	static CPlayData *m_pPlayData;
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_MANAGER_H_