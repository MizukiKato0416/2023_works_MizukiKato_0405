//=======================================================================
//�ω��̂Ȃ�MASK�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#include "main.h"
#include "mask.h"
#include "player.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================

LPDIRECT3DTEXTURE9 g_apTextureMask[MASKTYPE_MAX] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMask = NULL;		//���_�o�b�t�@�ւ̃|�C���^
MASK g_aMask[MAX_MASK];
int g_nCntDamage;	//�_���[�W���\������

//=======================================================================
//����������
//=======================================================================
void InitMask(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�ŃA�C�X�̃|�C���^
	int nCntMask;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�Q�[�W�̏�����
	for (nCntMask = 0; nCntMask < MAX_MASK; nCntMask++)
	{
		g_aMask[nCntMask].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMask[nCntMask].fWidth = 0.0f;
		g_aMask[nCntMask].fHeight = 0.0f;
		g_aMask[nCntMask].col = 0;
		g_aMask[nCntMask].bUse = false;
	}
	g_nCntDamage = 0;


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/damage02.png",
		&g_apTextureMask[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/gameOver.png",
		&g_apTextureMask[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/timeUp.png",
		&g_apTextureMask[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_MASK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMask,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffMask->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntMask = 0; nCntMask < MAX_MASK; nCntMask++)
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
	g_pVtxBuffMask->Unlock();
}

//=======================================================================
//�I������
//=======================================================================
void UninitMask(void)
{
	//�e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < MASKTYPE_MAX; nCntTex++)
	{
		if (g_apTextureMask[nCntTex] != NULL)
		{
			g_apTextureMask[nCntTex]->Release();
			g_apTextureMask[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMask != NULL)
	{
		g_pVtxBuffMask->Release();
		g_pVtxBuffMask = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateMask(void)
{
	for (int nCntMask = 0; nCntMask < MAX_MASK; nCntMask++)
	{
		if (g_aMask[nCntMask].bUse == true)
		{
			VERTEX_2D *pVtx;
			//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
			g_pVtxBuffMask->Lock(0, 0, (void**)&pVtx, 0);

			if (g_aMask[nCntMask].nType == MASKTYPE_DAMAGE)
			{
				g_nCntDamage++;
				if (g_nCntDamage > 20)
				{
					g_nCntDamage = 0;
					g_aMask[nCntMask].bUse = false;
				}
			}
			else if (g_aMask[nCntMask].nType == MASKTYPE_TIMEUP)
			{
				if (g_aMask[nCntMask].pos.y >= SCREEN_HEIGHT / 2.0f)
				{

				}
				else
				{
					g_aMask[nCntMask].pos.y += 10.0f;
				}
			}
			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffMask->Unlock();
		}
	}
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawMask(void)
{
	int nCntMask;

	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMask, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�

	for (nCntMask = 0; nCntMask < MASKTYPE_MAX; nCntMask++)
	{
		if (g_aMask[nCntMask].bUse == true)
		{
			pDevice->SetTexture(0, g_apTextureMask[g_aMask[nCntMask].nType]);	//�e�N�X�`���̐ݒ�
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntMask * 4,					//�`����J�n���钸�_�̃C���f�b�N�X
				2);					//�`�悷��v���~�e�B�u��
		}
	}
}

//=======================================================================
//�ݒ菈��
//=======================================================================
void SetMask(D3DXVECTOR3 pos, MASKTYPE nType, float fWidth, float fHeight)
{
	int nCntMask;
	for (nCntMask = 0; nCntMask < MAX_MASK; nCntMask++)
	{
		if (g_aMask[nCntMask].bUse == false)
		{
			g_aMask[nCntMask].pos = pos;
			g_aMask[nCntMask].fWidth = fWidth;
			g_aMask[nCntMask].fHeight = fHeight;
			g_aMask[nCntMask].nType = nType;
			g_aMask[nCntMask].bUse = true;


			//���_���W�̐ݒ�

			VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
									//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
			g_pVtxBuffMask->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntMask * 4);

			pVtx[0].pos = D3DXVECTOR3(g_aMask[nCntMask].pos.x , g_aMask[nCntMask].pos.y - g_aMask[nCntMask].fHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aMask[nCntMask].pos.x + g_aMask[nCntMask].fWidth, g_aMask[nCntMask].pos.y - g_aMask[nCntMask].fHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aMask[nCntMask].pos.x , g_aMask[nCntMask].pos.y + g_aMask[nCntMask].fHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aMask[nCntMask].pos.x + g_aMask[nCntMask].fWidth, g_aMask[nCntMask].pos.y + g_aMask[nCntMask].fHeight / 2.0f, 0.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffMask->Unlock();
			break;
		}
	}
}

//=======================================================================
//�擾����
//=======================================================================
MASK *GetMask(void)
{
	return &g_aMask[0];
}
