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

	//�v���C���[
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/player000.png",
		&m_pTexture[TYPE_PLAYER]);

	//�e
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/player_bullet000.png",
		&m_pTexture[TYPE_BULLET_PLAYER_NORMAL]);

	//�ۂ��e
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bullet000.png",
		&m_pTexture[TYPE_BULLET_SPHERE]);

	//�{�X�̒��i�e
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/boss_bullet_000.png",
		&m_pTexture[TYPE_BULLET_BOSS_STRAIGHT]);

	//�{�X�̃��[�U�[�e
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/boss_bullet_laser_000.png",
		&m_pTexture[TYPE_BULLET_BOSS_LASER]);

	//�{�X�̑̂���o���z�[�~���O�e
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/boss_bullet_001.png",
		&m_pTexture[TYPE_BULLET_BOSS_BODY_HOMING]);

	//����
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/explosion000.png",
		&m_pTexture[TYPE_EXPLOSION]);

	//�w�i00
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg000.jpg",
		&m_pTexture[TYPE_BG_00]);

	//�w�i01
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg001.png",
		&m_pTexture[TYPE_BG_01]);

	//�w�i02
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg002.png",
		&m_pTexture[TYPE_BG_02]);

	//�w�i(���j���[���)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/menu_bg000.jpg",
		&m_pTexture[TYPE_BG_MENU]);

	//�w�i(���U���g���)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/result_bg.png",
		&m_pTexture[TYPE_BG_RESULT]);

	//�G�퓬�@
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy000.png",
		&m_pTexture[TYPE_ENEMY_FIGHTER]);

	//�GUFO
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy001.png",
		&m_pTexture[TYPE_ENEMY_UFO]);

	//���̌^�G
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy003.png",
		&m_pTexture[TYPE_ENEMY_SPHERE]);

	//�p���[�A�b�v�A�C�e���𗎂Ƃ��G
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy_item_power.png",
		&m_pTexture[TYPE_ENEMY_ITEM_POWER]);

	//�X�s�[�h�A�b�v�A�C�e���𗎂Ƃ��G
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy_item_speed.png",
		&m_pTexture[TYPE_ENEMY_ITEM_SPEED]);

	//�v���C���[�̒e
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/hamehame.png",
		&m_pTexture[TYPE_PLAYER_BULLET_00]);

	//�G�t�F�N�g
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/effect000.jpg",
		&m_pTexture[TYPE_EFFECT]);

	//�i���o�[
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number.png",
		&m_pTexture[TYPE_NUMBER]);

	//�v���C���[�̃��C�t
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/life000.png",
		&m_pTexture[TYPE_PLAYER_LIFE]);

	//�e�̘A�˃X�s�[�h���A�b�v����A�C�e��
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/item_speed.png",
		&m_pTexture[TYPE_ITEM_SPEED]);

	//�e�̃��x�����オ��A�C�e��
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/item_power.png",
		&m_pTexture[TYPE_ITEM_POWER]);

	//�X�R�A���オ��A�C�e��
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/item_score.png",
		&m_pTexture[TYPE_ITEM_SCORE]);

	//���j���[��ʂ̏㉺�ɂ����
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ui_menu_000.png",
		&m_pTexture[TYPE_MENU_BAND]);

	//���j���[��ʂɂ���~(��)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ui_menu_001.png",
		&m_pTexture[TYPE_MENU_CIRCLE_SMALL]);

	//���j���[��ʂɂ���~(��)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ui_menu_002.png",
		&m_pTexture[TYPE_MENU_CIRCLE_BIG]);

	//���j���[��ʂɂ��������(GameStart)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ui_menu_003.png",
		&m_pTexture[TYPE_MENU_EXPLANATION_GAME]);

	//���j���[��ʂɂ��������(Tutorial)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ui_menu_005.png",
		&m_pTexture[TYPE_MENU_EXPLANATION_TUTORIAL]);

	//���j���[��ʂɂ��������(Exit)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ui_menu_006.png",
		&m_pTexture[TYPE_MENU_EXPLANATION_EXIT]);

	//���j���[��ʂɂ���GameStart
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ui_menu_004.png",
		&m_pTexture[TYPE_MENU_GAME_START]);

	//���j���[��ʂɂ���Tutorial
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ui_menu_007.png",
		&m_pTexture[TYPE_MENU_TUTORIAL]);

	//���j���[��ʂɂ���Exit
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ui_menu_008.png",
		&m_pTexture[TYPE_MENU_EXIT]);

	//�{�X�̉H
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/boss_wing.png",
		&m_pTexture[TYPE_BOSS_WING]);

	//�{�X�̑�
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/boss_body.png",
		&m_pTexture[TYPE_BOSS_BODY]);

	//�{�X�̑�C
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/boss_cannon.png",
		&m_pTexture[TYPE_BOSS_CANNON]);

	//�|�[�Y��ʂ̘g
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/pause.png",
		&m_pTexture[TYPE_PAUSE]);

	//�|�[�Y��ʂ�Exit
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/exit.png",
		&m_pTexture[TYPE_PAUSE_EXIT]);

	//�|�[�Y��ʂ�Continue
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/continue.png",
		&m_pTexture[TYPE_PAUSE_CONTINUE]);

	//�_���[�W���󂯂��ۂ̃}�X�N
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/damage_mask.png",
		&m_pTexture[TYPE_DAMAGE_MASK]);

	//�`���[�g���A���̐�����
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tutorial_explanation_000.png",
		&m_pTexture[TYPE_TUTORIAL_EXPLANATION_000]);

	//�`���[�g���A���̐�����
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tutorial_explanation_001.png",
		&m_pTexture[TYPE_TUTORIAL_EXPLANATION_001]);

	//�`���[�g���A���̐�����
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tutorial_explanation_002.png",
		&m_pTexture[TYPE_TUTORIAL_EXPLANATION_002]);

	//�`���[�g���A���̐�����
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tutorial_explanation_003.png",
		&m_pTexture[TYPE_TUTORIAL_EXPLANATION_003]);

	//�`���[�g���A���̐�����
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tutorial_explanation_004.png",
		&m_pTexture[TYPE_TUTORIAL_EXPLANATION_004]);

	//�`���[�g���A���̐�����
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tutorial_explanation_005.png",
		&m_pTexture[TYPE_TUTORIAL_EXPLANATION_005]);

	//�Q�[���N���A
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/game_clear_ui.png",
		&m_pTexture[TYPE_GAME_CLEAR]);

	//�Q�[���I�[�o�[
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/game_over_ui.png",
		&m_pTexture[TYPE_GAME_OVER]);

	//�^�C�g�����S
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/title_name.png",
		&m_pTexture[TYPE_TITLE]);

	//pressStart
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enter_or_start.png",
		&m_pTexture[TYPE_PRESS_START]);

	//�G��|�����Ƃ��ɏo��X�R�A(100)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy_kill_score_100.png",
		&m_pTexture[TYPE_ENEMY_KILL_SCORE_100]);

	//�G��|�����Ƃ��ɏo��X�R�A(200)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy_kill_score_200.png",
		&m_pTexture[TYPE_ENEMY_KILL_SCORE_200]);

	//�G��|�����Ƃ��ɏo��X�R�A(400)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy_kill_score_400.png",
		&m_pTexture[TYPE_ENEMY_KILL_SCORE_400]);
}	

//=============================================================================
//�I��
//=============================================================================
void CTexture::Uninit(void)
{
	for (int nCntTexture = 0; nCntTexture < TYPE_MAX; nCntTexture++)
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
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TYPE type)
{
	return m_pTexture[type]; 
}