//=======================================================================
//�Q�[�W�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#include "main.h"
#include "life.h"
#include "player.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================

LPDIRECT3DTEXTURE9 g_apTextureLife[MAX_TYPE] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Life g_aLife[MAX_LIFE];

//=======================================================================
//����������
//=======================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�ŃA�C�X�̃|�C���^
	int nCntLife;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�Q�[�W�̏�����
	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		g_aLife[nCntLife].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLife[nCntLife].fWidth = 0.0f;
		g_aLife[nCntLife].fHeight = 0.0f;
		g_aLife[nCntLife].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//PlayerLife.png",
		&g_apTextureLife[0]);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();
}

//=======================================================================
//�I������
//=======================================================================
void UninitLife(void)
{
	//�e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < MAX_TYPE; nCntTex++)
	{
		if (g_apTextureLife[nCntTex] != NULL)
		{
			g_apTextureLife[nCntTex]->Release();
			g_apTextureLife[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateLife(void)
{
	//�v���C���[�̗̑̓Q�[�W����
	PLAYER *pPlayer = GetPlayer();
	for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == true)
		{
			VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
									//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
			g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

			if (g_aLife[nCntLife].nType = GAUGETYPE_PLAYER)
			{
				


			}

			pVtx += (nCntLife * 4);


			pVtx[0].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x, g_aLife[nCntLife].pos.y - g_aLife[nCntLife].fHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + g_aLife[nCntLife].fWidth, g_aLife[nCntLife].pos.y - g_aLife[nCntLife].fHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x, g_aLife[nCntLife].pos.y + g_aLife[nCntLife].fHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + g_aLife[nCntLife].fWidth, g_aLife[nCntLife].pos.y + g_aLife[nCntLife].fHeight / 2.0f, 0.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffLife->Unlock();
		}
	}
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawLife(void)
{
	int nCntLife;

	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�

	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == true)
		{
			pDevice->SetTexture(0, g_apTextureLife[g_aLife[nCntLife].nType]);	//�e�N�X�`���̐ݒ�
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntLife * 4,					//�`����J�n���钸�_�̃C���f�b�N�X
				2);					//�`�悷��v���~�e�B�u��
		}
	}
}

//=======================================================================
//�ݒ菈��
//=======================================================================
void SetLife(D3DXVECTOR3 pos, GAUGETYPE nType, float fWidth, float fHeight)
{
	int nCntLife;
	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == false)
		{
			g_aLife[nCntLife].pos = pos;
			g_aLife[nCntLife].fWidth = fWidth;
			g_aLife[nCntLife].fHeight = fHeight;
			g_aLife[nCntLife].nType = nType;
			g_aLife[nCntLife].bUse = true;


			//���_���W�̐ݒ�

			VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
									//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
			g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntLife * 4);


			pVtx[0].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x , g_aLife[nCntLife].pos.y - g_aLife[nCntLife].fHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + g_aLife[nCntLife].fWidth, g_aLife[nCntLife].pos.y - g_aLife[nCntLife].fHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x , g_aLife[nCntLife].pos.y + g_aLife[nCntLife].fHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + g_aLife[nCntLife].fWidth, g_aLife[nCntLife].pos.y + g_aLife[nCntLife].fHeight / 2.0f, 0.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffLife->Unlock();
			break;
		}
	}
}

//=======================================================================
//�擾����
//=======================================================================
Life *GetLife(void)
{
	return &g_aLife[0];
}
