//===========================================
//�}�l�[�W������
//Author:KatoMizuki
//===========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "object.h"
#include "camera.h"
#include "light.h"

//�O���錾
class CRenderer;
class CInputKeyboard;
class CInputPadX;
class CInputPadD;
class CInputMouse;
class CTexture;
class CXload;
class CTitle;
class CMenu;
class CTutorial;
class CGame01;
class CGame02;
class CGame03;
class CResult;
class CFade;
class CMotionRoad;
class CPlayData;
class CSound;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CManager
{
public:
	//���[�h�̎��
	enum class MODE
	{
		TITLE = 0,		//�^�C�g��
		MENU,			//���j���[
		TUTORIAL,		//�`���[�g���A��
		GAME01,			//�Q�[��01
		GAME02,			//�Q�[��02
		GAME03,			//�Q�[��03
		RESULT,			//���U���g
		MAX
	};

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CManager *GetInstance(void);					//�C���X�^���X�擾����
	static CRenderer *GetRenderer(void);				//�����_���[�擾����
	static CInputKeyboard *GetInputKeyboard(void);		//�L�[�{�[�h�擾����
	static CInputPadX *GetInputPadX(void);				//�p�b�h(X)�擾����
	static CInputPadD *GetInputPadD(void);				//�p�b�h(D)�擾����
	static CInputMouse *GetInputMouse(void);			//�}�E�X�擾����
	static CLight *GetLight(void);						//���C�g�擾����
	static CTexture *GetTexture(void);					//�e�N�X�`���擾����
	static CCamera** GetCamera(void);					//�J�����擾����
	static CXload *GetXload(void);						//x�t�@�C���ǂݍ��ݎ擾����
	static CTitle *GetTitle(void);						//�^�C�g���擾����
	static CMenu *GetMenu(void);						//���j���[�擾����
	static CTutorial *GetTutorial(void);				//�`���[�g���A���擾����
	static CGame01 *GetGame01(void);					//�Q�[��01�擾����
	static CGame02 *GetGame02(void);					//�Q�[��02�擾����
	static CGame03 *GetGame03(void);					//�Q�[��03�擾����
	static CResult *GetResult(void);					//���U���g�擾����
	static void SetMode(MODE mode);						//���[�h�ݒ�
	static MODE GetMode(void);							//���[�h�擾
	static CFade *GetFade(void);						//�t�F�[�h�擾����
	static CMotionRoad *GetMotionRoad(void);			//���[�V�������[�h�擾����
	static CPlayData *GetPlayData(void);				//�v���C�f�[�^�擾����
	static CSound *GetSound(void);						//�T�E���h�擾����

private:
	//�����o�֐�
	CManager();				//�R���X�g���N�^
	~CManager();			//�f�X�g���N�^

	static CManager *s_pManager;						//�}�l�[�W���[�̃C���X�^���X
	static CRenderer *m_pRenderer;						//�����_���[�̃|�C���^
	static CInputKeyboard *m_pInputKeyboard;			//�L�[�{�[�h�̃|�C���^
	static CInputPadX *m_pInputPadX;					//�p�b�h(X)�̃|�C���^
	static CInputPadD *m_pInputPadD;					//�p�b�h(D)�̃|�C���^
	static CInputMouse *m_pInputMouse;					//�}�E�X�̃|�C���^
	static CLight *m_apLight[MAX_LIGHT];				//���C�g�̃|�C���^
	static CTexture *m_pTexture;						//�e�N�X�`���̃|�C���^
	static CCamera* m_apCamera[MAX_CAMERA];				//�J�����̃|�C���^
	static CXload *m_pXload;							//x�t�@�C���ǂݍ��݂̃|�C���^
	static CTitle *m_pTitle;							//�^�C�g���̃|�C���^
	static CMenu *m_pMenu;								//���j���[�̃|�C���^
	static CTutorial *m_pTutorial;						//�`���[�g���A���̃|�C���^
	static CGame01 *m_pGame01;							//�Q�[��01�̃|�C���^
	static CGame02 *m_pGame02;							//�Q�[��02�̃|�C���^
	static CGame03 *m_pGame03;							//�Q�[��03�̃|�C���^
	static CResult *m_pResult;							//���U���g�̃|�C���^
	static MODE m_mode;									//���[�h
	static CFade *m_pFade;								//�t�F�[�h�̃|�C���^
	static CMotionRoad *m_pMotionRoad;					//���[�V�������[�h�̃|�C���^
	static CPlayData *m_pPlayData;						//�v���C�f�[�^�̃|�C���^
	static CSound *m_pSound;							//�T�E���h�̃|�C���^
};


#endif // !_MANAGER_H_