//===========================================
//�V�[������
//Authore:��������
//===========================================
#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"

//================================================
//�}�N����`
//================================================
#define MAX_SCENE (2048)

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CScene
{
public:
	typedef enum
	{
		PRIORITY_NONE = 0,					//�Ȃ�
		PRIORITY_BG_0,						//�w�i0
		PRIORITY_EFFECT,					//�G�t�F�N�g
		PRIORITY_ITEM,						//�A�C�e��
		PRIORITY_BULLET_ENEMY,				//�e
		PRIORITY_ENEMY,						//�G
		PRIORITY_BOSS,						//�{�X
		PRIORITY_BULLET_PLAYER,				//�e
		PRIORITY_PLAYER,					//�v���C���[
		PRIORITY_EXPLOSION,					//����
		PRIORITY_UI,						//UI
		PRIORITY_FADE,						//�t�F�[�h
		PRIORITY_MAX
	} PRIORITY;

	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,				//�v���C���[
		OBJTYPE_BULLET_PLAYER,		//�v���C���[�̒e
		OBJTYPE_BULLET_ENEMY,		//�G�̒e
		OBJTYPE_ENEMY,				//�G
		OBJTYPE_EXPLOSION,			//����
		OBJTYPE_ITEM_SCORE,			//�X�R�A�A�b�v�A�C�e��
		OBJTYPE_ITEM_SPEED,			//�X�s�[�h�A�b�v�A�C�e��
		OBJTYPE_ITEM_POWER,			//�p���[�A�b�v�A�C�e��
		OBJTYPE_BOSS,				//�{�X
		OBJTYPE_MAX
	} OBJTYPE;

	CScene(int nPriority = PRIORITY_NONE);			//�R���X�g���N�^
	virtual ~CScene();								//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void);
	static CScene *GetScene(int nScene, int nPriority);
	D3DXVECTOR3 GetPos(void);
	void SetPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetSize(void);
	void SetSize(D3DXVECTOR3 size);

protected:
	void Release(void);

private:
	static CScene *m_apScene[PRIORITY_MAX][MAX_SCENE];
	static int m_nNumAll;					//�g�p���Ă���V�[���̑���
	int m_nID;								//�i�[��̔ԍ�
	int m_nPriority;						//�D�揇�ʂ̔ԍ�
	OBJTYPE m_objType;						//�I�u�W�F�N�g�̎��
	D3DXVECTOR3 m_pos;						//�|���S���̈ʒu
	D3DXVECTOR3 m_size;					//�|���S���̃T�C�Y
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_SCENE_H_