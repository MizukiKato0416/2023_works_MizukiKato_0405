//=======================================================================
//�X�e�[�W1�Q�[���w�i�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "bg3.h"
#include "block.h"
#include "player.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================

LPDIRECT3DTEXTURE9 g_pTextureBg3 = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg3 = NULL;		//���_�o�b�t�@�ւ̃|�C���^
float fPosTexU3;


//=======================================================================
//����������
//=======================================================================
void InitBg3(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//bg003.png",
		&g_pTextureBg3);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBg3,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffBg3->Lock(0, 0, (void**)&pVtx, 0);


	pVtx[0].pos = D3DXVECTOR3(0.0f, 600.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH * 2.0f, 600.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH * 2.0f, SCREEN_HEIGHT, 0.0f);


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
	g_pVtxBuffBg3->Unlock();
}


//=======================================================================
//�I������
//=======================================================================
void UninitBg3(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBg3 != NULL)
	{
		g_pTextureBg3->Release();
		g_pTextureBg3 = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBg3 != NULL)
	{
		g_pVtxBuffBg3->Release();
		g_pVtxBuffBg3 = NULL;
	}
}


//=======================================================================
//�X�V����
//=======================================================================
void UpdateBg3(void)
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
			fPosTexU3 += 0.0025f;
			if (fPosTexU3 >= 1.0f)
			{
				fPosTexU3 -= 1.0f;
			}
		}

		if (pPlayer->move.x > 0.0f)
		{
			fPosTexU3 += 0.001f * POLYGON_SPEED;
			if (fPosTexU3 >= 1.0f)
			{
				fPosTexU3 -= 1.0f;
			}
		}
	}

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffBg3->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(fPosTexU3, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fPosTexU3 + 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(fPosTexU3, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fPosTexU3 + 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBg3->Unlock();
}


//=======================================================================
//�`�揈��
//=======================================================================
void DrawBg3(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBg3, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureBg3);	//�e�N�X�`���̐ݒ�
											//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,					//�J�n���钸�_�̃C���f�b�N�X
		2);					//�`�悷��v���~�e�B�u��
}