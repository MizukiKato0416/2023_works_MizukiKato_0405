//===========================================
//�v���C���[����
//Authore:��������
//===========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "scene2D.h"

//�O���錾
class CUi;

//================================================
//�}�N����`
//================================================
#define PLAYER_WIDTH							(70.0f)		//�|���S���̕�
#define PLAYER_HEIGHT							(70.0f)		//�|���S���̍���
#define MAX_PLAYER_LIFE							(8)			//�v���C���[�̃��C�t�̍ő�l
#define MAX_PLAYER_INIT_LIFE					(5)			//�v���C���[�̃��C�t�̏����l
#define PLAYER_MOVE								(7.0f)		//�v���C���[�̈ړ����x
#define PLAYER_BULLET_NEXT_SHOOT_LEVEL_1		(20)		//���̒e��ł܂ł̊Ԋu���x��1
#define PLAYER_BULLET_NEXT_SHOOT_LEVEL_2		(15)		//���̒e��ł܂ł̊Ԋu���x��2
#define PLAYER_BULLET_NEXT_SHOOT_LEVEL_3		(10)		//���̒e��ł܂ł̊Ԋu���x��3
#define PLAYER_BULLET_NEXT_SHOOT_LEVEL_4		(5)			//���̒e��ł܂ł̊Ԋu���x��4
#define PLAYER_COLLISION_ADJUST					(25.0f)		//�v���C���[�̓����蔻�蒲���p
#define PLAYER_COLLISION_ENEMY_BULLET_ADJUST	(20.0f)		//�G�̒e�Ƃ̓����蔻�蒲���p
#define PLAYER_BULLET_POWER_LEVEL_2_POS_X		(20.0f)		//�e�̃��x��2����������鎞�̃v���C���[��X���W����ǂꂾ������Ă��邩���Βl
#define PLAYER_DAMAGE_COUNT						(300)		//�_���[�W���󂯂Ă����Ԃ̎���
#define PLAYER_BLINK_COUNT						(5)			//�_�ł���܂ł̃J�E���g
#define PLAYER_OVER_UNINIT_COUNT				(300)		//�v���C���[��j������܂ł̎���
#define PLAYER_OVER_EXPLOSION_COUNT				(30)		//�v���C���[�|�����Ƃ��ɏo��G�t�F�N�g�̐����Ԋu


//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CPlayer : public CScene2D
{
public:
	//�v���C���[�̒e�̏��
	typedef enum
	{
		PLAYER_BULLET_POWER_LEVEL_NONE = 0,
		PLAYER_BULLET_POWER_LEVEL_1,
		PLAYER_BULLET_POWER_LEVEL_2,
		PLAYER_BULLET_POWER_LEVEL_3,
		PLAYER_BULLET_POWER_LEVEL_4,
		PLAYER_BULLET_POWER_LEVEL_MAX
	} PLAYER_BULLET_POWER_LEVEL;

	//�v���C���[�̒e�̑����̏��
	typedef enum
	{
		PLAYER_BULLET_SPEED_LEVEL_NONE = 0,
		PLAYER_BULLET_SPEED_LEVEL_1,
		PLAYER_BULLET_SPEED_LEVEL_2,
		PLAYER_BULLET_SPEED_LEVEL_3,
		PLAYER_BULLET_SPEED_LEVEL_4,
		PLAYER_BULLET_SPEED_LEVEL_MAX
	} PLAYER_BULLET_SPEED_LEVEL;

	//�v���C���[�̏��
	typedef enum
	{
		PLAYER_STATE_NONE = 0,
		PLAYER_STATE_NORMAL,
		PLAYER_STATE_DAMAGE,
		PLAYER_STATE_MAX
	} PLAYER_STATE;

	CPlayer(int nPriority = PRIORITY_PLAYER);				//�R���X�g���N�^
	~CPlayer();												//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3	size);

	void SetBulletPowerLevel(PLAYER_BULLET_POWER_LEVEL bulletPowerLevel);	//�e�̃��x���ݒ菈��
	PLAYER_BULLET_POWER_LEVEL GetBulletPowerLevel(void);					//�e�̃��x���擾����
	void SetBulletSpeedLevel(PLAYER_BULLET_SPEED_LEVEL bulletSpeedLevel);	//���̒e�����܂ł̑����̃��x���ݒ菈��
	PLAYER_BULLET_SPEED_LEVEL GetBulletSpeedLevel(void);					//���̒e�����܂ł̑����̃��x���擾����
	PLAYER_STATE GetPlayerState(void);										//�v���C���[�̏�Ԏ擾����
	void SetPlayerState(PLAYER_STATE state);								//�v���C���[�̏�Ԑݒ菈��
	int GetLife(void);														//�v���C���[�̃��C�t�擾����
	void SetLife(int nLife);												//�v���C���[�̃��C�t�ݒ菈��

private:
	//�e�N�X�`���A�j���[�V�����̎��
	typedef enum
	{
		TEXPATTERN_LEFT = 0,	//�e�N�X�`���p�^�[����
		TEXPATTERN_SENTER,		//�e�N�X�`���p�^�[������
		TEXPATTERN_RIGHT,		//�e�N�X�`���p�^�[���E
		TEXPATTERN_MAX			//�e�N�X�`���p�^�[���ő�l
	} TEXPATTERN;

	//�����o�֐�
	D3DXVECTOR3 MoveLimit(D3DXVECTOR3 pos);									//�ړ�����
	bool Collision(D3DXVECTOR3 pos, CSound *pSound);						//�����蔻��
	void Move(CInputKeyboard *pInputKeyboard, CInputPadX *pInputPadX);		//�ړ�
	void Shoot(void);														//�ˌ�����
	void StateColor(void);													//��Ԃɉ������F�ɕω������鏈��
	bool GameOver(void);													//�Q�[���I�[�o�[���̏���

	static LPDIRECT3DTEXTURE9 m_pTexture;			//���L�e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_move;								//�|���S���̈ړ���
	D3DXVECTOR3	m_size;								//�T�C�Y
	float m_fAngle;									//��]�̌���
	int m_nLife;									//���C�t
	int m_nCounterShoot;							//���̒e��ł܂ł̃J�E���^�[
	int m_nCounterNotShoot;							//�e��ł��Ă��Ȃ����Ԃ̃J�E���^�[
	PLAYER_BULLET_POWER_LEVEL m_bulletPowerLevel;	//�e�̃��x��
	PLAYER_BULLET_SPEED_LEVEL m_bulletSpeedLevel;	//���̒e�����܂ł̑����̃��x��
	int m_nNextShoot;								//���̒e�����܂ł̊Ԋu
	PLAYER_STATE m_state;							//�v���C���[�̏��
	int m_nDamageCounter;							//�_���[�W���󂯂Ă����Ԃ̃J�E���^�[
	int m_nBlinkCounter;							//�_�ł����邽�߂̃J�E���^�[
	bool m_bBlink;									//�_�ł���Ƃ��̔�����Ԃ����ʂ̏�Ԃ��̃t���O
	CUi *m_pUi;										//�}�X�N���o�����߂�UI�̃|�C���^
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_PLAYER_H_