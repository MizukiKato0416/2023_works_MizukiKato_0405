//=======================================================================
//���C��(�V�X�e���n)����
//Aouthor: �����@����
//=======================================================================

#ifndef _MAIN_H_
#define _MAIN_H_

//�C���N���[�h�t�@�C��
#include <windows.h>
#include "d3dx9.h"			//�`��ɕK�v
#define DIRECTINPUT_VERSION (0x0800)	//�r���h���̌x���Ή������p�}�N��
#include "dinput.h"						//���͏����ɕK�v
#include "xaudio2.h"					//�T�E���h�����ɕK�v
#include <time.h>

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")			//�`��ɕK�v
#pragma comment(lib,"d3dx9.lib")		//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")		//DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"dinput8.lib")		//���͏����ɕK�v

//========================================================
//�}�N����`
//========================================================
#define SCREEN_WIDTH (1280)		//�E�B���h�E�̕�
#define SCREEN_HEIGHT (720)		//�E�B���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)


//========================================================
//��ʁi���[�h�j�̎��
//========================================================
typedef enum
{
	MODE_TITLE = 0,
	MODE_RULE,
	MODE_TUTORIAL,
	MODE_STAGE1,
	MODE_GAME,
	MODE_STAGE3,
	MODE_RESULT,
	MODE_GAMEOVER,
	MODE_MAX
} MODE;

//========================================================
//�v���g�^�C�v�錾
//========================================================
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//���_���W
	float rhw;				//1.0f�ŌŒ�
	D3DCOLOR col;			//���_�J���[
	D3DXVECTOR2 tex;		//	�e�N�X�`�����W
} VERTEX_2D;


#endif // !_MAIN_H_