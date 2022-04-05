//=======================================================================
//���[����ʂɊւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "rule.h"
#include "input.h"
#include "fade.h"
#include "menu.h"
#include "select.h"
#include "sound.h"


//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================

LPDIRECT3DTEXTURE9 g_pTextureRule = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRule = NULL;		//���_�o�b�t�@�ւ̃|�C���^

//=======================================================================
//����������
//=======================================================================
void InitRule(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//menu000.jpg",
		&g_pTextureRule);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRule,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffRule->Lock(0, 0, (void**)&pVtx, 0);


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
	g_pVtxBuffRule->Unlock();

	InitMenu();
	InitSelect();

	SetSelect(D3DXVECTOR3(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f, 0.0f), 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.0f, 70.0f);
	SetMenu(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 4.0f, 0.0f), 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400.0f * 1.2f, 70.0f * 1.2f);
	SetMenu(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 4.0f * 2.0f, 0.0f), 1, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400.0f * 1.2f, 70.0f * 1.2f);
	SetMenu(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 4.0f * 3.0f, 0.0f), 2, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400.0f * 1.2f, 70.0f * 1.2f);

	PlaySound(SOUND_LABEL_RESULT_BGM);

}


//=======================================================================
//�I������
//=======================================================================
void UninitRule(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureRule != NULL)
	{
		g_pTextureRule->Release();
		g_pTextureRule = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRule != NULL)
	{
		g_pVtxBuffRule->Release();
		g_pVtxBuffRule = NULL;
	}

	UninitMenu();
	UninitSelect();
}


//=======================================================================
//�X�V����
//=======================================================================
void UpdateRule(void)
{
	Select *pSelect;
	//�Z���N�g�̎擾
	pSelect = GetSelect();

	//�G���^�[���������Ƃ��̏���
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (pSelect->bMenu1 == true)
		{
			if (pSelect->nType == 0)
			{
				SetFade(MODE_STAGE1);
				PlaySound(SOUND_LABEL_DECIDE);
			}
		}
		else if (pSelect->bMenu2 == true)
		{
			if (pSelect->nType == 0)
			{
				SetFade(MODE_RULE2);
				PlaySound(SOUND_LABEL_DECIDE);
			}
		}
		else if (pSelect->bMenu3 == true)
		{
			if (pSelect->nType == 0)
			{
				SetFade(MODE_TITLE);
				PlaySound(SOUND_LABEL_RETURN);
			}
		}
	}
	
	UpdateMenu();
	UpdateSelect();
}


//=======================================================================
//�`�揈��
//=======================================================================
void DrawRule(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRule, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureRule);	//�e�N�X�`���̐ݒ�
											//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,					//�J�n���钸�_�̃C���f�b�N�X
		2);					//�`�悷��v���~�e�B�u��


	DrawMenu();
	DrawSelect();
}