//===========================================
//�^�C�g������
//Author:��������
//===========================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"
#include "camera.h"
#include "light.h"

//================================================
//�O���錾
//================================================
class CUi;
class CScene2D;

//================================================
//�}�N����`
//================================================
#define MAX_TITLE_UI_NUM			(4)				//�|���S���̊Ǘ��ԍ�
#define TITLE_LOGO_POSY				(0.0f)			//�^�C�g�����S��posY
#define TITLE_LOGO_SIZEX			(1000.0f)		//�^�C�g�����S�̃T�C�YX
#define TITLE_LOGO_SIZEY			(600.0f)		//�^�C�g�����S�̃T�C�YX
#define TITlE_PRESS_POSY			(600.0f)		//Press Enter��posY
#define TITlE_PRESS_SIZEX			(550.0f)		//Press Enter�̃T�C�YX
#define TITlE_PRESS_SIZEY			(250.0f)		//Press Enter�̃T�C�YY
#define TITlE_PLAYER_1P_POSY		(1580.0f)		//1P�摜��posY
#define TITlE_PLAYER_1P_SIZEX		(350.0f)		//1P�摜�̃T�C�YX
#define TITlE_PLAYER_1P_SIZEY		(350.0f)		//1P�摜�̃T�C�YY
#define TITlE_PLAYER_2P_POSY		(1350.0f)		//2P�摜��posY
#define TITlE_PLAYER_2P_SIZEX		(300.0f)		//2P�摜�̃T�C�YX
#define TITlE_PLAYER_2P_SIZEY		(300.0f)		//2P�摜�̃T�C�YY
#define TITLE_TO_RESULT_COUNT		(600)			//���U���g�ɍs���܂ł̎���

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CTitle : public CScene
{
public:
	CTitle(int nPriority = PRIORITY_NONE);		//�R���X�g���N�^
	~CTitle();									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CUi *GetUi(void);			//UI�̎擾����

private:
	CUi *m_apUi[MAX_TITLE_UI_NUM];		//UI�̃|�C���^
	CScene2D *m_pScene2D;				//Scene2D�̃|�C���^
	int m_nTitleCounter;				//���U���g�ɍs���܂ł̂܂ł̎���
};

#endif // !_TITLE_H_