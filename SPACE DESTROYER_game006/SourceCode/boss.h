//===========================================
//�{�X�̏���
//Authore:��������
//===========================================
#ifndef _BOSS_H_
#define _BOSS_H_
#include "scene.h"

//�O���錾
class CScene2D;
//================================================
//�}�N����`
//================================================
#define MAX_BOSS_POLYGON						(4)								//�|���S���̍ő吔
#define BOSS_WING_WIDTH							(1249.0f)						//�H�̃|���S���̕�
#define BOSS_WING_HEIGHT						(225.0f)						//�H�̃|���S���̍���
#define BOSS_BODY_WIDTH							(316.0f)						//�̂̃|���S���̕�
#define BOSS_BODY_HEIGHT						(327.0f)						//�̂̃|���S���̍���
#define BOSS_CANNON_WIDTH						(91.0f)							//��C�̃|���S���̕�
#define BOSS_CANNON_HEIGHT						(128.0f)						//��C�̃|���S���̍���
#define BOSS_CANNON_POS							(400.0f)						//�{�X�̒��S�ʒu����̑�C�̑��ΓI�Ȉʒu
#define BOSS_BODY_COLLISION_ADJUST				(-100.0f)						//�{�X�̑̂̓����蔻�蒲�߂̒l
#define BOSS_BODY_COLLISION_PLAYER_ADJUST		(-50.0f)						//�v���C���[�ƃ{�X�̑̂̓����蔻�蒲�߂̒l
#define BOSS_WING_COLLISION_ADJUST				(-200.0f)						//�{�X�̉H�̓����蔻�蒲�߂̒l
#define BOSS_WING_COLLISION_PLAYER_ADJUST		(-80.0f)						//�v���C���[�ƃ{�X�̉H�̓����蔻�蒲�߂̒l
#define BOSS_CANNON_COLLISION_ADJUST			(-50.0f)						//�{�X�̑�C�̓����蔻�蒲�߂̒l
#define BOSS_CANNON_COLLISION_PLAYER_ADJUST		(-10.0f)						//�v���C���[�ƃ{�X�̑�C�̓����蔻�蒲�߂̒l
#define BOSS_DAMAGE_COUNT						(10)							//�_���[�W���󂯂Ă����Ԃ̎���
#define BOSS_BODY_LIFE							(300)							//�̂̃��C�t
#define BOSS_WING_LIFE							(200)							//�H�̃��C�t
#define BOSS_CANNON_LIFE						(150)							//��C�̃��C�t
#define BOSS_CANNON_SHOOT_COUNTER				(180)							//��C���e�����Ԋu
#define BOSS_CANNON_SHOOT_ADJUST_X				(20.0f)							//��C���e���o��X���W����
#define BOSS_CANNON_SHOOT_ADJUST_Y				(50.0f)							//��C���e���o��Y���W����
#define BOSS_BODY_SHOOT_LASER_TIME				(200)							//�̂����[�U�[���o������
#define BOSS_BODY_SHOOT_LASER_COUNT				(100)							//�̂����[�U�[���o���^�C�~���O
#define BOSS_BODY_SHOOT_STRAIGHT_COUNT_0		(90)							//�̂̒��i����e���o���^�C�~���O����1
#define BOSS_BODY_SHOOT_STRAIGHT_COUNT_1		(180)							//�̂̒��i����e���o���^�C�~���O����2
#define BOSS_BODY_SHOOT_STRAIGHT_ADJUST			(40.0f)							//�̂̒��i����e���o���ʒu�����̒l
#define BOSS_BODY_SHOOT_ADJUST_Y				(60.0f)							//�̂̒e���o��y���W�����̒l
#define BOSS_BODY_SHOOT_DIFFUSION_00_NUM		(5)								//�̂̊g�U�e���o����00
#define BOSS_BODY_SHOOT_DIFFUSION_01_NUM		(6)								//�̂̊g�U�e���o����01
#define BOSS_BODY_SHOOT_DIFFUSION_00_COUNT		(120)							//�̂̊g�U�e00���o���^�C�~���O
#define BOSS_BODY_SHOOT_DIFFUSION_01_COUNT		(240)							//�̂̊g�U�e01���o���^�C�~���O
#define BOSS_BODY_SHOOT_HOMING_COUNT			(15)							//�z�[�~���O�e���o���^�C�~���O
#define BOSS_BODY_SHOOT_STRAIGHT_PHASE_COUNT	(800)							//�̂̒��i����e���o���t�F�[�Y�̎���
#define BOSS_BODY_SHOOT_DIFFUSION_PHASE_COUNT	(1000)							//�̂̊g�U����e���o���t�F�[�Y�̎���
#define BOSS_BODY_SHOOT_LASER_PHASE_COUNT		(600)							//�̂̃��[�U�[�e���o���t�F�[�Y�̎���
#define BOSS_BODY_SHOOT_HOMING_PHASE_COUNT		(280)							//�̂̃z�[�~���O�e���o���t�F�[�Y�̎���
#define BOSS_BODY_SHOOT_LASER_EFFECT_NUM		(6)								//�̂̃��[�U�[�e���o������̃G�t�F�N�g�̐�
#define BOSS_BODY_SHOOT_LASER_EFFECT_TIME		(40)							//�̂̃��[�U�[�e���o������̃G�t�F�N�g���o������
#define BOSS_BODY_SHOOT_LASER_EFFECT_COUNT		(3)								//�̂̃��[�U�[�e���o������̃G�t�F�N�g���o���Ԋu
#define BOSS_BODY_SHOOT_LASER_EFFECT_ADJUST		(300.0f)						//�̂̃��[�U�[�e���o������̃G�t�F�N�g���o���ʒu�����l
#define BOSS_CLEAR_UNINIT_COUNT					(500)							//�{�X��j������܂ł̎���
#define BOSS_CLEAR_EXPLOSION_COUNT				(10)							//�{�X�|�����Ƃ��ɏo��G�t�F�N�g�̐����Ԋu
#define BOSS_CLEAR_EXPLOSION_POS_X				((float)(rand() % 1250 + 15))	//�{�X�|�����Ƃ��ɏo��G�t�F�N�g��X���W
#define BOSS_CLEAR_EXPLOSION_POS_Y				((float)(rand() % 201))			//�{�X�|�����Ƃ��ɏo��G�t�F�N�g��Y���W

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CBoss : public CScene
{
public:
	CBoss(int nPriority = PRIORITY_BOSS);					//�R���X�g���N�^
	~CBoss();												//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBoss *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move);

	D3DXVECTOR3 GetBodyPos(void);			//�̂̈ʒu�擾����

private:
	//�{�X�̏��
	typedef enum
	{
		BOSS_STATE_NONE = 0,
		BOSS_STATE_NORMAL,
		BOSS_STATE_DAMAGE,
		BOSS_STATE_MAX
	} BOSS_STATE;

	//�{�X�̖{�̂̎ˌ��t�F�[�Y
	typedef enum
	{
		BOSS_BODY_SHOOT_PHASE_NONE = 0,
		BOSS_BODY_SHOOT_PHASE_STRAIGHT,			//���i
		BOSS_BODY_SHOOT_PHASE_DIFFUSION_00,		//�g�U00
		BOSS_BODY_SHOOT_PHASE_LASER,			//���[�U�[
		BOSS_BODY_SHOOT_PHASE_HOMING,			//�ǔ�
		BOSS_BODY_SHOOT_PHASE_MAX
	} BOSS_BODY_SHOOT_PHASE;

	//�����o�֐�
	void StateColor(int nCntPolygon);								//��Ԃɉ������F�ɕω������鏈��
	bool CollisionPlayerBullet(void);								//�v���C���[�̒e�Ƃ̓����蔻��
	void Shoot(int nCntPolygon);									//�ˌ�����
	void BodyShoot(int nCntPolygon);								//�̕����̎ˌ�����
	bool GameClear(void);											//�Q�[���N���A���̏���

	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_BOSS_POLYGON];			//�e�N�X�`���ւ̃|�C���^
	CScene2D *m_apScene2D[MAX_BOSS_POLYGON];						//Scene2D�̃C���X�^���X
	D3DXVECTOR3	m_size[MAX_BOSS_POLYGON];							//�T�C�Y
	D3DXVECTOR3	m_pos[MAX_BOSS_POLYGON];							//�ʒu
	D3DXVECTOR3	m_move;												//�ړ���
	int m_nBulletCounter[MAX_BOSS_POLYGON];							//�e���˗p�J�E���^
	BOSS_STATE m_state[MAX_BOSS_POLYGON];							//�{�X�̏��
	int m_nDamageCounter[MAX_BOSS_POLYGON];							//�_���[�W���󂯂Ă����Ԃ̃J�E���^�[
	int m_nLife[MAX_BOSS_POLYGON];									//���C�t
	BOSS_BODY_SHOOT_PHASE m_shootPhase;								//�{�̂̎ˌ��t�F�[�Y
	int m_nNextPhase;												//���̃t�F�[�Y�ɍs���܂ł̎���
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_BOSS_H_