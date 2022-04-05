//=============================================================================
//�e�N�X�`������
//Authore:��������
//=============================================================================
#include "texture.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{

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
	pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X���擾����

	//�e�N�X�`���̓ǂݍ���
	//��
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/base/sky.jpg",
		&m_pTexture[TEX_TYPE_SKY]);

	//�n��
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/base/mist.png",
		&m_pTexture[TEX_TYPE_TILE]);

	//�i���o�[
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/number.png",
		&m_pTexture[TEX_TYPE_NUMBER]);

	//�J���}
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/comma.png",
		&m_pTexture[TEX_TYPE_COMMA]);

	//�^�C�g���w�i
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TITLE/title_bg.png",
		&m_pTexture[TEX_TYPE_TITLE_BG]);

	//�^�C�g��UI:�^�C�g�����S
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TITLE/title_ui_logo.png",
		&m_pTexture[TEX_TYPE_TITLE_UI_LOGO]);

	//�^�C�g��UI:Press����
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TITLE/press_start_or_B!.png",
		&m_pTexture[TEX_TYPE_TITLE_UI_PRESS]);

	//�^�C�g��UI:1P�؂蔲���摜
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TITLE/title_ui_player_1p.png",
		&m_pTexture[TEX_TYPE_TITLE_UI_PLAYER_1P]);

	//�^�C�g��UI:2P�؂蔲���摜
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TITLE/title_ui_player_2p.png",
		&m_pTexture[TEX_TYPE_TITLE_UI_PLAYER_2P]);

	//���j���[�w�i
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU/menu_bg.png",
		&m_pTexture[TEX_TYPE_MENU_BG]);

	//���j���[�����g
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU/menu_ui_explanation_frame.png",
		&m_pTexture[TEX_TYPE_MEMU_EXPLANATION_FRAME]);

	//���j���[UI:��
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU/star.png",
		&m_pTexture[TEX_TYPE_MENU_UI_STAR]);

	//���j���[UI:���j���[���S
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU/menu_ui_logo.png",
		&m_pTexture[TEX_TYPE_MENU_LOGO]);

	//���j���[UI:�`���[�g���A��
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU/menu_ui_tutorial_button.png",
		&m_pTexture[TEX_TYPE_MENU_UI_TUTORIAL]);

	//���j���[UI:�Q�[���X�^�[�g
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU/menu_ui_game_button.png",
		&m_pTexture[TEX_TYPE_MENU_UI_GAME]);

	//���j���[UI:�^�C�g���ɖ߂�
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU/menu_ui_backtitle_button.png",
		&m_pTexture[TEX_TYPE_MENU_UI_BACKTITLE]);

	//���j���[UI:�`���[�g���A������
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU/menu_ui_tutorial_explanation.png",
		&m_pTexture[TEX_TYPE_MENU_UI_TUTORIAL_EXPLANATION]);

	//���j���[UI:�Q�[������
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU/menu_ui_game_explanation.png",
		&m_pTexture[TEX_TYPE_MENU_UI_GAME_EXPLANATION]);

	//���j���[UI:�Q�[���I������
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU/menu_ui_backtitle_explanation.png",
		&m_pTexture[TEX_TYPE_MENU_UI_BACKTITLE_EXPLANATION]);

	//�`���[�g���A��UI:�������
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TUTORIAL/tutorial_ui_explanation.png",
		&m_pTexture[TEX_TYPE_TUTORIAL_EXPLANATION]);

	//�Q�[��UI:�J�E���g�_�E��3
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/game_countdown3.png",
		&m_pTexture[TEX_TYPE_GAME_UI_COUNTDOWN03]);

	//�Q�[��UI:�J�E���g�_�E��2
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/game_countdown2.png",
		&m_pTexture[TEX_TYPE_GAME_UI_COUNTDOWN02]);

	//�Q�[��UI:�J�E���g�_�E��1
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/game_countdown1.png",
		&m_pTexture[TEX_TYPE_GAME_UI_COUNTDOWN01]);

	//�Q�[��UI:�X�^�[�g
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/game_start.png",
		&m_pTexture[TEX_TYPE_GAME_UI_START]);

	//�Q�[��UI:�Q�[���N���A
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/game_clear.png",
		&m_pTexture[TEX_TYPE_GAME_UI_CLEAR]);

	//�Q�[��UI:�^�C���A�b�v
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/timeup.png",
		&m_pTexture[TEX_TYPE_GAME_UI_TIME_UP]);

	//�S�[���e�[�v
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/goal_tape.jpg",
		&m_pTexture[TEX_TYPE_GOAL_TAPE]);

	//���U���g�w�i
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT/result_bg.png",
		&m_pTexture[TEX_TYPE_RESULT_BG]);

	//���U���gUI:Win
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT/Win!.png",
		&m_pTexture[TEX_TYPE_RESULT_UI_WIN]);

	//���U���gUI:�����L���O1��
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT/1st.png",
		&m_pTexture[TEX_TYPE_RESULT_UI_RANKING01]);

	//���U���gUI:�����L���O2��
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT/2nd.png",
		&m_pTexture[TEX_TYPE_RESULT_UI_RANKING02]);

	//���U���gUI:�����L���O3��
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT/3rd.png",
		&m_pTexture[TEX_TYPE_RESULT_UI_RANKING03]);

	//���U���gUI:�����L���O4��
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT/4th.png",
		&m_pTexture[TEX_TYPE_RESULT_UI_RANKING04]);

	//���U���gUI:�����L���O5��
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT/5th.png",
		&m_pTexture[TEX_TYPE_RESULT_UI_RANKING05]);

	//�|�[�YUI:�g
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PAUSE/pause_frame.png",
		&m_pTexture[TEX_TYPE_PAUSE_UI_FRAME]);

	//�|�[�YUI:�ĊJ
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PAUSE/pause_ui_start.png",
		&m_pTexture[TEX_TYPE_PAUSE_UI_START]);

	//�|�[�YUI:�I��
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PAUSE/pause_ui_exit.png",
		&m_pTexture[TEX_TYPE_PAUSE_UI_EXIT]);

	//�|�[�YUI:��蒼��
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PAUSE/pause_ui_restart.png",
		&m_pTexture[TEX_TYPE_PAUSE_UI_RESTART]);

	//�W�����v�G�t�F�N�g
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PLAYER/Jump_kemuri.png",
		&m_pTexture[TEX_TYPE_JUMP_SMOKE]);

	//�e�G�t�F�N�g
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PLAYER/effect000.jpg",
		&m_pTexture[TEX_TYPE_EFFECT]);

	//1P
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PLAYER/1P.png",
		&m_pTexture[TEX_TYPE_PLAYER_UI_1P]);

	//2P
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PLAYER/2P.png",
		&m_pTexture[TEX_TYPE_PLAYER_UI_2P]);
}

//=============================================================================
//�I��
//=============================================================================
void CTexture::Uninit(void)
{
	for (int nCntTexture = 0; nCntTexture < TEX_TYPE_MAX; nCntTexture++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCntTexture] != NULL)
		{
			m_pTexture[nCntTexture]->Release();
			m_pTexture[nCntTexture] = NULL;
		}
	}
}

//=============================================================================
//�e�N�X�`�����蓖��
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEX_TYPE type)
{
	return m_pTexture[type];
}