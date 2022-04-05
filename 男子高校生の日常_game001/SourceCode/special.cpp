//=======================================================================
//�K�E�Z��UI�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "special.h"
#include "item.h"
#include "life.h"
#include "fade.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================

LPDIRECT3DTEXTURE9 g_pTextureSpecial = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSpecial = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Special g_aSpecial;

//=======================================================================
//����������
//=======================================================================
void InitSpecial(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�ŃA�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�ʒu�̏�����
	g_aSpecial.pos = D3DXVECTOR3((SPECIAL_WIDTH / 2), LIFE_HEIGHT + SPECIAL_HEIGHT / 2, 0.0f);
	g_aSpecial.bUse = false;


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//SP_UI.png",
		&g_pTextureSpecial);



	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSpecial,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffSpecial->Lock(0, 0, (void**)&pVtx, 0);



	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_aSpecial.pos.x - (SPECIAL_WIDTH / 2), g_aSpecial.pos.y - SPECIAL_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aSpecial.pos.x + (SPECIAL_WIDTH / 2), g_aSpecial.pos.y - SPECIAL_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aSpecial.pos.x - (SPECIAL_WIDTH / 2), g_aSpecial.pos.y + SPECIAL_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aSpecial.pos.x + (SPECIAL_WIDTH / 2), g_aSpecial.pos.y + SPECIAL_HEIGHT / 2, 0.0f);

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
	g_pVtxBuffSpecial->Unlock();
}

//=======================================================================
//�I������
//=======================================================================
void UninitSpecial(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureSpecial != NULL)
	{
		g_pTextureSpecial->Release();
		g_pTextureSpecial = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSpecial != NULL)
	{
		g_pVtxBuffSpecial->Release();
		g_pVtxBuffSpecial = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateSpecial(void)
{
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffSpecial->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aSpecial.bUse == true)
	{
		pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	else if (g_aSpecial.bUse == false)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
	}



	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSpecial->Unlock();

}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawSpecial(void)
{

	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSpecial, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�

	//�e�N�X�`��
	pDevice->SetTexture(0, g_pTextureSpecial);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,					//�`����J�n���钸�_�̃C���f�b�N�X
		2);					//�`�悷��v���~�e�B�u��
}

//=======================================================================
//�擾����
//=======================================================================
Special *GetSpecial(void)
{
	return &g_aSpecial;
}
