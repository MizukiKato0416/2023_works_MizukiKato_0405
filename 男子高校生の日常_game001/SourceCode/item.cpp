//=======================================================================
//�A�C�e���Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "item.h"

//========================================================
//�O���[�o���ϐ�
//========================================================
LPDIRECT3DTEXTURE9 g_apTextureItem[ITEM_TYPE] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Item g_aItem[MAX_ITEM];

//========================================================
//����������
//========================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�ŃA�C�X�̃|�C���^
	int nCntItem;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�A�C�e���̏�����
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].nType = 0;
		g_aItem[nCntItem].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//LifeItem.png",
		&g_apTextureItem[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//spItem.png",
		&g_apTextureItem[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//Life.png",
		&g_apTextureItem[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//Life.png",
		&g_apTextureItem[3]);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
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
	g_pVtxBuffItem->Unlock();
}

//========================================================
//�A�C�e���̏I������
//========================================================
void UninitItem(void)
{
	int nCntItem;
	for (nCntItem = 0; nCntItem < ITEM_TYPE; nCntItem++)
	{
		if (g_apTextureItem[nCntItem] != NULL)
		{
			//�e�N�X�`���̔j��
			g_apTextureItem[nCntItem]->Release();
			g_apTextureItem[nCntItem] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//========================================================
////�A�C�e���̍X�V����
//========================================================
void UpdateItem(void)
{
	//-------------------------------------------------
	//�A�C�e���̈ړ��ʁA�g�p���g�p�̐ݒ�
	//-------------------------------------------------
	int nCntItem;
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{

		if (g_aItem[nCntItem].bUse == true)
		{

			g_aItem[nCntItem].pos -= g_aItem[nCntItem].move;

			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_WIDTH / 2.0f, g_aItem[nCntItem].pos.y - ITEM_HEIGHT / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_WIDTH / 2.0f, g_aItem[nCntItem].pos.y - ITEM_HEIGHT / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_WIDTH / 2.0f, g_aItem[nCntItem].pos.y + ITEM_HEIGHT / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_WIDTH / 2.0f, g_aItem[nCntItem].pos.y + ITEM_HEIGHT / 2.0f, 0.0f);

			if (g_aItem[nCntItem].pos.x <= 0 - ITEM_WIDTH)
			{
				g_aItem[nCntItem].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
			}

		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//========================================================
//�`�揈��
//========================================================
void DrawItem(void)
{
	int nCntItem;

	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			pDevice->SetTexture(0, g_apTextureItem[g_aItem[nCntItem].nType]);	//�e�N�X�`���̐ݒ�
																									//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntItem * 4,					//�`����J�n���钸�_�̃C���f�b�N�X
				2);					//�`�悷��v���~�e�B�u��
		}
	}
}

//========================================================
//�A�C�e���̐ݒ菈��
//========================================================
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move, int type)
{
	int nCntItem;
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			g_aItem[nCntItem].pos = pos;
			//���_���W�̐ݒ�

			VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
									//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
  			g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntItem * 4);



			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_WIDTH / 2.0f, g_aItem[nCntItem].pos.y - ITEM_HEIGHT / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_WIDTH / 2.0f, g_aItem[nCntItem].pos.y - ITEM_HEIGHT / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_WIDTH / 2.0f, g_aItem[nCntItem].pos.y + ITEM_HEIGHT / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_WIDTH / 2.0f, g_aItem[nCntItem].pos.y + ITEM_HEIGHT / 2.0f, 0.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffItem->Unlock();

			g_aItem[nCntItem].move = move;
			g_aItem[nCntItem].nType = type;
			g_aItem[nCntItem].bUse = true;
			break;
		}
	}
}

//=======================================================================
//�擾����
//=======================================================================
Item *GetItem(void)
{
	return &g_aItem[0];
}