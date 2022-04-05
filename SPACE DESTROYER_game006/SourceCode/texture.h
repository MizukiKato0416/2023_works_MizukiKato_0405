//=============================================================================
//�e�N�X�`������
//Authore:��������
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CTexture
{
public:
	//�e�N�X�`���^�C�v
	typedef enum
	{
		TYPE_PLAYER = 0,					//�v���C���[
		TYPE_BULLET_PLAYER_NORMAL,			//�v���C���[�̒ʏ�e
		TYPE_BULLET_SPHERE,					//�ۂ��e
		TYPE_BULLET_BOSS_STRAIGHT,			//�{�X�̒��i�e
		TYPE_BULLET_BOSS_LASER,				//�{�X�̃��[�U�[�e
		TYPE_BULLET_BOSS_BODY_HOMING,		//�{�X�̑̂���o���z�[�~���O�e
		TYPE_EXPLOSION,						//����
		TYPE_BG_00,							//�w�i00
		TYPE_BG_01,							//�w�i01
		TYPE_BG_02,							//�w�i02
		TYPE_BG_MENU,						//�w�i(���j���[���)
		TYPE_BG_RESULT,						//�w�i(���U���g���)
		TYPE_ENEMY_FIGHTER,					//�G�퓬�@
		TYPE_ENEMY_UFO,						//�GUFO
		TYPE_ENEMY_SPHERE,					//���̌^�G
		TYPE_ENEMY_ITEM_POWER,				//�p���[�A�b�v�A�C�e���𗎂Ƃ��G
		TYPE_ENEMY_ITEM_SPEED,				//�X�s�[�h�A�b�v�A�C�e���𗎂Ƃ��G
		TYPE_PLAYER_BULLET_00,				//�v���C���[�̒e00
		TYPE_EFFECT,						//�G�t�F�N�g
		TYPE_NUMBER,						//�i���o�[
		TYPE_PLAYER_LIFE,					//�v���C���[�̃��C�t
		TYPE_ITEM_SPEED,					//�e�̘A�˃X�s�[�h���オ��A�C�e��
		TYPE_ITEM_POWER,					//�e�̃��x�����A�b�v����A�C�e��
		TYPE_ITEM_SCORE,					//�X�R�A���A�b�v����A�C�e��
		TYPE_MENU_BAND,						//���j���[��ʂɂ���㉺�̑�
		TYPE_MENU_CIRCLE_SMALL,				//���j���[��ʂɂ���~(��)
		TYPE_MENU_CIRCLE_BIG,				//���j���[��ʂɂ���~(��)
		TYPE_MENU_EXPLANATION_GAME,			//���j���[��ʂɂ��������(GameStart)
		TYPE_MENU_EXPLANATION_TUTORIAL,		//���j���[��ʂɂ��������(Tutorial)
		TYPE_MENU_EXPLANATION_EXIT,			//���j���[��ʂɂ��������(Exit)
		TYPE_MENU_GAME_START,				//���j���[��ʂ�GameStart
		TYPE_MENU_TUTORIAL,					//���j���[��ʂ�Tutorial
		TYPE_MENU_EXIT,						//���j���[��ʂ�Exit
		TYPE_BOSS_WING,						//�{�X�̉H
		TYPE_BOSS_BODY,						//�{�X�̑�
		TYPE_BOSS_CANNON,					//�{�X�̑�C
		TYPE_PAUSE,							//�|�[�Y��ʂ̘g
		TYPE_PAUSE_EXIT,					//�|�[�Y��ʂ�Exit
		TYPE_PAUSE_CONTINUE,				//�|�[�Y��ʂ�Continue
		TYPE_DAMAGE_MASK,					//�_���[�W���󂯂��ۂ̃}�X�N
		TYPE_TUTORIAL_EXPLANATION_000,		//�`���[�g���A���̐�����
		TYPE_TUTORIAL_EXPLANATION_001,		//�`���[�g���A���̐�����
		TYPE_TUTORIAL_EXPLANATION_002,		//�`���[�g���A���̐�����
		TYPE_TUTORIAL_EXPLANATION_003,		//�`���[�g���A���̐�����
		TYPE_TUTORIAL_EXPLANATION_004,		//�`���[�g���A���̐�����
		TYPE_TUTORIAL_EXPLANATION_005,		//�`���[�g���A���̐�����
		TYPE_GAME_CLEAR,					//�Q�[���N���A
		TYPE_GAME_OVER,						//�Q�[���I�[�o�[
		TYPE_TITLE,							//�^�C�g����
		TYPE_PRESS_START,					//pressStart
		TYPE_ENEMY_KILL_SCORE_100,			//�G��|�����Ƃ��ɏo��X�R�A(100)
		TYPE_ENEMY_KILL_SCORE_200,			//�G��|�����Ƃ��ɏo��X�R�A(200)
		TYPE_ENEMY_KILL_SCORE_400,			//�G��|�����Ƃ��ɏo��X�R�A(400)
		TYPE_MAX							//�e�N�X�`���̍ő吔
	} TYPE;

	CTexture();			//�R���X�g���N�^
	~CTexture();		//�f�X�g���N�^

	void Init(void);	// �e�N�X�`���̐���
	LPDIRECT3DTEXTURE9 GetTexture(TYPE Type);	// �e�N�X�`���̊��蓖��
	void Uninit(void);	// �I��
private:
	LPDIRECT3DTEXTURE9	m_pTexture[TYPE_MAX];	//�e�N�X�`��
};

#endif