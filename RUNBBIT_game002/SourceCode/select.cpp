//=======================================================================
//���j���[�I���Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "select.h"
#include "input.h"
#include "sound.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================

LPDIRECT3DTEXTURE9 g_apTextureSelect[SELECT_TYPE] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelect = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Select g_aSelect[MAX_SELECT];								//���j���[�I��

//=======================================================================
//����������
//=======================================================================
void InitSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�ŃA�C�X�̃|�C���^
	int nCntSelect;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���j���[�̏�����
	for (nCntSelect = 0; nCntSelect < MAX_SELECT; nCntSelect++)
	{
		g_aSelect[nCntSelect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSelect[nCntSelect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSelect[nCntSelect].fSelectWidth = 0;
		g_aSelect[nCntSelect].fSelectHeight = 0;
		g_aSelect[nCntSelect].bUse = false;
		g_aSelect[nCntSelect].bMenu1 = true;
		g_aSelect[nCntSelect].bMenu2 = false;
		g_aSelect[nCntSelect].bMenu3 = false;
	}


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//player000.png",
		&g_apTextureSelect[0]);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SELECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSelect,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntSelect = 0; nCntSelect < MAX_SELECT; nCntSelect++)
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

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSelect->Unlock();
}

//=======================================================================
//�I������
//=======================================================================
void UninitSelect(void)
{
	int nCntSelect;
	for (nCntSelect = 0; nCntSelect < SELECT_TYPE; nCntSelect++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureSelect[nCntSelect] != NULL)
		{
			g_apTextureSelect[nCntSelect]->Release();
			g_apTextureSelect[nCntSelect] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSelect != NULL)
	{
		g_pVtxBuffSelect->Release();
		g_pVtxBuffSelect = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateSelect(void)
{
	//�C�ӂ̃L�[�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_DOWN) == true)
	{
		for (int nCntSelect = 0; nCntSelect < MAX_SELECT; nCntSelect++)
		{
			if (g_aSelect[nCntSelect].bMenu1 == true)
			{
				PlaySound(SOUND_LABEL_CURSOR);
				g_aSelect[nCntSelect].bMenu2 = true;
				g_aSelect[nCntSelect].bMenu1 = false;
			}
			else if (g_aSelect[nCntSelect].bMenu2 == true)
			{
				PlaySound(SOUND_LABEL_CURSOR);
				g_aSelect[nCntSelect].bMenu3 = true;
				g_aSelect[nCntSelect].bMenu2 = false;
			}
		}
	}
	else if (GetKeyboardTrigger(DIK_UP) == true)
	{
		for (int nCntSelect = 0; nCntSelect < MAX_SELECT; nCntSelect++)
		{
			if (g_aSelect[nCntSelect].bMenu3 == true)
			{
				PlaySound(SOUND_LABEL_CURSOR);
				g_aSelect[nCntSelect].bMenu2 = true;
				g_aSelect[nCntSelect].bMenu3 = false;
			}
			else if (g_aSelect[nCntSelect].bMenu2 == true)
			{
				PlaySound(SOUND_LABEL_CURSOR);
				g_aSelect[nCntSelect].bMenu1 = true;
				g_aSelect[nCntSelect].bMenu2 = false;
			}
		}
	}


	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntSelect = 0; nCntSelect < MAX_SELECT; nCntSelect++)
	{
		if (g_aSelect[nCntSelect].bMenu1 == true)
		{
			if (g_aSelect[nCntSelect].nType == 0)
			{
				pVtx[0].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x - g_aSelect[nCntSelect].fSelectWidth / 2.0f, g_aSelect[nCntSelect].pos.y - g_aSelect[nCntSelect].fSelectHeight / 2.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x + g_aSelect[nCntSelect].fSelectWidth / 2.0f, g_aSelect[nCntSelect].pos.y - g_aSelect[nCntSelect].fSelectHeight / 2.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x - g_aSelect[nCntSelect].fSelectWidth / 2.0f, g_aSelect[nCntSelect].pos.y + g_aSelect[nCntSelect].fSelectHeight / 2.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x + g_aSelect[nCntSelect].fSelectWidth / 2.0f, g_aSelect[nCntSelect].pos.y + g_aSelect[nCntSelect].fSelectHeight / 2.0f, 0.0f);
			}
		}
		else if (g_aSelect[nCntSelect].bMenu2 == true)
		{
			if (g_aSelect[nCntSelect].nType == 0)
			{
				pVtx[0].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x - g_aSelect[nCntSelect].fSelectWidth / 2.0f, (g_aSelect[nCntSelect].pos.y * 2 - g_aSelect[nCntSelect].fSelectHeight / 2.0f), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x + g_aSelect[nCntSelect].fSelectWidth / 2.0f, (g_aSelect[nCntSelect].pos.y * 2 - g_aSelect[nCntSelect].fSelectHeight / 2.0f), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x - g_aSelect[nCntSelect].fSelectWidth / 2.0f, (g_aSelect[nCntSelect].pos.y * 2 + g_aSelect[nCntSelect].fSelectHeight / 2.0f), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x + g_aSelect[nCntSelect].fSelectWidth / 2.0f, (g_aSelect[nCntSelect].pos.y * 2 + g_aSelect[nCntSelect].fSelectHeight / 2.0f), 0.0f);
			}
		}
		else if (g_aSelect[nCntSelect].bMenu3 == true)
		{
			if (g_aSelect[nCntSelect].nType == 0)
			{
				pVtx[0].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x - g_aSelect[nCntSelect].fSelectWidth / 2.0f, (g_aSelect[nCntSelect].pos.y * 3 - g_aSelect[nCntSelect].fSelectHeight / 2.0f), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x + g_aSelect[nCntSelect].fSelectWidth / 2.0f, (g_aSelect[nCntSelect].pos.y * 3 - g_aSelect[nCntSelect].fSelectHeight / 2.0f), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x - g_aSelect[nCntSelect].fSelectWidth / 2.0f, (g_aSelect[nCntSelect].pos.y * 3 + g_aSelect[nCntSelect].fSelectHeight / 2.0f), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x + g_aSelect[nCntSelect].fSelectWidth / 2.0f, (g_aSelect[nCntSelect].pos.y * 3 + g_aSelect[nCntSelect].fSelectHeight / 2.0f), 0.0f);
			}
		}
	}
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawSelect(void)
{
	int nCntSelect;

	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSelect, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�

	for (nCntSelect = 0; nCntSelect < MAX_SELECT; nCntSelect++)
	{
		if (g_aSelect[nCntSelect].bUse == true)
		{
			//�e�N�X�`��
			pDevice->SetTexture(0, g_apTextureSelect[g_aSelect[nCntSelect].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntSelect * 4,					//�`����J�n���钸�_�̃C���f�b�N�X
				2);					//�`�悷��v���~�e�B�u��
		}
	}
}

//=======================================================================
//�ݒ菈��
//=======================================================================
void SetSelect(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 move, float fSelectWidth, float fSelectHeight)
{
	int nCntSelect;
	for (nCntSelect = 0; nCntSelect < MAX_SELECT; nCntSelect++)
	{
		if (g_aSelect[nCntSelect].bUse == false)
		{
			g_aSelect[nCntSelect].pos = pos;
			g_aSelect[nCntSelect].fSelectWidth = fSelectWidth;
			g_aSelect[nCntSelect].fSelectHeight = fSelectHeight;
			//���_���W�̐ݒ�

			VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
									//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
			g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntSelect * 4);


			pVtx[0].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x - g_aSelect[nCntSelect].fSelectWidth / 2.0f, g_aSelect[nCntSelect].pos.y - g_aSelect[nCntSelect].fSelectHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x + g_aSelect[nCntSelect].fSelectWidth / 2.0f, g_aSelect[nCntSelect].pos.y - g_aSelect[nCntSelect].fSelectHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x - g_aSelect[nCntSelect].fSelectWidth / 2.0f, g_aSelect[nCntSelect].pos.y + g_aSelect[nCntSelect].fSelectHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aSelect[nCntSelect].pos.x + g_aSelect[nCntSelect].fSelectWidth / 2.0f, g_aSelect[nCntSelect].pos.y + g_aSelect[nCntSelect].fSelectHeight / 2.0f, 0.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffSelect->Unlock();

			g_aSelect[nCntSelect].nType = nType;
			g_aSelect[nCntSelect].move = move;
			g_aSelect[nCntSelect].bUse = true;
			break;
		}
	}
}

//=======================================================================
//�擾����
//=======================================================================
Select *GetSelect(void)
{
	return &g_aSelect[0];
}
