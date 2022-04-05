//=======================================================================
//���j���[�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "menu.h"
#include "select.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================

LPDIRECT3DTEXTURE9 g_apTextureMenu[MENU_TYPE] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMenu = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Menu g_aMenu[MAX_MENU];								//���j���[

//=======================================================================
//����������
//=======================================================================
void InitMenu(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�ŃA�C�X�̃|�C���^
	int nCntMenu;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���j���[�̏�����
	for (nCntMenu = 0; nCntMenu < MAX_MENU; nCntMenu++)
	{
		g_aMenu[nCntMenu].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMenu[nCntMenu].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMenu[nCntMenu].fMenuWidth = 0;
		g_aMenu[nCntMenu].fMenuHeight = 0;
		g_aMenu[nCntMenu].bUse = false;
		g_aMenu[nCntMenu].bSelectUse = false;
	}
	g_aMenu[0].bSelectUse = true;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//gameStartUi.png",
		&g_apTextureMenu[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//tutorialUi.png",
		&g_apTextureMenu[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//titleUi.png",
		&g_apTextureMenu[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//continueUi.png",
		&g_apTextureMenu[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//restartUi.png",
		&g_apTextureMenu[4]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//exitUi.png",
		&g_apTextureMenu[5]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_MENU,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMenu,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffMenu->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMenu = 0; nCntMenu < MAX_MENU; nCntMenu++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		if (g_aMenu[nCntMenu].bSelectUse == true)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
		}
		else if (g_aMenu[nCntMenu].bSelectUse == false)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMenu->Unlock();
}

//=======================================================================
//�I������
//=======================================================================
void UninitMenu(void)
{
	int nCntMenu;
	for (nCntMenu = 0; nCntMenu < MENU_TYPE; nCntMenu++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureMenu[nCntMenu] != NULL)
		{
			g_apTextureMenu[nCntMenu]->Release();
			g_apTextureMenu[nCntMenu] = NULL;
		}
		g_aMenu[nCntMenu].bUse = false;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMenu != NULL)
	{
		g_pVtxBuffMenu->Release();
		g_pVtxBuffMenu = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateMenu(void)
{
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffMenu->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMenu = 0; nCntMenu < MENU_TYPE; nCntMenu++)
	{
		if (g_aMenu[nCntMenu].bUse == true)
		{
			if (g_aMenu[nCntMenu].bSelectUse == true)
			{
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
			}
			else if (g_aMenu[nCntMenu].bSelectUse == false)
			{
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			pVtx += 4;
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMenu->Unlock();


	Select *pSelect;
	//�Z���N�g�̎擾
	pSelect = GetSelect();

	if (pSelect->bMenu1 == true)
	{
		g_aMenu[0].bSelectUse = true;
		g_aMenu[1].bSelectUse = false;
		g_aMenu[2].bSelectUse = false;
	}
	else if (pSelect->bMenu2 == true)
	{
		g_aMenu[1].bSelectUse = true;
		g_aMenu[0].bSelectUse = false;
		g_aMenu[2].bSelectUse = false;
	}
	else if (pSelect->bMenu3 == true)
	{
		g_aMenu[2].bSelectUse = true;
		g_aMenu[0].bSelectUse = false;
		g_aMenu[1].bSelectUse = false;
	}
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawMenu(void)
{
	int nCntMenu;

	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMenu, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�

	for (nCntMenu = 0; nCntMenu < MAX_MENU; nCntMenu++)
	{
		if (g_aMenu[nCntMenu].bUse == true)
		{
			//�e�N�X�`��
			pDevice->SetTexture(0, g_apTextureMenu[g_aMenu[nCntMenu].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntMenu * 4,					//�`����J�n���钸�_�̃C���f�b�N�X
				2);					//�`�悷��v���~�e�B�u��
		}
	}
}

//=======================================================================
//�ݒ菈��
//=======================================================================
void SetMenu(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 move, float fMenuWidth, float fMenuHeight)
{
	int nCntMenu;
	for (nCntMenu = 0; nCntMenu < MAX_MENU; nCntMenu++)
	{
		if (g_aMenu[nCntMenu].bUse == false)
		{
			g_aMenu[nCntMenu].pos = pos;
			g_aMenu[nCntMenu].fMenuWidth = fMenuWidth;
			g_aMenu[nCntMenu].fMenuHeight = fMenuHeight;
			//���_���W�̐ݒ�

			VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
									//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
			g_pVtxBuffMenu->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntMenu * 4);


			pVtx[0].pos = D3DXVECTOR3(g_aMenu[nCntMenu].pos.x - g_aMenu[nCntMenu].fMenuWidth / 2.0f, g_aMenu[nCntMenu].pos.y - g_aMenu[nCntMenu].fMenuHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aMenu[nCntMenu].pos.x + g_aMenu[nCntMenu].fMenuWidth / 2.0f, g_aMenu[nCntMenu].pos.y - g_aMenu[nCntMenu].fMenuHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aMenu[nCntMenu].pos.x - g_aMenu[nCntMenu].fMenuWidth / 2.0f, g_aMenu[nCntMenu].pos.y + g_aMenu[nCntMenu].fMenuHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aMenu[nCntMenu].pos.x + g_aMenu[nCntMenu].fMenuWidth / 2.0f, g_aMenu[nCntMenu].pos.y + g_aMenu[nCntMenu].fMenuHeight / 2.0f, 0.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffMenu->Unlock();

			g_aMenu[nCntMenu].nType = nType;
			g_aMenu[nCntMenu].move = move;
			g_aMenu[nCntMenu].bUse = true;
			break;
		}
	}
}

//=======================================================================
//�擾����
//=======================================================================
Menu *GetMenu(void)
{
	return &g_aMenu[0];
}
