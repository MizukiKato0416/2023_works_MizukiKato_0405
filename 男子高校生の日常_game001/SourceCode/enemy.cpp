//=======================================================================
//�G�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "enemy.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================

LPDIRECT3DTEXTURE9 g_apTextureEnemy[ENEMY_TYPE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Enemy g_aEnemy[MAX_ENEMY];							//�G

//=======================================================================
//����������
//=======================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�ŃA�C�X�̃|�C���^
	int nCntEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�G�̏�����
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nLife = 0;
		g_aEnemy[nCntEnemy].nCounterAnim = 0;
		g_aEnemy[nCntEnemy].nPatternAnim = 0;
		g_aEnemy[nCntEnemy].fEnemyWidth = 0;
		g_aEnemy[nCntEnemy].fEnemyHeight = 0;
		g_aEnemy[nCntEnemy].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//dog.png",
		&g_apTextureEnemy[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//huraipan.png",
		&g_apTextureEnemy[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//nabe.png",
		&g_apTextureEnemy[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//chalk_purple.png",
		&g_apTextureEnemy[3]);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
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
	g_pVtxBuffEnemy->Unlock();
}

//=======================================================================
//�I������
//=======================================================================
void UninitEnemy(void)
{
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < ENEMY_TYPE; nCntEnemy++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateEnemy(void)
{
	int nCntEnemy;
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{

		if (g_aEnemy[nCntEnemy].bUse == true)
		{

			if (GetMode() == MODE_GAME)
			{
				g_aEnemy[nCntEnemy].nCounterAnim++;
				if (g_aEnemy[nCntEnemy].nCounterAnim == 15)
				{
					g_aEnemy[nCntEnemy].nCounterAnim = 0;		//�J�E���^�[�������n�ɖ߂�
					g_aEnemy[nCntEnemy].nPatternAnim++;		//�p�^�[��No���X�V
					if (g_aEnemy[nCntEnemy].nPatternAnim > 1)
					{
						g_aEnemy[nCntEnemy].nPatternAnim = 0;
					}
					pVtx[0].tex = D3DXVECTOR2(g_aEnemy[nCntEnemy].nPatternAnim * 0.5f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(g_aEnemy[nCntEnemy].nPatternAnim * 0.5f + 0.5f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(g_aEnemy[nCntEnemy].nPatternAnim * 0.5f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(g_aEnemy[nCntEnemy].nPatternAnim * 0.5f + 0.5f, 1.0f);
				}
				g_aEnemy[nCntEnemy].pos -= g_aEnemy[nCntEnemy].move;

				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fEnemyWidth / 2.0f, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fEnemyHeight / 2.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fEnemyWidth / 2.0f, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fEnemyHeight / 2.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fEnemyWidth / 2.0f, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fEnemyHeight / 2.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fEnemyWidth / 2.0f, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fEnemyHeight / 2.0f, 0.0f);

				if (g_aEnemy[nCntEnemy].pos.x <= 0 - g_aEnemy[nCntEnemy].fEnemyWidth)
				{
					g_aEnemy[nCntEnemy].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
				}
			}

			else if (GetMode() == MODE_STAGE1)
			{
				g_aEnemy[nCntEnemy].pos -= g_aEnemy[nCntEnemy].move;

				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fEnemyWidth / 2.0f, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fEnemyHeight / 2.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fEnemyWidth / 2.0f, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fEnemyHeight / 2.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fEnemyWidth / 2.0f, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fEnemyHeight / 2.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fEnemyWidth / 2.0f, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fEnemyHeight / 2.0f, 0.0f);

				if (g_aEnemy[nCntEnemy].pos.y <= 0 - g_aEnemy[nCntEnemy].fEnemyHeight || g_aEnemy[nCntEnemy].pos.y >= SCREEN_HEIGHT + g_aEnemy[nCntEnemy].fEnemyHeight)
				{
					g_aEnemy[nCntEnemy].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
				}
			}

			else if (GetMode() == MODE_STAGE3)
			{
				g_aEnemy[nCntEnemy].pos -= g_aEnemy[nCntEnemy].move;

				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fEnemyWidth / 2.0f, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fEnemyHeight / 2.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fEnemyWidth / 2.0f, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fEnemyHeight / 2.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fEnemyWidth / 2.0f, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fEnemyHeight / 2.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fEnemyWidth / 2.0f, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fEnemyHeight / 2.0f, 0.0f);

				if (g_aEnemy[nCntEnemy].pos.y <= 0 - g_aEnemy[nCntEnemy].fEnemyHeight || g_aEnemy[nCntEnemy].pos.y >= SCREEN_HEIGHT + g_aEnemy[nCntEnemy].fEnemyHeight)
				{
					g_aEnemy[nCntEnemy].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
				}
				else if (g_aEnemy[nCntEnemy].pos.x <= 0 - g_aEnemy[nCntEnemy].fEnemyWidth)
				{
					g_aEnemy[nCntEnemy].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
				}
			}
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawEnemy(void)
{
	int nCntEnemy;

	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//�e�N�X�`��
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntEnemy * 4,					//�`����J�n���钸�_�̃C���f�b�N�X
				2);					//�`�悷��v���~�e�B�u��
		}
	}
}

//=======================================================================
//�ݒ菈��
//=======================================================================
void SetEnemy(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 move,int nLife, float fEnemyWidth, float fEnemyHeight)
{
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].fEnemyWidth = fEnemyWidth;
			g_aEnemy[nCntEnemy].fEnemyHeight = fEnemyHeight;
			//���_���W�̐ݒ�

			VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
									//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
			g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntEnemy * 4);


			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fEnemyWidth/2.0f, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fEnemyHeight/2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fEnemyWidth / 2.0f, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fEnemyHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fEnemyWidth / 2.0f, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fEnemyHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fEnemyWidth / 2.0f, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fEnemyHeight / 2.0f, 0.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffEnemy->Unlock();

			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].nLife = nLife;
			g_aEnemy[nCntEnemy].move = move;
			g_aEnemy[nCntEnemy].bUse = true;
			break;
		}
	}
}

//=======================================================================
//�擾����
//=======================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}

