#include "Block.h"

CBlock::CBlock():
	m_Texture(),
	m_Rect(),
	m_Item(),
	m_Type(0),
	m_SPos(),
	m_Pos(),
	m_Move(),
	m_Broken(0),
	m_BAttacked(false),
	m_Attacked(false),
	m_Dirction(0)
{
}

CBlock::~CBlock()
{
}

bool CBlock::Load(CTexture* tex, Vector2 pos, CRectangle rec, CItem* item, int type, int broken, CBlockDefine* define)
{
	m_Texture = tex;
	m_SPos = pos;
	m_Pos = pos;
	m_Rect = rec;
	m_Item = item;
	m_Type = type;
	m_Broken = broken;
	m_define = define;
	m_BAttacked = false;
	m_Attacked = false;
	m_Move = CVector2(m_define->x_ext1, m_define->y_ext1);
	m_Dirction = define->block;
	return true;
}

void CBlock::Update()
{
	if (m_Attacked) {
		if (m_BAttacked) {
			m_Attacked = false;
		}
		m_BAttacked = true;
	}
	else {
		m_BAttacked = false;
	}
	if (m_Type < 0) {
		return;
	}
	m_Pos += m_Move;
}

void CBlock::Render(float wx, float wy)
{
	if (m_Type < 0) {
		return;
	}

	float sw = g_pGraphics->GetTargetWidth();
	float sh = g_pGraphics->GetTargetHeight();
	if (m_Pos.x - wx + CHIPSIZE < 0 || m_Pos.x - wx > sw ||
		m_Pos.y - wy + CHIPSIZE < 0 || m_Pos.y - wy > sh) {
		return;
	}

	m_Texture->Render(m_Pos.x - wx, m_Pos.y - wy, m_Rect);
}

//�u���b�N��@��
void CBlock::AttackBlock(CPlayer* pl, CTexture* itemTextures)
{
	CRectangle r = pl->GetRect(true);
	if (pl->IsJumpingUp()) { //�W�����v�����ǂ���
		if (m_Type < 0) { //�\������Ă���u���b�N���ǂ���
			return;
		}

		//�}���I�̎�ނ����̃u���b�N���󂹂邩�ǂ���
		if ((m_define->broken /* ���󂹂�}���I�̎�� */ & pl->GetType()) != pl->GetType()) {
			if (m_Item == NULL)	return;
		}
		m_Attacked = true;

		//���̃u���b�N�ɃA�C�e�����܂܂�Ă��邩
		if (m_Item != NULL) {
			m_Item->BShow(m_Pos, pl->GetType(), itemTextures); //�A�C�e����\��������

			m_Type = m_define->nextIdx_Item - 1; //���̃u���b�N�̔ԍ���@���ꂽ��̃u���b�N�ԍ��ɕς��� (�A�C�e�����ӂ��܂�Ă���ꍇ)

			m_Item = NULL; //�o���������̂ŃA�C�e�����Ȃ���
		}
		else {
			m_Type = m_define->nextIdx - 1; //���̃u���b�N�̔ԍ���@���ꂽ��̃u���b�N�ԍ��ɕς���
		}

		m_define = CGameDefine::GetGameDefine()->GetBlockByIdx(m_Type + 1); //�@���ꂽ��̃u���b�N�ԍ��̒�`���擾����
		if (m_define == NULL) { //��`��������Ȃ������ꍇ
			m_Type = -1;
			return;
		}
		m_Dirction = m_define->block; //�����蔻����s���������X�V����
		m_Move.x = m_define->x_ext1; //�u���b�N�̈ړ����x���X�V����
		m_Move.y = m_define->y_ext1;


		//�摜�̕\���ʒu�i�}�b�v�`�b�v�̈ʒu�j���X�V����
		int tcx = m_Texture->GetWidth() / CHIPSIZE;
		m_Rect = CRectangle(m_Type % tcx, m_Type / tcx, m_Type % tcx + 1, m_Type / tcx + 1) * CHIPSIZE; 
	}
}
