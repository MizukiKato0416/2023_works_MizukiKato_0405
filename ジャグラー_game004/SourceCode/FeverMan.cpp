#include "FeverMan.h"
#include "databox.h"

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFeverMan = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureFeverMan = NULL;		//�e�N�X�`���ւ̃|�C���^
float posYJump = SCREEN_HEIGHT;
float moveY = 0.0f;

//����������
void InitFeverMan(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();				//�f�o�C�X���擾

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\FeverMan.png",
		&g_pTextureFeverMan);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFeverMan,
		NULL);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFeverMan->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffFeverMan->Unlock();

	posYJump = SCREEN_HEIGHT;
	moveY = 0.0f;
}

//�I������
void UninitFeverMan(void)
{
	//�e�N�X�`���j��
	if (g_pTextureFeverMan != NULL)
	{
		g_pTextureFeverMan->Release();
		g_pTextureFeverMan = NULL;
	}

	//���_�o�b�t�@�j��
	if (g_pVtxBuffFeverMan != NULL)
	{
		g_pVtxBuffFeverMan->Release();
		g_pVtxBuffFeverMan = NULL;
	}
}

//�X�V����
void UpdateFeverMan(void)
{
	//--------------------------------------------------------------
	//�d�͊֌W

	//�W�����v
	if (posYJump >= SCREEN_HEIGHT)
	{
		moveY = -14.0f;
	}

	//�d�͂����߂�
	moveY += 1.0f;

	posYJump += moveY;

	//--------------------------------------------------------------

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFeverMan->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0, posYJump - SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, posYJump - SCREEN_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0, posYJump, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, posYJump, 0.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffFeverMan->Unlock();
}

//�`�揈��
void DrawFeverMan(void)
{
	Data *pData;
	pData = GetData();

	LPDIRECT3DDEVICE9 pDevice;							//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();								//�f�o�C�X���擾

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffFeverMan,
		0,
		sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);									//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureFeverMan);		//�e�N�X�`���̐ݒ�

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,							//�J�n���钸�_�̃C���f�b�N�X
		2);							//�v���~�e�B�u�̐�
}