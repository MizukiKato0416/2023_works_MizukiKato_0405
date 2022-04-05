//=======================================================================
//���ԂɊւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include <math.h>
#include "main.h"
#include "time.h"
#include "fade.h"
#include "score.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Time g_aTimePolygon[MAX_TIME_POLYGON];							//�^�C�}�[�̃|���S����
int g_nTime;								//�^�C�}�[
int g_nCntTime;								//�^�C�}�[�����������炷�J�E���g

//=======================================================================
//����������
//=======================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�ŃA�C�X�̃|�C���^
	int nCntTime;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�X�R�A�̈ʒu�̏�����

	for (nCntTime = 0; nCntTime < MAX_TIME_POLYGON; nCntTime++)
	{
		g_aTimePolygon[nCntTime].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (TIME_POLYGON_WIDTH*(MAX_TIME_POLYGON - nCntTime) + (TIME_POLYGON_WIDTH / 2)), TIME_POLYGON_HEIGHT / 2, 0.0f);
	}
	g_nTime = 60;
	g_nCntTime = 0;



	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//score.png",
		&g_pTextureTime);



	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntTime = 0; nCntTime < MAX_TIME_POLYGON; nCntTime++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (TIME_POLYGON_WIDTH*(MAX_TIME_POLYGON - nCntTime)), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (TIME_POLYGON_WIDTH*(MAX_TIME_POLYGON - nCntTime - 1)), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (TIME_POLYGON_WIDTH*(MAX_TIME_POLYGON - nCntTime)), TIME_POLYGON_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (TIME_POLYGON_WIDTH*(MAX_TIME_POLYGON - nCntTime - 1)), TIME_POLYGON_HEIGHT, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;

	}


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}

//=======================================================================
//�I������
//=======================================================================
void UninitTime(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateTime(void)
{
	int nCntTime;
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	

	for (nCntTime = 0; nCntTime < MAX_TIME_POLYGON; nCntTime++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (TIME_POLYGON_WIDTH*(MAX_TIME_POLYGON - nCntTime)), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (TIME_POLYGON_WIDTH*(MAX_TIME_POLYGON - nCntTime - 1)), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (TIME_POLYGON_WIDTH*(MAX_TIME_POLYGON - nCntTime)), TIME_POLYGON_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (TIME_POLYGON_WIDTH*(MAX_TIME_POLYGON - nCntTime - 1)), TIME_POLYGON_HEIGHT, 0.0f);

		if (nCntTime == 0)
		{
			pVtx[0].tex = D3DXVECTOR2(g_nTime / (int)powf(10, 2)*0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_nTime / (int)powf(10, 2)*0.1f + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_nTime / (int)powf(10, 2)*0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_nTime / (int)powf(10, 2)*0.1f + 0.1f, 1.0f);
		}
		else if (nCntTime == 2)
		{
			pVtx[0].tex = D3DXVECTOR2(g_nTime % 10 * 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_nTime % 10 * 0.1f + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_nTime % 10 * 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_nTime % 10 * 0.1f + 0.1f, 1.0f);
		}
		else
		{
			pVtx[0].tex = D3DXVECTOR2(g_nTime % (int)powf(10, MAX_TIME_POLYGON - nCntTime) / (int)powf(10, 2 - nCntTime) *0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_nTime % (int)powf(10, MAX_TIME_POLYGON - nCntTime) / (int)powf(10, 2 - nCntTime)*0.1f + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_nTime % (int)powf(10, MAX_TIME_POLYGON - nCntTime) / (int)powf(10, 2 - nCntTime)*0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_nTime % (int)powf(10, MAX_TIME_POLYGON - nCntTime) / (int)powf(10, 2 - nCntTime)*0.1f + 0.1f, 1.0f);
		}

		pVtx += 4;
	}
	
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();


	g_nCntTime++;
	if (g_nCntTime >= 120 && g_nTime != 0)
	{
		g_nTime--;
		g_nCntTime = 0;
	}

	if (g_nTime <= 0 && GetFade() == FADE_NONE)
	{
		g_nTime = 0;
		SetFade(MODE_RESULT);
	}
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawTime(void)
{
	int nCntTime;

	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�

	for (nCntTime = 0; nCntTime < MAX_TIME_POLYGON; nCntTime++)
	{
		//�e�N�X�`��
		pDevice->SetTexture(0, g_pTextureTime);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			nCntTime * 4,					//�`����J�n���钸�_�̃C���f�b�N�X
			2);					//�`�悷��v���~�e�B�u��
	}
	
}

//=======================================================================
//�ݒ菈��
//=======================================================================
void SetTime(int nTime)
{
	g_nTime += nTime;
}

//=======================================================================
//�擾����
//=======================================================================
int GetTime(void)
{
	return g_nTime;
}
