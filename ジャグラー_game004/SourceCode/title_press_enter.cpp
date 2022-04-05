#include "title_press_enter.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "databox.h"
#include "FeverMan.h"

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitlePressEnter = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTitlePressEnter[2] = {};			//�e�N�X�`���ւ̃|�C���^

int nAlphaPressEnter = 0;		//PressEnter�̓��ߓx
bool bLockTitle = false;		//���ȏ�J�ڂ��Ȃ��悤�Ƀ��b�N�����`�`�`�`�`�`�`�`�`
float fTex = 0.0f;				//�e�N�X�`�����W
int nTime = 0;					//���Ԍo��
bool b = false;

//����������
void InitTitlePressEnter(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();				//�f�o�C�X���擾

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitlePressEnter,
		NULL);

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\titleText.png",
		&g_pTextureTitlePressEnter[0]);

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\press_enter.png",
		&g_pTextureTitlePressEnter[1]);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitlePressEnter->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0, 0.0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�(1.0f�Œ�)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitlePressEnter->Unlock();

	nAlphaPressEnter = 0;
	bLockTitle = false;
	fTex = 0.0f;
	nTime = 0;
	b = false;

	InitFeverMan();

	StopSound();
	PlaySound(SOUND_LABEL_DRUM_SE);
}

//�I������
void UninitTitlePressEnter(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//�e�N�X�`���j��
		if (g_pTextureTitlePressEnter[nCnt] != NULL)
		{
			g_pTextureTitlePressEnter[nCnt]->Release();
			g_pTextureTitlePressEnter[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�j��
	if (g_pVtxBuffTitlePressEnter != NULL)
	{
		g_pVtxBuffTitlePressEnter->Release();
		g_pVtxBuffTitlePressEnter = NULL;
	}
	UninitFeverMan();
}

//�X�V����
void UpdateTitlePressEnter(void)
{
	Data *pData;
	pData = GetData();

	switch (pData->nTitleNum)
	{
	case 0:
		nTime++;

		if (nTime >= 64)
		{
			nTime = 64;
			fTex += 0.00165f;

			if ((fTex + 0.04f) >= 0.15f)fTex += 0.001f;
			if ((fTex + 0.04f) >= 0.3f)fTex += 0.0001f;
			if ((fTex + 0.04f) >= 0.5f)fTex += 0.001f;
			if ((fTex + 0.04f) >= 0.7f)fTex += 0.002f;
			if ((fTex + 0.04f) >= 0.9f)fTex += 0.002f;

			if ((fTex + 0.04f) >= 1.0f)
			{
				nTime = 0;
				fTex = 0.0f;
				pData->nTitleNum++;
				PlaySound(SOUND_LABEL_TITLE_BGM);
			}
		}
		break;

	case 1:
		nTime++;
		if (nTime >= 32)
		{
			nTime = 0;
			b = true;
		}
		if (b == true)
		{
			UpdateFeverMan();
		}

		if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
		{
			bLockTitle = true;
			PlaySound(SOUND_LABEL_TITLE_SE);
			SetFade(MODE_JUGGLER);
		}

		if (bLockTitle == true)
		{
			switch (nAlphaPressEnter)
			{
			case 0:
				nAlphaPressEnter = 255;
				break;

			case 255:
				nAlphaPressEnter = 0;
				break;
			}
		}
		break;
	}

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitlePressEnter->Lock(0, 0, (void**)&pVtx, 0);

	switch (pData->nTitleNum)
	{
	case 0:
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(fTex, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(fTex + 0.04f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(fTex, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(fTex + 0.04f, 1.0f);
		break;

	case 1:
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		break;
	}

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255 - nAlphaPressEnter);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255 - nAlphaPressEnter);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255 - nAlphaPressEnter);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255 - nAlphaPressEnter);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitlePressEnter->Unlock();
}

//�`�揈��
void DrawTitlePressEnter(void)
{
	Data *pData;
	pData = GetData();

	LPDIRECT3DDEVICE9 pDevice;							//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();								//�f�o�C�X���擾

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffTitlePressEnter,
		0,
		sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);											//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitlePressEnter[pData->nTitleNum]);	//�e�N�X�`���̐ݒ�

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,							//�J�n���钸�_�̃C���f�b�N�X
		2);							//�v���~�e�B�u�̐�

	if (b == true)
	{
		DrawFeverMan();
	}
}