//=============================================================================
//�e�N�X�`������
//Author:KatoMizuki
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "texture.h"
#include "renderer.h"
#include "manager.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
std::vector<LPDIRECT3DTEXTURE9> CTexture::m_apTexture = {};
std::vector<std::string> CTexture::m_aPas;
map<string, int> CTexture::m_texType;
int CTexture::m_nNumTex = 0;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{
	m_texType.clear();
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
//�e�N�X�`���̐���
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X���擾����

	//text�t�@�C���ǂݍ���
	FILE *pFile = fopen("data/TEXTURE/texPas/texPas.txt", "r");
	if (pFile != NULL)
	{
		char cString[128];
		//��s���ۑ�
		while (fgets(cString, 128, pFile) != NULL)
		{
			//�������ۑ�
			fscanf(pFile, "%s", cString);
			//������̒���TEX_NUM����������
			if (strncmp("TEX_NUM", cString, 8) == 0)
			{
				//�e�N�X�`���ő吔�ǂݍ���
				fscanf(pFile, "%*s%d", &m_nNumTex);

				int nNum = 0;
				//��s���ۑ�
				while (fgets(cString, 128, pFile) != NULL)
				{
					//�������ۑ�
					fscanf(pFile, "%s", cString);
					//������̒���PAS����������
					if (strncmp("PAS", cString, 4) == 0)
					{
						//�p�X�̎擾
						fscanf(pFile, "%*s%s", &cString[0]);
						m_aPas.push_back(&cString[0]);

						//���O�̎擾
						fscanf(pFile, "%*s%*s%s", cString);
						//���O�Ɛ��̊��蓖��
						m_texType[cString] = nNum;
						nNum++;
					}
				}
			}
		}
	}
	else
	{
		printf("�t�@�C�����J���܂���ł���\n");
	}
	fclose(pFile);

	for (int nCntTex = 0; nCntTex < m_nNumTex; nCntTex++)
	{
		LPDIRECT3DTEXTURE9 pTexBuffer = NULL;
		//�e�N�X�`���̐���
		D3DXCreateTextureFromFile(pDevice,
			m_aPas[nCntTex].c_str(),
			&pTexBuffer);

		m_apTexture.push_back(pTexBuffer);
	}
}

//=============================================================================
//�I��
//=============================================================================
void CTexture::Uninit(void)
{
	for (int nCntTexture = 0; nCntTexture < m_nNumTex; nCntTexture++)
	{
		//�e�N�X�`���̔j��
		if (m_apTexture[nCntTexture] != NULL)
		{
			m_apTexture[nCntTexture]->Release();
			m_apTexture[nCntTexture] = NULL;
		}
	}
}

//=============================================================================
//�e�N�X�`�����蓖��
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(std::string texType)
{
	return m_apTexture[m_texType[texType]];
}