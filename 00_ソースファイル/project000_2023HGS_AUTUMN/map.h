//==========================================
//
//  �}�b�v�N���X(map.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MAP_H_
#define _MAP_H_

//==========================================
//  �O���錾
//==========================================
class CSpot;

//==========================================
//  �N���X��`
//==========================================
class CMap
{
public:

	//�����o�֐�
	CMap();
	~CMap();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	float GetWorldMove(void) { return m_vecMove; } //���E�ړ��ʂ̎擾
	D3DXVECTOR3 GetHeightMin(void); //��ԒႢ�n�_�̎擾
	D3DXVECTOR3 GetHeightNext(void); //��ԖڂɒႢ�n�_�̎擾
	void DeleteMin(void); //��ԒႢ�z���폜

private:

	//�����ݒ�p�\����
	struct DIFF
	{
		int nMinY; //Y�ŏ��l
		int nMaxY; //Y�ő�l
		int nMinX; //X�ŏ��l
		int nMaxX; //X�ő�l
	};

	//�萔
	const static DIFF m_Diff;
	static float m_vecMove; //���E�̈ړ���
#define NUM (10) //�f�[�^��

	//�����o�ϐ�
	CSpot* m_pSpot[NUM]; //�ړ��n�_

	//�����o�֐�
	void SetSpot(void);

};

#endif
