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

//ブロックを叩く
void CBlock::AttackBlock(CPlayer* pl, CTexture* itemTextures)
{
	CRectangle r = pl->GetRect(true);
	if (pl->IsJumpingUp()) { //ジャンプ中かどうか
		if (m_Type < 0) { //表示されているブロックかどうか
			return;
		}

		//マリオの種類がそのブロックを壊せるかどうか
		if ((m_define->broken /* ←壊せるマリオの種類 */ & pl->GetType()) != pl->GetType()) {
			if (m_Item == NULL)	return;
		}
		m_Attacked = true;

		//このブロックにアイテムが含まれているか
		if (m_Item != NULL) {
			m_Item->BShow(m_Pos, pl->GetType(), itemTextures); //アイテムを表示させる

			m_Type = m_define->nextIdx_Item - 1; //このブロックの番号を叩かれた後のブロック番号に変える (アイテムがふくまれている場合)

			m_Item = NULL; //出現させたのでアイテムをなくす
		}
		else {
			m_Type = m_define->nextIdx - 1; //このブロックの番号を叩かれた後のブロック番号に変える
		}

		m_define = CGameDefine::GetGameDefine()->GetBlockByIdx(m_Type + 1); //叩かれた後のブロック番号の定義を取得する
		if (m_define == NULL) { //定義が見つからなかった場合
			m_Type = -1;
			return;
		}
		m_Dirction = m_define->block; //当たり判定を行う方向を更新する
		m_Move.x = m_define->x_ext1; //ブロックの移動速度を更新する
		m_Move.y = m_define->y_ext1;


		//画像の表示位置（マップチップの位置）を更新する
		int tcx = m_Texture->GetWidth() / CHIPSIZE;
		m_Rect = CRectangle(m_Type % tcx, m_Type / tcx, m_Type % tcx + 1, m_Type / tcx + 1) * CHIPSIZE; 
	}
}
