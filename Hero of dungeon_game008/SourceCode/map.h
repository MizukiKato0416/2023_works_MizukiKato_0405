//===========================================
//�}�b�v����
//Author:KatoMizuki
//===========================================
#ifndef _MAP_H_
#define _MAP_H_
#include "object2D.h"

//�O���錾

//================================================
//�}�N����`
//================================================
#define MAP_ROOM_SIZE		(40.0f)											//�����̑傫��
#define MAP_SIZE			(200.0f)										//�}�b�v�̃T�C�Y
#define MAP_PLAYER_SIZE		(15.0f)											//�}�b�v�̃v���C���[�̃T�C�Y
#define MAP_CHECK_SIZE		(13.0f)											//�}�b�v�̃`�F�b�N�|�C���g�̃T�C�Y
#define MAP_ENEMY_SIZE		(8.0f)											//�}�b�v�̓G�̃T�C�Y
#define MAP_POS_X			(SCREEN_WIDTH - MAP_SIZE / 2.0f - 20.0f)		//�}�b�v�̌��_X
#define MAP_POS_Y			(MAP_SIZE / 2.0f + 20.0f)						//�}�b�v�̌��_Y

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMap : public CObject2D
{
public:
	//MAP�̎��
	enum class TYPE
	{
		NONE = 0,
		START,		//�X�^�[�g�̓�
		ROAD,		//��
		WALL,		//��
		PLAYER,		//�v���C���[
		ENEMY,		//�G
		CHECK,		//�`�F�b�N�|�C���g
		WARP,		//���[�v
		MAX
	};

	CMap(int nPriority = PRIORITY_MAP);	//�R���X�g���N�^
	~CMap();							//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMap *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriolty, TYPE type);
	//�}�b�v�̈ʒu�ݒ菈��
	static void SetStartRoomPos(void);
	//�G�̃|�C���^�ݒ菈��
	static void SetEnemyPointa(void);
	//�`�F�b�N�|�C���g�̃|�C���^�ݒ菈��
	static void SetCheckPointa(void);
	//�j������
	static void Delete(CObject *pSubjectObject);

private:
	//�����o�֐�
	void PlayerMove(void);				//�v���C���[�����������̏���
	void EnemyMove(void);				//�G������������ ����
	void DrawRange(D3DXVECTOR3 pos);	//�`��͈̔͂Ɋւ��鏈��

	static D3DXVECTOR3 m_posStartRoom;	//�X�^�[�g���镔���̌��ݒn
	TYPE m_type;						//MAP�̎��
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	bool m_bDraw;						//�`�悷�邩�ǂ���
	CObject *m_pObject;					//�I�u�W�F�N�g�̃|�C���^
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_MAP_H_