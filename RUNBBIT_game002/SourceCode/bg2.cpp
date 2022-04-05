//=======================================================================
//�X�e�[�W1�Q�[���w�i�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#include "main.h"
#include "bg2.h"
#include "block.h"
#include "player.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================

LPDIRECT3DTEXTURE9 g_pTextureBg2 = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg2 = NULL;		//���_�o�b�t�@�ւ̃|�C���^
float fPosTexU2;


//=======================================================================
//����������
//=======================================================================
void InitBg2(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//bg002.png",
		&g_pTextureBg2);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBg2,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffBg2->Lock(0, 0, (void**)&pVtx, 0);


	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);


	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;



	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 235);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 235);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 235);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 235);


	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBg2->Unlock();
}


//=======================================================================
//�I������
//=======================================================================
void UninitBg2(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBg2 != NULL)
	{
		g_pTextureBg2->Release();
		g_pTextureBg2 = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBg2 != NULL)
	{
		g_pVtxBuffBg2->Release();
		g_pVtxBuffBg2 = NULL;
	}
}


//=======================================================================
//�X�V����
//=======================================================================
void UpdateBg2(void)
{

	PLAYER *pPlayer;
	//�u���b�N�̎擾
	pPlayer = GetPlayer();

	BLOCK *pBlock2;
	//�u���b�N�̎擾
	pBlock2 = GetBlock2();

	

	if (pPlayer->pos.x >= SCREEN_WIDTH / 2.0f)
	{
		if (pBlock2->move.x > 0.0f)
		{
			fPosTexU2 += 0.005f;
			if (fPosTexU2 >= 1.0f)
			{
				fPosTexU2 -= 1.0f;
			}
		}

		if (pPlayer->move.x > 0.0f)
		{
			fPosTexU2 += 0.0015f * POLYGON_SPEED;
			if (fPosTexU2 >= 1.0f)
			{
				fPosTexU2 -= 1.0f;
			}
		}
	}

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffBg2->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(fPosTexU2, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fPosTexU2 + 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(fPosTexU2, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fPosTexU2 + 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBg2->Unlock();
}


//=======================================================================
//�`�揈��
//=======================================================================
void DrawBg2(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBg2, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureBg2);	//�e�N�X�`���̐ݒ�
											//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,					//�J�n���钸�_�̃C���f�b�N�X
		2);					//�`�悷��v���~�e�B�u��
}