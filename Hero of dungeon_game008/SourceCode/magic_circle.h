//===========================================
//���@�w����
//Author:KatoMizuki
//===========================================
#ifndef _MAGIC_CIRCLE_H_
#define _MAGIC_CIRCLE_H_
#include "object3D.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMagicCircle : public CObject3D
{
public:
	//��]���̎��
	enum class ROTATE_TYPE
	{
		NONE = 0,
		X ,			//X��
		Y,			//Y��
		Z,			//Z��
		MAX
	};

	CMagicCircle(int nPriority = PRIORITY_POLYGON_3D);		//�R���X�g���N�^
	~CMagicCircle();										//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMagicCircle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);
	void SetRotateType(ROTATE_TYPE rotateType) { m_rotateType = rotateType; }		//��]���ݒ菈��

private:
	ROTATE_TYPE m_rotateType;			//��]���̎��
};

#endif // !_MAGIC_CIRCLE_H_