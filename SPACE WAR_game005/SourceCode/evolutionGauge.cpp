//=======================================================================
//�i���Q�[�W�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#include "main.h"
#include "evolutionGauge.h"
#include "player.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================

LPDIRECT3DTEXTURE9 g_apTextureEvolutionGauge[EVOLUTION_GAUGETYPE_MAX] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEvolutionGauge = NULL;		//���_�o�b�t�@�ւ̃|�C���^
EvolutionGauge g_aEvolutionGauge[MAX_EVOLUTIONGAUGE];

//=======================================================================
//����������
//=======================================================================
void InitEvolutionGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�ŃA�C�X�̃|�C���^
	int nCntEvolutionGauge;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�Q�[�W�̏�����
	for (nCntEvolutionGauge = 0; nCntEvolutionGauge < MAX_EVOLUTIONGAUGE; nCntEvolutionGauge++)
	{
		g_aEvolutionGauge[nCntEvolutionGauge].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEvolutionGauge[nCntEvolutionGauge].fWidth = 0.0f;
		g_aEvolutionGauge[nCntEvolutionGauge].fHeight = 0.0f;
		g_aEvolutionGauge[nCntEvolutionGauge].bUse = false;
		g_aEvolutionGauge[nCntEvolutionGauge].bEvolution = false;
		g_aEvolutionGauge[nCntEvolutionGauge].bGaugeMax = false;
		g_aEvolutionGauge[nCntEvolutionGauge].fCnt = 0.0f;
		g_aEvolutionGauge[nCntEvolutionGauge].nCounter = 0;
		g_aEvolutionGauge[nCntEvolutionGauge].nTransparency = 255;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//PlayerEvolution.png",
		&g_apTextureEvolutionGauge[0]);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EVOLUTIONGAUGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEvolutionGauge,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffEvolutionGauge->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntEvolutionGauge = 0; nCntEvolutionGauge < MAX_EVOLUTIONGAUGE; nCntEvolutionGauge++)
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

		pVtx[0].col = D3DCOLOR_RGBA(255, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEvolutionGauge->Unlock();
}

