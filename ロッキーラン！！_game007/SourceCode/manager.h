//===========================================
//�}�l�[�W������
//Author:��������
//===========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "scene.h"
#include "camera.h"
#include "light.h"

//�O���錾
class CRenderer;
class CInputKeyboard;
class CInputPadX;
class CTitle;
class CTexture;
class CXload;
class CMenu;
class CGame01;
class CResult;
class CFade;
class CTutorial;
class CPlayData;
class CSound;
class CMotion;

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
		MODE_TITLE = 0,			//�^�C�g��
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

	static CRenderer *GetRenderer(void);				//�����_���[�擾����
	static CInputKeyboard *GetInputKeyboard(void);		//�L�[�{�[�h�擾����
	static CInputPadX *GetInputPadX(void);				//�p�b�h(X)�擾����
	static CTitle *GetTitle(void);						//�^�C�g���擾����
	static CMenu *GetMenu(void);						//���j���[�擾����
	static CTutorial *GetTutorial(void);				//�`���[�g���A������
	static CGame01 *GetGame01(void);					//�Q�[��01�擾����
	static CResult *GetResult(void);					//���U���g�擾����
	static CTexture *GetTexture(void);					//�e�N�X�`���擾����
	static CXload *GetXload(void);						//x�t�@�C���ǂݍ��ݎ擾����
	static void SetMode(MODE mode);						//���[�h�ݒ�
	static MODE GetMode(void);							//���[�h�擾
	static CFade *GetFade(void);						//�t�F�[�h�擾����
	static CPlayData *GetPlayData(void);				//�v���C�f�[�^�擾����
	static CCamera **GetCamera(void);					//�J�����擾����
	static CLight *GetLight(void);						//���C�g�擾����
	static CSound *GetSound(void);						//�T�E���h�擾����

private:
	static CTitle *m_pTitle;							//�^�C�g���̃|�C���^
	static CMenu *m_pMenu;								//���j���[�̃|�C���^
	static CTutorial *m_pTutorial;						//�`���[�g���A���̃|�C���^
	static CGame01 *m_pGame01;							//�Q�[��01�̃|�C���^
	static CResult *m_pResult;							//���U���g�̃|�C���^
	static CRenderer *m_pRenderer;						//�����_���[�̃|�C���^
	static CInputKeyboard *m_pInputKeyboard;			//�L�[�{�[�h�̃|�C���^
	static CInputPadX *m_pInputPadX;					//�p�b�h(X)�̃|�C���^
	static CTexture *m_pTexture;						//�e�N�X�`���̃|�C���^
	static CXload *m_pXload;							//x�t�@�C���ǂݍ��݂̃|�C���^
	static MODE m_mode;									//���[�h
	static CFade *m_pFade;								//�t�F�[�h�̃|�C���^
	static CPlayData *m_pPlayData;						//�v���C�f�[�^�N���X�̃|�C���^
	static CCamera *m_apCamera[MAX_CAMERA];				//�J�����̃|�C���^
	static CLight *m_apLight[MAX_LIGHT];				//���C�g�̃|�C���^
	static CSound *m_pSound;							//�T�E���h�̃|�C���^
	static CMotion *m_pMotion;							//���[�V�����̃|�C���^
};


#endif // !_MANAGER_H_