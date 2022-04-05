//=======================================================================
//���[�h�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "word.h"
#include "input.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================

LPDIRECT3DTEXTURE9 g_apTextureWord[WORD_TYPE] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWord = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Word g_aWord[MAX_WORD];								//���j���[
float g_fCnt;
float g_nCnt1;

//=======================================================================
//����������
//=======================================================================
void InitWord(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�ŃA�C�X�̃|�C���^
	int nCntWord;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���j���[�̏�����
	for (nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		g_aWord[nCntWord].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWord[nCntWord].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWord[nCntWord].fWordWidth = 0;
		g_aWord[nCntWord].nType = 0;
		g_aWord[nCntWord].nCnt = 0;
		g_aWord[nCntWord].fWordHeight = 0;
		g_aWord[nCntWord].bUse = false;
	}
	g_fCnt = 0.001f;
	g_nCnt1 = 1;



	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//pause.png",
		&g_apTextureWord[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//word_ninjin.png",
		&g_apTextureWord[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//title_word.png",
		&g_apTextureWord[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//word_ninjin.png",
		&g_apTextureWord[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//pushEnter.png",
		&g_apTextureWord[4]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//timeUp.png",
		&g_apTextureWord[5]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_WORD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWord,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffWord->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
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
	g_pVtxBuffWord->Unlock();
}

//=======================================================================
//�I������
//=======================================================================
void UninitWord(void)
{

	for (int nCntWord1 = 0; nCntWord1 < MAX_WORD; nCntWord1++)
	{
		g_aWord[nCntWord1].bUse = false;
	}

	int nCntWord;
	for (nCntWord = 0; nCntWord < WORD_TYPE; nCntWord++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureWord[nCntWord] != NULL)
		{
			g_apTextureWord[nCntWord]->Release();
			g_apTextureWord[nCntWord] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWord != NULL)
	{
		g_pVtxBuffWord->Release();
		g_pVtxBuffWord = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateWord(void)
{
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffWord->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		g_aWord[nCntWord].pos += g_aWord[nCntWord].move;
		if (g_aWord[nCntWord].nType == 1)
		{
			g_nCnt1++;
			g_aWord[nCntWord].fWordWidth += g_aWord[nCntWord].fWordWidth * g_fCnt;
			g_aWord[nCntWord].fWordHeight += g_aWord[nCntWord].fWordHeight * g_fCnt;
			if (g_nCnt1 >= 200)
			{
				g_fCnt = 0.0f;
			}
		}
		else if (g_aWord[nCntWord].nType == 2)
		{
			if (g_aWord[nCntWord].pos.y >= 200.0f)
			{
				g_aWord[nCntWord].move.y = 0.0f;
			}

			if (GetKeyboardPress(DIK_RIGHT) == true || GetKeyboardPress(DIK_D) == true)
			{
				g_aWord[nCntWord].move.x = 1.0f;
			}
			else if (GetKeyboardPress(DIK_LEFT) == true || GetKeyboardPress(DIK_A) == true)
			{
				g_aWord[nCntWord].move.x = -1.0f;
			}
			else if (GetKeyboardPress(DIK_RIGHT) == false && GetKeyboardPress(DIK_D) == false)
			{
				g_aWord[nCntWord].move.x = 0.0f;
			}
			else if (GetKeyboardPress(DIK_LEFT) == false && GetKeyboardPress(DIK_A) == false)
			{
				g_aWord[nCntWord].move.x = 0.0f;
			}

		}
		else if (g_aWord[nCntWord].nType == 4)
		{
			g_aWord[nCntWord].nCnt++;
			if (g_aWord[nCntWord].nCnt >= 100)
			{
				if (g_aWord[nCntWord].bUse == true)
				{
					g_aWord[nCntWord].bUse = false;
				}
				else if (g_aWord[nCntWord].bUse == false)
				{
					g_aWord[nCntWord].bUse = true;
				}
				g_aWord[nCntWord].nCnt = 0;
			}
		}


		pVtx[0].pos = D3DXVECTOR3(g_aWord[nCntWord].pos.x - g_aWord[nCntWord].fWordWidth / 2.0f, g_aWord[nCntWord].pos.y - g_aWord[nCntWord].fWordHeight / 2.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aWord[nCntWord].pos.x + g_aWord[nCntWord].fWordWidth / 2.0f, g_aWord[nCntWord].pos.y - g_aWord[nCntWord].fWordHeight / 2.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aWord[nCntWord].pos.x - g_aWord[nCntWord].fWordWidth / 2.0f, g_aWord[nCntWord].pos.y + g_aWord[nCntWord].fWordHeight / 2.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aWord[nCntWord].pos.x + g_aWord[nCntWord].fWordWidth / 2.0f, g_aWord[nCntWord].pos.y + g_aWord[nCntWord].fWordHeight / 2.0f, 0.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWord->Unlock();
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawWord(void)
{
	int nCntWord;

	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffWord, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�

	for (nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (g_aWord[nCntWord].bUse == true)
		{
			//�e�N�X�`��
			pDevice->SetTexture(0, g_apTextureWord[g_aWord[nCntWord].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntWord * 4,					//�`����J�n���钸�_�̃C���f�b�N�X
				2);					//�`�悷��v���~�e�B�u��
		}
	}
}

//=======================================================================
//�ݒ菈��
//=======================================================================
void SetWord(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 move, float fWordWidth, float fWordHeight)
{
	int nCntWord;
	for (nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (g_aWord[nCntWord].bUse == false)
		{
			g_aWord[nCntWord].pos = pos;
			g_aWord[nCntWord].fWordWidth = fWordWidth;
			g_aWord[nCntWord].fWordHeight = fWordHeight;
			//���_���W�̐ݒ�

			VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
									//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
			g_pVtxBuffWord->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntWord * 4);


			pVtx[0].pos = D3DXVECTOR3(g_aWord[nCntWord].pos.x - g_aWord[nCntWord].fWordWidth / 2.0f, g_aWord[nCntWord].pos.y - g_aWord[nCntWord].fWordHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aWord[nCntWord].pos.x + g_aWord[nCntWord].fWordWidth / 2.0f, g_aWord[nCntWord].pos.y - g_aWord[nCntWord].fWordHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aWord[nCntWord].pos.x - g_aWord[nCntWord].fWordWidth / 2.0f, g_aWord[nCntWord].pos.y + g_aWord[nCntWord].fWordHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aWord[nCntWord].pos.x + g_aWord[nCntWord].fWordWidth / 2.0f, g_aWord[nCntWord].pos.y + g_aWord[nCntWord].fWordHeight / 2.0f, 0.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffWord->Unlock();

			g_aWord[nCntWord].nType = nType;
			g_aWord[nCntWord].move = move;
			g_aWord[nCntWord].bUse = true;
			break;
		}
	}
}

//=======================================================================
//�擾����
//=======================================================================
Word *GetWord(void)
{
	return &g_aWord[0];
}