//=======================================================================
//�I������
//=======================================================================
void UninitEvolutionGauge(void)
{
	//�e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < EVOLUTION_GAUGETYPE_MAX; nCntTex++)
	{
		if (g_apTextureEvolutionGauge[nCntTex] != NULL)
		{
			g_apTextureEvolutionGauge[nCntTex]->Release();
			g_apTextureEvolutionGauge[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEvolutionGauge != NULL)
	{
		g_pVtxBuffEvolutionGauge->Release();
		g_pVtxBuffEvolutionGauge = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateEvolutionGauge(void)
{
	//�v���C���[�̗̑̓Q�[�W����
	PLAYER *pPlayer = GetPlayer();
	for (int nCntEvolutionGauge = 0; nCntEvolutionGauge < MAX_EVOLUTIONGAUGE; nCntEvolutionGauge++)
	{
		if (g_aEvolutionGauge[nCntEvolutionGauge].bUse == true)
		{
			VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
									//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
			g_pVtxBuffEvolutionGauge->Lock(0, 0, (void**)&pVtx, 0);

			if (pPlayer->bEvolution == true)
			{
				g_aEvolutionGauge[nCntEvolutionGauge].bEvolution = true;
			}

			if (g_aEvolutionGauge[nCntEvolutionGauge].bEvolution == true)
			{
				g_aEvolutionGauge[nCntEvolutionGauge].fCnt -= 0.02f;
				g_aEvolutionGauge[nCntEvolutionGauge].nCounter++;

				if (g_aEvolutionGauge[nCntEvolutionGauge].nCounter >= 5)
				{
					if (g_aEvolutionGauge[nCntEvolutionGauge].nTransparency == 255)
					{
						g_aEvolutionGauge[nCntEvolutionGauge].nTransparency = 0;
					}
					else if (g_aEvolutionGauge[nCntEvolutionGauge].nTransparency == 0)
					{
						g_aEvolutionGauge[nCntEvolutionGauge].nTransparency = 255;
					}
					g_aEvolutionGauge[nCntEvolutionGauge].nCounter = 0;
				}

				if (g_aEvolutionGauge[nCntEvolutionGauge].fCnt <= 0.0f)
				{
					g_aEvolutionGauge[nCntEvolutionGauge].fCnt = 0.0f;
					g_aEvolutionGauge[nCntEvolutionGauge].bEvolution = false;
					pPlayer->bEvolution = false;
					pPlayer->bDegenerate = true;
					g_aEvolutionGauge[nCntEvolutionGauge].nTransparency = 255;
					g_aEvolutionGauge[nCntEvolutionGauge].nCounter = 0;
				}
			}

			g_aEvolutionGauge[nCntEvolutionGauge].fWidth = (EVOLUTIONGAUGE_WIDTH / MAX_EVOLUTIONGAUGE_ADD) * g_aEvolutionGauge[nCntEvolutionGauge].fCnt;


			pVtx += (nCntEvolutionGauge * 4);

			pVtx[0].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x, g_aEvolutionGauge[nCntEvolutionGauge].pos.y - g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x + g_aEvolutionGauge[nCntEvolutionGauge].fWidth, g_aEvolutionGauge[nCntEvolutionGauge].pos.y - g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x, g_aEvolutionGauge[nCntEvolutionGauge].pos.y + g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x + g_aEvolutionGauge[nCntEvolutionGauge].fWidth, g_aEvolutionGauge[nCntEvolutionGauge].pos.y + g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);

			pVtx[0].col = D3DCOLOR_RGBA(255, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, g_aEvolutionGauge[nCntEvolutionGauge].nTransparency, 255);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffEvolutionGauge->Unlock();
		}
	}
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawEvolutionGauge(void)
{
	int nCntEvolutionGauge;

	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEvolutionGauge, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�

	for (nCntEvolutionGauge = 0; nCntEvolutionGauge < MAX_EVOLUTIONGAUGE; nCntEvolutionGauge++)
	{
		if (g_aEvolutionGauge[nCntEvolutionGauge].bUse == true)
		{
			pDevice->SetTexture(0, g_apTextureEvolutionGauge[g_aEvolutionGauge[nCntEvolutionGauge].nType]);	//�e�N�X�`���̐ݒ�
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntEvolutionGauge * 4,					//�`����J�n���钸�_�̃C���f�b�N�X
				2);					//�`�悷��v���~�e�B�u��
		}
	}
}

//=======================================================================
//�ݒ菈��
//=======================================================================
void SetEvolutionGauge(D3DXVECTOR3 pos, EVOLUTION_GAUGETYPE nType, float fWidth, float fHeight)
{
	int nCntEvolutionGauge;
	for (nCntEvolutionGauge = 0; nCntEvolutionGauge < MAX_EVOLUTIONGAUGE; nCntEvolutionGauge++)
	{
		if (g_aEvolutionGauge[nCntEvolutionGauge].bUse == false)
		{
			g_aEvolutionGauge[nCntEvolutionGauge].pos = pos;
			g_aEvolutionGauge[nCntEvolutionGauge].fWidth = fWidth;
			g_aEvolutionGauge[nCntEvolutionGauge].fHeight = fHeight;
			g_aEvolutionGauge[nCntEvolutionGauge].nType = nType;
			g_aEvolutionGauge[nCntEvolutionGauge].bUse = true;


			//���_���W�̐ݒ�

			VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
									//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
			g_pVtxBuffEvolutionGauge->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntEvolutionGauge * 4);


			pVtx[0].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x , g_aEvolutionGauge[nCntEvolutionGauge].pos.y - g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x + g_aEvolutionGauge[nCntEvolutionGauge].fWidth, g_aEvolutionGauge[nCntEvolutionGauge].pos.y - g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x , g_aEvolutionGauge[nCntEvolutionGauge].pos.y + g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x + g_aEvolutionGauge[nCntEvolutionGauge].fWidth, g_aEvolutionGauge[nCntEvolutionGauge].pos.y + g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffEvolutionGauge->Unlock();
			break;
		}
	}
}

//=======================================================================
//�Q�[�W��������
//=======================================================================
void SetAddEvolutionGauge(float fGauge)
{
	for (int nCntEvolutionGauge = 0; nCntEvolutionGauge < MAX_EVOLUTIONGAUGE; nCntEvolutionGauge++)
	{
		if (g_aEvolutionGauge[nCntEvolutionGauge].bUse == true)
		{
			if (g_aEvolutionGauge[nCntEvolutionGauge].bEvolution == false)
			{
				g_aEvolutionGauge[nCntEvolutionGauge].fCnt += fGauge;
			}

			if (g_aEvolutionGauge[nCntEvolutionGauge].nType == EVOLUTION_GAUGETYPE_PLAYER)
			{
				if (g_aEvolutionGauge[nCntEvolutionGauge].fCnt >= MAX_EVOLUTIONGAUGE_ADD)
				{
					g_aEvolutionGauge[nCntEvolutionGauge].fCnt = MAX_EVOLUTIONGAUGE_ADD;
					g_aEvolutionGauge[nCntEvolutionGauge].bGaugeMax = true;
				}
				else
				{
					g_aEvolutionGauge[nCntEvolutionGauge].bGaugeMax = false;
				}
			}

			g_aEvolutionGauge[nCntEvolutionGauge].fWidth = (EVOLUTIONGAUGE_WIDTH / MAX_EVOLUTIONGAUGE_ADD) * g_aEvolutionGauge[nCntEvolutionGauge].fCnt;

			//���_���W�̐ݒ�

			VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
									//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
			g_pVtxBuffEvolutionGauge->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntEvolutionGauge * 4);


			pVtx[0].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x, g_aEvolutionGauge[nCntEvolutionGauge].pos.y - g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x + g_aEvolutionGauge[nCntEvolutionGauge].fWidth, g_aEvolutionGauge[nCntEvolutionGauge].pos.y - g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x, g_aEvolutionGauge[nCntEvolutionGauge].pos.y + g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEvolutionGauge[nCntEvolutionGauge].pos.x + g_aEvolutionGauge[nCntEvolutionGauge].fWidth, g_aEvolutionGauge[nCntEvolutionGauge].pos.y + g_aEvolutionGauge[nCntEvolutionGauge].fHeight / 2.0f, 0.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffEvolutionGauge->Unlock();
		}
	}
}


//=======================================================================
//�擾����
//=======================================================================
EvolutionGauge *GetEvolutionGauge(void)
{
	return &g_aEvolutionGauge[0];
}
