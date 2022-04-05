//=======================================================================
//���j���[�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#include "main.h"
#include "menue.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "pad.h"
#include "ui.h"


//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureMenue = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMenue = NULL;		//���_�o�b�t�@�ւ̃|�C���^

//=======================================================================
//����������
//=======================================================================
void InitMenue(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//menue.jpg",
		&g_pTextureMenue);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMenue,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffMenue->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMenue->Unlock();

	PlaySound(SOUND_LABEL_MENU_BGM);
	InitUi();
	SetUi(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 4.0f, 0.0f), UITYPE_GAMESTART, 600.0f, 75.0f);
	SetUi(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 4.0f * 2.0f, 0.0f), UITYPE_TUTORIAL, 600.0f, 75.0f);
	SetUi(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 4.0f * 3.0f, 0.0f), UITYPE_BACKTITLE, 600.0f, 75.0f);
}

//=======================================================================
//�I������
//=======================================================================
void UninitMenue(void)
{
	UninitUi();
	StopSound(SOUND_LABEL_MENU_BGM);

	//�e�N�X�`���̔j��
	if (g_pTextureMenue != NULL)
	{
		g_pTextureMenue->Release();
		g_pTextureMenue = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMenue != NULL)
	{
		g_pVtxBuffMenue->Release();
		g_pVtxBuffMenue = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateMenue(void)
{
	int nSelect = GetPauseUi();
	UpdateUi();




	if (GetButtonTrigger(XINPUT_GAMEPAD_START) == true || GetKeyboardTrigger(DIK_SPACE) == true || GetButtonTrigger(XINPUT_GAMEPAD_B) == true)
	{
		if (nSelect == 0)
		{
			if (GetFade() == FADE_NONE)
			{
				SetFade(MODE_STAGE1);
				PlaySound(SOUND_LABEL_TITLE_DECIDE);
			}
		}
		else if (nSelect == 1)
		{
			if (GetFade() == FADE_NONE)
			{
				SetFade(MODE_DESCRIPTION);
				PlaySound(SOUND_LABEL_TITLE_DECIDE);
			}
		}
		else if (nSelect == 2)
		{
			if (GetFade() == FADE_NONE)
			{
				SetFade(MODE_TITLE);
				PlaySound(SOUND_LABEL_TITLE_DECIDE);
			}
		}
	}
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawMenue(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMenue, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureMenue);	//�e�N�X�`���̐ݒ�
												//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,					//�J�n���钸�_�̃C���f�b�N�X
		2);					//�`�悷��v���~�e�B�u��

	DrawUi();
}