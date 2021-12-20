#include "Item.h"


/**
 * �R���X�g���N�^
 *
 */
CItem::CItem() :
	item_pTexture(NULL),
	item_Position(0, 0),
	item_Move(0, 0),
	item_Show(false),
	item_BlockJump(false),
	item_Appear(false),
	item_CoinCount(0),
	item_SrcRect(){
}

/**
 * �f�X�g���N�^
 *
 */
CItem::~CItem() {
	//delete[] �ŉ�������悤��Release���f�X�g���N�^�Ŏ��s����
	Release();
}

/**
 * ������
 * �p�����[�^�[����W������������B
 *
 * ����
 * [in]			px					X���W
 * [in]			py					Y���W
 * [in]			type				�G�^�C�v
 */
void CItem::Initialize(float px, float py, int type) {
	item_Type = type;
	item_Position.x = px;
	item_Position.y = py;
	item_Move = Vector2(-2.0f, 0.0f);
	item_Show = true;
	item_Appear = false;
	item_BlockJump = false;
	switch (item_Type)
	{
		case ITEM_MUSH:
		{
			//�A�j���[�V�������쐬
			SpriteAnimationCreate anime[] = {
				{
					"�L�m�R",
					0,0,
					32,32,
					FALSE,{{5,0,0}}
				},
			};
			item_Motion.Create(anime,1);
			break;
		}
		case ITEM_COIN:
		{
			//�A�j���[�V�������쐬
			SpriteAnimationCreate anime[] = {
				{
					"�R�C��",
					0,0,
					32,32,
					TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0}}
				},
			};
			item_Motion.Create(anime, 1);
			break;
		}
		case ITEM_FOAM_MUSH:
		{
			//�A�j���[�V�������쐬
			SpriteAnimationCreate anime[] = {
				{
					"�A�L�m�R",
					0,0,
					32,32,
					TRUE,{{15,0,0},{15,1,0},{15,2,0},{15,1,0}}
				},
			};
			item_Motion.Create(anime, 1);
			break;
		}
		case ITEM_FOAM_COIN:
		{
			//�A�j���[�V�������쐬
			SpriteAnimationCreate anime[] = {
				{
					"�A�R�C��",
					0,0,
					32,32,
					TRUE,{{10,0,0},{10,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0}}
				},
			};
			item_Motion.Create(anime, 1);
			break;
		}
		default :
		{
			//�A�j���[�V�������쐬
			SpriteAnimationCreate anime[] = {
				{
					"�R�C��",
					0,0,
					32,32,
					FALSE,{{5,0,0}}
				},
			};
			item_Motion.Create(anime, 1);
			break;
		}
			
	}

}

/**
 * �X�V
 *
 */
void CItem::Update(float wx,float wy) {
	//�擾����\��
	if (!item_Show)
	{
		return;
	}
	if (wx > item_Position.x + item_pTexture->GetWidth() || wx + g_pGraphics->GetTargetWidth() < item_Position.x)
	{
		return;
	}
	//�A�j���[�V�����̍X�V
	item_Motion.AddTimer(CUtilities::GetFrameSecond());
	item_SrcRect = item_Motion.GetSrcRect();
	if (item_Type == ITEM_COIN)
	{
		item_SrcRect.Bottom -= 5;
	}
	switch (item_Type)
	{
		case ITEM_MUSH:
		{
			//�@�����u���b�N�Ɠ����ʒu�Ȃ�W�����v����
			if (item_BlockJump)
			{
				if (item_Appear)
				{
					item_Move.y = -ITEM_BLOCKJUMP;
					item_BlockJump = false;
				}
				item_Appear = true;
			}

			//�o���O��\���i�����蔻��͎c���i�X�e�[�W�Ɣ��肪���邽�߁j�j
			if (!item_Appear)
			{
				return;
			}

			//�d�͂ɂ�艺�ɏ�����������
			item_Move.y += ITEM_GRAVITY;
			if (item_Move.y >= 20.0f)
			{
				item_Move.y = 20.0f;
			}
			//���ۂɍ��W���ړ�������
			item_Position.x += item_Move.x;
			item_Position.y += item_Move.y;
			break;
		}
		case ITEM_COIN:
		{
			item_Move = Vector2(0, 0);
			break;
		}
		case ITEM_FOAM_MUSH:
		{
			item_Move.x += CUtilities::GetFrameSecond();

			//�ӂ�ӂ핂������
			item_Move.y = sin(item_Move.x) * 1.0f;

			//���ۂɍ��W���ړ�������
			item_Position.x += -1;
			item_Position.y += item_Move.y;
			break;
		}
		case ITEM_FOAM_COIN:
		{
			item_Move.x += CUtilities::GetFrameSecond();
			//�ӂ�ӂ핂������
			item_Move.y = sin(item_Move.x) * 1.0f;
			
			//���ۂɍ��W���ړ�������
			item_Position.x += -1;
			item_Position.y += item_Move.y;
			break;
		}
		default:
		{
			break;
		}


	}
	
	
	
	
}

/**
 * �X�e�[�W�Ƃ̓�����
 *
 * ����
 * [in]			ox					X���܂��
 * [in]			oy					Y���܂��
 */
void CItem::CollisionStage(float ox, float oy) {
	if (item_Type == ITEM_FOAM_MUSH || item_Type == ITEM_FOAM_COIN)
	{
		return;
	}

		item_Position.x += ox;
		item_Position.y += oy;
		//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
		if (oy < 0 && item_Move.y > 0)
		{
			item_Move.y = 0;
		}
		else if (oy > 0 && item_Move.y < 0)
		{
			item_Move.y = 0;
		}
		//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
		if (ox < 0 && item_Move.x > 0)
		{
			item_Move.x *= -1;
		}
		else if (ox > 0 && item_Move.x < 0)
		{
			item_Move.x *= -1;
		}
}

 

/**
 * �`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CItem::Render(float wx, float wy) {
	//��\��
	if (!item_Show)
	{
		return;
	}
	if (wx > item_Position.x + item_pTexture->GetWidth() || wx + g_pGraphics->GetTargetWidth() < item_Position.x)
	{
		return;
	}
	if (!item_Appear && item_Type == ITEM_MUSH)
	{
		return;
	}
	//�e�N�X�`���̕`��
	item_pTexture->Render(item_Position.x - wx, item_Position.y - wy,item_SrcRect);
}

/**
 * �f�o�b�O�`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CItem::RenderDebug(float wx, float wy) {
	//��\��
	if (!item_Show)
	{
		return;
	}
	if (wx > item_Position.x + item_pTexture->GetWidth() || wx + g_pGraphics->GetTargetWidth() > item_Position.x)
	{
		return;
	}
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));
}

/**
 * ���
 *
 */
void CItem::Release(void) {
	item_Motion.Release();
}


void CItem::BlockJump(bool jumpFlg)
{
	item_BlockJump = jumpFlg;
}