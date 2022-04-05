//=======================================================================
//�v���C���[�̃��C�t�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "life.h"
#include "item.h"
#include "sound.h"
#include "fade.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================

LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Life g_aLife[MAX_LIFE_POLYGON];							//���C�t�̃|���S����
float g_fLife;											//���C�t�̒l

//=======================================================================
//����������
//=======================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�ŃA�C�X�̃|�C���^
	int nCntLife;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���C�t�̈ʒu�̏�����
	for (nCntLife = 0; nCntLife < MAX_LIFE_POLYGON; nCntLife++)
	{
		g_aLife[nCntLife].pos = D3DXVECTOR3((LIFE_WIDTH * nCntLife) + (LIFE_WIDTH / 2), LIFE_HEIGHT / 2, 0.0f);
		g_aLife[nCntLife].bUse = false;

	}

	g_fLife = 4.0f;				//���C�t�̒l


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//life.png",
		&g_pTextureLife);



	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFE_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntLife = 0; nCntLife < MAX_LIFE_POLYGON; nCntLife++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x - (LIFE_WIDTH / 2) + (LIFE_WIDTH/4 * nCntLife), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + (LIFE_WIDTH / 2) + (LIFE_WIDTH/4 * nCntLife), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x - (LIFE_WIDTH / 2) + (LIFE_WIDTH/4 * nCntLife), LIFE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + (LIFE_WIDTH / 2) + (LIFE_WIDTH/4 * nCntLife), LIFE_HEIGHT, 0.0f);

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
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
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
	int nCntLife;
	int nCnt;
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntLife = 0; nCntLife < MAX_LIFE_POLYGON; nCntLife++)
	{

		for (nCnt = 0; nCnt < MAX_LIFE_POLYGON; nCnt++)
		{
			if (g_fLife >= nCnt + 0.5f)
			{
				g_aLife[nCnt].bUse = true;
			}
			else
			{
				g_aLife[nCnt].bUse = false;
			}
		}
		

		if (g_aLife[nCntLife].bUse == true)
		{
			if (g_fLife == nCntLife+0.5f)
			{
				pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			else
			{
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
			}
		}



		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();





	if (g_fLife <= 0.0f && GetFade() == FADE_NONE)
	{
		if (GetMode() == MODE_STAGE1)
		{
			g_fLife = 0.0f;
			SetFade(MODE_GAMEOVER);
		}
		else if (GetMode() == MODE_GAME)
		{
			g_fLife = 0.0f;
			SetFade(MODE_GAMEOVER);
		}
		else if (GetMode() == MODE_STAGE3)
		{
			g_fLife = 0.0f;
			SetFade(MODE_GAMEOVER);
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

	for (nCntLife = 0; nCntLife < MAX_LIFE_POLYGON; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == true)
		{
			//�e�N�X�`��
			pDevice->SetTexture(0, g_pTextureLife);

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
void SetLife(float fLife)
{
	g_fLife -= fLife;
	if (g_fLife>8)
	{
		g_fLife = 8;
	}
}

//=======================================================================
//�擾����
//=======================================================================
Life *GetLife(void)
{
	return &g_aLife[0];
}